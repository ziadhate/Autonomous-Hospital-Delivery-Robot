
.syntax unified
.cpu cortex-m4
.thumb

/* Export the reset handler as the program entry point. */
.global Reset_Handler
.type Reset_Handler, %function

/* External symbols provided by the linker script. */
.extern _estack
.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss
.extern SystemInit
.extern main

/*
 * Interrupt vector table.
 * The first entry is the initial stack pointer.
 * The second entry is the reset handler.
 */
.section .isr_vector, "a", %progbits
.align 2

Vector_Table:
    .word _estack           /* Initial main stack pointer */
    .word Reset_Handler     /* Reset */
    .word Default_Handler   /* NMI */
    .word Default_Handler   /* HardFault */
    .word Default_Handler   /* MemManage */
    .word Default_Handler   /* BusFault */
    .word Default_Handler   /* UsageFault */
    .word 0                 /* Reserved */
    .word 0                 /* Reserved */
    .word 0                 /* Reserved */
    .word 0                 /* Reserved */
    .word Default_Handler   /* SVCall */
    .word Default_Handler   /* Debug monitor */
    .word 0                 /* Reserved */
    .word Default_Handler   /* PendSV */
    .word Default_Handler   /* SysTick */

/*
 * STM32F401xE external interrupt slots.
 * This minimal test routes every external interrupt to Default_Handler.
 * Verify the exact vector table against the MCU reference manual
 * before enabling peripheral interrupts.
 */
.rept 85
    .word Default_Handler
.endr


/* Reset handler: prepare RAM, initialize the system, then call main. */
.section .text.Reset_Handler, "ax", %progbits
.align 2
.thumb_func
Reset_Handler:

    /* Copy initialized data from Flash to RAM. */
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata

Copy_Data:
    cmp r1, r2
    bcs Zero_BSS_Start
    ldr r3, [r0]
    str r3, [r1]
    adds r0, r0, #4
    adds r1, r1, #4
    b Copy_Data


Zero_BSS_Start:
    /* Clear the .bss section in RAM. */
    ldr r1, =_sbss
    ldr r2, =_ebss
    movs r3, #0

Zero_BSS:
    cmp r1, r2
    bcs Run_Application
    str r3, [r1]
    adds r1, r1, #4
    b Zero_BSS


Run_Application:
    /* Initialize system-level settings before entering main. */
    bl SystemInit

    /* Transfer control to the C application. */
    bl main


/* If main returns, remain in an infinite loop. */
Hang:
    b Hang

/* Calculate Reset_Handler size before switching sections. */
.size Reset_Handler, . - Reset_Handler


/* Default handler used by unimplemented interrupt vectors. */
.section .text.Default_Handler, "ax", %progbits
.align 2
.thumb_func
Default_Handler:
    b Default_Handler
