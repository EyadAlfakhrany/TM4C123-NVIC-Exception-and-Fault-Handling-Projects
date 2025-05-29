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

uint32 Divide(uint32 num1,uint32 num2)
{
    return num1/num2;
}

int main(void)
{
    uint32 var1 = 10, var2 = 0;

    /* Enable Interrupts, Exceptions and Faults */
    Enable_Exceptions();
    Enable_Faults();

    /* Set the DIV0 bit in the CFGCTRL register to trigger exception when divide by ZERO */
    NVIC_SYSTEM_CFGCTRL |= (1<<4);

    /* Try to divide by ZERO, This should trigger Hard Fault as the Usage Fault is disabled */
    Divide(var1,var2);

    while(1){}
}
