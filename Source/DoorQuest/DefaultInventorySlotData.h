#pragma once

#include "CoreMinimal.h"
#include "ItemTypeDataAsset.h"
#include "UObject/NoExportTypes.h"
#include "DefaultInventorySlotData.generated.h"

UCLASS(BlueprintType)

class DOORQUEST_API UDefaultInventorySlotData : public UObject {
    GENERATED_BODY()

public:
    UDefaultInventorySlotData(){};
    UDefaultInventorySlotData(UTexture2D *PIcon, int PQuantity)
        : Icon(PIcon), Quantity(PQuantity){};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot")
    UTexture2D *Icon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot")
    UItemTypeDataAsset *TypeDataAsset;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot")
    int Quantity;
};
