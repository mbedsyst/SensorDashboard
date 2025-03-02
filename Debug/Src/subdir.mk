################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/freertos.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/freertos.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/freertos.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F401xE -c -I../Inc -I"../$(ProjDirPath)/Headers/CMSIS/Include" -I"../$(ProjDirPath)/Headers/CMSIS/Device/ST/STM32F4xx/Include" -I../$(ProjDirPath)/Middlewares/ThirdParty/FreeRTOS/Source/include -I../$(ProjDirPath)/Middlewares/ThirdParty/FreeRTOS/Source/CMSIS_RTOS_V2 -I../$(ProjDirPath)/Middlewares/ThirdParty/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/zalma/OneDrive/Documents/STM32F4/SensorDashboard/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/zalma/OneDrive/Documents/STM32F4/SensorDashboard/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/freertos.cyclo ./Src/freertos.d ./Src/freertos.o ./Src/freertos.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

