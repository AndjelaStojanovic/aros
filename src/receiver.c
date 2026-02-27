#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "ipc_common.h"

int main(void) {
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open (pokreni prvo sender da kreira segment)");
        return EXIT_FAILURE;
    }

    shared_message_t *shm_ptr = mmap(NULL, sizeof(shared_message_t),
                                     PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        return EXIT_FAILURE;
    }

    printf("Primljena poruka od PID %d: %s\n",
           (int)shm_ptr->sender_pid, shm_ptr->message);

    munmap(shm_ptr, sizeof(shared_message_t));
    close(shm_fd);

    return EXIT_SUCCESS;
}

