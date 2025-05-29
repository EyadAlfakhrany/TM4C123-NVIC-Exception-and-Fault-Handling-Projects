#include "tm4c123gh6pm_registers.h"

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm(" WFI ")

int main(void)
{
    /* Point to the SysTick Control Register Address */
    volatile uint32 * ptr1 = (volatile unsigned long *)0xE000E010;

    /* Point to the SysTick Control Register Address + 1 */
    volatile uint8 * ptr2 = (volatile unsigned char *)0xE000E011;

    /* Point to the SysTick Control Register Address + 2 */
    volatile uint16 * ptr3 = (volatile unsigned short *)0xE000E012;

    /* Point to the SysTick Control Register Address + 1 */
    volatile uint32 * ptr4 = (volatile unsigned long *)0xE000E011;

    /* Enable Interrupts, Exceptions and Faults */
    Enable_Exceptions();
    Enable_Faults();

    /* Set the UNALIGNED bit in the CFGCTRL register to trigger exception when unaligned memory access happen */
    NVIC_SYSTEM_CFGCTRL |= (1<<3);

    *ptr1 = 10; /* Memory aligned access */

    *ptr2 = 10; /* Memory aligned access */

    *ptr3 = 10; /* Memory aligned access */

    *ptr4 = 10; /* Memory Unaligned access, It should trigger Hard Fault as the Usage Fault is disabled */

    while(1){}
}
