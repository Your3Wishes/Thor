// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.



#include "Thor.h"
#include "ThorGameMode.h"
#include "ThorHUD.h"
#include "ThorCharacter.h"
#include "LandMine.h"
#include "GoldLandMine.h"
#include "ThorMath.h"

AThorGameMode::AThorGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AThorHUD::StaticClass();

	UWorld* const World = GetWorld();

	if (World)
	{
		SpawnInitialLandMines();
	}

}



void AThorGameMode::SpawnInitialLandMines()
{
	for (int i = 0; i < 40; i++)
	{
		float randX = ThorMath::RandomRange(0, 2500.f) + (i*2500);
		float randY = ThorMath::RandomRange(-3000.f, 3000.f);

		FVector spawnLocation = FVector(randX, randY, 30.f);
		ALandMine* landMine = GetWorld()->SpawnActor<ALandMine>(ALandMine::StaticClass(), spawnLocation, FRotator::ZeroRotator);
	}


}

void AThorGameMode::SpawnLandMines()
{
	for (int i = 0; i < 40; i++)
	{
		float randX = ThorMath::RandomRange(0, 2500.f) + (i * 2500) + GetWorld()->OriginLocation.X;
		float randY = ThorMath::RandomRange(-3000.f, 3000.f);

		float randGoldMine = ThorMath::RandomRange(0, 100);

		FVector spawnLocation = FVector(randX, randY, 30.f);
		// Spawn Gold Mine
		if (randGoldMine <= 10)
		{
			AGoldLandMine* goldLandMine = GetWorld()->SpawnActor<AGoldLandMine>(AGoldLandMine::StaticClass(), spawnLocation, FRotator::ZeroRotator);
		}
		else
			ALandMine* landMine = GetWorld()->SpawnActor<ALandMine>(ALandMine::StaticClass(), spawnLocation, FRotator::ZeroRotator);
	}

}





