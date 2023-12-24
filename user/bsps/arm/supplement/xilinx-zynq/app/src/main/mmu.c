/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2023 Bernd Moessner
 * Copyright (C) 2013 embedded brains GmbH & Co. KG
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/*
#define ARM_CP15_TEXT_SECTION BSP_START_TEXT_SECTION

#include <bsp.h>
#include <bsp/start.h>
#include <bsp/arm-cp15-start.h>
#include <bsp/arm-a9mpcore-start.h>

BSP_START_DATA_SECTION static const arm_cp15_start_section_config 
zynq_mmu_config_table[] = {
  ARMV7_CP15_START_DEFAULT_SECTIONS,
#if defined(RTEMS_SMP)
  {
    .begin = 0xffff0000U,
    .end = 0xffffffffU,
    .flags = ARMV7_MMU_DEVICE
  },
#endif
  {
    .begin = 0xe0000000U,
    .end = 0xe0200000U,
    .flags = ARMV7_MMU_DEVICE
  }, {
    .begin = 0xf8000000U,
    .end = 0xf9000000U,
    .flags = ARMV7_MMU_DEVICE
  },
  // Map GP0 to access the FPGA peripherals 
  {
    .begin = 0x40000000,
    .end   = 0x7fffffff,
    .flags = ARMV7_MMU_DEVICE
  },
};


BSP_START_TEXT_SECTION void zynq_setup_mmu_and_cache(void);

BSP_START_TEXT_SECTION void zynq_setup_mmu_and_cache(void)
{
  uint32_t ctrl = arm_cp15_start_setup_mmu_and_cache(
    ARM_CP15_CTRL_A,
    ARM_CP15_CTRL_AFE | ARM_CP15_CTRL_Z
  );

  arm_cp15_start_setup_translation_table_and_enable_mmu_and_cache(
    ctrl,
    (uint32_t *) bsp_translation_table_base,
    ARM_MMU_DEFAULT_CLIENT_DOMAIN,
    &zynq_mmu_config_table[0],
    RTEMS_ARRAY_SIZE(zynq_mmu_config_table)
  );
}
*/

#include <arch/sys_arch.h>
#include <lwip/dhcp.h>
#include <netstart.h>
struct netif net_interface;

void init_network(void)
{
  int ret;
  ip_addr_t ipaddr, netmask, gw;
    
  IP_ADDR4( &ipaddr, 192, 168, 100, 236 );
  IP_ADDR4( &netmask, 255, 255, 255, 0 );
  IP_ADDR4( &gw, 0, 0, 0, 0 );
  unsigned char mac_ethernet_address[] = { 0x00, 0x06, 0x77, 0x00, 0x00, 0x00 };
  
  /*
  IP_ADDR4( &ipaddr, 10, 0, 2, 14 );
  IP_ADDR4( &netmask, 255, 255, 255, 0 );
  //IP_ADDR4( &gw, 10, 0, 2, 3 );
  IP_ADDR4( &gw, 0, 0, 0, 0 );
  unsigned char mac_ethernet_address[] = { 0x00, 0x06, 0x77, 0x00, 0x00, 0x00 };
  //unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x22, 0x01 };
*/
  netif_set_addr(&net_interface, (const ip4_addr_t*) &ipaddr, (const ip4_addr_t*) &netmask, (const ip4_addr_t*) &gw);


  ret = start_networking(
    &net_interface,
    &ipaddr,
    &netmask,
    &gw,
    mac_ethernet_address
  );

  if ( ret != 0 ) {
    return;
  }

  //dhcp_start( &net_interface );



}