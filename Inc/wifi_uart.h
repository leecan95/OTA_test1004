#ifndef _WIFI_UART_H_
#define _WIFI_UART_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stdio.h"
#include "stdlib.h"

#define WIFI_SSID "Lee123"
#define WIFI_PASS "leecan123"
#define BUS_COMMAND_STATE 0
#define BUS_STREAM_STATE 1
#define BUS_COMMAND_MODE "command"
#define BUS_STREAM_MODE "stream"
#define MACHINE_MODE	"machine"
#define HUMAN_MODE		"human"
#define ENABLE 1
#define DISABLE 0
#define TCP_PORT 3000

int getCmdResponse(unsigned char* uart_reponse);
int setupNetwork(char *ssid, char *password);
int setAutoJoinWifi(int state);
int checkDataTCP(void);
int setTCPServer(int port, int timeout);
int setAutostartTCP(int state);
int setCmdMode(const char *mode);
int setBUSmode(const char *mode);
int changeStream2Command(void);
int changeCommand2Stream(void);

#endif
