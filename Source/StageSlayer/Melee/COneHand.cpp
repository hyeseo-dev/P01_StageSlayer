#include "COneHand.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CActionComponent.h"

ACOneHand::ACOneHand()
{
	CapsuleComp->SetCapsuleSize(50.0f, 100.0f);
    CapsuleComp->SetupAttachment(RootComponent);
}

void ACOneHand::BeginPlay()
{
    CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ACOneHand::OnActorOverlap);

    Super::BeginPlay();
}

void ACOneHand::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UCActionComponent* ActionComp = Cast<UCActionComponent>(OtherActor->GetComponentByClass(UCActionComponent::StaticClass()));

        TArray<FHitResult> HitResults;
        FVector Start = GetActorLocation();
        FVector End = Start + GetActorForwardVector() * 150.0f;

        FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(50.0f, 100.0f);


        bool bHit = GetWorld()->SweepMultiByChannel(
            HitResults,
            Start,
            End,
            FQuat::Identity,
            ECC_Pawn,
            CapsuleShape
        );

        if (bHit)
        {
            for (auto& Hit : HitResults)
            {
                if (AActor* HitActor = Hit.GetActor())
                {
                    UGameplayStatics::ApplyDamage(HitActor, 50.0f, GetInstigatorController(), this, nullptr);
                }
            }
        }

		Attacking();

	}
}