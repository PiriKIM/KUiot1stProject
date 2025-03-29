#include "farmsql.h"
#include "serial.h"
#include "thread.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    const char *port_name = PORT_NAME; // 시리얼 포트 이름
    struct sp_port *port = setup_serial_port(port_name);
    SaveDataArgs args;       // sql, sensordata 넣는 구조체
    pthread_t save_thread;   // pthread ID"/dev/ttyUSB0";
    MySQLConnection mysql;
    int choice;
    bool dbConnected = false;
    SensorData rx;
    SensorData tx;

    // MySQL 연결 시도
    dbConnected = initMySQL(&mysql);
    if (!dbConnected)
    {
        printf("경고: 데이터베이스 연결 실패. data가 저장되지 않습니다.\n");
        waitEnter();
        return -1;
    }

    if (port == NULL) {
        return -1;
    }

    while (1) {
        receive_serial_data(port, &rx); // 데이터 수신 및 저장
        args.mysql = &mysql;
        args.data = &rx;
        // pthread를 사용해 스레드 생성
        pthread_create(&save_thread, NULL, saveDataThread, &args);
        // 스레드 종료 대기
        pthread_join(save_thread, NULL);

        if (rx.temperature >= 0 && rx.humidity >= 0 && rx.soil >= 0 && rx.sun >= 0)
        {
            if (rx.soil < 30 && rx.sun < 12)
                send_actuator(port, "3");
            else if (rx.soil < 30 && rx.sun > 11)
                send_actuator(port, "2");
            else if (rx.sun < 12)
                send_actuator(port, "1");
            else if (rx.sun > 11)
                send_actuator(port, "0");
        }
    }
    
    // MySQL 연결 종료  
    closeMySQL(&mysql);

    return 0;
}