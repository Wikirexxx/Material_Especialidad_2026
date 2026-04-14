################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc_driver.c \
../Src/adc_if.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_clock_driver.c \
../Src/system_clock_if.c \
../Src/usart_driver.c \
../Src/usart_if.c 

OBJS += \
./Src/adc_driver.o \
./Src/adc_if.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_clock_driver.o \
./Src/system_clock_if.o \
./Src/usart_driver.o \
./Src/usart_if.o 

C_DEPS += \
./Src/adc_driver.d \
./Src/adc_if.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_clock_driver.d \
./Src/system_clock_if.d \
./Src/usart_driver.d \
./Src/usart_if.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F405RGTx -c -I../Inc -I"C:/Users/franc/Documents/WS_STM32/SMT32F405/Chip_headers/Drivers/CMSIS/Include" -I"C:/Users/franc/Documents/WS_STM32/SMT32F405/Chip_headers/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc_driver.cyclo ./Src/adc_driver.d ./Src/adc_driver.o ./Src/adc_driver.su ./Src/adc_if.cyclo ./Src/adc_if.d ./Src/adc_if.o ./Src/adc_if.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_clock_driver.cyclo ./Src/system_clock_driver.d ./Src/system_clock_driver.o ./Src/system_clock_driver.su ./Src/system_clock_if.cyclo ./Src/system_clock_if.d ./Src/system_clock_if.o ./Src/system_clock_if.su ./Src/usart_driver.cyclo ./Src/usart_driver.d ./Src/usart_driver.o ./Src/usart_driver.su ./Src/usart_if.cyclo ./Src/usart_if.d ./Src/usart_if.o ./Src/usart_if.su

.PHONY: clean-Src

