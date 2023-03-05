#pragma once
#include "Module.h"

namespace WPEFramework 
{
   namespace Plugin 
   {
      class MyPlayer : public PluginHost::IPlugin
                     , public PluginHost::JSONRPC {

			private:

				MyPlayer(const MyPlayer&) = delete;
				MyPlayer& operator=(const MyPlayer&) = delete;
				

			public:

				MyPlayer(); 
			  virtual ~MyPlayer();     
		  
	 			// IPlugin methods
	 			virtual const string Initialize(PluginHost::IShell* service) override;
		 		virtual void Deinitialize(PluginHost::IShell* service) override;
	 			virtual string Information() const override { return {}; };


    		BEGIN_INTERFACE_MAP(MyPlayer)
    		INTERFACE_ENTRY(PluginHost::IPlugin)
    		END_INTERFACE_MAP
		
		};

   } // namespace Plugin
} // namespace WPEFramework
