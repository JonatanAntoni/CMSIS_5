/**************************************************************************//**
 * @file     mmu_ARMCA32.c
 * @brief    MMU Configuration for ARM Cortex-A9 Device Series
 * @version  V1.00
 * @date     30 Aug 2017
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

#include "RTE_Components.h"
#include CMSIS_device_header

//Import symbols from linker
extern uint32_t Image$$TTB$$ZI$$Base;

void MMU_CreateTranslationTable(void)
{
  uint32_t *ttb;

  // Set up memory attributes
  // 0 -> 0b01000100 = 0x00000044 = Normal, Inner/Outer Non-Cacheable
  // 1 -> 0b11111111 = 0x0000ff00 = Normal, Inner/Outer WriteBack Read/Write Allocate
  // 2 -> 0b00000100 = 0x00040000 = Device-nGnRE
  __set_MAIR0(0x04ff44);

  // Set up TTBCR for the Long-descriptor translation table format (EAE = 1)
  //
  // We're using only TTBR0 (EPD1 = 1), and the page table entries:
  //  - are using an 8-bit ASID from TTBR0
  //  - are outer-shareable (SH0 = 0b10)
  //  - are using Inner & Outer WBWA Normal memory ([IO]RGN0 = 0b01)
  //  - map
  //      + 32 bits of VA space (T0SZ = 0x00)
  //      + into a 40-bit PA space
  //
  //  32   28   24   20   16   12    8    4    0
  //    +----+----+----+----+----+----+----+----+
  //    |    |OOII|    |    |    |OOII|    |    |
  //    |    |RRRR|E   |  TT|    |RRRR|E T |   T|
  //    |E SS|GGGG|P   |  11|  SS|GGGG|P 0 |   0|
  //    |A HH|NNNN|DA  |  SS|  HH|NNNN|D S |   S|
  //    |E 11|1111|11  |  ZZ|  00|0000|0 Z-|---Z|
  //
  //     1000 0000 1000 0000 0010 0101 0000 0000
  //
  //   0x    8    0    8    0    2    5    0    0
  //
  // Note: the ISB is needed to ensure the changes to system
  //       context are before the write of SCTLR_EL1.M to enable
  //       the MMU. It is likely on a "real" implementation that
  //       this setup would work without an ISB, due to the
  //       amount of code that gets executed before enabling the
  //       MMU, but that would not be architecturally correct.
  //
  __set_TTBCR(0x80802500);
  __ISB();

  //===================================================================
  // PAGE TABLE generation
  //
  // There are 4 level one table entries addressing 1GB each
  // The first will be a Block entry marked as Device memory for peripherals (if any)
  // The next invalid
  // The next a Block entry marked as Normal for RAM where the code/stack/heap is
  // The next invalid
  //
  //         |63                                                                             1|0|
  //         +--------------------------------------------------------------------------------+-+
  // Invalid |................................................................................|0|
  //
  //
  //         |63                  52|51     39|40           n|n-1  12|11                   2|1|0|
  //         +----------------------+---------+--------------+-------+----------------------+-+-+
  // Block   |Upper block attributes|  res0   |Output address| res0  |Lower block attributes|0|1|
  //
  //
  //         |     63|62   61|     60|      59|58 52|51 40|39                        12|11 2|1|0|
  //         +-------+-------+-------+--------+-----+-----+----------------------------+----+-+-+
  // Table   |NSTable|APTable|XNTable|PXNTable|.....|res0 |Next level table addr[39:12]|....|1|1|
  //
  //
  //                Upper attributes                                    Lower attributes
  //         |63 59|58 55|54| 53|        52|            |11|10|9     8|7     6| 5|4            2|
  //         +-----+-----+--+---+----------+            +--+--+-------+-------+--+--------------+
  //         |.....|.....|XN|PXN|Contiguous|            |nG|AF|SH[1:0]|AP[2:1]|NS|AttrIndex[2:0]|
  //
  //  where ... is ignored, n is 30 for level 1 or 21 for level 2
  //=============================================================================================

  ttb = &Image$$TTB$$ZI$$Base;

  // Device memory
  ttb[0] = ((0 << 30) | (0b0111010010 << 2) | 0b01); // Output address + Lower attributes + Block tag
  ttb[1] = (0b100 << 20);                            // Upper attributes
  ttb[2] = 0;                                        // Mark entry invalid by setting bit 0 to 0
                                                     // Upper word ignored

  // RAM
  ttb[4] = ((2 << 30) | (0b0111010001 << 2) | 0b01); // Output address + Lower attributes + block tag
  ttb[5] = (0b000 << 20);                            // Upper attributes
  ttb[6] = 0;                                        // Mark entry invalid by setting bit 0 to 0
                                                     // Upper word ignored

  // Set location of level 1 page table
  __set_TTBR0((uint32_t)&Image$$TTB$$ZI$$Base);
  __ISB();

  // Set up domain access control register
  // We set domain 0 to Client and all other domains to No Access.
  // All translation table entries specify domain 0
  __set_DACR(1);
  __ISB();
}
