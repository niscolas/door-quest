#include "DefaultInteractorComponent.h"
#include "CollisionQueryParams.h"
#include "DoorQuest/Interactable.h"
#include "HelperMacros.h"
#include "WorldCollision.h"

UDefaultInteractorComponent::UDefaultInteractorComponent() {
}

void UDefaultInteractorComponent::BeginPlay() {
    Super::BeginPlay();
}

void UDefaultInteractorComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDefaultInteractorComponent::FindNearbyInteractables() {
    UTIL_IF_NULL_LOG_AND_RETURN(LogTemp, Error, GetWorld());
    UTIL_IF_NULL_LOG_AND_RETURN(LogTemp, Error, DetectionOriginComponent);

    FVector OriginLocation = DetectionOriginComponent->GetComponentLocation();

    TArray<FHitResult> OverlapResults;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(DetectionOriginRadius);
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());

    bool HasOverlaps = GetWorld()->SweepMultiByChannel(
        OverlapResults, OriginLocation, OriginLocation, FQuat::Identity,
        DetectionCollisionChannel, Sphere, QueryParams);

    if (EnableDebugging) {
        DrawDebugSphere(GetWorld(), OriginLocation, DetectionOriginRadius, 32,
                        FColor::Green, false, 2.0f);
    }

    if (!HasOverlaps) {
        RemoveCurrentFocus();
        return;
    }

    AActor *NearestInteractableActor = nullptr;
    float NearestInteractableActorDistance = FLT_MAX;

    for (const FHitResult &Result : OverlapResults) {
        AActor *OverlappedActor = Result.GetActor();

        UTIL_CONTINUE_IF(!OverlappedActor ||
                         !OverlappedActor->GetClass()->ImplementsInterface(
                             UInteractable::StaticClass()));

        float CurrentInteractableActorDistance =
            FVector::DistSquared(OverlappedActor->GetActorLocation(),
                                 GetOwner()->GetActorLocation());

        if (CurrentInteractableActorDistance <
            NearestInteractableActorDistance) {
            NearestInteractableActor = OverlappedActor;
            NearestInteractableActorDistance = CurrentInteractableActorDistance;
        }
    }

    if (!NearestInteractableActor) {
        RemoveCurrentFocus();
    } else {
        FocusOn(NearestInteractableActor);
    }
}

void UDefaultInteractorComponent::Interact() {
    UTIL_RETURN_IF(!FocusedInteractableActor);

    IInteractable::Execute_ReceiveInteraction(FocusedInteractableActor,
                                              GetOwner());
}

void UDefaultInteractorComponent::RemoveFocusedInteractableFromOverlapResults(
    TArray<FHitResult> &OverlapResults) {
    OverlapResults.RemoveAll([this](const FHitResult &OverlapResult) {
        return OverlapResult.GetActor() == FocusedInteractableActor;
    });
}

void UDefaultInteractorComponent::FocusOn(AActor *NewInteractableActor) {
    UTIL_RETURN_IF(!NewInteractableActor ||
                   FocusedInteractableActor == NewInteractableActor);

    RemoveCurrentFocus();
    IInteractable::Execute_ReceiveInteractionFocus(NewInteractableActor,
                                                   GetOwner());
    PreviousFocusedInteractableActor = FocusedInteractableActor;
    FocusedInteractableActor = NewInteractableActor;
}

void UDefaultInteractorComponent::RemoveCurrentFocus() {
    UTIL_RETURN_IF(!FocusedInteractableActor);

    IInteractable::Execute_LoseInteractionFocus(FocusedInteractableActor,
                                                GetOwner());
    FocusedInteractableActor = nullptr;
}
