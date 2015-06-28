// Fill out your copyright notice in the Description page of Project Settings.

#include "CairoTest.h"
#include "CairoBlueprintLibrary.h"

void UCairoBlueprintLibrary::CreateSurface(int32 imageWidth, int32 imageHeight, FCairoContext& context)
{
	if (imageWidth > 0 && imageHeight > 0)
	{
		int stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, imageWidth);
		context.buffersize = imageWidth * stride;
		context.buffer = (unsigned char *)FMemory::Malloc(context.buffersize);
		cairo_surface_t *surface = cairo_image_surface_create_for_data(context.buffer, CAIRO_FORMAT_ARGB32, imageWidth, imageHeight, stride);
		context.context = cairo_create(surface);
		cairo_set_source_rgba(context.context, 1, 1, 1, 0);
		cairo_set_operator(context.context, CAIRO_OPERATOR_SOURCE);
		cairo_paint(context.context);
		cairo_set_source_rgba(context.context, 0, 0, 0, 1);
		context.imageWidth = imageWidth;
		context.imageHeight = imageHeight;
	}
}

void UCairoBlueprintLibrary::DestroySurface(FCairoContext context)
{
	if (context.context != NULL)
	{
		cairo_destroy(context.context);
		FMemory::Free(context.buffer);
		context.context = NULL;
		context.buffersize = 0;
		context.buffer = NULL;
		context.imageWidth = 0;
		context.imageHeight = 0;
	}
}

UTexture2D* UCairoBlueprintLibrary::CreateTexture(FCairoContext context)
{
	if (context.context != NULL)
	{
		UTexture2D*	texture = UTexture2D::CreateTransient(context.imageWidth, context.imageHeight);
		texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
		texture->SRGB = 0;
		FTexture2DMipMap& Mip = texture->PlatformData->Mips[0];
		void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
		FMemory::Memcpy(Data, context.buffer, context.buffersize);
		Mip.BulkData.Unlock();
		texture->UpdateResource();
		return texture;
	}
	return NULL;
}

void UCairoBlueprintLibrary::SetSourceColor(FCairoContext context, FColor color)
{
	if (context.context != NULL) {
		cairo_set_source_rgba(context.context, color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0);
	}
}

void UCairoBlueprintLibrary::SetLineWidth(FCairoContext context, float width)
{
	if (context.context != NULL) {
		cairo_set_line_width(context.context, width);
	}
}

void UCairoBlueprintLibrary::DrawLine(FCairoContext context, FVector2D start, FVector2D end)
{
	if (context.context != NULL) {
		cairo_move_to(context.context, start.X, start.Y);
		cairo_line_to(context.context, end.X, end.Y);
		cairo_stroke(context.context);
	}
}

void UCairoBlueprintLibrary::DrawRectangle(FCairoContext context, FVector2D location, FVector2D size, bool filled=false) 
{
	if (context.context != NULL) {
		cairo_rectangle(context.context, location.X, location.Y, size.X, size.Y);

		if (filled)
			cairo_fill(context.context);
		else
			cairo_stroke(context.context);
	}
}

void UCairoBlueprintLibrary::DrawCircle(FCairoContext context, FVector2D location, float radius, bool filled)
{
	if (context.context != NULL) {
		cairo_arc(context.context, location.X, location.Y, radius, 0, 359);

		if (filled)
			cairo_fill(context.context);
		else
			cairo_stroke(context.context);
	}
}

void UCairoBlueprintLibrary::DrawRoundedRectangle(FCairoContext context, FVector2D location, FVector2D size, float corner_radius, bool filled)
{
	if (context.context != NULL)
	{
		double aspect = size.X / size.Y;
		double radius = corner_radius / aspect;
		double degrees = PI / 180.0;

		cairo_new_sub_path(context.context);
		cairo_arc(context.context, location.X + size.X - radius, location.Y + radius, radius, -90 * degrees, 0 * degrees);
		cairo_arc(context.context, location.X + size.X - radius, location.Y + size.Y - radius, radius, 0 * degrees, 90 * degrees);
		cairo_arc(context.context, location.X + radius, location.Y + size.Y - radius, radius, 90 * degrees, 180 * degrees);
		cairo_arc(context.context, location.X + radius, location.Y + radius, radius, 180 * degrees, 270 * degrees);
		cairo_close_path(context.context);
		
		if (filled)
			cairo_fill(context.context);
		else
			cairo_stroke(context.context);
	}
}

void UCairoBlueprintLibrary::SelectFont(FCairoContext context, FName family, float size, EFontSlant slant, EFontWeight weight)
{
	if (context.context != NULL)
	{
		cairo_font_slant_t c_slant;
		cairo_font_weight_t c_weight;

		switch (slant) 
		{
		case EFontSlant::FONT_SLANT_NORMAL:
			c_slant = CAIRO_FONT_SLANT_NORMAL;
			break;
		case EFontSlant::FONT_SLANT_ITALIC:
			c_slant = CAIRO_FONT_SLANT_ITALIC;
			break;
		case EFontSlant::FONT_SLANT_OBLIQUE:
			c_slant = CAIRO_FONT_SLANT_OBLIQUE;
			break;
		}

		switch (weight)
		{
		case EFontWeight::FONT_FONT_WEIGHT_NORMAL:
			c_weight = CAIRO_FONT_WEIGHT_NORMAL;
			break;
		case EFontWeight::FONT_FONT_WEIGHT_BOLD:
			c_weight = CAIRO_FONT_WEIGHT_BOLD;
			break;
		}

		cairo_select_font_face(context.context, family.GetPlainANSIString(), c_slant, c_weight);
		cairo_set_font_size(context.context, size);
	}
}

void UCairoBlueprintLibrary::DrawText(FCairoContext context, FString text, FVector2D location) {
	if (context.context != NULL)
	{
		cairo_move_to(context.context, location.X, location.Y);
		cairo_show_text(context.context, TCHAR_TO_UTF8(*text));
	}
}

void UCairoBlueprintLibrary::GetTextSize(FCairoContext context, FString text, FVector2D& size) {
	if (context.context != NULL)
	{
		cairo_text_extents_t extents;
		cairo_text_extents(context.context, TCHAR_TO_UTF8(*text), &extents);
		size.X = extents.width;
		size.Y = extents.height;
	}
}