#!/bin/bash

CXX_TOOLCHAIN=/usr/bin/g++
GCC_TOOLCHAIN=/usr/bin/gcc

JOBS=2
BUILD_MODE="Release"
BUILD_TESTS="OFF"
BUILD_EXAMPLES="OFF"
DEBUG_POSTFIX=""
MEMORY_DEBUG=""

BSROOT=$(realpath "..")
# ORIGIN_DIR=${BSROOT}/cmake-x86-gnu-linux
INSTALL_DIR=${BSROOT}/bluesky/install_dir
# BUILD_DIR=${BSROOT}/build_dir
WORK_SPACE=${BSROOT}/workspace

help() {
   echo "Usage:"
   echo "   -c    Configure for build mode: release/debug."
   echo "   -t    Configure for build tests: on/off."
   echo "   -e    Configure for build examples: on/off"
   echo "./build_script.sh -c=release -t=on -e=off"
   exit 1
}

until [[ -z "$1" ]]; do
   if [[ "$1" == "--" ]]; then
         break;
   elif [[ "$1" =~ ^-c=* ]]; then
      option=${1:3}
      if [[ $option == "debug" ]]; then
         BUILD_MODE="Debug"
         DEBUG_POSTFIX="d"
         MEMORY_DEBUG="-dbg"
         echo "BUILD MODE:"
         echo $BUILD_MODE
      fi
   elif [[ "$1" =~ ^-t=.* ]]; then
      option=${1:3} # get data of $1 from position 3
      if [[ $option == "on" ]]; then
         BUILD_TESTS="ON"
         echo $BUILD_TESTS
      fi
   elif [[ "$1" =~ ^-e=* ]]; then
      option=${1:3}
      if [[ $option == "off" ]]; then
         BUILD_EXAMPLES="OFF"
      fi
   else
      help
      exit 0
   fi
   shift
done


if [[ -d ${INSTALL_DIR} ]]; then
   rm -r ${INSTALL_DIR}
fi
mkdir -p ${INSTALL_DIR}

if [[ -d ${WORK_SPACE} ]]; then
   rm -r ${WORK_SPACE}/*
   #statements
fi
mkdir -p ${WORK_SPACE}
cd ${WORK_SPACE}

cmake \
   -D CMAKE_COMPILER=${CXX_TOOLCHAIN} \
   -D CMAKE_INSTALL_DIR=${INSTALL_DIR} \
   -D BUILD_TYPE=${BUILD_MODE} \
   -D BUILD_TESTS=${BUILD_TESTS} \
   ${BSROOT}/bluesky
cmake --build . --target install