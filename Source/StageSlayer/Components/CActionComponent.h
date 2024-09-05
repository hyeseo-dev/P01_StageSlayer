#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "CActionComponent.generated.h"

class ACAction;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STAGESLAYER_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Action")
	void AddAction(TSubclassOf<ACAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Action")
	ACAction* GetAction(TSubclassOf<ACAction> ActionClass) const;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void RemoveAction(ACAction* ActionToRemove);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StopActionByName(AActor* Instigator, FName ActionName);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameplayTag")
	FGameplayTagContainer ActiveGameplayTags;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TArray<TSubclassOf<ACAction>> DefaultActions;

	UPROPERTY()
	TArray<ACAction*> Actions;
};
