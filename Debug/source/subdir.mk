################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Accumulate_Line.c \
../source/adc.c \
../source/cbfifo.c \
../source/hexdump.c \
../source/i2c.c \
../source/main.c \
../source/mq7.c \
../source/mtb.c \
../source/process_command.c \
../source/pwm.c \
../source/rgb_led.c \
../source/semihost_hardfault.c \
../source/sht21.c \
../source/sysclock.c \
../source/test_cbfifo.c \
../source/timer.c \
../source/uart.c 

OBJS += \
./source/Accumulate_Line.o \
./source/adc.o \
./source/cbfifo.o \
./source/hexdump.o \
./source/i2c.o \
./source/main.o \
./source/mq7.o \
./source/mtb.o \
./source/process_command.o \
./source/pwm.o \
./source/rgb_led.o \
./source/semihost_hardfault.o \
./source/sht21.o \
./source/sysclock.o \
./source/test_cbfifo.o \
./source/timer.o \
./source/uart.o 

C_DEPS += \
./source/Accumulate_Line.d \
./source/adc.d \
./source/cbfifo.d \
./source/hexdump.d \
./source/i2c.d \
./source/main.d \
./source/mq7.d \
./source/mtb.d \
./source/process_command.d \
./source/pwm.d \
./source/rgb_led.d \
./source/semihost_hardfault.d \
./source/sht21.d \
./source/sysclock.d \
./source/test_cbfifo.d \
./source/timer.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=0 -I"C:\Users\djano\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Pes_final_project\board" -I"C:\Users\djano\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Pes_final_project\source" -I"C:\Users\djano\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Pes_final_project" -I"C:\Users\djano\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Pes_final_project\drivers" -I"C:\Users\djano\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Pes_final_project\CMSIS" -I"C:\Users\djano\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Pes_final_project\utilities" -I"C:\Users\djano\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Pes_final_project\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


