// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LandMine.generated.h"

UCLASS()
class THOR_API ALandMine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALandMine();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Root of land mine */
	UPROPERTY(EditAnywhere)
	USceneComponent* LandMineRoot;

	/** Mesh of land mine */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LandMineMesh;

	/** Trigger box for land mine collisions */
	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerBox;

	/** Minimum launch X velocity of land mine */
	UPROPERTY(EditAnywhere)
	int MinLaunchX = 2000;

	/** Maximum launch X velocity of land mine */
	UPROPERTY(EditAnywhere)
	int MaxLaunchX = 7000;

	/** Minimum launch Z velocity of land mine */
	UPROPERTY(EditAnywhere)
	int MinLaunchZ = 1000;

	/** Maximum launch Z velocity of land mine */
	UPROPERTY(EditAnywhere)
	int MaxLaunchZ = 4000;

	/** Maximum random x or y size of land mine */
	UPROPERTY(EditAnywhere)
	int MaxSizeLimit = 15;

	/** Minimum random x or y size of land mine */
	UPROPERTY(EditAnywhere)
	int MinSizeLimit = 5;

	/** Height of land mine */
	UPROPERTY(EditAnywhere)
	float Height = 1;

	UFUNCTION()
	void OnPlayerEnterTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweetResult);

	UFUNCTION()
	void DeleteLandMine();
	
};
