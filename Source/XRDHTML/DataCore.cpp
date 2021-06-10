// Fill out your copyright notice in the Description page of Project Settings.


#include "DataCore.h"

// Sets default values
ADataCore::ADataCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADataCore::BeginPlay()
{
	Super::BeginPlay();
	//loadCurveCSV("zirconium_data");
}

// Called every frame
void ADataCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADataCore::setBias(float x, float y)
{
	biasX = x;
	biasY = y;
}

void ADataCore::loadCurveCSV(FString fileName)
{
	FString csvFile = FPaths::GameContentDir() + "data/" + fileName + ".csv";
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, csvFile);
	if (FPaths::FileExists(csvFile))
	{
		FString FileContent;
		FFileHelper::LoadFileToString(FileContent, *csvFile);
		FCsvParser* csvfiles = new FCsvParser(FileContent);
		TArray<FString> t_str;
		TArray<TArray<const TCHAR*>> content = csvfiles->GetRows();
		for (TArray<const TCHAR*>& ite : content)
		{
			for (const TCHAR*& chr : ite)
			{
				t_str.Add(chr);
			}
		}
		for (int i = 0; i < t_str.Num(); i += 3)
		{
			FVector2D tempdata;
			tempdata.X = FCString::Atof(*t_str[i + 1]);
			tempdata.Y = FCString::Atof(*t_str[i + 2]);
			data.Add(tempdata);
		}
	}
	xMeshUnit = (data[data.Num()-1].X - data[0].X)/13;
	yMeshUnit = maxY(data[0].X, data[data.Num() - 1].X) / 7;
}


float ADataCore::interpolation(float x)
{
	for (auto i = 1; i < data.Num(); i++)
	{
		if (x >= data[i - 1].X && x <= data[i].X)
		{
			return data[i - 1].Y + (x - data[i - 1].X)*(data[i].Y - data[i - 1].Y) / (data[i].X - data[i - 1].X);
		}
	}
	return 0.;
}

float ADataCore::maxY(float angleStart, float angleEnd)
{
	float max = 0;
	for (FVector2D i : data)
	{
		if (i.X > angleStart && i.X < angleEnd && i.Y > max)
		{
			max = i.Y;
		}
	}
	return max;
}

TArray<FVector2D> ADataCore::generateSpectrum(float angleStart, float angleEnd, float angleStep, int height, int width)
{
	float max = 0;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(maxY(angleStart, angleEnd)));
	TArray<FVector2D> spectrum;
	float yunit = height / maxY(angleStart, angleEnd), xunit = width / (angleEnd - angleStart);
	for (float i = angleStart; i < angleEnd; i = i + angleStep)
	{
		spectrum.Add(FVector2D((i - angleStart)*xunit + biasX, height - (interpolation(i)*yunit) + biasY));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(max));
	return spectrum;
}

TArray<FVector4> ADataCore::generateMesh(float angleStart, float angleEnd, int height, int width)
{
	float xUnit = width / (angleEnd - angleStart), yUnit = height / maxY(angleStart, angleEnd);
	TArray<FVector4> meshLines;
	for (auto i = angleStart; i < angleEnd; i += xMeshUnit)
	{
		FVector4 xLine = FVector4(biasX + (i - angleStart)*xUnit, biasY + height, biasX + (i - angleStart)*xUnit, biasY);
		meshLines.Add(xLine);
	}
	for (float i = 0; i < maxY(angleStart, angleEnd); i += yMeshUnit)
	{
		FVector4 yLine = FVector4(biasX, biasY + (height - i*yUnit), biasX + width, biasY + (height - i*yUnit));
		meshLines.Add(yLine);
	}
	return meshLines;
}
