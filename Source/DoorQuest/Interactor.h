#pragma once

#include "CoreMinimal.h"
#include "DoorQuest/Interactable.h"
#include "UObject/Interface.h"
#include "Interactor.generated.h"

UINTERFACE(MinimalAPI)

class UInteractor : public UInterface {
    GENERATED_BODY()
};

class DOORQUEST_API IInteractor {
    GENERATED_BODY()
public:
    IInteractable *GetFocusedInteractable() const;
    void Interact();
    void Interact(IInteractable *Interactable);
};
