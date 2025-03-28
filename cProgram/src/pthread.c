#include "thread.h"

void *saveDataThread(void *arg) {
    SaveDataArgs *data_args = (SaveDataArgs *)arg;

    //pthread_mutex_lock(&lock); // 자원 보호 시작

    saveData(data_args->mysql, data_args->data);   // sql 데이터 저장

    //pthread_mutex_unlock(&lock); // 자원 보호 해제

    free(data_args);


    return NULL;
}
