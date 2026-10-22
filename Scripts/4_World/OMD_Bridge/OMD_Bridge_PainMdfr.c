modded class InediaInfectedAI_PainMdfr
{
	float m_OMD_Bridge_HandsPainLogSeconds = 0;
	float m_OMD_Bridge_HandsBreakRegenLogSeconds = 0;
	float m_OMD_Bridge_FeetPainLogSeconds = 0;
	float m_OMD_Bridge_SeveritySyncSeconds = 0;
	ref map<string, int> m_OMD_Symptom_InediaState;
	ref map<string, float> m_OMD_Symptom_InediaTick;

	override void InediaInfectedAI_HealLimbsHandler(PlayerBase player, float pDt)
	{
		super.InediaInfectedAI_HealLimbsHandler(player, pDt);

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!player || !player.m_InediaInfectedAI_ConfigPlayers || !player.InediaInfectedAI_GetPainManager())
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (InediaInfectedAI_PainManager.m_InediaPainLimbs.Find("hands") == -1)
		{
			OMD_Bridge_HealBridgeLimbPain(player, painManager, "hands");
		}
		if (InediaInfectedAI_PainManager.m_InediaPainLimbs.Find("feet") == -1)
		{
			OMD_Bridge_HealBridgeLimbPain(player, painManager, "feet");
		}

		OMD_Bridge_ApplyPainHealPerk(player, painManager);

		painManager.OMD_Bridge_EnsureMinPainFloorForLimb("hands");
		painManager.OMD_Bridge_EnsureMinPainFloorForLimb("feet");
		painManager.OMD_Bridge_EnsureMinPainFloorForLimb("head");
		painManager.OMD_Bridge_EnsureMinPainFloorForLimb("arms");
		painManager.OMD_Bridge_EnsureMinPainFloorForLimb("legs");
		painManager.OMD_Bridge_EnsureMinPainFloorForLimb("torso");

		OMD_Bridge_LogBridgeLimbPainTick(painManager, pDt, "hands");
		OMD_Bridge_LogBridgeLimbPainTick(painManager, pDt, "feet");
	}

	override void InediaInfectedAI_UpdateFracturesHandler(PlayerBase player, float pDt)
	{
		super.InediaInfectedAI_UpdateFracturesHandler(player, pDt);

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!player || !player.InediaInfectedAI_GetPainManager())
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager.LimbsBreakSystemIsActive())
		{
			return;
		}

		if (InediaInfectedAI_PainManager.m_InediaPainLimbs.Find("hands") == -1)
		{
			OMD_Bridge_TickLimbBreak(painManager, pDt, "hands");
		}
		if (InediaInfectedAI_PainManager.m_InediaPainLimbs.Find("feet") == -1)
		{
			OMD_Bridge_TickLimbBreak(painManager, pDt, "feet");
		}
	}

	override void InediaInfectedAI_UpdateDeepWoundsHandler(PlayerBase player, float pDt)
	{
		super.InediaInfectedAI_UpdateDeepWoundsHandler(player, pDt);

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!player || !player.InediaInfectedAI_GetPainManager())
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager.LimbsDeepWoundSystemIsActive())
		{
			return;
		}

		if (InediaInfectedAI_PainManager.m_InediaPainLimbs.Find("hands") == -1)
		{
			OMD_Bridge_TickLimbDeepWound(painManager, pDt, "hands");
		}
		if (InediaInfectedAI_PainManager.m_InediaPainLimbs.Find("feet") == -1)
		{
			OMD_Bridge_TickLimbDeepWound(painManager, pDt, "feet");
		}

		OMD_Bridge_TickAllSutures(painManager, pDt);
	}

	override void InediaInfectedAI_UpdateBulletsHandler(PlayerBase player, float pDt)
	{
		super.InediaInfectedAI_UpdateBulletsHandler(player, pDt);

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!player || !player.InediaInfectedAI_GetPainManager())
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager.LimbsBulletSystemIsActive())
		{
			return;
		}

		if (InediaInfectedAI_PainManager.m_InediaPainLimbs.Find("hands") == -1)
		{
			OMD_Bridge_TickLimbBullets(painManager, pDt, "hands");
		}
		if (InediaInfectedAI_PainManager.m_InediaPainLimbs.Find("feet") == -1)
		{
			OMD_Bridge_TickLimbBullets(painManager, pDt, "feet");
		}
	}

	override void InediaInfectedAI_ApplyMedicineBuffsHandler(PlayerBase player, float pDt)
	{
		super.InediaInfectedAI_ApplyMedicineBuffsHandler(player, pDt);

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!player || !player.InediaInfectedAI_GetPainManager())
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (InediaInfectedAI_PainManager.m_InediaPainLimbs.Find("hands") == -1)
		{
			OMD_Bridge_ApplyLimbBoneRegen(player, painManager, pDt, "hands");
			OMD_Bridge_ApplyLimbDeepWoundRegen(player, painManager, pDt, "hands");
		}
		if (InediaInfectedAI_PainManager.m_InediaPainLimbs.Find("feet") == -1)
		{
			OMD_Bridge_ApplyLimbBoneRegen(player, painManager, pDt, "feet");
			OMD_Bridge_ApplyLimbDeepWoundRegen(player, painManager, pDt, "feet");
		}

		if (OMD_BridgeConfig.IsDebugEnabled() && painManager.IsLimbBroken("hands"))
		{
			m_OMD_Bridge_HandsBreakRegenLogSeconds = m_OMD_Bridge_HandsBreakRegenLogSeconds + pDt;
			if (m_OMD_Bridge_HandsBreakRegenLogSeconds >= 10)
			{
				m_OMD_Bridge_HandsBreakRegenLogSeconds = 0;
				float mult = painManager.GetBreakStabilizationRegenerationMultiplierForLimb("hands");
				float bone = painManager.m_BoneRegenItemRegenMultiplier;
				float timeRemaining = painManager.GetBreakTimeRemainingSecondsForLimb("hands");
				int level = 0;
				if (painManager.m_LimbsBreakRegenerationLevels)
				{
					if (painManager.m_LimbsBreakRegenerationLevels.Contains("hands"))
					{
						level = painManager.m_LimbsBreakRegenerationLevels.Get("hands");
					}
				}
				Print("[OMD_Bridge] hands break regen mult=" + mult.ToString() + " bone=" + bone.ToString() + " timeRemaining=" + timeRemaining.ToString() + " level=" + level.ToString());
			}
		}

		OMD_Bridge_ApplyWoundHealPerks(player, painManager, pDt);
		OMD_Bridge_ApplySutureHealPerk(player, painManager, pDt);
		OMD_Bridge_ApplyDeepWoundSeverityRegen(player, painManager, pDt);
		OMD_Bridge_TickDeepWoundSeveritySync(painManager, pDt);
	}

	override void InediaInfectedAI_ApplyPainDebuffsHandler(PlayerBase player, float pDt)
	{
		super.InediaInfectedAI_ApplyPainDebuffsHandler(player, pDt);
		if (OMD_BridgeConfig.IsActive())
		{
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				OMD_Bridge_LogInediaPainAndFracture(player);
			}
		}

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!player || player.IsUnconscious() || !player.InediaInfectedAI_GetPainManager())
		{
			return;
		}

		OMD_Bridge_ApplyHandsAdsShock(player, pDt);
		OMD_Bridge_ApplyFeetRunShock(player, pDt);
		OMD_Bridge_ApplyFeetRunBlock(player);
	}

	protected void OMD_Bridge_ApplyHandsAdsShock(PlayerBase player, float pDt)
	{
		if (!player.IsRaised())
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		InediaInfectedAI_LimbPainLevels handsLevel = painManager.GetPainWithBuffsLevelForLimb("hands");
		if (handsLevel < InediaInfectedAI_LimbPainLevels.LOW)
		{
			return;
		}

		float shockPerSecond = 0;
		if (handsLevel >= InediaInfectedAI_LimbPainLevels.BADLY)
		{
			shockPerSecond = OMD_BridgeConfig.GetHandsDebuffAdsShockBadly();
		}
		else if (handsLevel >= InediaInfectedAI_LimbPainLevels.MEDIUM)
		{
			shockPerSecond = OMD_BridgeConfig.GetHandsDebuffAdsShockMedium();
		}
		else
		{
			shockPerSecond = OMD_BridgeConfig.GetHandsDebuffAdsShockLow();
		}

		if (shockPerSecond <= 0)
		{
			return;
		}

		float shockMultiplier = painManager.GetActionsShockMultiplierForLimb("hands");
		float shockToApply = shockPerSecond * shockMultiplier + player.InediaInfectedAI_GetShockRefillSpeed();
		player.DecreaseHealth("GlobalHealth", "Shock", shockToApply * pDt);
	}

	protected void OMD_Bridge_ApplyFeetRunShock(PlayerBase player, float pDt)
	{
		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		InediaInfectedAI_LimbPainLevels painFeetLevel = painManager.GetPainWithBuffsLevelForLimb("feet");
		if (painFeetLevel < InediaInfectedAI_LimbPainLevels.MEDIUM)
		{
			return;
		}

		player.GetMovementState(player.m_MovementState);
		if (!player.m_MovementState)
		{
			return;
		}

		bool isRunning = false;
		bool isWalking = false;
		if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_RUN)
		{
			isRunning = true;
		}
		else if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT)
		{
			isRunning = true;
		}
		else if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_CROUCH_RUN)
		{
			isRunning = true;
		}
		else if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_WALK)
		{
			isWalking = true;
		}

		if (!isRunning && !isWalking)
		{
			return;
		}

		float feetShockDamage = 0;
		if (isRunning)
		{
			if (painFeetLevel >= InediaInfectedAI_LimbPainLevels.BADLY)
			{
				feetShockDamage = OMD_BridgeConfig.GetFeetDebuffRunShockBadly();
			}
			else if (painFeetLevel >= InediaInfectedAI_LimbPainLevels.MEDIUM)
			{
				feetShockDamage = OMD_BridgeConfig.GetFeetDebuffRunShockMedium();
			}
		}
		else
		{
			if (painFeetLevel >= InediaInfectedAI_LimbPainLevels.BADLY)
			{
				feetShockDamage = OMD_BridgeConfig.GetFeetDebuffWalkShockBadly();
			}
			else if (painFeetLevel >= InediaInfectedAI_LimbPainLevels.MEDIUM)
			{
				feetShockDamage = OMD_BridgeConfig.GetFeetDebuffWalkShockMedium();
			}

			if (!painManager.IsLimbBroken("feet") && feetShockDamage > 0)
			{
				feetShockDamage = feetShockDamage * 0.5;
			}
		}

		if (feetShockDamage <= 0)
		{
			return;
		}

		feetShockDamage = feetShockDamage * painManager.GetActionsShockMultiplierForLimb("feet");
		float loadWeightKg = player.GetPlayerLoad() / 1000;
		feetShockDamage = feetShockDamage * (1 + Math.Clamp(Math.Pow((loadWeightKg - 10) / 30, 2), 0, 4));

		float legsShockAlreadyApplied = 0;
		if (isRunning)
		{
			legsShockAlreadyApplied = OMD_Bridge_GetLegsRunShockBaseline(player, painManager);
		}

		if (feetShockDamage <= legsShockAlreadyApplied)
		{
			return;
		}

		float shockToApply = feetShockDamage - legsShockAlreadyApplied;
		if (legsShockAlreadyApplied <= 0)
		{
			shockToApply = shockToApply + player.InediaInfectedAI_GetShockRefillSpeed();
		}

		player.DecreaseHealth("GlobalHealth", "Shock", shockToApply * pDt);
	}

	protected float OMD_Bridge_GetLegsRunShockBaseline(PlayerBase player, InediaInfectedAI_PainManager painManager)
	{
		if (!player.m_InediaInfectedAI_ConfigPlayers)
		{
			return 0;
		}

		if (!player.m_InediaInfectedAI_ConfigPlayers.ShockIfRunsWithPainedLegs)
		{
			return 0;
		}

		InediaInfectedAI_LimbPainLevels painLegsLevel = painManager.GetPainWithBuffsLevelForLimb("legs");
		float legsShockDamage = 0;
		if (painLegsLevel >= InediaInfectedAI_LimbPainLevels.BADLY)
		{
			legsShockDamage = 0.4;
		}
		else if (painLegsLevel >= InediaInfectedAI_LimbPainLevels.MEDIUM)
		{
			legsShockDamage = 0.2;
		}

		if (legsShockDamage <= 0)
		{
			return 0;
		}

		legsShockDamage = legsShockDamage * painManager.GetActionsShockMultiplierForLimb("legs");
		float loadWeightKg = player.GetPlayerLoad() / 1000;
		legsShockDamage = legsShockDamage * (1 + Math.Clamp(Math.Pow((loadWeightKg - 10) / 30, 2), 0, 4));
		return legsShockDamage;
	}

	protected void OMD_Bridge_ApplyFeetRunBlock(PlayerBase player)
	{
		if (!player.OMD_Bridge_ShouldBlockRunFromFeetFracture())
		{
			return;
		}

		player.GetMovementState(player.m_MovementState);
		if (!player.m_MovementState)
		{
			return;
		}

		if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_RUN || player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT || player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_CROUCH_RUN)
		{
			HumanInputController hic = player.GetInputController();
			if (hic)
			{
				hic.LimitsDisableSprint(true);
			}
		}
	}

	protected void OMD_Bridge_TickLimbBreak(InediaInfectedAI_PainManager painManager, float pDt, string limb)
	{
		float limbBreakTimeRemainingSeconds = painManager.GetBreakTimeRemainingSecondsForLimb(limb);

		if (limbBreakTimeRemainingSeconds > 0)
		{
			if (!painManager.IsLimbBroken(limb))
			{
				bool stabilizationStatusBefore = painManager.IsLimbStabilized(limb);
				float stabilizationShockReductionMultiplierBefore = painManager.GetBreakStabilizationShockReductionMultiplierForLimb(limb);
				float stabilizationRegenerationMultiplierBefore = painManager.GetBreakStabilizationRegenerationMultiplierForLimb(limb);

				painManager.ActivateBreakForLimb(limb, 0, false, false);
				painManager.SetBreakTimeRemainingSecondsForLimb(limb, limbBreakTimeRemainingSeconds);

				if (stabilizationStatusBefore)
				{
					painManager.ActivateBreakStabilizeForLimb(limb, stabilizationShockReductionMultiplierBefore, stabilizationRegenerationMultiplierBefore);
				}
			}
			else
			{
				painManager.SetBreakTimeRemainingSecondsForLimb(limb, limbBreakTimeRemainingSeconds - pDt);
			}
		}
		else
		{
			if (painManager.IsLimbBroken(limb))
			{
				painManager.DeactivateBreakForLimb(limb);
			}
		}
	}

	protected void OMD_Bridge_TickAllSutures(InediaInfectedAI_PainManager painManager, float pDt)
	{
		OMD_Bridge_TickLimbSuture(painManager, pDt, "head");
		OMD_Bridge_TickLimbSuture(painManager, pDt, "arms");
		OMD_Bridge_TickLimbSuture(painManager, pDt, "legs");
		OMD_Bridge_TickLimbSuture(painManager, pDt, "torso");
		OMD_Bridge_TickLimbSuture(painManager, pDt, "hands");
		OMD_Bridge_TickLimbSuture(painManager, pDt, "feet");
	}

	protected void OMD_Bridge_TickLimbSuture(InediaInfectedAI_PainManager painManager, float pDt, string limb)
	{
		float remaining = painManager.OMD_Bridge_GetSutureTimeRemainingSecondsForLimb(limb);

		if (remaining > 0)
		{
			if (!painManager.OMD_Bridge_IsLimbSutured(limb))
			{
				painManager.OMD_Bridge_SetSutureActiveForLimb(limb, true);
			}
			else
			{
				float healStep = pDt;
				if (painManager.OMD_Bridge_IsSutureBandageDirty(limb))
				{
					healStep = pDt * OMD_BridgeConfig.GetSutureDirtyHealModifier();
				}

				if (healStep < 0)
				{
					healStep = 0;
				}

				painManager.OMD_Bridge_SetSutureTimeRemainingSecondsForLimb(limb, remaining - healStep);
			}

			painManager.OMD_Bridge_TickSutureBandageDirty(limb, pDt);
		}
		else
		{
			if (painManager.OMD_Bridge_IsLimbSutured(limb))
			{
				painManager.OMD_Bridge_DeactivateSutureForLimb(limb);
			}
		}
	}

	protected void OMD_Bridge_ApplySutureHealPerk(PlayerBase player, InediaInfectedAI_PainManager painManager, float pDt)
	{
		float healMult = OMD_BridgeSkills.GetWoundHealPerkMultiplier(player);
		if (healMult <= 1.0)
		{
			return;
		}

		float perkExtraFraction = healMult - 1.0;
		OMD_Bridge_ApplySutureHealPerkForLimb(painManager, pDt, perkExtraFraction, "head");
		OMD_Bridge_ApplySutureHealPerkForLimb(painManager, pDt, perkExtraFraction, "arms");
		OMD_Bridge_ApplySutureHealPerkForLimb(painManager, pDt, perkExtraFraction, "legs");
		OMD_Bridge_ApplySutureHealPerkForLimb(painManager, pDt, perkExtraFraction, "torso");
		OMD_Bridge_ApplySutureHealPerkForLimb(painManager, pDt, perkExtraFraction, "hands");
		OMD_Bridge_ApplySutureHealPerkForLimb(painManager, pDt, perkExtraFraction, "feet");
	}

	protected void OMD_Bridge_ApplySutureHealPerkForLimb(InediaInfectedAI_PainManager painManager, float pDt, float perkExtraFraction, string limb)
	{
		if (!painManager.OMD_Bridge_IsLimbSutured(limb))
		{
			return;
		}

		float remaining = painManager.OMD_Bridge_GetSutureTimeRemainingSecondsForLimb(limb);
		if (remaining <= 0)
		{
			return;
		}

		if (perkExtraFraction <= 0)
		{
			return;
		}

		painManager.OMD_Bridge_SetSutureTimeRemainingSecondsForLimb(limb, remaining - pDt * perkExtraFraction);
	}

	protected void OMD_Bridge_TickLimbDeepWound(InediaInfectedAI_PainManager painManager, float pDt, string limb)
	{
		float limbDeepWoundTimeRemainingSeconds = painManager.GetDeepWoundTimeRemainingSecondsForLimb(limb);

		if (limbDeepWoundTimeRemainingSeconds > 0)
		{
			if (!painManager.IsLimbDeepWounded(limb))
			{
				bool bandagedStatusBefore = painManager.IsLimbDeepWoundBandaged(limb);
				float bandageEffectivenessTimeRemainingSecondsBefore = painManager.GetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb(limb);
				float bandageRegenerationMultiplierBefore = painManager.GetDeepWoundBandageRegenerationMultiplierForLimb(limb);

				painManager.ActivateDeepWoundForLimb(limb, 0, -2, 0, false, false);
				painManager.SetDeepWoundTimeRemainingSecondsForLimb(limb, limbDeepWoundTimeRemainingSeconds);

				if (bandagedStatusBefore)
				{
					painManager.ActivateDeepWoundBandageForLimb(limb, bandageEffectivenessTimeRemainingSecondsBefore, bandageRegenerationMultiplierBefore);
				}
			}
			else
			{
				painManager.SetDeepWoundTimeRemainingSecondsForLimb(limb, limbDeepWoundTimeRemainingSeconds - pDt);

				float newBleedingRate = painManager.GetDeepWoundBleedingRateForLimb(limb) - InediaInfectedAI_PainManager.DEEP_WOUND_BLEEDING_RATE_REGEN_ML_SEC;
				painManager.SetDeepWoundBleedingRateForLimb(limb, Math.Clamp(newBleedingRate, InediaInfectedAI_PainManager.DEEP_WOUND_BLEEDING_RATE_MIN, InediaInfectedAI_PainManager.DEEP_WOUND_BLEEDING_RATE_MAX));
			}
		}
		else
		{
			if (painManager.IsLimbDeepWounded(limb))
			{
				painManager.DeactivateDeepWoundForLimb(limb);
			}
		}
	}

	protected void OMD_Bridge_TickLimbBullets(InediaInfectedAI_PainManager painManager, float pDt, string limb)
	{
		if (painManager.GetBulletCountInLimb(limb) > 0)
		{
			painManager.SetBulletInBodySecondsForLimb(limb, painManager.GetBulletInBodySecondsForLimb(limb) + pDt);
		}
	}

	protected void OMD_Bridge_ApplyLimbBoneRegen(PlayerBase player, InediaInfectedAI_PainManager painManager, float pDt, string limb)
	{
		if (!painManager.LimbsBreakSystemIsActive())
		{
			return;
		}

		if (!painManager.IsLimbBroken(limb))
		{
			return;
		}

		float limbBreakTimeRemainingSeconds = painManager.GetBreakTimeRemainingSecondsForLimb(limb);
		if (limbBreakTimeRemainingSeconds <= 0)
		{
			return;
		}

		float boneRegenMultiplier = 1;
		if (painManager.IsLimbStabilized(limb))
		{
			boneRegenMultiplier = boneRegenMultiplier * painManager.GetBreakStabilizationRegenerationMultiplierForLimb(limb);
		}

		if (player.GetModifiersManager().IsModifierActive(InediaInfectedAI_eModifiers.MDF_BONE_REGEN))
		{
			boneRegenMultiplier = boneRegenMultiplier * painManager.m_BoneRegenItemRegenMultiplier;
		}

		if (boneRegenMultiplier < 1)
		{
			boneRegenMultiplier = 1;
		}

		painManager.SyncBreakRegenerationLevelForLimbServer(limb, boneRegenMultiplier);

		if (boneRegenMultiplier > 1)
		{
			float additionalBoneRegen = boneRegenMultiplier - 1;
			painManager.SetBreakTimeRemainingSecondsForLimb(limb, limbBreakTimeRemainingSeconds - pDt * additionalBoneRegen);
		}
	}

	protected void OMD_Bridge_ApplyLimbDeepWoundRegen(PlayerBase player, InediaInfectedAI_PainManager painManager, float pDt, string limb)
	{
		if (!painManager.LimbsDeepWoundSystemIsActive())
		{
			return;
		}

		if (!painManager.IsLimbDeepWounded(limb))
		{
			return;
		}

		float limbDeepWoundTimeRemainingSeconds = painManager.GetDeepWoundTimeRemainingSecondsForLimb(limb);
		if (limbDeepWoundTimeRemainingSeconds <= 0)
		{
			return;
		}

		float deepWoundRegenMultiplier = 1;

		if (painManager.IsLimbDeepWoundBandaged(limb))
		{
			deepWoundRegenMultiplier = deepWoundRegenMultiplier * painManager.GetDeepWoundBandageRegenerationMultiplierForLimb(limb);

			float newEffectivenessTimeRemainingSeconds = painManager.GetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb(limb) - pDt;
			painManager.SetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb(limb, newEffectivenessTimeRemainingSeconds);

			if (newEffectivenessTimeRemainingSeconds <= 0)
			{
				if (painManager.IsLimbDeepWoundBandageEffective(limb))
				{
					painManager.SetDeepWoundBandageEffectivenessForLimb(limb, false);
				}
			}
			else
			{
				if (!painManager.IsLimbDeepWoundBandageEffective(limb))
				{
					painManager.SetDeepWoundBandageEffectivenessForLimb(limb, true);
				}
			}
		}

		if (player.GetModifiersManager().IsModifierActive(InediaInfectedAI_eModifiers.MDF_DEEP_WOUND_REGEN))
		{
			deepWoundRegenMultiplier = deepWoundRegenMultiplier * painManager.m_DeepWoundRegenItemRegenMultiplier;
		}

		if (deepWoundRegenMultiplier < 1)
		{
			deepWoundRegenMultiplier = 1;
		}

		painManager.SyncDeepWoundRegenerationLevelForLimbServer(limb, deepWoundRegenMultiplier);

		if (deepWoundRegenMultiplier > 1)
		{
			float additionalDeepWoundRegen = deepWoundRegenMultiplier - 1;
			painManager.SetDeepWoundTimeRemainingSecondsForLimb(limb, limbDeepWoundTimeRemainingSeconds - pDt * additionalDeepWoundRegen);
		}
	}

	protected void OMD_Bridge_ApplyPainHealPerk(PlayerBase player, InediaInfectedAI_PainManager painManager)
	{
		float painHealMult = OMD_BridgeSkills.GetPainHealPerkMultiplier(player);
		if (painHealMult <= 1.0)
		{
			return;
		}

		float extraFraction = painHealMult - 1.0;
		float baseRate = 0.1;
		if (player.m_InediaInfectedAI_ConfigPlayers.PainHealingRatePerSecondPercent > 0)
		{
			baseRate = player.m_InediaInfectedAI_ConfigPlayers.PainHealingRatePerSecondPercent;
		}

		float extraHeal = baseRate * extraFraction;
		if (extraHeal <= 0)
		{
			return;
		}

		int i;
		string limb;
		for (i = 0; i < InediaInfectedAI_PainManager.m_InediaPainLimbs.Count(); i++)
		{
			limb = InediaInfectedAI_PainManager.m_InediaPainLimbs.Get(i);
			if (painManager.GetPainPercentForLimb(limb) > 0)
			{
				painManager.AddPainPercentForLimb(limb, -extraHeal);
			}
		}
	}

	protected void OMD_Bridge_ApplyDeepWoundSeverityRegen(PlayerBase player, InediaInfectedAI_PainManager painManager, float pDt)
	{
		if (!painManager.LimbsDeepWoundSystemIsActive())
		{
			return;
		}

		OMD_Bridge_ApplyDeepWoundSeverityRegenForLimb(player, painManager, pDt, "head");
		OMD_Bridge_ApplyDeepWoundSeverityRegenForLimb(player, painManager, pDt, "arms");
		OMD_Bridge_ApplyDeepWoundSeverityRegenForLimb(player, painManager, pDt, "legs");
		OMD_Bridge_ApplyDeepWoundSeverityRegenForLimb(player, painManager, pDt, "torso");
		OMD_Bridge_ApplyDeepWoundSeverityRegenForLimb(player, painManager, pDt, "hands");
		OMD_Bridge_ApplyDeepWoundSeverityRegenForLimb(player, painManager, pDt, "feet");
	}

	protected void OMD_Bridge_ApplyDeepWoundSeverityRegenForLimb(PlayerBase player, InediaInfectedAI_PainManager painManager, float pDt, string limb)
	{
		if (!painManager.IsLimbDeepWounded(limb))
		{
			return;
		}

		float remaining = painManager.GetDeepWoundTimeRemainingSecondsForLimb(limb);
		if (remaining <= 0)
		{
			return;
		}

		float inediaRegenMult = OMD_BridgeSkills.RecomputeDeepWoundRegenMultiplier(player, painManager, limb);
		float healPerkMult = OMD_BridgeSkills.GetWoundHealPerkMultiplier(player);
		float inediaBaseDrain = pDt * inediaRegenMult * healPerkMult;
		float severityMult = painManager.OMD_Bridge_GetDeepWoundSeverityRegenMultiplier(limb);
		float adjustment = inediaBaseDrain * (1.0 - severityMult);
		if (adjustment == 0)
		{
			return;
		}

		float newRemaining = remaining + adjustment;
		float maxDuration = painManager.GetDeepWoundMaxDurationSecondsForLimb(limb);
		if (newRemaining > maxDuration)
		{
			newRemaining = maxDuration;
		}

		if (newRemaining < 0)
		{
			newRemaining = 0;
		}

		painManager.SetDeepWoundTimeRemainingSecondsForLimb(limb, newRemaining);
	}

	protected void OMD_Bridge_TickDeepWoundSeveritySync(InediaInfectedAI_PainManager painManager, float pDt)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		m_OMD_Bridge_SeveritySyncSeconds = m_OMD_Bridge_SeveritySyncSeconds + pDt;
		if (m_OMD_Bridge_SeveritySyncSeconds < 3)
		{
			return;
		}

		m_OMD_Bridge_SeveritySyncSeconds = 0;
		painManager.OMD_Bridge_SyncAllDeepWoundSeverities();
		OMD_Bridge_LogDeepWoundSeverity(painManager, "head");
		OMD_Bridge_LogDeepWoundSeverity(painManager, "arms");
		OMD_Bridge_LogDeepWoundSeverity(painManager, "legs");
		OMD_Bridge_LogDeepWoundSeverity(painManager, "torso");
		OMD_Bridge_LogDeepWoundSeverity(painManager, "hands");
		OMD_Bridge_LogDeepWoundSeverity(painManager, "feet");
	}

	protected void OMD_Bridge_LogDeepWoundSeverity(InediaInfectedAI_PainManager painManager, string limb)
	{
		if (!OMD_BridgeConfig.IsDebugEnabled())
		{
			return;
		}

		if (!painManager.IsLimbDeepWounded(limb))
		{
			return;
		}

		float rate = painManager.GetDeepWoundBleedingRateForLimb(limb);
		int tier = painManager.OMD_Bridge_GetDeepWoundSeverityTierForLimb(limb);
		bool controlled = painManager.OMD_Bridge_HasEffectiveBleedControl(limb);
		float mult = painManager.OMD_Bridge_GetDeepWoundSeverityRegenMultiplier(limb);
		float timeRemaining = painManager.GetDeepWoundTimeRemainingSecondsForLimb(limb);
		Print("[OMD_Bridge] deepWoundSeverity limb=" + limb + " rate=" + rate.ToString() + " tier=" + tier.ToString() + " controlled=" + controlled.ToString() + " mult=" + mult.ToString() + " timeRemaining=" + timeRemaining.ToString());
	}

	protected void OMD_Bridge_ApplyWoundHealPerks(PlayerBase player, InediaInfectedAI_PainManager painManager, float pDt)
	{
		float healMult = OMD_BridgeSkills.GetWoundHealPerkMultiplier(player);
		if (healMult <= 1.0)
		{
			return;
		}

		float perkExtraFraction = healMult - 1.0;
		int i;
		string limb;
		float boneM;
		float woundM;
		float remaining;
		float extraRegen;

		if (painManager.LimbsBreakSystemIsActive())
		{
			for (i = 0; i < InediaInfectedAI_PainManager.m_InediaPainLimbs.Count(); i++)
			{
				limb = InediaInfectedAI_PainManager.m_InediaPainLimbs.Get(i);
				if (limb == "legs")
				{
					continue;
				}

				if (!painManager.IsLimbBroken(limb))
				{
					continue;
				}

				remaining = painManager.GetBreakTimeRemainingSecondsForLimb(limb);
				if (remaining <= 0)
				{
					continue;
				}

				boneM = OMD_BridgeSkills.RecomputeBoneRegenMultiplier(player, painManager, limb);
				extraRegen = boneM * perkExtraFraction;
				if (extraRegen > 0)
				{
					painManager.SetBreakTimeRemainingSecondsForLimb(limb, remaining - pDt * extraRegen);
				}
			}
		}

		if (painManager.LimbsDeepWoundSystemIsActive())
		{
			for (i = 0; i < InediaInfectedAI_PainManager.m_InediaPainLimbs.Count(); i++)
			{
				limb = InediaInfectedAI_PainManager.m_InediaPainLimbs.Get(i);
				if (!painManager.IsLimbDeepWounded(limb))
				{
					continue;
				}

				remaining = painManager.GetDeepWoundTimeRemainingSecondsForLimb(limb);
				if (remaining <= 0)
				{
					continue;
				}

				woundM = OMD_BridgeSkills.RecomputeDeepWoundRegenMultiplier(player, painManager, limb);
				extraRegen = woundM * perkExtraFraction;
				if (extraRegen > 0)
				{
					painManager.SetDeepWoundTimeRemainingSecondsForLimb(limb, remaining - pDt * extraRegen);
				}
			}
		}
	}

	protected void OMD_Bridge_HealBridgeLimbPain(PlayerBase player, InediaInfectedAI_PainManager painManager, string limb)
	{
		if (painManager.GetPainPercentForLimb(limb) > 0)
		{
			if (player.m_InediaInfectedAI_ConfigPlayers.PainHealingRatePerSecondPercent > 0)
			{
				painManager.AddPainPercentForLimb(limb, -player.m_InediaInfectedAI_ConfigPlayers.PainHealingRatePerSecondPercent);
			}
			else
			{
				painManager.AddPainPercentForLimb(limb, -0.1);
			}
		}
		else
		{
			if (painManager.GetMinimumPainPercentForLimb(limb) > 0)
			{
				painManager.AddPainPercentForLimb(limb, -1);
			}
		}
	}

	protected void OMD_Bridge_LogBridgeLimbPainTick(InediaInfectedAI_PainManager painManager, float pDt, string limb)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsDebugEnabled())
		{
			return;
		}

		if (limb == "hands")
		{
			m_OMD_Bridge_HandsPainLogSeconds = m_OMD_Bridge_HandsPainLogSeconds + pDt;
			if (m_OMD_Bridge_HandsPainLogSeconds < 10)
			{
				return;
			}

			m_OMD_Bridge_HandsPainLogSeconds = 0;
			float handsPain = painManager.GetPainPercentForLimb("hands");
			Print("[OMD_Bridge] hands pain tick=" + handsPain.ToString());
			return;
		}

		if (limb == "feet")
		{
			m_OMD_Bridge_FeetPainLogSeconds = m_OMD_Bridge_FeetPainLogSeconds + pDt;
			if (m_OMD_Bridge_FeetPainLogSeconds < 10)
			{
				return;
			}

			m_OMD_Bridge_FeetPainLogSeconds = 0;
			float feetPain = painManager.GetPainPercentForLimb("feet");
			Print("[OMD_Bridge] feet pain tick=" + feetPain.ToString());
		}
	}

	protected bool OMD_Bridge_SymptomServer()
	{
		if (!GetGame())
		{
			return false;
		}

		if (!GetGame().IsServer())
		{
			return false;
		}

		return true;
	}

	protected int OMD_Bridge_SymptomPainLevel(InediaInfectedAI_LimbPainLevels level)
	{
		if (level == InediaInfectedAI_LimbPainLevels.LOW)
		{
			return 1;
		}

		if (level == InediaInfectedAI_LimbPainLevels.MEDIUM)
		{
			return 2;
		}

		if (level == InediaInfectedAI_LimbPainLevels.BADLY)
		{
			return 3;
		}

		if (level == InediaInfectedAI_LimbPainLevels.CRITICAL)
		{
			return 4;
		}

		return 0;
	}

	protected void OMD_Bridge_LogInediaInt(string zone, string effect, int level, float value, string cause)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsDebugEnabled())
		{
			return;
		}

		if (!m_OMD_Symptom_InediaState)
		{
			m_OMD_Symptom_InediaState = new map<string, int>();
		}

		string key;
		key = effect + ":" + zone;
		bool known;
		known = m_OMD_Symptom_InediaState.Contains(key);
		int previous;
		previous = 0;
		if (known)
		{
			previous = m_OMD_Symptom_InediaState.Get(key);
		}

		if (!known)
		{
			m_OMD_Symptom_InediaState.Set(key, level);
			if (level <= 0)
			{
				return;
			}

			OMD_LogSymptom("INEDIA", zone, level, effect, "on", value, cause);
			return;
		}

		if (level == previous)
		{
			return;
		}

		string state;
		state = "off";
		if (level > previous)
		{
			state = "on";
		}
		m_OMD_Symptom_InediaState.Set(key, level);
		OMD_LogSymptom("INEDIA", zone, level, effect, state, value, cause);
	}

	protected bool OMD_Bridge_SymptomTickDue(string key, float pDt)
	{
		if (!m_OMD_Symptom_InediaTick)
		{
			m_OMD_Symptom_InediaTick = new map<string, float>();
		}

		float acc;
		acc = 0;
		if (m_OMD_Symptom_InediaTick.Contains(key))
		{
			acc = m_OMD_Symptom_InediaTick.Get(key);
		}
		acc = acc + pDt;
		if (acc < 10)
		{
			m_OMD_Symptom_InediaTick.Set(key, acc);
			return false;
		}

		m_OMD_Symptom_InediaTick.Set(key, 0);
		return true;
	}

	protected void OMD_Bridge_LogInediaPainLimb(InediaInfectedAI_PainManager painManager, string limb)
	{
		int level;
		level = OMD_Bridge_SymptomPainLevel(painManager.GetPainWithBuffsLevelForLimb(limb));
		float percent;
		percent = painManager.GetPainPercentForLimb(limb);
		OMD_Bridge_LogInediaInt(limb, "Pain", level, percent, "painLevel");
	}

	protected void OMD_Bridge_LogInediaFractureLimb(InediaInfectedAI_PainManager painManager, string limb)
	{
		int broken;
		broken = 0;
		if (painManager.IsLimbBroken(limb))
		{
			broken = 1;
		}
		OMD_Bridge_LogInediaInt(limb, "Fracture", broken, broken, "break");
	}

	protected void OMD_Bridge_LogInediaDeepLimb(InediaInfectedAI_PainManager painManager, string limb)
	{
		int wounded;
		wounded = 0;
		float rate;
		rate = 0;
		if (painManager.IsLimbDeepWounded(limb))
		{
			wounded = 1;
			rate = painManager.GetDeepWoundBleedingRateForLimb(limb);
		}
		OMD_Bridge_LogInediaInt(limb, "DeepWound", wounded, rate, "deepWound");
	}

	protected void OMD_Bridge_LogInediaBulletLimb(InediaInfectedAI_PainManager painManager, string limb, float pDt)
	{
		int count;
		count = painManager.GetBulletCountInLimb(limb);
		OMD_Bridge_LogInediaInt(limb, "Bullet", count, count, "bullet");

		int heavy;
		heavy = 0;
		if (count > 0 && painManager.LimbsBulletSystemIsActive())
		{
			InediaInfectedAI_BulletInBodyStages stage;
			stage = painManager.GetBulletInBodyStageForLimb(limb);
			if (stage >= InediaInfectedAI_BulletInBodyStages.SECOND)
			{
				heavy = 1;
			}
		}
		OMD_Bridge_LogInediaInt(limb, "HEAVYMETAL", heavy, heavy, "bullet");
		if (heavy == 1)
		{
			if (OMD_Bridge_SymptomTickDue("HEAVYMETAL:" + limb, pDt))
			{
				OMD_LogSymptom("INEDIA", limb, 2, "HEAVYMETAL", "tick", 2, "bullet");
			}
		}
	}

	protected void OMD_Bridge_LogInediaPainAndFracture(PlayerBase player)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsDebugEnabled())
		{
			return;
		}

		if (!OMD_Bridge_SymptomServer())
		{
			return;
		}

		if (!player)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager;
		painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return;
		}

		OMD_Bridge_LogInediaPainLimb(painManager, "head");
		OMD_Bridge_LogInediaPainLimb(painManager, "arms");
		OMD_Bridge_LogInediaPainLimb(painManager, "legs");
		OMD_Bridge_LogInediaPainLimb(painManager, "torso");
		OMD_Bridge_LogInediaPainLimb(painManager, "hands");
		OMD_Bridge_LogInediaPainLimb(painManager, "feet");
		OMD_Bridge_LogInediaFractureLimb(painManager, "head");
		OMD_Bridge_LogInediaFractureLimb(painManager, "arms");
		OMD_Bridge_LogInediaFractureLimb(painManager, "legs");
		OMD_Bridge_LogInediaFractureLimb(painManager, "torso");
		OMD_Bridge_LogInediaFractureLimb(painManager, "hands");
		OMD_Bridge_LogInediaFractureLimb(painManager, "feet");
	}

	protected void OMD_Bridge_LogDeepWoundSymptoms(PlayerBase player, float pDt)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsDebugEnabled())
		{
			return;
		}

		if (!OMD_Bridge_SymptomServer())
		{
			return;
		}

		if (!player)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager;
		painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return;
		}

		OMD_Bridge_LogInediaDeepLimb(painManager, "head");
		OMD_Bridge_LogInediaDeepLimb(painManager, "arms");
		OMD_Bridge_LogInediaDeepLimb(painManager, "legs");
		OMD_Bridge_LogInediaDeepLimb(painManager, "torso");
		OMD_Bridge_LogInediaDeepLimb(painManager, "hands");
		OMD_Bridge_LogInediaDeepLimb(painManager, "feet");

		float rate;
		rate = painManager.GetDeepWoundsBleedingRateWithMultipliers();
		int active;
		active = 0;
		if (rate > 0)
		{
			active = 1;
		}
		OMD_Bridge_LogInediaInt("body", "DeepWoundBleed", active, rate, "bleed");
		if (active == 1)
		{
			if (OMD_Bridge_SymptomTickDue("DeepWoundBleed:body", pDt))
			{
				OMD_LogSymptom("INEDIA", "body", 1, "DeepWoundBleed", "tick", rate, "bleed");
			}
		}
	}

	protected void OMD_Bridge_LogBulletSymptoms(PlayerBase player, float pDt)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsDebugEnabled())
		{
			return;
		}

		if (!OMD_Bridge_SymptomServer())
		{
			return;
		}

		if (!player)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager;
		painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return;
		}

		OMD_Bridge_LogInediaBulletLimb(painManager, "head", pDt);
		OMD_Bridge_LogInediaBulletLimb(painManager, "arms", pDt);
		OMD_Bridge_LogInediaBulletLimb(painManager, "legs", pDt);
		OMD_Bridge_LogInediaBulletLimb(painManager, "torso", pDt);
		OMD_Bridge_LogInediaBulletLimb(painManager, "hands", pDt);
		OMD_Bridge_LogInediaBulletLimb(painManager, "feet", pDt);
	}

	protected void OMD_Bridge_LogInternalBleedingSymptoms(PlayerBase player, float pDt)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsDebugEnabled())
		{
			return;
		}

		if (!OMD_Bridge_SymptomServer())
		{
			return;
		}

		if (!player)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager;
		painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return;
		}

		float rate;
		rate = 0;
		int active;
		active = 0;
		if (painManager.IsInternalBleedingActive())
		{
			active = 1;
			if (player.m_InediaInfectedAI_ConfigPlayers)
			{
				rate = player.m_InediaInfectedAI_ConfigPlayers.InternalBleedingBloodLossRateMl;
			}
			if (player.GetModifiersManager())
			{
				if (player.GetModifiersManager().IsModifierActive(InediaInfectedAI_eModifiers.MDF_BLOOD_CLOTTING))
				{
					if (painManager.m_BloodClottingItemClottingMultiplier > 1)
					{
						rate = rate / painManager.m_BloodClottingItemClottingMultiplier;
					}
				}
			}
		}

		OMD_Bridge_LogInediaInt("body", "InternalBleeding", active, rate, "bleed");
		if (active == 1)
		{
			if (OMD_Bridge_SymptomTickDue("InternalBleeding:body", pDt))
			{
				OMD_LogSymptom("INEDIA", "body", 1, "InternalBleeding", "tick", rate, "bleed");
			}
		}
	}
};
