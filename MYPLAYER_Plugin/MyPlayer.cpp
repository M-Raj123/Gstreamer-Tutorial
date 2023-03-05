#include"MyPlayer.h"
#include<iostream>

using namespace std;

namespace WPEFramework
{    
    namespace Plugin 
    {

    	  SERVICE_REGISTRATION(MyPlayer,1,0);    	

        MyPlayer::MyPlayer(): PluginHost::JSONRPC()
        {
           
        }

        MyPlayer::~MyPlayer()
        {

        }

        const string MyPlayer::Initialize(PluginHost::IShell* service )
        {
            //shared pointer initialized
            //initialize external library
            return (string());
        }

        void MyPlayer::Deinitialize(PluginHost::IShell* service )
        {
            //shared pointer deinitialized
            //deinitialize external library
           
        }

    }  // namespace plugin  
}  // namespace framework
