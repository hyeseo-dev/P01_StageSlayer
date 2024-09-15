#include "CAnimNotify_ResetCombo.h"
#include "Actions/CAction_MeleeAttack.h"

FString UCAnimNotify_ResetCombo::GetNotifyName_Implementation() const
{
	return "ResetCombo";
}

void UCAnimNotify_ResetCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ACAction_MeleeAttack* Melee = Cast<ACAction_MeleeAttack>(MeshComp->GetOwner());
	if (Melee)
	{
		Melee->ResetCombo();
	}

}