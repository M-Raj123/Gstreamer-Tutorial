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
           Register(_T("sayHello"),&MyPlayer::sayHello,this);
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
        
        
        uint32_t MyPlayer::sayHello(const JsonObject& parameters, JsonObject& response)
        {
            uint32_t result = Core::ERROR_NONE;
            // std::cout<< parameters ;
            // std::cout<< "Helloworld\n";
            return (result);
        }
        
    }  // namespace plugin  
}  // namespace framework
