#include "CMeleeBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraShake.h"
#include "Components/AudioComponent.h"

// ������
ACMeleeBase::ACMeleeBase()
{
	// �浹�� ������ SphereComponent ����
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	//SphereComp->OnComponentHit.AddDynamic(this, &ACMeleeBase::OnActorHit); // �浹 �� ȣ���� �Լ� ���ε�
	RootComponent = CapsuleComp;
;

	// �ð��� ȿ���� ���� ParticleSystemComponent ����
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(CapsuleComp);

	// ����� ����� ���� AudioComponent ����
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(CapsuleComp);

	// Ÿ�� �� Shake ���� ���� (�⺻��)
	ImpactShakeInnerRadius = 200.0f;
	ImpactShakeOuterRadius = 500.0f;
}

// ���� ���� �� ȣ��Ǵ� �Լ�
void ACMeleeBase::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComp->OnComponentHit.AddDynamic(this, &ACMeleeBase::OnActorHit);
}

// �浹 �� ȣ��Ǵ� �Լ�
void ACMeleeBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// �浹�� ����� �����ϰ�, �ڽ��� �ƴ� ��� ó��
	if (OtherActor && OtherActor != this)
	{
		Attacking();
	}
}


void ACMeleeBase::Attacking_Implementation()
{
    if (!IsPendingKill())
    {
        if (ImpactVFX)
        {
            UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
        }

        if (ImpactSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
        }

        if (ImpactShake)
        {
            UGameplayStatics::PlayWorldCameraShake(this, ImpactShake, GetActorLocation(), ImpactShakeInnerRadius, ImpactShakeOuterRadius);
        }
    }
}

