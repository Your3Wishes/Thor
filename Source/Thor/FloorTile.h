// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

UCLASS()
class THOR_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Gets a transform for next place to spawn a tile
	FTransform GetAttachPoint();

	UPROPERTY(EditAnywhere)
    USceneComponent* FloorTileRoot;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FloorTileMesh;

	UPROPERTY(EditAnywhere)
	UArrowComponent* AttachPoint;

	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void OnPlayerEnterTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweetResult);

	UFUNCTION()
	void DeleteTile();

	
	
};

FTransform GetAttachPoint(UArrowComponent * AttachPoint);
