################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/headers/gamesys/GUI.cpp \
../src/headers/gamesys/GUI_Dialog.cpp \
../src/headers/gamesys/GUI_Window.cpp 

OBJS += \
./src/headers/gamesys/GUI.o \
./src/headers/gamesys/GUI_Dialog.o \
./src/headers/gamesys/GUI_Window.o 

CPP_DEPS += \
./src/headers/gamesys/GUI.d \
./src/headers/gamesys/GUI_Dialog.d \
./src/headers/gamesys/GUI_Window.d 


# Each subdirectory must supply rules for building sources it contributes
src/headers/gamesys/%.o: ../src/headers/gamesys/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I"/home/bcthund/OneDrive/Projects/Programming/Project_Parsec/src/headers" -O3 -g3 -c -fmessage-length=0 -std=c++14 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


