################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../dbg_putchar.c \
../i2c.c \
../main.c \
../usiTwiSlave.c 

OBJS += \
./dbg_putchar.o \
./i2c.o \
./main.o \
./usiTwiSlave.o 

C_DEPS += \
./dbg_putchar.d \
./i2c.d \
./main.d \
./usiTwiSlave.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=attiny85 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


