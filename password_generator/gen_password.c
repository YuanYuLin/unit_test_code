#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <crypt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static char hash_table[] = {
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
'u', 'v', 'w', 'x', 'y', 'z',
'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
'U', 'V', 'W', 'X', 'Y', 'Z',
};

#define ENCRYPT_SHA_256		5
#define ENCRYPT_SHA_512		6

char* generate_password(int algor, char* password)
{
    char *enc;
    char hash_str[20];
    char byte = 0;
    char salt[8];
    int fd;
    int idx = 0;
    int i = 0;

    fd = open ("/dev/random", O_RDONLY);
    for(i=0;i<sizeof(salt);i++) {
        read(fd, &byte, sizeof(byte));
        idx = (byte % sizeof(hash_table));
        salt[i] = hash_table[idx];
    }
    close(fd);
    sprintf(hash_str, "$%d$%s$encrypted", algor, salt);
    enc = crypt(password, hash_str);
    return enc;
}

int main(int argc, char** argv)
{
    char *enc;
    char *password;

    if(argc < 2) {
        printf("error : wrong arguments\n");
        return 1;
    }

    password = argv[1];
    enc = generate_password(ENCRYPT_SHA_512, password);
    printf("SHA-512 - %ld Encrypted \n %s\n", strlen(enc), enc);
    enc = generate_password(ENCRYPT_SHA_256, password);
    printf("SHA-256 - %ld Encrypted \n %s\n", strlen(enc), enc);
    return 0;
}

