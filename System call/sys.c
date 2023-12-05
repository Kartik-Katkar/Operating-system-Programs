#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
void processRelatedSystemCalls() {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        printf("Child process (PID: %d) executing...\n", getpid());
        // Simulating some work in the child process
        sleep(2);
        exit(0);
    } 
    else if (pid > 0) {
        printf("Parent process (PID: %d) waiting for child to finish...\n", getpid());
        wait(2);
        
            printf("Child process (PID: %d) finished with status %d.\n", pid, WEXITSTATUS(status));
        
    } else {
        perror("Fork failed");
    }
}

void fileRelatedSystemCalls() {
    int fd;
    char buffer[100];
    char msg[100] = "Hello,!";
    ssize_t bytesRead, bytesWritten;

    // Open a file for writing
    fd = open("output.txt", O_RDWR | O_CREAT);
    if (fd == -1) {
        perror("Error open");
        return;
    }
    printf("File OPENED\n");

    // Write data to the file
    bytesWritten = write(fd, msg, strlen(msg));
    if (bytesWritten == -1) {
        perror("Error write");
    } else {
        printf("File Written\n");
    }

    // Close the file
    close(fd);
    printf("File Closed\n");

    // Open the file for reading
    fd = open("output.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    // Read data from the file
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("read");
    } else {
        buffer[bytesRead] = '\0';
        printf("Read from file: %s\n", buffer);
    }

    // Close the file
    close(fd);

    // Create a link to the file
    if (link("output.txt", "output_link.txt") == -1) {
        perror("link");
    } else {
        printf("Link created\n");
    }

    // Remove the link
    if (unlink("output_link.txt") == -1) {
        perror("unlink");
    } else {
        printf("Link removed\n");
    }
}

void communicationSystemCalls() {
    int pipefd[2];
    char buffer[20];
    pid_t pid;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    pid = fork();
    if (pid == 0) {
        // Child process
        close(pipefd[1]); // Close write end
        read(pipefd[0], buffer, sizeof(buffer));
            printf("Child received: %s\n", buffer);
            close(pipefd[0]);
        }
     
    else if (pid > 0) {
        // Parent process
        close(pipefd[0]); // Close read end
        char message[17] = "Hello from parent";
        write(pipefd[1], message, sizeof(message));
        close(pipefd[1]);
        wait(NULL);
    } else {
        perror("fork"); 
    }
}


void informationRelatedSystemCalls() {
    struct stat fileStat;

    uid_t uid = getuid();
    printf("User ID (UID): %d\n", uid);

    pid_t pid = getpid();
    printf("Process ID (PID): %d\n", pid);
    alarm(5);
    printf("An alarm has been set for 5 seconds.\n");

    printf("Sleeping for 3 seconds...\n");
    sleep(3);
    printf("Awake after sleep.\n");

    if (stat("output.txt", &fileStat) == -1) {
        perror("stat");
        return;
    }

    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("File Permissions: %o\n", fileStat.st_mode & 0777);
}

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Process-related system calls\n");
        printf("2. File-related system calls\n");
        printf("3. Communication system calls\n");
        printf("4. Information-related system calls\n");
        printf("5. Exit\n");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                processRelatedSystemCalls();
                break;
            case 2:
                fileRelatedSystemCalls();
                break;
            case 3:
                communicationSystemCalls();
                break;
            case 4:
                informationRelatedSystemCalls();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please select again.\n");
        }
    }

    return 0;
}
