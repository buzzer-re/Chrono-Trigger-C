################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Monster.c \
../Move.c \
../Player.c \
../Stage.c \
../game.c \
../utils.c 

OBJS += \
./Monster.o \
./Move.o \
./Player.o \
./Stage.o \
./game.o \
./utils.o 

C_DEPS += \
./Monster.d \
./Move.d \
./Player.d \
./Stage.d \
./game.d \
./utils.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


