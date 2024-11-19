#include "DefaultInteractorComponent.h"
#include "CollisionQueryParams.h"
#include "DoorQuest/Interactable.h"
#include "HelperMacros.h"
#include "WorldCollision.h"

UDefaultInteractorComponent::UDefaultInteractorComponent() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UDefaultInteractorComponent::BeginPlay() {
    Super::BeginPlay();
}

void UDefaultInteractorComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FindNearbyInteractables();
}

void UDefaultInteractorComponent::FindNearbyInteractables() {
    UTIL_IF_NULL_LOG_AND_RETURN(LogTemp, Error, GetWorld());
    UTIL_IF_NULL_LOG_AND_RETURN(LogTemp, Error, DetectionOriginComponent);

    FVector OriginLocation = DetectionOriginComponent->GetComponentLocation();

    TArray<FHitResult> OverlapResults;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(DetectionOriginRadius);
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());

    bool bHasOverlaps = GetWorld()->SweepMultiByChannel(
        OverlapResults, OriginLocation, OriginLocation, FQuat::Identity,
        ECC_WorldDynamic, Sphere, QueryParams);

    if (bHasOverlaps) {
        for (const FHitResult &Result : OverlapResults) {
            AActor *OverlappedActor = Result.GetActor();
            if (OverlappedActor &&
                OverlappedActor->GetClass()->ImplementsInterface(
                    UInteractable::StaticClass())) {
                IInteractable::Execute_ReceiveInteraction(OverlappedActor,
                                                          GetOwner());
            }
        }
    }

    if (EnableDebugging) {
        DrawDebugSphere(GetWorld(), OriginLocation, DetectionOriginRadius, 32,
                        FColor::Green, false, 2.0f);
    }
}
