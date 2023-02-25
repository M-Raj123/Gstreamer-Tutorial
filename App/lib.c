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

void stateChangeToPlayagain(struct custom_data *data)
{
    data->event = gst_event_new_seek(1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_NONE, 0);  // move the start position
    gst_element_send_event(data->pipeline, data->event);
    gst_element_set_state(data->pipeline, GST_STATE_PLAYING); 	// Restart the pipeline
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
        printf("4: close current video\n");
        printf("5. exit\n");

        scanf("%d",&n);
        printf("num: %d \n",n );

        if(n==5) 
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

/* Bus Thread */
void * busThread(void *arg)
{
    
    struct custom_data *ptr = (struct custom_data *) arg;
    
    while(ptr->pipeline!=NULL)
    {

        ptr->bus = gst_element_get_bus (ptr->pipeline);
        ptr->msg = gst_bus_timed_pop_filtered (ptr->bus, GST_CLOCK_TIME_NONE,GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
        
        /* handling error msg */
        if (ptr->msg != NULL) 
        {
            GError *err;
            gchar *debug_info;
            
            /* Parse message */
            switch (GST_MESSAGE_TYPE (ptr->msg)) 
            {
                case GST_MESSAGE_ERROR:
                {
                    gst_message_parse_error (ptr->msg, &err, &debug_info);
                    g_printerr ("Error received from element %s: %s\n",GST_OBJECT_NAME (ptr->msg->src), err->message);
                    g_printerr ("Debugging information: %s\n",debug_info ? debug_info : "none");
                    g_clear_error (&err);
                    g_free (debug_info);
                    break;
                }
                case GST_MESSAGE_EOS:
                {
                    g_print ("End-Of-Stream reached.\n");
                    stateChangeToPlayagain(ptr);   		// autoplay
                    break;
                }
                default:
                {
                    /* We should not reach here because we only asked for ERRORs and EOS */
                    g_printerr ("Unexpected message received.\n");
                    break;
                }
            }
    
        }
    }

    gst_message_unref (ptr->msg);
    gst_object_unref (ptr->bus);
}

