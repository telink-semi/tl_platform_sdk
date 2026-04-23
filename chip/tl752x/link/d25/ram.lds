OUTPUT_ARCH("riscv")

ENTRY(_reset_entry)

__heap_size = 8K;
__stack_size = 8K;

MEMORY
{
    dlm (xrw)     : ORIGIN = 0x80000, LENGTH = 64K
    ilm (xrw)     : ORIGIN = 0x0, LENGTH = 192K
    shram01(rw)   : ORIGIN = 0x50060000 + 74K, LENGTH = 54K
    idlog (rw)    : ORIGIN = 0x60000000, LENGTH = 256M   /* Fake region for ID_Log */
}

SECTIONS
{
      .init    :
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

      .text    :
      {
        *(.text .stub .text.* .gnu.linkonce.t.* ) KEEP(*(.text.*personality* )) *(.gnu.warning ) 
        KEEP(*(.flash ))
        . = ALIGN(4);
      } >ilm AT>ilm


    .eh_frame_hdr     :
    {
        *(.eh_frame_hdr )
        . = ALIGN(4);
    } >ilm AT>ilm

    .shram01_bss(NOLOAD) :
    {
        *(.shram01_hci_tx)
        *(.shram01_hci_rx)
        *(shram01_audio)
        . = ALIGN(4);
    } >shram01 AT>shram01

    . = ALIGN(4);
    .float_sec :
    {
        __float_sec_start = .;
        *(.float_sec)
        . = ALIGN(4);
        __float_sec_end = .;
    } >ilm AT>ilm

    . = ALIGN(0x20);
    .eh_frame     :
    {
        KEEP(*(.eh_frame ))
        . = ALIGN(4);
    } >ilm AT>ilm
    . = ALIGN(4);

    .rwdata    :
    {
        _vmadata = .;
        *(.retention_data)
        *(.data .data.* .gnu.linkonce.d.* ) KEEP(*(.gnu.linkonce.d.*personality* )) SORT(CONSTRUCTORS) 
        *(.srodata.cst16 ) *(.srodata.cst8 ) *(.srodata.cst4 ) *(.srodata.cst2 ) *(.srodata .srodata.* ) *(.sdata .sdata.* .gnu.linkonce.s.* ) *(.sdata2 .sdata2.* .gnu.linkonce.s.* )
        *(.rodata .rodata.* .gnu.linkonce.r.* )
        *(.noncacheable .noncacheable.* )
        . = ALIGN(4);
        _edata = .;
    }>dlm AT>ilm


  /* used by the startup to initialize data */
    PROVIDE(_lmadata = LOADADDR(.rwdata));

      .bss    :
      {
          __bss_start = .;
          *(.sbss*)
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
      } >dlm AT>dlm

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
        PROVIDE ( __stack_top = ORIGIN(dlm) + LENGTH(dlm));
    }

    .to_be_stripped_from_bin :
    {
        __idlog_start = .;
        KEEP(*(.to_be_stripped_from_bin))
        __idlog_end = .;
    } >idlog

}
