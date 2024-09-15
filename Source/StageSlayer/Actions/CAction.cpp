#include "CAction.h"
#include "Global.h"
#include "Components/CActionComponent.h"

bool ACAction::CanStart_Implementation(AActor* InstigatorActor)
{
	if (IsRunning())
	{
		return false;
	}

	UCActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	return true;
}

void ACAction::StartAction_Implementation(AActor* InstigatorActor)
{
	UCActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantTags);

	bIsRunning = true;

	Comp->OnActionStarted.Broadcast(Comp, this);
}

void ACAction::StopAction_Implementation(AActor* InstigatorActor)
{
	UCActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantTags);

	bIsRunning = false;

	Comp->OnActionStoppted.Broadcast(Comp, this);
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

