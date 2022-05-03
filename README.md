# PES Final Project
# Weather Monitoring Station

Codes for PES Final Project, ECEN-5813, Spring 2022</br>

# Author:GAURIECH ISHAAN PILLA </br>

Contact me if I have missed something or if you are facing issue in execution of the code @ gapi3583@colorado.edu </br>

# Objective of this Project <br/>
As there have been many cases of fire in and around boulder, I came up with the idea of making a weather monitoring station. <br/>
This project aims to continuously monitor climate using a temperature/humidity sensor (SHT21) to continuously monitor temperature and <br/>
an MQ7 sensor that is suitable for sensing CO concentrations in the air. <br/>

# Implementation <br/>
Successfully implemented all the functionalities that were pitched in the project proposal <br/>

1) FRDM-KL25Z initializes PWM and runs automated tests of PWM for different values of RGB LED in Danger, warning and <br/>
safe states before the start of the main function. <br/>
2) Initialization of all other modules used in the project and then run automated tests for circular buffer. <br/>
3) FRDM-KL25Z reads the temperature, humidity and CO level values from the SHT21 (Temperature/Humidity sensor) and MQ7 (CO Sensor).  <br/>
4) The interfacing of SHT21 is done over the I2C communication protocol. I2C1 is used for SHT21. <br/>
5) The interfacing of MQ7 is done with the help of internal ADC. <br/>
6) Starting of command processor. The command processor can take different inputs and produce corresponding outputs for it. The menu looks like this:- <br/>
	1.	Type ‘Author’ to get the Author's name <br/>
	2.	Type ‘Dump’ with Arguments: (Start, Len) to get a hex dump of the memory requested <br/>
	3.	Type ‘Temperature’ to Print surrounding temperature <br/>
	4.	Type ‘Humidity’ to Print surrounding Humidity levels <br/>
	5.	Type ‘CO’ to Print surrounding CO levels <br/>
	6.	Type ‘Weather’ for Starting Weather Monitoring station <br/>    
	7.	Type ‘Help’ to see weather options <br/>
7) UART is used to display the values of temperature, humidity and CO levels when the weather monitoring station starts. <br/> 
8) PWM is used for RGB LEDs that are used to indicate different situations. <br/>
	- GREEN: indicates the safe state. <br/>
	- YELLOW: indicates the warning state. <br/>
	- RED: indicates the danger state. <br/>
9) Systick timer and delay function is used to get the delay. <br/>


# Project source details </br>

1.Accumulate_Line.c - Reads the characters entered by user on terminal and sends the string for Process command function </br>
2.cbfifo.c - This file implements circular buffer functions. Example - enqueue, dequeue, length, capacity and reset </br>
3.hexdump.c - prints hex dump from the starting address till the length defined by user </br>
4.main.c - initialize different modules, Perform test cases for cbfifo and PWM then starts with serial user input in an infinite loop </br>
5.process_command.c - Decode the string received from terminal and perform the state table functions </br>
6.sysclock.c - This file initialize the system clock </br>
7.test_cbfifo.c - Runs the test cases for Circular Buffer </br>
8.uart.c - Initialization of UART0, interrupt handler and ties/replaces standard printf() and getchar() function implementation </br>
9.adc.c	- Contains functions to initialize and read ADC data </br>
10.i2c.c- Contains functions to initialize and read for i2c </br>
11.mq7.c- Contains function to get CO levels data from ADC </br>
12.pwm.c- Contains functions for PWM initialization </br>
13.rgb_led.c- Contains function declarations for RGB led </br>
14.sht21.c - Contains functions to get temperature and humidity values </br>
15.timer.c- Contains functions for systic timer initialization and other functions </br>

# UART conifguration 	</br>
Baud Rate - 38400 </br>
data bits -8 </br>
stop bit- 2 </br>
Parity - None </br>

# Files used from the previous assignments </br>
a)	Accumulate_Line.c & Accumulate_Line.h </br>
b)	cbfifo.c & cbfifo.h </br>
c)	hexdump.c & hexdump.h </br>
d)	process_command.c & process_command.h </br>
e)	pwm.c & pwm.h </br>
f)	rgb_led.c & rgb_led.h </br>
g)	sysclock.c & sysclock.h </br>
h)	test_cbfifo.c & test_cbfifo.h </br>
i)	timer.c & timer.h </br>
j)	uart.c & uart.h </br>

# Technology Used </br>
I chose this project because it will let me to work extensively with I2C, ADC, UART, and </br>
PWM, particularly with I2C, which was taught in class but not included in any of the </br>
assignments. I wanted to delve deeper into the UART, ADC, and PWM concepts that I </br>
had learnt and implemented in earlier assignments. UART will be used to show </br>
messages on the terminal, PWM will be used to operate the RGB LED to signify various </br>
conditions, and ADC will be used to retrieve data from the MQ7 CO Sensor in my </br>
project. </br>

# Things to learn in order to develop the project </br>
To interface the external temperature sensor with the FRDM-KL25Z board, this project  </br>
requires the learning of an I2C communication protocol. I predict that learning the I2C  </br>
protocol and how it works will be necessary before developing code for it. In addition, I  </br>
must use ADC to interface an external CO sensor and display the data on UART. In </br>
assignment 7, I aim to learn about ADC, but I'll have to figure out extra procedures to </br>
get data from an external sensor.</br>
Apart from that, because I had developed UART and PWM in the previous assignment, </br>
the implementation of these two concepts would strengthen the foundation of these two </br>
concepts. In addition, after my project's functionality has been established, I intend to </br>
implement a command processor. </br>
 

# Hardware Used </br>
1. SHT21 </br>
2. MQ7 </br>

# Bonus Implementation </br>
My idea was to extract only temperature values from SHT21 to represent the weather monitoring but along with temperature and CO levels,  </br>
humidity sensing is also implemented and the data of humidity is extracted from the SHT21 sensor along with the temperature values. </br>

# Google Drive Link for video- </br>
https://drive.google.com/file/d/1QSVkafFUy4M6mZ3zhJoB_b7JH6yf-uSr/view?usp=sharing </br>

Implementation in the video:- </br>
a) Introduction to my project hardware</br>
b) Showing testing of PWM and Cbfifo</br>
c) UART command processor starts. Showing output of temperature and CO levels</br>
d) The weather monitoring station starts.</br>
e) Showing MQ7 output for weather monitoring using a lighter. As I am pointing lighter </br>
directly towards the sensor, the CO levels fluctuate very quickly but I could capture all </br>
three states.</br>
f) Showing SHT21 output by blowing hot air on the sensor. I was able to demonstrate all 3 </br>
levels of my project in this video.</br>
g) Do let me know if something was not clear. I can demonstrate the output again.</br>

Contact me if there is any issue with the video. </br>