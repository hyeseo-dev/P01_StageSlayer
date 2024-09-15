#pragma once

#include "CoreMinimal.h"
#include "Actions/CAction.h"
#include "CAction_MeleeAttack.generated.h"

class UAnimMontage;
class UParticleSystem;

UCLASS()
class STAGESLAYER_API ACAction_MeleeAttack : public ACAction
{
	GENERATED_BODY()

public:
	ACAction_MeleeAttack();

public:
	virtual void StartAction_Implementation(AActor* InstigatorActor) override;

public:
	void PerformComboAttack(ACharacter* InstigatorCharacter);

	void ResetCombo();

protected:
	UPROPERTY(EditAnywhere, Category = "Action")
	TSubclassOf<AActor> MeleeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Action|Montage")
	UAnimMontage* FirstActionMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Action|Montage")
	UAnimMontage* SecondActionMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Action|Montage")
	UAnimMontage* TertiaryActionMontage;

	UPROPERTY(EditAnywhere, Category = "Action")
	FName HandSocketName;

	UPROPERTY(BlueprintReadOnly, Category = "Combo")
	int32 ComboCount;
};
