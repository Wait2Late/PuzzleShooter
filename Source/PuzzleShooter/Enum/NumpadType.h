#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class ENumpadType : uint8
{
	NumPad_0 = 0 	 UMETA(DisplayName = "0"),
	NumPad_1 = 1 	 UMETA(DisplayName = "1"),
	NumPad_2 = 2 	 UMETA(DisplayName = "2"),
	NumPad_3 = 3 	 UMETA(DisplayName = "3"),
	NumPad_4 = 4 	 UMETA(DisplayName = "4"),
	NumPad_5 = 5 	 UMETA(DisplayName = "5"),
	NumPad_6 = 6 	 UMETA(DisplayName = "6"),
	NumPad_7 = 7 	 UMETA(DisplayName = "7"),
	NumPad_8=  8 	 UMETA(DisplayName = "8"),
	NumPad_9 = 9	 UMETA(DisplayName = "9"),
	NumPad_C		 UMETA(DisplayName = "C"),
	NumPad_Backspace UMETA(DisplayName = "Backspace")
	
	
};
