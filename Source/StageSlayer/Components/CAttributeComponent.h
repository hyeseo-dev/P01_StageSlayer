#include "Components/ActorComponent.h"
#include "CAttributeComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STAGESLAYER_API UCAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCAttributeComponent();
protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }

	void IncreaseHealth(float InAmount);
	void DcreaseHealth(float InAmount);

	void SetMove();
	void SetStop();

private:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MaxHealth;

private:
	bool bCanMove;
	float CurrentHealth;
};