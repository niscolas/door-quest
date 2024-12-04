#pragma once

#include "DoorQuest/DefaultInventorySlotData.h"

static TArray<UDefaultInventorySlotData *>
CreateInventorySlotsFromItemMap(TMap<UItemTypeDataAsset *, int> ItemMap) {
    TArray<UDefaultInventorySlotData *> Result;

    for (auto InventorySlotKvp : ItemMap) {
        UDefaultInventorySlotData *NewInventorySlotData =
            NewObject<UDefaultInventorySlotData>();
        NewInventorySlotData->Icon = InventorySlotKvp.Key->GetIcon();
        NewInventorySlotData->Quantity = InventorySlotKvp.Value;

        Result.Add(NewInventorySlotData);
    }

    return Result;
}
