Program:    PSPEText
Version:    1.1
License:    GNU GLP Version 3
Copyright:  Copyright (c) 2009 Norman B. Lancaster (QBRADQ)
Contact:    qbradq@gmail.com

ABOUT
PSPEText is a kernel-mode plugin that allows you to suspend any PSP game at
any time and read text files stored on the memory stick. This is useful for
reading FAQs from sites like www.gamefaqs.com while playing your favorite PSP
games.

This text reader features an 80-column display, which is a must-have for
reading FAQ files.

LICENSE
PSPEText is Free and Open Source Software released under the GNU GPL version
3. Please see license.txt for the full license text.

INSTALLATION
Copy the file pspetext.prx to your PSP's /seplugins directory. Now add a line
to your game.txt, game150.txt, pops.txt etc. file to enable the plugin for
those game types. The line should look like this:

ms0:/seplugins/pspetext.prx 1

See the included game.txt for an example.

COMPATIBILITY
PSPEText should work with all games in all graphics modes. It has been tested
on a PSP Slim running the 5.50 GEN-A firmware with a wide variety of games.
At this time no games are known to fail to load with this module loaded. In a
very few games the text reader does not actually work, but in those cases the
game still works fine with the module loaded.

USAGE
Once your game has loaded, press and hold the left trigger, right trigger,
down arrow and cross keys for two seconds. A brief splash screen will display,
followed by the file load menu. Press the Select button to see usage.

Note that in some games the splash screen is more of a quick flicker.
This is normal.

Controller mapping:
********************* Common Controls *********************
[DPAD Up]    Move one line up
[DPAD Down]  Move one line down
[DPAD Left]  Move one page up
[DPAD Right] Move one page down
[Select]     Display this help file
[Start]      Exit
******************* File View Controls ********************
[Triangle]   Open a new file
****************** File Select Controls *******************
[Triangle]   Got to parent directory
[Cross]      Select file or directory
***********************************************************
