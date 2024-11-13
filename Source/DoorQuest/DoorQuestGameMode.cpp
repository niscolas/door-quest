// Copyright Epic Games, Inc. All Rights Reserved.

#include "DoorQuestGameMode.h"
#include "DoorQuestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADoorQuestGameMode::ADoorQuestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
