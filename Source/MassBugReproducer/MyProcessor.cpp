#include "MyProcessor.h"
#include "MassCommonTypes.h"
#include "MassExecutionContext.h"
#include "MyFragments.h"
#include "MySubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MyProcessor)

UMyProcessorA::UMyProcessorA()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	bAutoRegisterWithProcessingPhases = true;
	bRequiresGameThreadExecution = false;

	ExecutionOrder.ExecuteInGroup = UE::Mass::ProcessorGroupNames::Behavior;
}

void UMyProcessorA::ConfigureQueries()
{
	Super::ConfigureQueries();
	EntityQuery.AddRequirement<FMyFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.RegisterWithProcessor(*this);

	ProcessorRequirements.AddSubsystemRequirement<UMySubsystem>(EMassFragmentAccess::ReadWrite);
}

void UMyProcessorA::Execute(FMassEntityManager &EntityManager, FMassExecutionContext &Context)
{
	UMySubsystem &MySubsystem = Context.GetMutableSubsystemChecked<UMySubsystem>();
	
	check(IsInGameThread());
	check(EntityQuery.GetNumMatchingEntities(EntityManager) == MySubsystem.GetNumEntities());

	UE_LOG(LogMass, Error, TEXT("Execute called. NumMatchedEntities: %d"), EntityQuery.GetNumMatchingEntities(EntityManager));
	
	EntityQuery.ForEachEntityChunk(
		EntityManager, Context, [&MySubsystem](FMassExecutionContext &Context)
		{
			UE_LOG(LogMass, Error, TEXT("ForEachEntityChunk"));
			const int32 NumEntities = Context.GetNumEntities();
			const TArrayView<FMyFragment> FragmentList = Context.GetMutableFragmentView<FMyFragment>();

			// [...]
		});
	if(FMath::RandBool())
		MySubsystem.DespawnEntity(Context);
	if(FMath::RandBool())
		MySubsystem.SpawnEntities(1);
}
