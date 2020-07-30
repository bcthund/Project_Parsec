################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/headers/core/Colors.cpp \
../src/headers/core/Debug.cpp \
../src/headers/core/FractalNoise.cpp \
../src/headers/core/FrameRate.cpp \
../src/headers/core/Groups.cpp \
../src/headers/core/ParticleEmitter.cpp \
../src/headers/core/Particles.cpp \
../src/headers/core/RunningStat.cpp \
../src/headers/core/SimplexNoise.cpp \
../src/headers/core/Stipple.cpp \
../src/headers/core/SystemTextures.cpp \
../src/headers/core/TextureAtlas.cpp \
../src/headers/core/TimeSys.cpp \
../src/headers/core/VBO.cpp \
../src/headers/core/audiosys.cpp \
../src/headers/core/glinit.cpp \
../src/headers/core/helper.cpp \
../src/headers/core/joint.cpp \
../src/headers/core/lights.cpp \
../src/headers/core/matrix.cpp \
../src/headers/core/path.cpp \
../src/headers/core/profile.cpp \
../src/headers/core/ptimer.cpp \
../src/headers/core/shader.cpp \
../src/headers/core/skeleton.cpp \
../src/headers/core/state.cpp \
../src/headers/core/texture.cpp \
../src/headers/core/timer.cpp \
../src/headers/core/vao.cpp 

OBJS += \
./src/headers/core/Colors.o \
./src/headers/core/Debug.o \
./src/headers/core/FractalNoise.o \
./src/headers/core/FrameRate.o \
./src/headers/core/Groups.o \
./src/headers/core/ParticleEmitter.o \
./src/headers/core/Particles.o \
./src/headers/core/RunningStat.o \
./src/headers/core/SimplexNoise.o \
./src/headers/core/Stipple.o \
./src/headers/core/SystemTextures.o \
./src/headers/core/TextureAtlas.o \
./src/headers/core/TimeSys.o \
./src/headers/core/VBO.o \
./src/headers/core/audiosys.o \
./src/headers/core/glinit.o \
./src/headers/core/helper.o \
./src/headers/core/joint.o \
./src/headers/core/lights.o \
./src/headers/core/matrix.o \
./src/headers/core/path.o \
./src/headers/core/profile.o \
./src/headers/core/ptimer.o \
./src/headers/core/shader.o \
./src/headers/core/skeleton.o \
./src/headers/core/state.o \
./src/headers/core/texture.o \
./src/headers/core/timer.o \
./src/headers/core/vao.o 

CPP_DEPS += \
./src/headers/core/Colors.d \
./src/headers/core/Debug.d \
./src/headers/core/FractalNoise.d \
./src/headers/core/FrameRate.d \
./src/headers/core/Groups.d \
./src/headers/core/ParticleEmitter.d \
./src/headers/core/Particles.d \
./src/headers/core/RunningStat.d \
./src/headers/core/SimplexNoise.d \
./src/headers/core/Stipple.d \
./src/headers/core/SystemTextures.d \
./src/headers/core/TextureAtlas.d \
./src/headers/core/TimeSys.d \
./src/headers/core/VBO.d \
./src/headers/core/audiosys.d \
./src/headers/core/glinit.d \
./src/headers/core/helper.d \
./src/headers/core/joint.d \
./src/headers/core/lights.d \
./src/headers/core/matrix.d \
./src/headers/core/path.d \
./src/headers/core/profile.d \
./src/headers/core/ptimer.d \
./src/headers/core/shader.d \
./src/headers/core/skeleton.d \
./src/headers/core/state.d \
./src/headers/core/texture.d \
./src/headers/core/timer.d \
./src/headers/core/vao.d 


# Each subdirectory must supply rules for building sources it contributes
src/headers/core/%.o: ../src/headers/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-8 -std=c++17 -D__GXX_EXPERIMENTAL_CXX0X__ -DGL_GLEXT_PROTOTYPES -I"/home/bcthund/OneDrive/Projects/Programming/Project_Parsec/src/headers" -O0 -g3 -c -fmessage-length=0 -std=gnu++17 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


