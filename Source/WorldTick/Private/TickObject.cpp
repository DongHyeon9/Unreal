// Fill out your copyright notice in the Description page of Project Settings.


#include "TickObject.h"

UTickObject::UTickObject()
{
	bUseTick = true;
}

TStatId UTickObject::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UTickObject, STATGROUP_Tickables);
}

UWorld* UTickObject::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("SkillBase : %s has a null OuterPrivate in UDO_ActiveBase::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		if (ULevel* Level = GetLevel())
		{
			return Level->OwningWorld;
		}
	}
	return nullptr;
}

void UTickObject::RecursiveLog(TObjectPtr<UObject> _Outer)
{
	if (_Outer->GetOuter())
	{
		RecursiveLog(_Outer->GetOuter());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *_Outer->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *_Outer->GetName());
	}
}

void UTickObject::Tick(float _DeltaTime)
{
	if (bUseTick && GetWorldSettings() != nullptr)
	{
		//Æ½ ÇÔ¼ö ±¸Çö
		ReceiveTick(_DeltaTime);
	}
}

ULevel* UTickObject::GetLevel() const
{
	return GetTypedOuter<ULevel>();
}

AWorldSettings* UTickObject::GetWorldSettings() const
{
	UWorld* World = GetWorld();
	return (World ? World->GetWorldSettings() : nullptr);
}
