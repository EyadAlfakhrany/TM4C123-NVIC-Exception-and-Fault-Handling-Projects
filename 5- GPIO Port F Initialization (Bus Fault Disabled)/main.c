#include "tm4c123gh6pm_registers.h"

#define SYSTICK_PRIORITY_MASK        0x1FFFFFFF
#define SYSTICK_INTERRUPT_PRIORITY       3
#define SYSTICK_PRIORITY_BITS_POS        29

#define NUMBER_TICKS_PER_ONE_SECOND      1
#define NUMBER_TICKS_PER_TWO_SECOND      2
#define NUMBER_TICKS_PER_THREE_SECOND    3

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

volatile uint8 ticks_num = 0;

/* SysTick Timer ISR ... No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */
void SysTick_Handler(void)
{
    ticks_num++; /* increment the number of ticks */

    if(ticks_num == NUMBER_TICKS_PER_ONE_SECOND)
    {
        GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02; /* Turn on the Red LED and disable the others */
    }
    else if(ticks_num == NUMBER_TICKS_PER_TWO_SECOND)
    {
        GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04; /* Turn on the Blue LED and disable the others */
    }
    else if(ticks_num == NUMBER_TICKS_PER_THREE_SECOND)
    {
        GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x08; /* Turn on the Green LED and disable the others */
        ticks_num = 0; /* reset the variable value */
    }
}

/* Enable PF1, PF2 and PF3 (RED, Blue and Green LEDs) */
void Leds_Init(void)
{
    GPIO_PORTF_AMSEL_REG &= 0xF1;         /* Disable Analog on PF1, PF2 and PF3 */
    GPIO_PORTF_PCTL_REG  &= 0xFFFF000F;   /* Clear PMCx bits for PF1, PF2 and PF3 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   |= 0x0E;         /* Configure PF1, PF2 and PF3 as output pin */
    GPIO_PORTF_AFSEL_REG &= 0xF1;         /* Disable alternative function on PF1, PF2 and PF3 */
    GPIO_PORTF_DEN_REG   |= 0x0E;         /* Enable Digital I/O on PF1, PF2 and PF3 */
    GPIO_PORTF_DATA_REG  &= 0xF1;         /* Clear bit 0, 1 and 2 in Data register to turn off the leds */
}

/* Enable the SystTick Timer to run using the System Clock with Frequency 16Mhz and generate interrupt every 1 second */
void SysTick_Init(void)
{
    SYSTICK_CTRL_REG    = 0;               /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = 15999999;        /* Set the Reload value with 15999999 to count 1 Second */
    SYSTICK_CURRENT_REG = 0;               /* Clear the Current Register value */
    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x07;
    /* Assign priority level 3 to the SysTick Interrupt */
    NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (SYSTICK_INTERRUPT_PRIORITY << SYSTICK_PRIORITY_BITS_POS);
}

/* Set PRIV Bit(Bit 0) in the CONTROL register to switch to Unprivileged access level */
void Switch_To_Unprivileged(void)
{
    __asm(" MOV R0, #1 ");      /* Set the R0 register value to 1 */
    __asm(" MSR CONTROL, R0 "); /* Set the PRIV Bit(Bit 0) to 1 ... This will switch to Unprivileged access level */
}

int main(void)
{
    /* Enable clock for PORTF and wait for clock to start */
    SYSCTL_RCGCGPIO_REG |= 0x20;
    while(!(SYSCTL_PRGPIO_REG & 0x20));

    /* Enable Interrupts, Exceptions and Faults */
    Enable_Exceptions();
    Enable_Faults();

    /* Initialize the LEDs as GPIO Pins */
    Leds_Init();

    /* Switch to unprivileged */
    Switch_To_Unprivileged();

    /* Initialize the SysTick Timer to generate an interrupt every 1 second */
    /* SysTick or NVIC could not be accessed in the Unprivileged access level.
     * This will cause a hard fault exception, as the bus fault is disabled */
    SysTick_Init();

    while(1){}

}
