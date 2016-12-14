// Fill out your copyright notice in the Description page of Project Settings.

#include "Thor.h"
#include "LandMine.h"
#include "ThorCharacter.h"
#include "ThorMath.h"

// Sets default values
ALandMine::ALandMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LandMineRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LandMineRoot"));
	RootComponent = LandMineRoot;

	// Set up random X and Y sizes for mine
	int randX = ThorMath::RandomRange(MinSizeLimit, MaxSizeLimit);
	int randY = ThorMath::RandomRange(MinSizeLimit, MaxSizeLimit);

	// Set up the static mesh of the floor
	LandMineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LandMineMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LandMineVisualAsset(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	if (LandMineVisualAsset.Succeeded())
	{
		LandMineMesh->SetStaticMesh(LandMineVisualAsset.Object);
		LandMineMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.f));
		LandMineMesh->SetWorldScale3D(FVector(randX, randY, Height));
	}
	// Set up the material of the mine mesh
	static ConstructorHelpers::FObjectFinder<UMaterial> LandMineMaterial(TEXT("/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel"));
	if (LandMineMaterial.Succeeded())
	{
		LandMineMesh->SetMaterial(0, LandMineMaterial.Object);
	}
	LandMineMesh->SetupAttachment(LandMineRoot);

	// Setup Trigger Box
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MineTriggerBox"));
	TriggerBox->SetBoxExtent(FVector(100.f*randX, 100.f*randY, 100.f*Height), true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALandMine::OnPlayerEnterTriggerBox);
	TriggerBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	TriggerBox->SetupAttachment(LandMineRoot);

	// Find explosion emitter
	//particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MineExplosion"));

	//Explosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MineExplosion"));

}

// Called when the game starts or when spawned
void ALandMine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALandMine::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// Despawn if far enough from world origin
	UWorld* World = GetWorld();
	FVector MineLocation = GetActorLocation();
	if (MineLocation.X < World->OriginLocation.X - 50000)
	{
		DeleteLandMine();
	}
}

void ALandMine::OnPlayerEnterTriggerBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweetResult)
{
	OtherActor = Cast<AThorCharacter>(OtherActor);
	if (OtherActor != NULL)
	{
		float forceX = ThorMath::RandomRange(MinLaunchX,MaxLaunchX);
		float forceZ = ThorMath::RandomRange(MinLaunchZ, MaxLaunchZ);
		// Set launchforce to random X and Y forces
		FVector launchForce = FVector(forceX, 0.f, forceZ);
		// Apply Characters forward and upward velocity to launch force
		launchForce.X += OtherActor->GetVelocity().X/2;
		launchForce.Z += FMath::Abs(OtherActor->GetVelocity().Z / 2);
		Cast<AThorCharacter>(OtherActor)->LaunchCharacter(launchForce, true, true);
		
		// Generate explosion
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation(), GetActorRotation(),true);

		// Destroy landmine
		DeleteLandMine();
	}
}

void ALandMine::DeleteLandMine()
{
	Destroy();
}

