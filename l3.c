#include <gst/gst.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
    GstElement *pipeline, *bin;
    GstBus *bus;
    GstMessage *msg;
    gst_init(&argc ,&argv);
    printf("initiated\n");  

     pipeline = gst_parse_launch("playbin uri=file:///home/raj/Downloads/sintel_trailer-480p.webm",NULL);   // local disk filepath
        
     GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline");
     gst_element_set_state (pipeline, GST_STATE_PLAYING);

     /* Wait until error or EOS */
     bus = gst_element_get_bus (pipeline);
     msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

     /* handling error msg */
     if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR) 
     {
       g_error ("An error occurred! Re-run with the GST_DEBUG=*:WARN environment variable set for more details.\n");
     }
  
  /* Free resources */
  gst_message_unref (msg);
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  return 0; 
}

