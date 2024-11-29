#pragma once

#include "CoreMinimal.h"

struct DOORQUEST_API DefaultInventorySlotData {
    DefaultInventorySlotData();
    ~DefaultInventorySlotData();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot")
    UTexture2D *Icon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot")
    int Quantity;
};
