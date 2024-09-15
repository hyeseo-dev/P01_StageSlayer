#pragma once

#include "CoreMinimal.h"
#include "Melee/CMeleeBase.h"
#include "COneHand.generated.h"


UCLASS()
class STAGESLAYER_API ACOneHand : public ACMeleeBase
{
	GENERATED_BODY()

public:
	ACOneHand();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount;
};
