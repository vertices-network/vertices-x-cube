################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/tinyhttp/subdir.mk
-include Middlewares/Third_Party/cJSON/subdir.mk
-include Middlewares/Third_Party/Unity/subdir.mk
-include Middlewares/Third_Party/MbedTLS/subdir.mk
-include Middlewares/Third_Party/IOTA_C/wallet/subdir.mk
-include Middlewares/Third_Party/IOTA_C/crypto/subdir.mk
-include Middlewares/Third_Party/IOTA_C/core/utils/subdir.mk
-include Middlewares/Third_Party/IOTA_C/core/models/payloads/subdir.mk
-include Middlewares/Third_Party/IOTA_C/core/models/outputs/subdir.mk
-include Middlewares/Third_Party/IOTA_C/core/models/inputs/subdir.mk
-include Middlewares/Third_Party/IOTA_C/core/models/subdir.mk
-include Middlewares/Third_Party/IOTA_C/core/subdir.mk
-include Middlewares/Third_Party/IOTA_C/client/network/subdir.mk
-include Middlewares/Third_Party/IOTA_C/client/api/v1/subdir.mk
-include Middlewares/Third_Party/IOTA_C/client/api/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/subdir.mk
-include Middlewares/ST/STM32_Connect_Library/services/subdir.mk
-include Middlewares/ST/STM32_Connect_Library/netif/subdir.mk
-include Middlewares/ST/STM32_Connect_Library/core/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/Components/vl53l0x/subdir.mk
-include Drivers/BSP/Components/es_wifi/subdir.mk
-include Drivers/BSP/Components/LSM6DSL/subdir.mk
-include Drivers/BSP/Components/LPS22HB/subdir.mk
-include Drivers/BSP/Components/LIS3MDL/subdir.mk
-include Drivers/BSP/Components/HTS221/subdir.mk
-include Drivers/BSP/B-L4S5I-IOT01A/subdir.mk
-include Application/Wallet/subdir.mk
-include Application/Utils/subdir.mk
-include Application/User/subdir.mk
-include Application/Time/subdir.mk
-include Application/Tests/subdir.mk
-include Application/Startup/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := IOTA-Client
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
IOTA-Client.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
IOTA-Client.list \

OBJCOPY_BIN += \
IOTA-Client.bin \


# All Target
all: main-build

# Main-build Target
main-build: IOTA-Client.elf secondary-outputs

# Tool invocations
IOTA-Client.elf: $(OBJS) $(USER_OBJS) /Users/cyril/Documents/work/SDK/STM32CubeExpansion_IOTA1_V2.0.0/Projects/B-L4S5I-IOT01A/Applications/IOTA-Client/STM32CubeIDE/STM32L4S5VITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "IOTA-Client.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/Users/cyril/Documents/work/SDK/STM32CubeExpansion_IOTA1_V2.0.0/Projects/B-L4S5I-IOT01A/Applications/IOTA-Client/STM32CubeIDE/STM32L4S5VITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="IOTA-Client.map" -Wl,--gc-sections -static -L../../../../../../Middlewares/Third_Party/libsodium/library/STM32CubeIDE  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

IOTA-Client.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "IOTA-Client.list"
	@echo 'Finished building: $@'
	@echo ' '

IOTA-Client.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "IOTA-Client.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SIZE_OUTPUT)$(OBJDUMP_LIST)$(EXECUTABLES)$(OBJS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(OBJCOPY_BIN) IOTA-Client.elf
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
