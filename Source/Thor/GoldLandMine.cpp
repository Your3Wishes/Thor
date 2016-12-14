// Fill out your copyright notice in the Description page of Project Settings.

#include "Thor.h"
#include "GoldLandMine.h"

AGoldLandMine::AGoldLandMine()
{
	// Change the material of the mine mesh to gold
	static ConstructorHelpers::FObjectFinder<UMaterial> LandMineMaterial(TEXT("/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (LandMineMaterial.Succeeded())
	{
		LandMineMesh->SetMaterial(0, LandMineMaterial.Object);
	}
	LandMineMesh->SetupAttachment(LandMineRoot);

	// Override Launch Forces For Gold Mine
	MinLaunchX = 15000;
	MaxLaunchX = 50000;
	MaxLaunchZ = 9000;


}



