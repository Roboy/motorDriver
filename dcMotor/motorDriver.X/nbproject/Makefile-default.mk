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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../dcMotorV3/motorDriver.X/source/DEEEmulation.c ../../dcMotorV3/motorDriver.X/source/dma.c ../../dcMotorV3/motorDriver.X/source/initIO.c ../../dcMotorV3/motorDriver.X/source/qei.c ../../dcMotorV3/motorDriver.X/source/timers.c ../../dcMotorV3/motorDriver.X/source/pwm.c ../../dcMotorV3/motorDriver.X/source/can.c ../../dcMotorV3/motorDriver.X/source/main.c ../../dcMotorV3/motorDriver.X/source/spiFunctions.c ../../dcMotorV3/motorDriver.X/source/motorControl.c ../../dcMotorV3/motorDriver.X/source/serialPortFunctions.c ../../dcMotorV3/motorDriver.X/source/adc.c source/main.c source/initIO.c source/timers.c source/motorControl.c source/pwm.c source/spiFunctions.c source/qei.c source/adc.c source/can.c source/dma.c source/DEEEmulation.c source/FlashOperations.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/221278881/DEEEmulation.o ${OBJECTDIR}/_ext/221278881/dma.o ${OBJECTDIR}/_ext/221278881/initIO.o ${OBJECTDIR}/_ext/221278881/qei.o ${OBJECTDIR}/_ext/221278881/timers.o ${OBJECTDIR}/_ext/221278881/pwm.o ${OBJECTDIR}/_ext/221278881/can.o ${OBJECTDIR}/_ext/221278881/main.o ${OBJECTDIR}/_ext/221278881/spiFunctions.o ${OBJECTDIR}/_ext/221278881/motorControl.o ${OBJECTDIR}/_ext/221278881/serialPortFunctions.o ${OBJECTDIR}/_ext/221278881/adc.o ${OBJECTDIR}/source/main.o ${OBJECTDIR}/source/initIO.o ${OBJECTDIR}/source/timers.o ${OBJECTDIR}/source/motorControl.o ${OBJECTDIR}/source/pwm.o ${OBJECTDIR}/source/spiFunctions.o ${OBJECTDIR}/source/qei.o ${OBJECTDIR}/source/adc.o ${OBJECTDIR}/source/can.o ${OBJECTDIR}/source/dma.o ${OBJECTDIR}/source/DEEEmulation.o ${OBJECTDIR}/source/FlashOperations.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/221278881/DEEEmulation.o.d ${OBJECTDIR}/_ext/221278881/dma.o.d ${OBJECTDIR}/_ext/221278881/initIO.o.d ${OBJECTDIR}/_ext/221278881/qei.o.d ${OBJECTDIR}/_ext/221278881/timers.o.d ${OBJECTDIR}/_ext/221278881/pwm.o.d ${OBJECTDIR}/_ext/221278881/can.o.d ${OBJECTDIR}/_ext/221278881/main.o.d ${OBJECTDIR}/_ext/221278881/spiFunctions.o.d ${OBJECTDIR}/_ext/221278881/motorControl.o.d ${OBJECTDIR}/_ext/221278881/serialPortFunctions.o.d ${OBJECTDIR}/_ext/221278881/adc.o.d ${OBJECTDIR}/source/main.o.d ${OBJECTDIR}/source/initIO.o.d ${OBJECTDIR}/source/timers.o.d ${OBJECTDIR}/source/motorControl.o.d ${OBJECTDIR}/source/pwm.o.d ${OBJECTDIR}/source/spiFunctions.o.d ${OBJECTDIR}/source/qei.o.d ${OBJECTDIR}/source/adc.o.d ${OBJECTDIR}/source/can.o.d ${OBJECTDIR}/source/dma.o.d ${OBJECTDIR}/source/DEEEmulation.o.d ${OBJECTDIR}/source/FlashOperations.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/221278881/DEEEmulation.o ${OBJECTDIR}/_ext/221278881/dma.o ${OBJECTDIR}/_ext/221278881/initIO.o ${OBJECTDIR}/_ext/221278881/qei.o ${OBJECTDIR}/_ext/221278881/timers.o ${OBJECTDIR}/_ext/221278881/pwm.o ${OBJECTDIR}/_ext/221278881/can.o ${OBJECTDIR}/_ext/221278881/main.o ${OBJECTDIR}/_ext/221278881/spiFunctions.o ${OBJECTDIR}/_ext/221278881/motorControl.o ${OBJECTDIR}/_ext/221278881/serialPortFunctions.o ${OBJECTDIR}/_ext/221278881/adc.o ${OBJECTDIR}/source/main.o ${OBJECTDIR}/source/initIO.o ${OBJECTDIR}/source/timers.o ${OBJECTDIR}/source/motorControl.o ${OBJECTDIR}/source/pwm.o ${OBJECTDIR}/source/spiFunctions.o ${OBJECTDIR}/source/qei.o ${OBJECTDIR}/source/adc.o ${OBJECTDIR}/source/can.o ${OBJECTDIR}/source/dma.o ${OBJECTDIR}/source/DEEEmulation.o ${OBJECTDIR}/source/FlashOperations.o

# Source Files
SOURCEFILES=../../dcMotorV3/motorDriver.X/source/DEEEmulation.c ../../dcMotorV3/motorDriver.X/source/dma.c ../../dcMotorV3/motorDriver.X/source/initIO.c ../../dcMotorV3/motorDriver.X/source/qei.c ../../dcMotorV3/motorDriver.X/source/timers.c ../../dcMotorV3/motorDriver.X/source/pwm.c ../../dcMotorV3/motorDriver.X/source/can.c ../../dcMotorV3/motorDriver.X/source/main.c ../../dcMotorV3/motorDriver.X/source/spiFunctions.c ../../dcMotorV3/motorDriver.X/source/motorControl.c ../../dcMotorV3/motorDriver.X/source/serialPortFunctions.c ../../dcMotorV3/motorDriver.X/source/adc.c source/main.c source/initIO.c source/timers.c source/motorControl.c source/pwm.c source/spiFunctions.c source/qei.c source/adc.c source/can.c source/dma.c source/DEEEmulation.c source/FlashOperations.s


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC802
MP_LINKER_FILE_OPTION=,--script=../../dcMotorV3/motorDriver.X/source/DEEEmulation.c
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/221278881/DEEEmulation.o: ../../dcMotorV3/motorDriver.X/source/DEEEmulation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/DEEEmulation.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/DEEEmulation.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/DEEEmulation.c  -o ${OBJECTDIR}/_ext/221278881/DEEEmulation.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/DEEEmulation.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/DEEEmulation.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/dma.o: ../../dcMotorV3/motorDriver.X/source/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/dma.c  -o ${OBJECTDIR}/_ext/221278881/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/dma.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/initIO.o: ../../dcMotorV3/motorDriver.X/source/initIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/initIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/initIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/initIO.c  -o ${OBJECTDIR}/_ext/221278881/initIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/initIO.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/initIO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/qei.o: ../../dcMotorV3/motorDriver.X/source/qei.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/qei.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/qei.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/qei.c  -o ${OBJECTDIR}/_ext/221278881/qei.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/qei.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/qei.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/timers.o: ../../dcMotorV3/motorDriver.X/source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/timers.c  -o ${OBJECTDIR}/_ext/221278881/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/pwm.o: ../../dcMotorV3/motorDriver.X/source/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/pwm.c  -o ${OBJECTDIR}/_ext/221278881/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/can.o: ../../dcMotorV3/motorDriver.X/source/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/can.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/can.c  -o ${OBJECTDIR}/_ext/221278881/can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/can.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/main.o: ../../dcMotorV3/motorDriver.X/source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/main.c  -o ${OBJECTDIR}/_ext/221278881/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/spiFunctions.o: ../../dcMotorV3/motorDriver.X/source/spiFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/spiFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/spiFunctions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/spiFunctions.c  -o ${OBJECTDIR}/_ext/221278881/spiFunctions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/spiFunctions.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/spiFunctions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/motorControl.o: ../../dcMotorV3/motorDriver.X/source/motorControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/motorControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/motorControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/motorControl.c  -o ${OBJECTDIR}/_ext/221278881/motorControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/motorControl.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/motorControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/serialPortFunctions.o: ../../dcMotorV3/motorDriver.X/source/serialPortFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/serialPortFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/serialPortFunctions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/serialPortFunctions.c  -o ${OBJECTDIR}/_ext/221278881/serialPortFunctions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/serialPortFunctions.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/serialPortFunctions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/adc.o: ../../dcMotorV3/motorDriver.X/source/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/adc.c  -o ${OBJECTDIR}/_ext/221278881/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/main.o: source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/main.o.d 
	@${RM} ${OBJECTDIR}/source/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/main.c  -o ${OBJECTDIR}/source/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/initIO.o: source/initIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/initIO.o.d 
	@${RM} ${OBJECTDIR}/source/initIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/initIO.c  -o ${OBJECTDIR}/source/initIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/initIO.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/initIO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/timers.o: source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/timers.o.d 
	@${RM} ${OBJECTDIR}/source/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/timers.c  -o ${OBJECTDIR}/source/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/motorControl.o: source/motorControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/motorControl.o.d 
	@${RM} ${OBJECTDIR}/source/motorControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/motorControl.c  -o ${OBJECTDIR}/source/motorControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/motorControl.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/motorControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/pwm.o: source/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/pwm.o.d 
	@${RM} ${OBJECTDIR}/source/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/pwm.c  -o ${OBJECTDIR}/source/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/spiFunctions.o: source/spiFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/spiFunctions.o.d 
	@${RM} ${OBJECTDIR}/source/spiFunctions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/spiFunctions.c  -o ${OBJECTDIR}/source/spiFunctions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/spiFunctions.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/spiFunctions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/qei.o: source/qei.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/qei.o.d 
	@${RM} ${OBJECTDIR}/source/qei.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/qei.c  -o ${OBJECTDIR}/source/qei.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/qei.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/qei.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/adc.o: source/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/adc.o.d 
	@${RM} ${OBJECTDIR}/source/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/adc.c  -o ${OBJECTDIR}/source/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/can.o: source/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/can.o.d 
	@${RM} ${OBJECTDIR}/source/can.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/can.c  -o ${OBJECTDIR}/source/can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/can.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/dma.o: source/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/dma.o.d 
	@${RM} ${OBJECTDIR}/source/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/dma.c  -o ${OBJECTDIR}/source/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/dma.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/DEEEmulation.o: source/DEEEmulation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/DEEEmulation.o.d 
	@${RM} ${OBJECTDIR}/source/DEEEmulation.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/DEEEmulation.c  -o ${OBJECTDIR}/source/DEEEmulation.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/DEEEmulation.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/DEEEmulation.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/221278881/DEEEmulation.o: ../../dcMotorV3/motorDriver.X/source/DEEEmulation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/DEEEmulation.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/DEEEmulation.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/DEEEmulation.c  -o ${OBJECTDIR}/_ext/221278881/DEEEmulation.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/DEEEmulation.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/DEEEmulation.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/dma.o: ../../dcMotorV3/motorDriver.X/source/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/dma.c  -o ${OBJECTDIR}/_ext/221278881/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/dma.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/initIO.o: ../../dcMotorV3/motorDriver.X/source/initIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/initIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/initIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/initIO.c  -o ${OBJECTDIR}/_ext/221278881/initIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/initIO.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/initIO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/qei.o: ../../dcMotorV3/motorDriver.X/source/qei.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/qei.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/qei.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/qei.c  -o ${OBJECTDIR}/_ext/221278881/qei.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/qei.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/qei.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/timers.o: ../../dcMotorV3/motorDriver.X/source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/timers.c  -o ${OBJECTDIR}/_ext/221278881/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/timers.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/pwm.o: ../../dcMotorV3/motorDriver.X/source/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/pwm.c  -o ${OBJECTDIR}/_ext/221278881/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/pwm.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/can.o: ../../dcMotorV3/motorDriver.X/source/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/can.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/can.c  -o ${OBJECTDIR}/_ext/221278881/can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/can.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/main.o: ../../dcMotorV3/motorDriver.X/source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/main.c  -o ${OBJECTDIR}/_ext/221278881/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/spiFunctions.o: ../../dcMotorV3/motorDriver.X/source/spiFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/spiFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/spiFunctions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/spiFunctions.c  -o ${OBJECTDIR}/_ext/221278881/spiFunctions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/spiFunctions.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/spiFunctions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/motorControl.o: ../../dcMotorV3/motorDriver.X/source/motorControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/motorControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/motorControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/motorControl.c  -o ${OBJECTDIR}/_ext/221278881/motorControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/motorControl.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/motorControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/serialPortFunctions.o: ../../dcMotorV3/motorDriver.X/source/serialPortFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/serialPortFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/serialPortFunctions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/serialPortFunctions.c  -o ${OBJECTDIR}/_ext/221278881/serialPortFunctions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/serialPortFunctions.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/serialPortFunctions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221278881/adc.o: ../../dcMotorV3/motorDriver.X/source/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/221278881" 
	@${RM} ${OBJECTDIR}/_ext/221278881/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/221278881/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../dcMotorV3/motorDriver.X/source/adc.c  -o ${OBJECTDIR}/_ext/221278881/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221278881/adc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/221278881/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/main.o: source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/main.o.d 
	@${RM} ${OBJECTDIR}/source/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/main.c  -o ${OBJECTDIR}/source/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/initIO.o: source/initIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/initIO.o.d 
	@${RM} ${OBJECTDIR}/source/initIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/initIO.c  -o ${OBJECTDIR}/source/initIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/initIO.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/initIO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/timers.o: source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/timers.o.d 
	@${RM} ${OBJECTDIR}/source/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/timers.c  -o ${OBJECTDIR}/source/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/timers.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/motorControl.o: source/motorControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/motorControl.o.d 
	@${RM} ${OBJECTDIR}/source/motorControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/motorControl.c  -o ${OBJECTDIR}/source/motorControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/motorControl.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/motorControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/pwm.o: source/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/pwm.o.d 
	@${RM} ${OBJECTDIR}/source/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/pwm.c  -o ${OBJECTDIR}/source/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/pwm.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/spiFunctions.o: source/spiFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/spiFunctions.o.d 
	@${RM} ${OBJECTDIR}/source/spiFunctions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/spiFunctions.c  -o ${OBJECTDIR}/source/spiFunctions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/spiFunctions.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/spiFunctions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/qei.o: source/qei.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/qei.o.d 
	@${RM} ${OBJECTDIR}/source/qei.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/qei.c  -o ${OBJECTDIR}/source/qei.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/qei.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/qei.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/adc.o: source/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/adc.o.d 
	@${RM} ${OBJECTDIR}/source/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/adc.c  -o ${OBJECTDIR}/source/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/adc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/can.o: source/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/can.o.d 
	@${RM} ${OBJECTDIR}/source/can.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/can.c  -o ${OBJECTDIR}/source/can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/can.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/dma.o: source/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/dma.o.d 
	@${RM} ${OBJECTDIR}/source/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/dma.c  -o ${OBJECTDIR}/source/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/dma.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/DEEEmulation.o: source/DEEEmulation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/DEEEmulation.o.d 
	@${RM} ${OBJECTDIR}/source/DEEEmulation.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/DEEEmulation.c  -o ${OBJECTDIR}/source/DEEEmulation.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/DEEEmulation.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/source/DEEEmulation.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/source/FlashOperations.o: source/FlashOperations.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/FlashOperations.o.d 
	@${RM} ${OBJECTDIR}/source/FlashOperations.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  source/FlashOperations.s  -o ${OBJECTDIR}/source/FlashOperations.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/source/FlashOperations.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/source/FlashOperations.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/source/FlashOperations.o: source/FlashOperations.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/FlashOperations.o.d 
	@${RM} ${OBJECTDIR}/source/FlashOperations.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  source/FlashOperations.s  -o ${OBJECTDIR}/source/FlashOperations.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/source/FlashOperations.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/source/FlashOperations.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../dcMotorV3/motorDriver.X/source/DEEEmulation.c
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../dcMotorV3/motorDriver.X/source/DEEEmulation.c
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
