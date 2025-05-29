#include "tm4c123gh6pm_registers.h"

#define USAGE_FAULT_PRIORITY_MASK        0xFF1FFFFF
#define USAGE_FAULT_PRIORITY                 2
#define USAGE_FAULT_PRIORITY_BITS_POS        21
#define USAGE_FAULT_ENABLE_BIT_POS           18

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

/* Usage Fault Handler */
void UsageFault_Handler(void)
{
    /* Enter an infinite loop */
    while(1);
}

/* Active Usage Fault Exception and Setup its priority */
void UsageFault_Init(void)
{
    /* Assign priority level 2 to the Usage Fault Exception */
    NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & USAGE_FAULT_PRIORITY_MASK) | (USAGE_FAULT_PRIORITY << USAGE_FAULT_PRIORITY_BITS_POS);

    /* Enable the Usage Fault Exception */
    NVIC_SYSTEM_SYSHNDCTRL |= (1<<USAGE_FAULT_ENABLE_BIT_POS);
}

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

    /* Activate Usage Fault Exception */
    UsageFault_Init();

    /* Set the DIV0 bit in the CFGCTRL register to trigger exception when divide by ZERO */
    NVIC_SYSTEM_CFGCTRL |= (1<<4);

    /* Try to divide by ZERO, This should trigger Hard Fault as the Usage Fault is disabled */
    Divide(var1,var2);

    while(1){}
}
