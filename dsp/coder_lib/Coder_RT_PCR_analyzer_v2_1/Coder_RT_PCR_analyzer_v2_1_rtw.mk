###########################################################################
## Makefile generated for MATLAB file/project 'Coder_RT_PCR_analyzer_v2_1'. 
## 
## Makefile     : Coder_RT_PCR_analyzer_v2_1_rtw.mk
## Generated on : Mon Mar 18 10:42:52 2019
## MATLAB Coder version: 4.1 (R2018b)
## 
## Build Info:
## 
## Final product: ./Coder_RT_PCR_analyzer_v2_1.dll
## Product type : dynamic-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file
# DEF_FILE                Definition file

PRODUCT_NAME              = Coder_RT_PCR_analyzer_v2_1
MAKEFILE                  = Coder_RT_PCR_analyzer_v2_1_rtw.mk
COMPUTER                  = PCWIN64
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2018b
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2018b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = D:/Dropbox/00_sigmoid_fitting/DSP_subroutines/codegen_storage/dll/Coder_RT_PCR_analyzer_v2_1
ARCH                      = win64
RELATIVE_PATH_TO_ANCHOR   = .
COMPILER_COMMAND_FILE     = Coder_RT_PCR_analyzer_v2_1_rtw_comp.rsp
CMD_FILE                  = Coder_RT_PCR_analyzer_v2_1_rtw.rsp
DEF_FILE                  = $(PRODUCT_NAME).def
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          LCC-win64 v2.4.1 | gmake (64-bit Windows)
# Supported Version(s):    2.4.1
# ToolchainInfo Version:   R2018b
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

SHELL              = cmd
LCC_ROOT           = $(MATLAB_ROOT)/sys/lcc64/lcc64
LCC_BUILDLIB       = $(LCC_ROOT)/bin/buildlib
LCC_LIB            = $(LCC_ROOT)/lib64
MW_EXTERNLIB_DIR   = $(MATLAB_ROOT)/extern/lib/win64/microsoft
MW_LIB_DIR         = $(MATLAB_ROOT)/lib/win64
TOOLCHAIN_INCLUDES = -I$(LCC_ROOT)/include64
MEX_OPTS_FILE      = $(MATLAB_ROOT/rtw/c/tools/lcc-win64.xml

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Lcc-win64 C Compiler
CC_PATH = $(LCC_ROOT)/bin
CC = "$(CC_PATH)/lcc64"

# Linker: Lcc-win64 Linker
LD_PATH = $(LCC_ROOT)/bin
LD = "$(LD_PATH)/lcclnk64"

# Archiver: Lcc-win64 Archiver
AR_PATH = $(LCC_ROOT)/bin
AR = "$(AR_PATH)/lcclib64"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -Fo
LDDEBUG             =
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = /out:
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              =
CFLAGS               = -c -w -noregistrylookup -nodeclspec -I$(LCC_ROOT)/include64
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           = -win64 $(MEX_SRC) $(MEX_OPT_FILE)$(INCLUDES) -outdir $(RELATIVE_PATH_TO_ANCHOR)
MEX_LDFLAGS          = LINKFLAGS="$$LINKFLAGS $(LDFLAGS_ADDITIONAL)"
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -dll -entry LibMain -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL) $(DEF_FILE)

#--------------------
# File extensions
#--------------------

H_EXT               = .h
OBJ_EXT             = .obj
C_EXT               = .c
EXE_EXT             = .exe
SHAREDLIB_EXT       = .dll
STATICLIB_EXT       = .lib
MEX_EXT             = .mexw64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./Coder_RT_PCR_analyzer_v2_1.dll
PRODUCT_TYPE = "dynamic-library"
BUILD_TYPE = "Dynamic Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I./referenced_model_includes -I$(START_DIR) -ID:/Dropbox/00_SIG~1/DSP_SU~1 -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = -DMODEL=Coder_RT_PCR_analyzer_v2_1 -DHAVESTDIO -DUSE_RTMODEL

DEFINES = $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/Coder_RT_PCR_analyzer_v2_1_rtwutil.c $(START_DIR)/Coder_RT_PCR_analyzer_v2_1_initialize.c $(START_DIR)/Coder_RT_PCR_analyzer_v2_1_terminate.c $(START_DIR)/Coder_RT_PCR_analyzer_v2_1.c $(START_DIR)/Coder_DoN.c $(START_DIR)/mean.c $(START_DIR)/combineVectorElements.c $(START_DIR)/diff.c $(START_DIR)/abs.c $(START_DIR)/sum.c $(START_DIR)/Coder_Section_Jumping_v3_DoN.c $(START_DIR)/Coder_jumping_correction6.c $(START_DIR)/Coder_clfy.c $(START_DIR)/isfinite.c $(START_DIR)/sort1.c $(START_DIR)/sortIdx.c $(START_DIR)/Coder_Jump2orNot.c $(START_DIR)/Coder_DistanceBetweenSegs.c $(START_DIR)/power.c $(START_DIR)/Coder_LinearFilter_v2.c $(START_DIR)/Coder_SegMaxDiff.c $(START_DIR)/Coder_DistanceBetweenSegs_v2.c $(START_DIR)/Coder_find_peak_cluster.c $(START_DIR)/Coder_Section_Unimportant_v3.c $(START_DIR)/Coder_fst_fitting.c $(START_DIR)/Coder_Section_QuickAmp_v3.c $(START_DIR)/Coder_scd_fitting.c $(START_DIR)/Coder_Section_QuickAmp_v4.c $(START_DIR)/Coder_min5.c $(START_DIR)/Coder_Indirect_curvature_v3.c $(START_DIR)/Coder_Section_Baseline_v4.c $(START_DIR)/Coder_linear_fitting.c $(START_DIR)/Coder_baseline.c $(START_DIR)/Coder_Section_Baseline_v5.c $(START_DIR)/Coder_local_smoothing.c $(START_DIR)/Coder_Section_Baseline_v6.c $(START_DIR)/Coder_Section_Rp2.c $(START_DIR)/var.c $(START_DIR)/Coder_ABSD_corrector.c $(START_DIR)/Coder_ABSD_corrector_v3.c $(START_DIR)/Coder_LSR2.c $(START_DIR)/Coder_find_cycle.c $(START_DIR)/Coder_SigFit.c $(START_DIR)/Coder_SigFitter_4para.c $(START_DIR)/Coder_sig.c $(START_DIR)/rdivide_helper.c $(START_DIR)/Coder_getjacobian_4para.c $(START_DIR)/Coder_analytical_inverse.c $(START_DIR)/norm.c $(START_DIR)/all.c $(START_DIR)/Coder_classifier.c $(START_DIR)/Coder_dsig.c $(START_DIR)/Coder_new_ABSD.c $(START_DIR)/sign.c $(START_DIR)/mod.c $(START_DIR)/nullAssignment.c $(START_DIR)/Coder_classifier_2nd.c $(START_DIR)/Coder_signal_corrector.c $(START_DIR)/Coder_Indirect_curvature_v2.c $(START_DIR)/Coder_AsymmSigFit_old.c $(START_DIR)/Coder_SigFit_par2.c $(START_DIR)/Coder_SigFitter_2para_part1.c $(START_DIR)/Coder_sig_part1.c $(START_DIR)/Coder_getjacobian_par2.c $(START_DIR)/Coder_SigFit_par3.c $(START_DIR)/Coder_SigFitter_2para_part2.c $(START_DIR)/Coder_sig_part2.c $(START_DIR)/Coder_getjacobian_par3.c $(START_DIR)/dsig.c $(START_DIR)/Coder_multi_amp.c $(START_DIR)/Coder_SigFit_par.c $(START_DIR)/Coder_SigFitter_3para.c $(START_DIR)/Coder_getjacobian_3para.c $(START_DIR)/Coder_invsig.c $(START_DIR)/Coder_AsymmSigFit.c $(START_DIR)/Coder_SingleThresholdCt.c $(START_DIR)/Coder_RT_PCR_analyzer_v2_1_emxutil.c $(START_DIR)/rt_nonfinite.c $(START_DIR)/rtGetNaN.c $(START_DIR)/rtGetInf.c lccstub.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = Coder_RT_PCR_analyzer_v2_1_rtwutil.obj Coder_RT_PCR_analyzer_v2_1_initialize.obj Coder_RT_PCR_analyzer_v2_1_terminate.obj Coder_RT_PCR_analyzer_v2_1.obj Coder_DoN.obj mean.obj combineVectorElements.obj diff.obj abs.obj sum.obj Coder_Section_Jumping_v3_DoN.obj Coder_jumping_correction6.obj Coder_clfy.obj isfinite.obj sort1.obj sortIdx.obj Coder_Jump2orNot.obj Coder_DistanceBetweenSegs.obj power.obj Coder_LinearFilter_v2.obj Coder_SegMaxDiff.obj Coder_DistanceBetweenSegs_v2.obj Coder_find_peak_cluster.obj Coder_Section_Unimportant_v3.obj Coder_fst_fitting.obj Coder_Section_QuickAmp_v3.obj Coder_scd_fitting.obj Coder_Section_QuickAmp_v4.obj Coder_min5.obj Coder_Indirect_curvature_v3.obj Coder_Section_Baseline_v4.obj Coder_linear_fitting.obj Coder_baseline.obj Coder_Section_Baseline_v5.obj Coder_local_smoothing.obj Coder_Section_Baseline_v6.obj Coder_Section_Rp2.obj var.obj Coder_ABSD_corrector.obj Coder_ABSD_corrector_v3.obj Coder_LSR2.obj Coder_find_cycle.obj Coder_SigFit.obj Coder_SigFitter_4para.obj Coder_sig.obj rdivide_helper.obj Coder_getjacobian_4para.obj Coder_analytical_inverse.obj norm.obj all.obj Coder_classifier.obj Coder_dsig.obj Coder_new_ABSD.obj sign.obj mod.obj nullAssignment.obj Coder_classifier_2nd.obj Coder_signal_corrector.obj Coder_Indirect_curvature_v2.obj Coder_AsymmSigFit_old.obj Coder_SigFit_par2.obj Coder_SigFitter_2para_part1.obj Coder_sig_part1.obj Coder_getjacobian_par2.obj Coder_SigFit_par3.obj Coder_SigFitter_2para_part2.obj Coder_sig_part2.obj Coder_getjacobian_par3.obj dsig.obj Coder_multi_amp.obj Coder_SigFit_par.obj Coder_SigFitter_3para.obj Coder_getjacobian_3para.obj Coder_invsig.obj Coder_AsymmSigFit.obj Coder_SingleThresholdCt.obj Coder_RT_PCR_analyzer_v2_1_emxutil.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj lccstub.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : build


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#----------------------------------------
# Create a dynamic library
#----------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating dynamic library "$(PRODUCT)" ..."
	$(LD) $(SHAREDLIB_LDFLAGS) -o $(PRODUCT) @$(CMD_FILE) $(subst /,\,$(subst /,\,$(SYSTEM_LIBS))) $(subst /,\,$(subst /,\,$(TOOLCHAIN_LIBS)))
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : D:/Dropbox/00_sigmoid_fitting/DSP_subroutines/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/sys/lcc64/lcc64/mex/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


