#pragma once

#include "MassProcessor.h"
#include "MassExternalSubsystemTraits.h"
#include "MassExecutionContext.h"
#include "MassSubsystemBase.h"
#include "MyProcessor.generated.h"


UCLASS()
class MASSBUGREPRODUCER_API UMySubsystem : public UMassSubsystemBase
{
	GENERATED_BODY()

protected:
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override final { return WorldType == EWorldType::Game || WorldType == EWorldType::PIE; }
};

template <>
struct TMassExternalSubsystemTraits<UMySubsystem> final
{
	enum
	{
		GameThreadOnly = true
	};
};

UCLASS()
class MASSBUGREPRODUCER_API UMyProcessorA : public UMassProcessor
{
	GENERATED_BODY()

public:
	UMyProcessorA()
	{
		// ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::AllNetModes);
		bAutoRegisterWithProcessingPhases = true;
		bRequiresGameThreadExecution = false;
	}
	

protected:
	virtual void ConfigureQueries() override
	{
		ProcessorRequirements.AddSubsystemRequirement<UMySubsystem>(EMassFragmentAccess::ReadWrite);
	}

	virtual void Execute(FMassEntityManager &EntityManager, FMassExecutionContext &Context) override
	{
		UMySubsystem &MySubsystem = Context.GetMutableSubsystemChecked<UMySubsystem>();
		check(IsInGameThread());
	}

	virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const override { return false; }
};
