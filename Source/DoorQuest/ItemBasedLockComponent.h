#pragma once

#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "DoorQuest/DefaultInventorySlotData.h"
#include "ItemTypeDataAsset.h"
#include "ItemBasedLockComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class DOORQUEST_API UItemBasedLockComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UItemBasedLockComponent();

    UFUNCTION(BlueprintCallable, Category = "Item Requirements")
    bool TryUnlock(AActor *InventoryHolderActor);

    UFUNCTION(BlueprintPure, Category = "Item Requirements")
    TArray<UDefaultInventorySlotData *> GetRequirementsAsInventorySlots() const;

private:
    virtual void BeginPlay() override;

    virtual void
    TickComponent(float DeltaTime,
                  ELevelTick TickType,
                  FActorComponentTickFunction *ThisTickFunction) override;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Item Requirements",
              meta = (AllowPrivateAccess))
    TMap<UItemTypeDataAsset *, int> RequirementsMap;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Item Requirements",
              meta = (AllowPrivateAccess))
    bool IsLocked;
};
