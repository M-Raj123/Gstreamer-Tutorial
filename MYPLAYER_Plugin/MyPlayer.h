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

#pragma once
#include "Module.h"
#include "lib.h"

namespace WPEFramework 
{
   namespace Plugin 
   {
        class MyPlayer : public PluginHost::IPlugin, public PluginHost::JSONRPC 
	{		
		public:
				
		        MyPlayer(); 
		        virtual ~MyPlayer();
			       
			// IPlugin methods
			virtual const string Initialize(PluginHost::IShell* service) override;
			virtual void Deinitialize(PluginHost::IShell* service) override;
			virtual string Information() const override ;

    			BEGIN_INTERFACE_MAP(MyPlayer)
    			INTERFACE_ENTRY(PluginHost::IPlugin)
			INTERFACE_ENTRY(PluginHost::IDispatcher)
    			END_INTERFACE_MAP
		
		public:

			// simple method  
			uint32_t sayHello(const JsonObject& request, JsonObject& response);
			uint32_t sample(const JsonObject& request, JsonObject& response);
		
                	uint32_t setUrl(const JsonObject& request, JsonObject& response);
			uint32_t play(const JsonObject& request, JsonObject& response);
			uint32_t pause(const JsonObject& request, JsonObject& response);
			uint32_t exit(const JsonObject& request, JsonObject& response);
			uint32_t loop(const JsonObject& request, JsonObject& response);
				
		private:

			MyPlayer(const MyPlayer&) = delete;
			MyPlayer& operator=(const MyPlayer&) = delete;
				
		public:
			CustomData *data = new CustomData;
		
	};

   } // namespace Plugin
} // namespace WPEFramework
