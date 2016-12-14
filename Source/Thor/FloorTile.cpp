// Fill out your copyright notice in the Description page of Project Settings.

#include "Thor.h"
#include "FloorTile.h"
#include "Components/ArrowComponent.h"
#include "ThorCharacter.h"
#include "ThorGameMode.h"


// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorTileRoot = CreateDefaultSubobject<USceneComponent>(TEXT("FloorTileRoot"));
	RootComponent = FloorTileRoot;

	// Set up the static mesh of the floor
	FloorTileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorTileMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorVisualAsset(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	if (FloorVisualAsset.Succeeded())
	{
		FloorTileMesh->SetStaticMesh(FloorVisualAsset.Object);
		FloorTileMesh->SetRelativeLocation(FVector(500.f, 0.0f, 0.f));
		FloorTileMesh->SetWorldScale3D(FVector(10.f,10.f,0.1f));
	}
	// Set up the material of the floor mesh
	static ConstructorHelpers::FObjectFinder<UMaterial> FloorMaterial(TEXT("/Game/StarterContent/Materials/M_CobbleStone_Smooth.M_CobbleStone_Smooth"));
	if (FloorMaterial.Succeeded())
	{
		FloorTileMesh->SetMaterial(0,FloorMaterial.Object);
	}
	FloorTileMesh->SetupAttachment(FloorTileRoot);
	
	// Setup AttachPoint for next tile's spawn location
	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FloorAttachPoint"));
	AttachPoint->SetRelativeLocation(FVector(1000.f,0.f,0.f));
	AttachPoint->SetupAttachment(FloorTileRoot);

	// Setup Trigger Box
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetBoxExtent(FVector(32.f, 500.f, 10000.f),true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnPlayerEnterTriggerBox);
	TriggerBox->SetRelativeLocation(FVector(1000.f, 0.f, 200.f));
	TriggerBox->SetupAttachment(FloorTileRoot);
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorTile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FTransform AFloorTile::GetAttachPoint()
{
	return AttachPoint->GetComponentTransform();
}

void AFloorTile::OnPlayerEnterTriggerBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweetResult)
{
	OtherActor = Cast<AThorCharacter>(OtherActor);
	if (OtherActor != NULL)
	{
		//Cast<AThorGameMode>(GetWorld()->GetAuthGameMode())->AddFloorTile();
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AFloorTile::DeleteTile, 3.f, false);
	}
}

void AFloorTile::DeleteTile()
{
	Destroy();
}

