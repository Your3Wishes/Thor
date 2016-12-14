// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "ThorGameMode.generated.h"

UCLASS(minimalapi)
class AThorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AThorGameMode();

	void SpawnInitialLandMines();

	void SpawnLandMines();


};



