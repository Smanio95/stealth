// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "stealthCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FBranchingPointNotifyPayload;
struct FHitResult;
#ifdef STEALTH_stealthCharacter_generated_h
#error "stealthCharacter.generated.h already included, missing '#pragma once' in stealthCharacter.h"
#endif
#define STEALTH_stealthCharacter_generated_h

#define FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_SPARSE_DATA
#define FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void AttackReposition_Implementation(FTransform StartPos, FTransform EndPos); \
 \
	DECLARE_FUNCTION(execAttackReposition); \
	DECLARE_FUNCTION(execPlayAttack); \
	DECLARE_FUNCTION(execOnNotify); \
	DECLARE_FUNCTION(execOnOverlapExit); \
	DECLARE_FUNCTION(execOnOverlapBegin);


#define FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_ACCESSORS
#define FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_CALLBACK_WRAPPERS
#define FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAstealthCharacter(); \
	friend struct Z_Construct_UClass_AstealthCharacter_Statics; \
public: \
	DECLARE_CLASS(AstealthCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/stealth"), NO_API) \
	DECLARE_SERIALIZER(AstealthCharacter)


#define FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AstealthCharacter(AstealthCharacter&&); \
	NO_API AstealthCharacter(const AstealthCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AstealthCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AstealthCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AstealthCharacter) \
	NO_API virtual ~AstealthCharacter();


#define FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_20_PROLOG
#define FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_SPARSE_DATA \
	FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_ACCESSORS \
	FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_CALLBACK_WRAPPERS \
	FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_INCLASS_NO_PURE_DECLS \
	FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STEALTH_API UClass* StaticClass<class AstealthCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Smanio_stealth_proj_stealth_Source_stealth_stealthCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
