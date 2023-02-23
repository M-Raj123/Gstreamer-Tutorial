/* Structure to contain all our information */
struct custom_data {
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;
    GstEvent *event;
    char path[200];
};
