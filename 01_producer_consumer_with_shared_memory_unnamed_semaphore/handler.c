#include "producer.c"
#include "consumer.c"

void print_hello(void)
{
    printf("hello from buffer.h\n");
}

int main(int argc, char* argv[])
{
    int shm_fd;
    void* ptr;
    shared_buffer_struct bufst;

    shm_fd = shm_open("BUFFER_SEMAPHORE", O_CREAT | O_EXCL | O_RDWR, 777);
    if (st->shm_fd == -1)
    {
        perror("Shared Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    int ft = ftruncate(gv.shm_fd, SZ);
    if (ft == -1)
    {
        perror("Set Size to Shared Memory Failed\n");
        exit(EXIT_FAILURE);
    }

    ptr = mmap(NULL, sizeof(shared_buffer_struct), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, NULL);
    if (ptr == MAP_FAILED)
    {
        perror("Mapping Failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(shm_fd, bufst, sizeof(struct shared_buffer_struct));
    

    pid_t pid;
    if ((pid = fork()) < 0)
    {
        perror("Fork Failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid != 0) // parent : producer
    {
        shared_buffer_struct* ST;
        int pfd = shm_open("BUFFER_SEMAPHORE", O_CREAT | O_EXCL | O_RDWR, 777);
        void* pptr = mmap(NULL, 4096, PROT_WRITE, pfd, NULL);
        memcpy(ST, pfd, sizeof(shared_buffer_struct));

    }
    else // child : consumer
    {

    }

    return 0;
}


