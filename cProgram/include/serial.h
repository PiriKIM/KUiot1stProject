#ifndef SERIAL_H
#define SERIAL_H

#include "farmsql.h"
#include <libserialport.h>
#include <pthread.h>

#define PORT_NAME "/dev/ttyUSB0"  // 사용 중인 포트로 변경
#define BAUDRATE 115200


// 시리얼 포트 설정 함수
struct sp_port *setup_serial_port(const char *port_name);

// 시리얼 데이터 전송
void *send_serial_data(struct sp_port *port, SensorData *tx);

// 시리얼 데이터 수신 함수
void *receive_serial_data(struct sp_port *port, SensorData *rx);

// 액츄에이터 제어 메시지 전송
void send_actuator(struct sp_port *port, const char *message);

#endif 