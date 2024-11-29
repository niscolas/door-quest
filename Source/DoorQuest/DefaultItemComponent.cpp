#include "DefaultItemComponent.h"
#include "CoreGlobals.h"
#include "DoorQuest/InventoryHolder.h"
#include "HelperMacros.h"
#include "Logging/LogVerbosity.h"

UDefaultItemComponent::UDefaultItemComponent() {
}

void UDefaultItemComponent::BeginPlay() {
    Super::BeginPlay();
}

void UDefaultItemComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDefaultItemComponent::Pickup(AActor *PickupActor) {
    UTIL_IF_NULL_LOG_AND_RETURN(LogTemp, Error, TypeDataAsset);
    UTIL_IF_NULL_LOG_AND_RETURN(LogTemp, Error, PickupActor);
    UTIL_RETURN_IF(Quantity <= 0 ||
                   !PickupActor->GetClass()->ImplementsInterface(
                       UInventoryHolder::StaticClass()));

    IInventoryHolder::Execute_AddAmountForItemType(PickupActor, TypeDataAsset,
                                                   Quantity);
    PickedUp.Broadcast();
}
