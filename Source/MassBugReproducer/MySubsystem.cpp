#include "MySubsystem.h"

#include "MassExecutionContext.h"
#include "MassSpawnerSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MySubsystem)


UMySubsystem::UMySubsystem()
{
	static ConstructorHelpers::FObjectFinder<UMassEntityConfigAsset> MyEntityConfigAsset(
	TEXT("/Script/MassSpawner.MassEntityConfigAsset'/Game/EC_MyEntityConfig.EC_MyEntityConfig'"));
	check(MyEntityConfigAsset.Succeeded());
	MyEntityConfig = MyEntityConfigAsset.Object->GetConfig();
}

void UMySubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
	Super::Initialize(Collection);

	// VfxSubsystem = Collection.InitializeDependency<UVfxSubsystem>();
	SpawnerSubsystem = Collection.InitializeDependency<UMassSpawnerSubsystem>();
}

void UMySubsystem::OnWorldBeginPlay(UWorld &InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	SpawnEntities(1);
}

void UMySubsystem::SpawnEntities(int32 Num)
{
	const auto& EntityTemplate = MyEntityConfig.GetOrCreateEntityTemplate(*GetWorld());
	SpawnerSubsystem->SpawnEntities(EntityTemplate, 1, Handles);
}

void UMySubsystem::DespawnEntity(FMassExecutionContext &Context)
{
	if (Handles.Num() > 0)
	{
		const int32 Idx = FMath::RandRange(0, Handles.Num() - 1);
		Context.Defer().DestroyEntity(Handles[Idx]);
		Handles.RemoveAt(Idx);
	}
}
