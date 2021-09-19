// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


//#include "Engine/DataTable.h"
//#include "Engine/Texture2D.h"
#include "Engine.h"
#include "CoreMinimal.h"
#include "Serialization/Csv/CsvParser.h"
#include <Runtime\Core\Public\Misc\FileHelper.h>
#include "Misc/Paths.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Regex.h"
#include "Containers/UnrealString.h"
#include "DataCore.generated.h"

UCLASS()
class XRDHTML_API ADataCore : public AActor
{
	GENERATED_BODY()
public:	
	ADataCore();
	TArray<FVector2D> data;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "CurveCore")
		int xMeshUnit;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "CurveCore")
		int yMeshUnit;
	float biasX=0, biasY=0;
	UFUNCTION(BlueprintCallable, Category = "CurveCore")
		void setBias(float x, float y);
	UFUNCTION(BlueprintCallable, Category = "CurveCore")
		void loadCurveCSV(FString fileName);
	UFUNCTION(BlueprintCallable, Category = "CurveCore")
		float interpolation(float x);
	UFUNCTION(BlueprintCallable, Category = "CurveCore")
		float maxY(float angleStart, float angleEnd);
	UFUNCTION(BlueprintCallable, Category = "CurveCore")
		TArray<FVector2D> generateSpectrum(float angleStart, float angleEnd, float angleStep, int height, int width);
	UFUNCTION(BlueprintCallable, Category = "CurveCore")
		TArray<FVector4> generateMesh(float angleStart, float angleEnd, int height, int width);
	UFUNCTION(BlueprintCallable, Category = "Crystal Structure")
		TArray<FVector> readCIFFile(FString filename);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TMap<FString, float> atom_radius;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
