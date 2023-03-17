/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
*
* Copyright 2019 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/

#include "MyPlayer.h"
#include <string>
#include <iostream>
#include <plugins/System.h>

using namespace std;

namespace WPEFramework
{    
    namespace Plugin 
    {
    	SERVICE_REGISTRATION(MyPlayer,1,0);
    	
        MyPlayer::MyPlayer(): PluginHost::JSONRPC()
        {
            // simple method
            Register<JsonObject, JsonObject>(_T("sayHello"),&MyPlayer::sayHello,this);
            Register<JsonObject, JsonObject>(_T("sample"),&MyPlayer::sample,this);
    
            // JsonRpc call method
            Register<JsonObject, JsonObject>(_T("setUrl"),&MyPlayer::setUrl,this);
            Register<JsonObject, JsonObject>(_T("loop"),&MyPlayer::loop,this);
            Register<JsonObject, JsonObject>(_T("play"),&MyPlayer::play,this);
            Register<JsonObject, JsonObject>(_T("pause"),&MyPlayer::pause,this);
            Register<JsonObject, JsonObject>(_T("exit"),&MyPlayer::exit,this);

        }

        MyPlayer::~MyPlayer()
        {
        }

        const string MyPlayer::Initialize(PluginHost::IShell* service )
        {
            cout<< "Initializing \n" ;
            cout<<" ------------- MYPLAYER ---------------- \n";
            //shared pointer initialized
            //initialize external library
            return (string());
        }

        void MyPlayer::Deinitialize(PluginHost::IShell* service )
        {
            std::cout<< "Deinitializing \n" ;
            //shared pointer deinitialized
            //deinitialize external library 
        }


        /* virtual */ string MyPlayer::Information() const
        {
            // No additional info to report.
            // std::cout<< SERVICE_NAME << endl;
            return ((_T("The purpose of this plugin is provide ability to execute functional tests.\n")));
        }


        uint32_t MyPlayer::sayHello(const JsonObject& request, JsonObject& response) 
        {
            uint32_t result= Core::ERROR_NONE;
            response = "Hello";
            cout << request["output"].String() << endl;
            return result; 
        }

        uint32_t MyPlayer::sample(const JsonObject& request, JsonObject& response) 
        {
            uint32_t result= Core::ERROR_NONE;
            cout<< "sample() "<<request["message"].String()<<std::endl;
            response["status"] = "success";
            return result;  
        }

        uint32_t  MyPlayer::setUrl( const JsonObject& request, JsonObject& response)
        {
            uint32_t result= Core::ERROR_NONE;
            cout<<" ------------- path set ---------------- \n" ;
            string name = request["url"].String();
            string loop = request["repeat"].String();
            // cout<< "url -> " << name << endl;
            data->Print();
            data->setPath(data,name);
            response["message"] = "set path"; 
            data->Print();
            return result;
        }

        uint32_t MyPlayer::play(const JsonObject& request, JsonObject& response) 
        {
            uint32_t result= Core::ERROR_NONE;
            cout<<" ------------- Playing ---------------- \n";
            data->playState(data);
            data->Print();
            cout<< "-----------------\n";
            response["message"] = "video play";
            return result;  
        }
        
        uint32_t MyPlayer::pause(const JsonObject& request, JsonObject& response) 
        {
            uint32_t result= Core::ERROR_NONE;
            cout<<" ------------- Pause ---------------- \n";
            data->pauseState(data);
            data->Print();
            cout<< "-----------------\n";
            response["message"] = "video pause";
            return result;  
        }

        uint32_t MyPlayer::exit(const JsonObject& request, JsonObject& response) 
        {
            uint32_t result= Core::ERROR_NONE;
            cout<<" ------------ Exit ---------------- \n";
            data->destroyResource(data);
            data->Print();
            cout<< "-----------------\n";
            response["message"] = "player exit";
            return result;  
        }

        uint32_t MyPlayer::loop(const JsonObject& request, JsonObject& response) 
        {
            uint32_t result= Core::ERROR_NONE;
            cout<<" ------------- Repeat Mode ---------------- \n";
            string loop = request["repeat"].String();
            data->loop(data,loop);
            data->Print();
            cout<< "-----------------\n";
            if(loop == "1") response["message"] = "video loop mode on";
            else response["message"] = "loop mode off";
            return result;  
        }

    }  // namespace plugin  
}  // namespace framework
