#include<stdio.h>
#include<unistd.h>
#include<gst/gst.h>
#include<pthread.h>

void* myThread(void *arg)
{
    while(1)
    {
        printf(" running.. \n");
    }
  
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t t_id; 
    pthread_create(&t_id, NULL, myThread , NULL);
    pthread_join(t_id,NULL);

    return 0;

}
