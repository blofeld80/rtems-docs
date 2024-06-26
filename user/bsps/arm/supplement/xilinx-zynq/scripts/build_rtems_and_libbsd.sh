#!/bin/bash
#SPDX-License-Identifier: BSD-2-Clause
#Copyright (C) 2023 B. Moessner


THIS_SCRIPT=$(realpath "$0")
THIS_DIR=$(dirname "${THIS_SCRIPT}")


#################################################
## check the arguments the user has passed
function print_help {
  echo "Please call this script using ./build_rtems_and_libbsd -b <bsp_name>"
  echo "where bsp_name is one of:"
  echo "  xilinx_zynq_pynq"
  echo "  xilinx_zynq_picozed"
  echo "  xilinx_zynq_microzed"
  echo "  xilinx_zynq_zybo"
  echo "  xilinx_zynq_zybo_z7"
  echo "  xilinx_zynq_zedboard"
  echo "  xilinx_zynq_zc702"
  echo "  xilinx_zynq_zc706"
}

function print_error {
  echo "ERROR: ${1}"
}


if [[ $# -eq 0 ]] ; then
    print_error "No board provided!"
    print_help
    exit 1
fi

for a in "$@"; do
  case $1 in
    -b|--board)
      RTEMS_BSP_NAME="${2}"
      shift
      shift
      ;;
    -h|--help)
      print_help
      exit 1
      ;;
    -*|--*)
      echo "Unknown argument $1"
      exit 1
      ;;
    *)
      ;;
  esac
done



#################################################
## check if the board is supported by this script
case ${RTEMS_BSP_NAME} in

  xilinx_zynq_pynq)
    echo "Builing for bsp: ${RTEMS_BSP_NAME}"
    ;;
  xilinx_zynq_picozed)
    echo "Builing for bsp: ${RTEMS_BSP_NAME}"
    ;;
  xilinx_zynq_microzed)
    echo "Builing for bsp: ${RTEMS_BSP_NAME}"
    ;;
  xilinx_zynq_zybo)
    echo "Builing for bsp: ${RTEMS_BSP_NAME}"
    ;;
  xilinx_zynq_zybo_z7)
    echo "Builing for bsp: ${RTEMS_BSP_NAME}"
    ;;
  xilinx_zynq_zedboard)
    echo "Builing for bsp: ${RTEMS_BSP_NAME}"
    ;;
  xilinx_zynq_zc702)
    echo "Builing for bsp: ${RTEMS_BSP_NAME}"
    ;;
  xilinx_zynq_zc702)
    echo "Builing for bsp: ${RTEMS_BSP_NAME}"
    ;;
  xilinx_zynq_zc706)
    echo "Builing for bsp: ${RTEMS_BSP_NAME}"
    ;;
  *)
    print_error "Unknown board ${RTEMS_BSP_NAME}"
    exit 1
    ;;
esac


  
# Read the configuration
source ${THIS_DIR}/config.sh



if [ ! -d "${TOP_DIR}" ]; then 
  mkdir -p ${TOP_DIR}
fi

git_clone_commit "RTEMS"   ${RTEMS_OS_GIT_REPO}     ${RTEMS_OS_VER_COMMIT}     ${RTEMS_OS_SRC_DIR}  
git_clone_commit "LIBBSD"  ${RTEMS_LIBBSD_GIT_REPO} ${RTEMS_LIBBSD_VER_COMMIT} ${RTEMS_LIBBSD_SRC_DIR} 
git_clone_branch "LWIP"    ${RTEMS_LWIP_GIT_REPO}   ${RTEMS_LWIP_VER_COMMIT}  ${RTEMS_LWIP_SRC_DIR}  



if [ ! -d "${RTEMS_TOOLCHAIN_INSTALL_DIR}" ]; then 
  echo "ERROR: Install toolchain first"	
  exit 1
fi


if [ -d "${RTEMS_OS_INSTALL_DIR}" ]; then 
  echo "Delete old RTEMS installation"	
  rm -rf ${RTEMS_OS_INSTALL_DIR}
fi 


if [ -d "${RTEMS_LIBBSD_INSTALL_DIR}" ]; then 
  echo "Delete old Libbsd installation"	
  rm -rf ${RTEMS_LIBBSD_INSTALL_DIR}
fi 

if [ -d "${RTEMS_LWIP_INSTALL_DIR}" ]; then 
  echo "Delete old LWIP installation"	
  rm -rf ${RTEMS_LWIP_INSTALL_DIR}
fi 


#################################################
# Build RTEMS
pushd ${RTEMS_OS_SRC_DIR}
./waf clean
./waf bspdefaults --rtems-bsps=${RTEMS_BSP_ARCH}/${RTEMS_BSP_NAME} > config.ini
sed -i 's/RTEMS_POSIX_API = False/RTEMS_POSIX_API = True/g' config.ini
sed -i 's/RTEMS_SMP = False/RTEMS_SMP = True/g' config.ini
#sed -i 's/BUILD_TESTS = False/BUILD_TESTS = True/g' config.ini
#sed -i 's/BUILD_LIBTESTS = False/BUILD_LIBTESTS = True/g' config.ini
#sed -i 's/BUILD_ADATESTS = False/BUILD_ADATESTS = True/g' config.ini
#sed -i 's/BUILD_BENCHMARKS = False/BUILD_BENCHMARKS = True/g' config.ini
#sed -i 's/BUILD_FSTESTS = False/BUILD_FSTESTS = True/g' config.ini
#sed -i 's/BUILD_MPTESTS = False/BUILD_MPTESTS = True/g' config.ini
#sed -i 's/BUILD_PSXTESTS = False/BUILD_PSXTESTS = True/g' config.ini
#sed -i 's/BUILD_PSXTMTESTS = False/BUILD_PSXTMTESTS = True/g' config.ini
#sed -i 's/BUILD_RHEALSTONE = False/BUILD_RHEALSTONE = True/g' config.ini
#sed -i 's/BUILD_SPTESTS = False/BUILD_SPTESTS = True/g' config.ini
#sed -i 's/BUILD_UNITTESTS = False/BUILD_UNITTESTS = True/g' config.ini
#sed -i 's/BUILD_VALIDATIONTESTS = False/BUILD_VALIDATIONTESTS = True/g' config.ini
#sed -i 's/BSP_PRESS_KEY_FOR_RESET = 0/BSP_PRESS_KEY_FOR_RESET = 1/g' config.ini

sed -i 's/OPTIMIZATION_FLAGS = -O2 -g -fdata-sections -ffunction-section/OPTIMIZATION_FLAGS = -Og -g -fdata-sections -ffunction-section/g' config.ini
./waf configure --prefix=${RTEMS_OS_INSTALL_DIR} --rtems-tools=${RTEMS_TOOLCHAIN_INSTALL_DIR} --rtems-bsps=${RTEMS_BSP_ARCH}/${RTEMS_BSP_NAME}
./waf install
popd

#################################################
# Build Libbsd
pushd ${RTEMS_LIBBSD_SRC_DIR}
sed -i 's#git://git.rtems.org/rtems_waf.git#https://git.rtems.org/rtems_waf#g' .gitmodules
git submodule init
git submodule update rtems_waf
./waf clean
./waf configure --prefix=${RTEMS_LIBBSD_INSTALL_DIR} --rtems=${RTEMS_OS_INSTALL_DIR} --rtems-tools=${RTEMS_TOOLCHAIN_INSTALL_DIR} --rtems-bsps=${RTEMS_BSP_ARCH}/${RTEMS_BSP_NAME} --buildset=buildset/default.ini
./waf install
popd

 
#################################################
## Build LWIP
#pushd ${RTEMS_LWIP_SRC_DIR}
#git submodule init
#git submodule update
#./waf clean
#./waf configure --prefix=${RTEMS_LWIP_INSTALL_DIR} --rtems=${RTEMS_OS_INSTALL_DIR} --rtems-tools=${RTEMS_TOOLCHAIN_INSTALL_DIR} --rtems-bsps=${RTEMS_BSP_ARCH}/${RTEMS_BSP_NAME}
#./waf install
#popd


