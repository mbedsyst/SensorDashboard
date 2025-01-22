################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Library/BH1750.c \
../Src/Library/BMP280.c 

OBJS += \
./Src/Library/BH1750.o \
./Src/Library/BMP280.o 

C_DEPS += \
./Src/Library/BH1750.d \
./Src/Library/BMP280.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Library/%.o Src/Library/%.su Src/Library/%.cyclo: ../Src/Library/%.c Src/Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F401xE -c -I../Inc -I"../$(ProjDirPath)/Headers/CMSIS/Include" -I"../$(ProjDirPath)/Headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Library

clean-Src-2f-Library:
	-$(RM) ./Src/Library/BH1750.cyclo ./Src/Library/BH1750.d ./Src/Library/BH1750.o ./Src/Library/BH1750.su ./Src/Library/BMP280.cyclo ./Src/Library/BMP280.d ./Src/Library/BMP280.o ./Src/Library/BMP280.su

.PHONY: clean-Src-2f-Library

