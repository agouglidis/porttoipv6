#!/bin/bash

#****************************************************************************
#
# Install script for PortToIPv6 
# Copyright (C) 2005 - 2017 Antonios Gouglidis, agouglidis@gmail.com
# http://porttoipv6.sourceforge.net
#
#****************************************************************************

# Get enviroment
SUFFIX=""
PF_ENV=`uname`
if [ ${PF_ENV:0:6} = "CYGWIN" ]; then
    SUFFIX=".exe"
fi

# DEBUG can be set to YES to include debugging info, or NO otherwise
DEBUG_MODE="YES"
# TINYXML_USE_STL can be used to turn on STL support. NO, then STL
# will not be used. YES will include the STL files.
TINYXML_USE_STL="YES"

CXX="g++"
FLEX="flex++ -p"

DEBUG_MODE_CXXFLAGS="-Wall -Wno-format -g -DDEBUG"
RELEASE_MODE_CXXFLAGS="-Wall -Wno-unknown-pragmas -Wno-format -O3"
DEBUG_MODE_FXXFLAGS="-d"
RELEASE_MODE_FXXFLAGS=""

if [ ${DEBUG_MODE} = "YES" ]; then
   CXXFLAGS=${DEBUG_MODE_CXXFLAGS}
   FXXFLAGS=${DEBUG_MODE_FXXFLAGS}
else
   CXXFLAGS=${RELEASE_MODE_CXXFLAGS}
   FXXFLAGS=${RELEASE_MODE_FXXFLAGS}
fi


#****************************************************************************
# Preprocessor directives
#****************************************************************************
if [ $TINYXML_USE_STL = "YES" ]; then
  DEFS=" -DTIXML_USE_STL"
else
  DEFS=""
fi

#****************************************************************************
# Makefile code common to all platforms
#****************************************************************************

CXXFLAGS_PF=$CXXFLAGS 
CXXFLAGS=$CXXFLAGS" "$DEFS

#****************************************************************************
# Functions
#****************************************************************************
output=""
ProcCheck()
{
	if [ $? -eq 0 ];then
		echo "${output}: OK"
	else
		echo "${output}: ERROR"
		exit 1	
	fi	
}


#****************************************************************************

# Build tinyXml
cd tinyxml
echo "Make TinyXml..."
make
output="make"
ProcCheck
cd ..

#****************************************************************************

echo "Building mos..."

cd IPv4Scanner

output="${FLEX} ${FXXFLAGS} mos.flex"
${FLEX} ${FXXFLAGS} mos.flex
ProcCheck

output="${CXX} -c ${CXXFLAGS} lex.yy.cc -o mos.o"
${CXX} -c ${CXXFLAGS} lex.yy.cc -o mos.o
ProcCheck

output="${CXX} ${CXXFLAGS_PF} -o mos ../tinyxml/tinyxml.o ../tinyxml/tinyxmlparser.o mos.o ../tinyxml/tinyxmlerror.o ../tinyxml/tinystr.o"
${CXX} ${CXXFLAGS_PF} -o mos ../tinyxml/tinyxml.o ../tinyxml/tinyxmlparser.o mos.o ../tinyxml/tinyxmlerror.o ../tinyxml/tinystr.o
ProcCheck

chmod +x mos

echo "Creating ipv4scanner..."
output="./mos < IPv4Scanner.mos > ipv4scanner.flex"
./mos${SUFFIX} < IPv4Scanner.mos > ipv4scanner.flex
ProcCheck

echo "Building ipv4scanner..."
output="${FLEX} ${FXXFLAGS} ipv4scanner.flex"
${FLEX} ${FXXFLAGS} ipv4scanner.flex
ProcCheck

output="${CXX} ${CXXFLAGS_PF} lex.yy.cc -o ipv4scanner"
${CXX} ${CXXFLAGS_PF} lex.yy.cc -o ipv4scanner
ProcCheck

chmod +x ipv4scanner

cd ../IPv6cg

echo "Creating ipv6cg..."
output="../IPv4Scanner/mos < ipv6cg.mos > ipv6cg.cc"
../IPv4Scanner/mos${SUFFIX} < ipv6cg.mos > ipv6cg.cc
ProcCheck

echo "Building ipv6cg..."
output="${CXX} -c ${CXXFLAGS} ipv6cg.cc -o ipv6cg.o"
${CXX} -c ${CXXFLAGS} ipv6cg.cc -o ipv6cg.o
ProcCheck

output="${CXX} ${CXXFLAGS_PF} -o ipv6cg ../tinyxml/tinyxml.o ../tinyxml/tinyxmlparser.o ipv6cg.o ../tinyxml/tinyxmlerror.o ../tinyxml/tinystr.o"
${CXX} ${CXXFLAGS_PF} -o ipv6cg ../tinyxml/tinyxml.o ../tinyxml/tinyxmlparser.o ipv6cg.o ../tinyxml/tinyxmlerror.o ../tinyxml/tinystr.o
ProcCheck

chmod +x ipv6cg
