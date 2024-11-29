#pragma once

#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "DoorQuest/InventoryHolder.h"
#include "DefaultInventoryHolderComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryContentsChanged);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class DOORQUEST_API UDefaultInventoryHolderComponent : public UActorComponent,
                                                       public IInventoryHolder {
    GENERATED_BODY()

public:
    UDefaultInventoryHolderComponent();

    UFUNCTION(BlueprintPure, Category = "Inventory")
    virtual bool
    TryGetAmountForItemType_Implementation(UItemTypeDataAsset *ItemType,
                                           int &Amount) const override;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    virtual bool
    AddAmountForItemType_Implementation(UItemTypeDataAsset *ItemType,
                                        int Amount) override;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    virtual bool
    DecreaseAmountForItemType_Implementation(UItemTypeDataAsset *ItemType,
                                             int DecreaseAmount) override;

private:
    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Inventory",
              meta = (AllowPrivateAccess))
    TMap<UItemTypeDataAsset *, int> Inventory;

    UPROPERTY(BlueprintAssignable,
              Category = "Inventory",
              meta = (AllowPrivateAccess))
    FInventoryContentsChanged OnInventoryContentsChanged;

    virtual void BeginPlay() override;

    virtual void
    TickComponent(float DeltaTime,
                  ELevelTick TickType,
                  FActorComponentTickFunction *ThisTickFunction) override;
};
