#include "farmsql.h"
#include "serial.h"
//#include <libserialport.h>

// 시리얼 포트 설정 함수   ATmega uart 송수신 설정값과 동일하게 셋팅 필요
struct sp_port *setup_serial_port(const char *port_name) {
    struct sp_port *port;
    sp_get_port_by_name(port_name, &port);
    sp_open(port, SP_MODE_READ_WRITE);  //SP_MODE_READ_WRITE는 상수로 정의된 값
    sp_set_baudrate(port, 115200);  // Baud rate 설정
    printf("Serial port %s opened successfully.\n", port_name);
    
    return port;
}

// 시리얼 데이터 전송    아마 사용안 할 듯?
void *send_serial_data(struct sp_port *port, SensorData *tx) {
    int tx_bytes;

    tx_bytes = sp_blocking_write(port, tx, sizeof(SensorData), 1000);
    if (tx_bytes > 0){
        printf("Sent serial data\n");
    }
    else {
        printf("Error reading data: %d\n", tx_bytes);
    }

    return 0;
}

// 시리얼 데이터 수신 함수
void *receive_serial_data(struct sp_port *port, SensorData *rx) {
    
    int bytes_read = sp_blocking_read(port, rx, sizeof(SensorData), 1000); // 데이터를 읽음

    if (bytes_read == sizeof(SensorData)) {
        // 데이터 수신 성공: 구조체 값 출력
        printf("Received serial data:\n");
        printf("  Temperature: %d\n", rx->temperature);
        printf("  Humidity: %d\n", rx->humidity);
        printf("  Soil: %d\n", rx->soil);
        printf("  Light: %d\n", rx->sun);
        printf("  Light: %s\n", rx->cond);
    } else if (bytes_read > 0) {
        // 부분적으로 데이터 수신
        printf("Partial data received (%d of %lu bytes)\n", bytes_read, sizeof(SensorData));
    } else {
        // 에러 처리
        printf("Error reading data: %d\n", bytes_read);
    }
}


// https://www.joinc.co.kr/w/Site/Thread/Beginning/PthreadApiReference              pthread
// https://sigrok.org/api/libserialport/unstable/a00018.html                        libserialport
// https://docs.oracle.com/cd/E26502_01/html/E35303/tlib-1.html#tlib-79569          pthread