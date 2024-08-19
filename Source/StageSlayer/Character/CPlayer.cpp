#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACPlayer::ACPlayer()
{
	//Create Scene Component
	CHelpers::CreateSceneComponent(this, &SpringArmComp, "SpringArmComp", GetMesh());
	CHelpers::CreateSceneComponent(this, &CameraComp, "CameraComp", SpringArmComp);

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
	
}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACPlayer::OnTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayer::OnLookUp);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

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
