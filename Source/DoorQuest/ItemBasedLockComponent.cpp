#include "ItemBasedLockComponent.h"
#include "DoorQuest/DefaultInventorySlotData.h"
#include "DoorQuest/InventoryHelper.h"
#include "DoorQuest/InventoryHolder.h"
#include "HelperMacros.h"

UItemBasedLockComponent::UItemBasedLockComponent() {
}

void UItemBasedLockComponent::BeginPlay() {
    Super::BeginPlay();
}

void UItemBasedLockComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UItemBasedLockComponent::TryUnlock(AActor *InventoryHolderActor) {
    UTIL_RETURN_VALUE_IF(
        !InventoryHolderActor ||
            !InventoryHolderActor->Implements<UInventoryHolder>(),
        false);

    UTIL_RETURN_VALUE_IF(!IsLocked || RequirementsMap.Num() == 0, true);

    for (auto RequirementKvp : RequirementsMap) {
        UItemTypeDataAsset *TypeDataAsset = RequirementKvp.Key;
        int RequiredQuantity = RequirementKvp.Value;
        int ActualQuantity;

        UTIL_RETURN_VALUE_IF(
            (!IInventoryHolder::Execute_TryGetAmountForItemType(
                 InventoryHolderActor, TypeDataAsset, ActualQuantity) ||
             ActualQuantity < RequiredQuantity),
            false);

        IInventoryHolder::Execute_DecreaseAmountForItemType(
            InventoryHolderActor, TypeDataAsset, RequiredQuantity);
    }

    IsLocked = false;
    return true;
}

TArray<UDefaultInventorySlotData *>
UItemBasedLockComponent::GetRequirementsAsInventorySlots() const {
    return CreateInventorySlotsFromItemMap(RequirementsMap);
}
