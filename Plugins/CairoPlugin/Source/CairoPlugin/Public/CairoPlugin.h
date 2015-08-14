// Some copyright should be here...

#pragma once

#include "ModuleManager.h"



class FCairoPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};