#include "Settings.h"

USecondSettings::USecondSettings()
{
	this->AMyActor = AActor::StaticClass();

}

#if WITH_EDITOR
FName USecondSettings::GetCategoryName() const
{
	return FName("Plugins");
}
#endif
