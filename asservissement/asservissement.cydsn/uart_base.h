#ifndef UART_BASE_H
#define UART_BASE_H

#include <device.h>
#include <stdlib.h>
#include <string.h>
#include "Options.h"
#include "types.h"

#define NB_CMD 17
#define MAX_CMD 8
#define SIZE_MAX_BUFFER 50

typedef uint8 BOOL;

struct uart_command
{
	char* command;
	void (*function)(char*);
};

struct uart
{
	char buffer[SIZE_MAX_BUFFER];
	uint8_t index;
	BOOL first_parameter_call;
	BOOL is_buffer_unlocked;
	uint8_t number_commands;
	struct uart_command* commands;
	void (*start)(void);
	void (*stop)(void);
	uint8_t (*get_char)(void);
	void (*clear_rx_buffer)(void);
	void (*clear_tx_buffer)(void);
	void (*put_string)(uint8_t*);
	void (*put_string_const)(const uint8_t*);
};

void uart_init(	struct uart* uart,
				uint8_t number_commands, 
				void (*start)(void),
				void (*stop)(void),
				uint8_t (*get_char)(void),
				void (*clear_rx_buffer)(void),
				void (*clear_tx_buffer)(void),
				void (*put_string)(uint8_t*),
				void (*put_string_const)(const uint8_t*));
void uart_set_command(struct uart* uart, uint8_t index, const char* command, void (*function)(char*));
void uart_check(struct uart* uart);
BOOL uart_command_check(struct uart* uart);
char* uart_get_param(struct uart* uart);
void uart_call(struct uart* uart, char* command, char* str);
void uart_command_reset(struct uart* uart);
void uart_stop(struct uart* uart);

//**********Commande PC vers PSOC***************
void read_xy(struct uart* uart, char* p);
void quad_dec_value(struct uart* uart, char* p);
void timer_write_period(struct uart* uart, char* p);
void time_exec_counter(struct uart* uart, char* p);
void reset (struct uart* uart, char* p);
void set_consigne_asserv(struct uart* uart, char* p);
void set_PID(struct uart* uart, char* p);
void pwmR(struct uart* uart, char* p);
void pwmL(struct uart* uart, char* p);
void demuxR(struct uart* uart, char* p);
void demuxL(struct uart* uart, char* p);
void stop(struct uart* uart, char* p);
void gotoxy(struct uart* uart, char* p);
void gotoa(struct uart* uart, char* p);
void gotod(struct uart* uart, char* p);
void resetCoef(struct uart* uart, char* p);
void set_multiple_xy(struct uart* uart, char* p);

//*********Debug**********************************

#endif