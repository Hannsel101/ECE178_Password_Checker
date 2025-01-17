/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'myCPU' in SOPC Builder design 'niosSys'
 * SOPC Builder design path: ../../niosSys.sopcinfo
 *
 * Generated: Thu Apr 23 16:29:44 PDT 2020
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * Altera_UP_SD_Card_Avalon_Interface_0 configuration
 *
 */

#define ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_BASE 0x800
#define ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_IRQ -1
#define ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_NAME "/dev/Altera_UP_SD_Card_Avalon_Interface_0"
#define ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_SPAN 1024
#define ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_TYPE "Altera_UP_SD_Card_Avalon_Interface"
#define ALT_MODULE_CLASS_Altera_UP_SD_Card_Avalon_Interface_0 Altera_UP_SD_Card_Avalon_Interface


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00001020
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1c
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x08000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "myCPU"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x08000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00001020
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1c
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x08000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x08000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_UP_AVALON_CHARACTER_LCD
#define __ALTERA_UP_SD_CARD_AVALON_INTERFACE


/*
 * HEX_0 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_0 altera_avalon_pio
#define HEX_0_BASE 0x18d0
#define HEX_0_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_0_CAPTURE 0
#define HEX_0_DATA_WIDTH 7
#define HEX_0_DO_TEST_BENCH_WIRING 0
#define HEX_0_DRIVEN_SIM_VALUE 0
#define HEX_0_EDGE_TYPE "NONE"
#define HEX_0_FREQ 50000000
#define HEX_0_HAS_IN 0
#define HEX_0_HAS_OUT 1
#define HEX_0_HAS_TRI 0
#define HEX_0_IRQ -1
#define HEX_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_0_IRQ_TYPE "NONE"
#define HEX_0_NAME "/dev/HEX_0"
#define HEX_0_RESET_VALUE 0
#define HEX_0_SPAN 16
#define HEX_0_TYPE "altera_avalon_pio"


/*
 * HEX_1 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_1 altera_avalon_pio
#define HEX_1_BASE 0x18c0
#define HEX_1_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_1_CAPTURE 0
#define HEX_1_DATA_WIDTH 7
#define HEX_1_DO_TEST_BENCH_WIRING 0
#define HEX_1_DRIVEN_SIM_VALUE 0
#define HEX_1_EDGE_TYPE "NONE"
#define HEX_1_FREQ 50000000
#define HEX_1_HAS_IN 0
#define HEX_1_HAS_OUT 1
#define HEX_1_HAS_TRI 0
#define HEX_1_IRQ -1
#define HEX_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_1_IRQ_TYPE "NONE"
#define HEX_1_NAME "/dev/HEX_1"
#define HEX_1_RESET_VALUE 0
#define HEX_1_SPAN 16
#define HEX_1_TYPE "altera_avalon_pio"


/*
 * HEX_2 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_2 altera_avalon_pio
#define HEX_2_BASE 0x18b0
#define HEX_2_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_2_CAPTURE 0
#define HEX_2_DATA_WIDTH 7
#define HEX_2_DO_TEST_BENCH_WIRING 0
#define HEX_2_DRIVEN_SIM_VALUE 0
#define HEX_2_EDGE_TYPE "NONE"
#define HEX_2_FREQ 50000000
#define HEX_2_HAS_IN 0
#define HEX_2_HAS_OUT 1
#define HEX_2_HAS_TRI 0
#define HEX_2_IRQ -1
#define HEX_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_2_IRQ_TYPE "NONE"
#define HEX_2_NAME "/dev/HEX_2"
#define HEX_2_RESET_VALUE 0
#define HEX_2_SPAN 16
#define HEX_2_TYPE "altera_avalon_pio"


/*
 * HEX_3 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_3 altera_avalon_pio
#define HEX_3_BASE 0x18a0
#define HEX_3_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_3_CAPTURE 0
#define HEX_3_DATA_WIDTH 7
#define HEX_3_DO_TEST_BENCH_WIRING 0
#define HEX_3_DRIVEN_SIM_VALUE 0
#define HEX_3_EDGE_TYPE "NONE"
#define HEX_3_FREQ 50000000
#define HEX_3_HAS_IN 0
#define HEX_3_HAS_OUT 1
#define HEX_3_HAS_TRI 0
#define HEX_3_IRQ -1
#define HEX_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_3_IRQ_TYPE "NONE"
#define HEX_3_NAME "/dev/HEX_3"
#define HEX_3_RESET_VALUE 0
#define HEX_3_SPAN 16
#define HEX_3_TYPE "altera_avalon_pio"


/*
 * HEX_4 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_4 altera_avalon_pio
#define HEX_4_BASE 0x1890
#define HEX_4_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_4_CAPTURE 0
#define HEX_4_DATA_WIDTH 7
#define HEX_4_DO_TEST_BENCH_WIRING 0
#define HEX_4_DRIVEN_SIM_VALUE 0
#define HEX_4_EDGE_TYPE "NONE"
#define HEX_4_FREQ 50000000
#define HEX_4_HAS_IN 0
#define HEX_4_HAS_OUT 1
#define HEX_4_HAS_TRI 0
#define HEX_4_IRQ -1
#define HEX_4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_4_IRQ_TYPE "NONE"
#define HEX_4_NAME "/dev/HEX_4"
#define HEX_4_RESET_VALUE 0
#define HEX_4_SPAN 16
#define HEX_4_TYPE "altera_avalon_pio"


/*
 * HEX_5 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_5 altera_avalon_pio
#define HEX_5_BASE 0x1880
#define HEX_5_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_5_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_5_CAPTURE 0
#define HEX_5_DATA_WIDTH 7
#define HEX_5_DO_TEST_BENCH_WIRING 0
#define HEX_5_DRIVEN_SIM_VALUE 0
#define HEX_5_EDGE_TYPE "NONE"
#define HEX_5_FREQ 50000000
#define HEX_5_HAS_IN 0
#define HEX_5_HAS_OUT 1
#define HEX_5_HAS_TRI 0
#define HEX_5_IRQ -1
#define HEX_5_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_5_IRQ_TYPE "NONE"
#define HEX_5_NAME "/dev/HEX_5"
#define HEX_5_RESET_VALUE 0
#define HEX_5_SPAN 16
#define HEX_5_TYPE "altera_avalon_pio"


/*
 * HEX_6 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_6 altera_avalon_pio
#define HEX_6_BASE 0x1870
#define HEX_6_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_6_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_6_CAPTURE 0
#define HEX_6_DATA_WIDTH 7
#define HEX_6_DO_TEST_BENCH_WIRING 0
#define HEX_6_DRIVEN_SIM_VALUE 0
#define HEX_6_EDGE_TYPE "NONE"
#define HEX_6_FREQ 50000000
#define HEX_6_HAS_IN 0
#define HEX_6_HAS_OUT 1
#define HEX_6_HAS_TRI 0
#define HEX_6_IRQ -1
#define HEX_6_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_6_IRQ_TYPE "NONE"
#define HEX_6_NAME "/dev/HEX_6"
#define HEX_6_RESET_VALUE 0
#define HEX_6_SPAN 16
#define HEX_6_TYPE "altera_avalon_pio"


/*
 * HEX_7 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_7 altera_avalon_pio
#define HEX_7_BASE 0x1860
#define HEX_7_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_7_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_7_CAPTURE 0
#define HEX_7_DATA_WIDTH 7
#define HEX_7_DO_TEST_BENCH_WIRING 0
#define HEX_7_DRIVEN_SIM_VALUE 0
#define HEX_7_EDGE_TYPE "NONE"
#define HEX_7_FREQ 50000000
#define HEX_7_HAS_IN 0
#define HEX_7_HAS_OUT 1
#define HEX_7_HAS_TRI 0
#define HEX_7_IRQ -1
#define HEX_7_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_7_IRQ_TYPE "NONE"
#define HEX_7_NAME "/dev/HEX_7"
#define HEX_7_RESET_VALUE 0
#define HEX_7_SPAN 16
#define HEX_7_TYPE "altera_avalon_pio"


/*
 * High_Res_Timer configuration
 *
 */

#define ALT_MODULE_CLASS_High_Res_Timer altera_avalon_timer
#define HIGH_RES_TIMER_ALWAYS_RUN 0
#define HIGH_RES_TIMER_BASE 0x1800
#define HIGH_RES_TIMER_COUNTER_SIZE 32
#define HIGH_RES_TIMER_FIXED_PERIOD 0
#define HIGH_RES_TIMER_FREQ 50000000
#define HIGH_RES_TIMER_IRQ 2
#define HIGH_RES_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define HIGH_RES_TIMER_LOAD_VALUE 49999
#define HIGH_RES_TIMER_MULT 0.001
#define HIGH_RES_TIMER_NAME "/dev/High_Res_Timer"
#define HIGH_RES_TIMER_PERIOD 1
#define HIGH_RES_TIMER_PERIOD_UNITS "ms"
#define HIGH_RES_TIMER_RESET_OUTPUT 0
#define HIGH_RES_TIMER_SNAPSHOT 1
#define HIGH_RES_TIMER_SPAN 32
#define HIGH_RES_TIMER_TICKS_PER_SEC 1000
#define HIGH_RES_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define HIGH_RES_TIMER_TYPE "altera_avalon_timer"


/*
 * KEY_0 configuration
 *
 */

#define ALT_MODULE_CLASS_KEY_0 altera_avalon_pio
#define KEY_0_BASE 0x1840
#define KEY_0_BIT_CLEARING_EDGE_REGISTER 0
#define KEY_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEY_0_CAPTURE 1
#define KEY_0_DATA_WIDTH 4
#define KEY_0_DO_TEST_BENCH_WIRING 0
#define KEY_0_DRIVEN_SIM_VALUE 0
#define KEY_0_EDGE_TYPE "FALLING"
#define KEY_0_FREQ 50000000
#define KEY_0_HAS_IN 1
#define KEY_0_HAS_OUT 0
#define KEY_0_HAS_TRI 0
#define KEY_0_IRQ 4
#define KEY_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define KEY_0_IRQ_TYPE "EDGE"
#define KEY_0_NAME "/dev/KEY_0"
#define KEY_0_RESET_VALUE 0
#define KEY_0_SPAN 16
#define KEY_0_TYPE "altera_avalon_pio"


/*
 * LEDG configuration
 *
 */

#define ALT_MODULE_CLASS_LEDG altera_avalon_pio
#define LEDG_BASE 0x1850
#define LEDG_BIT_CLEARING_EDGE_REGISTER 0
#define LEDG_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDG_CAPTURE 0
#define LEDG_DATA_WIDTH 8
#define LEDG_DO_TEST_BENCH_WIRING 0
#define LEDG_DRIVEN_SIM_VALUE 0
#define LEDG_EDGE_TYPE "NONE"
#define LEDG_FREQ 50000000
#define LEDG_HAS_IN 0
#define LEDG_HAS_OUT 1
#define LEDG_HAS_TRI 0
#define LEDG_IRQ -1
#define LEDG_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDG_IRQ_TYPE "NONE"
#define LEDG_NAME "/dev/LEDG"
#define LEDG_RESET_VALUE 0
#define LEDG_SPAN 16
#define LEDG_TYPE "altera_avalon_pio"


/*
 * LEDs configuration
 *
 */

#define ALT_MODULE_CLASS_LEDs altera_avalon_pio
#define LEDS_BASE 0x18e0
#define LEDS_BIT_CLEARING_EDGE_REGISTER 0
#define LEDS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDS_CAPTURE 0
#define LEDS_DATA_WIDTH 18
#define LEDS_DO_TEST_BENCH_WIRING 0
#define LEDS_DRIVEN_SIM_VALUE 0
#define LEDS_EDGE_TYPE "NONE"
#define LEDS_FREQ 50000000
#define LEDS_HAS_IN 0
#define LEDS_HAS_OUT 1
#define LEDS_HAS_TRI 0
#define LEDS_IRQ -1
#define LEDS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDS_IRQ_TYPE "NONE"
#define LEDS_NAME "/dev/LEDs"
#define LEDS_RESET_VALUE 0
#define LEDS_SPAN 16
#define LEDS_TYPE "altera_avalon_pio"


/*
 * SDRAM configuration
 *
 */

#define ALT_MODULE_CLASS_SDRAM altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x8000000
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/SDRAM"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 7.185
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 32
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 134217728
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.4
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 15.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 15.0
#define SDRAM_T_WR 14.0


/*
 * Switches configuration
 *
 */

#define ALT_MODULE_CLASS_Switches altera_avalon_pio
#define SWITCHES_BASE 0x18f0
#define SWITCHES_BIT_CLEARING_EDGE_REGISTER 0
#define SWITCHES_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SWITCHES_CAPTURE 0
#define SWITCHES_DATA_WIDTH 18
#define SWITCHES_DO_TEST_BENCH_WIRING 0
#define SWITCHES_DRIVEN_SIM_VALUE 0
#define SWITCHES_EDGE_TYPE "NONE"
#define SWITCHES_FREQ 50000000
#define SWITCHES_HAS_IN 1
#define SWITCHES_HAS_OUT 0
#define SWITCHES_HAS_TRI 0
#define SWITCHES_IRQ 3
#define SWITCHES_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SWITCHES_IRQ_TYPE "LEVEL"
#define SWITCHES_NAME "/dev/Switches"
#define SWITCHES_RESET_VALUE 0
#define SWITCHES_SPAN 16
#define SWITCHES_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x1908
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x1908
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x1908
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "niosSys"


/*
 * System_Clock_Timer configuration
 *
 */

#define ALT_MODULE_CLASS_System_Clock_Timer altera_avalon_timer
#define SYSTEM_CLOCK_TIMER_ALWAYS_RUN 0
#define SYSTEM_CLOCK_TIMER_BASE 0x1820
#define SYSTEM_CLOCK_TIMER_COUNTER_SIZE 32
#define SYSTEM_CLOCK_TIMER_FIXED_PERIOD 0
#define SYSTEM_CLOCK_TIMER_FREQ 50000000
#define SYSTEM_CLOCK_TIMER_IRQ 1
#define SYSTEM_CLOCK_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SYSTEM_CLOCK_TIMER_LOAD_VALUE 49999
#define SYSTEM_CLOCK_TIMER_MULT 0.001
#define SYSTEM_CLOCK_TIMER_NAME "/dev/System_Clock_Timer"
#define SYSTEM_CLOCK_TIMER_PERIOD 1
#define SYSTEM_CLOCK_TIMER_PERIOD_UNITS "ms"
#define SYSTEM_CLOCK_TIMER_RESET_OUTPUT 0
#define SYSTEM_CLOCK_TIMER_SNAPSHOT 1
#define SYSTEM_CLOCK_TIMER_SPAN 32
#define SYSTEM_CLOCK_TIMER_TICKS_PER_SEC 1000
#define SYSTEM_CLOCK_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define SYSTEM_CLOCK_TIMER_TYPE "altera_avalon_timer"


/*
 * TCM configuration
 *
 */

#define ALT_MODULE_CLASS_TCM altera_avalon_onchip_memory2
#define TCM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define TCM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define TCM_BASE 0x0
#define TCM_CONTENTS_INFO ""
#define TCM_DUAL_PORT 1
#define TCM_GUI_RAM_BLOCK_TYPE "AUTO"
#define TCM_INIT_CONTENTS_FILE "niosSys_TCM"
#define TCM_INIT_MEM_CONTENT 1
#define TCM_INSTANCE_ID "NONE"
#define TCM_IRQ -1
#define TCM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TCM_NAME "/dev/TCM"
#define TCM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define TCM_RAM_BLOCK_TYPE "AUTO"
#define TCM_READ_DURING_WRITE_MODE "DONT_CARE"
#define TCM_SINGLE_CLOCK_OP 0
#define TCM_SIZE_MULTIPLE 1
#define TCM_SIZE_VALUE 2048
#define TCM_SPAN 2048
#define TCM_TYPE "altera_avalon_onchip_memory2"
#define TCM_WRITABLE 1


/*
 * character_lcd_0 configuration
 *
 */

#define ALT_MODULE_CLASS_character_lcd_0 altera_up_avalon_character_lcd
#define CHARACTER_LCD_0_BASE 0xc00
#define CHARACTER_LCD_0_IRQ -1
#define CHARACTER_LCD_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CHARACTER_LCD_0_NAME "/dev/character_lcd_0"
#define CHARACTER_LCD_0_SPAN 2
#define CHARACTER_LCD_0_TYPE "altera_up_avalon_character_lcd"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x1908
#define JTAG_UART_0_IRQ 0
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * sysID configuration
 *
 */

#define ALT_MODULE_CLASS_sysID altera_avalon_sysid_qsys
#define SYSID_BASE 0x1900
#define SYSID_ID 305419896
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysID"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1587683138
#define SYSID_TYPE "altera_avalon_sysid_qsys"

#endif /* __SYSTEM_H_ */
