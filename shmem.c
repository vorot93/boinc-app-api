#include "shmem.h"

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

ShmemResult shmem_open(const char* path) {
    SHARED_MEM* shmem = NULL;

    void** pp = (void**)&shmem;
    int fd = open(path, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        return (ShmemResult) {
            .data = NULL,
            .status = EBADF,
            .err = 0,
            .msg = "Failed to open file descriptor",
        };
    }

    struct stat sbuf;
    int err = fstat(fd, &sbuf);
    if (err) {
        close(fd);
        return (ShmemResult) {
            .data = NULL,
            .status = EIO,
            .err = err,
            .msg = "fstat() failed",
        };
    }
    size_t size = sizeof(SHARED_MEM);
    if (sbuf.st_size < size) {
        // The following 2 lines extend the file and clear its new
        // area to all zeros because they write beyond the old EOF.
        // See the lseek man page for details.
        lseek(fd, size-1, SEEK_SET);
        write(fd, "\0", 1);
    }

    *pp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, fd, 0);

    close(fd);

    if (*pp == MAP_FAILED) {
        return (ShmemResult) {
            .data = NULL,
            .status = EIO,
            .err = 0,
            .msg = "mmap() failed to map against SHARED_MEM",
        };
    }

    return (ShmemResult) {
        .data = shmem,
        .status = 0,
        .err = 0,
        .msg = "\0",
    };
}

void shmem_delete(SHARED_MEM* self) {
    munmap(self, sizeof(SHARED_MEM));
}
