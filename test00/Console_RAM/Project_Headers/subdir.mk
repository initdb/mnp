################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Headers/Cpu.c" \
"../Project_Headers/UART0.c" \

C_SRCS += \
../Project_Headers/Cpu.c \
../Project_Headers/UART0.c \

OBJS += \
./Project_Headers/Cpu_c.obj \
./Project_Headers/UART0_c.obj \

OBJS_QUOTED += \
"./Project_Headers/Cpu_c.obj" \
"./Project_Headers/UART0_c.obj" \

C_DEPS += \
./Project_Headers/Cpu_c.d \
./Project_Headers/UART0_c.d \

OBJS_OS_FORMAT += \
./Project_Headers/Cpu_c.obj \
./Project_Headers/UART0_c.obj \

C_DEPS_QUOTED += \
"./Project_Headers/Cpu_c.d" \
"./Project_Headers/UART0_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Project_Headers/Cpu_c.obj: ../Project_Headers/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Project_Headers/Cpu.args" -o "Project_Headers/Cpu_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Project_Headers/%.d: ../Project_Headers/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Project_Headers/UART0_c.obj: ../Project_Headers/UART0.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Project_Headers/UART0.args" -o "Project_Headers/UART0_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


