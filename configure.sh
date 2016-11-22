#!/bin/bash

#default options
VERBOSE="false"
DEBUG="false"
RELEASE="false"
MAKE="false"
TEST="false"
CLEAN="false"
CLEAN_ALL="false"
AUTO="false"
GLOBAL_INSTALL="false"
WINDOWS="false"

while [[ $# > 0 ]]
do
  key="$1"

  case $key in
    -v | --verbose)
      VERBOSE="true"
      ;;
    -d | --debug)
      DEBUG="true"
      ;;
    -m | --make)
      MAKE="true"
      ;;
    -t | --test)
      TEST="true"
      ;;
    -c | --clean)
      CLEAN="true"
      ;;
    -ca | --clean-all)
      CLEAN="true"
      CLEAN_ALL="true"
      ;;
    --release)
      RELEASE="true"
      ;;
    --auto)
      AUTO="true"
      ;;
    --global-install)
      GLOBAL_INSTALL="true"
      ;;
    --windows)
      WINDOWS="true"
      ;;
    *)
      # Unknown option
      ;;
  esac
  shift
done

# Create the version information file
./gen_version.sh

# Check to see if we have a CI provided branch value
if [[ -z $CI_BUILD_REF_NAME ]]
then
  BRANCH="$(git symbolic-ref HEAD 2> /dev/null || echo "(unnamed branch)")" # detached HEAD
  BRANCH=${BRANCH##refs/heads/}
else
  BRANCH="${CI_BUILD_REF_NAME##*/}"
fi

if [[ $BRANCH == release* ]] || [[ $BRANCH == "releases" ]]
then
  ON_RELEASE_BRANCH="true"
else
  ON_RELEASE_BRANCH="false"
fi

if [[ "true" == $AUTO ]]
then
  if [[ "false" == $ON_RELEASE_BRANCH ]]
  then
    DEBUG=true
  fi
  CLEAN_ALL=true
  CLEAN=true
  TEST=true
  MAKE=false
  GLOBAL_INSTALL=true
fi


#if [[ "true" == $CLEAN_ALL ]]
#then
#  git submodule deinit .
#fi

# Initialize submodules
#git submodule init
#git submodule update

# Build cmake options string
OPTIONS=""
if [[ "true" == $VERBOSE ]]
then
  OPTIONS="$OPTIONS -DCMAKE_VERBOSE_MAKEFILE=ON"
fi

if [[ "true" == $DEBUG ]]
then
  OPTIONS="$OPTIONS -DCMAKE_BUILD_TYPE=Debug"
else
  OPTIONS="$OPTIONS -DCMAKE_BUILD_TYPE=Release"
fi

if [[ "true" == $RELEASE ]]
then
  OPTIONS="$OPTIONS -DDEVELOPMENT_BUILD=False"
elif [[ "true" == $DEBUG ]]
then
  OPTIONS="$OPTIONS -DDEVELOPMENT_BUILD=True"
elif [[ "true" == $ON_RELEASE_BRANCH ]]
then
  OPTIONS="$OPTIONS -DDEVELOPMENT_BUILD=False"
else
  OPTIONS="$OPTIONS -DDEVELOPMENT_BUILD=True"
fi

if [[ "true" == $TEST ]]
then
  OPTIONS="$OPTIONS -DTESTING_ENABLED:BOOLEAN=true"
fi

if [[ "true" == $GLOBAL_INSTALL ]] && [[ "false" == $WINDOWS ]]
then
  OPTIONS="$OPTIONS -DCMAKE_INSTALL_PREFIX=/usr/local"
elif [[ "true" == $WINDOWS ]]
then
  OPTIONS="$OPTIONS -DCMAKE_INSTALL_PREFIX=`pwd`/windows"
else
  OPTIONS="$OPTIONS -DCMAKE_INSTALL_PREFIX=`pwd`/linux"
fi

if [[ "true" == $WINDOWS ]]
then
  OPTIONS="$OPTIONS -G Ninja"
fi

if [[ "true" == $CLEAN ]]
then
  rm -rf build
  rm -rf target
fi

mkdir -p build
cd build
echo "cmake $OPTIONS .."
cmake $OPTIONS ..

if [[ "true" == $MAKE ]]
then
  make 
  make install
  if [[ "true" == $TEST ]]
  then
    make test
  fi
fi

