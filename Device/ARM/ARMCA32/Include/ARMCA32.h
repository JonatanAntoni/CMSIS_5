/******************************************************************************
 * @file     ARMCA32.h
 * @brief    CMSIS Cortex-A32 Core Peripheral Access Layer Header File
 * @version  V1.00
 * @data     30 Aug 2017
 *
 * @note
 *
 ******************************************************************************/
/*
 * Copyright (c) 2009-2017 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ARMCA32_H__
#define __ARMCA32_H__

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum IRQn
{
/******  SGI Interrupts Numbers                 *************************************/
  SGI0_IRQn            =  0,
  SGI1_IRQn            =  1,
  SGI2_IRQn            =  2,
  SGI3_IRQn            =  3,
  SGI4_IRQn            =  4,
  SGI5_IRQn            =  5,
  SGI6_IRQn            =  6,
  SGI7_IRQn            =  7,
  SGI8_IRQn            =  8,
  SGI9_IRQn            =  9,
  SGI10_IRQn           = 10,
  SGI11_IRQn           = 11,
  SGI12_IRQn           = 12,
  SGI13_IRQn           = 13,
  SGI14_IRQn           = 14,
  SGI15_IRQn           = 15,

/******  Cortex-A32 Processor Exceptions Numbers ************************************/
  SecurePhyTimer_IRQn  = 29,        /*!< Physical Timer Interrupt                   */

} IRQn_Type;

/************************************************************************************/
/*                         Peripheral memory map                                    */
/************************************************************************************/

/* Peripheral and RAM base address */
#define VE_A32_MP_DRAM_BASE                    (0x80000000UL)                        /*!< (DRAM      ) Base Address */
#define VE_A32_MP_GIC_DISTRIBUTOR_BASE         (0x2F000000UL)                        /*!< (GIC DIST  ) Base Address */
#define VE_A32_MP_GIC_REDISTRIBUTOR_BASE       (0x2F100000UL)                        /*!< (GIC REDIST) Base Address */
#define VE_A32_MP_GIC_INTERFACE_BASE           (0x2C000000UL)                        /*!< (GIC CPU IF) Base Address */
#define VE_A32_MP_PL310_BASE                   (0x2C0F0000UL)                        /*!< (L2C-310   ) Base Address */
#define VE_A32_MP_REFCLK_BASE                  (0x2A430000)                          /*!< (REFCLK    ) Base Address */
#define GIC_DISTRIBUTOR_BASE                   VE_A32_MP_GIC_DISTRIBUTOR_BASE
#define GIC_REDISTRIBUTOR_BASE                 VE_A32_MP_GIC_REDISTRIBUTOR_BASE
#define GIC_INTERFACE_BASE                     VE_A32_MP_GIC_INTERFACE_BASE
#define L2C_310_BASE                           VE_A32_MP_PL310_BASE
#define SCTR_BASE                              VE_A32_MP_REFCLK_BASE

/* --------  Configuration of the Cortex-A32 Processor and Core Peripherals  ------ */
#define __CA_REV        0x0001U    /* Core revision r0p1                            */
#define __CORTEX_A          32U    /* Cortex-A32 Core                               */
#define __FPU_PRESENT        1U    /* FPU present                                   */
#define __GIC_PRESENT        1U    /* GIC present                                   */
#define __TIM_PRESENT        1U    /* TIM present                                   */
#define __L2C_PRESENT        1U    /* L2C present                                   */

#include "core_ca.h"
#include <system_ARMCA32.h>

#ifdef __cplusplus
}
#endif

#endif  // __ARMCA32_H__
