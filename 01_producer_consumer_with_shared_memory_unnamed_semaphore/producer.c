#include "buffer.h"

void producer(void)
{
    shared_buffer_struct bufst;

    int shm_fd = shm_open("BUFFER_SEMAPHORE", O_CREAT | O_EXCL | O_RDWR, 777);
    if (shm_fd == -1)
    {
        perror("Shared Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    ft = ftruncate(gv.shm_fd, SZ);
    if (ft == -1)
    {
        perror("Set Size to Shared Memory Failed\n");
        exit(EXIT_FAILURE);
    }

    void* ptr = mmap(NULL, SZ, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, NULL);
    if (ptr == MAP_FAILED)
    {
        perror("Mapping Failed\n");
        exit(EXIT_FAILURE);
    }

}




























