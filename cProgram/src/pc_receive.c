// #include <stdio.h>
// #include <stdlib.h>
// #include <libserialport.h>

// #define PORT_NAME "/dev/ttyUSB0"  // 사용 중인 포트로 변경
// #define BAUDRATE 115200

// int main(void) {
//     struct sp_port *port;
//     sp_get_port_by_name(PORT_NAME, &port);

//     if (sp_open(port, SP_MODE_READ) != SP_OK) {
//         printf("포트를 열 수 없습니다.\n");
//         return 1;
//     }

//     sp_set_baudrate(port, BAUDRATE);
//     sp_set_bits(port, 8);
//     sp_set_parity(port, SP_PARITY_NONE);
//     sp_set_stopbits(port, 1);
//     sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE);

//     printf("연결되었습니다! 데이터 수신 중...\n");

//     char buffer[256];
//     while (1) {
//         int bytes_read = sp_nonblocking_read(port, buffer, sizeof(buffer) - 1);

//         if (bytes_read > 0) {
//             buffer[bytes_read] = '\0';
//             printf("수신된 데이터: %s", buffer);
//         }
//     }

//     sp_close(port);
//     sp_free_port(port);

//     return 0;
// }
