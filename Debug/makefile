################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
transmit_tiny.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: transmit_tiny.elf secondary-outputs

# Tool invocations
transmit_tiny.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,transmit_tiny.map -mmcu=attiny85 -o "transmit_tiny.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

transmit_tiny.lss: transmit_tiny.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S transmit_tiny.elf  >"transmit_tiny.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: transmit_tiny.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny85 transmit_tiny.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) transmit_tiny.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
