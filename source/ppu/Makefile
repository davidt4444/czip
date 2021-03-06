################################
#       Subdirectories
################################

DIRS := ../spu

###############################
#       Target
###############################

PROGRAM_ppu:= czip

###############################
#       Local Defines
###############################

IMPORTS := ../spu/mypigz15.a -lspe2

INSTALL_DIR = $(SDKBIN)
INSTALL_FILES = $(PROGRAM_ppu)
CC_OPT_LEVEL = -O
CFLAGS =-DMAX_WBITS=13 -DMAX_MEM_LEVEL=5 -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
###############################
#       make.footer
###############################

# --------------------------------------------------------------  
# (C)Copyright 2001,2007,                                         
# International Business Machines Corporation,                    
# Sony Computer Entertainment, Incorporated,                      
# Toshiba Corporation,                                            
#                                                                 
# All Rights Reserved.                                            
# --------------------------------------------------------------  
# PROLOG END TAG zYx                                              

ifndef __MAKE_FOOTER__
__MAKE_FOOTER__		:= 1

ifeq "$(MAKEFILE_LIST)" ""

  ########################################################################
  #			Makefile Version < 3.80
  ########################################################################

  USR_LOCAL		?= /usr/local
  MAKE_3_80		?= $(firstword $(wildcard			\
  				$(USR_LOCAL)/sti/bin/make 		\
  				$(USR_LOCAL)/sti/latest-sdk/bin/make 	\
  				$(USR_LOCAL)/sti/*/bin/make))
  _MAKECMDGOALS		:= $(MAKECMDGOALS)

  $(warning $(MAKE) (v$(MAKE_VERSION)) is too old -- looking for v3.80)

  ifeq "$(MAKE_3_80)" ""
    $(error "make" v3.80 not found)
  else

    rerun_make $(_MAKECMDGOALS):
	@echo "Found $(MAKE_3_80)"
	@echo
	@echo "Automatically restarting make:"
	@echo "    $(MAKE_3_80) $(MAKECMDGOALS)"
	@echo
	@          $(MAKE_3_80) $(MAKECMDGOALS)
  endif

else

# At this point, make.footer is always the last one in MAKEFILE_LIST
make_footer		:= $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))

ifndef CELL_TOP
  CELL_TOP_relative	= $(dir $(make_footer))
  export CELL_TOP	= $(shell cd $(CELL_TOP_relative) && pwd)
endif

ifndef __MAKE_HEADER__
  ifneq "$(MAKEFILE_LIST)" ""
    include $(CELL_TOP)/make.header
  endif
endif

HOST_PROCESSOR	:= $(shell uname -m)

PPU64_PROCESSOR_TYPE := $(shell grep "^cpu" /proc/cpuinfo | grep "Cell Broadband Engine" > /dev/null; if [ $$? = 0 ]; then  echo "Cell"; fi)


########################################################################
#			Default Targets
########################################################################

all: dirs libraries programs misc_ install


########################################################################
#		Systemsim Hardware Simulator Defines
########################################################################

# The systemsim hardware simulator can be installed anywhere, but the default
# is to expect it with everything else.

ifndef SYSTEMSIM_TOP
  SYSTEMSIM_TOP		= /opt/ibm/systemsim-cell
endif

SYSTEMSIM_LINUX		= $(SYSTEMSIM_TOP)/run/cell/linux


########################################################################
#		Common GNU Defines (Host, PPU32, PPU64, SPU)
########################################################################

PPU_PREFIX		= ppu-
PPU32_PREFIX		= ppu32-

ifeq "$(HOST_PROCESSOR)" "ppc64"
  GNU_ROOT		=
  GNU_SYSROOT		=
  GNU_PPU_BINDIR	= /usr/bin
  GNU_SPU_BINDIR	= /usr/bin
  PPU_TOOL_PREFIX	=
  PPU32_TOOL_PREFIX	=
else
  GNU_ROOT		= /opt/cell
  GNU_SYSROOT		= $(GNU_ROOT)/sysroot
  GNU_PPU_BINDIR	= $(GNU_ROOT)/bin
  GNU_SPU_BINDIR	= $(GNU_ROOT)/bin
  PPU_TOOL_PREFIX	= $(PPU_PREFIX)
  PPU32_TOOL_PREFIX	= $(PPU32_PREFIX)
endif

SPU_TOOL_PREFIX		= spu-

PPU32_BINDIR		= $(GNU_PPU_BINDIR)
PPU64_BINDIR		= $(GNU_PPU_BINDIR)
SPU_BINDIR		= $(GNU_SPU_BINDIR)

ifndef CCACHE
  export CCACHE		:= $(shell which ccache 2>/dev/null)
endif


########################################################################
#			Processor Targets
########################################################################

# Set what to build, and what processor to target
# Cross-Compile targets are ppu, ppu64, spu.
# Native targets include i686, ppc64.


#********************
# SPU Targets
#********************

SPU_TARGETS		:= $(strip $(PROGRAM_spu)		\
			   	   $(PROGRAMS_spu)		\
			   	   $(LIBRARY_spu)		\
			   	   $(LIBRARY_embed)		\
			   	   $(LIBRARY_embed64)		\
			   	   $(SHARED_LIBRARY_embed)	\
			   	   $(SHARED_LIBRARY_embed64))

ifdef SPU_TARGETS
  TARGET_PROCESSOR	:= spu
endif


#********************
# 32-bit PPU Targets
#********************

PPU_TARGETS		:= $(strip $(PROGRAM_ppu)		\
			   	   $(PROGRAMS_ppu)		\
			   	   $(LIBRARY_ppu)		\
			   	   $(SHARED_LIBRARY_ppu))

ifdef PPU_TARGETS
  TARGET_PROCESSOR	:= ppu
endif


#********************
# 64-bit PPU Targets
#********************

PPU64_TARGETS		:= $(strip $(PROGRAM_ppu64)		\
			   	   $(PROGRAMS_ppu64)		\
			   	   $(LIBRARY_ppu64)		\
			  	   $(SHARED_LIBRARY_ppu64))

ifdef PPU64_TARGETS
  TARGET_PROCESSOR	:= ppu64
endif


#####################
# Host Targets
#####################


ifndef TARGET_PROCESSOR
  TARGET_PROCESSOR	:= $(HOST_PROCESSOR)
endif

ifeq "$(TARGET_PROCESSOR)" "host"
  TARGET_PROCESSOR	:= $(HOST_PROCESSOR)
endif

ifeq "$(TARGET_PROCESSOR)" "$(HOST_PROCESSOR)"
  __host__		= 1
endif


##########################################################
# SPU Programs and Plugins Embedded in 32-bit PPU Objects
##########################################################

ifdef LIBRARY_embed
  _EMBED		= 1
endif

ifdef SHARED_LIBRARY_embed
  _EMBED		= 1
endif


##########################################################
# SPU Programs and Plugins Embedded in 64-bit PPU Objects
##########################################################

ifdef LIBRARY_embed64
  _EMBED64		= 1
endif

ifdef SHARED_LIBRARY_embed64
  _EMBED64		= 1
endif


#####################
# Generic Targets
#####################

__tp__			= $(TARGET_PROCESSOR)
__$(__tp__)__		= 1

PROGRAM			+= $(PROGRAM_$(__tp__))
PROGRAMS		+= $(PROGRAMS_$(__tp__))
LIBRARY			+= $(LIBRARY_$(__tp__))
SHARED_LIBRARY		+= $(SHARED_LIBRARY_$(__tp__))


#*****************************
# Split the target name from
# its install directory
#*****************************

get_dir		= $(strip $(subst ./,,$(dir $(1))))
get_name	= $(notdir $(1))

ifneq "$(PROGRAM)" ""
  _PROGRAM_dir		    := $(call get_dir, $(PROGRAM))
  _PROGRAM 		    := $(call get_name,$(PROGRAM))
endif

ifneq "$(PROGRAMS)" ""
  _PROGRAMS_dirs	    := $(call get_dir, $(PROGRAMS))
  _PROGRAMS 		    := $(call get_name,$(PROGRAMS))
endif

ifneq "$(LIBRARY)" ""
  _LIBRARY_dir		    := $(call get_dir, $(LIBRARY))
  _LIBRARY 		    := $(call get_name,$(LIBRARY))
endif

ifneq "$(LIBRARY_embed)" ""
  _LIBRARY_embed_dir	    := $(call get_dir, $(LIBRARY_embed))
  _LIBRARY_embed 	    := $(call get_name,$(LIBRARY_embed))
endif

ifneq "$(LIBRARY_embed64)" ""
  _LIBRARY_embed64_dir	    := $(call get_dir, $(LIBRARY_embed64))
  _LIBRARY_embed64	    := $(call get_name,$(LIBRARY_embed64))
endif

ifneq "$(SHARED_LIBRARY)" ""
  _SHARED_LIBRARY_dir	    := $(call get_dir, $(SHARED_LIBRARY))
  _SHARED_LIBRARY	    := $(call get_name,$(SHARED_LIBRARY))
endif

ifneq "$(SHARED_LIBRARY_embed)" ""
  _SHARED_LIBRARY_embed_dir := $(call get_dir, $(SHARED_LIBRARY_embed))
  _SHARED_LIBRARY_embed     := $(call get_name,$(SHARED_LIBRARY_embed))
endif

ifneq "$(SHARED_LIBRARY_embed64)" ""
  _SHARED_LIBRARY_embed64_dir := $(call get_dir, $(SHARED_LIBRARY_embed64))
  _SHARED_LIBRARY_embed64     := $(call get_name,$(SHARED_LIBRARY_embed64))
endif


########################################################################
#			SDK Defines
########################################################################

CBE_SYSROOT		?= $(CELL_TOP)/sysroot
OPTDIR		 	 = /opt/ibm/cell-sdk/prototype
SDK_OPTDIR		 = $(CBE_SYSROOT)$(OPTDIR)

SDKBIN_spu		 = $(SDK_OPTDIR)/spu/bin
SDKBIN_ppu		 = $(SDK_OPTDIR)/bin
SDKBIN_ppu64		 = $(SDK_OPTDIR)/bin

SDKINC_spu		 = $(CBE_SYSROOT)/usr/spu/include
SDKINC_ppu		 = $(CBE_SYSROOT)/usr/include
SDKINC_ppu64		 = $(CBE_SYSROOT)/usr/include

SDKLIB_spu		 = $(CBE_SYSROOT)/usr/spu/lib
SDKLIB_ppu		 = $(CBE_SYSROOT)/usr/lib
SDKLIB_ppu64		 = $(CBE_SYSROOT)/usr/lib64

SDKBIN_host		 = $(CELL_TOP)/host/bin
SDKINC_host		 = $(CELL_TOP)/host/include
SDKLIB_host		 = $(CELL_TOP)/host/lib
SDKBIN_$(HOST_PROCESSOR) = $(SDKBIN_host)
SDKINC_$(HOST_PROCESSOR) = $(SDKINC_host)
SDKLIB_$(HOST_PROCESSOR) = $(SDKLIB_host)

SDKBIN			 = $(SDKBIN_$(__tp__))
SDKINC			 = $(SDKINC_$(__tp__))
SDKLIB			 = $(SDKLIB_$(__tp__))


########################################################################
#			IDL Rules
########################################################################

ifdef IDL_SRC
  IDL_STUB_H		?= stub.h
  IDL_PPU_TARGET	?= ppu/stub_$(IDL_SRC:.idl=.c)
  IDL_SPU_TARGET	?= spu/stub_$(IDL_SRC:.idl=.c)

  IDL_TARGETS		= $(IDL_STUB_H) $(IDL_PPU_TARGET) $(IDL_SPU_TARGET)

  IDL_BIN		= $(SDKBIN_host)

  IDL_SRC_V		= $(filter $(addprefix %,$(IDL_SRC)),$^)

  $(IDL_TARGETS): $(IDL_BIN)/idl $(IDL_SRC)
	$< -f $(IDL_STUB_H) -p $(IDL_PPU_TARGET) -s $(IDL_SPU_TARGET) $(IDL_FLAGS) $(IDL_SRC_V)

  OTHER_TARGETS	+= $(IDL_TARGETS)

  ifdef DIRS
    $(DIRS): $(IDL_TARGETS)
  endif
endif


########################################################################
#			Targets
########################################################################

.PHONY:	all dirs libraries programs misc_ install clean

dirs:	   $(GNU_DIRS) $(DIRS)
programs:  $(PROGRAM) $(PROGRAMS)
libraries: $(LIBRARY)         $(SHARED_LIBRARY)		\
	   $(LIBRARY_embed)   $(SHARED_LIBRARY_embed)	\
	   $(LIBRARY_embed64) $(SHARED_LIBRARY_embed64)
misc_:	   $(OBJS_ONLY) $(HEADERS_ONLY) $(CONFIG_LOG) $(OTHER_TARGETS)

TARGETS		= $(PROGRAM)	     $(PROGRAMS)		\
	  	  $(LIBRARY)	     $(SHARED_LIBRARY)		\
		  $(LIBRARY_embed)   $(SHARED_LIBRARY_embed)	\
		  $(LIBRARY_embed64) $(SHARED_LIBRARY_embed64)	\
	  	  $(OBJS_ONLY) $(HEADERS_ONLY) $(CONFIG_LOG) $(OTHER_TARGETS)
		  
LOCAL_TARGETS	= $(_PROGRAM)	      $(_PROGRAMS)		\
	  	  $(_LIBRARY)	      $(_SHARED_LIBRARY)	\
		  $(_LIBRARY_embed)   $(_SHARED_LIBRARY_embed)	\
		  $(_LIBRARY_embed64) $(_SHARED_LIBRARY_embed64)


########################################################################
#			Compilers
########################################################################

#################
# HOST Compiler
#################


ifdef __host__
  ifeq "$(HOST_COMPILER)" "local"
    TOOL_BINDIR		= /usr/bin
  endif

  TOOL_PREFIX		=
  PATH			:= $(TOOL_BINDIR):$(SDKBIN_host):$(PATH)

  ifeq "$(CC)" "cc"
    CC			:= $(CCACHE) $(TOOL_BINDIR)/gcc
    CXX			:= $(CCACHE) $(TOOL_BINDIR)/g++
  endif
endif


#################
# SPU Compiler
#################

ifdef __spu__
  TOOL_BINDIR		= $(SPU_BINDIR)
  TOOL_PREFIX		= $(SPU_TOOL_PREFIX)
  PATH			:= $(TOOL_BINDIR):$(PATH)

  ifeq "$(SPU_COMPILER)" "spuxlc"
    SPU_COMPILER	:= xlc
  endif

  ifeq "$(SPU_COMPILER)" "xlc"

    _XLC_VERSIONS	:= $(XLC_VERSION)
    _USING_XLC		:= 1

  else

    CC			:= $(CCACHE) $(TOOL_BINDIR)/$(TOOL_PREFIX)gcc
    CXX			:= $(CCACHE) $(TOOL_BINDIR)/$(TOOL_PREFIX)g++

    ifeq "$(wildcard $(CC))" ""
      $(warning $(CC) not found)
      $(error $(SPU_COMPILER) spu tools are not found on this machine)
    endif

  endif

  XLC_PREFIX		:= spu

endif


#################
# PPU Compiler
#################

ifdef __ppu__
  TOOL_BINDIR		= $(PPU32_BINDIR)
  TOOL_PREFIX		= $(PPU32_TOOL_PREFIX)
  PATH			:= $(TOOL_BINDIR):$(PATH)

  ifeq "$(PPU32_COMPILER)" "ppuxlc"
    PPU32_COMPILER	:= xlc
  endif

  ifeq "$(PPU32_COMPILER)" "xlc"
    _XLC_VERSIONS	:= $(XLC_VERSION)
    _USING_XLC		:= 1
  else
    CPPFLAGS_gcc	+= -m32 -mabi=altivec -maltivec

    ifeq "$(SYSTEMSIM_STANDALONE)" "1"
      _INCLUDE     += -I $(SYSTEMSIM_TOP)/include
    endif

    CC	 := $(CCACHE) $(TOOL_BINDIR)/$(PPU32_PREFIX)gcc
    CXX	 := $(CCACHE) $(TOOL_BINDIR)/$(PPU32_PREFIX)g++
  endif

  XLC_PREFIX		:= ppu
endif


#################
# PPU64 Compiler
#################

ifdef __ppu64__
  TOOL_BINDIR		= $(PPU64_BINDIR)
  TOOL_PREFIX		= $(PPU_TOOL_PREFIX)
  PATH			:= $(TOOL_BINDIR):$(PATH)

  ifeq "$(PPU64_COMPILER)" "xlc"
    _XLC_VERSIONS	:= $(XLC_VERSION)
    _USING_XLC		:= 1
    CPPFLAGS_xlc	+= -q64
  else
#   sce

    CC	:= $(CCACHE) $(TOOL_BINDIR)/$(PPU_PREFIX)gcc
    CXX	:= $(CCACHE) $(TOOL_BINDIR)/$(PPU_PREFIX)g++
  endif

  PATH	:= $(TOOL_BINDIR):$(PATH)
  XLC_PREFIX		:= ppu
endif


#################
# XLC Compiler
#################

ifdef _USING_XLC
  ifndef TOBEY_EXPORT_DIR
    # check for xlc in the order specified
    find_xlc = $(shell for i in $(1); do if [ -e $$i/bin/$(2)xlc ]; then echo "$$i"; exit; elif [ -e $$i/ship/bin/$(2)xlc ]; then echo "$$i/ship"; exit; fi; done)

    _XLC_VERSIONS	:= $(subst xlc/,/opt/ibmcmp/xlc/,$(_XLC_VERSIONS))  \
		   	   $(subst xlc/,$(USR_LOCAL)/xlc/,$(_XLC_VERSIONS))

    TOBEY_EXPORT_DIR := $(call find_xlc,$(_XLC_VERSIONS),$(XLC_PREFIX))
    export TOBEY_EXPORT_DIR
  endif

  ifeq "$(TOBEY_EXPORT_DIR)" ""
    $(error Error: No $(XLC_PREFIX)xlc found.  $(CELL_TOP)/make.env specified these choices: $(addsuffix /bin/$(XLC_PREFIX)xlc,$(_XLC_VERSIONS)))
  else
    CC		:= $(TOBEY_EXPORT_DIR)/bin/$(XLC_PREFIX)xlc
    CXX		:= $(TOBEY_EXPORT_DIR)/bin/$(XLC_PREFIX)xlc++
    PATH	:= $(TOBEY_EXPORT_DIR)/bin:$(PATH)
  endif
endif


########################################################################
#			Other Tools
########################################################################

PATH	 := .:$(PATH)

AS	 := $(TOOL_BINDIR)/$(TOOL_PREFIX)as
LD	 := $(TOOL_BINDIR)/$(TOOL_PREFIX)ld

ifdef __spu__
  # spu-ar doesn't work correctly
  AR	 := $(GNU_PPU_BINDIR)/$(PPU_TOOL_PREFIX)ar
else
  ifdef __ppu__
    AR		:= $(TOOL_BINDIR)/$(PPU_TOOL_PREFIX)ar
  else
    ifdef __ppu64__
      AR	:= $(TOOL_BINDIR)/$(PPU_TOOL_PREFIX)ar
    else
      # host
      AR	:= $(TOOL_BINDIR)/ar
    endif
  endif
endif

EMBEDSPU32 := $(GNU_PPU_BINDIR)/ppu-embedspu -m32
EMBEDSPU64 := $(GNU_PPU_BINDIR)/ppu-embedspu -m64

OBJCOPY	 := $(TOOL_BINDIR)/$(TOOL_PREFIX)objcopy
OBJDUMP	 := $(TOOL_BINDIR)/$(TOOL_PREFIX)objdump
RANLIB	 := $(TOOL_BINDIR)/$(TOOL_PREFIX)ranlib
READELF	 := $(TOOL_BINDIR)/$(TOOL_PREFIX)readelf

AWK	 := awk
CP	 := cp -pf
FLEX	 := flex
GZIP	 := gzip -f
INDENT	 := indent -bad -bap -bbb -bli0 -cli4 -i4 -l80 -nip -pcs -psl -sob
MKDIR	 := mkdir -p
MV	 := mv
PERL	 := perl
RM	 := rm -f
SED	 := sed
SORT	 := sort
TAR	 := tar
TAR_GZIP := $(TAR) -z
TAR_BZIP := $(TAR) -j
YACC	 := yacc

REMOVE_EMPTY_DIRECTORY := rmdir -p --ignore-fail-on-non-empty


# Default to allowing a .i file to be compiled (i.e. #line are not added).
# If you want to see the files that the code comes from (i.e. add the #line)
# then set this value to 0
#
WANT_TO_COMPILE_I_FILE	?= 1


########################################################################
#			VPATH
########################################################################

empty		:=
space		:= $(empty) $(empty)

_VPATH		:= $(subst $(space),:,$(strip $(VPATH)))
VPATH		:= $(_VPATH)


########################################################################
#			Include Directories
########################################################################

_INCLUDE	:= -I.

ifdef VPATH
  _INCLUDE	+= -I $(subst :, -I ,$(VPATH))
endif

_INCLUDE	+= $(INCLUDE)

ifdef __x86__
  # Nvidia has updated OpenGL files -- use those if installed
  NVIDIA_INCLUDE := $(wildcard /usr/share/doc/NVIDIA_GLX-1.0/include)
  ifneq "$(NVIDIA_INCLUDE)" ""
    _INCLUDE	+= -I $(NVIDIA_INCLUDE)
  endif
endif

_INCLUDE	+= -I $(SDKINC)

PREV_DIR_1	= $(dir $(CURDIR))
PREV_DIR_2	= $(dir $(PREV_DIR_1:%/=%))


########################################################################
#			Preprocessor Flags
########################################################################
ifeq "$(SYSTEMSIM_STANDALONE)" "1"
  TEXT_ADDRESS ?= 0x1000
endif



ifdef _USING_XLC
  #----------------------------------
  # XLC-Specific Preprocessor Flags
  #----------------------------------
  # CPPFLAGS_xlc		- User-defined in Makefile for xlc only
  # -qcpluscmt			- Allow // as a comment
  # -M				- Create a dependency file while compiling
  # -ma				- Generate inline calls to the "alloca" function

  COMPILER_CPPFLAGS	 = $(CPPFLAGS_xlc)		\
  			   -qcpluscmt -M -ma
  COMPILER_LDFLAGS	 = $(LDFLAGS_xlc)

  ifdef __spu__
    VECTOR_FLAG		 = -qinclude=spu_intrinsics.h
  endif

  ifdef __ppu__
    VECTOR_FLAG 	 = -qaltivec -qenablevmx
  
    ifeq "$(SYSTEMSIM_STANDALONE)" "1"
      COMPILER_LDFLAGS          += -qnocrt -qstaticlink -Wl,-Ttext=$(TEXT_ADDRESS)
    endif

  endif
else
  #----------------------------------
  # GCC-Specific Preprocessor Flags
  #----------------------------------
  # CPPFLAGS_gcc		- User-defined in Makefile for gcc only
  # -W				- Enable extra warnings
  # -Wall			- Enable all preprocessor warnings
  # -Winline			- Warn when inlined function cannot be inlined

  COMPILER_CPPFLAGS	 = $(CPPFLAGS_gcc)
  COMPILER_LDFLAGS	 = $(LDFLAGS_gcc)
  WARNING_FLAGS		?= -W -Wall -Winline

  ifdef __spu__
    # spu main() has different parameters
    WARNING_FLAGS	+= -Wno-main
    VECTOR_FLAG		 = -include spu_intrinsics.h
  endif

  ifdef __ppu__
    VECTOR_FLAG		 = -include altivec.h
    
    ifeq "$(SYSTEMSIM_STANDALONE)" "1"
      COMPILER_LDFLAGS          += -nostartfiles -static -Wl,-Ttext=$(TEXT_ADDRESS)
    endif
  endif
endif

COMMON_CPPFLAGS	= $(NO_STDINC)		\
		  $(USE_VPATH)		\
		  $(WARNING_FLAGS)	\
		  $(COMPILER_CPPFLAGS)

_SPPFLAGS	= $(CPPFLAGS_$(@:.o=))	\
		  $(CPPFLAGS_$(@:.s=))	\
		  $(CPPFLAGS_$(@:.i=))	\
		  $(CPPFLAGS_$(@:.d=))	\
		  $(CPPFLAGS)		\
		  $(COMMON_CPPFLAGS)	\
		  $(_INCLUDE)

_CPPFLAGS	= $(_SPPFLAGS)		\
		  $(VECTOR_FLAG)

ifdef _USING_XLC
  ifdef __spu__
    # The following are all debug flags
    # _CPPFLAGS	+= -qxflag=plstfe:plstopt:plst3:bundle:hbrlate:ngunroll
  endif
endif


########################################################################
#			Compiler Flags
########################################################################


ifdef _USING_XLC
  COMPILER_CFLAGS	 = $(CFLAGS_xlc)
  CFLAGS_so		?= -qpic
  NOSTARTFILES		:= -qnocrt
  NOSTDLIB		:= -qnolib

  ifdef __spu__
    CC_OPT_LEVEL_DEBUG  := -g -qnoopt
  endif
else
  COMPILER_CFLAGS	:= $(CFLAGS_gcc)
  CFLAGS_so		?= -fpic
  NOSTARTFILES		:= -nostartfiles
  NOSTDLIB		:= -nostdlib
endif

ifdef _SHARED_LIBRARY
  COMPILER_CFLAGS	+= $(CFLAGS_so)
endif

ifndef CC_OPT_LEVEL_DEBUG
  CC_OPT_LEVEL_DEBUG	:= -g -O0
endif

ifndef CC_OPT_LEVEL
  ifdef _USING_XLC
   CC_OPT_LEVEL		:= -O3
  else
   CC_OPT_LEVEL		:= -O3
  endif		
endif

COMMON_CFLAGS	:= $(CC_OPT_LEVEL) $(COMPILER_CFLAGS)

_CFLAGS_	 = $(CFLAGS_$(@:.o=))	\
		   $(CFLAGS)		\
		   $(COMMON_CFLAGS)

ifdef _USING_XLC
  _CFLAGS	 = $(_CFLAGS_:-fno-inline=-qnoinline)
else
  _CFLAGS	 = $(_CFLAGS_:-qnoinline=-fno-inline)
endif

COMMON_CXXFLAGS	:= $(CC_OPT_LEVEL) $(COMPILER_CFLAGS)

_CXXFLAGS_	 = $(CXXFLAGS_$(@:.o=))	\
		   $(CXXFLAGS)		\
		   $(COMMON_CXXFLAGS)

ifdef _USING_XLC
  _CXXFLAGS	 = $(_CXXFLAGS_:-fno-inline=-qnoinline)
else
  _CXXFLAGS	 = $(_CXXFLAGS_:-qnoinline=-fno-inline)
endif

ifdef __spu__
  ifndef _USING_XLC
    _CXXFLAGS	+= -fno-exceptions -fno-rtti
  endif
endif


########################################################################
#			Assembly Flags
########################################################################

COMMON_ASFLAGS	= 

ifdef __ppu__
  ifeq "$(PPU32_COMPILER)" "cell"
    COMMON_ASFLAGS	+= -a32
  endif
endif

_ASFLAGS	= $(ASFLAGS_$(@:.o=))	\
		  $(ASFLAGS)		\
		  $(COMMON_ASFLAGS)	\
		  $(_INCLUDE)


########################################################################
#			Imported Libraries
########################################################################

ifdef IMPORTS
  _IMPORTS	:= $(filter-out -l%,$(IMPORTS))
  SYS_LIBS	+= $(filter -l%,$(IMPORTS))
endif

ifdef _PROGRAMS
  # This is in addition to IMPORTS, which applies to all PROGRAMS
  PER_FILE_IMPORTS   := $(foreach prog,$(_PROGRAMS),$(IMPORTS_$(prog)))
  _PER_FILE_IMPORTS  := $(filter-out -l%,$(PER_FILE_IMPORTS))
  PER_FILE_SYS_LIBS  := $(filter -l%,$(PER_FILE_IMPORTS))
endif


########################################################################
#			Link Flags
########################################################################

ifndef _USING_XLC
  ifdef STRIP_PROGRAM
    STRIP_FLAG		:= -Wl,-s
  endif

  ifdef MAPFILE
    _MAP_FLAG		:= -Wl,-Map,$(MAPFILE)
  endif
endif

COMMON_LDFLAGS		= $(STRIP_FLAG) $(_MAP_FLAG)

ifneq "$(SYS_LIBS)$(PER_FILE_SYS_LIBS)" ""
  COMMON_LDFLAGS	+= -L$(SDKLIB_$(__tp__))

  ifdef __host__
    ifneq "$(filter -lX%,$(SYS_LIBS))" ""
      MULTI_OS_DIR	= $(shell $(CC) -print-multi-os-directory 2>/dev/null)
      COMMON_LDFLAGS	+= -L/usr/X11R6/lib/$(MULTI_OS_DIR)
    endif
  endif
endif

ifdef __spu__
  # Until we have an SPU loader capable of performing runtime relocations
  # as needed (feature 4758), we will collapse the text and data segments on
  # all SPU executables by default.
  COMMON_LDFLAGS	+= -Wl,-N
endif

ifdef START_FILE
  COMMON_LDFLAGS	+= $(NOSTARTFILES)
endif

ifdef __spu__
  SHARED_LDFLAGS	:= -shared -soname=$(_SHARED_LIBRARY_embed)
endif

ifdef __ppu__
  SHARED_LDFLAGS	:= -shared -soname=$(_SHARED_LIBRARY) -m elf32ppc

  ifdef _USING_XLC
    COMMON_LDFLAGS	+= -Wl,-m,elf32ppc
  else
    COMMON_LDFLAGS	+= -m32 -Wl,-m,elf32ppc
  endif
  COMMON_LDFLAGS	+= -R$(OPTDIR)/sysroot/usr/lib
endif

ifdef __ppu64__
  SHARED_LDFLAGS	:= -shared -soname=$(_SHARED_LIBRARY)
  ifdef _USING_XLC
    COMMON_LDFLAGS	+= -q64
  endif
  COMMON_LDFLAGS	+= -R$(OPTDIR)/sysroot/usr/lib
endif

ifdef __host__
  SHARED_LDFLAGS	:= -shared -soname=$(_SHARED_LIBRARY)
endif


_LDFLAGS	= $(LDFLAGS_$@)		\
		  $(LDFLAGS)		\
		  $(COMPILER_LDFLAGS)	\
		  $(COMMON_LDFLAGS)


########################################################################
#			Source Rules
########################################################################

SRC_BUILT_HERE = $(C_BUILT_HERE) $(S_BUILT_HERE) $(H_BUILT_HERE)


########################################################################
#			Object Rules
########################################################################

ifneq "$(PROGRAM)$(LIBRARY)$(_SHARED_LIBRARY)" ""
  ifndef OBJS
    IMPLICIT_OBJS	:= 1
  endif
endif

ifdef VPATH
  all_src = $(sort $(notdir $(foreach path,. $(subst :, ,$(VPATH)),$(wildcard $(path)/*.$(1)))))
else
  all_src = $(wildcard *.$(1))
endif

CXX_SRC1 = $(call all_src,C)
CXX_SRC2 = $(call all_src,cpp)
CXX_SRC3 = $(call all_src,cc)
CXX_SRC4 = $(call all_src,cxx)

CXX_OBJS = $(strip $(CXX_SRC1:.C=.o)  $(CXX_SRC2:.cpp=.o) \
		   $(CXX_SRC3:.cc=.o) $(CXX_SRC4:.cxx=.o))

ifdef IMPLICIT_OBJS
  # if no OBJS specified, assume what they are
  # For a single programs, assume all .c .s source files will be used

  C_SRC		:= $(call all_src,c) $(C_BUILT_HERE)
  S_SRC		:= $(call all_src,S)
  AS_SRC	:= $(call all_src,s)

  C_OBJS	:= $(C_SRC:.c=.o)
  S_OBJS	:= $(S_SRC:.S=.o)
  AS_OBJS	:= $(AS_SRC:.s=.o)

  OBJS		:= $(strip $(C_OBJS) $(S_OBJS) $(CXX_OBJS) $(AS_OBJS))
endif

ifdef _PROGRAMS
  # Objects can be explicitly declared as OBJS_program, where program is
  # the name of one of the programs.  If no objects are explictly declared,
  # then it is assumed that program is created from program.o.

  OBJS		:= $(foreach prog,$(_PROGRAMS),$(if $(OBJS_$(prog)),$(OBJS_$(prog)),$(prog).o))
endif

ifdef _EMBED
  EMBED_OBJS	= $(patsubst %,%-embed.o,$(_PROGRAM) $(_PROGRAMS))
  EMBED_OBJS_V	= $(filter $(addprefix %/,$(EMBED_OBJS)) $(EMBED_OBJS),$^)
endif

ifdef _EMBED64
  EMBED64_OBJS	 = $(patsubst %,%-embed64.o,$(_PROGRAM) $(_PROGRAMS))
  EMBED64_OBJS_V = $(filter $(addprefix %/,$(EMBED64_OBJS)) $(EMBED64_OBJS),$^)
endif

ifdef OBJS
  # This includes the full path of each object (needed for clone trees & VPATH)
  OBJS_V	= $(filter $(addprefix %/,$(OBJS)) $(OBJS),$^)
endif

ifdef START_FILE
  START_FILE_V	= $(filter $(addprefix %/,$(START_FILE)) $(START_FILE),$^)
endif

########################################################################
#			Implicit Rules
########################################################################

#*************************************
#    Create Objects (.o)
#*************************************

#----------
#    C
#----------
%.o: %.c
	$(CC) $(_CPPFLAGS) $(_CFLAGS) -c $<

#----------
#   C++
#----------
%.o: %.C
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) -c $<

%.o: %.cpp
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) -c $<

%.o: %.cc
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) -c $<

%.o: %.cxx
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) -c $<

#----------
# Assembly
#----------
%.o: %.s
	$(AS) $(_ASFLAGS) -o $@ $<

%.o: %.S
	$(CPP) $(_SPPFLAGS) $< | $(AS) $(ASFLAGS) -o $@


#*************************************
#   Create Assembly Source (.s)
#*************************************

ifdef __spu__
  ifeq "$(SPU_TIMING)" "1"
      ASM_RULE_2 = ; /opt/ibm/cell-sdk/prototype/bin/spu_timing -running-count $@
  endif
endif

#----------
#    C
#----------
%.s: %.c
	$(CC) $(_CPPFLAGS) $(_CFLAGS) -S $< $(ASM_RULE_2)

#----------
#   C++
#----------
%.s: %.C
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) -S $< $(ASM_RULE_2)

%.s: %.cpp
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) -S $< $(ASM_RULE_2)

%.s: %.cc
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) -S $< $(ASM_RULE_2)

%.s: %.cxx
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) -S $< $(ASM_RULE_2)

#----------
# Assembly
#----------

ifdef _USING_XLC
%.s: %.S
	$(CPP) $(_SPPFLAGS) $< > $@
else
%.s: %.S
	$(CPP) $(_SPPFLAGS) -o $@ $<
endif

#*************************************
#   Create Preprocessed Source (.i)
#*************************************

ifdef _USING_XLC
  _IFLAGS = -P
else
  _IFLAGS = -E -P -o $@
endif

#----------
#    C
#----------
%.i: %.c
	$(CC) $(_CPPFLAGS) $(_CFLAGS) $(_IFLAGS) $<

#----------
#   C++
#----------
%.i: %.C
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) $(_IFLAGS) $<

%.i: %.cpp
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) $(_IFLAGS) $<

%.i: %.cc
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) $(_IFLAGS) $<

%.i: %.cxx
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) $(_IFLAGS) $<

#----------
# Assembly
#----------
%.i: %.S
	$(CC) $(_SPPFLAGS) $(_CFLAGS) $(_IFLAGS) $<


#*********************************
#   Create Listing Files (.lst)
#*********************************

ifdef _USING_XLC
  _LSTFLAGS	= -qsource -qshowinc -qlist -qlistopt -c
else
  _LSTFLAGS	= -E -o $@
endif

#----------
#    C
#----------
%.lst: %.c
	$(CC) $(_CPPFLAGS) $(_CFLAGS) $(_LSTFLAGS) $<

#----------
#   C++
#----------
%.lst: %.C
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) $(_LSTFLAGS) $<

%.lst: %.cpp
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) $(_LSTFLAGS) $<

%.lst: %.cc
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) $(_LSTFLAGS) $<

%.lst: %.cxx
	$(CXX) $(_CPPFLAGS) $(_CXXFLAGS) $(_LSTFLAGS) $<

#----------
# Assembly
#----------
%.lst: %.S
	$(CXX) $(_SPPFLAGS) $(_CXXFLAGS) $(_LSTFLAGS) $<


########################################################################
#			Subdirectories
########################################################################

# dummydir:

ifdef DIRS
.PHONY: $(DIRS)

$(DIRS):
	@if [ -r $@/Makefile ]; then $(MAKE) -C $@ $(MAKECMDGOALS); fi
endif

ifdef GNU_DIRS
.PHONY: $(GNU_DIRS)
$(GNU_DIRS):
	@if [ -r $@/Makefile.sti ];					\
	then								\
	    echo;							\
	    echo "***************************************************"; \
	    echo "*";							\
	    echo "* [`date +\"%b %d %T\"`] Configuring gnu directory $(notdir $(CURDIR))/$@";\
	    echo "*";							\
	    echo "***************************************************"; \
	    echo;							\
	    $(MAKE) -C $@ -f Makefile.sti;				\
	fi;								\
	if [ -r $@/Makefile ];						\
	then								\
	    echo;							\
	    echo "***************************************************"; \
	    echo "*";							\
	    echo "* [`date +\"%b %d %T\"`] Building gnu directory $(notdir $(CURDIR))/$@";\
	    echo "*";							\
	    echo "***************************************************"; \
	    echo;							\
	    $(MAKE) -C $@ all install;					\
	fi
endif


########################################################################
#			Library Rules
########################################################################

ifdef _LIBRARY
$(_LIBRARY): $(SRC_BUILT_HERE) $(OBJS) $(_IMPORTS)
	$(AR) -qcs $@ $(OBJS_V) $(_IMPORTS)
endif


########################################################################
#			Embedded Library Rules
########################################################################

ifdef _LIBRARY_embed
$(_LIBRARY_embed): $(EMBED_OBJS)
	$(AR) -qcs $@ $(EMBED_OBJS_V)
endif

ifdef _LIBRARY_embed64
$(_LIBRARY_embed64): $(EMBED64_OBJS)
	$(AR) -qcs $@ $(EMBED64_OBJS_V)
endif

ifdef EMBED_OBJS
# Embed into a 32-bit PPU obj
$(EMBED_OBJS): %-embed.o: %
	$(EMBEDSPU32) $(subst -,_,$<) $< $@
endif

ifdef EMBED64_OBJS
# Embed spu obj into a 64-bit PPU obj
$(EMBED64_OBJS): %-embed64.o: %
	$(EMBEDSPU64) $(subst -,_,$<) $< $@
endif


########################################################################
#			Executable Program Rules
########################################################################

ifeq "$(CXX_OBJS)" ""
  _LD = $(CC)
else
  _LD = $(CXX)
endif

ifdef _PROGRAM
$(_PROGRAM): $(SRC_BUILT_HERE) $(OBJS) $(_IMPORTS) $(START_FILE)
	$(_LD) -o $@ $(START_FILE_V) $(OBJS_V) $(_LDFLAGS) $(_IMPORTS) $(SYS_LIBS)
endif

ifdef _PROGRAMS
#The % doesn't work in the $(OBJS_%) dependency:
#$(_PROGRAMS): %: $(SRC_BUILT_HERE) $(OBJS_%) $(_IMPORTS)
$(_PROGRAMS): $(SRC_BUILT_HERE) $(OBJS) $(_IMPORTS) $(_PER_FILE_IMPORTS) $(START_FILE)
	@if [ "$(OBJS_$@)" != "" ];					\
	then								\
	    objs="$(filter $(addprefix %/,$(OBJS_$@)) $(OBJS_$@),$^)";	\
	else								\
	    objs="$(filter $(addprefix %/,$@.o) $@.o,$^)";		\
	fi;								\
	per_file_syslibs="$(filter -l%,$(IMPORTS_$@))";			\
	per_file_imports="$(filter $(addprefix %/,$(IMPORTS_$@)) $(IMPORTS_$@),$^)";\
	imports="$(_IMPORTS) $$per_file_imports $$per_file_syslibs";	\
	echo "$(_LD) -o $@ $(START_FILE_V) $$objs $(_LDFLAGS) $$imports $(SYS_LIBS)";\
	      $(_LD) -o $@ $(START_FILE_V) $$objs $(_LDFLAGS) $$imports $(SYS_LIBS)
endif


########################################################################
#			Shared Library Rules
########################################################################

ifdef _SHARED_LIBRARY
$(_SHARED_LIBRARY): $(SRC_BUILT_HERE) $(OBJS)
	$(LD) -o $@ $(SHARED_LDFLAGS) $(OBJS_V)
endif

ifdef _SHARED_LIBRARY_embed
$(_SHARED_LIBRARY_embed): $(SRC_BUILT_HERE) $(EMBED_OBJS)
	$(subst spu,ppu,$(subst $(SPU_TOOL_PREFIX),$(PPU32_TOOL_PREFIX),$(LD))) -o $@ $(SHARED_LDFLAGS) $(EMBED_OBJS_V)
endif

ifdef _SHARED_LIBRARY_embed64
$(_SHARED_LIBRARY_embed64): $(SRC_BUILT_HERE) $(EMBED64_OBJS)
	$(subst spu,ppu,$(subst $(SPU_TOOL_PREFIX),$(PPU_TOOL_PREFIX),$(LD))) -o $@ $(SHARED_LDFLAGS) $(EMBED64_OBJS_V)
endif


########################################################################
#			Install Rules
########################################################################
.SECONDEXPANSION:

ifdef _PROGRAM_dir
$(PROGRAM): $(_PROGRAM)
	@if [ "$(@D)" = "" ]; then echo "Error in PROGRAM definition (use = instead of :=)"; exit 1; fi
	@$(MKDIR) $(@D)
	$(CP) $< $@
endif

ifdef _PROGRAMS_dirs
$(PROGRAMS): $$(@F)
	@if [ "$(@D)" = "" ]; then echo "Error in PROGRAMS definition (use = instead of :=)"; exit 1; fi
	@$(MKDIR) $(@D)
	$(CP) $< $@
endif

ifdef _LIBRARY_dir
$(LIBRARY): $(_LIBRARY)
	@if [ "$(@D)" = "" ]; then echo "Error in LIBRARY definition (use = instead of :=)"; exit 1; fi
	@$(MKDIR) $(@D)
	$(CP) $< $@
endif

ifdef _LIBRARY_embed_dir
$(LIBRARY_embed): $(_LIBRARY_embed)
	@if [ "$(@D)" = "" ]; then echo "Error in LIBRARY_embed definition (use = instead of :=)"; exit 1; fi
	@$(MKDIR) $(@D)
	$(CP) $< $@
endif

ifdef _LIBRARY_embed64_dir
$(LIBRARY_embed64): $(_LIBRARY_embed64)
	@if [ "$(@D)" = "" ]; then echo "Error in LIBRARY_embed64 definition (use = instead of :=)"; exit 1; fi
	@$(MKDIR) $(@D)
	$(CP) $< $@
endif

ifdef _SHARED_LIBRARY_dir
$(SHARED_LIBRARY): $(_SHARED_LIBRARY)
	@if [ "$(@D)" = "" ]; then echo "Error in SHARED_LIBRARY definition (use = instead of :=)"; exit 1; fi
	@$(MKDIR) $(@D)
	$(CP) $< $@
endif

ifdef SHARED_LIBRARY_embed_dir
$(SHARED_LIBRARY_embed): $(_SHARED_LIBRARY_embed)
	@if [ "$(@D)" = "" ]; then echo "Error in SHARED_LIBRARY_embed definition (use = instead of :=)"; exit 1; fi
	@$(MKDIR) $(@D)
	$(CP) $< $@
endif

ifdef SHARED_LIBRARY_embed64_dir
$(SHARED_LIBRARY_embed64): $(_SHARED_LIBRARY_embed64)
	@if [ "$(@D)" = "" ]; then echo "Error in SHARED_LIBRARY_embed64 definition (use = instead of :=)"; exit 1; fi
	@$(MKDIR) $(@D)
	$(CP) $< $@
endif


ifdef INSTALL_DIR
  _INSTALL_FILES = $(foreach dir,$(INSTALL_DIR),$(addprefix $(dir)/,$(INSTALL_FILES)))
else
  _INSTALL_FILES = $(INSTALL_FILES)
endif

ifdef TARGET_INSTALL_DIR
  _INSTALL_FILES += $(addprefix $(TARGET_INSTALL_DIR)/,$(TARGETS))
endif

ifneq "$(_INSTALL_FILES)" ""
$(_INSTALL_FILES): $$(@F)
	@$(MKDIR) $(@D)
	$(CP) $< $@
endif

install: $(_INSTALL_FILES)


########################################################################
#			Cleanup Rules
########################################################################

cleaninstall:
ifdef _INSTALL_FILES
	@$(RM) $(_INSTALL_FILES)
endif

cleanlocal:

cleanmap:
ifdef MAPFILE
	@$(RM) $(MAPFILE)
endif

cleantobey:
ifdef _USING_XLC
	@$(RM) *_tobey.c *.lst *.i *.i.tmp *o\$$1.s
endif

cleanobj:
	@$(RM) $(TARGETPATH_)*.o

cleand:
	@$(RM) $(TARGETPATH_)*.d

cleanlib:
	@$(RM) $(LIBRARY)$(_LIBRARY)					\
	       $(SHARED_LIBRARY)$(_SHARED_LIBRARY)			\
	       $(LIBRARY_embed)$(_LIBRARY_embed)			\
	       $(LIBRARY_embed64)$(_LIBRARY_embed64)			\
	       $(SHARED_LIBRARY_embed) $(_SHARED_LIBRARY_embed)		\
	       $(SHARED_LIBRARY_embed64) $(_SHARED_LIBRARY_embed64)

cleanexe:
	@$(RM) $(PROGRAM) $(_PROGRAM) $(PROGRAMS) $(_PROGRAMS)

cleantargets:
	@$(RM) -r $(LOCAL_TARGETS) $(OTHER_TARGETS)

cleandir: cleanobj cleand cleanlib cleanexe cleantargets cleanmap cleantobey cleanlocal
	@$(RM) out $(SRC_BUILT_HERE)

.PHONY: cleansubdirs

cleansubdirs:
ifdef DIRS
	@for i in $(DIRS); do \
	  if [ -e $$i/Makefile ]; then $(MAKE) -C $$i clean; fi \
	done
endif
ifdef GNU_DIRS
	for i in $(GNU_DIRS); do \
	  if [ -e $$i/Makefile.sti ]; then $(MAKE) -C $$i -f Makefile.sti clean; fi \
	done
endif

clean: cleandir cleansubdirs cleaninstall


########################################################################
#			Dependency Rules 
########################################################################

ifdef OBJS
  _OBJS		= $(OBJS)
endif

ifdef OBJS_ONLY
  _OBJS		+= $(OBJS_ONLY)
endif

ifdef _OBJS
  $(_OBJS): Makefile

  ifndef _USING_XLC
    $(_OBJS): %.o: %.d
  endif
endif

MACROIZE = -e 's, $(CBE_SYSROOT), $$(CBE_SYSROOT),g'		\
	   -e 's,$(TOBEY_EXPORT_DIR),$$(TOBEY_EXPORT_DIR),g'	\
	   -e 's,$(GNU_SYSROOT),$$(GNU_SYSROOT),g'		\
	   -e 's,$(CELL_TOP),$$(CELL_TOP),g'

CONVERT_U = -M $(_CPPFLAGS) $< | \
	    sed -e 's/\($*\)\.o[ :]*/\1.o \1.i \1.lst $@ : /g'	\
	    $(MACROIZE) > $@; [ -s $@ ] || $(RM) $@

ifdef _USING_XLC

# xlc handles .d automagically with the -M option while compiling

else

%.d: %.c
	@set -e; $(CC) $(CONVERT_U)

%.d: %.C
	@set -e; $(CXX) $(CONVERT_U)

%.d: %.cpp
	@set -e; $(CXX) $(CONVERT_U)

%.d: %.cc
	@set -e; $(CXX) $(CONVERT_U)

%.d: %.cxx
	@set -e; $(CXX) $(CONVERT_U)

%.d: %.S
	@set -e; $(CC) $(CONVERT_U)

%.d: %.s
	@touch $@

endif


########################################################################
#			Build Info
########################################################################

# Specify a target that will print out the key variables.  This is
# useful for debugging a Makefile.


listenv:
	@echo
	@echo "Directory Configuration:"
	@echo "------------------------"
	@echo "    Building on:      $(HOST_PROCESSOR) $(shell if [ -r /etc/redhat-release ]; then cat /etc/redhat-release; fi)"
	@echo "    Target Processor: $(TARGET_PROCESSOR)"
	@echo "    Makefiles:        $(strip $(MAKEFILE_LIST))"
	@echo
	@echo "    CELL_TOP       = $(CELL_TOP)"
	@echo "    VPATH          = $(VPATH)"
	@echo "    PATH           = $(PATH)"
	@echo 
	@echo "    CBE_SYSROOT    = $(CBE_SYSROOT)"
	@echo "    OPTDIR	  = $(OPTDIR)"
	@echo "    SDK_OPTDIR	  = $(SDK_OPTDIR)"
	@echo 
	@echo "    SDKBIN	  = $(SDKBIN)"
	@echo "    SDKINC	  = $(SDKINC)"
	@echo "    SDKLIB	  = $(SDKLIB)"
	@echo 
	@echo "    Files:"
	@echo "    ------"
	@echo "    Targets        = $(strip $(TARGETS))"
	@echo "    Objects        = $(strip $(OBJS))"
	@echo "    Embed Objects  = $(strip $(EMBED_OBJS))"
	@echo "    Embed64 Objs   = $(strip $(EMBED64_OBJS))"
	@echo "    C++ Objects    = $(strip $(CXX_OBJS))"
	@echo "    Install Files  = $(strip $(_INSTALL_FILES))"
	@echo
	@echo "    Build Tools:"
	@echo "    ------------"
	@echo "    C Preprocessor = $(CPP)"
	@echo "    C Compiler     = `which $(CC)`"
	@echo "    C++ Compiler   = `which $(CXX)`"
	@echo "    Assembler      = `which $(AS)`"
	@echo "    Linker         = `which $(LD)`"
	@echo
	@echo "    Default Flags"
	@echo "    -------------"
	@echo "    CPPFLAGS       = $(strip $(_CPPFLAGS))"
	@echo "    CXXFLAGS       = $(strip $(_CXXFLAGS))"
	@echo "    CFLAGS         = $(strip $(_CFLAGS))"
	@echo "    ASFLAGS        = $(strip $(_ASFLAGS))"
	@echo "    LDFLAGS        = $(strip $(_LDFLAGS))"
	@echo "    SYS_LIBS       = $(strip $(SYS_LIBS))"
	@echo "    IMPORTS        = $(strip $(_IMPORTS))"

$(CELL_TOP)/make.header $(CELL_TOP)/make.env $(make_footer) Makefile Makefile.sti: ;


########################################################################
#			Dependencies
########################################################################

ifdef _OBJS
  ifneq "$(MAKECMDGOALS)" "listenv"
  ifneq "$(MAKECMDGOALS)" "clean"
    DEPEND_FILES := $(foreach file,$(_OBJS:.o=.d),$(wildcard $(file)))
    ifneq "$(DEPEND_FILES)" ""
      include $(DEPEND_FILES)
    endif
  endif
  endif
endif

endif # MAKEFILE_LIST
endif # __MAKE_FOOTER__
