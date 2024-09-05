#include "CAction.h"
#include "Components/CActionComponent.h"

void ACAction::StartAction_Implementation(AActor* InstigatorActor)
{
	UCActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantTags);

}

void ACAction::StopAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped : %s"), *GetNameSafe(this));

	UCActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantTags);
}

bool ACAction::IsRunning() const
{
	return bIsRunning;
}

UCActionComponent* ACAction::GetOwningComponent() const
{
	return Cast<UCActionComponent>(GetOuter());
}

void ACAction::SetOwningComponent(UCActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

