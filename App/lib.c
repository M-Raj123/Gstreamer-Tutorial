#include<stdio.h>
#include<gst/gst.h>
#include"lib.h"

void toCreatePipeline(struct custom_data *data)
{

    if(data->pipeline!=NULL)
    {
        gst_element_set_state (data->pipeline, GST_STATE_NULL);
        gst_object_unref(data->pipeline);
    }

    strcpy(data->path, "playbin uri=");
    char s[100];
    scanf("%s",s);
    strcat(data->path,s);

    printf("path: %s\n",data->path);
    printf("path changed\n");
    
    /* Build the pipeline */
    data->pipeline = gst_parse_launch(data->path,NULL);  

}

void stateChangePlay(struct custom_data *data)
{
	gst_element_set_state (data->pipeline, GST_STATE_PLAYING);  //  Start playing 
}

void stateChangePause(struct custom_data *data)
{
	gst_element_set_state (data->pipeline, GST_STATE_PAUSED);   // video paused	
}

void stateChangeNull(struct custom_data *data)
{
	gst_element_set_state (data->pipeline, GST_STATE_NULL);     // set state NUll  
    gst_object_unref (data->pipeline);
}

void destroyResource(struct custom_data *data)
{
    /* Free resources */
	gst_element_set_state (data->pipeline, GST_STATE_NULL);
    gst_object_unref (data->pipeline);
}

/* controller thread */
void * ctrlThread(void *arg)
{

    struct custom_data *ptr = (struct custom_data *) arg;

    static int n,flag=0;
    
    pthread_t b_id;
    
    printf("inside the fun()\n");
    
    while(1)
    {

        printf("enter the choice:\n");
        printf("1: file path:\n");
        printf("2: play\n");
        printf("3: pause\n");
        printf("4: new path\n");
        printf("5: close current video\n");
        printf("6. exit\n");

        scanf("%d",&n);
        printf("num: %d \n",n );

        if(n==6) 
        {   
            if(!flag) 
            {
                destroyResource(ptr);
            }

            pthread_cancel(b_id);
            printf("exitt....\n");
            break;
        }

        printf("before switch....\n");

        switch(n)
        {
            case 1: 
            {       printf("construct pipeline\n");
                    toCreatePipeline(ptr);
                    pthread_create(&b_id, NULL, busThread , ptr);
                    break;
            }
            case 2: 
            {
                    printf("play\n");
                    stateChangePlay(ptr);
                    break;
            }
            case 3: 
            {
                    printf("pause\n");
                    stateChangePause(ptr);
                    break;
            }
            case 4: 
            {
                    printf("new path\n");
                    toCreatePipeline(ptr);  
                    break; 
            }
            case 5:
            {
                    printf("video close\n");
                    destroyResource(ptr);
                    flag=1;
                    printf("exit ---\n");
                    break;
            } 
            default: 
            {
                printf("exit switch\n");
                break;
            }
        }

    }
    return NULL;
}
