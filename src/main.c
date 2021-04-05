/*
 *   PSPEText
 *
 *   Copyright (c) 2008-2009 Norman B. Lancaster
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include <pspkernel.h>
#include <pspctrl.h>
#include <stdio.h>
#include <pspthreadman.h>

#include "pspetext.h"
#include "debug.h"

PSP_MODULE_INFO("pspetext", 0x1000, 0, 0);
PSP_HEAP_SIZE_KB(0);
int module_start (SceSize argc, void* argp) __attribute__((alias("plugin_entry")));

SceUID pluginThread;
SceUID runingUids[256];
int runingUids_num;

int plugin_thread(SceSize argc, void* argp)
{
	int padTime = 0;
	int i, waitCount = 0;
	SceCtrlData pad;

	debugPrintf("plugin_thread()\n");

	while(1)
	{
		// Read the controls and update the timer
		sceCtrlPeekBufferPositive(&pad, 1);
		if(pad.Buttons & PSP_CTRL_LTRIGGER &&
			pad.Buttons & PSP_CTRL_RTRIGGER &&
			pad.Buttons & PSP_CTRL_DOWN &&
			pad.Buttons & PSP_CTRL_CROSS)
		{
			padTime ++;
		}
		else padTime = 0;

		// If the time has come trigger off the application
		#ifndef	PSPLINK_DEBUG
		if(padTime >= 10)
		#endif//PSPLINK_DEBUG
		{
			// Suspend all game threads (or at least threads that did not exist before we did)
			if(sceKernelGetThreadmanIdList(SCE_KERNEL_TMID_Thread,
				runingUids, 256, &runingUids_num) < 0)
			{
				debugPrintf("sceKernelGetThreadmanIdList() failed.\n");
			}
			else
			{
				waitCount = 0;;
				while(1)
				{
					sceKernelDelayThread(5000);
					int readyFound = 0;
					for(i = 0; i < runingUids_num; i ++)
					{
						// Skip our own thread
						if(pluginThread == runingUids[i]) continue;

						// Check thread information.
						SceKernelThreadInfo info;
						info.size = sizeof(SceKernelThreadInfo);
						int ret = sceKernelReferThreadStatus(runingUids[i], &info);
						if(ret != 0)
						{
							debugPrintf("sceKernelReferThreadStatus() failed 0x%08X\n", ret);
						}
						// Skip kernel threads
						if((info.attr & 0x80000000) == 0) continue;
						// Skip ready threads
						if((info.status & PSP_THREAD_READY) != 0)
						{
							debugPrintf("Waiting for thread %d\n", runingUids[i]);
							readyFound = 1;
							continue;
						}
						//dump_thread_info(runingUids[i]);
						// Skip already suspended threads
						if((info.status & PSP_THREAD_SUSPEND) != 0) continue;

						// Suspend the thread
						int code = sceKernelSuspendThread(runingUids[i]);
						if(code < 0)
						{
							debugPrintf("Unable to suspend thread %d code 0x%08X\n", runingUids[i], code);
						}
						else
						{
							debugPrintf("Suspended thread %d\n", runingUids[i]);
						}
					}

					// If no threads are ready then continue.
					if(readyFound == 0)
					{
						waitCount = 0;
						break;
					}

					waitCount++;
					// 2.5 second max wait
					if(waitCount > 50) break;
				}
			}

			// Execute PSPEText main function if we successfully stoped all threads.
			if(waitCount == 0)
			{
				petMain();
				padTime = 0;
			}

			// Resume all threads suspended earlier
			for(i = 0; i < runingUids_num; i ++)
			{
				if(sceKernelResumeThread(runingUids[i]) < 0)
				{
					debugPrintf("Unable to resume thread %d\n", runingUids[i]);
				}
				else
				{
					debugPrintf("Resuming thread %d\n", runingUids[i]);
				}
			}
		}

		// Sleep
		sceKernelDelayThread(100000);
	}

	sceKernelSleepThread();

	return 0;
}


int pet_sceKernelRegisterExitCallback(int cbid)
{
	debugPrintf("pet_sceKernelRegisterExitCallback(%d)\n", cbid);
	return cbid;
}

int plugin_entry(SceSize argc, void* argp)
{
	int (*plugin_thread_func)(SceSize args, void *argp) = plugin_thread;

	debugPrintf("plugin_entry()\n");
	//plugin_thread_func = (void *) ((u32) plugin_thread_func & 0x7fffffff);

	pluginThread = sceKernelCreateThread("plugin_thread", (void*)plugin_thread_func, 0x18, 0x800, 0, NULL);
	if(pluginThread >= 0)
	{
		// Start our thread
		debugPrintf("Starting thread %d\n", pluginThread);
		sceKernelStartThread(pluginThread, argc, argp);
		sceKernelDelayThread(100000);
		debugPrintf("sceKernelStartThread() returned\n");
	}
	else
	{
		debugPrintf("sceKernelCreateThread() : 0x%08X\n", pluginThread);
	}

	return 0;
}
