#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "CAction.generated.h"

class UCActionComponent;

UCLASS()
class STAGESLAYER_API ACAction : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* InstigatorActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const;

	void SetOwningComponent(UCActionComponent* NewActionComp);

protected:
	UFUNCTION(BlueprintCallable, Category = "Action")
	UCActionComponent* GetOwningComponent() const;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTag")
	FGameplayTagContainer GrantTags;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayTag")
	FGameplayTagContainer BlockedTags;

	UPROPERTY()
	bool bIsRunning;

	UPROPERTY()
	UCActionComponent* ActionComp;
};
