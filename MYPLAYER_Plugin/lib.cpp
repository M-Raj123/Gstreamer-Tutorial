#include "lib.h"
#include <iostream>
#include <gst/gst.h>
#include <pthread.h>
#include <bits/stdc++.h>
#include <string>

using namespace std;


int CustomData::setPath(CustomData *data, string name)
{
    /* gstreamer initialized*/
    gst_init(NULL,NULL);
    
    data->path =  "playbin uri=" + name;

    // building pipeline
    if(data->pipeline!=NULL)
    {
        cout<< "pipeline not null \n";
        gst_element_set_state (data->pipeline, GST_STATE_NULL);
        gst_object_unref(data->pipeline);
    }
    
    cout<< "pipeline null \n";  
    data->pipeline =  gst_parse_launch(data->path.c_str(),nullptr);
    pthread_t b_id;
    pthread_create(&b_id, NULL, busThread , data);
    
    return 0;
}

void CustomData::playState(CustomData *data)
{
    gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
}

void CustomData::pauseState(CustomData *data)
{
    gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
}

void CustomData::destroyResource(CustomData *data)
{
    /* Free resources */
	  gst_element_set_state (data->pipeline, GST_STATE_NULL);
    gst_object_unref (data->pipeline);
}

void CustomData::stateChangeToPlayagain(CustomData *data)
{
    data->event = gst_event_new_seek(1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_NONE, 0);  // move the start position
    gst_element_send_event(data->pipeline, data->event);
    gst_element_set_state(data->pipeline, GST_STATE_PLAYING); // Restart the pipeline
}

void CustomData::loop(CustomData *data, string loop)
{
    if(loop == "1")
    {
        data->repeat = 1;
    }
    else
    {
        data->repeat = 0;
    }
}

void CustomData::Print()
{       
    cout<< path << endl ;  
}



void * busThread(void *arg)
{

    CustomData *data = (CustomData *) arg;
    cout<< "inside thread \n";
    cout<< data->path<< endl;

    while(data->pipeline!=NULL) 
    {   
        // cout<< "inside while \n";
        data->bus = gst_element_get_bus(data ->pipeline);
        data->msg = gst_bus_timed_pop_filtered (data->bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
        
        /* handling error msg */
        if (data->msg != NULL) 
        {
            GError *err;
            gchar *debug_info;
            
            /* Parse message */
            switch (GST_MESSAGE_TYPE(data->msg)) 
            {
                case GST_MESSAGE_ERROR:
                {
                    gst_message_parse_error (data->msg, &err, &debug_info);
                    // g_printerr ("Error received from element %s: %s\n",GST_OBJECT_NAME (ptr->msg->src), err->message);
                    // g_printerr ("Debugging information: %s\n",debug_info ? debug_info : "none");
                    g_clear_error (&err);
                    g_free (debug_info);
                    break;
                }
                case GST_MESSAGE_EOS:
                {
                    g_print ("End-Of-Stream reached.\n");
                    if(data->repeat == 1 ) data->stateChangeToPlayagain(data);
                    else data->destroyResource(data);
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

    gst_message_unref (data->msg);
    gst_object_unref (data->bus);
    pthread_exit(NULL);

    return NULL;
}
