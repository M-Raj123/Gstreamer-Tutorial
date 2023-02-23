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

