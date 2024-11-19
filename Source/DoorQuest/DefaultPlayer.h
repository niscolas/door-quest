#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "DefaultPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)

class ADefaultPlayer : public ACharacter {
    GENERATED_BODY()

public:
    ADefaultPlayer();

    FORCEINLINE class USpringArmComponent *GetCameraBoom() const {
        return CameraBoom;
    }

    FORCEINLINE class UCameraComponent *GetFollowCamera() const {
        return FollowCamera;
    }

private:
    UFUNCTION(BlueprintCallable,
              Category = "Player",
              meta = (AllowPrivateAccess))
    void Move(FVector2D MovementVector);

    UFUNCTION(BlueprintCallable,
              Category = "Player",
              meta = (AllowPrivateAccess))
    void Look(FVector2D LookAxisVector);

    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = Camera,
              meta = (AllowPrivateAccess))
    USpringArmComponent *CameraBoom;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = Camera,
              meta = (AllowPrivateAccess))
    UCameraComponent *FollowCamera;
};
