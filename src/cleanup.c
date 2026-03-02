#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "ipc_common.h"

int main(void) {
    printf("Cleanup: brisanje shared memory segmenta i semafora...\n");

    /* Pokušaj da ukloniš shared memory segment */
    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
    } else {
        printf("Shared memory '%s' obrisan.\n", SHM_NAME);
    }

    /* Pokušaj da ukloniš semafore */
    if (sem_unlink(SEM_EMPTY_NAME) == -1) {
        perror("sem_unlink SEM_EMPTY_NAME");
    } else {
        printf("Semafor '%s' obrisan.\n", SEM_EMPTY_NAME);
    }

    if (sem_unlink(SEM_FULL_NAME) == -1) {
        perror("sem_unlink SEM_FULL_NAME");
    } else {
        printf("Semafor '%s' obrisan.\n", SEM_FULL_NAME);
    }

    return EXIT_SUCCESS;
}

