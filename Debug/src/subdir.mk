################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Project_Parsec.cpp 

OBJS += \
./src/Project_Parsec.o 

CPP_DEPS += \
./src/Project_Parsec.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-8 -std=c++17 -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I"/home/bcthund/OneDrive/Projects/Programming/Project_Parsec/src/headers" -O0 -g3 -c -fmessage-length=0 -std=gnu++17 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


