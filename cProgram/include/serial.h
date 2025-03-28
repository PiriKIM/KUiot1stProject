#ifndef SERIAL_H
#define SERIAL_H

#include "farmsql.h"
#include <libserialport.h>
#include <pthread.h>
//atmeega128 uart 설정 헤더 추가 필요할듯?



// 시리얼 포트 설정 함수
struct sp_port *setup_serial_port(const char *port_name);

// 시리얼 데이터 전송
void *send_serial_data(struct sp_port *port, SensorData *tx);

// 시리얼 데이터 수신 함수
void *receive_serial_data(struct sp_port *port, SensorData *tx);

#endif 