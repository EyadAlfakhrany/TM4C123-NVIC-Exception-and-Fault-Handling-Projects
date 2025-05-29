# TM4C123 NVIC Exception and Fault Handling Projects

This repository contains 15 projects demonstrating exception and fault handling on the TM4C123 microcontroller using NVIC. Each project focuses on different fault scenarios such as Usage Fault, Bus Fault, Hard Fault, and NVIC configuration.

---

## Project 1: NVIC Hard Fault on Divide by Zero (Usage Fault Disabled)

**Description:**  
Enables interrupts, faults, and sets the DIV0 bit to trigger an exception on division by zero. Usage Fault is disabled, causing a Hard Fault on divide by zero.

**NVIC Role:**  
Usage Fault is disabled in NVIC; therefore, a Hard Fault is generated when dividing by zero.

---

## Project 2: NVIC Enable Usage Fault with Priority and Handler

**Description:**  
Activates Usage Fault exception in NVIC with priority setup and a dedicated handler. Division by zero triggers a Usage Fault instead of Hard Fault.

**NVIC Role:**  
Usage Fault enabled and prioritized through NVIC for precise exception handling.

---

## Project 3: NVIC Hard Fault on Unaligned Memory Access (Usage Fault Disabled)

**Description:**  
Enables unaligned access trap. Accessing unaligned memory address causes a Hard Fault because Usage Fault is disabled.

**NVIC Role:**  
Usage Fault disabled; unaligned access triggers Hard Fault.

---

## Project 4: NVIC Enable Usage Fault for Unaligned Memory Access

**Description:**  
Enables Usage Fault in NVIC and sets priority. Unaligned memory access triggers a Usage Fault instead of a Hard Fault.

**NVIC Role:**  
NVIC manages Usage Fault exception for unaligned access.

---

## Project 5: NVIC GPIO Port F Initialization with Bus Fault Disabled

**Description:**  
Initializes GPIO Port F and attempts to read a switch causing a Bus Fault. Bus Fault is disabled, so a Hard Fault occurs instead.

**NVIC Role:**  
Bus Fault disabled; Hard Fault generated on bus error.

---

## Project 6: NVIC Enable Bus Fault with Priority and Handler

**Description:**  
Enables Bus Fault exception with priority and handler. Bus faults are caught and handled explicitly.

**NVIC Role:**  
NVIC configures Bus Fault for dedicated handling.

---

## Project 7: NVIC Access Reserved Memory with Bus Fault Disabled (Hard Fault)

**Description:**  
Access to reserved memory with Bus Fault disabled results in a Hard Fault.

**NVIC Role:**  
Bus Fault disabled; NVIC does not handle bus errors.

---

## Project 8: NVIC Enable Bus Fault for Reserved Memory Access

**Description:**  
Enables Bus Fault in NVIC. Reserved memory access triggers Bus Fault instead of Hard Fault.

**NVIC Role:**  
Bus Fault enabled and managed via NVIC.

---

## Project 9: NVIC Divide by Zero without Usage Fault Enabled

**Description:**  
Sets DIV0 bit, but Usage Fault disabled; division by zero triggers Hard Fault.

**NVIC Role:**  
Usage Fault disabled in NVIC.

---

## Project 10: NVIC Usage Fault Enabled for Divide by Zero

**Description:**  
Enables Usage Fault in NVIC; division by zero triggers Usage Fault.

**NVIC Role:**  
NVIC handles Usage Fault with priority.

---

## Project 11: NVIC Unaligned Memory Access without Usage Fault Enabled

**Description:**  
Unaligned access triggers Hard Fault because Usage Fault is disabled.

**NVIC Role:**  
Usage Fault disabled in NVIC.

---

## Project 12: NVIC Usage Fault Enabled for Unaligned Memory Access

**Description:**  
Usage Fault enabled in NVIC; unaligned access triggers Usage Fault.

**NVIC Role:**  
NVIC manages Usage Fault exception.

---

## Project 13: NVIC GPIO Initialization with Bus Fault Disabled (Duplicate of Project 5)

**Description:**  
Same as Project 5.

---

## Project 14: NVIC Bus Fault Enabled for GPIO Access (Duplicate of Project 6)

**Description:**  
Same as Project 6.

---

## Project 15: NVIC Comprehensive Faults Enabled with Proper Priority and Handlers

**Description:**  
Fully enables exceptions, faults, and sets NVIC priorities. Tests divide by zero, unaligned access, and GPIO faults with dedicated handlers.

**NVIC Role:**  
Complete NVIC configuration for all fault types with appropriate priorities.

---

# General Notes

- **NVIC** (Nested Vectored Interrupt Controller) enables/disables fault exceptions and sets their priority levels.
- Disabling specific faults leads to Hard Faults instead of the more specific fault exceptions.
- This repository demonstrates fault activation, priority setup, and handler implementation on TM4C123 MCU.

---

Feel free to reach out for code explanations or further enhancements.
