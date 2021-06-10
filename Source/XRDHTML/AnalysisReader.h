// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "GameFramework/Actor.h"
#include "XmlFile.h"
#include "AnalysisReader.generated.h"


USTRUCT(BlueprintType)
struct FHitMaterial
{
	GENERATED_BODY()
	FHitMaterial()        // this is your default constructor which is required for a USTRUCT definition
	{
		// initialize things here if desired or required
	}
	UPROPERTY(BlueprintReadWrite)
		FString id;
	UPROPERTY(BlueprintReadWrite)
		FString Formula;
	UPROPERTY(BlueprintReadWrite)
		FString FOM;
	UPROPERTY(BlueprintReadWrite)
		FString yScaling;
	UPROPERTY(BlueprintReadWrite)
		FString dScaling;
	UPROPERTY(BlueprintReadWrite)
		FString xOffset;
	UPROPERTY(BlueprintReadWrite)
		FString Card;
	UPROPERTY(BlueprintReadWrite)
		FString dILineCount;
	UPROPERTY(BlueprintReadWrite)
		FString QualityMark;
	UPROPERTY(BlueprintReadWrite)
		FString Source;
	UPROPERTY(BlueprintReadWrite)
		FString SpaceGroup;
	UPROPERTY(BlueprintReadWrite)
		FString PearsonSymbol;
	UPROPERTY(BlueprintReadWrite)
		FString PIR;
	UPROPERTY(BlueprintReadWrite)
		FString Density;
	UPROPERTY(BlueprintReadWrite)
		FString FormulaUnits;
	UPROPERTY(BlueprintReadWrite)
		FString a;
	UPROPERTY(BlueprintReadWrite)
		FString b;
	UPROPERTY(BlueprintReadWrite)
		FString c;
	UPROPERTY(BlueprintReadWrite)
		FString alpha;
	UPROPERTY(BlueprintReadWrite)
		FString beta;
	UPROPERTY(BlueprintReadWrite)
		FString gamma;
	UPROPERTY(BlueprintReadWrite)
		FString volume;
	UPROPERTY(BlueprintReadWrite)
		FString CSDNumber;
};

USTRUCT(BlueprintType)
struct FPDFCard
{
	GENERATED_BODY()
	FPDFCard()
	{

	}
	UPROPERTY(BlueprintReadWrite)
		TArray<FVector2D> peaks;
	UPROPERTY(BlueprintReadWrite)
		TArray<FString> infos;
};


UCLASS()
class XRDHTML_API AAnalysisReader : public AActor
{
	GENERATED_BODY()
	
public:	
	FXmlFile* HitList;
	// Sets default values for this actor's properties
	AAnalysisReader();
	UFUNCTION(BlueprintCallable, Category = "AnalysisReader")
		FPDFCard LoadPDFFile(const FString &cardpath);
	UFUNCTION(BlueprintCallable, Category = "AnalysisReader")
		void LoadXMLFile(const FString &filename);
		
	UFUNCTION(BlueprintCallable, Category = "AnalysisReader")
		TArray<FHitMaterial> GetHitList();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
