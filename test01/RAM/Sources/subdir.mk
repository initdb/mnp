################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/console_io.c" \
"../Sources/exceptions.c" \
"../Sources/main.c" \
"../Sources/terminal_wrapper.c" \
"../Sources/uart_support.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/console_io.c \
../Sources/exceptions.c \
../Sources/main.c \
../Sources/terminal_wrapper.c \
../Sources/uart_support.c \

OBJS += \
./Sources/Events_c.obj \
./Sources/console_io_c.obj \
./Sources/exceptions_c.obj \
./Sources/main_c.obj \
./Sources/terminal_wrapper_c.obj \
./Sources/uart_support_c.obj \

OBJS_QUOTED += \
"./Sources/Events_c.obj" \
"./Sources/console_io_c.obj" \
"./Sources/exceptions_c.obj" \
"./Sources/main_c.obj" \
"./Sources/terminal_wrapper_c.obj" \
"./Sources/uart_support_c.obj" \

C_DEPS += \
./Sources/Events_c.d \
./Sources/console_io_c.d \
./Sources/exceptions_c.d \
./Sources/main_c.d \
./Sources/terminal_wrapper_c.d \
./Sources/uart_support_c.d \

OBJS_OS_FORMAT += \
./Sources/Events_c.obj \
./Sources/console_io_c.obj \
./Sources/exceptions_c.obj \
./Sources/main_c.obj \
./Sources/terminal_wrapper_c.obj \
./Sources/uart_support_c.obj \

C_DEPS_QUOTED += \
"./Sources/Events_c.d" \
"./Sources/console_io_c.d" \
"./Sources/exceptions_c.d" \
"./Sources/main_c.d" \
"./Sources/terminal_wrapper_c.d" \
"./Sources/uart_support_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/Events.args" -o "Sources/Events_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/console_io_c.obj: ../Sources/console_io.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/console_io.args" -o "Sources/console_io_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/exceptions_c.obj: ../Sources/exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/exceptions.args" -o "Sources/exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/terminal_wrapper_c.obj: ../Sources/terminal_wrapper.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/terminal_wrapper.args" -o "Sources/terminal_wrapper_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart_support_c.obj: ../Sources/uart_support.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/uart_support.args" -o "Sources/uart_support_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


