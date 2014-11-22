################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SOIA/SysInterface/Linux/lin_launcher.cpp 

OBJS += \
./SOIA/SysInterface/Linux/lin_launcher.o 

CPP_DEPS += \
./SOIA/SysInterface/Linux/lin_launcher.d 


# Each subdirectory must supply rules for building sources it contributes
SOIA/SysInterface/Linux/%.o: ../SOIA/SysInterface/Linux/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/mxu/git/SOIAstd/SOIA/GlobalHeaders" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


