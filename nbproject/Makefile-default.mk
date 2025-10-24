#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/CompactInstrument.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/CompactInstrument.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/main.c src/Ports.c src/ISR.c src/T1.c src/SRC.c src/I2C.c src/EMC1701_Driver.c src/SPI.c src/OLED_Driver.c src/AsmFunctions.s src/DisplayLayout.c src/ButtonHandler.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/Ports.o ${OBJECTDIR}/src/ISR.o ${OBJECTDIR}/src/T1.o ${OBJECTDIR}/src/SRC.o ${OBJECTDIR}/src/I2C.o ${OBJECTDIR}/src/EMC1701_Driver.o ${OBJECTDIR}/src/SPI.o ${OBJECTDIR}/src/OLED_Driver.o ${OBJECTDIR}/src/AsmFunctions.o ${OBJECTDIR}/src/DisplayLayout.o ${OBJECTDIR}/src/ButtonHandler.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/Ports.o.d ${OBJECTDIR}/src/ISR.o.d ${OBJECTDIR}/src/T1.o.d ${OBJECTDIR}/src/SRC.o.d ${OBJECTDIR}/src/I2C.o.d ${OBJECTDIR}/src/EMC1701_Driver.o.d ${OBJECTDIR}/src/SPI.o.d ${OBJECTDIR}/src/OLED_Driver.o.d ${OBJECTDIR}/src/AsmFunctions.o.d ${OBJECTDIR}/src/DisplayLayout.o.d ${OBJECTDIR}/src/ButtonHandler.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/Ports.o ${OBJECTDIR}/src/ISR.o ${OBJECTDIR}/src/T1.o ${OBJECTDIR}/src/SRC.o ${OBJECTDIR}/src/I2C.o ${OBJECTDIR}/src/EMC1701_Driver.o ${OBJECTDIR}/src/SPI.o ${OBJECTDIR}/src/OLED_Driver.o ${OBJECTDIR}/src/AsmFunctions.o ${OBJECTDIR}/src/DisplayLayout.o ${OBJECTDIR}/src/ButtonHandler.o

# Source Files
SOURCEFILES=src/main.c src/Ports.c src/ISR.c src/T1.c src/SRC.c src/I2C.c src/EMC1701_Driver.c src/SPI.c src/OLED_Driver.c src/AsmFunctions.s src/DisplayLayout.c src/ButtonHandler.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/CompactInstrument.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP32GS502
MP_LINKER_FILE_OPTION=,--script=p33EP32GS502.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/d1ea9a1ff07036543342f833ed97d77f32079c95 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/Ports.o: src/Ports.c  .generated_files/flags/default/59cc29008d2315d206196fc53611faa175c5f63e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Ports.o.d 
	@${RM} ${OBJECTDIR}/src/Ports.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Ports.c  -o ${OBJECTDIR}/src/Ports.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/Ports.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/ISR.o: src/ISR.c  .generated_files/flags/default/648356f16eebc672f065a262c7cdfa755812bd31 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ISR.o.d 
	@${RM} ${OBJECTDIR}/src/ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ISR.c  -o ${OBJECTDIR}/src/ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/T1.o: src/T1.c  .generated_files/flags/default/af90c0565c43d193c9d070e6e73662d4606c23f3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/T1.o.d 
	@${RM} ${OBJECTDIR}/src/T1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/T1.c  -o ${OBJECTDIR}/src/T1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/T1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/SRC.o: src/SRC.c  .generated_files/flags/default/f1081c99ee0ce90ae41fe3217d251ade89a47e9a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SRC.o.d 
	@${RM} ${OBJECTDIR}/src/SRC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SRC.c  -o ${OBJECTDIR}/src/SRC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/SRC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/I2C.o: src/I2C.c  .generated_files/flags/default/e23aa17e86277b4d491b7d00dd23c3ad5ce3e60a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/I2C.o.d 
	@${RM} ${OBJECTDIR}/src/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C.c  -o ${OBJECTDIR}/src/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/I2C.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/EMC1701_Driver.o: src/EMC1701_Driver.c  .generated_files/flags/default/aa3c25ff866dc0cdf67391960934915bafd56e85 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/EMC1701_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/EMC1701_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EMC1701_Driver.c  -o ${OBJECTDIR}/src/EMC1701_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EMC1701_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/SPI.o: src/SPI.c  .generated_files/flags/default/4a05bb2037f0cc9c06003c958dd8722b6d6a0bb9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SPI.o.d 
	@${RM} ${OBJECTDIR}/src/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SPI.c  -o ${OBJECTDIR}/src/SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/SPI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/OLED_Driver.o: src/OLED_Driver.c  .generated_files/flags/default/c2130a7d5f906bb05a985ca62bd1f54f14623f6e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/OLED_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/OLED_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/OLED_Driver.c  -o ${OBJECTDIR}/src/OLED_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/OLED_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/DisplayLayout.o: src/DisplayLayout.c  .generated_files/flags/default/5033996d70c4a63db95b0d54b355d167e84c99a3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/DisplayLayout.o.d 
	@${RM} ${OBJECTDIR}/src/DisplayLayout.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/DisplayLayout.c  -o ${OBJECTDIR}/src/DisplayLayout.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/DisplayLayout.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/ButtonHandler.o: src/ButtonHandler.c  .generated_files/flags/default/177f4f757957cb51fc907430b1452cffd9c312c0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ButtonHandler.o.d 
	@${RM} ${OBJECTDIR}/src/ButtonHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ButtonHandler.c  -o ${OBJECTDIR}/src/ButtonHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/ButtonHandler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/28ed5cbcc8b8eda3144f589bec324369aa5e3366 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/Ports.o: src/Ports.c  .generated_files/flags/default/ea19281e234710462a1582e4bd1be0a45fb1ebc4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Ports.o.d 
	@${RM} ${OBJECTDIR}/src/Ports.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Ports.c  -o ${OBJECTDIR}/src/Ports.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/Ports.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/ISR.o: src/ISR.c  .generated_files/flags/default/1d71d4f196561396bf1000080669921da0fb8e35 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ISR.o.d 
	@${RM} ${OBJECTDIR}/src/ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ISR.c  -o ${OBJECTDIR}/src/ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/ISR.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/T1.o: src/T1.c  .generated_files/flags/default/8b53c2441d8cdaeaf5ccebc544d5245cf25ecbfa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/T1.o.d 
	@${RM} ${OBJECTDIR}/src/T1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/T1.c  -o ${OBJECTDIR}/src/T1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/T1.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/SRC.o: src/SRC.c  .generated_files/flags/default/adfadeabe9533a2dd80b0af67bbe96c6a615ec09 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SRC.o.d 
	@${RM} ${OBJECTDIR}/src/SRC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SRC.c  -o ${OBJECTDIR}/src/SRC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/SRC.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/I2C.o: src/I2C.c  .generated_files/flags/default/a927806781ef876da0752d0cf953391597fe9ea1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/I2C.o.d 
	@${RM} ${OBJECTDIR}/src/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C.c  -o ${OBJECTDIR}/src/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/I2C.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/EMC1701_Driver.o: src/EMC1701_Driver.c  .generated_files/flags/default/4a5ad06c24d2318bb7d1cd9078b9b19003e176b0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/EMC1701_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/EMC1701_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EMC1701_Driver.c  -o ${OBJECTDIR}/src/EMC1701_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EMC1701_Driver.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/SPI.o: src/SPI.c  .generated_files/flags/default/8de312ca6a041722b0221f3ea3eb133d6518291b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SPI.o.d 
	@${RM} ${OBJECTDIR}/src/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SPI.c  -o ${OBJECTDIR}/src/SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/SPI.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/OLED_Driver.o: src/OLED_Driver.c  .generated_files/flags/default/ff9bd4e6533c0d732849a83d16c9e252e814c764 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/OLED_Driver.o.d 
	@${RM} ${OBJECTDIR}/src/OLED_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/OLED_Driver.c  -o ${OBJECTDIR}/src/OLED_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/OLED_Driver.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/DisplayLayout.o: src/DisplayLayout.c  .generated_files/flags/default/3ee75505c09f5756466aba5817de00350a9e1762 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/DisplayLayout.o.d 
	@${RM} ${OBJECTDIR}/src/DisplayLayout.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/DisplayLayout.c  -o ${OBJECTDIR}/src/DisplayLayout.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/DisplayLayout.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/ButtonHandler.o: src/ButtonHandler.c  .generated_files/flags/default/5b07ccccb344b89c48f424a14a64bb9bf6ac34a1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ButtonHandler.o.d 
	@${RM} ${OBJECTDIR}/src/ButtonHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ButtonHandler.c  -o ${OBJECTDIR}/src/ButtonHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/ButtonHandler.o.d"      -mno-eds-warn  -g -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/AsmFunctions.o: src/AsmFunctions.s  .generated_files/flags/default/72a9f47aaa2192631396d0d7eaf0fa3fd548adc5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/AsmFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/AsmFunctions.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/AsmFunctions.s  -o ${OBJECTDIR}/src/AsmFunctions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/src/AsmFunctions.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/src/AsmFunctions.o: src/AsmFunctions.s  .generated_files/flags/default/3521747e8ced7e3432d2a6e613df05e3a5546a91 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/AsmFunctions.o.d 
	@${RM} ${OBJECTDIR}/src/AsmFunctions.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/AsmFunctions.s  -o ${OBJECTDIR}/src/AsmFunctions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/src/AsmFunctions.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/CompactInstrument.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/CompactInstrument.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/CompactInstrument.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/CompactInstrument.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -save-temps=obj -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/CompactInstrument.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
