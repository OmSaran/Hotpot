#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <time.h>
#include <stdlib.h>

#define FILEPATH "/mnt/hotpot/file"
#define FILESIZE 512 * 1024 * 1024

int main() {
    srand(time(NULL));
    int fd;
    void* addr;
    char ch;
    int rnum;
    int i;

    rnum = rand() % 24;
    ch = (char)(rnum + 65);
    printf("The random character filled is %c\n", ch);

    fd = open(FILEPATH, O_RDWR | O_CREAT);
	if (fd < 0) {
        perror("Failed to create file");
        exit(1);
    }
    printf("Created file successfully\n");

    addr = mmap(NULL, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }
    printf("Mmapped successfully\n");

    char *caddr = (char *)addr;
    for(i=0; i<FILESIZE; i++) {
        caddr[i] = ch;
    }
    printf("Successfully wrote\n");
}
