################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/FreeRTOS_Playground/common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o: D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/FreeRTOS_Playground/common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c common/ThirdParty/SEGGER/Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/common/ThirdParty/FreeRTOS/include" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/common/ThirdParty/SEGGER/Config" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/common/ThirdParty/SEGGER/OS" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/common/ThirdParty/SEGGER/SEGGER" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/common/ThirdParty/FreeRTOS" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/FreeRTOS_Playground/common/ThirdParty/FreeRTOS" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/FreeRTOS_Playground/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/FreeRTOS_Playground/common/ThirdParty/FreeRTOS/include" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/FreeRTOS_Playground/common/ThirdParty/SEGGER/Config" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/FreeRTOS_Playground/common/ThirdParty/SEGGER/OS" -I"D:/All_Learnings/Embedded-ALL/FreeRTOS_Restart_21_12_23/ide_wrkspc/RTOS_work/FreeRTOS_Playground/common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-ThirdParty-2f-SEGGER-2f-Config

clean-common-2f-ThirdParty-2f-SEGGER-2f-Config:
	-$(RM) ./common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.cyclo ./common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d ./common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o ./common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.su

.PHONY: clean-common-2f-ThirdParty-2f-SEGGER-2f-Config

