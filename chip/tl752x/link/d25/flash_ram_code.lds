OUTPUT_ARCH("riscv")

ENTRY(_reset_entry)

__heap_size = 8K;
__stack_size = 8K;

MEMORY
{
    dlm (xrw)     : ORIGIN = 0x80000, LENGTH = 64K
    ilm (rx)      : ORIGIN = 0, LENGTH = 192K
    flash(rx)     : ORIGIN = 0x10000000 , LENGTH = 1024K
    idlog (rw)    : ORIGIN = 0x60000000, LENGTH = 256M   /* Fake region for ID_Log */
}

SECTIONS
{
      .init :
    {
        __ilm_start = .;
        KEEP (*(SORT_NONE(.init)))
        *(.retention_ram_code)
        . = ALIGN(8);
    } >ilm AT>flash
    
    .ilm_code :
    {
        *(.ilm_code)
        KEEP(*(.ram_code ))
        KEEP(*(.flash_init_data )) 
        KEEP(*(.flash ))
        *(.text .stub .text.* .gnu.linkonce.t.* ) KEEP(*(.text.*personality* )) *(.gnu.warning )
        KEEP(*(.eh_frame ))
        *(.eh_frame_hdr ) 
        KEEP(*(.exec.itable))     
        __ilm_end = .;
        . = ALIGN(4);
    } >ilm AT>flash

    
    . = ALIGN(4);

    .rwdata    :
    {
        _vmadata = .;
        *(.retention_data)
        *(.data .data.* .gnu.linkonce.d.* ) KEEP(*(.gnu.linkonce.d.*personality* )) SORT(CONSTRUCTORS)
          *(.rodata .rodata.* .gnu.linkonce.r.* )
          *(.srodata.cst16 ) *(.srodata.cst8 ) *(.srodata.cst4 ) *(.srodata.cst2 ) *(.srodata .srodata.* ) *(.sdata .sdata.* .gnu.linkonce.s.* ) *(.sdata2 .sdata2.* .gnu.linkonce.s.* ) 
        *(.noncacheable .noncacheable.* )
        _edata = .;
        . = ALIGN(4);
    }>dlm AT>flash

  /* used by the startup to initialize data */
    PROVIDE(_lmadata = LOADADDR(.rwdata));

      .bss    :
      {
          __bss_start = .;
          *(.sbss*)
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
      } >dlm AT>dlm

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

      /* Catch common orphans so they don't fall into IDLOG by accident */
      /DISCARD/ : { *(.note.*) *(.comment) *(.gnu*) }

      /* Hard stop if IDLOG would overflow */
      ASSERT((__idlog_end - __idlog_start) <= LENGTH(idlog),
         "Too many IDLOG entries: increase IDLOG LENGTH")
}
