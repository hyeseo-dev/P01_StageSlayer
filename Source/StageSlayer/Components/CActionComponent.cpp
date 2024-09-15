#include "CActionComponent.h"
#include "Global.h"
#include "Actions/CAction.h"

UCActionComponent::UCActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();
	for (TSubclassOf<ACAction> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}
}

void UCActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString Message = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, Message);

}

void UCActionComponent::AddAction(TSubclassOf<ACAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}
	ACAction* NewAction = NewObject<ACAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

ACAction* UCActionComponent::GetAction(TSubclassOf<ACAction> ActionClass) const
{
	for (ACAction* Action : Actions)
	{
		if (Action && Action->IsA(ActionClass))
		{
			return Action;
		}
	}

	return nullptr;
}

void UCActionComponent::RemoveAction(ACAction* ActionToRemove)
{
	if (!ensure(ActionToRemove && !ActionToRemove->IsRunning()))
	{
		return;
	}

	Actions.Remove(ActionToRemove);
}

bool UCActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (ACAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				Action->StartAction(Instigator);
				return true;
			}
		}
	}
	return false;
}

bool UCActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (ACAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}
	return false;
}