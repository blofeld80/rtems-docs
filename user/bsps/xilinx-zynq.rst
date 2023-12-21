.. SPDX-License-Identifier: CC-BY-SA-4.0

.. Copyright (C) 2015, 2020 Chris Johns (chrisj@rtems.org)

xilinx-zynq
===========

This BSP supports the Xilinx Zynq range of devices. This family of
devices contain the same ARM hard IP and the different parts have
different sizes of programable logic. There are some helper scripts
in the appendix that might be usefull to get started.

The BSP defaults may need to be adjusted using ``configure`` BSP
options to match the size of memory your board may have.

Supported boards
----------------

+----------------------+------------------------------------+-----------------------------------------------------------------------------------------------------+
| RTEMS BSP Name       | Compatible Board                   | Product Page                                                                                        |
+======================+====================================+=====================================================================================================+
| xilinx_zynq_zc702    | ZC702                              | https://www.xilinx.com/products/boards-and-kits/ek-z7-zc702-g.html                                  |
+----------------------+------------------------------------+-----------------------------------------------------------------------------------------------------+
| xilinx_zynq_zc706    | ZC706                              | https://www.xilinx.com/products/boards-and-kits/ek-z7-zc706-g.html                                  |
+----------------------+------------------------------------+-----------------------------------------------------------------------------------------------------+
| xilinx_zynq_zedboard | Zedboard                           | https://www.avnet.com/wps/portal/us/products/avnet-boards/avnet-board-families/zedboard/            |
+----------------------+------------------------------------+-----------------------------------------------------------------------------------------------------+
| xilinx_zynq_picozed  | Picozed 7010, 7015, 7020, 7030     | https://www.avnet.com/wps/portal/us/products/avnet-boards/avnet-board-families/picozed/             |
+----------------------+------------------------------------+-----------------------------------------------------------------------------------------------------+
| xilinx_zynq_zybo     | Zybo                               | https://digilent.com/reference/programmable-logic/zybo/start                                        |
+----------------------+------------------------------------+-----------------------------------------------------------------------------------------------------+
| xilinx_zynq_zybo_z7  | Zybo Z7-10, Z7-20                  | https://digilent.com/reference/programmable-logic/zybo-z7/start                                     |
+----------------------+------------------------------------+-----------------------------------------------------------------------------------------------------+
| xilinx_zynq_pynq     | PYNQ Z1, Z2                        | http://www.pynq.io/home.html                                                                        |
+----------------------+------------------------------------+-----------------------------------------------------------------------------------------------------+
| xilinx_zynq_microzed | MicroZed 7010, 7020                | https://www.avnet.com/wps/portal/us/products/avnet-boards/avnet-board-families/microzed/            |                                                             
+----------------------+------------------------------------+-----------------------------------------------------------------------------------------------------+
| xilinx_zynq_a9_qemu  | QEMU Machine xilinx-zynq-a9        |                                                                                                     |
+----------------------+------------------------------------+-----------------------------------------------------------------------------------------------------+

**NOTE:**  For Arty Z7-10/20 please compare schematic and xdc with PYNQ Z1


+----------------------+-------------------+-------------------+----------------------+----------------------------------------------------------------------------+------------------+---------------------+------------------------------------+-------------------+
| RTEMS BSP Name       | xilinx_zynq_zc702 | xilinx_zynq_zc706 | xilinx_zynq_zedboard | xilinx_zynq_picozed                                                        | xilinx_zynq_zybo | xilinx_zynq_zybo_z7 | xilinx_zynq_microzed               | xilinx_zynq_pynq  |
+======================+===================+===================+======================+============================================================================+==================+=====================+====================================+===================+
| **Compatible Board** | ZC702             | ZC706             | Zedboard             | PicoZed 7010 / 7015 / 7020 / 7030                                          | Zybo             | Zybo Z7-10 / Z7-20  | MicoZed 7010 / 7020 SOM C/I        | PYNQ Z1 / Z2      |
+----------------------+-------------------+-------------------+----------------------+----------------------------------------------------------------------------+------------------+---------------------+------------------------------------+-------------------+
| **Carrier**          | NA                | NA                | NA                   | AES-PZCC-FMC-V2-G                                                          | NA               | NA                  | NA                                 | NA                |
+----------------------+-------------------+-------------------+----------------------+----------------------------------------------------------------------------+------------------+---------------------+------------------------------------+-------------------+
| **Part**             | XC7Z020-1CLG484C  | XC7Z045-2FFG900C  | XC7Z020-1CLG484C     | XC7Z010-1CLG400C/I, XC7Z015-1SBG485I, XC7Z020-1CLG400C/I, XC7Z030-1SBG485I | XC7Z010-1CLG400C | XC7Z010-1CLG400C    | XC7Z010-1CLG400C, XC7Z020-1CLG400C | XC7Z020-1CLG400C  |
+----------------------+-------------------+-------------------+----------------------+----------------------------------------------------------------------------+------------------+---------------------+------------------------------------+-------------------+
| **SD Card**          | Yes               | Yes               | Yes                  | Yes                                                                        | Yes              | Yes                 | Yes                                | Yes               |
+----------------------+-------------------+-------------------+----------------------+----------------------------------------------------------------------------+------------------+---------------------+------------------------------------+-------------------+
| **PS QSPI**          | 2x16 MB           | 16 MB             | 32 MB                | 16 MB                                                                      | 16 MB            | 16 MB               | 16 MB                              | 16 MB             |
+----------------------+-------------------+-------------------+----------------------+----------------------------------------------------------------------------+------------------+---------------------+------------------------------------+-------------------+
| **PS DDR3**          | 1 GB              | 1 GB              | 512 MB               | 1 GB                                                                       | 512 MB           | 1 GB                | 1 GB                               | 512 MB            |
+----------------------+-------------------+-------------------+----------------------+----------------------------------------------------------------------------+------------------+---------------------+------------------------------------+-------------------+
| **PS Clk**           | 33.33 MHz         | 33.33 MHz         | 33.33 MHz            | 33.33 MHz                                                                  | 50 MHz           | 33.33 MHz           | 33.33 MHz                          | 50 MHz            |
+----------------------+-------------------+-------------------+----------------------+----------------------------------------------------------------------------+------------------+---------------------+------------------------------------+-------------------+
| **Console UART**     | 1                 | 1                 | 1                    | 1                                                                          | 1                | 1                   | 0                                  | 1                 |
+----------------------+-------------------+-------------------+----------------------+----------------------------------------------------------------------------+------------------+---------------------+------------------------------------+-------------------+



Host Machine Setup
------------------

On Ubuntu 20.04 / 22.04, prepare the machine using:

.. code-block:: bash

    sudo apt install build-essential unzip pax bison flex texinfo \
    python3-dev python-is-python3 libpython2-dev libncurses5-dev zlib1g-dev \
    ninja-build pkg-config libtool libpixman-1-dev default-jre libhidapi-dev \
    libftdi-dev libusb-1.0-0 libusb-1.0-0-dev libglib2.0-dev

    sudo snap install cmake

In addition to that, install: 

#. `Xilinx 2021.2 Vivado / Vitis tools <https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/archive.html>`_
#. `VS Code <https://code.visualstudio.com/>`_ or Eclipse Embedded (commented out in `install_tools.sh`)
#. `Segger J-Link Software <https://www.segger.com/downloads/jlink/>`_ if you plan to use J-Link 
#. `Xilinx Cable Drivers <https://docs.xilinx.com/r/en-US/ug973-vivado-release-notes-install-license/Install-Cable-Drivers>`_ if you want to use OpenOCD


As mentioned above, a couple of scripts are provided in the appendix to easen 
project creation. Following the RTEMS quick start guide, the 
scripts will operate on the folder ``~/quick-start``. You can adjust
tool versions and paths in ``config.sh``. In order to build / install Xilinx QEMU, 
OpenOCD and the RTEMS tools, you can run:

.. code-block:: bash

    cd ~
    git clone https://github.com/RTEMS/rtems-docs.git
    cd ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq

    ./install_tools.sh

You will find all tools installed in  ``~/quick-start/install/tools``.

Hardware Reference Designs
--------------------------

Build the reference design (Xilinx Vivado)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For all boards mentioned above you can generate the reference design by 
running

.. code-block:: bash

    cd ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq

    ./build_hardware.sh -b <board_name>

where ``board_name`` must be one of ``Pynq-Z1``,  ``Pynq-Z2``, 
``Picozed-7010``,  ``Picozed-7015``, ``Picozed-7020``,  ``Picozed-7030``, 
``Microzed-7010``, ``Microzed-7020``, ``Zybo``, ``Zybo-Z7-10`` or 
``Zybo-Z7-20``.


After completion you will find in  ``~/quick-start/install/hw/<board_name>``:

#. A ``*.xsa`` file - it is an archive which contains bitstream and several initialization files (can be read in by Xilinx Vitis) 
#. A ``*.bit`` file - the FPGA bitstream
#. A ``fsbl.elf`` file - the first stage bootloader
#. A ``boot.bin`` and a ``boot.mcs`` file. These files are bootimages and contain the bitstream and the first stage bootloader. The ``boot.mcs`` is used by the Xilinx tools to program non-volatile memory parts. The ``boot.bin`` can be put on an FAT32 formatted SD card. If you switch your board to SD card boot mode and connect the USB Uart (115k2, 8N1) you should be able to already observe the following boot up messages. 

.. code-block:: none

    Xilinx First Stage Boot Loader Release 2021.2 Nov  1 2023-20:58:14
    Devcfg driver initialized 
    Silicon Version 3.1
    Boot mode is SD
    SD: rc= 0SD Init Done 
    Flash Base Address: 0xE0100000
    Reboot status register: 0x60600000
    Multiboot Register: 0x0000C000
    Image Start Address: 0x00000000
    Partition Header Offset:0x00000C80
    Partition Count: 2
    Partition Number: 1
    Header Dump
    Image Word Len: 0x000F6EC0
    Data Word Len: 0x000F6EC0
    Partition Word Len:0x000F6EC0
    Load Addr: 0x00000000
    Exec Addr: 0x00000000
    Partition Start: 0x000065D0
    Partition Attr: 0x00000020
    Partition Checksum Offset: 0x00000000
    Section Count: 0x00000001
    Checksum: 0xFFD14B7E
    Bitstream
    In FsblHookBeforeBitstreamDload function 
    PCAP:StatusReg = 0x40000A30
    PCAP:device ready
    PCAP:Clear done
    Level Shifter Value = 0xA 
    Devcfg Status register = 0x40000A30 
    PCAP:Fabric is Initialized done
    PCAP register dump:
    PCAP CTRL 0xF8007000: 0x4C00E07F
    PCAP LOCK 0xF8007004: 0x0000001A
    PCAP CONFIG 0xF8007008: 0x00000508
    PCAP ISR 0xF800700C: 0x0802000B
    PCAP IMR 0xF8007010: 0xFFFFFFFF
    PCAP STATUS 0xF8007014: 0x00006A30
    PCAP DMA SRC ADDR 0xF8007018: 0x00100001
    PCAP DMA DEST ADDR 0xF800701C: 0xFFFFFFFF
    PCAP DMA SRC LEN 0xF8007020: 0x000F6EC0
    PCAP DMA DEST LEN 0xF8007024: 0x000F6EC0
    PCAP ROM SHADOW CTRL 0xF8007028: 0xFFFFFFFF
    PCAP MBOOT 0xF800702C: 0x0000C000
    PCAP SW ID 0xF8007030: 0x00000000
    PCAP UNLOCK 0xF8007034: 0x757BDF0D
    PCAP MCTRL 0xF8007080: 0x30800100
    DMA Done !
    FPGA Done ! In FsblHookAfterBitstreamDload function 
    Handoff Address: 0x00000000
    In FsblHookBeforeHandoff function 
    No Execution Address JTAG handoff 


Boot
----

Build the Bootloader (Xilinx Vitis)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The bootloader initialises the Zynq device. The Xilinx tool provide an
interface to configure the hardware. This is includes the buses,
clocks, memory and UART board rate. The output of this is called
``ps7_init`` and is a C file. The Xilinx SDK builds a first stage boot
loader (FSBL) using this file.

The U-Boot boot loader has it's own FSBL called ``MLO`` to initialise
the hardware.

You can generate the FSBL by running:

.. code-block:: bash

    cd ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/scripts

    ./build_fsbl.sh -x <full_path_to_xsa_file> -o <full_path_to_output_folder>


Internally, the script will create a TCL script in which it commands 
Vitis to create a hardware plattform and build the Xilinx BSP for
the given ``*.xsa`` as well as the first stage bootloader. Then it
hands over the TCL script to Vitis for execution. After Vitis has 
completed its work, the script will copy the bitstream and FSBL 
executable to the specified output folder.


Create a Bootimage (Xilinx Bootgen)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

RTEMS applications can be booted solely with the help of Xilinx Bootgen and 
the First Stage Bootloader (**FSBL**). Xilinx Bootgen creates a boot.bin file 
which contains the FSBL, the FPGA bitstream, and optionally an application 
(there are more data sections possible). If the application is not included in 
the boot.bin file, the FSBL will enable the JTAG interface and halt operation 
after the FPGA is programmed. 

Xilinx Bootgen takes in a ``*.bif`` - file which usually looks this way:

.. code-block:: none

    the_ROM_image:
    {
      [bootloader] fsbl.elf
      bitstream.bit
      app.elf
    }


To create a boot image simply run:

.. code-block:: bash

    # SD Card boot.bin
    bootgen -arch zynq -image my.bif -w on -o boot.bin

    # Some programmers expect mcs
    bootgen -arch zynq -image my.bif -w on -o boot.mcs


Alternatively, run: 

.. code-block:: bash

    cd ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/scripts

    ./build_boot_file.sh -b <full_path_to_bit_file> -f <full_path_to_fsbl_file> -a <full_path_to_app_file> -o <full_path_to_output_folder>

The script will create the ``*.bif`` file on the fly and hand it over to 
Xilinx Bootgen. The parameter ``full_path_to_app_file`` is optional.


BSP Details
-----------

Clocks
~~~~~~

An application can provide a function called:

.. code-block:: c

    uint32_t a9mpcore_clock_periphclk(void);

to return the peripheral clock. Normally this is half the CPU
clock. This function is declared ``weak`` so you can override the
default behaviour by providing it in your application.

Console
~~~~~~~

The console driver for the UARTs will always be initialized to a 
baud rate of 115200 with 8 bit characters, 1 stop bit and no parity
bits during start up.
Previous configurations programmed into the hardware by the Xilinx
tools or a bootloader will be overwritten.

The settings for the console driver can be changed by the user
application through the termios API afterwards.

MMU
~~~

The Zynq has a memory management unit (MMU). A basic configuration is
provided in ``rtems/bsps/arm/xilinx-zynq/start/bspstartmmu.c``. It 
might be required to unlock the memory regions of FPGA / CPU peripherals 
by adding an entry to ``zynq_mmu_config_table``. It is also possible to
override the MMU from the application level by adding a c to the application
which contains something like:

.. code-block:: c

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
        .begin = <your_section_begin>,
        .end = <your_section_end>,
        .flags = ARMV7_MMU_DEVICE
    },
    {
        .begin = 0xe0000000U,
        .end = 0xe0200000U,
        .flags = ARMV7_MMU_DEVICE
    }, {
        .begin = 0xf8000000U,
        .end = 0xf9000000U,
        .flags = ARMV7_MMU_DEVICE
    }
    };

    BSP_START_TEXT_SECTION void zynq_setup_mmu_and_cache(void) __attribute__ ((weak));

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

Network (LibBSD)
~~~~~~~~~~~~~~~~

The Cadence network interface driver of LibBSD works on the Xilinx Zynq
platform. The hardware checksum support works on real hardware but does not
seem to be supported on Qemu therefore the default state is to disable
``IFCAP_TXCSUM`` and ``IFCAP_RXCSUM`` and this can be enabled from the shell
with:

.. code-block:: bash

    ifconfig cgem0 rxcsum txcsum

or with an ``ioctl()`` call to the network interface driver with ``SIOCSIFCAP``
and the mask ``IFCAP_TXCSUM`` and ``IFCAP_RXCSUM`` set.


Tutorial 
--------

This section contains a tiny tutorial on building RTEMS applications
using CMake and debugging them on QEMU and real hardware. The tutorial is
based on the Picozed 7015 board.


Build RTEMS and libBSD 
~~~~~~~~~~~~~~~~~~~~~~

First of all, RTEMS and libBSD need to be build. 

.. code-block:: bash

    cd ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/scripts

    # if you haven´t installed the tools
    ./install_tools.sh
    # to get the XSA file
    ./build_hardware.sh -b Picozed-7015
    # build RTEMS and libBSD
    ./build_rtems_and_libbsd.sh -b xilinx_zynq_picozed 

After completion, RTEMS and libBSD can be found in ``quick-start\install\sw\xilinx_zynq_picozed``.


Create a CMake Toolchain File 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There are a few approaches to RTEMS + CMake. For example:

#. See `https://github.com/nasa/PSP/blob/main/cmake/Modules/Platform/RTEMS.cmake <https://github.com/nasa/PSP/blob/main/cmake/Modules/Platform/RTEMS.cmake>`_ for extending CMake
#. See `https://github.com/robamu-org/rtems-cmake <https://github.com/robamu-org/rtems-cmake>`_ to extend RTEMS with modern CMake

Both of them have their pro/con and could even be combined. However, 

#. a `CMake Toolchainfile <https://cmake.org/cmake/help/book/mastering-cmake/chapter/Cross%20Compiling%20With%20CMake.html>`_ is required in either way 
#. having modern CMake mechanisms availale only pays off if the CMakeLists of the libraries one puts on top of libbsd can be modified (not the case on my side)

This demo will use only use a toolchain file, which can be generated by 
running:

.. code-block:: bash

    cd ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/scripts

    ./create_toolchain_file.sh -b xilinx_zynq_picozed

After completion, the file ``toolchain.make`` can be found in 
``quick-start\install\sw\xilinx_zynq_picozed\cmake``.


The toolchain file sets up the compiler paths and the initial flags. The 
example avoids using ``-qrtems`` by always using a gcc spec file. In 
addition to that, the executable linker flags are set so that each 
exectuable will link to a 'pre_main.o'. This is to make the unit tests 
of higher level libraries, which one might want to stack on libbsd, can 
be build without modifications to build scripts of this libraries. The 
executable format is changed to ``elf`` as the J-Link software does not 
accept ``exe``.


Create an Application
~~~~~~~~~~~~~~~~~~~~~

An example application can be found in ``~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/app``. 
It is componsed of three parts:

#. ``main.cpp`` simple "Hello World"
#. ``pre_main.c`` RTEMS initalization and jump to main
#. ``CMakeLists.txt`` the CMake build script

Test the build:

.. code-block:: bash

    cd ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/app
    mkdir build && cd build

    # Run CMake configure step
    cmake -G"Ninja" -DCMAKE_TOOLCHAIN_FILE=~/quick-start/install/sw/xilinx_zynq_picozed/cmake/toolchain.cmake -DCMAKE_BUILD_TYPE=Debug ../src/

        [cmake] -- The C compiler identification is GNU 13.2.0
        [cmake] -- The CXX compiler identification is GNU 13.2.0
        [cmake] -- Could not determine Eclipse version, assuming at least 3.6 (Helios). Adjust CMAKE_ECLIPSE_VERSION if this is wrong.
        [cmake] -- Detecting C compiler ABI info
        [cmake] -- Detecting C compiler ABI info - done
        [cmake] -- Check for working C compiler: /home/blofeld/quick-start/install/tools/toolchain/bin/arm-rtems6-gcc - skipped
        [cmake] -- Detecting C compile features
        [cmake] -- Detecting C compile features - done
        [cmake] -- Detecting CXX compiler ABI info
        [cmake] -- Detecting CXX compiler ABI info - done
        [cmake] -- Check for working CXX compiler: /home/blofeld/quick-start/install/tools/toolchain/bin/arm-rtems6-g++ - skipped
        [cmake] -- Detecting CXX compile features
        [cmake] -- Detecting CXX compile features - done
        [cmake] -- Configuring done (1.6s)
        [cmake] -- Generating done (0.0s)
        [cmake] -- Build files have been written to: /home/blofeld/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/app/build

    # Run CMake build
    cmake --build .

        [3/3] Linking CXX executable ZynqDemo.elf
            Memory region         Used Size  Region Size  %age Used
                  RAM_INT_0:          0 GB       192 KB      0.00%
                  RAM_INT_1:          0 GB      65024 B      0.00%
                    RAM_MMU:          0 GB        16 KB      0.00%
                        RAM:     522224 KB    522224 KB    100.00%
                    NOCACHE:          1 MB         1 MB    100.00%
        UNEXPECTED_SECTIONS:          0 GB         0 GB


The CMake build will create three binaries (all can be found in the build folder):

#. ``ZynqDemo.exe`` - file contains code and debug symbols
#. ``ZynqDemo.dbg`` - file contains the debug symbols but no application code
#. ``ZynqDemo.elf`` - file contains application code but not debug symbols


Install VS Code and required extensions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

VS Code can be installed from `here <https://code.visualstudio.com/download>`_. Start VS Code and install the following extensions:

.. image:: supplement/xilinx-zynq/img/vscode_extensions.png
   :width: 600

**Note:** I am using WSL2. VS Code is installed on Windows 11 and I have the 
**Remote - WSL** extension installed. All other extensions need to be
installed on the Linux side. This can be done by starting VS code from the
Linux drive.

Prepare the VS Code Workspace by running:

.. code-block:: bash

    cd ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/scripts

    ./create_vs_code_folder.sh  -b xilinx_zynq_picozed


The script will create the folder ``.vscode`` in the ``app`` folder and create five files:

#. ``tasks.json`` - contains a task to start QEMU. This task will be started when a QEMU debug session is started
#. ``settings.json`` - CMake minimal configuration, source dir, build dir and Generator to use
#. ``launch.json`` - the debug launch configurations for QEMU and OpenOCD
#. ``cmake-kits.json`` - VS Code introduces the concept of kits to define toolchains. In this kit we simply define a kit called RTEMS and specify the toolchain file
#. ``c_cpp_properties.json`` - some standard configuration for working with C/C++ (i.e. make intellisense work)

Open VS Code and in the folder ``app``. 

.. code-block:: bash

    cd ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/app

    code .

#. If asked, do not agree to hide the activiybar
#. If asked to "Configure Cmake Options Visibility" select yes and make sure they are not hidden
#. If required, **Ctrl + Shift + P** → type "Kit" → Select a kit → use RTEMS
#. Try to build the project by clicking on "build" in the lower option bar
#. If VS Code got stuck somewhere, open the command palette (**Ctrl + Shift + P**) and run "CMake: Configure" by yourself

.. image:: supplement/xilinx-zynq/img/vscode_view_1.png
   :width: 600

QEMU Debug Session
~~~~~~~~~~~~~~~~~~

Contrary to the next chapter, this one will use a devicetree based machine. 
Xilinx proposes to use the machine ``arm-generic-fdt-7series`` (`LINK <https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/821854273/Running+Bare+Metal+Applications+on+QEMU#RunningBareMetalApplicationsonQEMU-Runningabare-metalapplicationonZynq7000>`_). 
This virtual machine is described by a devicetree which can be used to model 
the hardware of a concrete board. 

A devicetree example for the Picozed board has been added (see subfolder 
``dts``). Some notes on that:

#. The skelton ``zynq-7000.dtsi`` has been modified to make QEMU load a model of the PL310 cache controller. It may sound strange, but  ``compatible = "arm,pl310-cache";`` must be replaced by ``compatible = "arm,l2x0";`` as the original setting only loads a dummy and you will end up with a fatal error (``ARM_FATAL_L2C_310_UNEXPECTED_ID``) as soon as RTEMS has been configured to use I/D caches.
#. | The devicetree specifies two cores. Therefore, ``RTEMS_SMP`` needs to be enabled when building RTEMS

The devicetree blob can be build using:

.. code-block:: bash
    
    cd ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/dts
    mkdir ~/quick-start/install/sw/xilinx_zynq_zybo/dtb
    ~/quick-start/install/tools/toolchain/bin/dtc  -I dts -O dtb -o ~/quick-start/install/sw/xilinx_zynq_zybo/dtb/picozed-zynq7.dtb picozed-zynq7.dts


Now run the machine with (be aware that the app is configured to restart after finishing):

.. code-block:: bash

    ~/quick-start/install/tools/qemu/bin/qemu-system-aarch64 -M arm-generic-fdt-7series -serial /dev/null -serial mon:stdio -display none \
    -m 1024M -kernel ~/rtems-docs/user/bsps/arm/supplement/xilinx-zynq/app/build/ZynqDemo.exe -dtb ~/quick-start/install/dtb/picozed-zynq7.dtb


    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
                                STACK USAGE BY THREAD
    ID         NAME                  LOW        HIGH       CURRENT     AVAIL   USED
    0x09010001 IDLE                  0x002090f0 0x0020a0df 0x0020a0e0   4080      0
    0x0b010001                       0x0020a368 0x0020c357 0x0020c358   8176    648
    0x00000000 Interrupt Stack       0x00203b50 0x00204b3f 0x00000000   4080     60

    [ RTEMS shutdown ]
    CPU: 0
    RTEMS version: 6.0.0.e05d8455ad4269e2cb93078512979ebd0d49166a
    RTEMS tools: 13.2.0 20230727 (RTEMS 6, RSB 052ae74bb2448646fd90a5e809863bdd339f1aed-modified, Newlib 3cacedb)
    executing thread ID: 0x0b010001
    executing thread name:
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
    Hello World
                                STACK USAGE BY THREAD
    ID         NAME                  LOW        HIGH       CURRENT     AVAIL   USED
    0x09010001 IDLE                  0x002090f0 0x0020a0df 0x0020a0e0   4080      0
    0x0b010001                       0x0020a368 0x0020c357 0x0020c358   8176    648
    0x00000000 Interrupt Stack       0x00203b50 0x00204b3f 0x00000000   4080     60

    ...

**NOTE:** To shutdown a QEMU machine use ``CTRL + A``, release the keys and hit ``X``.


Of course the program can be debugged using QEMU. Set a breakpoint, open the "Run and Debug" tab and click the "Play" button.

.. image:: supplement/xilinx-zynq/img/DebugStart.png
   :width: 600


.. image:: supplement/xilinx-zynq/img/DebugBPhit.png
   :width: 600




Debugging QEMU target ``xilinx-zynq-a9``
-----------------------------------------

The machine ``xilinx-zynq-a9`` is only a single core without caches. 
It seems to have become deprecated as no Xilinx documentation is 
mentioning it anymore. However, this part of the documentation is still 
valid and has highly valuable information on running QEMU from the command 
line and GDB.

To debug an application add the QEMU options ``-s``. If you need to
debug an initialisation issue also add ``-S``. For example to debug a
networking application you could use:

.. code-block:: none

    qemu-system-arm -M xilinx-zynq-a9 -m 256M -no-reboot -serial \
        null -serial mon:stdio -nographic \
	-net nic,model=cadence_gem -net vde,id=vde0,sock=/tmp/vde1 \
	-kernel myapp.exe \
	-s -S

Start GDB with the same executable QEMU is running and connect to the
QEMU GDB server:

.. code-block:: none

    (gdb) target remote :1234

If your application is crashing set a breakpoint on the fatal error
handler:

.. code-block:: none

    (gdb) b bsp_fatal_extension

Enter continue to run the application. Running QEMU loads the
executable and initialises the CPU. If the ``-S`` option is provided
the CPU is held in reset. Without the option the CPU runs starting
RTEMS. Either way you are connecting to set up target and all you need
to do is continue:

.. code-block:: none

    (gdb) c

If you have a crash and the breakpoint on ``bsp_fatal_extension`` is
hit, load the following a GDB script:

.. code-block:: none

    define arm-crash
     set $code = $arg0
     set $r0 = ((const rtems_exception_frame *) $code)->register_r0
     set $r1 = ((const rtems_exception_frame *) $code)->register_r1
     set $r2 = ((const rtems_exception_frame *) $code)->register_r2
     set $r3 = ((const rtems_exception_frame *) $code)->register_r3
     set $r4 = ((const rtems_exception_frame *) $code)->register_r4
     set $r5 = ((const rtems_exception_frame *) $code)->register_r5
     set $r6 = ((const rtems_exception_frame *) $code)->register_r6
     set $r7 = ((const rtems_exception_frame *) $code)->register_r7
     set $r8 = ((const rtems_exception_frame *) $code)->register_r8
     set $r9 = ((const rtems_exception_frame *) $code)->register_r9
     set $r10 = ((const rtems_exception_frame *) $code)->register_r10
     set $r11 = ((const rtems_exception_frame *) $code)->register_r11
     set $r12 = ((const rtems_exception_frame *) $code)->register_r12
     set $sp = ((const rtems_exception_frame *) $code)->register_sp
     set $lr = ((const rtems_exception_frame *) $code)->register_lr
     set $pc = ((const rtems_exception_frame *) $code)->register_pc
     set $cpsr = ((const rtems_exception_frame *) $code)->register_cpsr
   end

Enter the command:

.. code-block:: none

    (gdb) arm-crash code


Enter ``bt`` to see the stack back trace.

The script moves the context back to the crash location. You should be
able to view variables and inspect the stack.

The fatal error handler runs inside an exception context that is not
the one than generated the exception.


Appendix
--------

Configuration - `config.sh`
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Adjust this file to switch tool versions and directory paths.

.. literalinclude:: supplement/xilinx-zynq/scripts/config.sh
   :language: bash

Install OpenOCD, RTEMS Toolchain and Xilinx QEMU  - `install_tools.sh`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: bash
    
    ./install_tools.sh

.. literalinclude:: supplement/xilinx-zynq/scripts/install_tools.sh
   :language: bash



Build Hardware - `build_hardware.sh`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This script will call `build_fsbl.sh` and `build_boot_file.sh`

.. code-block:: bash
    
    ./build_hardware.sh -b <board_name>

.. literalinclude:: supplement/xilinx-zynq/scripts/build_hardware.sh
   :language: bash


Build FSBL - `build_fsbl.sh`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: bash

    ./build_fsbl.sh -x <full_path_to_xsa_file> -o <full_path_to_output_folder>

.. literalinclude:: supplement/xilinx-zynq/scripts/build_fsbl.sh
   :language: bash

Build Bootimage - `build_boot_file.sh`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: bash

    ./build_boot_file.sh -b <full_path_to_bit_file> -f <full_path_to_fsbl_file> -a <full_path_to_app_file> -o <full_path_to_output_folder>

.. literalinclude:: supplement/xilinx-zynq/scripts/build_boot_file.sh
   :language: bash