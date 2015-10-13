################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CVtool.cpp \
../src/main.cpp \
../src/matrix.cpp 

OBJS += \
./src/CVtool.o \
./src/main.o \
./src/matrix.o 

CPP_DEPS += \
./src/CVtool.d \
./src/main.d \
./src/matrix.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -I"/home/t1audrai/Documents/ProjetElec/git/PES9EETAAS/DisplayImage/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


