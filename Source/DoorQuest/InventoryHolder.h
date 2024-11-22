#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "ItemTypeDataAsset.h"
#include "UObject/Interface.h"
#include "InventoryHolder.generated.h"

UINTERFACE(MinimalAPI)

class UInventoryHolder : public UInterface {
    GENERATED_BODY()
};

class DOORQUEST_API IInventoryHolder {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory")
    bool TryGetAmountForItemType(UItemTypeDataAsset *ItemType,
                                 int &Amount) const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory")
    bool AddAmountForItemType(UItemTypeDataAsset *ItemType, int Amount);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory")
    bool DecreaseAmountForItemType(UItemTypeDataAsset *ItemType, int Amount);
};
