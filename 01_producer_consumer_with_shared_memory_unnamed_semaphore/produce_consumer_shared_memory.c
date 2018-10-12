/*******************************************************************************
 * FILE:                produce_consumer_shared_memory.c
 * TITLE:               Main program, multi-processing producer-consumer
 *                      adopting POSIX unnamed semaphore for synchronization
 *                      between two process.
 *                      Using POSIX Shared Memory object for inter-process
 *                      communication
 * Date:                October 13, 2018
 * Author:              yks93
 * Email:               keesung0705@gmail.com
 * Assignment:          Operating Systems - Assignment #01
 * Due Date:            ~
 *
 * Problem Statement:   Implement a simple program using POSIX Semaphore.
 *                      Create POSIX Shared Memory between two processes to act 
 *                      as a buffer for data transfer. These two processes 
 *                      communicates in the producer-consumer mode. 
 *                      The producer process loops through 0 to 1000, transfers 
 *                      sequential integer values to the consumer through 
 *                      the shared memory. 
 *                      The consumer process loops through 0 to 1000, retrieves 
 *                      the data from buffer.
 * Compile:             gcc produce_consumer_shared_memory.c -o ./bin/result -lrt -pthread
********************************************************************************/

/* Including header files */
#include "buffer.h"

/*******************************************************************************
 * Name of Function:    main
 * Purpose:             Fork the main process, use each as a producer, consumer
 *                      respectively. Create a POSIX Shared Memory to inter
 *                      communicate with each other. 
 *                      Use POSIX unnamed semaphore to synchronize two processes
 * Parameters:          ()
 * Return Value:        int
 * Calls to:            access, shm_open, ftruncate, mmap, fork, wait
 *                      memset, exit
 *                      sem_init, sem_wait, sem_post
 *                      munmap, close, shm_unlink
 *                      printf, print_int, print_str
 * Called from:         --
 * Method:              1. check whether the shared memory object exists
 *                         if there is, remove it
 *                      2. create, open, map a new POSIX Shared Memroy object
 *                      3. fork a process
 *                      In Parent Process
 *                          a. P-Operation on semaphore var which indicates
 *                             remaining buffer space
 *                          b. enqueue new data into buffer in shared memory
 *                          c. V-Operation on semaphore var which indicates
 *                             number of data in buffer
 *                      In Child Process
 *                          a. P-Operation on semaphore var which indicates
 *                             number of data in buffer
 *                          b. dequeue oldest data from buffer in shared memeory
 *                          c. V-Operation on semaphore var which indicates
 *                             remaining buffer space
 *                          --after processing data complete
 *                          d. unmap virtual memory of child process from
 *                             shared memory object
 *                          e. close the file descriptor refering to shared
 *                             memory object
 *                          f. exit explicitly with success status
 *                      4. unmap virtual memory of parent process from
 *                         shared memory object
 *                      5. close the file descriptor refering to shared 
 *                         memory object
 *                      6. remove the shared memory object from file system
 *                      7. exit(return) with sucess status
 ******************************************************************************/
int main()
{
    /* Declaring vaiables differentiate between parent and child process */
    pid_t pid;

    /*
     *  shm_fd
     *      -> file descriptor for POSIX Shared Memory object
     *  i_trunc, i_unmap, i_close, i_unlink
     *      -> vars for error check
     *  ptr
     *      -> pointer to access the shared memeory object
     *      -> returned value from mmap( ) function on success
     */
    int shm_fd;
    int i_trunc, i_unmap, i_close, i_unlink;
    void* ptr;

    {
        /* 
         *  check whether the shared memory object of the NAME exists
         *  if yes
         *      -> remove using unlink( ) function
         *  if no
         *      -> do nothing
         */
        struct stat st_tmp;
        if (access("/dev/shm/BUFFER", F_OK) == 0)
        {
            i_unlink = shm_unlink("BUFFER");
            if (i_unlink == -1) {
                perror("Initialization Failed\n");
                exit(EXIT_FAILURE);
            }
            print_str("Initialize OK");
        }
    }

    /* create and open  a new POSIX Shared Memeory object */
    shm_fd = shm_open("BUFFER", O_CREAT|O_RDWR, 777);
    if (shm_fd == -1) {
        perror("Shared Memory Open Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("Open OK");

    /* set the size of shared memeory object */
    i_trunc = ftruncate(shm_fd, sizeof(shared_buffer_struct));
    if (i_trunc == -1) {
        perror("ftruncate( ) Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("Ftruncate OK");

    /* map the shared memory object into the virtual address space of the calling process */
    ptr = mmap(NULL, sizeof(shared_buffer_struct), PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Memory Mapping Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("mmap OK");

    /* cast the shared memory mapped pointer to the pointer of proper type */
    shared_buffer_struct* stptr = (shared_buffer_struct*) ptr;
    print_str("ptr casting");

    /* initialize the variables - in, out, buffer, 2 semaphore */
    stptr->in = 0;      print_int(stptr->in);
    stptr->out = 0;     print_int(stptr->out);
    memset(stptr->buffer, -1, sizeof(int) * 100);
    sem_init(&(stptr->buffer_has_space), 1, 100);
    sem_init(&(stptr->buffer_has_data), 1, 0);

    /* fork a process */
    if ((pid = fork()) < 0) {
        perror("fork() Failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid != 0) 
    {   // parent : PRODUCER
        print_str("parent begin !!!\n");
        int i;
        for (i=0; i < 1000; ++i) 
        {
            sem_wait(&(stptr->buffer_has_space));
            stptr->buffer[stptr->in] = i;
            printf("inside parent: %d\n", stptr->buffer[stptr->in]);
            ++(stptr->in);
            stptr->in %= 100;
            sem_post(&(stptr->buffer_has_data));
        }
    }
    else
    {   // child : CONSUMER
        print_str("child begin !!!\n");
        int i;
        for (i=0; i < 1000; ++i)
        {
            sem_wait(&(stptr->buffer_has_data));
            printf("\tchild: %d\n", stptr->buffer[stptr->out]);         
            ++(stptr->out);
            stptr->out %= 100;
            sem_post(&(stptr->buffer_has_space));
        }

        /*
         *  The main process was forked previously, 
         *  now two processes (parent and child) have its own
         *  memory space
         *  
         *  This is clean-up code only for child process
         */
        i_unmap = munmap(ptr, sizeof(shared_buffer_struct));
        if (i_unmap == -1) {
            perror("m-Unmapping in Child Failed\n");
            exit(EXIT_FAILURE);
        }
        print_str("memory Unmap in Child OK");

        i_close = close(shm_fd);
        if (i_close == -1) {
            perror("Close Failed in Child \n");
            exit(EXIT_FAILURE);
        }
        print_str("Close in Child OK");

        /* end of the child process */
        exit(EXIT_SUCCESS);
    }

    /* wait until the child process to exit */
    wait(0);

    /*
     *  Clean-up code for parent process
     */

    /* unmap the shared memory object from the virtual address space of the calling process */
    i_unmap = munmap(ptr, sizeof(shared_buffer_struct));
    if (i_unmap == -1) {
        perror("m-Unmapping Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("memory Unmap OK");

    /* close the file descriptor allocated by shm_open( ) */
    i_close = close(shm_fd);
    if (i_close == -1) {
        perror("Close Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("Close OK");

    /* remove the shared memory object itself by name */
    i_unlink = shm_unlink("BUFFER");
    if (i_unlink == -1) {
        perror("Unlink Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("Unlink OK");

    /* end of the parent process. end of main */
    return 0;
}


