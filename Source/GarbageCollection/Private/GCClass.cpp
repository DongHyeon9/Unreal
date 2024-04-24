// Fill out your copyright notice in the Description page of Project Settings.


#include "GCClass.h"
#include "GCObjectNN.h"

FGCClass::FGCClass(TObjectPtr<UGCObjectNN> _GCObj) :obj(_GCObj)
{
	UE_LOG(LogTemp, Warning, TEXT("FGCClass Constructor"));
}

FGCClass::~FGCClass()
{
	UE_LOG(LogTemp, Warning, TEXT("FGCClass Destructor"));
}

void FGCClass::AddReferencedObjects(FReferenceCollector& _Collector)
{
	if (obj->IsValidLowLevel())
	{
		_Collector.AddReferencedObject(obj);
	}
}

FString FGCClass::GetReferencerName() const
{
	return TEXT("FGCClass");
}
