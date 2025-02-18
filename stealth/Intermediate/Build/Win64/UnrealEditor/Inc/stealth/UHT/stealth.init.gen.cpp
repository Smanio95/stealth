// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodestealth_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_stealth;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_stealth()
	{
		if (!Z_Registration_Info_UPackage__Script_stealth.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/stealth",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x954E6E27,
				0x0F40AED9,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_stealth.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_stealth.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_stealth(Z_Construct_UPackage__Script_stealth, TEXT("/Script/stealth"), Z_Registration_Info_UPackage__Script_stealth, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x954E6E27, 0x0F40AED9));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
