#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)

class UInteractable : public UInterface {
    GENERATED_BODY()
};

class DOORQUEST_API IInteractable {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void ReceiveInteractionFocus(AActor *InteractorActor);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void LoseInteractionFocus(AActor *InteractorActor);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void ReceiveInteraction(AActor *InteractorActor);
};
