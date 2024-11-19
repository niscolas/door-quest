#pragma once

#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "CoreMinimal.h"
#include "DoorQuest/Interactor.h"
#include "Math/MathFwd.h"
#include "DefaultInteractorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class DOORQUEST_API UDefaultInteractorComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UDefaultInteractorComponent();

private:
    virtual void BeginPlay() override;

    virtual void
    TickComponent(float DeltaTime,
                  ELevelTick TickType,
                  FActorComponentTickFunction *ThisTickFunction) override;

    void FindNearbyInteractables();

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

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Interaction|Debug",
              meta = (AllowPrivateAccess))
    bool EnableDebugging;
};
