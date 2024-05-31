#include "TouchDesignerConnectionActor.h"

ATouchDesignerConnectionActor::ATouchDesignerConnectionActor() {
	PrimaryActorTick.bCanEverTick = true;
}

void ATouchDesignerConnectionActor::BeginPlay() {
	Super::BeginPlay();

	Manager.Connect(
		Unreal_Engine_Port,
		&Touch_Designer_IP_Address,
		Touch_Designer_Port
	);
}

void ATouchDesignerConnectionActor::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) {
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	Manager.ReceiveValues();
	
	for (auto& kvp : Manager.Kvs) {
		ReceivedValues.Add(kvp.Key, kvp.Value);
	}

	for (auto& kvp : SentValues) {
		if (kvp.Key.IsEmpty()) {
			continue;
		}
		
		Manager.SendValue(TCHAR_TO_ANSI(*kvp.Key), kvp.Key.Len(), kvp.Value);
	}
}

void ATouchDesignerConnectionActor::BeginDestroy() {
	Super::BeginDestroy();

	bool _ = Manager.Disconnect();
}
