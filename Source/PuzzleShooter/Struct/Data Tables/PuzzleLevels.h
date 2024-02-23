#pragma once

#include "CoreMinimal.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"

#include "PuzzleLevels.generated.h"

USTRUCT(BlueprintType)
struct FPuzzleLevels : public FTableRowBase
{
	GENERATED_BODY()

	FPuzzleLevels();
	~FPuzzleLevels();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ELevelZoneType> LevelZoneType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> Password;
};
