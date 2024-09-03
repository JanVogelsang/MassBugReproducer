#pragma once

#include "MassSubsystemBase.h"
#include "MassExternalSubsystemTraits.h"
#include "MassEntityConfigAsset.h"
#include "MySubsystem.generated.h"


UCLASS()
class MASSBUGREPRODUCER_API UMySubsystem : public UMassSubsystemBase
{
	GENERATED_BODY()

public:
	UMySubsystem();

	virtual void Initialize(FSubsystemCollectionBase &Collection) override;

	virtual void OnWorldBeginPlay(UWorld &InWorld) override;

	void SpawnEntities(int32 Num);
	void DespawnEntity(FMassExecutionContext& Context);
	int32 GetNumEntities() const{ return Handles.Num(); }

protected:
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override final { return WorldType == EWorldType::Game || WorldType == EWorldType::PIE; }

	UPROPERTY(Transient)
	TObjectPtr<class UMassSpawnerSubsystem> SpawnerSubsystem;

	UPROPERTY(Transient)
	FMassEntityConfig MyEntityConfig;
	
	UPROPERTY(Transient)
	TArray<FMassEntityHandle> Handles;
};

template <>
struct TMassExternalSubsystemTraits<UMySubsystem> final
{
	enum
	{
		GameThreadOnly = true
	};
};
