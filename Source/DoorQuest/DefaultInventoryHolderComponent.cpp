#include "DefaultInventoryHolderComponent.h"
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
    if (!TryGetAmountForItemType(ItemType, CurrentAmount)) {
        Inventory[ItemType] = Amount;
    } else {
        Inventory[ItemType] += Amount;
    }

    OnInventoryContentsChanged.Broadcast();

    return true;
}

bool UDefaultInventoryHolderComponent::DecreaseAmountForItemType_Implementation(
    UItemTypeDataAsset *ItemType, int DecreaseAmount) {
    int CurrentAmount;
    if (!TryGetAmountForItemType(ItemType, CurrentAmount)) {
        return false;
    }

    Inventory[ItemType] = FMath::Max(0, CurrentAmount - DecreaseAmount);
    OnInventoryContentsChanged.Broadcast();

    return true;
}
