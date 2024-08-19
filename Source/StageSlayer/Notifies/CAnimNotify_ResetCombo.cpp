#include "CAnimNotify_ResetCombo.h"
#include "Character/CPlayer.h"

FString UCAnimNotify_ResetCombo::GetNotifyName_Implementation() const
{
	return "ResetCombo";
}

void UCAnimNotify_ResetCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ACPlayer* PC = Cast<ACPlayer>(MeshComp->GetOwner());
	if (PC)
	{
		PC->ResetComboCount();
	}

}