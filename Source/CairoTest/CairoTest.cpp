// Fill out your copyright notice in the Description page of Project Settings.

#include "CairoTest.h"
#include "../../ThirdParty/cairo/Includes/cairo.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, CairoTest, "CairoTest" );

class FCairoTestGameModule : public FDefaultGameModuleImpl 
{
//private:
//	cairo_t *cr;

	virtual void StartupModule() override
	{
		//cairo_surface_t *surface;

		//surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 120, 120);
		//cr = cairo_create(surface);
	}

	virtual void ShutdownModule()
	{
		//cairo_destroy(cr);
	}
};