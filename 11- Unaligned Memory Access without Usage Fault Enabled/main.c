#include "tm4c123gh6pm_registers.h"

#define BUS_FAULT_PRIORITY_MASK        0xFFFF1FFF
#define BUS_FAULT_PRIORITY                 1
#define BUS_FAULT_PRIORITY_BITS_POS        13
#define BUS_FAULT_ENABLE_BIT_POS           17

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

/* Bus Fault Handler */
void BusFault_Handler(void)
{
    /* Enter an infinite loop */
    while(1);
}

/* Active Bus Fault Exception and Setup its priority */
void BusFault_Init(void)
{
    /* Assign priority level 1 to the Bus Fault Exception */
    NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & BUS_FAULT_PRIORITY_MASK) | (BUS_FAULT_PRIORITY << BUS_FAULT_PRIORITY_BITS_POS);

    /* Enable the Bus Fault Exception */
    NVIC_SYSTEM_SYSHNDCTRL |= (1<<BUS_FAULT_ENABLE_BIT_POS);
}

int main(void)
{
    /* Enable Interrupts, Exceptions and Faults */
    Enable_Exceptions();
    Enable_Faults();

    /* Enable Bus Fault Exception */
    BusFault_Init();

    /* Point to address from the reserved memory area */
    volatile uint32 *ptr = (unsigned long *)0x20008000;

    /* Access this address should trigger hard fault exception as the bus fault is disabled */
    *ptr = 10;

    while(1){}
}
