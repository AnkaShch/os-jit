#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* Exit with error message */
#define handle_error(msg)                                                      \
    do {                                                                       \
        perror(msg);                                                           \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

/* int add(int a) {return a + p;} */
unsigned char func_code[] = {0x55, 0x48, 0x89, 0xe5, 0x89, 0x7d, 0xfc, 0x8b,
                             0x45, 0xfc, 0x83, 0xc0, 0x42, 0x5d, 0xc3};

typedef int (*funptr)(int);

int main(int argc, char *argv[]) {
    int d, p;
    void *ptr = mmap(0, sizeof(func_code), PROT_WRITE | PROT_EXEC,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    scanf("%d", &d);
    scanf("%d", &p);

    func_code[12] = p;

    if (ptr == MAP_FAILED) {
        handle_error("mmap");
    }

    memcpy(ptr, func_code, sizeof(func_code));

    if (mprotect(ptr, sizeof(func_code), PROT_READ | PROT_EXEC) != 0) {
        perror("Error with mprotect");
        munmap(ptr, sizeof(func_code));
        return -1;
    }

    funptr func = ptr;
    int result = func(d);
    printf("%d + %d = %d\n", d, p, result);

    munmap(ptr, sizeof(func_code));
    return EXIT_SUCCESS;
}
