#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "ipc_common.h"

int main(void) {
    printf("Sender: unesi poruku (max %d znakova): ", MAX_MESSAGE_LEN - 1);

    char input[MAX_MESSAGE_LEN];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Greška pri čitanju unosa.\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = '\0';

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    if (ftruncate(shm_fd, sizeof(shared_message_t)) == -1) {
        perror("ftruncate");
        close(shm_fd);
        return EXIT_FAILURE;
    }

    shared_message_t *shm_ptr = mmap(NULL, sizeof(shared_message_t),
                                     PROT_READ | PROT_WRITE, MAP_SHARED,
                                     shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        return EXIT_FAILURE;
    }

    sem_t *sem_empty = sem_open(SEM_EMPTY_NAME, O_CREAT, 0666, 1);
    if (sem_empty == SEM_FAILED) {
        perror("sem_open sem_empty");
        munmap(shm_ptr, sizeof(shared_message_t));
        close(shm_fd);
        return EXIT_FAILURE;
    }

    sem_t *sem_full = sem_open(SEM_FULL_NAME, O_CREAT, 0666, 0);
    if (sem_full == SEM_FAILED) {
        perror("sem_open sem_full");
        sem_close(sem_empty);
        munmap(shm_ptr, sizeof(shared_message_t));
        close(shm_fd);
        return EXIT_FAILURE;
    }

    if (sem_wait(sem_empty) == -1) {
        perror("sem_wait sem_empty");
        sem_close(sem_empty);
        sem_close(sem_full);
        munmap(shm_ptr, sizeof(shared_message_t));
        close(shm_fd);
        return EXIT_FAILURE;
    }

    snprintf(shm_ptr->message, MAX_MESSAGE_LEN, "%s", input);
    shm_ptr->sender_pid = getpid();
    printf("Poruka upisana u deljenu memoriju (PID: %d).\n", (int)shm_ptr->sender_pid);

    if (sem_post(sem_full) == -1) {
        perror("sem_post sem_full");
        sem_close(sem_empty);
        sem_close(sem_full);
        munmap(shm_ptr, sizeof(shared_message_t));
        close(shm_fd);
        return EXIT_FAILURE;
    }

    sem_close(sem_empty);
    sem_close(sem_full);

    munmap(shm_ptr, sizeof(shared_message_t));
    close(shm_fd);

    return EXIT_SUCCESS;
}

