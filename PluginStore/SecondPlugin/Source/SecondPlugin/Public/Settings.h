#pragma once
#include "Engine/DeveloperSettings.h"
#include "Settings.generated.h"

UCLASS(config = Game, defaultconfig, meta = ( DisplayName = "Second" ))

class SECONDPLUGIN_API USecondSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	USecondSettings();
	
	#if WITH_EDITOR
	virtual FName GetCategoryName() const override;
	#endif
	
private:
	
	UPROPERTY(config, EditAnywhere, Category = "Default Classes")
	TSubclassOf<AActor> AMyActor;
	
};
