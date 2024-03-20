// Fill out your copyright notice in the Description page of Project Settings.


#include "NumberBlock.h"

#include "Kismet/GameplayStatics.h"
#include "PuzzleShooter/PuzzleShooterProjectile.h"
#include "PuzzleShooter/Game Instance/NumbersGameInstance.h"




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
	UNumbersGameInstance* NumberGI = GetWorld()->GetGameInstance<UNumbersGameInstance>();
	const int NumpadNumber = NumpadType.GetIntValue();

	if (OtherActor->Implements<UHitNumberBlock>() && NumberGI->Implements<UGameInstanceInterface>())
	{
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
			UpdateNumberUI();
			break;
		}
		




		
		
		OtherActor->Destroy();

	}
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString(TEXT("Bullet touched me")));
}

void ANumberBlock::C_Erasure()
{
	UNumbersGameInstance* NumberGI = GetWorld()->GetGameInstance<UNumbersGameInstance>();
	IGameInstanceInterface::Execute_C(NumberGI);
	
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
		FString(TEXT("ERASED")));

	UpdateNumberUI(); 
}

// void ANumberBlock::OnInitializeLevelZone()
// {
// 	TArray<AActor*> OutActors;
//
// 	const TSubclassOf<ANumpad> NumPad;
// 	
// 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), NumPad, OutActors);
//
// 	const AActor* ParentAttachedActor = this->GetAttachParentActor();
//
// 	for (const auto OutActor : OutActors)
// 	{
// 		if (OutActor == ParentAttachedActor)
// 		{
//
// 			ANumpad* NumpadActor = NumPad.GetDefaultObject();;
// 			LevelZone = NumpadActor->GetLevelZone();
// 		}
// 	}
// 	
// }