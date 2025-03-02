################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Tasks/ConfigSystem.c \
../Src/Tasks/Console.c \
../Src/Tasks/ReadSensor.c \
../Src/Tasks/TaskManager.c \
../Src/Tasks/UpdateDash.c \
../Src/Tasks/WriteFlash.c 

OBJS += \
./Src/Tasks/ConfigSystem.o \
./Src/Tasks/Console.o \
./Src/Tasks/ReadSensor.o \
./Src/Tasks/TaskManager.o \
./Src/Tasks/UpdateDash.o \
./Src/Tasks/WriteFlash.o 

C_DEPS += \
./Src/Tasks/ConfigSystem.d \
./Src/Tasks/Console.d \
./Src/Tasks/ReadSensor.d \
./Src/Tasks/TaskManager.d \
./Src/Tasks/UpdateDash.d \
./Src/Tasks/WriteFlash.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Tasks/%.o Src/Tasks/%.su Src/Tasks/%.cyclo: ../Src/Tasks/%.c Src/Tasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F401xE -c -I../Inc -I"../$(ProjDirPath)/Headers/CMSIS/Include" -I"../$(ProjDirPath)/Headers/CMSIS/Device/ST/STM32F4xx/Include" -I../$(ProjDirPath)/Middlewares/ThirdParty/FreeRTOS/Source/include -I../$(ProjDirPath)/Middlewares/ThirdParty/FreeRTOS/Source/CMSIS_RTOS_V2 -I../$(ProjDirPath)/Middlewares/ThirdParty/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/zalma/OneDrive/Documents/STM32F4/SensorDashboard/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/zalma/OneDrive/Documents/STM32F4/SensorDashboard/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Tasks

clean-Src-2f-Tasks:
	-$(RM) ./Src/Tasks/ConfigSystem.cyclo ./Src/Tasks/ConfigSystem.d ./Src/Tasks/ConfigSystem.o ./Src/Tasks/ConfigSystem.su ./Src/Tasks/Console.cyclo ./Src/Tasks/Console.d ./Src/Tasks/Console.o ./Src/Tasks/Console.su ./Src/Tasks/ReadSensor.cyclo ./Src/Tasks/ReadSensor.d ./Src/Tasks/ReadSensor.o ./Src/Tasks/ReadSensor.su ./Src/Tasks/TaskManager.cyclo ./Src/Tasks/TaskManager.d ./Src/Tasks/TaskManager.o ./Src/Tasks/TaskManager.su ./Src/Tasks/UpdateDash.cyclo ./Src/Tasks/UpdateDash.d ./Src/Tasks/UpdateDash.o ./Src/Tasks/UpdateDash.su ./Src/Tasks/WriteFlash.cyclo ./Src/Tasks/WriteFlash.d ./Src/Tasks/WriteFlash.o ./Src/Tasks/WriteFlash.su

.PHONY: clean-Src-2f-Tasks

