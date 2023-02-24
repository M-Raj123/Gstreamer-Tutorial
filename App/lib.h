/* Structure to contain all our information */
struct custom_data {
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;
    GstEvent *event;
    char path[200];
};

void toCreatePipeline(struct custom_data *data);
void stateChangePause(struct custom_data *data);
void stateChangePlay(struct custom_data *data);
void stateChangeNull(struct custom_data *data);
void destroyResource(struct custom_data *data);
void stateChangeToPlayagain(struct custom_data *data);
void msg(struct custom_data *data);
void * ctrlThread(void * arg);
void * busThread(void *arg);
