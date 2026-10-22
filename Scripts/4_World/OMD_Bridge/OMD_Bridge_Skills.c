class OMD_BridgeSkills
{
	static bool TryGetPerkValue(PlayerBase player, string skillId, string perkId, out float perkValue)
	{
		perkValue = 0;
		if (!player)
		{
			return false;
		}

		if (!player.GetTerjeSkills())
		{
			return false;
		}

		return player.GetTerjeSkills().GetPerkValue(skillId, perkId, perkValue);
	}

	static void AddMedicineExperience(PlayerBase player, int amount)
	{
		if (!player)
		{
			return;
		}

		if (amount <= 0)
		{
			return;
		}

		if (!player.GetTerjeSkills())
		{
			return;
		}

		player.GetTerjeSkills().AddSkillExperience("med", amount);
		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] med XP +" + amount.ToString());
		}
	}

	static float ModifyBandageActionTime(PlayerBase player, float defaultActionTimeSeconds)
	{
		float perkSpeedMod = 1.0;
		float perkValue;
		if (TryGetPerkValue(player, "med", "mastdress", perkValue))
		{
			perkSpeedMod = perkSpeedMod + perkValue;
		}

		return defaultActionTimeSeconds * Math.Clamp(perkSpeedMod, 0.1, 2);
	}

	static float ModifySurgeryActionTime(PlayerBase player, float defaultActionTimeSeconds)
	{
		float perkValue;
		if (!TryGetPerkValue(player, "med", "surgeon", perkValue))
		{
			return defaultActionTimeSeconds;
		}

		return defaultActionTimeSeconds * Math.Clamp(1.0 + perkValue, 0, 1);
	}

	static float ModifySurgerySuccessChancePercent(PlayerBase player, string perkId, float defaultSuccessChancePercent)
	{
		float chance01 = defaultSuccessChancePercent / 100.0;
		float perkValue;
		if (!TryGetPerkValue(player, "med", perkId, perkValue))
		{
			return defaultSuccessChancePercent;
		}

		float perkAffectRange = Math.Clamp(1.0 - chance01, 0, 1);
		chance01 = chance01 + perkAffectRange * perkValue;
		return Math.Clamp(chance01 * 100.0, 0, 100);
	}

	static float GetThickBloodBleedMultiplier(PlayerBase player)
	{
		float perkValue;
		if (!TryGetPerkValue(player, "immunity", "thkblood", perkValue))
		{
			return 1.0;
		}

		return Math.Clamp(1.0 + perkValue, 0.1, 1.0);
	}

	static float GetWoundHealPerkMultiplier(PlayerBase player)
	{
		float healMult = 1.0;
		float perkValue;
		if (TryGetPerkValue(player, "immunity", "whealing", perkValue))
		{
			healMult = healMult * (1.0 + perkValue);
		}

		if (TryGetPerkValue(player, "immunity", "qhealing", perkValue))
		{
			healMult = healMult * (1.0 + perkValue);
		}

		if (healMult < 1.0)
		{
			healMult = 1.0;
		}

		return healMult;
	}

	static float GetPainHealPerkMultiplier(PlayerBase player)
	{
		float perkValue;
		if (!TryGetPerkValue(player, "immunity", "qhealing", perkValue))
		{
			return 1.0;
		}

		float healMult = 1.0 + perkValue;
		if (healMult < 1.0)
		{
			healMult = 1.0;
		}

		return healMult;
	}

	static float RecomputeBoneRegenMultiplier(PlayerBase player, InediaInfectedAI_PainManager painManager, string limb)
	{
		float boneRegenMultiplier = 1.0;
		if (painManager.IsLimbStabilized(limb))
		{
			boneRegenMultiplier = boneRegenMultiplier * painManager.GetBreakStabilizationRegenerationMultiplierForLimb(limb);
		}

		if (player.GetModifiersManager() && player.GetModifiersManager().IsModifierActive(InediaInfectedAI_eModifiers.MDF_BONE_REGEN))
		{
			boneRegenMultiplier = boneRegenMultiplier * painManager.m_BoneRegenItemRegenMultiplier;
		}

		if (boneRegenMultiplier < 1.0)
		{
			boneRegenMultiplier = 1.0;
		}

		return boneRegenMultiplier;
	}

	static float RecomputeDeepWoundRegenMultiplier(PlayerBase player, InediaInfectedAI_PainManager painManager, string limb)
	{
		float deepWoundRegenMultiplier = 1.0;
		if (painManager.IsLimbDeepWoundBandaged(limb))
		{
			deepWoundRegenMultiplier = deepWoundRegenMultiplier * painManager.GetDeepWoundBandageRegenerationMultiplierForLimb(limb);
		}

		if (player.GetModifiersManager() && player.GetModifiersManager().IsModifierActive(InediaInfectedAI_eModifiers.MDF_DEEP_WOUND_REGEN))
		{
			deepWoundRegenMultiplier = deepWoundRegenMultiplier * painManager.m_DeepWoundRegenItemRegenMultiplier;
		}

		if (deepWoundRegenMultiplier < 1.0)
		{
			deepWoundRegenMultiplier = 1.0;
		}

		return deepWoundRegenMultiplier;
	}
};
