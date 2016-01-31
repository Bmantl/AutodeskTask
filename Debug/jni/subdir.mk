################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../jni/Benchmark.cpp \
../jni/Main.cpp \
../jni/Mat.cpp \
../jni/Matrix.cpp 

OBJS += \
./jni/Benchmark.o \
./jni/Main.o \
./jni/Mat.o \
./jni/Matrix.o 

CPP_DEPS += \
./jni/Benchmark.d \
./jni/Main.d \
./jni/Mat.d \
./jni/Matrix.d 


# Each subdirectory must supply rules for building sources it contributes
jni/%.o: ../jni/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/lib/jvm/jdk1.8.0_72/include -I/usr/lib/jvm/jdk1.8.0_72/include/linux -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


