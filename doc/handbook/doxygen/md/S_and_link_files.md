@page Asm_and_link S and link files

# Use of combinations

According to different usage scenarios, we can choose the corresponding combination.

----------------------------------------------------------------------------------------------------------------------------------------
Usage scenario                                                          S file                         link file
----------------------------------------------------------------------- ------------------------------ ---------------------------------
Common boot from flash                                                  cstartup_b91_flash.S           flash_boot.link

Used when testing performance (coremark and                             cstartup_b91_flash.S           flash_boot_ramcode.link
dhrystone)

Used to load to ram to start the program, cannot                        cstartup_b91_ram.S             ram_boot.link  
be loadedto the flash for execution

----------------------------------------------------------------------------------------------------------------------------------------

The differences in the S files therein are as follows:

------------------------------------------------------------------------------------
S file                   Description
------------------------ -----------------------------------------------------------
cstartup_b91_flash.S     It is the S file required to start the program from flash.

cstartup_b91_ram.S       It is the S file required to start the program  from ram.

------------------------------------------------------------------------------------

The differences in link files are as follows:

-------------------------------------------------------------------------------------------------------------------------
link file                        Description
-------------------------------- ----------------------------------------------------------------------------------------
flash_boot.link                  Used in normal usage scenarios.

flash_boot_ramcode.link          The only difference with the flash_boot.link file is that it puts all the segments except the vector segment needed for booting into the ramcode segment, and all the programs run in ram, which makes the execution time fast.

ram_boot.link                    This file is used to load to ram to start the program, cannot be loaded to flash for execution. This link file works with cstartup_b91_ram.S file.

-------------------------------------------------------------------------------------------------------------------------

# Configuration method

## Link

You can select the link file to be used by the following configuration.

![link file configuration](pic/linkfileconfiguration.png "link file configuration")

## S file

S files are selected differently by the following macro definitions.

![Macro definitions for distinguishing S files](pic/macrodefinitionsfordistinguishingSfiles.png "Macro definitions for distinguishing S files")

Macros can be defined in the following way to decide which S file to choose to use.

![Selecting macro definitions for S files](pic/selectingmacrodefinitionsforSfiles.png "Selecting macro definitions for S files")

## objdump.txt

The relevant distributions of VMA and LMA can be seen in the generated objdump.txt file.

The following figure shows an objdump.txt file generated by compiling with cstartup_b91_flash.S and flash_boot.link file.

In this file, the VMA and LMA addresses of vectors and text are the same, and these two segments are taken from the flash for execution.

![The VMA and LAMA addresses of vectors and text](pic/thevmaandlamaaddressesofvectorsandtext.png "The VMA and LAMA addresses of vectors and text")

The VMA and LMA addresses of retention_reset, retention_data, and ram_code are different. The LMA address is the flash address, and the VMA address is the IRAM address. In the S file, it will move these three segments from the flash to the IRAM correspondingly.

![VMA and LMA addresses of retention_reset, retention_data, and ram_code](pic/vmaandlmaaddressesofretentionresetretentiondataandramcode.png "VMA and LMA addresses of retention_reset, retention_data, and ram_code")

The addresses of VMA and LMA of data segment are different, the address of LMA is in flash and the address of VMA is in DRAM.

In the S file, the data segment will be moved from flash to DRAM correspondingly.

![The VMA and LMA addresses of data segment](pic/thevmaandlmaaddressesofdatasegment.png "The VMA and LMA addresses of data segment")

# Link file details

## Code detail

Take the flash_boot.link file as an example:

```C
// Set the code entry to _RESET_ENTRY
ENTRY(_RESET_ENTRY)
SECTIONS
{
// Define the variable NDS_SAG_LMA_FLASH = 0x20000000
    NDS_SAG_LMA_FLASH = 0x20000000 ;
//specify the current address is 0x20000000 (without AT addresses involved are VMA), the point is to represent the current address
//VMA(Virtual Memory Address): is the address where the program is running.
//LMA(Load Memory Address): The load address, here can be simply understood as the address in flash.
    . = 0x20000000;	
// Define the variable BIN_BEGIN equal to the current address
    PROVIDE (BIN_BEGIN = .) .
// Define vectors segment, VMA address and LMA address are 0x2000000, so no AT commands are added here.
// that is, the vectors segment is loaded and run at 0x20000000 (here 0x20000000 is the base address of the flash, that is, vectors segment is stored in the flash 0x20000000, and also from this address to take the commands to run)
//keep is equivalent to telling the compiler that this section should not be garbage collected. The garbage collection is to remove unused sections and not output to the output file, set with the --gc-sections option. But you can use KEEP to keep it. For example, the following vectors section is required to be kept.
    .vectors      : { KEEP(*(.vectors )) }
//Specify the current location as 0x0 (which is the starting address of IRAM)
    . = 0x00000000;
//Define the retention_reset segment with VMA address 0x0
//LMA address= ALIGN(LOADADADDR (.vectors) + SIZEOF (.vectors),8)
//LOADADDR (section): Get the address of the LMA of the section.
//SIZEOF (section): Get the size of the section
//AT (addr): Define the address of the LMA of this segment.
// When VMA and LMA do not match, you need to set LMA with AT commands
    .retention_reset  : AT( ALIGN(LOADADDR (.vectors) + SIZEOF (.vectors),8))
     { KEEP(*(.retention_reset )) }
// some addresses of retention_reset segment of VMA, LMA need to be saved to the variable, S file will be used.
    PROVIDE (_RETENTION_RESET_VMA_START = ADDR(.retention_reset));
    PROVIDE (_RETENTION_RESET_LMA_START = LOADADADDR(.retention_reset));
    PROVIDE (_RETENTION_RESET_VMA_END = .) .
//The aes_data segment can be only in the first 64K addresses of the IRAM, so please do not modify its location if you are not sure of the usage.
// Set current address = . Address aligned by 8
// If no value (point) is assigned to the current address, the addresses of all segments will be listed in order.
    . = ALIGN(8);
    PROVIDE (_AES_VMA_START = .) .
    .aes_data   (NOLOAD)  : { KEEP(*(.aes_data )) }
    PROVIDE (_AES_VMA_END = .) .
    . = ALIGN(8);
    .retention_data : AT( ALIGN(LOADADDR (.retention_reset) + SIZEOF (.retention_reset),8))
      { KEEP(*(.retention_data )) }
    PROVIDE (_RETENTION_DATA_VMA_START = ADDR(.retention_data));
    PROVIDE (_RETENTION_DATA_LMA_START = LOADADADDR(.retention_data));
    PROVIDE (_RETENTION_DATA_VMA_END = .) .

    . = ALIGN(8);
    .ram_code : AT( ALIGN(LOADADDR (.retention_data) + SIZEOF (.retention_data),8))
      { KEEP(*(.ram_code )) }
    PROVIDE (_RAMCODE_VMA_END = .) .
    PROVIDE (_RAMCODE_VMA_START = ADDR(.ram_code));
    PROVIDE (_RAMCODE_LMA_START = LOADADADDR(.ram_code));
    PROVIDE (_RAMCODE_SIZE = SIZEOF (.ram_code));
    . = ALIGN(LOADADADDR (.ram_code) + SIZEOF (.ram_code), 8);
    .text   : AT(ALIGN(LOADADADDR (.ram_code) + SIZEOF (.ram_code), 8))
       { *(.text .stub .text.* .gnu.linkonce.t.* ) KEEP(*(.text.*personality* )) *(.gnu.warning ) }
    . rodata   : AT(ALIGN(LOADADADDR (.text) + SIZEOF (.text), ALIGNOF(. rodata)))
       { *(. rodata . rodata.* .gnu.linkonce.r.* )}
//Added allocation of segments of eh_frame/eh_frame_hdr, compile error will occur if there is no allocation when using puts function
    .eh_frame_hdr 	: AT(ALIGN(LOADADADDR (. rodata) + SIZEOF (. rodata), ALIGNOF(.eh_frame_hdr)))
        { *(.eh_frame_hdr ) }
    . = ALIGN(0x20);
    .eh_frame : AT(ALIGN(LOADADDR (.eh_frame_hdr) + SIZEOF (.eh_frame_hdr), 32))
        { KEEP(*(.eh_frame )) }
//allocate memory space for the command compression table.exec.itable
    .exec.itable : AT(ALIGN(LOADADDR (.eh_frame) + SIZEOF (.eh_frame), ALIGNOF(.exec.itable)))
        { KEEP(*(.exec.itable)) }

    . = 0x00080000;
    PROVIDE( __global_pointer$ = . + (4K / 2) );
// ALIGNOF(.data): return the alignment requirement of the VMA of data.
// If the section has been allocated, it will return the aligned byte named “section”. The linker will report an error if the section has not been allocated yet.
    .data : AT(ALIGN(LOADADADDR (.exec.itable) + SIZEOF (.exec.itable), ALIGNOF(.data)))
        { *(.data .data.* .gnu.linkonce.d.* ) KEEP(*(.gnu.linkonce.d.*personality* )) SORT(CONSTRUCTORS)
            \*(.srodata.cst16 ) \*(.srodata.cst8 ) \*(.srodata.cst4 ) \*(.srodata.cst2 ) \*(. srodata . srodata.\* ) \*(. sdata . sdata.\* .gnu.linkonce.s.\* ) \*(.sdata2 .sdata2.\* .gnu.linkonce.s.\* )
        }
    PROVIDE (_DATA_VMA_END = .) .
    PROVIDE (_DATA_VMA_START = ADDR(.data));
    PROVIDE (_DATA_LMA_START = LOADADDR(.data));
//BIN_SIZE = LMA address of data segment + size of data segment - BIN_BEGIN.
//The bin file is actually the LMA of all the segments stitched together and generally arranged in order (the values in the AT commands are set according to this rule)
    PROVIDE (BIN_SIZE = LOADADDR(.data) + SIZEOF(.data) - BIN_BEGIN);
//Each output section can have a type, and the type is a keyword enclosed in parentheses.
// NOLOAD, section is marked as a non-loadable type and will not be loaded into memory when the program runs.
//The bss segment does not need to be loaded, the S file will zero out the VMA address space of the bss segment.
    . = ALIGN(8);
    PROVIDE (_BSS_VMA_START = .) .
    . sbss (NOLOAD) : { \*(. dynsbss ) \*(. sbss . sbss.\* .gnu.linkonce.sb.* ) \*(. scommon . scommon.\* ) }
    . bss  (NOLOAD) : { \*(. dynbss ) \*(. bss . bss.\* .gnu.linkonce.b.\* ) \*(COMMON ) . = ALIGN(8); }
    PROVIDE (_BSS_VMA_END = .) .

    . = ALIGN(8);
//_end is the starting address of the heap, the heap is growing upwards, and generally we set it in the space not used after bss
// functions like sprintf/malloc/free are called, these functions will call the _sbrk function to allocate heap memory, and _sbrk will determine where to start allocating heap space via the _end symbol (usually the end of the .bss segment), otherwise a link error will occur.
    _end = .
    PROVIDE (end = .) .
//Define the start address of the stack, here the end location of DRAM is defined.
    PROVIDE (_STACK_TOP = 0x00a0000);
    PROVIDE (FLASH_SIZE = 0x0100000);
}

ASSERT((BIN_SIZE)<= FLASH_SIZE, "BIN FILE OVERFLOW");
```

## Alignment

The link file involves some alignment rules. If it involves multiple segments moved together, you need to pay attention to the alignment of these segments. When the starting address of LMA and VMA are not consistent, multiple segments moving together is likely to encounter move error.

The following is an example of an error:

The code in the S file is trying to move the sdata and data segments from the LMA to the VMA. The starting address of the VMA is 0x00080000 and the starting address of the LMA is related to the previous code and is aligned according to the alignment rules of the VMA for sdata.

![Example of error in link file alignment rules](pic/exampleoferrorinlinkfilealignmentrules.png "Example of error in link file alignment rules")

The following figure shows an error-prone lst file compiled with the above link file.

![The lst file with error](pic/thelstfilewitherror.png "The lst file with error")

There are several methods of modification:

(1) Move one segment at a time so that you don't have the problems above.

(2) Merge sdata, data segments.

# S file details

Take the cstartup_b91_flash.S file as an example.

## Code detail

```C
// Define the vector segment, the code starting after this sentence belongs to the vectors segment, until the next segment name encountered, or the end of the file
// where "ax" means the section is assignable and executable
//`a' section is allocable `x' section is executable
.section .vectors, "ax" 
.option push        //push saves the current .option configuration
.option norelax    //set to norelax
.org 0x0          //The pseudo command .org is telling the compiler the offset address of the next command. Set the offset address to 0.
//The .global pseudo-command is used to define a global symbol that allows the linker to recognize it globally, that is a symbol defined in a program file can be visible to all other program files.
.global _RESET_ENTRY 
// The .type pseudo-command is used to define the type of the symbol. The following is the definition of _RESET_ENTRY as a function
.type _RESET_ENTRY,@function
// The .align pseudo-command is used to push the current PC address to a location aligned to "the integer power of 2 bytes". The following is to push the current PC address to 4 bytes aligned.
.align 2
//The label _RESET_ENTRY is the entry address of the program.
_RESET_ENTRY:
//The entry address of the program must be an executable command, here is a jump command to the label _START
    j     _START
// Set the offset address to 0x18 to store BIN_SIZE (4 bytes), BIN_SIZE is defined in the link file.
    .org 0x18
    .word (BIN_SIZE)
// Set the offset address to 0x20 to store the keyword, this location must be this value, otherwise the program will not run.
    .org 0x20
    .word ('T'<<24 | 'L'<<16 | 'N'<<8 | 'K')
// Set the offset address to 0x26 to store the flash configuration, later the flash fetching command will decide which protocol to go according to this configuration.
//The following 6 are supported and can be selected according to flash model.
     .org 0x26
     //.short (0x0003) //READ: cmd:1x, addr:1x, data:1x, dummy:0
    //.short (0x070B) //FREAD: cmd:1x, addr:1x, data:1x, dummy:8
    .short (0x173B) //DREAD: cmd:1x, addr:1x, data:2x, dummy:8
    //.short (0x53BB) //X2READ: cmd:1x, addr:2x, data:2x, dummy:4
    //.short (0x276B) //QREAD: cmd:1x, addr:1x, data:4x, dummy:8
    //.short (0x65EB) //X4READ: cmd:1x, addr:4x, data:4x, dummy:6
// Use pop to restore .option configuration
.option pop 
//4 byte alignment
    .align 2

_START:
//This is for debug use, it will output PB4 high. It is generally used to check the status, the default is off.
#if 0
    lui   t0,0x80140        //0x8014030a
    li    t1, 0xef
    li    t2, 0x10
    sb    t1 , 0x30a(t0)   //0x8014030a PB oen = 0xef
    sb    t2 , 0x30b(t0)   //0x8014030b PB output = 0x10
#endif
    //initialize the global pointer gp register, __global_pointer$ is defined in the link file.
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
//initialize stack pointer sp register, _STACK_TOP is defined in the link file.
     la t0, _STACK_TOP
    mv sp, t0

#ifdef __nds_execit
// Set the command compression table and address
    la t0, _ITB_BASE_
    csrw uitb , t0
#endif
// Set FS to 0b11, clear fscsr (is the processing that needs to be done before floating point operations)
#ifdef __riscv_flen
    /* Enable FPU */
    li t0, 0x00006000
    csrrs t0, mstatus , t0
    /* Initialize FCSR */
    fscsr zero
#endif
// Set the interrupt entry base address
    la t0, __vectors
    csrw mtvec, t0
// enable interrupt vector mode (need to enable two places, no modification here)
    /* Enable vectored external plic interrupt */
    csrsi mmisc_ctl, 2

    /*vector mode enable bit (VECTORED) of the Feature Enable Register */
    lui    t0, 0xe4000
    li     t1, 0x02
    sw     t1, 0x0(t0)   //(*(volatile unsigned long*)(0xe4000000))= 0x02
// Enable I/D-Cache
    csrr t0, mcache_ctl
    ori t0, t0, 1 #/I-Cache
    ori t0, t0, 2 #/D-Cache
    csrw mcache_ctl, t0
    fence.i
//Move the retention_reset segment from flash to ram

_RETENTION_RESET_INIT:
    la t1, _RETENTION_RESET_LMA_START
    la t2, _RETENTION_RESET_VMA_START
    la t3, _RETENTION_RESET_VMA_END
_RETENTION_RESET_BEGIN:
    bleu t3, t2, _RETENTION_DATA_INIT
    lw t0, 0(t1)
    sw t0, 0(t2)
    addi t1, t1, 4
    addi t2, t2, 4
    j _RETENTION_RESET_BEGIN
//Move the retention_data segment from flash to ram
_RETENTION_DATA_INIT:
    la t1, _RETENTION_DATA_LMA_START
    la t2, _RETENTION_DATA_VMA_START
    la t3, _RETENTION_DATA_VMA_END
_RETENTION_DATA_INIT_BEGIN:
    bleu t3, t2, _RAMCODE_INIT
    lw t0, 0(t1)
    sw t0, 0(t2)
    addi t1, t1, 4
    addi t2, t2, 4
    j _RETENTION_DATA_INIT_BEGIN
//Move ram_code segment from flash to ram
_RAMCODE_INIT:
    la t1, _RAMCODE_LMA_START
    la t2, _RAMCODE_VMA_START
    la t3, _RAMCODE_VMA_END
_RAMCODE_INIT_BEGIN:
    bleu t3, t2, _DATA_INIT
    lw t0, 0(t1)
    sw t0, 0(t2)
    addi t1, t1, 4
    addi t2, t2, 4
    j _RAMCODE_INIT_BEGIN
//Move data segments from flash to ram
_DATA_INIT:
    la t1, _DATA_LMA_START
    la t2, _DATA_VMA_START
    la t3, _DATA_VMA_END
_DATA_INIT_BEGIN:
    bleu t3, t2, _ZERO_BSS
    lw t0, 0(t1)
    sw t0, 0(t2)
    addi t1, t1, 4
    addi t2, t2, 4
    j _DATA_INIT_BEGIN
//clear the bss segment to zero
_ZERO_BSS:
    lui t0, 0
    la t2, _BSS_VMA_START
    la t3, _BSS_VMA_END
_ZERO_BSS_BEGIN:
    bleu t3, t2, _ZERO_AES
    sw t0, 0(t2)
    addi t2, t2, 4
    j _ZERO_BSS_BEGIN
// Clear the AES segment to zero
_ZERO_AES:
    lui t0, 0
    la t2, _AES_VMA_START
    la t3, _AES_VMA_END
_ZERO_AES_BEGIN:
    bleu t3, t2, _FILL_STK
    sw t0, 0(t2)
    addi t2, t2, 4
    j _ZERO_AES_BEGIN
//The stack area are initialized to 0x55, the default code is not open, because the ram is relatively large and will be more time-consuming. If the debug needs, it can be opened to use.
_FILL_STK:
#if 0
    lui t0, 0x55555
    addi t0, t0, 0x555
    la t2, _BSS_VMA_END
    la t3, _STACK_TOP
_FILL_STK_BEGIN:
    bleu t3, t2, _MAIN_FUNC
    sw t0, 0(t2)
    addi t2, t2, 4
    j _FILL_STK_BEGIN
#endif
//jump to the main function
_MAIN_FUNC:
    nop
//Use j or jal can only jump to [-524288,524287], beyond this range we can only use jalr to achieve, in order to avoid such problems, we uniformly use jalr to jump.
    la t0, main
    jalr t0

    nop
    nop
    nop
    nop
    nop
_END:
j _END 

//Define a macro with the name INTERRUPT, the parameter is num, and the macro ends at .endm
.macro INTERRUPT num
//Weak definition
.weak entry_irq\num
.set entry_irq\num, default_irq_entry
.long entry_irq\num
.endm
//There are a total of 64 interrupt sources
#define VECTOR_NUMINTRS 63
.section .ram_code, "ax"
//Define ram_code segment, all interrupt entry address should be in ram_code, so as to enter interrupt quickly.
.global __vectors
// There are 64 interrupt sources, and the formula for the alignment that needs to be set here is: 2ceiling(log2(N))+2, and N is 64, so the it should be set to 256 alignment here.
.balign 256

__vectors:
    .long trap_entry
//Actually here is a for loop that defines the 63 interrupt entry addresses in addition to the trap interrupt.
//after expansion is:
//.weak entry_irq1
//.set entry_irq1, default_irq_entry
//.long entry_irq1
//.........
//.weak entry_irq63
//.set entry_irq63, default_irq_entry
//.long entry_irq63
//We use vector mode, after an interrupt occurs, the pc will point to address __vectors +4*interrupt ID, if the interrupt ID is 2, it will jump to entry_irq2
.altmacro
.set irqno, 1
.rept VECTOR_NUMINTRS/* .rept .endr */
INTERRUPT %irqno
.set irqno, irqno+1
.endr
```

## Differences between vectors and retention_reset segments

The retention_reset is the startup code that will run when comes back from retention.

The current retention_reset processing is not to move these segments (retention_reset, retention_data, ram_code) from flash to ram, because these segments are retained during the retention phase and will not be lost. The condition for this processing is that the size of the retention ram is larger than these segments, and if there is more than that, then the move action needs to be done.

The retention_reset boot part requires more processing than the vectors, include: flash wake-up, multi-address register recovery. which is a must-do processing coming from the retention.

## Others

### Notes on the use of .org

In the current compilation environment, .org and Link Time Optimization (-flto) in the optimization option cannot be used at the same time. However, (-flto) is definitely selected in order to compile a small bin file, so if you want to use .org in the S file, you need to use it as follows:

![The Link TimeOptimization (-flto) in optimization options](pic/thelinktimeoptimizationinoptimizationoptions.png "The Link TimeOptimization (-flto) in optimization options")

```C
.option push       //push saves the current .option configuration
.option norelax   // set to norelax
.org 0x0         //set .org
.........
.option pop     // Use pop to restore the .option configuration
```

The description of .option is as follows:

The .option pseudo-command is used to set certain architecture-specific options that enable the assembler to recognize the option and act according to the definition of the option.

The push, pop are used to temporarily save or restore the options specified by the .option pseudo-command:

The ".option push" pseudo-command temporarily saves the current option settings, allowing new options to be specified later using the .option pseudo-command, while the ".option pop" pseudo-command restores the most recently saved option settings to take effect again.

The combination of ".option push" and ".option pop" makes it possible to set different options specifically for a section of code embedded in an assembly program without affecting the global option settings.

### Compression command

The RISC-V's C Extension, which refers to replacing 32bit commands with 16bit commands, and Andes' CoDense (Code Dense) technology puts 32bit commands inside the command table and replaces them with 16 EXEC.IT 0xxxxx where the original 32bit commands appear.

The macro \__nds_execit is set to be on by compiler default, while \_ITB_BASE_ will be set to the first address of .exec.itable.

Set _ITB_BASE_ to register uitb in the S file as the base address of the command table. The compression instructions are put into the .exec.itable segment.

### FPU enable

The macro \__riscv_flen is set to be on by compiler default.

Before executing a floating-point command, the mstatus<14:13> FS segment needs to be changed to a non-zero value, otherwise a command exception will occur. So the S file sets FS to 0b11 and initializes the floating-point control status register FCSR to 0.