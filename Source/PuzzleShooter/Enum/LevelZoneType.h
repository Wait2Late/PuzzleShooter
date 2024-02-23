#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class ELevelZoneType : uint8
{
	Level_0 UMETA(DisplayName = "Level 0"),
	Level_1 UMETA(DisplayName = "Level 1"),
	Level_2 UMETA(DisplayName = "Level 2"),
	Level_3 UMETA(DisplayName = "Level 3"),
	Level_4 UMETA(DisplayName = "Level 4"),
	
};
