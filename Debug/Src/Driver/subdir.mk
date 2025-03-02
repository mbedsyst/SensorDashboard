################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Driver/I2C.c \
../Src/Driver/RTC.c \
../Src/Driver/SPI.c \
../Src/Driver/SYSTICK.c \
../Src/Driver/UART.c \
../Src/Driver/VCOM.c 

OBJS += \
./Src/Driver/I2C.o \
./Src/Driver/RTC.o \
./Src/Driver/SPI.o \
./Src/Driver/SYSTICK.o \
./Src/Driver/UART.o \
./Src/Driver/VCOM.o 

C_DEPS += \
./Src/Driver/I2C.d \
./Src/Driver/RTC.d \
./Src/Driver/SPI.d \
./Src/Driver/SYSTICK.d \
./Src/Driver/UART.d \
./Src/Driver/VCOM.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Driver/%.o Src/Driver/%.su Src/Driver/%.cyclo: ../Src/Driver/%.c Src/Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F401xE -c -I../Inc -I"../$(ProjDirPath)/Headers/CMSIS/Include" -I"../$(ProjDirPath)/Headers/CMSIS/Device/ST/STM32F4xx/Include" -I../$(ProjDirPath)/Middlewares/ThirdParty/FreeRTOS/Source/include -I../$(ProjDirPath)/Middlewares/ThirdParty/FreeRTOS/Source/CMSIS_RTOS_V2 -I../$(ProjDirPath)/Middlewares/ThirdParty/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/zalma/OneDrive/Documents/STM32F4/SensorDashboard/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/zalma/OneDrive/Documents/STM32F4/SensorDashboard/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Driver

clean-Src-2f-Driver:
	-$(RM) ./Src/Driver/I2C.cyclo ./Src/Driver/I2C.d ./Src/Driver/I2C.o ./Src/Driver/I2C.su ./Src/Driver/RTC.cyclo ./Src/Driver/RTC.d ./Src/Driver/RTC.o ./Src/Driver/RTC.su ./Src/Driver/SPI.cyclo ./Src/Driver/SPI.d ./Src/Driver/SPI.o ./Src/Driver/SPI.su ./Src/Driver/SYSTICK.cyclo ./Src/Driver/SYSTICK.d ./Src/Driver/SYSTICK.o ./Src/Driver/SYSTICK.su ./Src/Driver/UART.cyclo ./Src/Driver/UART.d ./Src/Driver/UART.o ./Src/Driver/UART.su ./Src/Driver/VCOM.cyclo ./Src/Driver/VCOM.d ./Src/Driver/VCOM.o ./Src/Driver/VCOM.su

.PHONY: clean-Src-2f-Driver

