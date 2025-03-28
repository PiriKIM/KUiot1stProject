#include "farmsql.h"
#include "serial.h"
#include <pthread.h>
#include "thread.h"

int main() {
    const char *port_name = "/dev/ttyUSB0"; // 시리얼 포트 이름
    struct sp_port *port = setup_serial_port(port_name);
    // uint16_t buffer[10];     // 수신데이터 저장
    SaveDataArgs args;       // sql, sensordata 넣는 구조체
    pthread_t save_thread;   // pthread ID"/dev/ttyUSB0";
    MySQLConnection mysql;
    int choice;
    bool dbConnected = false;
    SensorData rx;
    SensorData tx;
    int i = 0;

    // MySQL 연결 시도
    dbConnected = initMySQL(&mysql);
    if (!dbConnected)
    {
        printf("경고: 데이터베이스 연결 실패. data가 저장되지 않습니다.\n");
        waitEnter();
    }

    if (port == NULL) {
        return -1;
    }

    while (i < 10) {
        receive_serial_data(port, &tx); // 데이터 수신 및 저장
        args.mysql = &mysql;
        args.data = &rx;
        // pthread를 사용해 스레드 생성
        pthread_create(&save_thread, NULL, saveDataThread, &args);
        // 스레드 종료 대기
        pthread_join(save_thread, NULL); // 스레드 종료 대기
        // MySQL 연결 종료  
        i++; 
    }

    closeMySQL(&mysql);

    return 0;
}