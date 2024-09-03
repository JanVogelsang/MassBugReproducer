#pragma once

#include "MassEntityTypes.h"
#include "MyFragments.generated.h"


USTRUCT()
struct MASSBUGREPRODUCER_API FMyFragment : public FMassFragment
{
	GENERATED_BODY()

	FVector2f Velocity;

	float Rotation = 0.f;
};
