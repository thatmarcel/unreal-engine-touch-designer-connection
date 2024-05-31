#pragma once

#include "CoreMinimal.h"
#include "TouchDesignerConnectionManager.h"
#include "Components/ActorComponent.h"
#include "TouchDesignerConnectionActor.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLANKTEST1_API ATouchDesignerConnectionActor : public AActor {
	GENERATED_BODY()
private:
	TouchDesignerConnectionManager Manager = TouchDesignerConnectionManager();
public:
	UPROPERTY(EditAnywhere, SimpleDisplay)
	FString Touch_Designer_IP_Address = FString(TEXT("127.0.0.1"));
	UPROPERTY(EditAnywhere, SimpleDisplay)
	uint16 Touch_Designer_Port = 39451;
	UPROPERTY(EditAnywhere, SimpleDisplay)
	uint16 Unreal_Engine_Port = 39452;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, double> ReceivedValues;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FString, double> SentValues;
	
	ATouchDesignerConnectionActor();
	
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
};
