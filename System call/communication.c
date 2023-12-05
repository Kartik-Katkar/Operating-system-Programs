#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>  // Include this header for rand and srand
 

int main()
{
    int arr[5];
    for(int j = 0;j<5;j++)
    {
        arr[j]= rand()%10;
    }
    int fd = open("System_Call/sum",O_WRONLY);
    for(int i = 0;i<5;i++)
    {
        write(fd,&arr[i],sizeof(arr[i]));
        printf("Wrote %d\n",arr[i]);
    }
    close(fd);
    return 0;
}
