#include<stdio.h>
#include<gst/gst.h>
int main(int argc,char *argv[])    // with arguments
{
    guint major,minor,micro,nano;  // unsigned integer datatype
    
    // printf("%d %d %d %d \n",major,minor,nano,macro); // o/p - 0 0 0 0
    
    /* init */
    gst_init(&argc,&argv);  

    gst_version(&major,&minor,&micro,&nano);
    
    printf("The Gstreamer version:%d.%d.%d.%d\n",major,minor,micro,nano);
    // The Gstreamer version:1.20.3.0
    
    return 0;
}
