#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int arr[5],sum;
    int fd = open("System_Call/sum",O_RDONLY);
    for(int i = 0;i<5;i++)
    {
        read(fd,&arr[i],sizeof(arr[i]));
        sum = sum+arr[i];
        //printf("READs %d\n",arr[i]);
    }
    printf("%d\n",sum);
    close(fd);
    return 0;
}
