#pragma once

#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "CoreMinimal.h"
#include "DoorQuest/Interactor.h"
#include "Engine/EngineTypes.h"
#include "Math/MathFwd.h"
#include "DefaultInteractorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class DOORQUEST_API UDefaultInteractorComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UDefaultInteractorComponent();

private:
    UFUNCTION(BlueprintCallable,
              Category = "Interaction",
              meta = (AllowPrivateAccess))
    void FindNearbyInteractables();

    UFUNCTION(BlueprintCallable,
              Category = "Interaction",
              meta = (AllowPrivateAccess))
    void Interact();

    virtual void BeginPlay() override;

    virtual void
    TickComponent(float DeltaTime,
                  ELevelTick TickType,
                  FActorComponentTickFunction *ThisTickFunction) override;

    void RemoveFocusedInteractableFromOverlapResults(
        TArray<FHitResult> &OverlapResults);
    void FocusOn(AActor *InteractableActor);
    void RemoveCurrentFocus();

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Interaction",
              meta = (AllowPrivateAccess))
    USceneComponent *DetectionOriginComponent;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Interaction",
              meta = (AllowPrivateAccess))
    float DetectionOriginRadius = 100.f;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Interaction",
              meta = (AllowPrivateAccess))
    TEnumAsByte<ECollisionChannel> DetectionCollisionChannel = ECC_WorldStatic;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Interaction|Debug",
              meta = (AllowPrivateAccess))
    AActor *FocusedInteractableActor;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Interaction|Debug",
              meta = (AllowPrivateAccess))
    AActor *PreviousFocusedInteractableActor;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Interaction|Debug",
              meta = (AllowPrivateAccess))
    bool EnableDebugging;
};
