#pragma once

#include "FixedTickMassProcessor.h"
#include "MyProcessor.generated.h"


UCLASS()
class MASSBUGREPRODUCER_API UMyProcessorA : public UFixedTickMassProcessor
{
	GENERATED_BODY()

public:
	UMyProcessorA();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager &EntityManager, FMassExecutionContext &Context) override;

	FMassEntityQuery EntityQuery;

	virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const override { return false; }
};
