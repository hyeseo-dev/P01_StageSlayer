#include "CMeleeBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraShake.h"
#include "Components/AudioComponent.h"

// 생성자
ACMeleeBase::ACMeleeBase()
{
	// 충돌을 감지할 SphereComponent 생성
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	//SphereComp->OnComponentHit.AddDynamic(this, &ACMeleeBase::OnActorHit); // 충돌 시 호출할 함수 바인딩
	RootComponent = CapsuleComp;
;

	// 시각적 효과를 위한 ParticleSystemComponent 생성
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(CapsuleComp);

	// 오디오 재생을 위한 AudioComponent 생성
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(CapsuleComp);

	// 타격 시 Shake 범위 설정 (기본값)
	ImpactShakeInnerRadius = 200.0f;
	ImpactShakeOuterRadius = 500.0f;
}

// 게임 시작 시 호출되는 함수
void ACMeleeBase::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComp->OnComponentHit.AddDynamic(this, &ACMeleeBase::OnActorHit);
}

// 충돌 시 호출되는 함수
void ACMeleeBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 충돌한 대상이 존재하고, 자신이 아닌 경우 처리
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

