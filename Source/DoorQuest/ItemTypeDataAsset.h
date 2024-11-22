#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Unix/UnixPlatform.h"
#include "ItemTypeDataAsset.generated.h"

UCLASS()

class DOORQUEST_API UItemTypeDataAsset : public UPrimaryDataAsset {
    GENERATED_BODY()

public:
    FORCEINLINE UTexture2D *GetIcon() const {
        return Icon;
    }

private:
    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Item",
              meta = (AllowPrivateAccess))
    UTexture2D *Icon;
};
