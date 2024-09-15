#include "CAction_MeleeAttack.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ACAction_MeleeAttack::ACAction_MeleeAttack()
{
	HandSocketName = "Muzzle_01";
	ComboCount = 0;
}

void ACAction_MeleeAttack::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);

	ACharacter* Character = Cast<ACharacter>(InstigatorActor);
	if (Character)
	{
		PerformComboAttack(Character);
	}
}

void ACAction_MeleeAttack::PerformComboAttack(ACharacter* InstigatorCharacter)
{
	
	if (ensure(MeleeClass))
	{
		ACharacter* Character = Cast<ACharacter>(InstigatorCharacter);
		switch (ComboCount)
		{
		case 0:
			if (FirstActionMontage)
			{
				Character->PlayAnimMontage(FirstActionMontage);
				ComboCount++;
			}
			break;
		case 1:
			if (SecondActionMontage)
			{
				Character->PlayAnimMontage(SecondActionMontage);
				ComboCount++;
			}
			break;
		case 2:
			if (TertiaryActionMontage)
			{
				Character->PlayAnimMontage(TertiaryActionMontage);
				ResetCombo();
			}
			break;
		}
	}

	//StopAction(InstigatorCharacter);
}

void ACAction_MeleeAttack::ResetCombo()
{
	ComboCount = 0;
}