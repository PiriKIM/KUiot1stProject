#include "farmsql.h"
#include "serial.h"

// 시리얼 포트 설정 함수   ATmega uart 송수신 설정값과 동일하게 셋팅 필요
struct sp_port *setup_serial_port(const char *port_name) {
    // struct sp_port *port;
    // sp_get_port_by_name(port_name, &port);
    // sp_open(port, SP_MODE_READ_WRITE);  //SP_MODE_READ_WRITE는 상수로 정의된 값
    // sp_set_baudrate(port, 115200);  // Baud rate 설정
    // printf("Serial port %s opened successfully.\n", port_name);

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
    int cds = -1, soil = -1, temp = -1, humidity = -1;

    char buffer[256];

    int bytes_read = sp_nonblocking_read(port, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
        // 파싱하기 위해 복사본 생성
        char *token = strtok(buffer, ",");

        while (token != NULL)
        {
            if (strncmp(token, "CDS:", 4) == 0)
            {
                cds = atoi(token + 4);
            }
            else if (strncmp(token, "Soil:", 5) == 0)
            {
                soil = atoi(token + 5);
            }
            else if (strncmp(token, "Temp:", 5) == 0)
            {
                temp = atoi(token + 5);
            }
            else if (strncmp(token, "Humidity:", 9) == 0)
            {
                humidity = atoi(token + 9);
            }
            
            token = strtok(NULL, ",");
        }
    }
    rx->temperature = temp;
    rx->humidity = humidity;
    rx->soil = soil;
    rx->sun = cds;
    strcpy(rx->cond, "good");
    if (rx->temperature >= 0 && rx->humidity >= 0 && rx->soil >= 0 && rx->sun >= 0)
    {
        // 데이터 수신 성공: 구조체 값 출력
        printf("Received serial data:\n");
        printf("  temperature: %d\n", rx->temperature);
        printf("  humidity: %d\n", rx->humidity);
        printf("  soil: %d\n", rx->soil);
        printf("  sun: %d\n", rx->sun);
        printf("  cond: %s\n", rx->cond);
    }
}


// https://www.joinc.co.kr/w/Site/Thread/Beginning/PthreadApiReference              pthread
// https://sigrok.org/api/libserialport/unstable/a00018.html                        libserialport
// https://docs.oracle.com/cd/E26502_01/html/E35303/tlib-1.html#tlib-79569          pthread