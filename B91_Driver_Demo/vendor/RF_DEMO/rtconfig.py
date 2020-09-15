import os
ARCH     = 'risc-v'
CPU      = 'e310'
# toolchains options
CROSS_TOOL  = 'gcc'

#------- toolchains path -------------------------------------------------------
if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = '/usr/bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
#BUILD = 'release'

CORE = 'risc-v'
MAP_FILE = 'rf_demo.map'
#LINK_FILE = './freedom-e-sdk/bsp/env/freedom-e300-hifive1/flash.lds'
LINK_FILE = '../../boot.link'
TARGET_NAME = 'rf_demo.bin'

#------- GCC settings ----------------------------------------------------------
if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'riscv32-elf-'
    CC = PREFIX + 'gcc'
    CXX= PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    #TARGET_EXT = 'lst'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    NM = PREFIX + 'nm'
    READELF = PREFIX + 'readelf'

    #DEVICE = ' -march=rv32imac -mabi=ilp32 -DUSE_PLIC -DUSE_M_TIME -DNO_INIT -mcmodel=medany -msmall-data-limit=8 -L.  -nostartfiles  -lc '
    DEVICE = ' -O2 -flto -g3 -Wall -mcpu=d25f -ffunction-sections -fdata-sections -c -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fshort-wchar -fuse-ld=bfd -MMD -MP '
    CFLAGS = DEVICE
    #CFLAGS += ' -save-temps=obj'
    #AFLAGS = '-c'+ DEVICE + ' -x assembler-with-cpp'
    AFLAGS = DEVICE
    #AFLAGS += ' -Iplatform -Ifreedom-e-sdk/bsp/include -Ifreedom-e-sdk/bsp/env'
    LFLAGS = ' -O2 -nostartfiles -static -flto -g3 -mcpu=d25f -ffunction-sections -fdata-sections -fmessage-length=0 -fno-builtin -fomit-frame-pointer -fno-strict-aliasing -fshort-wchar -fuse-ld=bfd'
    LFLAGS += ' -T ' + LINK_FILE
    LFLAGS += ' -Wl,--gc-sections,-cref,-Map=' + MAP_FILE
    #LFLAGS += ' -Wl,--gc-sections, -Map=' + MAP_FILE
    #LFLAGS += ' -T ' + LINK_FILE
    #LFLAGS += ' -Wl,-wrap=memset'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -g3'
        AFLAGS += ' -g3'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = NM + ' -n -l -C $TARGET  > symbol.txt \n'
    POST_ACTION = READELF + ' -a $TARGET  > readelf.txt \n'
    POST_ACTION = OBJCPY + ' -S -O binary $TARGET '  + TARGET_NAME + '\n'
    POST_ACTION += SIZE + ' $TARGET' + '\n'
