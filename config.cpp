class CfgPatches
{
	class OMD_Bridge
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"InediaInfectedAI",
			"TerjeCore",
			"TerjeMedicine",
			"TerjeMedicine_Tools",
			"TerjeSkills"
		};
	};
};

class CfgMods
{
	class OMD_Bridge
	{
		dir = "OMD_Bridge";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "OMD Bridge";
		credits = "OMD";
		author = "OMD";
		authorID = "0";
		version = "0.1.0";
		type = "mod";
		dependencies[] = { "Game", "World", "Mission" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "OMD_Bridge/Scripts/3_Game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "OMD_Bridge/Scripts/4_World" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "OMD_Bridge/Scripts/5_Mission" };
			};
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class Clothing;
	class Splint: Inventory_Base
	{
		class InediaPain
		{
			ShowTips = 1;
			IsFractureStabilizationItem = 1;
			FractureStabilizationItemAllowedLimbs[] = {"arms", "legs", "hands", "feet"};
			FractureStabilizationItemShockReductionMultiplier = 1.5;
			FractureStabilizationItemRegenerationMultiplier = 1.5;
			FractureStabilizationItemActionTimeSeconds = 10;
			FractureStabilizationItemActionText = "#STR_inediainfectedai_stabilize_break";
			FractureStabilizationItemActionAnimationId = 59;
			FractureStabilizationItemQuantityPerUse = 1;
		};
	};
	class InediaPain_SplintKit: Inventory_Base
	{
		class InediaPain
		{
			ShowTips = 1;
			IsFractureStabilizationItem = 1;
			FractureStabilizationItemAllowedLimbs[] = {"head", "arms", "legs", "torso", "hands", "feet"};
			FractureStabilizationItemShockReductionMultiplier = 3;
			FractureStabilizationItemRegenerationMultiplier = 3;
			FractureStabilizationItemActionTimeSeconds = 10;
			FractureStabilizationItemActionText = "#STR_inediainfectedai_stabilize_break";
			FractureStabilizationItemActionAnimationId = 59;
			FractureStabilizationItemQuantityPerUse = 20;
		};
	};
	class SewingKit: Inventory_Base
	{
		class InediaPain
		{
			ShowTips = 1;
			IsDeepWoundClosureItem = 1;
			DeepWoundClosureItemAllowedLimbs[] = {"head", "arms", "legs", "torso", "hands", "feet"};
			DeepWoundClosureItemRequiredPainkillerLevel = 1;
			DeepWoundClosureItemActionTimeSeconds = 10;
			DeepWoundClosureItemActionText = "#STR_inediainfectedai_wound_closure_tool_close_wound";
			DeepWoundClosureItemActionAnimationId = 71;
			DeepWoundClosureItemQuantityPerUse = 20;
			DeepWoundClosureItemSuccessChancePercent = 30;
			DeepWoundClosureItemAssistSuccessChancePercent = 40;
			DeepWoundClosureItemProcedureBloodLossMl = 150;
		};
	};
	class InediaPain_SurgicalKit: Inventory_Base
	{
		class InediaPain
		{
			ShowTips = 1;
			IsDeepWoundClosureItem = 1;
			DeepWoundClosureItemAllowedLimbs[] = {"head", "arms", "legs", "torso", "hands", "feet"};
			DeepWoundClosureItemRequiredPainkillerLevel = 1;
			DeepWoundClosureItemActionTimeSeconds = 10;
			DeepWoundClosureItemActionText = "#STR_inediainfectedai_wound_closure_tool_close_wound";
			DeepWoundClosureItemActionAnimationId = 71;
			DeepWoundClosureItemQuantityPerUse = 20;
			DeepWoundClosureItemSuccessChancePercent = 90;
			DeepWoundClosureItemAssistSuccessChancePercent = 100;
			DeepWoundClosureItemProcedureBloodLossMl = 50;
			IsExtractBulletItem = 1;
			ExtractBulletItemAllowedLimbs[] = {"head", "arms", "legs", "torso"};
			ExtractBulletItemRequiredPainkillerLevel = 2;
			ExtractBulletItemActionTimeSeconds = 10;
			ExtractBulletItemActionText = "#STR_inediainfectedai_bullet_extraction_tool_extract_bullet";
			ExtractBulletItemActionAnimationId = 71;
			ExtractBulletItemQuantityPerUse = 20;
			ExtractBulletItemSuccessChancePercent = 70;
			ExtractBulletItemAssistSuccessChancePercent = 80;
			ExtractBulletItemProcedureBloodLossMl = 100;
			IsInternalBleedingStoppingItem = 1;
			InternalBleedingStoppingItemRequiredPainkillerLevel = 3;
			InternalBleedingStoppingItemActionTimeSeconds = 10;
			InternalBleedingStoppingItemActionText = "#STR_inediainfectedai_internal_bleeding_treatment_tool_stop_internal_bleeding";
			InternalBleedingStoppingItemActionAnimationId = 71;
			InternalBleedingStoppingItemQuantityPerUse = 20;
			InternalBleedingStoppingItemSuccessChancePercent = 30;
			InternalBleedingStoppingItemAssistSuccessChancePercent = 40;
			InternalBleedingStoppingItemProcedureBloodLossMl = 500;
			IsCutClosureItem = 1;
			CutClosureItemActionTimeSeconds = 3;
			CutClosureItemActionText = "#STR_inediainfectedai_remove_scratch";
			CutClosureItemActionAnimationId = 71;
			CutClosureItemQuantityPerUse = 5;
		};
	};
	class TerjeSurgicalKit: Inventory_Base
	{
		class InediaPain
		{
			IsDeepWoundClosureItem = 1;
			DeepWoundClosureItemAllowedLimbs[] = {"head", "arms", "legs", "torso", "hands", "feet"};
			DeepWoundClosureItemRequiredPainkillerLevel = 1;
			DeepWoundClosureItemActionTimeSeconds = 10;
			DeepWoundClosureItemActionText = "#STR_inediainfectedai_wound_closure_tool_close_wound";
			DeepWoundClosureItemActionAnimationId = 71;
			DeepWoundClosureItemQuantityPerUse = 1;
			DeepWoundClosureItemSuccessChancePercent = 70;
			DeepWoundClosureItemAssistSuccessChancePercent = 80;
			DeepWoundClosureItemProcedureBloodLossMl = 50;
			ShowTips = 1;
		};
	};
	class Rag: Inventory_Base
	{
		class InediaPain
		{
			DeepWoundBandageItemRegenerationMultiplier = 1;
			DeepWoundBandageItemEffectiveDurationSeconds = 560;
		};
	};
	class Bandana_ColorBase: Clothing
	{
		class InediaPain
		{
			DeepWoundBandageItemRegenerationMultiplier = 1;
			DeepWoundBandageItemEffectiveDurationSeconds = 560;
		};
	};
	class BandageDressing: Inventory_Base
	{
		class InediaPain
		{
			DeepWoundBandageItemRegenerationMultiplier = 1.5;
			DeepWoundBandageItemEffectiveDurationSeconds = 1000;
		};
	};
	class InediaPain_HemostaticDressing: Inventory_Base
	{
		class InediaPain
		{
			DeepWoundBandageItemRegenerationMultiplier = 3;
			DeepWoundBandageItemEffectiveDurationSeconds = 1500;
		};
	};
	class TerjeBandageHemostatic: BandageDressing
	{
		class InediaPain
		{
			DeepWoundBandageItemRegenerationMultiplier = 3;
			DeepWoundBandageItemEffectiveDurationSeconds = 1500;
		};
	};
};
