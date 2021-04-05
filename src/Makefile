# Environment setup

TARGET = pspetext
OBJS = main.o font.o basecon.o input.o pspetext.o debug.o filebuf.o pet_getfile.o pet_common.o pet_fileutil.o

# Define to build this as a prx (instead of a static elf)
BUILD_PRX=1

PRX_EXPORTS=exports.exp

USE_PSPSDK_LIBC = 1

INCDIR =
CFLAGS = -O2 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LIBS =
LIBDIR =

# We set PSPSDK explicitly before calling Make
#PSPSDK=$(shell psp-config --pspsdk-path)
include /home/qbradq/data/bin/pspsdk/psp/sdk/lib/build_prx.mak
