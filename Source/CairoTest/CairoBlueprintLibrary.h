// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ThirdParty/cairo/Includes/cairo.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include <UnrealMathUtility.h>
#include "CairoBlueprintLibrary.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FCairoContext
{
	GENERATED_USTRUCT_BODY()

		cairo_t *context;
	unsigned char *buffer;
	uint32 buffersize;
	int32 imageWidth;
	int32 imageHeight;
};

UENUM(BlueprintType)
enum class EFontSlant
{
	FONT_SLANT_NORMAL	UMETA(DisplayName = "Normal"),
	FONT_SLANT_ITALIC	UMETA(DisplayName = "Italic"),
	FONT_SLANT_OBLIQUE	UMETA(DisplayName = "Oblique")
};

UENUM(BlueprintType)
enum class EFontWeight
{
	FONT_FONT_WEIGHT_NORMAL	UMETA(DisplayName = "Normal"),
	FONT_FONT_WEIGHT_BOLD	UMETA(DisplayName = "Bold"),
};

/**
 * 
 */
UCLASS()
class CAIROTEST_API UCairoBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void CreateSurface(int32 imageWidth, int32 imageHeight, FCairoContext& context);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static UTexture2D* CreateTexture(FCairoContext context);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void DestroySurface(FCairoContext context);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void SetSourceColor(FCairoContext context, FColor color);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void SetLineWidth(FCairoContext context, float width);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void DrawLine(FCairoContext context, FVector2D start, FVector2D end);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void DrawRectangle(FCairoContext context, FVector2D location, FVector2D size, bool filled);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void DrawCircle(FCairoContext context, FVector2D location, float radius, bool filled);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void DrawRoundedRectangle(FCairoContext context, FVector2D location, FVector2D size, float corner_radius, bool filled);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void SelectFont(FCairoContext context, FName family, float size, EFontSlant slant, EFontWeight weight);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void DrawText(FCairoContext context, FString text, FVector2D location);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Cairo")
	static void GetTextSize(FCairoContext context, FString text, FVector2D& size);
};
