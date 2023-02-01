#pragma once
#include "CoreMinimal.h"
#define LOCTEXT_NAMESPACE "MessegeLog"
DECLARE_LOG_CATEGORY_EXTERN(DHhan, Log, All);
#define DHLOG_CALLINFO (FString(__FUNCTION__)+TEXT("(")+FString::FromInt(__LINE__)+TEXT(")"))
#define DHLOG_S(Verbosity) UE_LOG(DHhan,Verbosity,TEXT("%s"),*DHLOG_CALLINFO)
#define DHLOG(Verbosity,Format,...) UE_LOG(DHhan,Verbosity,TEXT("%s %s"),*DHLOG_CALLINFO, *FString::Printf(Format,##__VA_ARGS__))
#define DHCHECK(Expr,...) {if(!(Expr)){DHLOG(Error,TEXT("ASSERTION : %s"),TEXT("'"#Expr"'"));return __VA_ARGS__;}}
#define PRINTSTR(Key,Time,Color,Format,...) GEngine->AddOnScreenDebugMessage(Key,Time,Color,FString::Printf(Format,##__VA_ARGS__))
#define DHMSG(Verbosity,Format,...) CreateLog(TEXT("DHLog"));FMessageLog(TEXT("DHLog")).Verbosity(FText::FromString(FString::Printf(Format,##__VA_ARGS__)))
void CreateLog(FName logName);