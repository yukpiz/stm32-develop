/* Program Entry, set to mark it as "used" and avoid gcc warnings */
ENTRY(ResetHandler)

/* Memory Spaces Definitions */
MEMORY
{
	RAM      (RWX) : ORIGIN = 0x20000000, LENGTH = 16K
	FLASH    (RX)  : ORIGIN = 0x08000000, LENGTH = 128K
	EEPROM   (RW)  : ORIGIN = 0x08080000, LENGTH = 4K
}
/* code/data sections */

SECTIONS
{
    /* code */
    .text : 
    {
        KEEP(*(.vectors_flash))
        KEEP(*(.guard))
        *(.text)      /* Program code */
        *(.text.*)    /* main goes here */
        *(.stub .gnu.linkonce.t.*)
        *(.rodata .rodata.*)
        . = ALIGN(4); 
    } > FLASH
    
    /* needed for 64 bit division */
	.ARM.exidx : 
	{
		*(.ARM.exidx*)
	} > FLASH
    
    /* all initialized data will go here */ 
    __datai_start = .;
     
    .data : AT ( __datai_start )
    {
        . = ALIGN(4);
        __data_start = .;
        *(.vectors_ram) /* ram vectors */
        *(.data)       /* Data memory */
        *(.data.*)
        . = ALIGN(4);
        __data_end = .; 
    } > RAM
    
    .eeprom (NOLOAD) :
    {
        *(.eeprom)
    } > EEPROM AT > FLASH


    .bss :
    {
        . = ALIGN(4);
        __bss_start = .;
        *(.bss)       /* Zero-filled run time allocate data memory */
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } > RAM
     
    
    .heap :
    {
        __heap_start = .;
    } > RAM
    
     __heap_end = ORIGIN(RAM) + LENGTH(RAM);
     __stack = ORIGIN(RAM) + LENGTH(RAM) - 4;
} 
