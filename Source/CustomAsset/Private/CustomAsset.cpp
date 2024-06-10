#include "CustomAsset.h"

DEFINE_LOG_CATEGORY(CustomAsset);

#define LOCTEXT_NAMESPACE "FCustomAsset"

void FCustomAsset::StartupModule()
{
	UE_LOG(CustomAsset, Warning, TEXT("CustomAsset module has been loaded"));
}

void FCustomAsset::ShutdownModule()
{
	UE_LOG(CustomAsset, Warning, TEXT("CustomAsset module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomAsset, CustomAsset)