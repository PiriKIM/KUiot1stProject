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

    while (1) {
        receive_serial_data(port, &rx); // 데이터 수신 및 저장
        args.mysql = &mysql;
        args.data = &rx;
        // pthread를 사용해 스레드 생성
        pthread_create(&save_thread, NULL, saveDataThread, &args);
        // 스레드 종료 대기
        pthread_join(save_thread, NULL);
        i++; 
    }
    
    // MySQL 연결 종료  
    closeMySQL(&mysql);

    return 0;
}



/*
typedef struct {
    int temperature; // 온도
    int humidity;    // 습도
    int soil;        // 토양수분
    int sun;         // 일조량
    char cond[10];   // 상태
} SensorData;

int main(void) {
    struct sp_port *port;
    sp_get_port_by_name(PORT_NAME, &port);

    if (sp_open(port, SP_MODE_READ) != SP_OK) {
        printf("포트를 열 수 없습니다.\n");
        return 1;
    }

    sp_set_baudrate(port, BAUDRATE);
    sp_set_bits(port, 8);
    sp_set_parity(port, SP_PARITY_NONE);
    sp_set_stopbits(port, 1);
    sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE);

    printf("연결되었습니다! 데이터 수신 중...\n");

    int cds = -1, soil = -1, temp = -1, humidity = -1;
    SensorData rx;
    char buffer[256];
    while (1)
    {
        int bytes_read = sp_nonblocking_read(port, buffer, sizeof(buffer) - 1);
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
        if (bytes_read > 0)
        {

            // 파싱하기 위해 복사본 생성
            char *token = strtok(buffer, ",");

            while (token != NULL)
            {
                if (strncmp(token, "CDS:", 4) == 0)
                {
                    cds = atoi(token + 4);
                    rx.sun = cds;
                }
                else if (strncmp(token, "Soil:", 5) == 0)
                {
                    soil = atoi(token + 5);
                    rx.soil = soil;
                }
                else if (strncmp(token, "Temp:", 5) == 0)
                {
                    temp = atoi(token + 5);
                    rx.temperature = temp;
                }
                else if (strncmp(token, "Humidity:", 9) == 0)
                {
                    humidity = atoi(token + 9);
                    rx.humidity = humidity;
                }

                token = strtok(NULL, ",");
            }

            strcpy(rx.cond, "good");

            // 데이터 수신 성공: 구조체 값 출력
            printf("Received serial data:\n");
            printf("  temperature: %d\n", rx.temperature);
            printf("  humidity: %d\n", rx.humidity);
            printf("  soil: %d\n", rx.soil);
            printf("  sun: %d\n", rx.sun);
            printf("  cond: %s\n", rx.cond);
        }
        // else
        // {
        //     // 에러 처리
        //     printf("Error reading No data: %d\n", bytes_read);
        // }
    }

    sp_close(port);
    sp_free_port(port);

    return 0;
}
*/