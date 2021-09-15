// Fill out your copyright notice in the Description page of Project Settings.


#include "UploadScore.h"

// Sets default values
AUploadScore::AUploadScore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUploadScore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUploadScore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUploadScore::AddRecord(FString record)
{
	records.Add(record);
}

FString AUploadScore::CheckGuestID(FString id)
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL("https://yqwu.site/app/XRD/HTML/login/checkGuestID.php?&id=" + id);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	HttpRequest->SetHeader("Content-Type", TEXT("application/json"));
	//HttpRequest->OnProcessRequestComplete().BindUObject(this, &AUploadScore::OnYourFunctionCompleted);
	HttpRequest->ProcessRequest();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &AUploadScore::OnYourFunctionCompleted);
	/*
	TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response = HttpRequest->GetResponse();
	int i = 0;
	while (true)
	{
		i++;
		int32 code = Response->GetResponseCode();
		if (code != 0)
			break;
		if (i == 100)
			break;
		FPlatformProcess::Sleep(0.1);
	}
	if (i == 100)
		return "´íÎó: ÍøÂçÇëÇó³¬Ê±.";
	return Response->GetContentAsString();
	*/
	return "Done";
}

FString AUploadScore::SendRecord(FString id, FString score)
{
	FString recordStr;
	for (auto record : records)
	{
		recordStr += record + "\n";
	}
	FString recordUrl = FGenericPlatformHttp::UrlEncode(recordStr);
	FString idUrl = FGenericPlatformHttp::UrlEncode(id);
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	
	HttpRequest->SetURL("https://yqwu.site/app/XRD/HTML/score/upload.php?key=dD999QlNCTA1yBq6&type=guest&details=" + recordUrl + "&id=" + id + "&score=" + score);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	HttpRequest->SetHeader("Content-Type", TEXT("application/json"));
	//HttpRequest->OnProcessRequestComplete().BindUObject(this, &AUploadScore::OnYourFunctionCompleted);
	HttpRequest->ProcessRequest();
	return "https://yqwu.site/app/XRD/HTML/score/upload.php?key=dD999QlNCTA1yBq6&type=guest&details=" + recordUrl + "&id=" + id + "&score=" + score;
}

void AUploadScore::OnYourFunctionCompleted(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	code = HttpResponse->GetResponseCode();
	res = HttpResponse->GetContentAsString();
}