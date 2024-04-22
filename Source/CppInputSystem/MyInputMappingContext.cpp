// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInputMappingContext.h"
#include "InputActions/MyInputAction_Jump.h"
#include "InputActions/MyInputAction_Look.h"
#include "InputActions/MyInputAction_Move.h"

UMyInputMappingContext::UMyInputMappingContext()
{
	//CDO�� InputAction ������Ʈ ����
	auto jumpInputAction = UMyInputAction_Jump::StaticClass()->GetDefaultObject<UMyInputAction_Jump>();
	auto moveInputAction = UMyInputAction_Move::StaticClass()->GetDefaultObject<UMyInputAction_Move>();
	auto lookInputAction = UMyInputAction_Look::StaticClass()->GetDefaultObject<UMyInputAction_Look>();

	FEnhancedActionKeyMapping ia_Jump{ jumpInputAction ,EKeys::SpaceBar };
	FEnhancedActionKeyMapping ia_Move{ moveInputAction ,EKeys::D };
	FEnhancedActionKeyMapping ia_Look{ lookInputAction ,EKeys::Mouse2D };

	auto swizzleAxis = CreateDefaultSubobject<UInputModifierSwizzleAxis>(TEXT("SwizzleAxis"));
	auto negateMove = CreateDefaultSubobject<UInputModifierNegate>(TEXT("NegateMove"));
	auto negateLook = CreateDefaultSubobject<UInputModifierNegate>(TEXT("NegateLook"));

	Mappings.Reserve(6);
	ia_Move.Modifiers.Reserve(2);

	//�⺻������ �����̵�
	Mappings.Emplace(ia_Move);

	//Ű ���� �� �����̵�
	ia_Move.Key = EKeys::W;
	ia_Move.Modifiers.Emplace(swizzleAxis);
	Mappings.Emplace(ia_Move);

	//Ű ���� �� �Ĺ��̵�
	ia_Move.Key = EKeys::S;
	ia_Move.Modifiers.Emplace(negateMove);
	Mappings.Emplace(ia_Move);

	//Ű ���� �� �����̵�
	ia_Move.Key = EKeys::A;
	ia_Move.Modifiers.Remove(swizzleAxis);
	Mappings.Emplace(ia_Move);

	//Ű ���� �� Look����
	negateLook->bX = false;
	negateLook->bZ = false;
	ia_Look.Modifiers.Emplace(negateLook);
	Mappings.Emplace(ia_Look);

	//���� ����
	Mappings.Emplace(ia_Jump);
}
