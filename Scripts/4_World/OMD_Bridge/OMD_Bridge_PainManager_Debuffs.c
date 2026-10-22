modded class InediaInfectedAI_PainManager
{
	override void ProcessPainDamage(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (OMD_BridgeConfig.IsActive() && ammo == "FallDamageShock")
		{
			OMD_Bridge_ProcessFallDamageShock(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
			return;
		}

		super.ProcessPainDamage(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	override float GetPainArmsHandShakeMultiplier()
	{
		float armsShake = super.GetPainArmsHandShakeMultiplier();
		if (!OMD_BridgeConfig.IsActive())
		{
			return armsShake;
		}

		float handsShake = OMD_Bridge_GetHandsAimShakeMultiplier();
		if (handsShake > armsShake)
		{
			return handsShake;
		}

		return armsShake;
	}

	override eInjuryHandlerLevels InediaInfectedAI_GetInjuryLevel()
	{
		eInjuryHandlerLevels maxInjuryLevel = super.InediaInfectedAI_GetInjuryLevel();
		if (!OMD_BridgeConfig.IsActive() || !PainSystemIsActive())
		{
			return maxInjuryLevel;
		}

		eInjuryHandlerLevels feetInjuryLevel = OMD_Bridge_GetFeetInjuryLevel();
		if (feetInjuryLevel > maxInjuryLevel)
		{
			maxInjuryLevel = feetInjuryLevel;
		}

		return maxInjuryLevel;
	}

	override bool CanLimbBeBrokenAfterHit(string limb, float receivedDamage)
	{
		if (OMD_BridgeConfig.IsActive())
		{
			if (limb == "hands" || limb == "feet")
			{
				if (OMD_Bridge_RollLimbProtectionBlock(limb, "break"))
				{
					return false;
				}
			}
		}

		return super.CanLimbBeBrokenAfterHit(limb, receivedDamage);
	}

	override bool CanGetDeepWoundFromHit(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (OMD_BridgeConfig.IsActive())
		{
			string limb = GetInediaPainLimbFromDmgZone(dmgZone);
			if (limb == "hands" || limb == "feet")
			{
				if (OMD_Bridge_RollLimbProtectionBlock(limb, "wound"))
				{
					return false;
				}
			}
		}

		return super.CanGetDeepWoundFromHit(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	override bool CanGetBulletFromHit(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (OMD_BridgeConfig.IsActive())
		{
			string limb = GetInediaPainLimbFromDmgZone(dmgZone);
			if (limb == "hands" || limb == "feet")
			{
				if (OMD_Bridge_RollLimbProtectionBlock(limb, "bullet"))
				{
					return false;
				}
			}
		}

		return super.CanGetBulletFromHit(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	float OMD_Bridge_GetHandsAimShakeMultiplier()
	{
		if (!PainSystemIsActive())
		{
			return 0;
		}

		m_Player.GetMovementState(m_Player.m_MovementState);
		if (m_Player.m_MovementState && m_Player.m_MovementState.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_RAISEDPRONE)
		{
			return 0;
		}

		InediaInfectedAI_LimbPainLevels painHandsLevel = GetPainWithBuffsLevelForLimb("hands");
		float shakeMultiplier = 0;

		if (painHandsLevel >= InediaInfectedAI_LimbPainLevels.BADLY)
		{
			shakeMultiplier = OMD_BridgeConfig.GetHandsDebuffAimShakeBadly();
		}
		else if (painHandsLevel >= InediaInfectedAI_LimbPainLevels.MEDIUM)
		{
			shakeMultiplier = OMD_BridgeConfig.GetHandsDebuffAimShakeMedium();
		}
		else if (painHandsLevel >= InediaInfectedAI_LimbPainLevels.LOW)
		{
			shakeMultiplier = OMD_BridgeConfig.GetHandsDebuffAimShakeLow();
		}

		if (shakeMultiplier > 0)
		{
			shakeMultiplier = shakeMultiplier * GetActionsShockMultiplierForLimb("hands");
		}

		return shakeMultiplier;
	}

	float OMD_Bridge_GetHandsActionTimeMultiplier()
	{
		if (!OMD_BridgeConfig.IsActive() || !PainSystemIsActive())
		{
			return 1;
		}

		InediaInfectedAI_LimbPainLevels painHandsLevel = GetPainWithBuffsLevelForLimb("hands");
		float timeMultiplier = 1;

		if (painHandsLevel >= InediaInfectedAI_LimbPainLevels.CRITICAL)
		{
			timeMultiplier = OMD_BridgeConfig.GetHandsDebuffActionTimeCritical();
		}
		else if (painHandsLevel >= InediaInfectedAI_LimbPainLevels.BADLY)
		{
			timeMultiplier = OMD_BridgeConfig.GetHandsDebuffActionTimeBadly();
		}
		else if (painHandsLevel >= InediaInfectedAI_LimbPainLevels.MEDIUM)
		{
			timeMultiplier = OMD_BridgeConfig.GetHandsDebuffActionTimeMedium();
		}
		else if (painHandsLevel >= InediaInfectedAI_LimbPainLevels.LOW)
		{
			timeMultiplier = OMD_BridgeConfig.GetHandsDebuffActionTimeLow();
		}

		if (IsLimbBroken("hands") && !IsLimbStabilized("hands"))
		{
			if (timeMultiplier < OMD_BridgeConfig.GetHandsDebuffActionTimeBadly())
			{
				timeMultiplier = OMD_BridgeConfig.GetHandsDebuffActionTimeBadly();
			}
		}

		if (timeMultiplier < 1)
		{
			timeMultiplier = 1;
		}

		return timeMultiplier;
	}

	eInjuryHandlerLevels OMD_Bridge_GetFeetInjuryLevel()
	{
		InediaInfectedAI_LimbPainLevels painLevel = GetPainWithBuffsLevelForLimb("feet");
		eInjuryHandlerLevels currentInjuryLevel = eInjuryHandlerLevels.PRISTINE;

		if (painLevel >= InediaInfectedAI_LimbPainLevels.CRITICAL)
		{
			currentInjuryLevel = eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		else if (painLevel >= InediaInfectedAI_LimbPainLevels.BADLY)
		{
			currentInjuryLevel = eInjuryHandlerLevels.DAMAGED;
		}
		else if (painLevel >= InediaInfectedAI_LimbPainLevels.MEDIUM)
		{
			currentInjuryLevel = eInjuryHandlerLevels.DAMAGED;
		}
		else if (painLevel >= InediaInfectedAI_LimbPainLevels.LOW)
		{
			currentInjuryLevel = eInjuryHandlerLevels.WORN;
		}

		if (painLevel >= InediaInfectedAI_LimbPainLevels.LOW)
		{
			if (IsLimbBroken("feet") && !IsLimbStabilized("feet"))
			{
				currentInjuryLevel = Math.Clamp(currentInjuryLevel + 1, eInjuryHandlerLevels.PRISTINE, eInjuryHandlerLevels.BADLY_DAMAGED);
			}

			if (GetBulletCountInLimb("feet") > 0)
			{
				currentInjuryLevel = Math.Clamp(currentInjuryLevel + 1, eInjuryHandlerLevels.PRISTINE, eInjuryHandlerLevels.BADLY_DAMAGED);
			}
		}

		return currentInjuryLevel;
	}

	bool OMD_Bridge_RollLimbProtectionBlock(string limb, string protectionKind)
	{
		float protection = OMD_Bridge_GetLimbAttachmentProtection(limb, protectionKind);
		if (protection <= 0)
		{
			return false;
		}

		protection = Math.Clamp(protection, 0, 1);
		if (Math.RandomFloat01() <= protection)
		{
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] protection blocked limb=" + limb + " kind=" + protectionKind + " value=" + protection.ToString());
			}

			return true;
		}

		return false;
	}

	float OMD_Bridge_GetLimbAttachmentProtection(string limb, string protectionKind)
	{
		if (!m_Player)
		{
			return 0;
		}

		string slotName = "";
		float coef = 1;
		string protectionKey = "melee";

		if (limb == "hands")
		{
			slotName = "Gloves";
			if (protectionKind == "break")
			{
				coef = OMD_BridgeConfig.GetHandsGlovesProtectionBreakCoef();
			}
			else if (protectionKind == "wound")
			{
				coef = OMD_BridgeConfig.GetHandsGlovesProtectionWoundCoef();
			}
			else
			{
				coef = OMD_BridgeConfig.GetHandsGlovesProtectionBulletCoef();
				protectionKey = "firearm";
			}
		}
		else if (limb == "feet")
		{
			slotName = "Feet";
			if (protectionKind == "break")
			{
				coef = OMD_BridgeConfig.GetFeetBootsProtectionBreakCoef();
			}
			else if (protectionKind == "wound")
			{
				coef = OMD_BridgeConfig.GetFeetBootsProtectionWoundCoef();
			}
			else
			{
				coef = OMD_BridgeConfig.GetFeetBootsProtectionBulletCoef();
				protectionKey = "firearm";
			}
		}
		else
		{
			return 0;
		}

		ItemBase attachment = ItemBase.Cast(m_Player.GetItemOnSlot(slotName));
		if (!attachment || attachment.IsRuined())
		{
			return 0;
		}

		float baseProtection = GetGame().ConfigGetFloat("CfgVehicles " + attachment.GetType() + " Protection " + protectionKey);
		if (baseProtection <= 0)
		{
			return 0;
		}

		return baseProtection * coef;
	}

	protected void OMD_Bridge_ProcessFallDamageShock(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (!m_Player || !m_Player.IsAlive() || !damageResult || !source || !PainSystemIsActive())
		{
			return;
		}

		if (!m_Player.m_InediaInfectedAI_ConfigZombie || !m_Player.m_InediaInfectedAI_ConfigPlayers)
		{
			return;
		}

		if (m_Player.m_InediaInfectedAI_ConfigPlayers.FallPainMultiplier <= 0)
		{
			return;
		}

		float painDamage = damageResult.GetDamage("", "Shock") * m_Player.m_InediaInfectedAI_WeaponMultiplier;
		painDamage = painDamage * m_Player.m_InediaInfectedAI_ConfigPlayers.FallPainMultiplier;

		float fallHeight = 0;
		DayZPlayerImplementFallDamage fallDamage = m_Player.GetFallDamage();
		if (fallDamage)
		{
			fallHeight = fallDamage.GetHeight();
		}

		float feetOnlyHeight = OMD_BridgeConfig.GetFallFeetOnlyHeightMeters();
		float feetAndLegsHeight = OMD_BridgeConfig.GetFallFeetAndLegsHeightMeters();
		bool damageFeet = true;
		bool damageLegs = false;

		if (fallHeight > 0 && fallHeight < feetOnlyHeight)
		{
			damageFeet = false;
		}

		if (fallHeight >= feetAndLegsHeight)
		{
			damageLegs = true;
		}

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] fall height=" + fallHeight.ToString() + " feet=" + damageFeet.ToString() + " legs=" + damageLegs.ToString() + " pain=" + painDamage.ToString());
		}

		if (m_Player.m_InediaInfectedAI_ConfigPlayers.LimbsBreakFromFalls && painDamage > 30)
		{
			float fallFractureChance = painDamage;
			fallFractureChance = fallFractureChance * InediaInfectedAI_SyberiaCompatibility.GetSyberiaFractureChanceMultiplier(m_Player);

			if (damageFeet && fallFractureChance > 0 && Math.RandomFloatInclusive(0, 100) <= fallFractureChance)
			{
				ActivateBreakForLimb("feet", 0);
			}

			if (damageLegs && fallFractureChance > 0 && Math.RandomFloatInclusive(0, 100) <= fallFractureChance)
			{
				ActivateBreakForLimb("legs", 0);
			}
		}

		if (m_Player.GetHealth("", "Shock") > PlayerConstants.UNCONSCIOUS_THRESHOLD)
		{
			if (damageFeet)
			{
				AddPainPercentForLimb("feet", painDamage);
				OMD_Bridge_TryFallDeepWound("feet", painDamage);
			}

			if (damageLegs)
			{
				AddPainPercentForLimb("legs", painDamage);
				OMD_Bridge_TryFallDeepWound("legs", painDamage);
			}

			if (painDamage > 30)
			{
				AddPainPercentForLimb("arms", Math.RandomFloatInclusive(0, painDamage), m_Player.m_InediaInfectedAI_ConfigPlayers.LimbsBreakFromFalls);
				OMD_Bridge_TryFallDeepWound("arms", painDamage);
			}
		}
		else
		{
			foreach (string inediaPainLimbFall: InediaInfectedAI_PainManager.m_InediaPainLimbs)
			{
				bool applyLimb = true;
				if (inediaPainLimbFall == "feet" && !damageFeet)
				{
					applyLimb = false;
				}

				if (inediaPainLimbFall == "legs" && !damageLegs)
				{
					applyLimb = false;
				}

				if (!applyLimb)
				{
					continue;
				}

				AddPainPercentForLimb(inediaPainLimbFall, Math.RandomFloatInclusive(0, painDamage), m_Player.m_InediaInfectedAI_ConfigPlayers.LimbsBreakFromFalls);
				OMD_Bridge_TryFallDeepWound(inediaPainLimbFall, painDamage);
			}
		}
	}

	protected void OMD_Bridge_TryFallDeepWound(string limb, float painDamage)
	{
		if (!m_Player.m_InediaInfectedAI_ConfigPlayers.LimbsDeepWoundFromFalls)
		{
			return;
		}

		if (painDamage <= 30)
		{
			return;
		}

		float deepWoundChanceFall = painDamage / 3 * GetInediaLimbDamageMultiplier(limb, "Blood", "Melee");
		if (deepWoundChanceFall > 0 && Math.RandomFloatInclusive(0, 100) <= deepWoundChanceFall)
		{
			ActivateDeepWoundForLimb(limb, painDamage * DEEP_WOUND_PAIN_TO_BLEEDING_MULTIPLIER);
		}
	}
};
