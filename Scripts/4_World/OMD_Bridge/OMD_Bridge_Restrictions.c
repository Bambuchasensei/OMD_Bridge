modded class InediaInfectedAI_Restrictions
{
	override static float PainSystem_ModifyInternalBleedingClosureSurgeryActionTime(PlayerBase player, ItemBase item, float defaultActionTimeSeconds)
	{
		float result = super.PainSystem_ModifyInternalBleedingClosureSurgeryActionTime(player, item, defaultActionTimeSeconds);
		if (!OMD_BridgeConfig.IsActive())
		{
			return result;
		}

		return OMD_BridgeSkills.ModifySurgeryActionTime(player, result);
	}

	override static float PainSystem_ModifyInternalBleedingClosureSurgerySuccessChance(PlayerBase player, ItemBase item, float defaultSuccessChancePercent)
	{
		float result = super.PainSystem_ModifyInternalBleedingClosureSurgerySuccessChance(player, item, defaultSuccessChancePercent);
		if (!OMD_BridgeConfig.IsActive())
		{
			return result;
		}

		return OMD_BridgeSkills.ModifySurgerySuccessChancePercent(player, "surgint", result);
	}

	override static float PainSystem_ModifyDeepWoundClosureSurgeryActionTime(PlayerBase player, ItemBase item, float defaultActionTimeSeconds)
	{
		float result = super.PainSystem_ModifyDeepWoundClosureSurgeryActionTime(player, item, defaultActionTimeSeconds);
		if (!OMD_BridgeConfig.IsActive())
		{
			return result;
		}

		return OMD_BridgeSkills.ModifySurgeryActionTime(player, result);
	}

	override static float PainSystem_ModifyDeepWoundClosureSurgerySuccessChance(PlayerBase player, ItemBase item, float defaultSuccessChancePercent)
	{
		float result = super.PainSystem_ModifyDeepWoundClosureSurgerySuccessChance(player, item, defaultSuccessChancePercent);
		if (!OMD_BridgeConfig.IsActive())
		{
			return result;
		}

		return OMD_BridgeSkills.ModifySurgerySuccessChancePercent(player, "surgsw", result);
	}

	override static float PainSystem_ModifyExtractBulletSurgeryActionTime(PlayerBase player, ItemBase item, float defaultActionTimeSeconds)
	{
		float result = super.PainSystem_ModifyExtractBulletSurgeryActionTime(player, item, defaultActionTimeSeconds);
		if (!OMD_BridgeConfig.IsActive())
		{
			return result;
		}

		return OMD_BridgeSkills.ModifySurgeryActionTime(player, result);
	}

	override static float PainSystem_ModifyExtractBulletSurgerySuccessChance(PlayerBase player, ItemBase item, float defaultSuccessChancePercent)
	{
		float result = super.PainSystem_ModifyExtractBulletSurgerySuccessChance(player, item, defaultSuccessChancePercent);
		if (!OMD_BridgeConfig.IsActive())
		{
			return result;
		}

		return OMD_BridgeSkills.ModifySurgerySuccessChancePercent(player, "surgbw", result);
	}

	override static float PainSystem_ModifyDeepWoundBandageActionTime(PlayerBase player, ItemBase item, float defaultActionTimeSeconds)
	{
		float result = super.PainSystem_ModifyDeepWoundBandageActionTime(player, item, defaultActionTimeSeconds);
		if (!OMD_BridgeConfig.IsActive())
		{
			return result;
		}

		return OMD_BridgeSkills.ModifyBandageActionTime(player, result);
	}
};

modded class InediaInfectedAI_ActionFractureStabilization
{
	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);
		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!GetGame().IsServer())
		{
			return;
		}

		if (!action_data || !action_data.m_Player)
		{
			return;
		}

		OMD_BridgeSkills.AddMedicineExperience(action_data.m_Player, OMD_BridgeConfig.GetXpSplint());
	}
};
