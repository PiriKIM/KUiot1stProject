#include "farmsql.h"
#include "serial.h"
#include "uart0.h"

// 운영체제 확인을 위한 매크로 추가
// #ifdef _WIN32
// #define CLEAR_SCREEN "cls"
// #else
// #define CLEAR_SCREEN "clear"
// #endif

// 메뉴 상수 정의를 enum으로 변경
// typedef enum
// {
//     VIEW_HISTORY = 1,
//     MONTHLY_STATS, 
//     EXIT = 0
// } MenuOption;

// // 메뉴 출력 함수
// void printMenu()
// {
//     system(CLEAR_SCREEN);
//     printf("=== SmartFarm DB 시스템 ===\n");
//     printf("1. 기록 보기\n");
//     printf("2. 월별 통계 보기\n"); 
//     printf("0. 종료\n");
//     printf("선택: ");
// }

int main() {
    const char *port_name = "/dev/ttyUSB0"; // 시리얼 포트 이름
    struct sp_port *port = setup_serial_port(port_name);
    uint16_t buffer[10];     // 수신데이터 저장
    SaveDataArgs args;       // sql, sensordata 넣는 구조체
    pthread_t save_thread;   // pthread ID"/dev/ttyUSB0";
    MySQLConnection mysql;
    int choice;
    bool dbConnected = false;
    SensorData rx;
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

    while (i = 10) {
        receive_serial_data(port, buffer); // 데이터 수신 및 저장
        args.mysql = mysql;
        args.data = rx;
        // pthread를 사용해 스레드 생성
        pthread_create(&save_thread, NULL, saveDataThread, &args);
        // 스레드 종료 대기
        pthread_join(save_thread, NULL); // 스레드 종료 대기
        // MySQL 연결 종료  
        i++; 
    }

    closeMySQL(mysql);
    sp_close(port);
    sp_free_port(port);
    return 0;
}