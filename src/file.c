#include "file.h"

void createFile(char* path) {
    int fd = open(path, O_WRONLY | O_EXCL | O_CREAT, 0664);
    if (fd == -1) {
        exit (EXIT_FAILURE);
    }
}

void copyRW(char* source, char* target) {
    int fd_to, fd_from;
    char buffer[16];
    size_t offset = 0;
    size_t bytes_read;

    fd_from = open(source, O_RDONLY);
    if (fd_from == -1) return;

    createFile(target);
    fd_to = open(target, O_WRONLY);

    do {
        bytes_read = read(fd_from, buffer, sizeof(buffer));
        write_all(fd_to, buffer, bytes_read);

        offset += bytes_read;
    } while(bytes_read == sizeof(buffer));
    close(fd_from);
    close(fd_to);
}

void copyMmap(char* source, char* target) {
    int fd_to, fd_from;
    char *src, *tg;
    size_t size;

    fd_from = open(source, O_RDONLY);
    size = lseek(fd_from, 0, SEEK_END);
    src = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd_from, 0);

    fd_to = open(target, O_RDWR | O_CREAT, 0666);
    ftruncate(fd_to, size);
    tg = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_to, 0);

    memcpy(fd_to, fd_from, size);
    munmap(src, size);
    munmap(tg, size);

    close(fd_from);
    close(fd_to);
}

ssize_t write_all (int fd, const void* buffer, size_t count)
{
    size_t left_to_write = count;
    while (left_to_write > 0) {
        size_t written = write (fd, buffer, count);
        if (written == -1) return -1;
        else left_to_write -= written;
    }
    assert (left_to_write == 0);
    return count;
}
