################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Make-OTASys.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Make-OTASys.list \

OBJCOPY_BIN += \
Make-OTASys.bin \


# All Target
all: Make-OTASys.elf secondary-outputs

# Tool invocations
Make-OTASys.elf: $(OBJS) $(USER_OBJS) C:\Users\canlv\Documents\Make-OTASys\STM32F411RETX_FLASH.ld
	arm-none-eabi-gcc -o "Make-OTASys.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\canlv\Documents\Make-OTASys\STM32F411RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Make-OTASys.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Make-OTASys.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Make-OTASys.list"
	@echo 'Finished building: $@'
	@echo ' '

Make-OTASys.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Make-OTASys.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
