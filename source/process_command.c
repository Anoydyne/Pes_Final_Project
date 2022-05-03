/***********************************************************************************************
 *
 *    File name   : process_command.c
 *    Description : command processing functions
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains functions to process the given user input
 *    Reference	  : Code reference taken from professor's command processing lecture slides
 *
 *
 **********************************************************************************************/

/**************************************************************************
 * File includes here
 **************************************************************************/
#include "process_command.h"

/******************************************************************************
 * Defines here
 *****************************************************************************/
#define Hexdump_max_size 	(640)

#define WARNING_TEMP 		(26) 	// Warning temperature threshold
#define WARNING_CO 			(350) 	// Warning CO levels

#define DANGER_TEMP 		(30) 	// Danger temperature threshold
#define DANGER_CO 			(800) 	// Danger CO levels

#define MAX_PWM				(255)	// Maximum PWM value for RGB Led
#define HUNDRED_MS			(10)	// Value for 100ms timer

// Defining for function pointer
typedef void (*command_handler_t)(int, char *argv[]);

//Author command handler
void handle_author(int argc, char *argv[]);

//Hexdump command handler
void handle_dump(int argc, char *argv[]);

//help command handler
void handle_help(int argc, char *argv[]);

//Temperature command handler
void handle_temp(int argc, char *argv[]);

//Humidity command handler
void handle_hum(int argc, char *argv[]);

//CO(carbon monoxide)  Level command handler
void handle_co(int argc, char *argv[]);

//Weather monitoring station command handler
void handle_weather(int argc, char *argv[]);

//Structure to define command table
typedef struct
{
    const char *name;
    command_handler_t handler;
    const char *help_string;
} command_table_t;

//state table with all the possible commands. This can be modified in future with more options
static const command_table_t commands[] =
{
    // TODO: fill out command table here

    { "author"		, 	handle_author	, "author help" 	},
    { "dump"		, 	handle_dump		,  "dump help"  	},
    { "help"		, 	handle_help		, "command help"	},
    {"temperature"	,	handle_temp		, "temperature help"},
    {"humidity"		,	handle_hum		, "humidity help"	},
    {"co"			,	handle_co		, "CO help"			},
    {"Weather"		,	handle_weather	, "Weather help"	},
};

//Calculating the number of commands
static const int num_commands = sizeof(commands) / sizeof(command_table_t);

//Function to print the Author name on user input of Author
void handle_author(int argc, char *argv[])
{
    printf("Gauriech Ishaan Pilla \n\r");
    printf("? ");
}

//Function to print the surrounding humidity on user input of humidity
void handle_hum(int argc, char *argv[])
{
    // Setting I2C1 Flags
    I2C1_Set_Flags();
    // Storing humidity value from SHT21 Sensor
    float hum= read_humidity();
    // Printing Current Humidity
    printf("Current Humidity is: %.3f \n\r",hum);
    printf("? ");
}

//Function to print the surrounding temperature on user input of temperature
void handle_temp(int argc, char *argv[])
{
    // Setting I2C1 Flags
    I2C1_Set_Flags();
    // Storing temperature value from SHT21 Sensor
    float temp=read_temperature();
    // Printing Current Temperature
    printf("Current Temperature is: %.3f \n\r",temp);
    printf("? ");
}

//Function to print the surrounding CO (carbon monoxide) Levels on user input of CO
void handle_co(int argc, char *argv[])
{
    {
        // Storing CO Levels value from MQ7 Sensor
        int co= get_co();
        // Printing Current CO Levels
        printf("CO Levels=%d\n\r",co);
    }
    printf("? ");
}

//Function to start weather monitoring station
void handle_weather(int argc, char *argv[])
{
    printf("\n\r Weather Monitoring Starts \n\r");
    reset_timer();
    while(1)
    {
        int time= get_timer();								// 100 ms timer starts
        if (time>=HUNDRED_MS)
        {
            reset_timer();
            // Obtaining the current temperature
            I2C1_Set_Flags();
            float temp=read_temperature();
            printf("\n\rTEMPERATURE=%.3f\n\r",temp);

            // Obtaining the current Humidity level
            I2C1_Set_Flags();
            float hum= read_humidity();
            printf("HUMIDITY=%.3f\n\r",hum);

            // Obtaining the current CO level
            int co= get_co();
            printf("CO=%d\n\r",co);

            Delay(HUNDRED_MS);

            /***************************************************************************************
             * If loop to compare current temperature and CO levels and define states
             * Safe State	- If temperature and CO levels both are below safe values
             * Warning State- If either temperature or CO levels are above warning values
             * Danger State - If either temperature or CO levels are above danger values
             **************************************************************************************/

            if (temp>=DANGER_TEMP || co>DANGER_CO)
            {
                printf("\n\r DANGER!! \n\r");
                printf("\n\r");
                rgb_led(MAX_PWM,0,0);
            }
            else if (temp>=WARNING_TEMP || co>WARNING_CO)
            {
                printf("\n\r WARNING!! \n\r");
                printf("\n\r");
                rgb_led(MAX_PWM,MAX_PWM,0);
            }
            else if(temp<WARNING_TEMP && co<WARNING_CO)
            {
                printf("\n\r SAFE!! \n\r");
                printf("\n\r");
                rgb_led(0,MAX_PWM,0);
            }
        }
    }
    printf("? ");
}

//Function to print hexdump when user gives input for dump
void handle_dump(int argc, char *argv[])
{
    uint32_t len = 0;
    uint32_t start = 0;

    //Taking input from serial terminal and saving the start address which can be decimal or hexadecimal
    if (((*argv[1] >= '0') && (*argv[1] <= '9'))|| ((*argv[1] >= 'A') && (*argv[1] <= 'F'))|| ((*argv[1] >= 'a') && (*argv[1] <= 'f')))
    {
        sscanf(argv[1], "%x", &start);

        //Taking input from serial terminal for hexdump length
        if (strstr((char*) argv[2], "0x") || strstr((char*) argv[2], "0X"))
        {
            sscanf(argv[2], "%x", &len);
        }
        else
        {
            sscanf(argv[2], "%d", &len);
        }

        //Maximum limit is defined as 640. Checking if the user input is within the range for hexdump
        if (len > Hexdump_max_size)
        {
            printf("Length out of range. Enter length between 1 to 640 or 0x01 to 0x280\n\r");
            printf("? ");
            return;
        }

        //Calling hexdump function if the input start address is within the range
        hexdump(start, len);
        printf("? ");
    }
    else
    {
        printf("Unknown Command \n\r");	// If user input not satisfied, print error command/unknown command
        printf("? ");
    }
}

//Function to print all commands when Help command is given as user input
void handle_help(int argc, char *argv[])
{
    printf("Command: Temperature		; Arguments: NONE			; Description: Prints surrounding temperature \n\r");
    printf("Command: CO 			; Arguments: NONE			; Description: Prints surrounding CO Levels \n\r");
    printf("Command: Weather 		; Arguments: NONE			; Description: Starts Weather Monitoring station \n\r");
    printf("\n\r? ");
}

// Process command function. This function is used to decode the user input data, perform Lexical Analysis
// and run the code for the given user specified commands and perform the necessary functions.
// code reference for this function is taken from professor's slides

void process_command(char *input)
{
    char *p = input;
    char *end;
    // find end of string
    for (end = input; *end != '\0'; end++)
    {
        ;
    }
    // Tokenize input in place
    bool in_token = false;
    char *argv[10];
    int argc = 0;
    memset(argv, 0, sizeof(argv));

    //Performing lexical analysis.Checking the end of string and terminating by adding Null character.
    //Post that storing the string values and passing it for further command processing
    for (p = input; p < end; p++)
    {
        switch (in_token)
        {
        case false:
            if ((*p != ' ') || (*p != '\t'))
            {
                argv[argc] = p;
                argc++;
                in_token = true;
            }
            break;
        case true:
            if ((*p == ' ') || (*p == '\t'))
            {
                *p = '\0';
                in_token = false;
            }
            break;
        }
    }

    argv[argc] = NULL;		//Append string

    if (argc == 0)   		//No command
    {
        return;
    }

    //Comparing input with commands in state table and performing the functions accordingly.
    for (int i = 0; i < num_commands; i++)
    {

        if (strcasecmp(argv[0], commands[i].name) == 0)
        {
            commands[i].handler(argc, argv);
            break;
        }
        //Error handling if the input command is not one of the commands from state table.
        if (i == (num_commands - 1))
        {
            printf("Unknown Command :");
            for (int j = 0; j < argc; j++)
            {
                printf(" %s", argv[j]);
            }
            printf("\n\r? ");
        }
    }

}
