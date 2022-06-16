/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#include "app.h"
#include "stdio.h"
#include "sl_simple_timer.h"
#include "app_log.h"

//extern const volatile uint8_t myText[];

const uint8_t myText[] = {
    "It was close upon half-past six and the evening shadows were growing"
    "denser when two soldiers reached the little space, planted with trees,"
    "opposite the Musee Galliera, where the Rue de Chaillot and the Rue"
    "Pierre-Charron meet. One wore an infantryman's sky-blue great-coat; the"
    "other, a Senegalese, those clothes of undyed wool, with baggy breeches"
    "and a belted jacket, in which the Zouaves and the native African troops"
    "have been dressed since the war. One of them had lost his right leg, the"
    "other his left arm."
    "They walked round the open space, in the center of which stands a fine"
    "group of Silenus figures, and stopped. The infantryman threw away his"
    "cigarette. The Senegalese picked it up, took a few quick puffs at it,"
    "put it out by squeezing it between his fore-finger and thumb and stuffed"
    "it into his pocket. All this without a word."
    "Almost at the same time two more soldiers came out of the Rue Galliera."
    "It would have been impossible to say to what branch they belonged, for"
    "their military attire was composed of the most incongruous civilian"
    "garments. However, one of them sported a Zouave's _chechia_, the other"
    "an artilleryman's _kepi_. The first walked on crutches, the other on two"
    "sticks. These two kept near the newspaper-kiosk which stands at the edge"
    "of the pavement."
    "Three others came singly by the Rue Pierre-Charron, the Rue Brignoles"
    "and the Rue de Chaillot: a one-armed rifleman, a limping sapper and a"
    "marine with a hip that looked as if it was twisted. Each of them made"
    "straight for a tree and leant against it."
    "Not a word was uttered among them. None of the seven crippled soldiers"
    "seemed to know his companions or to trouble about or even perceive their"
    "presence. They stood behind their trees or behind the kiosk or behind"
    "the group of Silenus figures without stirring. And the few wayfarers"
    "who, on that evening of the 3rd of April, 1915, crossed this"
    "unfrequented square, which received hardly any light from the shrouded"
    "street-lamps, did not slacken pace to observe the men's motionless"
    "outlines."
    "A clock struck half-past six. At that moment the door of one of the"
    "houses overlooking the square opened. A man came out, closed the door"
    "behind him, crossed the Rue de Chaillot and walked round the open space"
    "in front of the museum. It was an officer in khaki. Under his red"
    "forage-cap, with its three lines of gold braid, his head was wrapped in"
    "a wide linen bandage, which hid his forehead and neck. He was tall and"
    "very slenderly built. His right leg ended in a wooden stump with a"
    "rubber foot to it.He leant on a stick."
    "Leaving the square,he stepped into the roadway of the Rue"
    "Here she comes, said the officer."
     "She took the road by which he had arrived and turned down the Rue"
     "Pierre-Charron, keeping to the right-hand pavement and thus making for"
     "the space where the street meets the Rue de Chaillot. Her walk was"
     "light, her step easy and wellbalanced. The wind, buffeting against her"
     "as she moved quickly on her way, swelled out the long blue veil floating"
     "around her shoulders. Notwithstanding the width of the cloak, the"
     "rhythmical swing of her body and the youthfulness of her figure were"
     "revealed. The officer kept behind her and walked along with an"
     "absent-minded air, twirling his stick, like a man taking an aimless"
     "stroll."
     "At this moment there was nobody in sight, in that part of the street,"
     "except him and her. But, just after she had crossed the Avenue Marceau"
     "and some time before he reached it, a motor standing in the avenue"
     "started driving in the same direction as the nurse, at a fixed distance"
     "from her."
     "It was a taxi-cab. And the officer noticed two things: first, that there"
     "were two men inside it and, next, that one of them leant out of the"
     "window almost the whole time, talking to the driver. He was able to"
     "catch a momentary glimpse of this mans face, cut in half by a heavy"
     "mustache and surmounted by a gray felt hat."
     "Meanwhile, the nurse walked on without turning round. The officer had"
     "crossed the street and now hurried his pace, the more so as it struck"
     "him that the cab was also increasing its speed as the girl drew near the"
     "space in front of the museum."
     "From where he was the officer could take in almost the whole of the"
     "little square at a glance and, however sharply he looked, he discerned"
     "nothing in the darkness that revealed the presence of the seven crippled"
     "men. No one, moreover, was passing on foot or driving. In the distance"
     "only, in the dusk of the wide crossing avenues, two tram-cars, with"
     "lowered blinds, disturbed the silence."
     "Nor did the girl, presuming that she was paying attention to the sights"
     "of the street, appear to see anything to alarm her. She gave not the"
     "least sign of hesitation. And the behavior of the motorcab following"
     "her did not seem to strike her either, for she did not look round once."
     "The cab, however, was gaining ground. When it neared the square,it was"
     "ten or fifteen yards, at most, from the nurse; and, by the time that"
     "she, still noticing nothing, had reached the first trees, it came"
     "closer yet and, leaving the middle of the road, began to hug the step."


};

//const uint8_t myText[] = {"U-Boot 2009.08 (Nov 15 2009 - 22:03:26)"
//"   CPU:    Xtensa test_mmuhifi_c3 at 41.6777 MHz"
//"   Board:  XT-AV200: Avnet board + Xilinx LX200 FPGA + Tensilica bitstream"
//"   SysRAM: 96 MB"
//"   Flash: 16 MB"
//"   In:    serial"
//"   Out:   serial"
//"   Err:   serial"
//"   MAC:    00:50:C2:13:6f:07"
//"   IP:     192.168.11.105"
//"   open_ethernet"
//"   Autobooting in 5 seconds, press <SPACE> to stop"
//"   Using open_ethernet device"
//"   TFTP from server 192.168.11.55; our IP address is 192.168.11.105"
//"   Filename uImage.xtensa-2.6.29-smp.test_mmuhifi_c3."
//"   Load address: 0xd2000000"
//"   Loading: #################################################################"
//"            ###############"
//"   done"
//"   Bytes transferred = 1161826 (11ba62 hex)"
//"   Automatic boot of image at addr 0xD2000000 ..."
//"   ## Booting kernel from Legacy Image at d2000000 ..."
//"      Image Name:   Linux-2.6.29-rc7"
//"      Image Type:   Xtensa Linux Kernel Image (gzip compressed)"
//"      Data Size:    1161762 Bytes =  1.1 MB"
//"      Load Address: d0001000"
//"      Entry Point:  d0001000"
//"      Verifying Checksum ... OK"
//"      Uncompressing Kernel Image ... OK"
//
//"   ## Linux Boot Params Starting At Address:0xd5f50000"
//"      MEMORY:          tag:0x1003, type:0X1000, start:0X0, end:0X6000000"
//"      COMMAND_LINE:    tag:0x1001, size:188, data:console=ttyS0,38400 ip=192.168.11.105:192.168.11.55:192.168.11.1:255.255.255.0:*HiFi-2 Demo* root=/dev/nfs rw nfsroot=192.168.11.55:/exports/LINUX_ROOT.HiFi-2 debug coredump_filter=0xff"
//"      SERIAL_BAUDRATE: tag:0x1004, size:4, baudrate:38400"
//
//"   ## Transferring Control to Linux Kernel At Address 0xd0001000 ..."
//"   parse_bootparam: Ignoring tag 0x1004"
//"   lx60 platform_init(bootparams:d5f50000)"
//"   Linux version 2.6.29-rc7 (pdelaney@pdelaney_fc5.hq.tensilica.com) (gcc version 4.2.1) #201 SMP Tue Nov 17 23:49:39 PST 2009"
//"   lx60 platform_setup(cmdline[0]:console=ttyS0,38400 ip=192.168.11.105:192.168.11.55:192.168.11.1:255.255.255.0:*HiFi-2 Demo* root=/dev/nfs rw nfsroot=192.168.11.55:/exports/LINUX_ROOT.HiFi-2 debug coredump_filter=0xff)"
//"   smp_init_cpus: Core Count = 3"
//"   smp_init_cpus: Core Id = 9320"
//"   On node 0 totalpages: 24576"
//"   free_area_init_node: node 0, pgdat d0196540, node_mem_map d01fa000"
//"     Normal zone: 216 pages used for memmap"
//"     Normal zone: 24360 pages, LIFO batch:3"
//"   smp_prepare_boot_cpu:"
//"   Built 1 zonelists in Zone order, mobility grouping on.  Total pages: 24360"
//"   Kernel command line: console=ttyS0,38400 ip=192.168.11.105:192.168.11.55:192.168.11.1:255.255.255.0:*HiFi-2 Demo* root=/dev/nfs rw nfsroot=192.168.11.55:/exports/LINUX_ROOT.HiFi-2 debug coredump_filter=0xff"
//"   trap_init 0"
//"   PID hash table entries: 512 (order: 9, 2048 bytes)"
//"   time_init: Platform Calibrating CPU frequency"
//"   time_init: ccount_per_jiffy:416777 [41.67 MHz], nsec_per_ccount:23"
//"   Console: colour dummy device 80x25"
//"   console [ttyS0] enabled"
//"   Dentry cache hash table entries: 16384 (order: 4, 65536 bytes)"
//"   Inode-cache hash table entries: 8192 (order: 3, 32768 bytes)"
//"   Memory: 95196k/98304k available (1229k kernel code, 3040k reserved, 28k data, 72k init 0k highmem)"
//"   Calibrating delay loop... 41.26 BogoMIPS (lpj=206336)"
//"   Mount-cache hash table entries: 512"
//"   cpu 1 fffd"
//"   secondary_trap_init 1"
//"   Calibrating delay loop... 41.67 BogoMIPS (lpj=208384)"
//"   secondary_irq_init: set cached_irq_mask and enable interrupts))"
//"   secondary_time_init()"
//"   secondary_irq_enable(intrnum:6): cpu:1, INTENABLE:7c"
//"   secondary_irq_enable(intrnum:0): cpu:1, INTENABLE:7d"
//"   cpu 2 fff9"
//"   secondary_trap_init 2"
//"   Calibrating delay loop... 41.57 BogoMIPS (lpj=207872)"
//"   secondary_irq_init: set cached_irq_mask and enable interrupts))"
//"   secondary_time_init()"
//"   secondary_irq_enable(intrnum:6): cpu:2, INTENABLE:7c"
//"   secondary_irq_enable(intrnum:0): cpu:2, INTENABLE:7d"
//"   Brought up 3 CPUs"
//"   smp_cpus_done:"
//"   net_namespace: 304 bytes"
//"   NET: Registered protocol family 16"
//"   lx60_init()"
//"   bio: create slab <bio-0> at 0"
//"   NET: Registered protocol family 2"
//"   IP route cache hash table entries: 1024 (order: 0, 4096 bytes)"
//"   TCP established hash table entries: 4096 (order: 3, 32768 bytes)"
//"   TCP bind hash table entries: 4096 (order: 3, 32768 bytes)"
//"   TCP: Hash tables configured (established 4096 bind 4096)"
//"   TCP reno registered"
//"  NET: Registered protocol family 1"
//"   msgmni has been set to 186"
//"   alg: No test for md5 (md5-generic)"
//"   alg: No test for des (des-generic)"
//"   alg: No test for des3_ede (des3_ede-generic)"
//"   alg: No test for stdrng (krng)"
//"   io scheduler noop registered (default)"
//"   Serial: 8250/16550 driver, 4 ports, IRQ sharing disabled"
//"   serial8250: ttyS0 at MMIO 0x0 (irq = 3) is a 16550A"
//"   oeth_probe: {"
//"   oeth_setup: Open Ethernet Core Version 1.0.1"
//"    : oeth_setup: Found id1:2000, id2:5c30 at phy_id:3."
//"    : Hardware MAC Address: 00:50:c2:13:6f:0f"
//"   eth0 (): not using net_device_ops yet"
//"   oeth_probe: }"
//"   mice: PS/2 mouse device common for all mice"
//"   TCP cubic registered"
//"   NET: Registered protocol family 17"
//"   RPC: Registered udp transport module."
//"   RPC: Registered tcp transport module."
//"   oeth_open:  Ready to process packets now on dev->name:eth0, dev:d597d800;"
//"   IP-Config: Complete:"
//"        device=eth0, addr=192.168.11.105, mask=255.255.255.0, gw=192.168.11.1,"
//"        host=HiFi-2 Demo, domain=, nis-domain=(none),"
//"        bootserver=192.168.11.55, rootserver=192.168.11.55, rootpath="
//"   Looking up port of RPC 100003/2 on 192.168.11.55"
//"   Looking up port of RPC 100005/1 on 192.168.11.55"
//"   VFS: Mounted root (nfs filesystem) on device 0:11."
//"   Freeing unused kernel memory: 72k freed"
//"   Starting portmap: done"
//"   Initializing random number generator... done."
//"   Starting network..."
//"   ip: RTNETLINK answers: File exists"
//"   Starting sshd: OK"
//"   Starting NFS statd: done"
//"   Starting NFS services: done"
//"   Starting NFS daemon: done"
//"   Starting NFS mountd: done"
//"   Starting domain name daemon: namedwarning: `named uses 32-bit capabilities (legacy support in use)"
//"   failed"
//"   Fri Nov 20 17:10:37 2009"
//"   Mounting Other NFS Filesystems"
//
//"   Welcome to your custom Xtensa HiFi-2 Codec Developemnt System"
//"   hifi login: root"
//"   Password: linux1"};

#define DATA_NOTIFICATION_INTERVAL 1 //ms

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;
static uint8_t Notification_enabled = 0;

// Periodic timer handle.
static sl_simple_timer_t app_periodic_timer;

// Periodic timer callback.
static void app_periodic_timer_cb(sl_simple_timer_t *timer, void *data);

uint8_t connection;
uint8_t connection_MTU;


uint16_t myTextsize;
volatile int16_t offset = 0;

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
  ///

  myTextsize = sizeof(myText);

  app_log("The size of the file is: %d \n\n\n\n",myTextsize );

//  for(long loop = 0; loop < myTextsize ; loop++)
//     app_log("%c ", myText[loop]);
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
  ///
  ///
  sl_status_t sc;
 // static uint8_t counter = 0;




  if ( Notification_enabled == 1)
    {
      if (offset <= myTextsize)
            {

            //  if(counter++ == 1){

       //  do {
              sc = sl_bt_gatt_server_send_notification(1, gattdb_Text,
                                                connection_MTU-5,
                                                &myText[offset]);
             offset+= connection_MTU-5;
     //        counter = 0;
           //   }
            // app_log("%d \n\r", offset );
        //    }
        //    while(sc == 0);
            //app_log_info("%x", sc);

            }



    }

}
/**************************************************************************//**
 * Timer callback
 * Called periodically to time periodic temperature measurements and indications.
 *****************************************************************************/
static void app_periodic_timer_cb(sl_simple_timer_t *timer, void *data)
{
  (void)data;
  (void)timer;
//  sl_status_t sc;
//  static uint16_t offset = 0;


//
//
//  if ((offset >= 0) && (offset <= myTextsize))
//      {
//
////        for(long loop = 0; loop < connection_MTU ; loop++)
////           app_log("%c ", myText[offset+loop]);
//
//
//        sc = sl_bt_gatt_server_notify_all(gattdb_Text,
//                                          connection_MTU,
//                                          &myText[offset]);
//
////        sl_bt_gatt_server_send_notification(1, gattdb_Text,
////                                                                                      connection_MTU,
////                                                                                      &myText[offset]);
//
//       offset+= connection_MTU;
//
//    //    app_log("MTU %d , offset %d \n\n", connection_MTU, offset);
//
//      }


}


/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[8];
  uint16_t  max_mtu;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:

      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);

      // Pad and reverse unique ID to get System ID.
      system_id[0] = address.addr[5];
      system_id[1] = address.addr[4];
      system_id[2] = address.addr[3];
      system_id[3] = 0xFF;
      system_id[4] = 0xFE;
      system_id[5] = address.addr[2];
      system_id[6] = address.addr[1];
      system_id[7] = address.addr[0];

      sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id,
                                                   0,
                                                   sizeof(system_id),
                                                   system_id);
      app_assert_status(sc);

      // Create an advertising set.
      sc = sl_bt_advertiser_create_set(&advertising_set_handle);
      app_assert_status(sc);

      sl_bt_gatt_server_set_max_mtu(250,&max_mtu);
      // Set advertising interval to 100ms.
      sc = sl_bt_advertiser_set_timing(
        advertising_set_handle,
        160, // min. adv. interval (milliseconds * 1.6)
        160, // max. adv. interval (milliseconds * 1.6)
        0,   // adv. duration
        0);  // max. num. adv. events
      app_assert_status(sc);
      // Start general advertising and enable connections.
      sc = sl_bt_advertiser_start(
        advertising_set_handle,
        sl_bt_advertiser_general_discoverable,
        sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);
      break;


    case sl_bt_evt_gatt_server_characteristic_status_id:

         if (gattdb_Text == evt->data.evt_gatt_server_characteristic_status.characteristic) {
           // client characteristic configuration changed by remote GATT client
           if (sl_bt_gatt_server_client_config == (sl_bt_gatt_server_characteristic_status_flag_t)evt->data.evt_gatt_server_characteristic_status.status_flags) {

               if(sl_bt_gatt_notification == (sl_bt_gatt_client_config_flag_t)evt->data.evt_gatt_server_characteristic_status.client_config_flags)
                 {
                   Notification_enabled = 1;
                   connection = evt->data.evt_gatt_server_characteristic_status.connection;
                   app_log(" Notification_enabled = 1");

                   sc = sl_simple_timer_start(&app_periodic_timer,
                                                 DATA_NOTIFICATION_INTERVAL,
                                                 app_periodic_timer_cb,
                                                 NULL,
                                                 true);
                      app_assert_status(sc);
                 }
               else if(sl_bt_gatt_disable == (sl_bt_gatt_client_config_flag_t)evt->data.evt_gatt_server_characteristic_status.client_config_flags)
                 {
                   Notification_enabled = 0;
                   sl_simple_timer_stop(&app_periodic_timer);
                 }

           }
           // confirmation of indication received from remove GATT client
          else {
             app_assert(false,
                        "[E: 0x%04x] Unexpected status flag in evt_gatt_server_characteristic_status\n",
                        (int)evt->data.evt_gatt_server_characteristic_status.status_flags);
           }
         }
         break;

    case sl_bt_evt_gatt_mtu_exchanged_id:

      connection_MTU = evt->data.evt_gatt_mtu_exchanged.mtu;

      break;


    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      Notification_enabled = 0;
      offset = 0;

      //sl_bt_connection_set_preferred_phy(1,2,2);
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:

      Notification_enabled = 0;
      offset = 0;
      sl_simple_timer_stop(&app_periodic_timer);
      // Restart advertising after client has disconnected.
      sc = sl_bt_advertiser_start(
        advertising_set_handle,
        sl_bt_advertiser_general_discoverable,
        sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);
      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}
