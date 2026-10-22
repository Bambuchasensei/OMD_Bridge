modded class InediaInfectedAI_PainManager
{
	float m_PainHandsPercent = 0;
	float m_PainFeetPercent = 0;

	float m_PainHandsWithBuffsPercent = 0;
	float m_PainFeetWithBuffsPercent = 0;

	InediaInfectedAI_LimbPainLevels m_PainHandsLevel = InediaInfectedAI_LimbPainLevels.ZERO;
	InediaInfectedAI_LimbPainLevels m_PainFeetLevel = InediaInfectedAI_LimbPainLevels.ZERO;
	InediaInfectedAI_LimbPainLevels m_PainHandsWithBuffsLevel = InediaInfectedAI_LimbPainLevels.ZERO;
	InediaInfectedAI_LimbPainLevels m_PainFeetWithBuffsLevel = InediaInfectedAI_LimbPainLevels.ZERO;

	bool m_OMD_Bridge_RedirectArmsPainToHands = false;
	bool m_OMD_Bridge_SutureHitBandageWasDirty = false;

	float m_BreakHandsTimeRemainingSeconds = 0;
	float m_HandsDeepWoundTimeRemainingSeconds = 0;
	float m_HandsDeepWoundBleedingRate = 0;
	float m_HandsDeepWoundBandageItemRegenerationMultiplier = 1;
	float m_HandsDeepWoundBandageItemEffectivenessTimeRemainingSeconds = 0;
	float m_HandsBreakStabilizationItemShockReductionMultiplier = 1;
	float m_HandsBreakStabilizationItemRegenerationMultiplier = 1;
	float m_HandsBulletInBodySeconds = 0;
	float m_BreakHandsLastActivateTime = -1000000;
	float m_HandsDeepWoundLastActivateTime = -1000000;

	float m_BreakFeetTimeRemainingSeconds = 0;
	float m_FeetDeepWoundTimeRemainingSeconds = 0;
	float m_FeetDeepWoundBleedingRate = 0;
	float m_FeetDeepWoundBandageItemRegenerationMultiplier = 1;
	float m_FeetDeepWoundBandageItemEffectivenessTimeRemainingSeconds = 0;
	float m_FeetBreakStabilizationItemShockReductionMultiplier = 1;
	float m_FeetBreakStabilizationItemRegenerationMultiplier = 1;
	float m_FeetBulletInBodySeconds = 0;
	float m_BreakFeetLastActivateTime = -1000000;
	float m_FeetDeepWoundLastActivateTime = -1000000;

	float m_SutureHeadTimeRemainingSeconds = 0;
	float m_SutureArmsTimeRemainingSeconds = 0;
	float m_SutureLegsTimeRemainingSeconds = 0;
	float m_SutureTorsoTimeRemainingSeconds = 0;
	float m_SutureHandsTimeRemainingSeconds = 0;
	float m_SutureFeetTimeRemainingSeconds = 0;

	int m_SutureWoundTierHead = 0;
	int m_SutureWoundTierArms = 0;
	int m_SutureWoundTierLegs = 0;
	int m_SutureWoundTierTorso = 0;
	int m_SutureWoundTierHands = 0;
	int m_SutureWoundTierFeet = 0;

	float m_SutureBandageDirtyProgressHead = 0;
	float m_SutureBandageDirtyProgressArms = 0;
	float m_SutureBandageDirtyProgressLegs = 0;
	float m_SutureBandageDirtyProgressTorso = 0;
	float m_SutureBandageDirtyProgressHands = 0;
	float m_SutureBandageDirtyProgressFeet = 0;

	bool m_SutureBandageUsedRagHead = false;
	bool m_SutureBandageUsedRagArms = false;
	bool m_SutureBandageUsedRagLegs = false;
	bool m_SutureBandageUsedRagTorso = false;
	bool m_SutureBandageUsedRagHands = false;
	bool m_SutureBandageUsedRagFeet = false;

	int m_OMD_Bridge_SutureScratchPendingHead = 0;
	int m_OMD_Bridge_SutureScratchPendingArms = 0;
	int m_OMD_Bridge_SutureScratchPendingLegs = 0;
	int m_OMD_Bridge_SutureScratchPendingTorso = 0;
	int m_OMD_Bridge_SutureScratchPendingHands = 0;
	int m_OMD_Bridge_SutureScratchPendingFeet = 0;


	override string GetInediaPainLimbFromDmgZone(string dmgZone)
	{
		if (OMD_BridgeConfig.IsActive())
		{
			if (dmgZone == "LeftHand" || dmgZone == "RightHand")
			{
				return "hands";
			}

			if (dmgZone == "LeftFoot" || dmgZone == "RightFoot")
			{
				return "feet";
			}
		}

		return super.GetInediaPainLimbFromDmgZone(dmgZone);
	}

	override void AddPainPercentForLimb(string limb, float painDamage, bool painActions = false, EntityAI source = null, int damageType = DT_CLOSE_COMBAT)
	{
		if (OMD_BridgeConfig.IsActive() && m_OMD_Bridge_RedirectArmsPainToHands && limb == "arms")
		{
			limb = "hands";
		}

		if (limb == "hands")
		{
			OMD_Bridge_AddPainPercentForBridgeLimb("hands", painDamage, painActions, source, damageType);
			return;
		}

		if (limb == "feet")
		{
			OMD_Bridge_AddPainPercentForBridgeLimb("feet", painDamage, painActions, source, damageType);
			return;
		}

		super.AddPainPercentForLimb(limb, painDamage, painActions, source, damageType);
	}

	override float GetPainPercentForLimb(string limb)
	{
		if (limb == "hands")
		{
			if (!PainSystemIsActive())
			{
				return 0;
			}

			return m_PainHandsPercent;
		}

		if (limb == "feet")
		{
			if (!PainSystemIsActive())
			{
				return 0;
			}

			return m_PainFeetPercent;
		}

		return super.GetPainPercentForLimb(limb);
	}

	override float GetMinimumPainPercentForLimb(string limb)
	{
		float minPercent = super.GetMinimumPainPercentForLimb(limb);
		if (!OMD_BridgeConfig.IsActive() || !PainSystemIsActive())
		{
			return minPercent;
		}

		float scratchMinPercent = OMD_Bridge_GetScratchMinPainPercentForLimb(limb);
		if (scratchMinPercent > minPercent)
		{
			minPercent = scratchMinPercent;
		}

		return minPercent;
	}

	float OMD_Bridge_GetScratchMinPainPercentForLimb(string limb)
	{
		if (!m_Player)
		{
			return 0;
		}

		if (m_Player.OMD_Bridge_CountLimbScratches(limb) <= 0)
		{
			return 0;
		}

		return OMD_BridgeConfig.GetScratchMinPainPercentForLimb(limb);
	}

	void OMD_Bridge_EnsureMinPainFloorForLimb(string limb)
	{
		if (!OMD_BridgeConfig.IsActive() || !PainSystemIsActive())
		{
			return;
		}

		float minimumPainPercent = GetMinimumPainPercentForLimb(limb);
		if (minimumPainPercent <= 0)
		{
			return;
		}

		if (GetPainPercentForLimb(limb) >= minimumPainPercent)
		{
			return;
		}

		AddPainPercentForLimb(limb, -1);
	}

	override void SetPainLevelForLimb(string limb, InediaInfectedAI_LimbPainLevels level)
	{
		if (limb == "hands")
		{
			if (!PainSystemIsActive())
			{
				return;
			}

			m_PainHandsLevel = level;
			return;
		}

		if (limb == "feet")
		{
			if (!PainSystemIsActive())
			{
				return;
			}

			m_PainFeetLevel = level;
			return;
		}

		super.SetPainLevelForLimb(limb, level);
	}

	override InediaInfectedAI_LimbPainLevels GetPainLevelForLimb(string limb)
	{
		if (limb == "hands")
		{
			if (!PainSystemIsActive())
			{
				return InediaInfectedAI_LimbPainLevels.ZERO;
			}

			return m_PainHandsLevel;
		}

		if (limb == "feet")
		{
			if (!PainSystemIsActive())
			{
				return InediaInfectedAI_LimbPainLevels.ZERO;
			}

			return m_PainFeetLevel;
		}

		return super.GetPainLevelForLimb(limb);
	}

	override void SetPainWithBuffsPercentForLimb(string limb, float value)
	{
		if (limb == "hands")
		{
			if (!PainSystemIsActive())
			{
				return;
			}

			m_PainHandsWithBuffsPercent = Math.Clamp(value, 0, 100);
			return;
		}

		if (limb == "feet")
		{
			if (!PainSystemIsActive())
			{
				return;
			}

			m_PainFeetWithBuffsPercent = Math.Clamp(value, 0, 100);
			return;
		}

		super.SetPainWithBuffsPercentForLimb(limb, value);
	}

	override float GetPainWithBuffsPercentForLimb(string limb)
	{
		if (limb == "hands")
		{
			if (!PainSystemIsActive())
			{
				return 0;
			}

			return m_PainHandsWithBuffsPercent;
		}

		if (limb == "feet")
		{
			if (!PainSystemIsActive())
			{
				return 0;
			}

			return m_PainFeetWithBuffsPercent;
		}

		return super.GetPainWithBuffsPercentForLimb(limb);
	}

	override void SetPainWithBuffsLevelForLimb(string limb, InediaInfectedAI_LimbPainLevels level)
	{
		if (limb == "hands")
		{
			if (!PainSystemIsActive())
			{
				return;
			}

			m_PainHandsWithBuffsLevel = level;
			return;
		}

		if (limb == "feet")
		{
			if (!PainSystemIsActive())
			{
				return;
			}

			m_PainFeetWithBuffsLevel = level;
			return;
		}

		super.SetPainWithBuffsLevelForLimb(limb, level);
	}

	override InediaInfectedAI_LimbPainLevels GetPainWithBuffsLevelForLimb(string limb)
	{
		if (limb == "hands")
		{
			if (!PainSystemIsActive())
			{
				return InediaInfectedAI_LimbPainLevels.ZERO;
			}

			return m_PainHandsWithBuffsLevel;
		}

		if (limb == "feet")
		{
			if (!PainSystemIsActive())
			{
				return InediaInfectedAI_LimbPainLevels.ZERO;
			}

			return m_PainFeetWithBuffsLevel;
		}

		return super.GetPainWithBuffsLevelForLimb(limb);
	}

	override void UpdatePainLevelsForAllLimbs()
	{
		InediaInfectedAI_LimbPainLevels handsBefore = m_PainHandsWithBuffsLevel;
		InediaInfectedAI_LimbPainLevels feetBefore = m_PainFeetWithBuffsLevel;

		super.UpdatePainLevelsForAllLimbs();

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (m_InediaPainLimbs.Find("hands") == -1 || m_InediaPainLimbs.Find("feet") == -1)
		{
			OMD_Bridge_UpdateBridgeLimbsPainLevels();
			return;
		}

		if (m_PainHandsWithBuffsLevel != handsBefore || m_PainFeetWithBuffsLevel != feetBefore)
		{
			OMD_Bridge_SyncPainLevelsServer();
		}
	}

	override void ProcessPainDamage(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.ProcessPainDamage(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (GetGame().IsServer())
		{
			if (OMD_BridgeConfig.OMD_Bridge_IsServiceHitAmmo(ammo))
			{
				if (OMD_BridgeConfig.IsDebugEnabled())
				{
					Print("[OMD_Bridge] service hit skip ammo=" + ammo);
				}

				return;
			}
		}

		bool skipArmorScratch = false;
		if (GetGame().IsServer())
		{
			if (OMD_Bridge_ShouldSkipArmorScratch(dmgZone, ammo, component, source, modelPos))
			{
				skipArmorScratch = true;
				if (OMD_BridgeConfig.IsDebugEnabled())
				{
					Print("[OMD_Bridge] armor scratch skip zone=" + dmgZone + " ammo=" + ammo);
				}
			}
		}

		OMD_Bridge_LogPainHit(dmgZone);

		string sutureHitLimb = GetInediaPainLimbFromDmgZone(dmgZone);
		int sutureScratchesBefore = 0;
		bool sutureWasActive = false;
		m_OMD_Bridge_SutureHitBandageWasDirty = false;
		if (sutureHitLimb != "" && m_Player)
		{
			sutureWasActive = OMD_Bridge_IsLimbSutured(sutureHitLimb);
			sutureScratchesBefore = m_Player.OMD_Bridge_CountLimbScratches(sutureHitLimb);
			string sutureBandageLimb = OMD_Bridge_ResolveSuturedLimbForHit(sutureHitLimb);
			if (sutureBandageLimb != "")
			{
				m_OMD_Bridge_SutureHitBandageWasDirty = OMD_Bridge_IsSutureBandageDirty(sutureBandageLimb);
			}
		}

		if (!skipArmorScratch)
		{
			OMD_Bridge_ProcessHitScratches(damageResult, dmgZone);
		}

		OMD_Bridge_TryTearSutureOnHit(damageResult, dmgZone);
		OMD_Bridge_BlockSutureTearScratchBoost(sutureHitLimb, sutureWasActive, sutureScratchesBefore);
		m_OMD_Bridge_SutureHitBandageWasDirty = false;
	}

	protected bool OMD_Bridge_ShouldSkipArmorScratch(string dmgZone, string ammo, int component, EntityAI source, vector modelPos)
	{
		if (!OMD_BridgeConfig.IsArmorScratchBlockEnabled())
		{
			return false;
		}

		if (!OMD_BridgeConfig.OMD_Bridge_IsArmorScratchBlockAmmo(ammo))
		{
			return false;
		}

		if (!m_Player)
		{
			return false;
		}

		return m_Player.OMD_Bridge_IsZoneArmorCovered(dmgZone, ammo, component, source, modelPos);
	}

	override void RunPainActionsForLimb(string limb, float painDamage, EntityAI source = null, int damageType = DT_CLOSE_COMBAT)
	{
		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_RunPainActionsForHands(painDamage, source, damageType);
			return;
		}

		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_RunPainActionsForFeet(painDamage, source, damageType);
			return;
		}

		super.RunPainActionsForLimb(limb, painDamage, source, damageType);
	}

	override void OnStoreSave()
	{
		super.OnStoreSave();
		OMD_Bridge_OnStoreSave();
	}

	override void OnStoreLoad()
	{
		super.OnStoreLoad();
		OMD_Bridge_OnStoreLoad();
	}

	override void ResetDebuffsInPlayerStorage()
	{
		super.ResetDebuffsInPlayerStorage();
		OMD_Bridge_ResetDebuffsInPlayerStorage();
	}

	void OMD_Bridge_BeginArmsToHandsRedirect()
	{
		m_OMD_Bridge_RedirectArmsPainToHands = true;
	}

	void OMD_Bridge_EndArmsToHandsRedirect()
	{
		m_OMD_Bridge_RedirectArmsPainToHands = false;
	}

	void OMD_Bridge_ApplySyncedPainLevels(int handsWithBuffsLevel, int feetWithBuffsLevel)
	{
		m_PainHandsWithBuffsLevel = OMD_Bridge_IntToPainLevel(handsWithBuffsLevel);
		m_PainFeetWithBuffsLevel = OMD_Bridge_IntToPainLevel(feetWithBuffsLevel);
		m_PainHandsLevel = m_PainHandsWithBuffsLevel;
		m_PainFeetLevel = m_PainFeetWithBuffsLevel;
	}

	protected void OMD_Bridge_AddPainPercentForBridgeLimb(string limb, float painDamage, bool painActions, EntityAI source, int damageType)
	{
		if (!PainSystemIsActive() || !m_Player.m_InediaInfectedAI_ConfigPlayers || !m_Player.GetAllowDamage() || painDamage == 0)
		{
			return;
		}

		float limbPainPercentNewValue = Math.Clamp(GetPainPercentForLimb(limb) + painDamage, 0, 100);

		float minimumPainPercent = GetMinimumPainPercentForLimb(limb);
		if (limbPainPercentNewValue < minimumPainPercent)
		{
			limbPainPercentNewValue = minimumPainPercent;
		}

		if (limb == "hands")
		{
			m_PainHandsPercent = limbPainPercentNewValue;
		}
		else if (limb == "feet")
		{
			m_PainFeetPercent = limbPainPercentNewValue;
		}

		if (painActions)
		{
			RunPainActionsForLimb(limb, painDamage, source, damageType);
		}
		else
		{
			UpdatePainLevelsForAllLimbs();
		}
	}

	protected void OMD_Bridge_UpdateBridgeLimbsPainLevels()
	{
		if (!PainSystemIsActive() || !m_Player.m_InediaInfectedAI_ConfigPlayers)
		{
			return;
		}

		bool needSync = false;

		if (OMD_Bridge_UpdateOneBridgeLimbPainLevels("hands"))
		{
			needSync = true;
		}

		if (OMD_Bridge_UpdateOneBridgeLimbPainLevels("feet"))
		{
			needSync = true;
		}

		if (needSync)
		{
			OMD_Bridge_SyncPainLevelsServer();
		}
	}

	protected bool OMD_Bridge_UpdateOneBridgeLimbPainLevels(string limb)
	{
		float limbPainPercent = GetPainPercentForLimb(limb);
		InediaInfectedAI_LimbPainLevels limbPainLevelBefore = GetPainLevelForLimb(limb);
		InediaInfectedAI_LimbPainLevels limbPainLevelAfter = OMD_Bridge_PercentToPainLevel(limbPainPercent);

		bool changed = false;

		if (limbPainLevelBefore != limbPainLevelAfter)
		{
			SetPainLevelForLimb(limb, limbPainLevelAfter);
			changed = true;
		}

		float limbPainWithBuffsPercent = limbPainPercent;

		if (PainkillerStrongEffectIsActive())
		{
			limbPainWithBuffsPercent = limbPainPercent - 100;
		}
		else if (PainkillerMediumEffectIsActive())
		{
			limbPainWithBuffsPercent = limbPainPercent - 50;
		}
		else if (PainkillerLightEffectIsActive())
		{
			limbPainWithBuffsPercent = limbPainPercent - 30;
		}

		InediaInfectedAI_LimbPainLevels limbPainWithBuffsLevelBefore = GetPainWithBuffsLevelForLimb(limb);
		InediaInfectedAI_LimbPainLevels limbPainWithBuffsLevelAfter = OMD_Bridge_PercentToPainLevel(limbPainWithBuffsPercent);

		SetPainWithBuffsPercentForLimb(limb, limbPainWithBuffsPercent);

		if (limbPainWithBuffsLevelBefore != limbPainWithBuffsLevelAfter)
		{
			SetPainWithBuffsLevelForLimb(limb, limbPainWithBuffsLevelAfter);
			changed = true;
		}

		return changed;
	}

	protected InediaInfectedAI_LimbPainLevels OMD_Bridge_PercentToPainLevel(float limbPainPercent)
	{
		if (limbPainPercent <= InediaInfectedAI_LimbPainLevelsBorders.ZERO)
		{
			return InediaInfectedAI_LimbPainLevels.ZERO;
		}

		if (limbPainPercent <= InediaInfectedAI_LimbPainLevelsBorders.LOW)
		{
			return InediaInfectedAI_LimbPainLevels.LOW;
		}

		if (limbPainPercent <= InediaInfectedAI_LimbPainLevelsBorders.MEDIUM)
		{
			return InediaInfectedAI_LimbPainLevels.MEDIUM;
		}

		if (limbPainPercent <= InediaInfectedAI_LimbPainLevelsBorders.BADLY)
		{
			return InediaInfectedAI_LimbPainLevels.BADLY;
		}

		return InediaInfectedAI_LimbPainLevels.CRITICAL;
	}

	protected InediaInfectedAI_LimbPainLevels OMD_Bridge_IntToPainLevel(int level)
	{
		if (level <= 0)
		{
			return InediaInfectedAI_LimbPainLevels.ZERO;
		}

		if (level == 1)
		{
			return InediaInfectedAI_LimbPainLevels.LOW;
		}

		if (level == 2)
		{
			return InediaInfectedAI_LimbPainLevels.MEDIUM;
		}

		if (level == 3)
		{
			return InediaInfectedAI_LimbPainLevels.BADLY;
		}

		return InediaInfectedAI_LimbPainLevels.CRITICAL;
	}

	protected void OMD_Bridge_SyncPainLevelsServer()
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (!m_Player)
		{
			return;
		}

		m_Player.OMD_Bridge_SetPainLevelsSync(m_PainHandsWithBuffsLevel, m_PainFeetWithBuffsLevel);
	}

	protected void OMD_Bridge_RunPainActionsForHands(float painDamage, EntityAI source, int damageType)
	{
		if (!PainSystemIsActive() || !m_Player.m_InediaInfectedAI_ConfigPlayers || painDamage <= 0)
		{
			return;
		}

		UpdatePainLevelsForAllLimbs();
		InediaInfectedAI_LimbPainLevels limbPainWithBuffsLevel = GetPainWithBuffsLevelForLimb("hands");

		if (painDamage >= 2 && limbPainWithBuffsLevel >= InediaInfectedAI_LimbPainLevels.LOW)
		{
			OMD_Bridge_TryKnockItemFromHands(painDamage);
		}

		if (CanLimbBeBrokenAfterHit("hands", painDamage))
		{
			ActivateBreakForLimb("hands", 60);
			OMD_Bridge_TryKnockItemFromHandsOnFracture();
		}

		if (painDamage >= 3 && Math.RandomFloatInclusive(0, 100) <= 20 && IsLimbDeepWounded("hands"))
		{
			float deepWoundIncreasedTime = Math.Clamp(GetDeepWoundTimeRemainingSecondsForLimb("hands") + 300, 0, GetDeepWoundMaxDurationSecondsForLimb("hands"));
			SetDeepWoundTimeRemainingSecondsForLimb("hands", deepWoundIncreasedTime);

			if (IsLimbDeepWoundBandaged("hands") && IsLimbDeepWoundBandageEffective("hands"))
			{
				SetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb("hands", 0);
			}
		}
	}

	protected void OMD_Bridge_TryKnockItemFromHands(float painDamage)
	{
		if (!m_Player)
		{
			return;
		}

		float dropChance = GetPainWithBuffsPercentForLimb("hands") * OMD_BridgeConfig.GetHandsDebuffDropChancePerPainPercent();
		dropChance = dropChance * GetActionsShockMultiplierForLimb("hands");
		if (dropChance <= 0)
		{
			return;
		}

		if (Math.RandomFloatInclusive(0, 100) <= dropChance)
		{
			m_Player.InediaInfectedAI_KnockItemOutOfHands();
		}
	}

	protected void OMD_Bridge_TryKnockItemFromHandsOnFracture()
	{
		if (!m_Player)
		{
			return;
		}

		float dropChance = OMD_BridgeConfig.GetHandsDebuffDropChanceOnFracture();
		if (dropChance <= 0)
		{
			return;
		}

		if (Math.RandomFloatInclusive(0, 100) <= dropChance)
		{
			m_Player.InediaInfectedAI_KnockItemOutOfHands();
		}
	}

	protected void OMD_Bridge_OnStoreSave()
	{
		if (!OMD_BridgeConfig.IsActive() || !m_Player)
		{
			return;
		}

		InediaInfectedAI_PlayerStorage playerStorage = m_Player.InediaInfectedAI_GetPlayerStorage();
		if (!playerStorage)
		{
			return;
		}

		playerStorage.Set("m_PainHandsPercent", m_PainHandsPercent);
		playerStorage.Set("m_PainFeetPercent", m_PainFeetPercent);
		playerStorage.Set("m_BreakHandsTimeRemainingSeconds", m_BreakHandsTimeRemainingSeconds);
		playerStorage.Set("HandsStabilizeIsActive", IsLimbStabilized("hands"));
		playerStorage.Set("m_HandsBreakStabilizationItemShockReductionMultiplier", m_HandsBreakStabilizationItemShockReductionMultiplier);
		playerStorage.Set("m_HandsBreakStabilizationItemRegenerationMultiplier", m_HandsBreakStabilizationItemRegenerationMultiplier);
		playerStorage.Set("m_HandsDeepWoundTimeRemainingSeconds", m_HandsDeepWoundTimeRemainingSeconds);
		playerStorage.Set("m_HandsDeepWoundBleedingRate", m_HandsDeepWoundBleedingRate);
		playerStorage.Set("HandsDeepWoundBandageIsActive", IsLimbDeepWoundBandaged("hands"));
		playerStorage.Set("m_HandsDeepWoundBandageItemEffectivenessTimeRemainingSeconds", m_HandsDeepWoundBandageItemEffectivenessTimeRemainingSeconds);
		playerStorage.Set("m_HandsDeepWoundBandageItemRegenerationMultiplier", m_HandsDeepWoundBandageItemRegenerationMultiplier);
		playerStorage.Set("HandsBulletCount", GetBulletCountInLimb("hands"));
		playerStorage.Set("m_HandsBulletInBodySeconds", GetBulletInBodySecondsForLimb("hands"));
		playerStorage.Set("m_BreakFeetTimeRemainingSeconds", m_BreakFeetTimeRemainingSeconds);
		playerStorage.Set("FeetStabilizeIsActive", IsLimbStabilized("feet"));
		playerStorage.Set("m_FeetBreakStabilizationItemShockReductionMultiplier", m_FeetBreakStabilizationItemShockReductionMultiplier);
		playerStorage.Set("m_FeetBreakStabilizationItemRegenerationMultiplier", m_FeetBreakStabilizationItemRegenerationMultiplier);
		playerStorage.Set("m_FeetDeepWoundTimeRemainingSeconds", m_FeetDeepWoundTimeRemainingSeconds);
		playerStorage.Set("m_FeetDeepWoundBleedingRate", m_FeetDeepWoundBleedingRate);
		playerStorage.Set("FeetDeepWoundBandageIsActive", IsLimbDeepWoundBandaged("feet"));
		playerStorage.Set("m_FeetDeepWoundBandageItemEffectivenessTimeRemainingSeconds", m_FeetDeepWoundBandageItemEffectivenessTimeRemainingSeconds);
		playerStorage.Set("m_FeetDeepWoundBandageItemRegenerationMultiplier", m_FeetDeepWoundBandageItemRegenerationMultiplier);
		playerStorage.Set("FeetBulletCount", GetBulletCountInLimb("feet"));
		playerStorage.Set("m_FeetBulletInBodySeconds", GetBulletInBodySecondsForLimb("feet"));
		playerStorage.Set("ScratchCountHead", m_Player.OMD_Bridge_GetScratchCountStored("head"));
		playerStorage.Set("ScratchCountArms", m_Player.OMD_Bridge_GetScratchCountStored("arms"));
		playerStorage.Set("ScratchCountLegs", m_Player.OMD_Bridge_GetScratchCountStored("legs"));
		playerStorage.Set("ScratchCountTorso", m_Player.OMD_Bridge_GetScratchCountStored("torso"));
		playerStorage.Set("ScratchCountHands", m_Player.OMD_Bridge_GetScratchCountStored("hands"));
		playerStorage.Set("ScratchCountFeet", m_Player.OMD_Bridge_GetScratchCountStored("feet"));
		OMD_Bridge_OnStoreSaveSutures(playerStorage);
		playerStorage.CommitData();
	}

	protected void OMD_Bridge_OnStoreLoad()
	{
		if (!OMD_BridgeConfig.IsActive() || !m_Player)
		{
			return;
		}

		InediaInfectedAI_PlayerStorage playerStorage = m_Player.InediaInfectedAI_GetPlayerStorage();
		if (!playerStorage)
		{
			return;
		}

		playerStorage.RefreshData();

		m_PainHandsPercent = playerStorage.Get("m_PainHandsPercent");
		m_PainFeetPercent = playerStorage.Get("m_PainFeetPercent");
		m_BreakHandsTimeRemainingSeconds = playerStorage.Get("m_BreakHandsTimeRemainingSeconds");
		m_HandsBreakStabilizationItemShockReductionMultiplier = playerStorage.Get("m_HandsBreakStabilizationItemShockReductionMultiplier");
		m_HandsBreakStabilizationItemRegenerationMultiplier = playerStorage.Get("m_HandsBreakStabilizationItemRegenerationMultiplier");

		if (playerStorage.Get("HandsStabilizeIsActive") != 0)
		{
			m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_STABILIZE, true);
		}

		m_HandsDeepWoundTimeRemainingSeconds = playerStorage.Get("m_HandsDeepWoundTimeRemainingSeconds");
		m_HandsDeepWoundBleedingRate = playerStorage.Get("m_HandsDeepWoundBleedingRate");
		m_HandsDeepWoundBandageItemEffectivenessTimeRemainingSeconds = playerStorage.Get("m_HandsDeepWoundBandageItemEffectivenessTimeRemainingSeconds");
		m_HandsDeepWoundBandageItemRegenerationMultiplier = playerStorage.Get("m_HandsDeepWoundBandageItemRegenerationMultiplier");

		if (playerStorage.Get("HandsDeepWoundBandageIsActive") != 0)
		{
			m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BANDAGE, true);
		}

		SetBulletCountInLimb("hands", playerStorage.Get("HandsBulletCount"));
		m_HandsBulletInBodySeconds = playerStorage.Get("m_HandsBulletInBodySeconds");

		m_BreakFeetTimeRemainingSeconds = playerStorage.Get("m_BreakFeetTimeRemainingSeconds");
		m_FeetBreakStabilizationItemShockReductionMultiplier = playerStorage.Get("m_FeetBreakStabilizationItemShockReductionMultiplier");
		m_FeetBreakStabilizationItemRegenerationMultiplier = playerStorage.Get("m_FeetBreakStabilizationItemRegenerationMultiplier");

		if (playerStorage.Get("FeetStabilizeIsActive") != 0)
		{
			m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_STABILIZE, true);
		}

		m_FeetDeepWoundTimeRemainingSeconds = playerStorage.Get("m_FeetDeepWoundTimeRemainingSeconds");
		m_FeetDeepWoundBleedingRate = playerStorage.Get("m_FeetDeepWoundBleedingRate");
		m_FeetDeepWoundBandageItemEffectivenessTimeRemainingSeconds = playerStorage.Get("m_FeetDeepWoundBandageItemEffectivenessTimeRemainingSeconds");
		m_FeetDeepWoundBandageItemRegenerationMultiplier = playerStorage.Get("m_FeetDeepWoundBandageItemRegenerationMultiplier");

		if (playerStorage.Get("FeetDeepWoundBandageIsActive") != 0)
		{
			m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BANDAGE, true);
		}

		SetBulletCountInLimb("feet", playerStorage.Get("FeetBulletCount"));
		m_FeetBulletInBodySeconds = playerStorage.Get("m_FeetBulletInBodySeconds");
		m_Player.OMD_Bridge_SetScratchCountStored("head", playerStorage.Get("ScratchCountHead"));
		m_Player.OMD_Bridge_SetScratchCountStored("arms", playerStorage.Get("ScratchCountArms"));
		m_Player.OMD_Bridge_SetScratchCountStored("legs", playerStorage.Get("ScratchCountLegs"));
		m_Player.OMD_Bridge_SetScratchCountStored("torso", playerStorage.Get("ScratchCountTorso"));
		m_Player.OMD_Bridge_SetScratchCountStored("hands", playerStorage.Get("ScratchCountHands"));
		m_Player.OMD_Bridge_SetScratchCountStored("feet", playerStorage.Get("ScratchCountFeet"));
		OMD_Bridge_OnStoreLoadSutures(playerStorage);
	}

	protected void OMD_Bridge_ResetDebuffsInPlayerStorage()
	{
		if (!m_Player)
		{
			return;
		}

		InediaInfectedAI_PlayerStorage playerStorage = m_Player.InediaInfectedAI_GetPlayerStorage();
		if (!playerStorage)
		{
			return;
		}

		playerStorage.Set("m_PainHandsPercent", 0);
		playerStorage.Set("m_PainFeetPercent", 0);
		playerStorage.Set("m_BreakHandsTimeRemainingSeconds", 0);
		playerStorage.Set("m_HandsDeepWoundTimeRemainingSeconds", 0);
		playerStorage.Set("HandsBulletCount", 0);
		playerStorage.Set("m_BreakFeetTimeRemainingSeconds", 0);
		playerStorage.Set("m_FeetDeepWoundTimeRemainingSeconds", 0);
		playerStorage.Set("FeetBulletCount", 0);
		playerStorage.Set("ScratchCountHead", 0);
		playerStorage.Set("ScratchCountArms", 0);
		playerStorage.Set("ScratchCountLegs", 0);
		playerStorage.Set("ScratchCountTorso", 0);
		playerStorage.Set("ScratchCountHands", 0);
		playerStorage.Set("ScratchCountFeet", 0);
		m_Player.OMD_Bridge_SetScratchCountStored("head", 0);
		m_Player.OMD_Bridge_SetScratchCountStored("arms", 0);
		m_Player.OMD_Bridge_SetScratchCountStored("legs", 0);
		m_Player.OMD_Bridge_SetScratchCountStored("torso", 0);
		m_Player.OMD_Bridge_SetScratchCountStored("hands", 0);
		m_Player.OMD_Bridge_SetScratchCountStored("feet", 0);
		OMD_Bridge_ResetSuturesInPlayerStorage(playerStorage);
		playerStorage.CommitData();
	}

	void OMD_Bridge_RemoveAllBridgeDebuffs(bool spawnUsedItems = true)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (!m_Player)
		{
			return;
		}

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		array<string> limbs = OMD_BridgeTreatment.GetLimbs();
		int i;
		for (i = 0; i < limbs.Count(); i++)
		{
			string limb = limbs.Get(i);
			m_Player.OMD_Bridge_RemoveAllLimbScratches(limb);
			OMD_Bridge_DeactivateSutureForLimb(limb);
		}

		bool clearHands = true;
		bool clearFeet = true;
		if (m_InediaPainLimbs)
		{
			if (m_InediaPainLimbs.Find("hands") != -1)
			{
				clearHands = false;
			}

			if (m_InediaPainLimbs.Find("feet") != -1)
			{
				clearFeet = false;
			}
		}

		if (clearHands)
		{
			DeactivateBreakForLimb("hands", spawnUsedItems);
			DeactivateDeepWoundForLimb("hands", spawnUsedItems);
			SetBulletCountInLimb("hands", 0);
			SetBulletInBodySecondsForLimb("hands", 0);
			AddPainPercentForLimb("hands", -100);
		}
		else
		{
			SetBulletInBodySecondsForLimb("hands", 0);
		}

		if (clearFeet)
		{
			DeactivateBreakForLimb("feet", spawnUsedItems);
			DeactivateDeepWoundForLimb("feet", spawnUsedItems);
			SetBulletCountInLimb("feet", 0);
			SetBulletInBodySecondsForLimb("feet", 0);
			AddPainPercentForLimb("feet", -100);
		}
		else
		{
			SetBulletInBodySecondsForLimb("feet", 0);
		}

		OMD_Bridge_SyncPainLevelsServer();
		m_Player.SetSynchDirty();
		OMD_Bridge_ResetDebuffsInPlayerStorage();
	}

	protected void OMD_Bridge_LogPainHit(string dmgZone)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsDebugEnabled())
		{
			return;
		}

		string limb = GetInediaPainLimbFromDmgZone(dmgZone);
		float handsPain = GetPainPercentForLimb("hands");
		float armsPain = GetPainPercentForLimb("arms");
		float feetPain = GetPainPercentForLimb("feet");
		float legsPain = GetPainPercentForLimb("legs");
		int handsScratches = 0;
		int feetScratches = 0;
		if (m_Player)
		{
			handsScratches = m_Player.OMD_Bridge_CountHandsScratches();
			feetScratches = m_Player.OMD_Bridge_CountFeetScratches();
		}
		string handsBreakText = "0";
		if (IsLimbBroken("hands"))
		{
			handsBreakText = "1";
		}
		string feetBreakText = "0";
		if (IsLimbBroken("feet"))
		{
			feetBreakText = "1";
		}
		Print("[OMD_Bridge] dmgZone=" + dmgZone + " limb=" + limb + " hands=" + handsPain.ToString() + " feet=" + feetPain.ToString() + " arms=" + armsPain.ToString() + " legs=" + legsPain.ToString() + " handsScratch=" + handsScratches.ToString() + " feetScratch=" + feetScratches.ToString() + " handsBreak=" + handsBreakText + " feetBreak=" + feetBreakText);
	}

	protected void OMD_Bridge_RunPainActionsForFeet(float painDamage, EntityAI source, int damageType)
	{
		if (!PainSystemIsActive() || !m_Player.m_InediaInfectedAI_ConfigPlayers || painDamage <= 0)
		{
			return;
		}

		UpdatePainLevelsForAllLimbs();

		if (CanLimbBeBrokenAfterHit("feet", painDamage))
		{
			ActivateBreakForLimb("feet", 60);
		}

		if (painDamage >= 3 && Math.RandomFloatInclusive(0, 100) <= 20 && IsLimbDeepWounded("feet"))
		{
			float deepWoundIncreasedTime = Math.Clamp(GetDeepWoundTimeRemainingSecondsForLimb("feet") + 300, 0, GetDeepWoundMaxDurationSecondsForLimb("feet"));
			SetDeepWoundTimeRemainingSecondsForLimb("feet", deepWoundIncreasedTime);

			if (IsLimbDeepWoundBandaged("feet") && IsLimbDeepWoundBandageEffective("feet"))
			{
				SetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb("feet", 0);
			}
		}
	}

	protected float OMD_Bridge_GetBridgeLimbDeepWoundBleed(string limb)
	{
		if (!IsLimbDeepWounded(limb))
		{
			return 0;
		}

		float limbBleed = 0;
		if (!IsLimbDeepWoundBandaged(limb))
		{
			limbBleed = GetDeepWoundBleedingRateForLimb(limb);
		}
		else if (!IsLimbDeepWoundBandageEffective(limb))
		{
			limbBleed = 0.5 * GetDeepWoundBleedingRateForLimb(limb);
		}

		if (limbBleed <= 0)
		{
			return 0;
		}

		float bloodScale = Math.InverseLerp(PlayerConstants.BLOOD_THRESHOLD_FATAL, PlayerConstants.BLEEDING_LOW_PRESSURE_BLOOD, m_Player.GetHealth("GlobalHealth", "Blood"));
		bloodScale = Math.Clamp(bloodScale, PlayerConstants.BLEEDING_LOW_PRESSURE_MIN_MOD, 1);
		limbBleed = limbBleed * bloodScale;

		if (m_Player.GetModifiersManager() && m_Player.GetModifiersManager().IsModifierActive(InediaInfectedAI_eModifiers.MDF_BLOOD_CLOTTING))
		{
			if (m_BloodClottingItemClottingMultiplier > 1)
			{
				limbBleed = limbBleed / m_BloodClottingItemClottingMultiplier;
			}
		}

		if (!m_Player.IsUnconscious())
		{
			limbBleed = limbBleed * m_Player.m_InediaInfectedAI_ConfigPlayers.LimbsDeepWoundConsciousBleedRateMultiplier;
		}
		else
		{
			limbBleed = limbBleed * m_Player.m_InediaInfectedAI_ConfigPlayers.LimbsDeepWoundUnconsciousBleedRateMultiplier;
		}

		return limbBleed;
	}

	void OMD_Bridge_TryDeepWoundFromScratches(string limb, int scratchCount)
	{
		if (!GetGame().IsServer() || !OMD_BridgeConfig.IsActive() || !m_Player)
		{
			return;
		}

		if (m_Player.InediaInfectedAI_IsNPC() || !m_Player.GetAllowDamage())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsScratchesToDeepWoundEnabled())
		{
			return;
		}

		OMD_Bridge_TryConvertScratchesToDeepWound(limb, scratchCount);
	}

	void OMD_Bridge_TryConvertScratchesToDeepWound(string limb, int scratchCount)
	{
		if (!GetGame().IsServer() || !OMD_BridgeConfig.IsActive() || !m_Player)
		{
			return;
		}

		if (!OMD_BridgeConfig.IsScratchesToDeepWoundEnabled())
		{
			return;
		}

		if (m_Player.InediaInfectedAI_IsNPC() || !m_Player.GetAllowDamage())
		{
			return;
		}

		if (!OMD_Bridge_IsSutureLimbSupported(limb))
		{
			return;
		}

		if (OMD_Bridge_IsLimbSutured(limb))
		{
			int pendingScratches = OMD_Bridge_TakeSutureScratchPending(limb);
			if (pendingScratches > 0)
			{
				if (OMD_Bridge_IsSutureBandaged(limb))
				{
					OMD_Bridge_HandleBandagedSutureScratches(limb, pendingScratches);
				}
				else
				{
					OMD_Bridge_TryTearSutureFromScratch(limb);
					if (!OMD_Bridge_IsLimbSutured(limb))
					{
						OMD_Bridge_RollbackSutureTearScratches(limb, pendingScratches);
					}
				}
			}

			return;
		}

		if (IsLimbDeepWounded(limb))
		{
			OMD_Bridge_TryBoostDeepWoundFromScratches(limb, scratchCount);
			return;
		}

		int needed = OMD_BridgeConfig.GetScratchesToDeepWoundCount();
		if (scratchCount < needed)
		{
			return;
		}

		float rate = OMD_BridgeConfig.GetScratchesDeepWoundRate();
		bool opened = ActivateDeepWoundForLimb(limb, 0, -1, 0, false, false);
		if (!opened)
		{
			return;
		}

		SetDeepWoundBleedingRateForLimb(limb, Math.Clamp(rate, DEEP_WOUND_BLEEDING_RATE_MIN, DEEP_WOUND_BLEEDING_RATE_MAX));
		OMD_Bridge_SyncDeepWoundSeverityForLimb(limb);
		m_Player.OMD_Bridge_RemoveAllLimbScratches(limb);

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] scratch convert deep wound limb=" + limb + " scratches=" + scratchCount.ToString() + " rate=" + rate.ToString());
		}
	}

	void OMD_Bridge_TryBoostDeepWoundFromScratches(string limb, int scratchCount)
	{
		if (!GetGame().IsServer() || !OMD_BridgeConfig.IsActive() || !m_Player)
		{
			return;
		}

		if (!IsLimbDeepWounded(limb))
		{
			return;
		}

		int boostCount = OMD_BridgeConfig.GetScratchesDeepWoundRateBoostCount();
		float boostRate = OMD_BridgeConfig.GetScratchesDeepWoundRateBoost();
		if (boostCount <= 0 || boostRate <= 0)
		{
			return;
		}

		if (scratchCount < boostCount)
		{
			return;
		}

		float currentRate = GetDeepWoundBleedingRateForLimb(limb);
		float newRate = Math.Clamp(currentRate + boostRate, DEEP_WOUND_BLEEDING_RATE_MIN, DEEP_WOUND_BLEEDING_RATE_MAX);
		SetDeepWoundBleedingRateForLimb(limb, newRate);
		OMD_Bridge_SyncDeepWoundSeverityForLimb(limb);

		int removed = 0;
		while (removed < boostCount)
		{
			m_Player.OMD_Bridge_RemoveOneScratch(limb);
			removed = removed + 1;
		}

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] scratch boost deep wound limb=" + limb + " removed=" + boostCount.ToString() + " rate=" + currentRate.ToString() + "->" + newRate.ToString());
		}
	}

	protected void OMD_Bridge_ProcessHitScratches(TotalDamageResult damageResult, string dmgZone)
	{
		if (!GetGame().IsServer() || !OMD_BridgeConfig.IsActive() || !damageResult || !m_Player)
		{
			return;
		}

		if (!m_Player.GetAllowDamage() || m_Player.InediaInfectedAI_IsNPC())
		{
			return;
		}

		string limb = GetInediaPainLimbFromDmgZone(dmgZone);
		if (limb == "")
		{
			return;
		}

		if (limb != "hands" && limb != "feet" && limb != "head" && limb != "arms" && limb != "legs" && limb != "torso")
		{
			return;
		}

		float healthDamage = damageResult.GetDamage(dmgZone, "Health");
		float bloodDamage = damageResult.GetDamage(dmgZone, "Blood");
		float shockDamage = damageResult.GetDamage(dmgZone, "Shock");
		if (healthDamage <= 0)
		{
			healthDamage = damageResult.GetDamage("", "Health");
		}
		if (bloodDamage <= 0)
		{
			bloodDamage = damageResult.GetDamage("", "Blood");
		}
		if (shockDamage <= 0)
		{
			shockDamage = damageResult.GetDamage("", "Shock");
		}

		if (healthDamage <= 0 && bloodDamage <= 0 && shockDamage <= 0)
		{
			return;
		}

		m_Player.OMD_Bridge_TryAddLimbScratch(limb, dmgZone);
		int scratchCount = m_Player.OMD_Bridge_CountLimbScratches(limb);
		if (OMD_Bridge_IsLimbSutured(limb))
		{
			OMD_Bridge_TryDeepWoundFromScratches(limb, scratchCount);
			return;
		}

		OMD_Bridge_TryDeepWoundFromScratches(limb, scratchCount);
	}

	void OMD_Bridge_NoteSutureScratchPending(string limb, int amount)
	{
		if (!GetGame().IsServer() || amount <= 0)
		{
			return;
		}

		if (!OMD_Bridge_IsLimbSutured(limb))
		{
			return;
		}

		if (limb == "head")
		{
			m_OMD_Bridge_SutureScratchPendingHead = m_OMD_Bridge_SutureScratchPendingHead + amount;
			return;
		}

		if (limb == "arms")
		{
			m_OMD_Bridge_SutureScratchPendingArms = m_OMD_Bridge_SutureScratchPendingArms + amount;
			return;
		}

		if (limb == "legs")
		{
			m_OMD_Bridge_SutureScratchPendingLegs = m_OMD_Bridge_SutureScratchPendingLegs + amount;
			return;
		}

		if (limb == "torso")
		{
			m_OMD_Bridge_SutureScratchPendingTorso = m_OMD_Bridge_SutureScratchPendingTorso + amount;
			return;
		}

		if (limb == "hands")
		{
			m_OMD_Bridge_SutureScratchPendingHands = m_OMD_Bridge_SutureScratchPendingHands + amount;
			return;
		}

		if (limb == "feet")
		{
			m_OMD_Bridge_SutureScratchPendingFeet = m_OMD_Bridge_SutureScratchPendingFeet + amount;
		}
	}

	int OMD_Bridge_TakeSutureScratchPending(string limb)
	{
		int pending = 0;
		if (limb == "head")
		{
			pending = m_OMD_Bridge_SutureScratchPendingHead;
			m_OMD_Bridge_SutureScratchPendingHead = 0;
			return pending;
		}

		if (limb == "arms")
		{
			pending = m_OMD_Bridge_SutureScratchPendingArms;
			m_OMD_Bridge_SutureScratchPendingArms = 0;
			return pending;
		}

		if (limb == "legs")
		{
			pending = m_OMD_Bridge_SutureScratchPendingLegs;
			m_OMD_Bridge_SutureScratchPendingLegs = 0;
			return pending;
		}

		if (limb == "torso")
		{
			pending = m_OMD_Bridge_SutureScratchPendingTorso;
			m_OMD_Bridge_SutureScratchPendingTorso = 0;
			return pending;
		}

		if (limb == "hands")
		{
			pending = m_OMD_Bridge_SutureScratchPendingHands;
			m_OMD_Bridge_SutureScratchPendingHands = 0;
			return pending;
		}

		if (limb == "feet")
		{
			pending = m_OMD_Bridge_SutureScratchPendingFeet;
			m_OMD_Bridge_SutureScratchPendingFeet = 0;
			return pending;
		}

		return 0;
	}

	void OMD_Bridge_ClearSutureScratchPending(string limb)
	{
		if (limb == "head")
		{
			m_OMD_Bridge_SutureScratchPendingHead = 0;
			return;
		}

		if (limb == "arms")
		{
			m_OMD_Bridge_SutureScratchPendingArms = 0;
			return;
		}

		if (limb == "legs")
		{
			m_OMD_Bridge_SutureScratchPendingLegs = 0;
			return;
		}

		if (limb == "torso")
		{
			m_OMD_Bridge_SutureScratchPendingTorso = 0;
			return;
		}

		if (limb == "hands")
		{
			m_OMD_Bridge_SutureScratchPendingHands = 0;
			return;
		}

		if (limb == "feet")
		{
			m_OMD_Bridge_SutureScratchPendingFeet = 0;
		}
	}

	void OMD_Bridge_RollbackSutureTearScratches(string limb, int count)
	{
		if (!GetGame().IsServer() || !m_Player || count <= 0)
		{
			return;
		}

		int safety = 0;
		int left = count;
		while (left > 0 && safety < 8)
		{
			m_Player.OMD_Bridge_RemoveOneScratch(limb);
			left = left - 1;
			safety = safety + 1;
		}

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture tear boost blocked limb=" + limb);
		}
	}

	void OMD_Bridge_BlockSutureTearScratchBoost(string limb, bool sutureWasActive, int scratchesBefore)
	{
		if (!GetGame().IsServer() || !sutureWasActive || limb == "" || !m_Player)
		{
			return;
		}

		if (OMD_Bridge_IsLimbSutured(limb))
		{
			return;
		}

		int scratchesAfter = m_Player.OMD_Bridge_CountLimbScratches(limb);
		if (scratchesAfter <= scratchesBefore)
		{
			return;
		}

		int safety = 0;
		while (scratchesAfter > scratchesBefore && safety < 8)
		{
			m_Player.OMD_Bridge_RemoveOneScratch(limb);
			scratchesAfter = m_Player.OMD_Bridge_CountLimbScratches(limb);
			safety = safety + 1;
		}

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture tear boost blocked limb=" + limb);
		}
	}

	void OMD_Bridge_ActivateSutureForLimb(string limb, int woundTier = 0)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!m_Player)
		{
			return;
		}

		float healSeconds = OMD_BridgeConfig.GetSutureHealSeconds();
		if (healSeconds <= 0)
		{
			return;
		}

		if (!OMD_Bridge_IsSutureLimbSupported(limb))
		{
			return;
		}

		if (woundTier < 0)
		{
			woundTier = 0;
		}

		if (woundTier > 3)
		{
			woundTier = 3;
		}

		bool alreadySutured = OMD_Bridge_IsLimbSutured(limb);
		float remainingSeconds = 0;
		int storedTier = 0;
		if (alreadySutured)
		{
			remainingSeconds = OMD_Bridge_GetSutureTimeRemainingSecondsForLimb(limb);
			storedTier = OMD_Bridge_GetSutureWoundTierForLimb(limb);
		}

		if (storedTier > woundTier)
		{
			woundTier = storedTier;
		}

		float appliedHeal = healSeconds;
		bool keptTimer = false;
		if (alreadySutured && remainingSeconds > 0)
		{
			appliedHeal = remainingSeconds;
			keptTimer = true;
		}

		OMD_Bridge_ClearSutureScratchPending(limb);
		OMD_Bridge_SetSutureWoundTierForLimb(limb, woundTier);
		OMD_Bridge_ClearSutureBandageForLimb(limb);
		OMD_Bridge_SetSutureTimeRemainingSecondsForLimb(limb, appliedHeal);
		OMD_Bridge_SetSutureActiveForLimb(limb, true);

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture activated limb=" + limb + " heal=" + appliedHeal.ToString() + " tier=" + woundTier.ToString() + " kept=" + keptTimer.ToString());
		}
	}

	void OMD_Bridge_DeactivateSutureForLimb(string limb)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (!m_Player)
		{
			return;
		}

		if (!OMD_Bridge_IsSutureLimbSupported(limb))
		{
			return;
		}

		OMD_Bridge_ClearSutureScratchPending(limb);
		OMD_Bridge_ClearSutureBandageForLimb(limb);
		OMD_Bridge_SetSutureWoundTierForLimb(limb, 0);
		OMD_Bridge_SetSutureTimeRemainingSecondsForLimb(limb, 0);
		OMD_Bridge_SetSutureActiveForLimb(limb, false);

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture deactivated limb=" + limb);
		}
	}

	bool OMD_Bridge_IsLimbSutured(string limb)
	{
		if (!m_Player)
		{
			return false;
		}

		int bitIndex = m_Player.OMD_Bridge_GetSutureBitIndexForLimb(limb);
		if (bitIndex < 0)
		{
			return false;
		}

		return m_Player.OMD_Bridge_GetSutureStateBit(bitIndex);
	}

	float OMD_Bridge_GetSutureTimeRemainingSecondsForLimb(string limb)
	{
		if (limb == "head")
		{
			return m_SutureHeadTimeRemainingSeconds;
		}

		if (limb == "arms")
		{
			return m_SutureArmsTimeRemainingSeconds;
		}

		if (limb == "legs")
		{
			return m_SutureLegsTimeRemainingSeconds;
		}

		if (limb == "torso")
		{
			return m_SutureTorsoTimeRemainingSeconds;
		}

		if (limb == "hands")
		{
			return m_SutureHandsTimeRemainingSeconds;
		}

		if (limb == "feet")
		{
			return m_SutureFeetTimeRemainingSeconds;
		}

		return 0;
	}

	void OMD_Bridge_SetSutureTimeRemainingSecondsForLimb(string limb, float seconds)
	{
		float clamped = seconds;
		if (clamped < 0)
		{
			clamped = 0;
		}

		if (limb == "head")
		{
			m_SutureHeadTimeRemainingSeconds = clamped;
			return;
		}

		if (limb == "arms")
		{
			m_SutureArmsTimeRemainingSeconds = clamped;
			return;
		}

		if (limb == "legs")
		{
			m_SutureLegsTimeRemainingSeconds = clamped;
			return;
		}

		if (limb == "torso")
		{
			m_SutureTorsoTimeRemainingSeconds = clamped;
			return;
		}

		if (limb == "hands")
		{
			m_SutureHandsTimeRemainingSeconds = clamped;
			return;
		}

		if (limb == "feet")
		{
			m_SutureFeetTimeRemainingSeconds = clamped;
		}
	}

	void OMD_Bridge_TryTearSutureOnHit(TotalDamageResult damageResult, string dmgZone)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		string hitLimb = GetInediaPainLimbFromDmgZone(dmgZone);
		if (hitLimb == "")
		{
			return;
		}

		string sutureLimb = OMD_Bridge_ResolveSuturedLimbForHit(hitLimb);
		if (sutureLimb == "")
		{
			return;
		}

		float receivedDamage = 0;
		if (damageResult)
		{
			receivedDamage = damageResult.GetDamage(dmgZone, "Health");
			if (receivedDamage <= 0)
			{
				receivedDamage = damageResult.GetDamage("", "Health");
			}
		}

		bool bandageWasDirty = false;
		if (OMD_Bridge_IsSutureBandaged(sutureLimb))
		{
			bandageWasDirty = m_OMD_Bridge_SutureHitBandageWasDirty;
			float dirtFromDamage = receivedDamage * OMD_BridgeConfig.GetSutureBandageDirtyPerDamage();
			float dirtCap = OMD_BridgeConfig.GetSutureBandageDirtyPerDamageMax();
			if (dirtFromDamage > dirtCap)
			{
				dirtFromDamage = dirtCap;
			}

			if (dirtFromDamage < 0)
			{
				dirtFromDamage = 0;
			}

			OMD_Bridge_AddSutureBandageDirt(sutureLimb, dirtFromDamage, "damage");
		}

		if (OMD_Bridge_IsSutureBandaged(sutureLimb) && !bandageWasDirty)
		{
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] suture tear skipped bandaged clean limb=" + sutureLimb);
			}

			return;
		}

		if (bandageWasDirty)
		{
			OMD_Bridge_TrySutureDirtyBandageInfection(sutureLimb);
		}

		float tearChance = OMD_BridgeConfig.GetSutureTearBaseChance() + receivedDamage * OMD_BridgeConfig.GetSutureTearChancePerDamage();
		float tearMax = OMD_BridgeConfig.GetSutureTearMaxChance();
		if (tearChance > tearMax)
		{
			tearChance = tearMax;
		}

		if (tearChance < 0)
		{
			tearChance = 0;
		}

		if (tearChance <= 0)
		{
			return;
		}

		float roll = Math.RandomFloatInclusive(0, 100);
		bool torn = roll <= tearChance;

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture tear try hitLimb=" + hitLimb + " sutureLimb=" + sutureLimb + " dmg=" + receivedDamage.ToString() + " chance=" + tearChance.ToString() + " roll=" + roll.ToString() + " torn=" + torn.ToString() + " dirty=" + OMD_Bridge_IsSutureBandageDirty(sutureLimb).ToString());
			if (bandageWasDirty)
			{
				Print("[OMD_Bridge] suture dirty tear try limb=" + sutureLimb + " chance=" + tearChance.ToString() + " roll=" + roll.ToString() + " torn=" + torn.ToString());
			}
		}

		if (!torn)
		{
			return;
		}

		OMD_Bridge_TearSutureAndRestoreWound(sutureLimb);
	}

	void OMD_Bridge_TryTearSutureFromScratch(string limb)
	{
		if (!GetGame().IsServer() || !m_Player)
		{
			return;
		}

		if (OMD_Bridge_IsSutureBandaged(limb))
		{
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] suture scratch ignored bandaged limb=" + limb);
			}

			return;
		}

		float chance = OMD_BridgeConfig.GetSutureTearChanceFromScratch();
		if (chance <= 0)
		{
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] suture scratch tear skipped limb=" + limb + " chance=0");
			}

			return;
		}

		float roll = Math.RandomFloatInclusive(0, 100);
		bool torn = roll <= chance;

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture scratch tear try limb=" + limb + " chance=" + chance.ToString() + " roll=" + roll.ToString() + " torn=" + torn.ToString());
		}

		if (!torn)
		{
			return;
		}

		OMD_Bridge_TearSutureAndRestoreWound(limb);
	}

	void OMD_Bridge_TearSutureAndRestoreWound(string limb)
	{
		if (!GetGame().IsServer() || !m_Player)
		{
			return;
		}

		int tier = OMD_Bridge_GetSutureWoundTierForLimb(limb);
		bool alreadyWounded = IsLimbDeepWounded(limb);
		int scratchCountBeforeClear = m_Player.OMD_Bridge_CountLimbScratches(limb);
		m_Player.OMD_Bridge_RemoveAllLimbScratches(limb);
		OMD_Bridge_ClearSutureScratchPending(limb);
		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture tear scratch count cleared limb=" + limb + " count=" + scratchCountBeforeClear.ToString());
		}

		OMD_Bridge_DeactivateSutureForLimb(limb);

		if (alreadyWounded)
		{
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] suture tear kept existing wound limb=" + limb + " tier=" + tier.ToString());
			}

			return;
		}

		float rate = OMD_Bridge_GetBleedingRateForWoundTier(tier);
		bool opened = ActivateDeepWoundForLimb(limb, 0, -1, 0, false, false);
		if (!opened)
		{
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] suture tear restore failed limb=" + limb + " tier=" + tier.ToString());
			}

			return;
		}

		SetDeepWoundBleedingRateForLimb(limb, Math.Clamp(rate, DEEP_WOUND_BLEEDING_RATE_MIN, DEEP_WOUND_BLEEDING_RATE_MAX));
		OMD_Bridge_SyncDeepWoundSeverityForLimb(limb);

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture tear restored limb=" + limb + " tier=" + tier.ToString() + " rate=" + rate.ToString());
		}
	}

	float OMD_Bridge_GetBleedingRateForWoundTier(int tier)
	{
		float lightMax = OMD_BridgeConfig.GetDeepWoundSeverityLightMax();
		float mediumMax = OMD_BridgeConfig.GetDeepWoundSeverityMediumMax();
		float rate = (DEEP_WOUND_BLEEDING_RATE_MIN + lightMax) / 2;

		if (tier == 2)
		{
			rate = (lightMax + mediumMax) / 2;
		}

		if (tier >= 3)
		{
			rate = mediumMax + 3;
		}

		if (rate < DEEP_WOUND_BLEEDING_RATE_MIN)
		{
			rate = DEEP_WOUND_BLEEDING_RATE_MIN;
		}

		if (rate > DEEP_WOUND_BLEEDING_RATE_MAX)
		{
			rate = DEEP_WOUND_BLEEDING_RATE_MAX;
		}

		return rate;
	}

	string OMD_Bridge_ResolveSuturedLimbForHit(string hitLimb)
	{
		if (OMD_Bridge_IsLimbSutured(hitLimb))
		{
			return hitLimb;
		}

		string sibling = OMD_Bridge_GetSutureSiblingLimb(hitLimb);
		if (sibling == "")
		{
			return "";
		}

		if (OMD_Bridge_IsLimbSutured(sibling))
		{
			return sibling;
		}

		return "";
	}

	string OMD_Bridge_GetSutureSiblingLimb(string limb)
	{
		if (limb == "arms")
		{
			return "hands";
		}

		if (limb == "hands")
		{
			return "arms";
		}

		if (limb == "legs")
		{
			return "feet";
		}

		if (limb == "feet")
		{
			return "legs";
		}

		return "";
	}

	void OMD_Bridge_OnStoreSaveSutures(InediaInfectedAI_PlayerStorage playerStorage)
	{
		if (!playerStorage)
		{
			return;
		}

		playerStorage.Set("m_SutureHeadTimeRemainingSeconds", m_SutureHeadTimeRemainingSeconds);
		playerStorage.Set("HeadSutureIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsLimbSutured("head")));
		playerStorage.Set("m_SutureArmsTimeRemainingSeconds", m_SutureArmsTimeRemainingSeconds);
		playerStorage.Set("ArmsSutureIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsLimbSutured("arms")));
		playerStorage.Set("m_SutureLegsTimeRemainingSeconds", m_SutureLegsTimeRemainingSeconds);
		playerStorage.Set("LegsSutureIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsLimbSutured("legs")));
		playerStorage.Set("m_SutureTorsoTimeRemainingSeconds", m_SutureTorsoTimeRemainingSeconds);
		playerStorage.Set("TorsoSutureIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsLimbSutured("torso")));
		playerStorage.Set("m_SutureHandsTimeRemainingSeconds", m_SutureHandsTimeRemainingSeconds);
		playerStorage.Set("HandsSutureIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsLimbSutured("hands")));
		playerStorage.Set("m_SutureFeetTimeRemainingSeconds", m_SutureFeetTimeRemainingSeconds);
		playerStorage.Set("FeetSutureIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsLimbSutured("feet")));

		OMD_Bridge_OnStoreSaveSutureBandages(playerStorage);
	}

	void OMD_Bridge_OnStoreLoadSutures(InediaInfectedAI_PlayerStorage playerStorage)
	{
		if (!playerStorage)
		{
			return;
		}

		m_SutureHeadTimeRemainingSeconds = playerStorage.Get("m_SutureHeadTimeRemainingSeconds");
		m_SutureArmsTimeRemainingSeconds = playerStorage.Get("m_SutureArmsTimeRemainingSeconds");
		m_SutureLegsTimeRemainingSeconds = playerStorage.Get("m_SutureLegsTimeRemainingSeconds");
		m_SutureTorsoTimeRemainingSeconds = playerStorage.Get("m_SutureTorsoTimeRemainingSeconds");
		m_SutureHandsTimeRemainingSeconds = playerStorage.Get("m_SutureHandsTimeRemainingSeconds");
		m_SutureFeetTimeRemainingSeconds = playerStorage.Get("m_SutureFeetTimeRemainingSeconds");

		OMD_Bridge_SetSutureActiveForLimb("head", playerStorage.Get("HeadSutureIsActive") != 0);
		OMD_Bridge_SetSutureActiveForLimb("arms", playerStorage.Get("ArmsSutureIsActive") != 0);
		OMD_Bridge_SetSutureActiveForLimb("legs", playerStorage.Get("LegsSutureIsActive") != 0);
		OMD_Bridge_SetSutureActiveForLimb("torso", playerStorage.Get("TorsoSutureIsActive") != 0);
		OMD_Bridge_SetSutureActiveForLimb("hands", playerStorage.Get("HandsSutureIsActive") != 0);
		OMD_Bridge_SetSutureActiveForLimb("feet", playerStorage.Get("FeetSutureIsActive") != 0);

		OMD_Bridge_OnStoreLoadSutureBandages(playerStorage);
	}

	void OMD_Bridge_ResetSuturesInPlayerStorage(InediaInfectedAI_PlayerStorage playerStorage)
	{
		if (!playerStorage)
		{
			return;
		}

		playerStorage.Set("m_SutureHeadTimeRemainingSeconds", 0);
		playerStorage.Set("HeadSutureIsActive", 0);
		playerStorage.Set("m_SutureArmsTimeRemainingSeconds", 0);
		playerStorage.Set("ArmsSutureIsActive", 0);
		playerStorage.Set("m_SutureLegsTimeRemainingSeconds", 0);
		playerStorage.Set("LegsSutureIsActive", 0);
		playerStorage.Set("m_SutureTorsoTimeRemainingSeconds", 0);
		playerStorage.Set("TorsoSutureIsActive", 0);
		playerStorage.Set("m_SutureHandsTimeRemainingSeconds", 0);
		playerStorage.Set("HandsSutureIsActive", 0);
		playerStorage.Set("m_SutureFeetTimeRemainingSeconds", 0);
		playerStorage.Set("FeetSutureIsActive", 0);

		OMD_Bridge_SetSutureActiveForLimb("head", false);
		OMD_Bridge_SetSutureActiveForLimb("arms", false);
		OMD_Bridge_SetSutureActiveForLimb("legs", false);
		OMD_Bridge_SetSutureActiveForLimb("torso", false);
		OMD_Bridge_SetSutureActiveForLimb("hands", false);
		OMD_Bridge_SetSutureActiveForLimb("feet", false);
		m_SutureHeadTimeRemainingSeconds = 0;
		m_SutureArmsTimeRemainingSeconds = 0;
		m_SutureLegsTimeRemainingSeconds = 0;
		m_SutureTorsoTimeRemainingSeconds = 0;
		m_SutureHandsTimeRemainingSeconds = 0;
		m_SutureFeetTimeRemainingSeconds = 0;
		OMD_Bridge_ClearSutureBandageForLimb("head");
		OMD_Bridge_ClearSutureBandageForLimb("arms");
		OMD_Bridge_ClearSutureBandageForLimb("legs");
		OMD_Bridge_ClearSutureBandageForLimb("torso");
		OMD_Bridge_ClearSutureBandageForLimb("hands");
		OMD_Bridge_ClearSutureBandageForLimb("feet");
		OMD_Bridge_SetSutureWoundTierForLimb("head", 0);
		OMD_Bridge_SetSutureWoundTierForLimb("arms", 0);
		OMD_Bridge_SetSutureWoundTierForLimb("legs", 0);
		OMD_Bridge_SetSutureWoundTierForLimb("torso", 0);
		OMD_Bridge_SetSutureWoundTierForLimb("hands", 0);
		OMD_Bridge_SetSutureWoundTierForLimb("feet", 0);
	}

	void OMD_Bridge_SetSutureActiveForLimb(string limb, bool isActive)
	{
		if (!m_Player)
		{
			return;
		}

		int bitIndex = m_Player.OMD_Bridge_GetSutureBitIndexForLimb(limb);
		if (bitIndex < 0)
		{
			return;
		}

		m_Player.OMD_Bridge_SetSutureStateBit(bitIndex, isActive);
	}

	protected bool OMD_Bridge_IsSutureLimbSupported(string limb)
	{
		if (limb == "head")
		{
			return true;
		}

		if (limb == "arms")
		{
			return true;
		}

		if (limb == "legs")
		{
			return true;
		}

		if (limb == "torso")
		{
			return true;
		}

		if (limb == "hands")
		{
			return true;
		}

		if (limb == "feet")
		{
			return true;
		}

		return false;
	}

	protected float OMD_Bridge_SutureActiveToStorage(bool isActive)
	{
		if (isActive)
		{
			return 1;
		}

		return 0;
	}

	bool OMD_Bridge_HasTourniquetControl(string limb)
	{
		return false;
	}

	bool OMD_Bridge_HasEffectiveBleedControl(string limb)
	{
		if (IsLimbDeepWoundBandaged(limb) && IsLimbDeepWoundBandageEffective(limb))
		{
			return true;
		}

		return OMD_Bridge_HasTourniquetControl(limb);
	}

	int OMD_Bridge_GetDeepWoundSeverityTierForLimb(string limb)
	{
		if (!IsLimbDeepWounded(limb))
		{
			return 0;
		}

		float rate = GetDeepWoundBleedingRateForLimb(limb);
		float lightMax = OMD_BridgeConfig.GetDeepWoundSeverityLightMax();
		float mediumMax = OMD_BridgeConfig.GetDeepWoundSeverityMediumMax();

		if (rate < lightMax)
		{
			return 1;
		}

		if (rate < mediumMax)
		{
			return 2;
		}

		return 3;
	}

	float OMD_Bridge_GetDeepWoundSeverityRegenMultiplier(string limb)
	{
		int tier = OMD_Bridge_GetDeepWoundSeverityTierForLimb(limb);
		if (tier <= 0)
		{
			return 1.0;
		}

		bool controlled = OMD_Bridge_HasEffectiveBleedControl(limb);
		if (tier == 1)
		{
			if (controlled)
			{
				return OMD_BridgeConfig.GetDeepWoundRegenLightControlled();
			}

			return OMD_BridgeConfig.GetDeepWoundRegenLightOpen();
		}

		if (tier == 2)
		{
			if (controlled)
			{
				return OMD_BridgeConfig.GetDeepWoundRegenMediumControlled();
			}

			return OMD_BridgeConfig.GetDeepWoundRegenMediumOpen();
		}

		if (controlled)
		{
			return OMD_BridgeConfig.GetDeepWoundRegenHeavyControlled();
		}

		return OMD_BridgeConfig.GetDeepWoundRegenHeavyOpen();
	}

	void OMD_Bridge_SyncDeepWoundSeverityForLimb(string limb)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (!m_Player)
		{
			return;
		}

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		int tier = OMD_Bridge_GetDeepWoundSeverityTierForLimb(limb);
		m_Player.OMD_Bridge_SetDeepWoundSeverityForLimb(limb, tier);
	}

	void OMD_Bridge_SyncAllDeepWoundSeverities()
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		OMD_Bridge_SyncDeepWoundSeverityForLimb("head");
		OMD_Bridge_SyncDeepWoundSeverityForLimb("torso");
		OMD_Bridge_SyncDeepWoundSeverityForLimb("arms");
		OMD_Bridge_SyncDeepWoundSeverityForLimb("legs");
		OMD_Bridge_SyncDeepWoundSeverityForLimb("hands");
		OMD_Bridge_SyncDeepWoundSeverityForLimb("feet");
	}

	bool OMD_Bridge_IsSutureBandaged(string limb)
	{
		if (!m_Player)
		{
			return false;
		}

		return m_Player.OMD_Bridge_GetSutureBandageBit(limb);
	}

	bool OMD_Bridge_IsSutureBandageDirty(string limb)
	{
		if (!m_Player)
		{
			return false;
		}

		return m_Player.OMD_Bridge_GetSutureBandageDirtyBit(limb);
	}

	bool OMD_Bridge_IsSutureBandagedClean(string limb)
	{
		if (!OMD_Bridge_IsSutureBandaged(limb))
		{
			return false;
		}

		if (OMD_Bridge_IsSutureBandageDirty(limb))
		{
			return false;
		}

		return true;
	}

	bool OMD_Bridge_IsSutureUnbandaged(string limb)
	{
		if (!OMD_Bridge_IsLimbSutured(limb))
		{
			return false;
		}

		if (OMD_Bridge_IsSutureBandaged(limb))
		{
			return false;
		}

		return true;
	}

	void OMD_Bridge_ActivateSutureBandageForLimb(string limb, bool usedRag)
	{
		if (!GetGame().IsServer() || !m_Player)
		{
			return;
		}

		if (!OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			return;
		}

		if (!OMD_Bridge_IsLimbSutured(limb))
		{
			return;
		}

		bool hadDirt = OMD_Bridge_IsSutureBandageDirty(limb);
		float progressBefore = OMD_Bridge_GetSutureBandageDirtyProgressForLimb(limb);
		OMD_Bridge_SetSutureBandageUsedRagForLimb(limb, usedRag);
		OMD_Bridge_SetSutureBandageDirtyProgressForLimb(limb, 0);
		m_Player.OMD_Bridge_SetSutureBandageDirtyBit(limb, false);
		m_Player.OMD_Bridge_SetSutureBandageBit(limb, true);

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture bandage limb=" + limb + " rag=" + usedRag.ToString());
			if (hadDirt || progressBefore > 0)
			{
				Print("[OMD_Bridge] suture bandage cleaned limb=" + limb);
			}
		}
	}

	void OMD_Bridge_DisinfectSutureBandageForLimb(string limb)
	{
		if (!GetGame().IsServer() || !m_Player)
		{
			return;
		}

		if (!OMD_Bridge_IsSutureBandaged(limb))
		{
			return;
		}

		OMD_Bridge_SetSutureBandageDirtyProgressForLimb(limb, 0);
		m_Player.OMD_Bridge_SetSutureBandageDirtyBit(limb, false);

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture bandage disinfect limb=" + limb);
		}
	}

	void OMD_Bridge_ClearSutureBandageForLimb(string limb)
	{
		OMD_Bridge_SetSutureBandageDirtyProgressForLimb(limb, 0);
		OMD_Bridge_SetSutureBandageUsedRagForLimb(limb, false);

		if (!m_Player)
		{
			return;
		}

		m_Player.OMD_Bridge_SetSutureBandageBit(limb, false);
		m_Player.OMD_Bridge_SetSutureBandageDirtyBit(limb, false);
	}

	bool OMD_Bridge_SutureBandageCanBecomeDirty(string limb)
	{
		if (!OMD_Bridge_IsSutureLimbSupported(limb))
		{
			return false;
		}

		return true;
	}

	void OMD_Bridge_TickSutureBandageDirty(string limb, float pDt)
	{
		if (!GetGame().IsServer() || !m_Player)
		{
			return;
		}

		if (!OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			return;
		}

		if (!OMD_Bridge_IsLimbSutured(limb))
		{
			return;
		}

		if (!OMD_Bridge_IsSutureBandaged(limb))
		{
			return;
		}

		if (OMD_Bridge_IsSutureBandageDirty(limb))
		{
			OMD_Bridge_TickSutureDirtySepsis(limb, pDt);
			return;
		}

		if (!OMD_Bridge_SutureBandageCanBecomeDirty(limb))
		{
			return;
		}

		float dirtySeconds = OMD_BridgeConfig.GetSutureBandageDirtySeconds();
		if (OMD_Bridge_GetSutureBandageUsedRagForLimb(limb))
		{
			dirtySeconds = OMD_BridgeConfig.GetSutureRagDirtySeconds();
		}

		if (dirtySeconds <= 0)
		{
			return;
		}

		float timeDirt = pDt * (100.0 / dirtySeconds);
		OMD_Bridge_AddSutureBandageDirt(limb, timeDirt, "time");
	}

	void OMD_Bridge_AddSutureBandageDirt(string limb, float amount, string source)
	{
		if (!GetGame().IsServer() || !m_Player)
		{
			return;
		}

		if (amount <= 0)
		{
			return;
		}

		if (!OMD_Bridge_IsSutureBandaged(limb))
		{
			return;
		}

		if (OMD_Bridge_IsSutureBandageDirty(limb))
		{
			return;
		}

		float total = OMD_Bridge_GetSutureBandageDirtyProgressForLimb(limb) + amount;
		if (total < 0)
		{
			total = 0;
		}

		bool becameDirty = false;
		if (total >= 100)
		{
			total = 100;
			becameDirty = true;
		}

		OMD_Bridge_SetSutureBandageDirtyProgressForLimb(limb, total);
		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture bandage dirt limb=" + limb + " add=" + amount.ToString() + " total=" + total.ToString() + " source=" + source);
		}

		if (!becameDirty)
		{
			return;
		}

		m_Player.OMD_Bridge_SetSutureBandageDirtyBit(limb, true);
		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture bandage became dirty limb=" + limb);
		}
	}

	void OMD_Bridge_HandleBandagedSutureScratches(string limb, int pendingScratches)
	{
		if (!GetGame().IsServer() || !m_Player || pendingScratches <= 0)
		{
			return;
		}

		bool wasDirty = OMD_Bridge_IsSutureBandageDirty(limb);
		float perScratch = OMD_BridgeConfig.GetSutureBandageDirtyPerScratch();
		int scratchIndex = 0;
		while (scratchIndex < pendingScratches)
		{
			OMD_Bridge_AddSutureBandageDirt(limb, perScratch, "scratch");
			scratchIndex = scratchIndex + 1;
		}

		if (!wasDirty)
		{
			return;
		}

		int eventIndex = 0;
		while (eventIndex < pendingScratches)
		{
			OMD_Bridge_TrySutureDirtyBandageInfection(limb);
			if (OMD_Bridge_IsLimbSutured(limb))
			{
				OMD_Bridge_TryTearSutureFromDirtyBandageScratch(limb);
			}

			if (!OMD_Bridge_IsLimbSutured(limb))
			{
				OMD_Bridge_RollbackSutureTearScratches(limb, pendingScratches);
				return;
			}

			eventIndex = eventIndex + 1;
		}
	}

	void OMD_Bridge_TryTearSutureFromDirtyBandageScratch(string limb)
	{
		if (!GetGame().IsServer() || !m_Player)
		{
			return;
		}

		if (!OMD_Bridge_IsSutureBandageDirty(limb))
		{
			return;
		}

		float chance = OMD_BridgeConfig.GetSutureTearChanceFromScratchDirtyBandage();
		float roll = Math.RandomFloatInclusive(0, 100);
		bool torn = false;
		if (chance > 0)
		{
			torn = roll <= chance;
		}

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture dirty tear try limb=" + limb + " chance=" + chance.ToString() + " roll=" + roll.ToString() + " torn=" + torn.ToString());
		}

		if (!torn)
		{
			return;
		}

		OMD_Bridge_TearSutureAndRestoreWound(limb);
	}

	void OMD_Bridge_TrySutureDirtyBandageInfection(string limb)
	{
		if (!GetGame().IsServer() || !m_Player)
		{
			return;
		}

		float chance = OMD_BridgeConfig.GetSutureDirtyBandageInfectionChance();
		float roll = Math.RandomFloatInclusive(0, 100);
		bool infected = false;
		if (chance > 0)
		{
			infected = roll <= chance;
		}

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture dirty infection try limb=" + limb + " chance=" + chance.ToString() + " roll=" + roll.ToString() + " infected=" + infected.ToString());
		}

		if (!infected)
		{
			return;
		}

		OMD_Bridge_ApplySutureDirtySepsis(limb);
	}

	void OMD_Bridge_ApplySutureDirtySepsis(string limb)
	{
		if (!m_Player || !m_Player.GetTerjeStats())
		{
			return;
		}

		float sepsisValue = m_Player.GetTerjeStats().GetSepsisValue();
		m_Player.GetTerjeStats().SetSepsisValue(sepsisValue + 0.05);

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] suture dirty sepsis limb=" + limb);
		}
	}

	void OMD_Bridge_TickSutureDirtySepsis(string limb, float pDt)
	{
		if (!m_Player || !m_Player.GetTerjeStats())
		{
			return;
		}

		float chancePerMinute = OMD_BridgeConfig.GetSutureDirtySepsisChancePerMinute();
		if (chancePerMinute <= 0)
		{
			return;
		}

		float chanceThisTick = chancePerMinute * (pDt / 60.0);
		if (Math.RandomFloat01() >= chanceThisTick)
		{
			return;
		}

		OMD_Bridge_ApplySutureDirtySepsis(limb);
	}

	int OMD_Bridge_GetSutureWoundTierForLimb(string limb)
	{
		if (limb == "head")
		{
			return m_SutureWoundTierHead;
		}

		if (limb == "arms")
		{
			return m_SutureWoundTierArms;
		}

		if (limb == "legs")
		{
			return m_SutureWoundTierLegs;
		}

		if (limb == "torso")
		{
			return m_SutureWoundTierTorso;
		}

		if (limb == "hands")
		{
			return m_SutureWoundTierHands;
		}

		if (limb == "feet")
		{
			return m_SutureWoundTierFeet;
		}

		return 0;
	}

	void OMD_Bridge_SetSutureWoundTierForLimb(string limb, int tier)
	{
		if (tier < 0)
		{
			tier = 0;
		}

		if (tier > 3)
		{
			tier = 3;
		}

		if (limb == "head")
		{
			m_SutureWoundTierHead = tier;
			return;
		}

		if (limb == "arms")
		{
			m_SutureWoundTierArms = tier;
			return;
		}

		if (limb == "legs")
		{
			m_SutureWoundTierLegs = tier;
			return;
		}

		if (limb == "torso")
		{
			m_SutureWoundTierTorso = tier;
			return;
		}

		if (limb == "hands")
		{
			m_SutureWoundTierHands = tier;
			return;
		}

		if (limb == "feet")
		{
			m_SutureWoundTierFeet = tier;
		}
	}

	float OMD_Bridge_GetSutureBandageDirtyProgressForLimb(string limb)
	{
		if (limb == "head")
		{
			return m_SutureBandageDirtyProgressHead;
		}

		if (limb == "arms")
		{
			return m_SutureBandageDirtyProgressArms;
		}

		if (limb == "legs")
		{
			return m_SutureBandageDirtyProgressLegs;
		}

		if (limb == "torso")
		{
			return m_SutureBandageDirtyProgressTorso;
		}

		if (limb == "hands")
		{
			return m_SutureBandageDirtyProgressHands;
		}

		if (limb == "feet")
		{
			return m_SutureBandageDirtyProgressFeet;
		}

		return 0;
	}

	void OMD_Bridge_SetSutureBandageDirtyProgressForLimb(string limb, float progress)
	{
		if (progress < 0)
		{
			progress = 0;
		}

		if (limb == "head")
		{
			m_SutureBandageDirtyProgressHead = progress;
			return;
		}

		if (limb == "arms")
		{
			m_SutureBandageDirtyProgressArms = progress;
			return;
		}

		if (limb == "legs")
		{
			m_SutureBandageDirtyProgressLegs = progress;
			return;
		}

		if (limb == "torso")
		{
			m_SutureBandageDirtyProgressTorso = progress;
			return;
		}

		if (limb == "hands")
		{
			m_SutureBandageDirtyProgressHands = progress;
			return;
		}

		if (limb == "feet")
		{
			m_SutureBandageDirtyProgressFeet = progress;
		}
	}

	bool OMD_Bridge_GetSutureBandageUsedRagForLimb(string limb)
	{
		if (limb == "head")
		{
			return m_SutureBandageUsedRagHead;
		}

		if (limb == "arms")
		{
			return m_SutureBandageUsedRagArms;
		}

		if (limb == "legs")
		{
			return m_SutureBandageUsedRagLegs;
		}

		if (limb == "torso")
		{
			return m_SutureBandageUsedRagTorso;
		}

		if (limb == "hands")
		{
			return m_SutureBandageUsedRagHands;
		}

		if (limb == "feet")
		{
			return m_SutureBandageUsedRagFeet;
		}

		return false;
	}

	void OMD_Bridge_SetSutureBandageUsedRagForLimb(string limb, bool usedRag)
	{
		if (limb == "head")
		{
			m_SutureBandageUsedRagHead = usedRag;
			return;
		}

		if (limb == "arms")
		{
			m_SutureBandageUsedRagArms = usedRag;
			return;
		}

		if (limb == "legs")
		{
			m_SutureBandageUsedRagLegs = usedRag;
			return;
		}

		if (limb == "torso")
		{
			m_SutureBandageUsedRagTorso = usedRag;
			return;
		}

		if (limb == "hands")
		{
			m_SutureBandageUsedRagHands = usedRag;
			return;
		}

		if (limb == "feet")
		{
			m_SutureBandageUsedRagFeet = usedRag;
		}
	}

	void OMD_Bridge_OnStoreSaveSutureBandages(InediaInfectedAI_PlayerStorage playerStorage)
	{
		if (!playerStorage)
		{
			return;
		}

		playerStorage.Set("m_SutureWoundTierHead", m_SutureWoundTierHead);
		playerStorage.Set("m_SutureWoundTierArms", m_SutureWoundTierArms);
		playerStorage.Set("m_SutureWoundTierLegs", m_SutureWoundTierLegs);
		playerStorage.Set("m_SutureWoundTierTorso", m_SutureWoundTierTorso);
		playerStorage.Set("m_SutureWoundTierHands", m_SutureWoundTierHands);
		playerStorage.Set("m_SutureWoundTierFeet", m_SutureWoundTierFeet);

		playerStorage.Set("m_SutureBandageDirtyProgressHead", m_SutureBandageDirtyProgressHead);
		playerStorage.Set("m_SutureBandageDirtyProgressArms", m_SutureBandageDirtyProgressArms);
		playerStorage.Set("m_SutureBandageDirtyProgressLegs", m_SutureBandageDirtyProgressLegs);
		playerStorage.Set("m_SutureBandageDirtyProgressTorso", m_SutureBandageDirtyProgressTorso);
		playerStorage.Set("m_SutureBandageDirtyProgressHands", m_SutureBandageDirtyProgressHands);
		playerStorage.Set("m_SutureBandageDirtyProgressFeet", m_SutureBandageDirtyProgressFeet);

		playerStorage.Set("HeadSutureBandageIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandaged("head")));
		playerStorage.Set("ArmsSutureBandageIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandaged("arms")));
		playerStorage.Set("LegsSutureBandageIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandaged("legs")));
		playerStorage.Set("TorsoSutureBandageIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandaged("torso")));
		playerStorage.Set("HandsSutureBandageIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandaged("hands")));
		playerStorage.Set("FeetSutureBandageIsActive", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandaged("feet")));

		playerStorage.Set("HeadSutureBandageIsDirty", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandageDirty("head")));
		playerStorage.Set("ArmsSutureBandageIsDirty", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandageDirty("arms")));
		playerStorage.Set("LegsSutureBandageIsDirty", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandageDirty("legs")));
		playerStorage.Set("TorsoSutureBandageIsDirty", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandageDirty("torso")));
		playerStorage.Set("HandsSutureBandageIsDirty", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandageDirty("hands")));
		playerStorage.Set("FeetSutureBandageIsDirty", OMD_Bridge_SutureActiveToStorage(OMD_Bridge_IsSutureBandageDirty("feet")));

		playerStorage.Set("HeadSutureBandageUsedRag", OMD_Bridge_SutureActiveToStorage(m_SutureBandageUsedRagHead));
		playerStorage.Set("ArmsSutureBandageUsedRag", OMD_Bridge_SutureActiveToStorage(m_SutureBandageUsedRagArms));
		playerStorage.Set("LegsSutureBandageUsedRag", OMD_Bridge_SutureActiveToStorage(m_SutureBandageUsedRagLegs));
		playerStorage.Set("TorsoSutureBandageUsedRag", OMD_Bridge_SutureActiveToStorage(m_SutureBandageUsedRagTorso));
		playerStorage.Set("HandsSutureBandageUsedRag", OMD_Bridge_SutureActiveToStorage(m_SutureBandageUsedRagHands));
		playerStorage.Set("FeetSutureBandageUsedRag", OMD_Bridge_SutureActiveToStorage(m_SutureBandageUsedRagFeet));
		playerStorage.Set("SutureBandageDirtIsPercent", 1);
	}

	void OMD_Bridge_OnStoreLoadSutureBandages(InediaInfectedAI_PlayerStorage playerStorage)
	{
		if (!playerStorage || !m_Player)
		{
			return;
		}

		m_SutureWoundTierHead = Math.Round(playerStorage.Get("m_SutureWoundTierHead"));
		m_SutureWoundTierArms = Math.Round(playerStorage.Get("m_SutureWoundTierArms"));
		m_SutureWoundTierLegs = Math.Round(playerStorage.Get("m_SutureWoundTierLegs"));
		m_SutureWoundTierTorso = Math.Round(playerStorage.Get("m_SutureWoundTierTorso"));
		m_SutureWoundTierHands = Math.Round(playerStorage.Get("m_SutureWoundTierHands"));
		m_SutureWoundTierFeet = Math.Round(playerStorage.Get("m_SutureWoundTierFeet"));

		m_SutureBandageDirtyProgressHead = playerStorage.Get("m_SutureBandageDirtyProgressHead");
		m_SutureBandageDirtyProgressArms = playerStorage.Get("m_SutureBandageDirtyProgressArms");
		m_SutureBandageDirtyProgressLegs = playerStorage.Get("m_SutureBandageDirtyProgressLegs");
		m_SutureBandageDirtyProgressTorso = playerStorage.Get("m_SutureBandageDirtyProgressTorso");
		m_SutureBandageDirtyProgressHands = playerStorage.Get("m_SutureBandageDirtyProgressHands");
		m_SutureBandageDirtyProgressFeet = playerStorage.Get("m_SutureBandageDirtyProgressFeet");

		m_SutureBandageUsedRagHead = playerStorage.Get("HeadSutureBandageUsedRag") != 0;
		m_SutureBandageUsedRagArms = playerStorage.Get("ArmsSutureBandageUsedRag") != 0;
		m_SutureBandageUsedRagLegs = playerStorage.Get("LegsSutureBandageUsedRag") != 0;
		m_SutureBandageUsedRagTorso = playerStorage.Get("TorsoSutureBandageUsedRag") != 0;
		m_SutureBandageUsedRagHands = playerStorage.Get("HandsSutureBandageUsedRag") != 0;
		m_SutureBandageUsedRagFeet = playerStorage.Get("FeetSutureBandageUsedRag") != 0;

		m_Player.OMD_Bridge_SetSutureBandageBit("head", playerStorage.Get("HeadSutureBandageIsActive") != 0);
		m_Player.OMD_Bridge_SetSutureBandageBit("arms", playerStorage.Get("ArmsSutureBandageIsActive") != 0);
		m_Player.OMD_Bridge_SetSutureBandageBit("legs", playerStorage.Get("LegsSutureBandageIsActive") != 0);
		m_Player.OMD_Bridge_SetSutureBandageBit("torso", playerStorage.Get("TorsoSutureBandageIsActive") != 0);
		m_Player.OMD_Bridge_SetSutureBandageBit("hands", playerStorage.Get("HandsSutureBandageIsActive") != 0);
		m_Player.OMD_Bridge_SetSutureBandageBit("feet", playerStorage.Get("FeetSutureBandageIsActive") != 0);

		m_Player.OMD_Bridge_SetSutureBandageDirtyBit("head", playerStorage.Get("HeadSutureBandageIsDirty") != 0);
		m_Player.OMD_Bridge_SetSutureBandageDirtyBit("arms", playerStorage.Get("ArmsSutureBandageIsDirty") != 0);
		m_Player.OMD_Bridge_SetSutureBandageDirtyBit("legs", playerStorage.Get("LegsSutureBandageIsDirty") != 0);
		m_Player.OMD_Bridge_SetSutureBandageDirtyBit("torso", playerStorage.Get("TorsoSutureBandageIsDirty") != 0);
		m_Player.OMD_Bridge_SetSutureBandageDirtyBit("hands", playerStorage.Get("HandsSutureBandageIsDirty") != 0);
		m_Player.OMD_Bridge_SetSutureBandageDirtyBit("feet", playerStorage.Get("FeetSutureBandageIsDirty") != 0);
		if (playerStorage.Get("SutureBandageDirtIsPercent") == 0)
		{
			OMD_Bridge_NormalizeLegacySutureBandageDirt("head");
			OMD_Bridge_NormalizeLegacySutureBandageDirt("arms");
			OMD_Bridge_NormalizeLegacySutureBandageDirt("legs");
			OMD_Bridge_NormalizeLegacySutureBandageDirt("torso");
			OMD_Bridge_NormalizeLegacySutureBandageDirt("hands");
			OMD_Bridge_NormalizeLegacySutureBandageDirt("feet");
			playerStorage.Set("SutureBandageDirtIsPercent", 1);
		}
	}

	void OMD_Bridge_NormalizeLegacySutureBandageDirt(string limb)
	{
		float progress = OMD_Bridge_GetSutureBandageDirtyProgressForLimb(limb);
		float seconds = OMD_BridgeConfig.GetSutureBandageDirtySeconds();
		if (OMD_Bridge_GetSutureBandageUsedRagForLimb(limb))
		{
			seconds = OMD_BridgeConfig.GetSutureRagDirtySeconds();
		}

		if (seconds <= 0)
		{
			return;
		}

		float scaled = progress / seconds * 100.0;
		if (scaled > 100)
		{
			scaled = 100;
		}

		OMD_Bridge_SetSutureBandageDirtyProgressForLimb(limb, scaled);
		if (scaled >= 100 && m_Player)
		{
			m_Player.OMD_Bridge_SetSutureBandageDirtyBit(limb, true);
		}
	}
};
