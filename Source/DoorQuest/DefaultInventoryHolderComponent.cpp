#include "DefaultInventoryHolderComponent.h"
#include "DefaultInventorySlotData.h"
#include "ItemTypeDataAsset.h"

UDefaultInventoryHolderComponent::UDefaultInventoryHolderComponent() {
}

void UDefaultInventoryHolderComponent::BeginPlay() {
    Super::BeginPlay();
}

void UDefaultInventoryHolderComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UDefaultInventoryHolderComponent::TryGetAmountForItemType_Implementation(
    UItemTypeDataAsset *ItemType, int &Amount) const {
    if (const int *TempAmount = Inventory.Find(ItemType)) {
        Amount = *TempAmount;
        return true;
    }

    return false;
}

bool UDefaultInventoryHolderComponent::AddAmountForItemType_Implementation(
    UItemTypeDataAsset *ItemType, int Amount) {
    int CurrentAmount;

    if (!TryGetAmountForItemType_Implementation(ItemType, CurrentAmount)) {
        Inventory.Add(ItemType, Amount);
    } else {
        Inventory[ItemType] += Amount;
    }

    InventoryContentsChanged.Broadcast();

    return true;
}

bool UDefaultInventoryHolderComponent::DecreaseAmountForItemType_Implementation(
    UItemTypeDataAsset *ItemType, int DecreaseAmount) {
    int CurrentAmount;

    if (!TryGetAmountForItemType_Implementation(ItemType, CurrentAmount)) {
        return false;
    }

    Inventory[ItemType] = FMath::Max(0, CurrentAmount - DecreaseAmount);
    InventoryContentsChanged.Broadcast();

    return true;
}

TArray<UDefaultInventorySlotData *>
UDefaultInventoryHolderComponent::GetInventorySlots() const {
    TArray<UDefaultInventorySlotData *> Result;

    for (auto InventorySlotKvp : Inventory) {
        UDefaultInventorySlotData *NewInventorySlotData =
            NewObject<UDefaultInventorySlotData>();
        NewInventorySlotData->Icon = InventorySlotKvp.Key->GetIcon();
        NewInventorySlotData->Quantity = InventorySlotKvp.Value;

        Result.Add(NewInventorySlotData);
    }

    return Result;
}
