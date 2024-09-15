#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;
class UCAttributeComponent;
class UCMontagesComponent;
class UCActionComponent;

UCLASS()
class STAGESLAYER_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnTurn(float Axis);
	void OnLookUp(float Axis);

	void OnZoom(float Axis);

	void OnRoll();
	void OnEvade();

private:
	void PriamryAttack();

private:
	void PrimaryAction();
	void SecondaryAction();
	void TertiaryAction();

public:
	void ResetComboCount();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UAnimMontage* PrimaryActionMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UAnimMontage* SecondaryActionMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UAnimMontage* TertiaryActionMontage;

private:
	int32 ComboCount;
};
