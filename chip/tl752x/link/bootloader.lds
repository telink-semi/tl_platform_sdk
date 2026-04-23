OUTPUT_ARCH("riscv")

ENTRY(_reset_entry)

__heap_size = 0K;
__stack_remain_size = 1K;
__stack_size = 4K;

MEMORY
{
	dlm (xrw)     : ORIGIN = 0x80000, LENGTH = 32K
	ilm (rx)      : ORIGIN = 0x50060000, LENGTH = 32K
	#ilm (rx)      : ORIGIN = 0, LENGTH = 32K
}
SECTIONS
{
  	.init	:
	{
	    KEEP (*(SORT_NONE(.init)))
	} >ilm
  
    .ilm_code :
	{
		*(.ilm_code)
	} >ilm
	
  	.text	:
  	{
    	*(.text .text.*)
  	} >ilm

	.rodata	: AT(ALIGN(LOADADDR (.text) + SIZEOF (.text), ALIGNOF(.rodata)))
	{
		*(.rodata .rodata.*)
	} >ilm

	.eh_frame_hdr 	: AT(ALIGN(LOADADDR (.rodata) + SIZEOF (.rodata), ALIGNOF(.eh_frame_hdr)))
	{
		*(.eh_frame_hdr )
	} >ilm

	. = ALIGN(4);
	.float_sec : AT(ALIGN(LOADADDR (.eh_frame_hdr) + SIZEOF (.eh_frame_hdr), ALIGNOF(.float_sec)))
	{
		__float_sec_start = .;
		*(.float_sec)
		__float_sec_end = .;
	} >ilm

	. = ALIGN(0x20);
	.eh_frame 	: AT(ALIGN(LOADADDR (.float_sec) + SIZEOF (.float_sec), 32))
	{ KEEP(*(.eh_frame ))
	} >ilm
	. = ALIGN(4);

    .rwdata	: AT(ALIGN(LOADADDR (.eh_frame) + SIZEOF (.eh_frame),ALIGNOF(.rwdata)))
	{
		_vmadata = .;
		*(.data .data.* .gnu.linkonce.d.* ) KEEP(*(.gnu.linkonce.d.*personality* )) SORT(CONSTRUCTORS)
		*(.srodata.cst16 ) *(.srodata.cst8 ) *(.srodata.cst4 ) *(.srodata.cst2 ) *(.srodata .srodata.* ) *(.sdata .sdata.* .gnu.linkonce.s.* ) *(.sdata2 .sdata2.* .gnu.linkonce.s.* )
		_edata = .;
	}>dlm


  /* used by the startup to initialize data */
	PROVIDE(_lmadata = LOADADDR(.rwdata));

  	.bss	:
  	{
  		__bss_start = .;
  		*(.sbss*)
	    *(.bss .bss.*)
		*(COMMON)
		__bss_end = .;
  	} >dlm

    . = ALIGN(8);
    _end = .;
    PROVIDE (end = .);

  	. = ALIGN(8);

  	.heap ORIGIN(dlm) + LENGTH(dlm) - __stack_size - __heap_size:
  	{
		/* end is the starting address of the heap, the heap grows upward */
		PROVIDE ( __heap_start = . );
		PROVIDE ( __heap_end = ORIGIN(dlm) + LENGTH(dlm) - __stack_size);
	}

  	.stack ORIGIN(dlm) + LENGTH(dlm) - __stack_size:
  	{
		PROVIDE ( __stack_limit = .);
		PROVIDE ( __stack_trap = __stack_limit +__stack_remain_size);
		PROVIDE ( __stack_top = ORIGIN(dlm) + LENGTH(dlm));
	}
}
