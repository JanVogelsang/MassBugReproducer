#pragma once

#include "MassProcessor.h"
#include "FixedTickMassProcessor.generated.h"


UCLASS(Abstract)
class MASSBUGREPRODUCER_API UFixedTickMassProcessor : public UMassProcessor
{
	GENERATED_BODY()

protected:
	virtual void ConfigureQueries() override;

	// virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const override { return false; }
};
