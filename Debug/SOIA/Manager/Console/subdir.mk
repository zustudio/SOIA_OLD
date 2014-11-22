################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SOIA/Manager/Console/ConsoleManager.cpp 

OBJS += \
./SOIA/Manager/Console/ConsoleManager.o 

CPP_DEPS += \
./SOIA/Manager/Console/ConsoleManager.d 


# Each subdirectory must supply rules for building sources it contributes
SOIA/Manager/Console/%.o: ../SOIA/Manager/Console/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/mxu/git/SOIAstd/SOIA/GlobalHeaders" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


