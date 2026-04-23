OUTPUT_ARCH("riscv")

ENTRY(_reset_entry)

__heap_size = 8K;
__stack_size = 8K;

MEMORY
{
	dlm (xrw)        : ORIGIN = 0x80000, LENGTH = 128K
	ilm (xrw)         : ORIGIN = 0x0, LENGTH = 384K+128K
	shram01(xrw)     : ORIGIN = 0x50060000, LENGTH = 54K+74K
	idlog (rw)    : ORIGIN = 0x60000000, LENGTH = 256M   /* Fake region for ID_Log */
}

SECTIONS
{
  	.init	:
	{
	    KEEP (*(SORT_NONE(.init)))
		. = ALIGN(4);
	} >ilm AT>ilm
    
    .ilm_code :
	{
		*(.retention_ram_code)
		*(.ilm_code)
		KEEP(*(.ram_code ))
		KEEP(*(.flash_init_data )) 
		KEEP(*libgcc.a:save-restore.o) KEEP(*(.exec.itable))
		. = ALIGN(4);
	} >ilm AT>ilm

  	.text	:
  	{
        *(.flash)
    	*(.text .stub .text.* .gnu.linkonce.t.* ) KEEP(*(.text.*personality* )) *(.gnu.warning ) 
		. = ALIGN(4);
  	} >ilm AT>ilm

	.eh_frame_hdr 	:
	{
		*(.eh_frame_hdr )
	} >ilm AT>ilm

	. = ALIGN(4);
	.float_sec :
	{
		__float_sec_start = .;
		*(.float_sec)
		__float_sec_end = .;
		. = ALIGN(4);
	} >ilm AT>ilm

	. = ALIGN(0x20);
	.eh_frame 	:
	{
		KEEP(*(.eh_frame ))
	} >ilm AT>ilm
	. = ALIGN(4);

    PROVIDE (_ILM_VMA_START = ADDR(.init));
    PROVIDE (_ILM_LMA_START = LOADADDR(.init));
    PROVIDE (_ILM_VMA_END = .);
    PROVIDE (_ILM_SIZE = (_ILM_VMA_END) -(_ILM_VMA_START));
    

	.shram01_bss(NOLOAD) :
	{
		*(.shram01_hci_rx);
		*(.shram01_hci_tx);
	}>shram01 AT>shram01

    .rwdata	:
  	{
		_vmadata = .;
		*(.retention_data)
	   *(.data .data.* .gnu.linkonce.d.* ) KEEP(*(.gnu.linkonce.d.*personality* )) SORT(CONSTRUCTORS) 
          *(.rodata .rodata.* .gnu.linkonce.r.* )
          *(.srodata.cst16 ) *(.srodata.cst8 ) *(.srodata.cst4 ) *(.srodata.cst2 ) *(.srodata .srodata.* ) *(.sdata .sdata.* .gnu.linkonce.s.* ) *(.sdata2 .sdata2.* .gnu.linkonce.s.* )
		*(.noncacheable .noncacheable.* )
		_edata = .;
		. = ALIGN(4);
  	} >dlm AT>ilm

  /* used by the startup to initialize data */
	PROVIDE(_lmadata = LOADADDR(.rwdata));
	
	PROVIDE (_DATA_VMA_END = .);    
    PROVIDE (_DATA_VMA_START = ADDR(.rwdata));
    PROVIDE (_DATA_LMA_START = LOADADDR(.rwdata));
    PROVIDE (_DATA_LMA_START_OFFSET = LOADADDR(.rwdata)- LOADADDR(.init));
   
  	.bss	:
  	{
  		__bss_start = .;
  		*(.sbss*)
	    *(.bss .bss.*)
		*(COMMON)
		__bss_end = .;
  	} >dlm AT>dlm
  	
    PROVIDE (_DLM_SIZE = (__bss_start) -(_vmadata));

    . = ALIGN(8);
    _end = .;
    PROVIDE (end = .);

  	.heap ORIGIN(dlm) + LENGTH(dlm) - __stack_size - __heap_size:
  	{
		/* end is the starting address of the heap, the heap grows upward */
		PROVIDE ( __heap_start = . );
		PROVIDE ( __heap_end = ORIGIN(dlm) + LENGTH(dlm) - __stack_size);
	}

  	.stack ORIGIN(dlm) + LENGTH(dlm) - __stack_size:
  	{
		PROVIDE ( __stack_limit = .);
		PROVIDE ( __stack_top = ORIGIN(dlm) + LENGTH(dlm));
	}

	.to_be_stripped_from_bin :
	{
		__idlog_start = .;
		KEEP(*(.to_be_stripped_from_bin))
		__idlog_end = .;
	} >idlog

}
ASSERT(_ILM_SIZE <= 0x60000,"IRAM SIZE ERROR")
