// Fill out your copyright notice in the Description page of Project Settings.


#include "GCGameInstance.h"
#include "GCClass.h"
#include "GCObjectNN.h"

UGCGameInstance::UGCGameInstance()
{

}

void UGCGameInstance::Init()
{
	Super::Init();

	propertyObj = NewObject<UGCObjectNN>(this);
	nonPropertyObj = NewObject<UGCObjectNN>(this);
	propertyObjArray.Emplace(NewObject<UGCObjectNN>(this));
	nonPropertyObjArray.Emplace(NewObject<UGCObjectNN>(this));
	gcClassMember = new FGCClass(NewObject<UGCObjectNN>(this));

	UE_LOG(LogTemp, Log, TEXT("==========스코프 안에서 객체 생성=========="));
	{
		TUniquePtr<FGCClass> gcClassScope = MakeUnique<FGCClass>(NewObject<UGCObjectNN>(this));
		derivedFGCObjectScope = gcClassScope->GetObj();

		propertyObj->SetStringData(TEXT("Property Obj"));
		nonPropertyObj->SetStringData(TEXT("None Property Obj"));
		propertyObjArray[0]->SetStringData(TEXT("Property Obj Array"));
		nonPropertyObjArray[0]->SetStringData(TEXT("None Property Obj Array"));
		derivedFGCObjectScope->SetStringData(TEXT("Derived FGCObject With Native In Scope"));
		gcClassMember->GetObj()->SetStringData(TEXT("Derived FGCObject With Native In Member"));

		UE_LOG(LogTemp, Log, TEXT("==========GC 전=========="));
		PrintObjectsState(propertyObj);
		PrintObjectsState(nonPropertyObj);
		PrintObjectsState(propertyObjArray[0]);
		PrintObjectsState(nonPropertyObjArray[0]);
		PrintObjectsState(derivedFGCObjectScope);
		PrintObjectsState(gcClassMember->GetObj());
		UE_LOG(LogTemp, Log, TEXT("==========GC 전=========="));

		GEngine->ForceGarbageCollection();
	}
	UE_LOG(LogTemp, Log, TEXT("==========스코프 안에서 객체 생성=========="));

	FTimerHandle printTimerHandle{};
	GetWorld()->GetTimerManager().SetTimer(printTimerHandle, FTimerDelegate::CreateLambda([&]() {
		TObjectPtr<UGCObjectNN> derivedFGCObjectMember = gcClassMember->GetObj();
		delete gcClassMember;

		UE_LOG(LogTemp, Log, TEXT("==========GC 후=========="));
		PrintObjectsState(propertyObj);
		PrintObjectsState(nonPropertyObj);
		PrintObjectsState(propertyObjArray[0]);
		PrintObjectsState(nonPropertyObjArray[0]);
		PrintObjectsState(derivedFGCObjectScope);
		PrintObjectsState(derivedFGCObjectMember);
		UE_LOG(LogTemp, Log, TEXT("==========GC 후=========="));
		}), 3.f, false);
}

void UGCGameInstance::PrintObjectsState(const TObjectPtr<UGCObjectNN> _Obj)
{
	if (_Obj->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *_Obj->GetStringData());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("없어요"));
	}
}
