
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

/* Enable PF0 (SW2) */
void SW2_Init(void)
{
    GPIO_PORTF_LOCK_REG   = 0x4C4F434B;   /* Unlock the GPIO_PORTF_CR_REG */
    GPIO_PORTF_CR_REG    |= (1<<0);       /* Enable changes on PF0 */
    GPIO_PORTF_AMSEL_REG &= ~(1<<0);      /* Disable Analog on PF0 */
    GPIO_PORTF_PCTL_REG  &= 0xFFFFFFF0;   /* Clear PMCx bits for PF0 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   &= ~(1<<0);      /* Configure PF0 as input pin */
    GPIO_PORTF_AFSEL_REG &= ~(1<<0);      /* Disable alternative function on PF0 */
    GPIO_PORTF_PUR_REG   |= (1<<0);       /* Enable pull-up on PF0 */
    GPIO_PORTF_DEN_REG   |= (1<<0);       /* Enable Digital I/O on PF0 */
}

/* Enable PF1 (RED LED) */
void Led_Red_Init(void)
{
    GPIO_PORTF_AMSEL_REG &= ~(1<<1);      /* Disable Analog on PF1 */
    GPIO_PORTF_PCTL_REG  &= 0xFFFFFF0F;   /* Clear PMCx bits for PF1 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   |= (1<<1);       /* Configure PF1 as output pin */
    GPIO_PORTF_AFSEL_REG &= ~(1<<1);      /* Disable alternative function on PF1 */
    GPIO_PORTF_DEN_REG   |= (1<<1);       /* Enable Digital I/O on PF1 */
    GPIO_PORTF_DATA_REG  &= ~(1<<1);      /* Clear bit 1 in Data register to turn off the led */
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
    /* Enable clock for PORTF and allow time for clock to start
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= 0x00000020;
    delay = SYSCTL_REGCGC2_REG; */

    /* Enable Interrupts, Exceptions and Faults */
    Enable_Exceptions();
    Enable_Faults();

    /* Enable Bus Fault Exception */
    BusFault_Init();

    /* Initialize the Red LED and SW2 as GPIO Pins, This will cause a Bus Fault Exception */
    Led_Red_Init();
    SW2_Init();

    while(1)
    {
        /* Check the switch state */
        if(!(GPIO_PORTF_DATA_REG & (1<<0)))
        {
            GPIO_PORTF_DATA_REG |= (1<<1);  /* LED ON */
        }
        else
        {
            GPIO_PORTF_DATA_REG &= ~(1<<1); /* LED OFF */
        }
    }
}
