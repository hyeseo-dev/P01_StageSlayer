#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CAttributeComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"

ACPlayer::ACPlayer()
{
	//Create Scene Component
	CHelpers::CreateSceneComponent(this, &SpringArmComp, "SpringArmComp", GetMesh());
	CHelpers::CreateSceneComponent(this, &CameraComp, "CameraComp", SpringArmComp);

	//Create Actor Component
	CHelpers::CreateActorComponent(this, &AttributeComp, "AttributeComp");
	CHelpers::CreateActorComponent(this, &StateComp, "StateComp");
	CHelpers::CreateActorComponent(this, &MontagesComp, "MontagesComp");
	CHelpers::CreateActorComponent(this, &ActionComp, "ActionComp");

	//Component Settings
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi");
	if (MeshAsset)
	{
		GetMesh()->SetSkeletalMesh(MeshAsset);
	}

	//-> SpringArmComp
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 140));
	SpringArmComp->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;

	//-> Movmement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	ComboCount = 0;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	StateComp->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);
}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACPlayer::OnTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayer::OnLookUp);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &ACPlayer::OnRoll);
	PlayerInputComponent->BindAction("Evade", EInputEvent::IE_Released, this, &ACPlayer::OnEvade);

	//PlayerInputComponent->BindAction("OneHand", IE_Pressed, this, &ACPlayer::OnOneHand);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ACPlayer::PriamryAttack);

}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(ControlRotation).GetForwardVector();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(ControlRotation).GetRightVector();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnTurn(float Axis)
{
	float Rate = Axis * 45.f * GetWorld()->GetDeltaSeconds();

	AddControllerYawInput(Rate);
}

void ACPlayer::OnLookUp(float Axis)
{
	float Rate = Axis * 45.f * GetWorld()->GetDeltaSeconds();

	AddControllerPitchInput(Rate);
}

void ACPlayer::OnZoom(float Axis)
{
}

void ACPlayer::OnRoll()
{
	ActionComp->StartActionByName(this, "Roll");
}

void ACPlayer::OnEvade()
{
	CheckFalse(StateComp->IsIdleMode());
	CheckFalse(AttributeComp->IsCanMove());

	if (InputComponent->GetAxisValue("MoveForward") < 0.f)
	{

		StateComp->SetBackstepMode();
		return;
	}

	StateComp->SetRollMode();
}


void ACPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	FVector Start = GetActorLocation();
	FVector Target;

	if (GetVelocity().IsNearlyZero())
	{
		Target = Start + CameraComp->GetForwardVector().GetSafeNormal2D();
	}
	else
	{
		Target = Start + GetVelocity().GetSafeNormal2D();
	}

	FRotator ForceRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
	SetActorRotation(ForceRotation);

	MontagesComp->PlayRoll();
}

void ACPlayer::Begin_Backstep()
{
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	MontagesComp->PlayBackstep();
}

void ACPlayer::End_Roll()
{
	StateComp->SetIdleMode();
}

void ACPlayer::End_Backstep()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	StateComp->SetIdleMode();
}

void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Roll:
	{
		Begin_Roll();
	}
	break;
	case EStateType::Backstep:
	{
		Begin_Backstep();
	}
	break;
	}
}

void ACPlayer::PriamryAttack()
{
	switch (ComboCount)
	{
	case 0:
		PrimaryAction();
		ComboCount++;
		break;
	case 1:
		SecondaryAction();
		ComboCount++;
		break;
	case 2:
		TertiaryAction();
		break;
	}
}

void ACPlayer::PrimaryAction()
{
	if (PrimaryActionMontage)
	{
		PlayAnimMontage(PrimaryActionMontage);
	}
}

void ACPlayer::SecondaryAction()
{
	if (SecondaryActionMontage)
	{
		PlayAnimMontage(SecondaryActionMontage);
	}
}

void ACPlayer::TertiaryAction()
{
	if (TertiaryActionMontage)
	{
		PlayAnimMontage(TertiaryActionMontage);
	}
}

void ACPlayer::ResetComboCount()
{
	ComboCount = 0;
}
