/*
 * wifi_uart.c
 *
 *  Created on: Apr 10, 2020
 *      Author: canlv
 */
#include <wifi_uart.h>
#include "main.h"

extern UART_HandleTypeDef huart1;
static uint8_t wifi_command[128];
UART_HandleTypeDef *wifi_uart = &huart1;

int setCmdMode(const char *mode){
	size_t command_len;
	uint8_t resp_buff[128] = { 0 };
	sprintf((unsigned char*)wifi_command, "set sy c f %s\r\n", mode);
	command_len = strlen((char*)wifi_command);
	HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);
	if(getCmdResponse(resp_buff)<0)
		return -1;
	else
		return 0;
}

int getCmdResponse(unsigned char* uart_reponse)
{
    uint8_t header[16] = { 0 };
    uint8_t error_code[1];
    int rc = 0;

    HAL_UART_Receive(wifi_uart, (uint8_t*)header, 9, 0xFFFF);

    if(header[0] == 'R')
    {
    	if(header[1] == '0')
		{
			int len = atoi((char *)&header[2]);
			// every response always ends in /r/n (i.e., always > 2 bytes)
			if(len > 2)
			{
				unsigned char temp[2];

				// read the data (without the trailing /r/n)
				HAL_UART_Receive(wifi_uart, uart_reponse, len - 2, 0xFFFF);
				// cleanup the trailing /r/n
				HAL_UART_Receive(wifi_uart, temp, 2, 0xFFFF);
				// return actual data length
				return len - 2;
			}
			else
			{
				return 0;
			}

		}else{
			int len = atoi((char *)&header[2]);
			HAL_UART_Receive(wifi_uart, uart_reponse, len, 0xFFFF);
			printf("awm failed %s\r\n", uart_reponse);
		}

    }else {
    	printf("garbage amw %s\r\n", header);
    }
    return -1;
}

int setupNetwork(char *ssid, char *password){

	    uint8_t resp_buff[128] = { 0 };
	    size_t command_len;
	    sprintf((unsigned char*)wifi_command, "set wl s \"%s\"\r\n", ssid);
	    command_len = strlen((char*)wifi_command);
	    HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);

	    if(getCmdResponse(resp_buff)<0)
	    	return -1;

	    sprintf((unsigned char*)wifi_command, "set wl p %s\r\n", password);
	    command_len = strlen((char*)wifi_command);
	    HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);
	    if(getCmdResponse(resp_buff)<0)
	        return -1;
	    else
	    	return 0;
}
int setAutoJoinWifi(int state){
		uint8_t resp_buff[128] = { 0 };
		size_t command_len;
		sprintf((unsigned char*)wifi_command, "set wl o e %d\r\n", state);
		command_len = strlen((char*)wifi_command);
		HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);
		if(getCmdResponse(resp_buff)<0)
			return -1;
		else
			return 0;
}
int setTCPServer(int port, int timeout){

	uint8_t resp_buff[128] = { 0 };
	size_t command_len;
	sprintf((unsigned char*)wifi_command, "set tc s p %d\r\n", port);
	command_len = strlen((char*)wifi_command);
	HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);

	if(getCmdResponse(resp_buff)<0)
		return -1;

	sprintf((unsigned char*)wifi_command, "set tc s t %d\r\n", timeout);
	command_len = strlen((char*)wifi_command);
	HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);
	if(getCmdResponse(resp_buff)<0)
		return -1;
	else
		return 0;

}
int setAutostartTCP(int state){

	uint8_t resp_buff[128] = { 0 };
	size_t command_len;
	sprintf((unsigned char*)wifi_command, "set tc s a %d\r\n", state);
	command_len = strlen((char*)wifi_command);
	HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);
	if(getCmdResponse(resp_buff)<0)
		return -1;
	else
		return 0;
}
int setBUSmode(const char *mode){

	uint8_t resp_buff[128] = { 0 };
	size_t command_len;
	sprintf((unsigned char*)wifi_command, "set bus.mode %s\r\n", mode);
	command_len = strlen((char*)wifi_command);
	HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);

	if(getCmdResponse(resp_buff)<0)
		return -1;
	sprintf((unsigned char*)wifi_command, "save\r\n");
	command_len = strlen((char*)wifi_command);
	HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);

	if(getCmdResponse(resp_buff)<0)
	return -1;
	sprintf((unsigned char*)wifi_command, "reboot\r\n");
	command_len = strlen((char*)wifi_command);
	HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);

	if(getCmdResponse(resp_buff)<0)
		return -1;
	else
		return 0;
}

int changeStream2Command(void){

	uint8_t resp_buff[128] = { 0 };
	size_t command_len;

	sprintf((unsigned char*)wifi_command, "$$$\r\n");
	command_len = strlen((char*)wifi_command);
	HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);

	if(getCmdResponse(resp_buff)<0)
		return -1;
	else
		return 0;

}

int changeCommand2Stream(void){

	uint8_t resp_buff[128] = { 0 };
	size_t command_len;

	sprintf((unsigned char*)wifi_command, "exit\r\n");
	command_len = strlen((char*)wifi_command);
	HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);

	if(getCmdResponse(resp_buff)<0)
		return -1;
	else
		return 0;
}

int checkDataTCP(void){
	uint8_t resp_buff[128] = { 0 };
	size_t command_len;
	int state;
	sprintf((unsigned char*)wifi_command, "poll all -r\r\n");
	command_len = strlen((char*)wifi_command);
	HAL_UART_Transmit(wifi_uart, wifi_command, command_len, 0xFFFF);
	state = getCmdResponse(resp_buff);

	return state;
}



