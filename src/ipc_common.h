#ifndef IPC_COMMON_H
#define IPC_COMMON_H

#include <semaphore.h>
#include <sys/types.h>

#define SHM_NAME "/aros_chat_shm"
#define SEM_EMPTY_NAME "/aros_chat_sem_empty"
#define SEM_FULL_NAME  "/aros_chat_sem_full"

#define MAX_MESSAGE_LEN 256

typedef struct {
    char message[MAX_MESSAGE_LEN];
    pid_t sender_pid;
} shared_message_t;

#endif

