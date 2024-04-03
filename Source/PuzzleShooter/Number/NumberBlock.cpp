// Fill out your copyright notice in the Description page of Project Settings.


#include "NumberBlock.h"

#include "EngineUtils.h"
#include "Numpad.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleShooter/PuzzleShooterProjectile.h"
#include "PuzzleShooter/Game Instance/NumbersGameInstance.h"
#include "../Subsystems/LevelZoneSubsystem.h"


// Sets default values
ANumberBlock::ANumberBlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetStaticMesh(CubeMeshRef);
	FTransform transform(FVector(1,1,1));
	StaticMeshComponent->SetWorldTransform(transform);
	// StaticMeshComponent->SetBoundsScale(0.25);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Cube"));
	BoxComponent->SetBoxExtent(FVector(1,1,1));
	BoxComponent->SetWorldTransform(FTransform(FVector(10,10,10)));
	BoxComponent->SetupAttachment(StaticMeshComponent);
	BoxComponent->SetBoundsScale(10);
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ANumberBlock::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ANumberBlock::BeginPlay()
{
	Super::BeginPlay();

	
	// OnInitializeLevelZone();
}




// Called every frame
void ANumberBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANumberBlock::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UNumbersGameInstance* NumberGI = GetGameInstance<UNumbersGameInstance>();

	

	
	const ULevelZoneSubsystem* levelZoneSubsystem = GetGameInstance<UNumbersGameInstance>()->GetSubsystem<ULevelZoneSubsystem>();
	const TEnumAsByte<ELevelZoneType> CurrentLevelZone = levelZoneSubsystem->CurrentLevelZone;
	

	if (CurrentLevelZone == this->LevelZone &&
		OtherActor->Implements<UHitNumberBlock>() &&
		NumberGI->Implements<UGameInstanceInterface>())
	{
		const int NumpadNumber = NumpadType.GetIntValue();
		switch (NumpadType)
		{
		/* case ENumpadType::NumPad_Backspace:
		// 	IGameInstanceInterface::Execute_BackSpace(NumberGI);
		// 	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
		// 		FString(TEXT("BACKSPACE")));
		// 	UpdateNumberUI();
		// 	break;*/
		case ENumpadType::NumPad_C:
			C_Erasure();
			break;
		default: //default is a numbered pad
			IGameInstanceInterface::Execute_SetNumber(NumberGI, NumpadNumber);
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
				FString::Printf(TEXT("Numpad type: %d"), NumpadNumber));
			break;
		}
		
		UpdateNumberUI();
		OtherActor->Destroy();
	}
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString(TEXT("Bullet touched me")));
}

void ANumberBlock::SetLevelZone(ELevelZoneType NewLevelZone)
{
	LevelZone = NewLevelZone;
}

void ANumberBlock::C_Erasure()
{
	UNumbersGameInstance* NumberGI = GetWorld()->GetGameInstance<UNumbersGameInstance>();
	IGameInstanceInterface::Execute_C(NumberGI);
	
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
		FString(TEXT("ERASED")));

	// UpdateNumberUI(); 
}

void ANumberBlock::OnInitializeLevelZone() // Not needed
{
	TArray<AActor*> OutActors;

	const TSubclassOf<ANumpad> NumPad;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), NumPad, OutActors);

	// GetAllChildActors()
	const AActor* ParentAttachedActor = this->GetAttachParentActor();

	for (const auto OutActor : OutActors)
	{
		if (OutActor == ParentAttachedActor)
		{
			// OutActors->
			// OutActors[0]->GetDefaultSubobjects(OutActors->);
			
		}
	}

	for (int i = 0; i < OutActors.Num(); ++i)
	{
		OutActors[i]->GetDefaultAttachComponent();
		
	}

	for (const ANumpad* Numpad : TActorRange<ANumpad>(GetWorld()))
		if (Numpad == GetParentActor())
			SetLevelZone(Numpad->LevelZone);


}