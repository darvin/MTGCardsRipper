// Fill out your copyright notice in the Description page of Project Settings.


#include "UFFScryfallLoader.h"
#include "Json.h"

// Sets default values for this component's properties
UUFFScryfallLoader::UUFFScryfallLoader()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUFFScryfallLoader::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUFFScryfallLoader::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// ...
}




void UUFFScryfallLoader::Fetch()
{
	UE_LOG(LogActor, Warning, TEXT("Fetching!"));
	UE_LOG(LogActor, Warning, TEXT("1!"));
	UE_LOG(LogActor, Warning, TEXT("334"));
	FString Path =  FPaths::ProjectContentDir() + TEXT("3cards.json");
	UE_LOG(LogActor, Warning, TEXT("%s"), *Path);

	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *Path);

	FString JsonStringWrapped = TEXT("{\"content\":")+JsonString+TEXT("}");
	// UE_LOG(LogActor, Warning, TEXT("%s"), JsonString);
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStringWrapped);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	// TArray<FAwesomeStruct> AwesomeStruct;

	TArray<TSharedPtr<FJsonValue>> CardsJson = JsonObject->GetArrayField(TEXT("content"));

	for (auto CardJson : CardsJson)
	{
		TSharedPtr<FJsonObject> CardObject;
		CardJson->TryGetObject(*&CardObject);
		
		FString CardName = CardObject->GetStringField(TEXT("name"));
	}

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
		}

		// GenerateStructsFromJson(AwesomeStructs, JsonObject);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
		}
	}

}

