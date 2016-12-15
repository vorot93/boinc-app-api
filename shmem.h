#ifndef shmem_h_INCLUDED
#define shmem_h_INCLUDED

#include "models.h"

typedef struct {
    SHARED_MEM* data;
    int status;
    int err;
    const char* msg;
} ShmemResult;

ShmemResult shmem_open(const char*);
void shmem_delete(SHARED_MEM*);

#endif
