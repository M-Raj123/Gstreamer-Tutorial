#include <iostream>
#include <gst/gst.h>
#include <pthread.h>
#include <string>

using namespace std;

class CustomData
{
    public:
        int repeat;
        string path;
        GstElement *pipeline = nullptr;
        GstBus *bus = nullptr;
        GstMessage *msg = nullptr;
        GstEvent *event;
        
        CustomData()
        {
            cout<< "Constructor" << endl ;
            
        }
        ~CustomData()
        {
            cout<< "Destructor" << endl ;
        }

    public:

        void Print();
        int setPath(CustomData *data, string name);
        void playState(CustomData *data);
        void pauseState(CustomData *data);
        void destroyResource(CustomData *data);
        void stateChangeToPlayagain(CustomData *data);
        int exit();
        void loop(CustomData *data, string loop);

};

void * busThread(void *arg);
