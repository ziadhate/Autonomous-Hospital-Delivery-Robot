
/* Select the reset handler as the firmware entry point. */
ENTRY(Reset_Handler)

/* Define the memory regions available on the STM32F401RE. */
MEMORY
{
    /* Main Flash: 512 KiB starting at 0x08000000. */
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K

    /* Main SRAM: 64 KiB starting at 0x20000000. */
    RAM (xrw)   : ORIGIN = 0x20000000, LENGTH = 64K

    /* Core-coupled memory: 32 KiB, not accessible by every bus master. */
    CCMRAM (xrw): ORIGIN = 0x10000000, LENGTH = 32K
}

/* Initial stack pointer: top of the main SRAM region. */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Reserve minimum heap and stack space for initial link-time checks. */
_Min_Heap_Size = 0x200;
_Min_Stack_Size = 0x800;

SECTIONS
{
    /* Keep the interrupt vector table at the beginning of Flash. */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    /* Place executable code and read-only constants in Flash. */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    /* ARM exception-unwinding metadata. */
    .ARM.extab :
    {
        *(.ARM.extab*)
    } > FLASH

    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > FLASH

    /*
     * Initialized variables run from RAM but their initial values
     * are stored in Flash in the firmware image.
     */
    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > RAM AT > FLASH

    /* Zero-initialized and uninitialized static storage in RAM. */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > RAM

    /*
     * Optional section for data explicitly assigned to CCMRAM.
     * Nothing is placed here unless source code requests this section.
     */
    .ccmram :
    {
        . = ALIGN(4);
        *(.ccmram)
        *(.ccmram*)
        . = ALIGN(4);
    } > CCMRAM

    /* Reserve heap and stack-check space in main SRAM. */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE(end = .);
        PROVIDE(_end = .);
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } > RAM

    /* Do not store these metadata sections in the loadable image. */
    /DISCARD/ :
    {
        *(.note*)
        *(.comment*)
    }
}

/* Fail the link if the statically allocated sections exceed SRAM. */
ASSERT(_ebss <= ORIGIN(RAM) + LENGTH(RAM),
       "Error: .bss exceeds main SRAM")
