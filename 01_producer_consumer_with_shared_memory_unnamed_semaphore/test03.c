#include <stdio.h>

#ifndef __BUFFER_H__
#define __BUFFER_H__
#include "buffer.h"

void print_test(void)
{
    shared_buffer_struct gv;
    gv.in = 0;
    gv.out = 1;
    gv.count = 2;
    gv.buffer[gv.in] = -1;
    print_int(gv.in);
    print_int(gv.out);
    print_int(gv.count);
    print_int(gv.buffer[gv.out-1]);
}

void shared_memeory_test(void)
{
    shared_buffer_struct ST;

    int shm_fd;
    int i, iii, ic, i_unlink;
    char* addr;
    void* ptr; 

    shm_fd = shm_open("BUFFER", O_CREAT|O_RDWR, 777);
    if (shm_fd == -1) {
        perror("Shared Memory Open Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("Open OK");

    i = ftruncate(shm_fd, sizeof(shared_buffer_struct));
    if (i == -1) {
        perror("ftruncate( ) Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("Ftruncate OK");

    addr = mmap(NULL, sizeof(shared_buffer_struct), PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (addr == MAP_FAILED) {
        perror("Memory Mapping Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("mmap OK");

    ptr = (shared_buffer_struct*) malloc(sizeof(shared_buffer_struct));
    if (ptr == NULL) {
        perror("malloc( ) Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("heap allocation to 'ptr' succeeded");

    memcpy(addr, ptr, sizeof(shared_buffer_struct));
    print_str("memcpy OK");

    shared_buffer_struct* stptr = (shared_buffer_struct*) ptr;
    print_str("ptr casting");

    ST.in = 9;                  
    print_str("set .in OK"); 
    print_int(ST.in);
    
    stptr->in = ST.in;
    print_int(stptr->in);
    ST.in = 0;
    print_int(ST.in);
    print_str("get through ptr");

    free(ptr);
    print_str("just freed memory 'ptr'");

    iii = munmap(addr, sizeof(shared_buffer_struct));
    if (iii == -1) {
        perror("m-Unmapping Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("memory Unmap OK");

    ic = close(shm_fd);
    if (ic == -1) {
        perror("Close Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("Close OK");

    i_unlink = shm_unlink("BUFFER");
    if (i_unlink == -1) {
        perror("Unlink Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("Unlink OK");

}

int main(void)
{   
    // print_test();

    // print_int(sizeof(shared_buffer_struct));
    shared_memeory_test();

    return 0;
}

#endif /* __BUFFER_H__ */


