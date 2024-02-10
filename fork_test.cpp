#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#include "iostream"

int main(int argc, char *argv[]) {
    for (int i = 0; i < 3; i++) {
        fork();
        std::cout << "Hello, World!" << std::endl;
        wait(NULL);
    }
}

/*
    int i;
    pid_t pid;

    std::string *message;
    int n;

    printf("fork program starting\n");

    pid = fork();

    switch (pid)
    {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        message = new std::string("This is the child");
        n = 5;
        break;
    default:
        message = new std::string("This is the parent");
        n = 3;
        break;
    }
    for (i = 0; i < n; i++)
    {
        printf("%s\n", message);
        sleep(1);
    }
    exit(0);
*/