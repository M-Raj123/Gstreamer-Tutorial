#include<stdio.h>
#include<unistd.h>
#include<gst/gst.h>
#include<pthread.h>
#include "lib.h"

int main(int argc, char* argv[])
{

    struct custom_data data; 
    
    /* Initialize GStreamer */
    gst_init(&argc ,&argv);
    printf("initiated\n");  

    pthread_t t_id; 
    pthread_create(&t_id, NULL, ctrlThread , &data);
    pthread_join(t_id,NULL);

    return 0;
}

