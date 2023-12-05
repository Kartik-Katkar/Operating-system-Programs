#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>

void *sender(void *arg) {
    char *fifo_name = (char *)arg;
    int fd;

    fd = open(fifo_name, O_WRONLY);
    write(fd, "Hello", 5);

    // printf("Sender having a pid of %d has sent the data\n", getpid());    
    close(fd);
    
    return NULL;
}

void *receiver(void *arg) {
    char *fifo_name = (char *)arg;
    int fd;
    char buffer[100];

    fd = open(fifo_name, O_RDONLY);
    read(fd, buffer, 50);
    // printf("Receiver having a pid of %d has received the data\n", getpid());
    printf("Received data: %s\n", buffer);
    close(fd);
    
    return NULL;
}

int main() {
    while (1) {
        system("clear");
        printf("Lab 4: System Call Demonstration\n");
        printf("1. Process Related System Calls\n");
        printf("2. File Related System Calls\n");
        printf("3. Communication System Calls\n");
        printf("4. Information Related System Calls\n");
        printf("5. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Process Related System Calls
                printf("1. fork\n");
                printf("2. exit\n");
                printf("3. wait\n");

                int sub_choice;
                printf("Enter sub-choice: ");
                scanf("%d", &sub_choice);

                switch (sub_choice) {
                    case 1:
                        printf("Executing fork system call...\n");
                        pid_t child_pid = fork();
                        if (child_pid == 0) {
                            printf("This is the child process.\n");
                        } else if (child_pid > 0) {
                            printf("This is the parent process. Child PID: %d\n", child_pid);
                        } else {
                            printf("Fork failed.\n");
                        }
                        break;
                    case 2:
                        printf("Executing exit system call...\n");
                        exit(0);
                        break;
                    case 3:
                        printf("Executing wait system call...\n");
                        wait(NULL);
                        printf("Child process has completed.\n");
                        break;
                    default:
                        printf("Invalid sub-choice\n");
                        break;
                }
                break;

            case 2: // File Related System Calls
                printf("1. open\n");
                printf("2. read\n");
                printf("3. write\n");
                printf("4. close\n");
                printf("5. link\n");
                printf("6. unlink\n");
                printf("7. stat\n");

                printf("Enter sub-choice: ");
                scanf("%d", &sub_choice);

                switch (sub_choice) {
                    case 1:
                        printf("Executing open system call...\n");
                        int fd = open("sample.txt", O_CREAT | O_WRONLY, 0644);
                        if (fd != -1) {
                            printf("File opened for writing.\n");
                            close(fd);
                        } else {
                            printf("Error opening file.\n");
                        }
                        break;
                    case 2:
                        printf("Executing read system call...\n");
                        fd = open("sample.txt", O_RDONLY);
                        if (fd != -1) {
                            char content[100];
                            ssize_t bytesRead = read(fd, content, sizeof(content));
                            if (bytesRead > 0) {
                                content[bytesRead] = '\0';
                                printf("Content read from file: %s\n", content);
                            } else {
                                printf("Error reading file.\n");
                            }
                            close(fd);
                        } else {
                            printf("Error opening file.\n");
                        }
                        break;
                    case 3:
                        printf("Executing write system call...\n");
                        fd = open("sample.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        if (fd != -1) {
                            write(fd, "Hello, world!", 13);
                            printf("Content written to file.\n");
                            close(fd);
                        } else {
                            printf("Error opening file.\n");
                        }
                        break;
                    case 4:
                        printf("Executing close system call...\n");
                        close(sub_choice); // Replace sub_choice with the actual file descriptor
                        printf("File closed.\n");
                        break;
                    case 5:
                        printf("Executing link system call...\n");
                        link("sample.txt", "sample_link.txt");
                        printf("Hard link created.\n");
                        break;
                    case 6:
                        printf("Executing unlink system call...\n");
                        unlink("sample_link.txt");
                        printf("Hard link removed.\n");
                        break;
                    case 7:
                        printf("Executing stat system call...\n");
                        struct stat st;
                        if (stat("sample.txt", &st) == 0) {
                            printf("File Size: %lld bytes\n", (long long)st.st_size);
                            printf("File Permissions: %o\n", st.st_mode & 0777);
                        } else {
                            printf("Error getting file information.\n");
                        }
                        break;
                    default:
                        printf("Invalid sub-choice\n");
                        break;
                }
                break;
        
            case 3: // Communication System Calls
                printf("1. pipe\n");
                printf("2. fifo\n");

                printf("Enter sub-choice: ");
                scanf("%d", &sub_choice);

                switch (sub_choice) {
                    case 1:
                        printf("Executing pipe system call...\n");
                        int pipe_fd[2];
                        if (pipe(pipe_fd) == 0) {
                            printf("Pipe created.\n");
                            close(pipe_fd[0]);
                            close(pipe_fd[1]);
                        } else {
                            printf("Error creating pipe.\n");
                        }
                        break;
                    case 2:
                        printf("Executing fifo system call...\n");
                        mkfifo("myfifo", 0666);
                        printf("FIFO created.\n");

                        // Create sender and receiver threads
            pthread_t sender_thread, receiver_thread;
            printf("Creating sender thread...\n");
            pthread_create(&sender_thread, NULL, sender, "myfifo");
            printf("Creating receiver thread...\n");
            pthread_create(&receiver_thread, NULL, receiver, "myfifo");

            // Wait for both threads to finish
            pthread_join(sender_thread, NULL);
            pthread_join(receiver_thread, NULL);

                        break;
                    default:
                        printf("Invalid sub-choice\n");
                        break;
                }
                break;

            case 4: // Information Related System Calls
                printf("Executing information related system call...\n");
                printf("Current User: %s\n", getenv("USER"));
                system("date");
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice\n");
                break;
        }

        printf("Press Enter to continue...");
        getchar(); // Consume the newline character left in the input buffer
        getchar(); // Wait for the user to press Enter
    }

    return 0;
}
