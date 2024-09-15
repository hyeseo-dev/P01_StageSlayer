#pragma once

class UCapsuleComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;
class UAudioComponent;
class USoundCue;
class UCameraShake;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMeleeBase.generated.h"

UCLASS()
class STAGESLAYER_API ACMeleeBase : public AActor
{
	GENERATED_BODY()

public:
	ACMeleeBase();
	
protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	virtual void OnBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter) {};

	UFUNCTION()
	virtual void OnEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter) {};

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Attacking();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* ImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	TSubclassOf<UCameraShake> ImpactShake;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	float ImpactShakeInnerRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	float ImpactShakeOuterRadius;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UProjectileMovementComponent* MoveComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UAudioComponent* AudioComp;

};
