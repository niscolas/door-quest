#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemTypeDataAsset.h"
#include "DefaultItemComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickedUp);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class DOORQUEST_API UDefaultItemComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UDefaultItemComponent();

    UFUNCTION(BlueprintCallable, Category = "Item")
    void Pickup(AActor *PickupActor);

private:
    virtual void BeginPlay() override;

    virtual void
    TickComponent(float DeltaTime,
                  ELevelTick TickType,
                  FActorComponentTickFunction *ThisTickFunction) override;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Item",
              meta = (AllowPrivateAccess))
    UItemTypeDataAsset *TypeDataAsset;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Item",
              meta = (AllowPrivateAccess))
    int Quantity = 1;

    UPROPERTY(BlueprintAssignable,
              Category = "Item",
              meta = (AllowPrivateAccess))
    FPickedUp PickedUp;
};
