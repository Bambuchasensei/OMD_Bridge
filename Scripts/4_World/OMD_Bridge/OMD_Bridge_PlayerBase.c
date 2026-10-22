modded class PlayerBase
{
	static const int OMD_BRIDGE_HANDS_BREAK = 0;
	static const int OMD_BRIDGE_HANDS_STABILIZE = 1;
	static const int OMD_BRIDGE_HANDS_DEEP_WOUND = 2;
	static const int OMD_BRIDGE_HANDS_BANDAGE = 3;
	static const int OMD_BRIDGE_HANDS_BANDAGE_EFFECTIVE = 4;
	static const int OMD_BRIDGE_HANDS_BULLET_BIT1 = 5;
	static const int OMD_BRIDGE_HANDS_BULLET_BIT2 = 6;

	static const int OMD_BRIDGE_FEET_BREAK = 0;
	static const int OMD_BRIDGE_FEET_STABILIZE = 1;
	static const int OMD_BRIDGE_FEET_DEEP_WOUND = 2;
	static const int OMD_BRIDGE_FEET_BANDAGE = 3;
	static const int OMD_BRIDGE_FEET_BANDAGE_EFFECTIVE = 4;
	static const int OMD_BRIDGE_FEET_BULLET_BIT1 = 5;
	static const int OMD_BRIDGE_FEET_BULLET_BIT2 = 6;

	static const int OMD_BRIDGE_SUTURE_HEAD = 0;
	static const int OMD_BRIDGE_SUTURE_ARMS = 1;
	static const int OMD_BRIDGE_SUTURE_LEGS = 2;
	static const int OMD_BRIDGE_SUTURE_TORSO = 3;
	static const int OMD_BRIDGE_SUTURE_HANDS = 4;
	static const int OMD_BRIDGE_SUTURE_FEET = 5;

	static const int OMD_BRIDGE_SEVERITY_SHIFT_HEAD = 0;
	static const int OMD_BRIDGE_SEVERITY_SHIFT_TORSO = 2;
	static const int OMD_BRIDGE_SEVERITY_SHIFT_ARMS = 4;
	static const int OMD_BRIDGE_SEVERITY_SHIFT_LEGS = 6;
	static const int OMD_BRIDGE_SEVERITY_SHIFT_HANDS = 8;
	static const int OMD_BRIDGE_SEVERITY_SHIFT_FEET = 10;

	static const int OMD_BRIDGE_SCRATCH_BITS = 5;
	static const int OMD_BRIDGE_SCRATCH_MASK = 31;
	static const int OMD_BRIDGE_SCRATCH_SHIFT_HEAD = 0;
	static const int OMD_BRIDGE_SCRATCH_SHIFT_ARMS = 5;
	static const int OMD_BRIDGE_SCRATCH_SHIFT_LEGS = 10;
	static const int OMD_BRIDGE_SCRATCH_SHIFT_TORSO = 15;
	static const int OMD_BRIDGE_SCRATCH_SHIFT_HANDS = 20;
	static const int OMD_BRIDGE_SCRATCH_SHIFT_FEET = 25;

	int m_OMD_Bridge_PainLevelsSync = 0;
	int m_OMD_Bridge_HandsStateSync = 0;
	int m_OMD_Bridge_FeetStateSync = 0;
	int m_OMD_Bridge_SutureStateSync = 0;
	int m_OMD_Bridge_SutureBandageSync = 0;
	int m_OMD_Bridge_DeepWoundSeveritySync = 0;
	int m_OMD_Bridge_ScratchCountsSyncLow = 0;
	int m_OMD_Bridge_ScratchCountsSyncHigh = 0;
	protected ref map<string, float> m_OMD_Symptom_TerjeValue;

	void PlayerBase()
	{
		RegisterNetSyncVariableInt("m_OMD_Bridge_PainLevelsSync", 0, 255);
		RegisterNetSyncVariableInt("m_OMD_Bridge_HandsStateSync", 0, 127);
		RegisterNetSyncVariableInt("m_OMD_Bridge_FeetStateSync", 0, 127);
		RegisterNetSyncVariableInt("m_OMD_Bridge_SutureStateSync", 0, 63);
		RegisterNetSyncVariableInt("m_OMD_Bridge_SutureBandageSync", 0, 4095);
		RegisterNetSyncVariableInt("m_OMD_Bridge_DeepWoundSeveritySync", 0, 4095);
		RegisterNetSyncVariableInt("m_OMD_Bridge_ScratchCountsSyncLow", 0, 32767);
		RegisterNetSyncVariableInt("m_OMD_Bridge_ScratchCountsSyncHigh", 0, 32767);
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		OMD_Bridge_ApplySyncedPainLevels();
	}

	override void InediaInfectedAI_RemoveInediaDebuffs(bool spawnUsedItems = true)
	{
		InediaInfectedAI_PainManager painManager = InediaInfectedAI_GetPainManager();
		if (painManager)
		{
			painManager.OMD_Bridge_RemoveAllBridgeDebuffs(spawnUsedItems);
		}

		super.InediaInfectedAI_RemoveInediaDebuffs(spawnUsedItems);
	}

	override void SetActions(out TInputActionMap InputActionMap)
	{
		super.SetActions(InputActionMap);

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		AddAction(OMD_Bridge_ActionFractureUnstabilizationHandsSelf, InputActionMap);
		AddAction(OMD_Bridge_ActionFractureUnstabilizationFeetSelf, InputActionMap);
		AddAction(OMD_Bridge_ActionFractureUnstabilizationHandsTarget, InputActionMap);
		AddAction(OMD_Bridge_ActionFractureUnstabilizationFeetTarget, InputActionMap);

		AddAction(OMD_Bridge_ActionDeepWoundUnbandageIneffectiveHandsSelf, InputActionMap);
		AddAction(OMD_Bridge_ActionDeepWoundUnbandageIneffectiveFeetSelf, InputActionMap);
		AddAction(OMD_Bridge_ActionDeepWoundUnbandageEffectiveHandsSelf, InputActionMap);
		AddAction(OMD_Bridge_ActionDeepWoundUnbandageEffectiveFeetSelf, InputActionMap);
		AddAction(OMD_Bridge_ActionDeepWoundUnbandageIneffectiveHandsTarget, InputActionMap);
		AddAction(OMD_Bridge_ActionDeepWoundUnbandageIneffectiveFeetTarget, InputActionMap);
		AddAction(OMD_Bridge_ActionDeepWoundUnbandageEffectiveHandsTarget, InputActionMap);
		AddAction(OMD_Bridge_ActionDeepWoundUnbandageEffectiveFeetTarget, InputActionMap);
	}

	override bool CanSprint()
	{
		if (!super.CanSprint())
		{
			return false;
		}

		if (!OMD_BridgeConfig.IsActive())
		{
			return true;
		}

		if (!OMD_BridgeConfig.GetFeetDebuffBlockSprintOnFracture())
		{
			return true;
		}

		InediaInfectedAI_PainManager painManager = InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return true;
		}

		if (painManager.IsLimbBroken("feet") && !painManager.IsLimbStabilized("feet"))
		{
			return false;
		}

		return true;
	}

	float OMD_Bridge_GetHandsActionTimeMultiplier()
	{
		InediaInfectedAI_PainManager painManager = InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return 1;
		}

		return painManager.OMD_Bridge_GetHandsActionTimeMultiplier();
	}

	bool OMD_Bridge_ShouldBlockRunFromFeetFracture()
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		if (!OMD_BridgeConfig.GetFeetDebuffBlockRunOnFracture())
		{
			return false;
		}

		InediaInfectedAI_PainManager painManager = InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return false;
		}

		if (painManager.IsLimbBroken("feet") && !painManager.IsLimbStabilized("feet"))
		{
			return true;
		}

		return false;
	}

	void OMD_Bridge_SetPainLevelsSync(InediaInfectedAI_LimbPainLevels handsWithBuffsLevel, InediaInfectedAI_LimbPainLevels feetWithBuffsLevel)
	{
		int handsLevel = OMD_Bridge_PainLevelToInt(handsWithBuffsLevel);
		int feetLevel = OMD_Bridge_PainLevelToInt(feetWithBuffsLevel);
		int packed = (handsLevel & 15) | ((feetLevel & 15) << 4);

		if (packed == m_OMD_Bridge_PainLevelsSync)
		{
			return;
		}

		m_OMD_Bridge_PainLevelsSync = packed;
		SetSynchDirty();
	}

	int OMD_Bridge_GetSyncedHandsPainLevel()
	{
		return m_OMD_Bridge_PainLevelsSync & 15;
	}

	int OMD_Bridge_GetSyncedFeetPainLevel()
	{
		return (m_OMD_Bridge_PainLevelsSync >> 4) & 15;
	}

	void OMD_Bridge_SetHandsStateBit(int bitIndex, bool value)
	{
		int mask = 1 << bitIndex;
		int packed = m_OMD_Bridge_HandsStateSync;

		if (value)
		{
			packed = packed | mask;
		}
		else
		{
			packed = packed & ~mask;
		}

		if (packed == m_OMD_Bridge_HandsStateSync)
		{
			return;
		}

		m_OMD_Bridge_HandsStateSync = packed;
		SetSynchDirty();
	}

	bool OMD_Bridge_GetHandsStateBit(int bitIndex)
	{
		int mask = 1 << bitIndex;
		return (m_OMD_Bridge_HandsStateSync & mask) != 0;
	}

	void OMD_Bridge_SetFeetStateBit(int bitIndex, bool value)
	{
		int mask = 1 << bitIndex;
		int packed = m_OMD_Bridge_FeetStateSync;

		if (value)
		{
			packed = packed | mask;
		}
		else
		{
			packed = packed & ~mask;
		}

		if (packed == m_OMD_Bridge_FeetStateSync)
		{
			return;
		}

		m_OMD_Bridge_FeetStateSync = packed;
		SetSynchDirty();
	}

	bool OMD_Bridge_GetFeetStateBit(int bitIndex)
	{
		int mask = 1 << bitIndex;
		return (m_OMD_Bridge_FeetStateSync & mask) != 0;
	}

	void OMD_Bridge_SetSutureStateBit(int bitIndex, bool value)
	{
		int mask = 1 << bitIndex;
		int packed = m_OMD_Bridge_SutureStateSync;

		if (value)
		{
			packed = packed | mask;
		}
		else
		{
			packed = packed & ~mask;
		}

		if (packed == m_OMD_Bridge_SutureStateSync)
		{
			return;
		}

		m_OMD_Bridge_SutureStateSync = packed;
		SetSynchDirty();
	}

	bool OMD_Bridge_GetSutureStateBit(int bitIndex)
	{
		int mask = 1 << bitIndex;
		return (m_OMD_Bridge_SutureStateSync & mask) != 0;
	}

	void OMD_Bridge_SetSutureBandageBit(string limb, bool value)
	{
		int bitIndex = OMD_Bridge_GetSutureBitIndexForLimb(limb);
		if (bitIndex < 0)
		{
			return;
		}

		int mask = 1 << bitIndex;
		int packed = m_OMD_Bridge_SutureBandageSync;

		if (value)
		{
			packed = packed | mask;
		}
		else
		{
			packed = packed & ~mask;
		}

		if (packed == m_OMD_Bridge_SutureBandageSync)
		{
			return;
		}

		m_OMD_Bridge_SutureBandageSync = packed;
		SetSynchDirty();
	}

	bool OMD_Bridge_GetSutureBandageBit(string limb)
	{
		int bitIndex = OMD_Bridge_GetSutureBitIndexForLimb(limb);
		if (bitIndex < 0)
		{
			return false;
		}

		int mask = 1 << bitIndex;
		return (m_OMD_Bridge_SutureBandageSync & mask) != 0;
	}

	void OMD_Bridge_SetSutureBandageDirtyBit(string limb, bool value)
	{
		int bitIndex = OMD_Bridge_GetSutureBitIndexForLimb(limb);
		if (bitIndex < 0)
		{
			return;
		}

		int mask = 1 << (bitIndex + 6);
		int packed = m_OMD_Bridge_SutureBandageSync;

		if (value)
		{
			packed = packed | mask;
		}
		else
		{
			packed = packed & ~mask;
		}

		if (packed == m_OMD_Bridge_SutureBandageSync)
		{
			return;
		}

		m_OMD_Bridge_SutureBandageSync = packed;
		SetSynchDirty();
	}

	bool OMD_Bridge_GetSutureBandageDirtyBit(string limb)
	{
		int bitIndex = OMD_Bridge_GetSutureBitIndexForLimb(limb);
		if (bitIndex < 0)
		{
			return false;
		}

		int mask = 1 << (bitIndex + 6);
		return (m_OMD_Bridge_SutureBandageSync & mask) != 0;
	}

	void OMD_Bridge_SetDeepWoundSeverityForLimb(string limb, int tier)
	{
		int shift = OMD_Bridge_GetSeverityShiftForLimb(limb);
		if (shift < 0)
		{
			return;
		}

		if (tier < 0)
		{
			tier = 0;
		}

		if (tier > 3)
		{
			tier = 3;
		}

		int clearMask = ~(3 << shift);
		int packed = (m_OMD_Bridge_DeepWoundSeveritySync & clearMask) | ((tier & 3) << shift);
		if (packed == m_OMD_Bridge_DeepWoundSeveritySync)
		{
			return;
		}

		m_OMD_Bridge_DeepWoundSeveritySync = packed;
		SetSynchDirty();
	}

	int OMD_Bridge_GetSyncedDeepWoundSeverityForLimb(string limb)
	{
		int shift = OMD_Bridge_GetSeverityShiftForLimb(limb);
		if (shift < 0)
		{
			return 0;
		}

		return (m_OMD_Bridge_DeepWoundSeveritySync >> shift) & 3;
	}

	int OMD_Bridge_GetSeverityShiftForLimb(string limb)
	{
		if (limb == "head")
		{
			return OMD_BRIDGE_SEVERITY_SHIFT_HEAD;
		}

		if (limb == "torso")
		{
			return OMD_BRIDGE_SEVERITY_SHIFT_TORSO;
		}

		if (limb == "arms")
		{
			return OMD_BRIDGE_SEVERITY_SHIFT_ARMS;
		}

		if (limb == "legs")
		{
			return OMD_BRIDGE_SEVERITY_SHIFT_LEGS;
		}

		if (limb == "hands")
		{
			return OMD_BRIDGE_SEVERITY_SHIFT_HANDS;
		}

		if (limb == "feet")
		{
			return OMD_BRIDGE_SEVERITY_SHIFT_FEET;
		}

		return -1;
	}

	int OMD_Bridge_GetSutureBitIndexForLimb(string limb)
	{
		if (limb == "head")
		{
			return OMD_BRIDGE_SUTURE_HEAD;
		}

		if (limb == "arms")
		{
			return OMD_BRIDGE_SUTURE_ARMS;
		}

		if (limb == "legs")
		{
			return OMD_BRIDGE_SUTURE_LEGS;
		}

		if (limb == "torso")
		{
			return OMD_BRIDGE_SUTURE_TORSO;
		}

		if (limb == "hands")
		{
			return OMD_BRIDGE_SUTURE_HANDS;
		}

		if (limb == "feet")
		{
			return OMD_BRIDGE_SUTURE_FEET;
		}

		return -1;
	}

	int OMD_Bridge_CountHandsScratches()
	{
		return OMD_Bridge_CountLimbScratches("hands");
	}

	int OMD_Bridge_CountFeetScratches()
	{
		return OMD_Bridge_CountLimbScratches("feet");
	}

	int OMD_Bridge_GetScratchLimbShift(string limb)
	{
		if (limb == "head")
		{
			return OMD_BRIDGE_SCRATCH_SHIFT_HEAD;
		}

		if (limb == "arms")
		{
			return OMD_BRIDGE_SCRATCH_SHIFT_ARMS;
		}

		if (limb == "legs")
		{
			return OMD_BRIDGE_SCRATCH_SHIFT_LEGS;
		}

		if (limb == "torso")
		{
			return OMD_BRIDGE_SCRATCH_SHIFT_TORSO;
		}

		if (limb == "hands")
		{
			return OMD_BRIDGE_SCRATCH_SHIFT_HANDS;
		}

		if (limb == "feet")
		{
			return OMD_BRIDGE_SCRATCH_SHIFT_FEET;
		}

		return -1;
	}

	int OMD_Bridge_GetScratchCountStored(string limb)
	{
		int shift = OMD_Bridge_GetScratchLimbShift(limb);
		if (shift < 0)
		{
			return 0;
		}

		if (shift < 15)
		{
			return (m_OMD_Bridge_ScratchCountsSyncLow >> shift) & OMD_BRIDGE_SCRATCH_MASK;
		}

		int highShift = shift - 15;
		return (m_OMD_Bridge_ScratchCountsSyncHigh >> highShift) & OMD_BRIDGE_SCRATCH_MASK;
	}

	void OMD_Bridge_SetScratchCountStored(string limb, int count)
	{
		int shift = OMD_Bridge_GetScratchLimbShift(limb);
		if (shift < 0)
		{
			return;
		}

		if (count < 0)
		{
			count = 0;
		}

		if (count > OMD_BRIDGE_SCRATCH_MASK)
		{
			count = OMD_BRIDGE_SCRATCH_MASK;
		}

		if (shift < 15)
		{
			int packedLow = m_OMD_Bridge_ScratchCountsSyncLow;
			packedLow = packedLow & ~(OMD_BRIDGE_SCRATCH_MASK << shift);
			packedLow = packedLow | (count << shift);
			if (packedLow == m_OMD_Bridge_ScratchCountsSyncLow)
			{
				return;
			}

			m_OMD_Bridge_ScratchCountsSyncLow = packedLow;
			SetSynchDirty();
			return;
		}

		int highShift = shift - 15;
		int packedHigh = m_OMD_Bridge_ScratchCountsSyncHigh;
		packedHigh = packedHigh & ~(OMD_BRIDGE_SCRATCH_MASK << highShift);
		packedHigh = packedHigh | (count << highShift);
		if (packedHigh == m_OMD_Bridge_ScratchCountsSyncHigh)
		{
			return;
		}

		m_OMD_Bridge_ScratchCountsSyncHigh = packedHigh;
		SetSynchDirty();
	}

	int OMD_Bridge_CountLimbScratches(string limb)
	{
		int stored = OMD_Bridge_GetScratchCountStored(limb);
		int bleeds = OMD_Bridge_CountBleedingZonesForLimb(limb);
		if (bleeds > stored)
		{
			return bleeds;
		}

		return stored;
	}

	bool OMD_Bridge_IsSutureBlockingScratchCount(string limb)
	{
		InediaInfectedAI_PainManager painManager = InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return false;
		}

		return painManager.OMD_Bridge_IsLimbSutured(limb);
	}

	void OMD_Bridge_DropNewestScratchBleeds(string limb, int count)
	{
		int safety = 0;
		int left = count;
		while (left > 0 && safety < 16)
		{
			OMD_Bridge_RemoveOneScratchBleed(limb);
			left = left - 1;
			safety = safety + 1;
		}
	}

	void OMD_Bridge_BumpScratchCount(string limb, int delta)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (delta <= 0)
		{
			return;
		}

		if (OMD_Bridge_IsSutureBlockingScratchCount(limb))
		{
			OMD_Bridge_NoteUnbandagedSutureScratch(limb, delta);
			OMD_Bridge_DropNewestScratchBleeds(limb, delta);
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] suture scratch counter skipped limb=" + limb + " delta=" + delta.ToString());
			}

			return;
		}

		OMD_Bridge_SetScratchCountStored(limb, OMD_Bridge_GetScratchCountStored(limb) + delta);
		OMD_Bridge_NoteUnbandagedSutureScratch(limb, delta);
	}

	void OMD_Bridge_NoteUnbandagedSutureScratch(string limb, int amount)
	{
		if (!GetGame().IsServer() || amount <= 0)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return;
		}

		painManager.OMD_Bridge_NoteSutureScratchPending(limb, amount);
	}

	void OMD_Bridge_SyncScratchCountFromBleeds(string limb)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		int bleeds = OMD_Bridge_CountBleedingZonesForLimb(limb);
		int stored = OMD_Bridge_GetScratchCountStored(limb);
		if (bleeds > stored)
		{
			OMD_Bridge_SetScratchCountStored(limb, bleeds);
		}
	}

	bool OMD_Bridge_IsZoneArmorCovered(string dmgZone, string ammo, int component, EntityAI source, vector modelPos)
	{
		return false;
	}

	bool OMD_Bridge_AddLimbScratchFromSource(string limb, string dmgZone, float chancePercent)
	{
		if (!GetGame().IsServer())
		{
			return false;
		}

		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		if (chancePercent < 0)
		{
			chancePercent = OMD_BridgeConfig.GetScratchChancePercentForLimb(limb);
		}

		if (chancePercent <= 0)
		{
			return false;
		}

		if (chancePercent < 100 && Math.RandomFloatInclusive(0, 100) > chancePercent)
		{
			return false;
		}

		OMD_Bridge_RegisterLimbScratch(limb, dmgZone);
		return true;
	}

	void OMD_Bridge_TryAddHandsScratch(string dmgZone)
	{
		OMD_Bridge_TryAddLimbScratch("hands", dmgZone);
	}

	void OMD_Bridge_TryAddFeetScratch(string dmgZone)
	{
		OMD_Bridge_TryAddLimbScratch("feet", dmgZone);
	}

	void OMD_Bridge_TryAddLimbScratch(string limb, string dmgZone)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (limb == "feet")
		{
			EntityAI shoes = GetInventory().FindAttachment(InventorySlots.FEET);
			if (shoes && shoes.GetHealthLevel() < GameConstants.STATE_DAMAGED)
			{
				return;
			}
		}

		float chance = OMD_BridgeConfig.GetScratchChancePercentForLimb(limb);
		if (chance <= 0)
		{
			return;
		}

		if (Math.RandomFloatInclusive(0, 100) > chance)
		{
			return;
		}

		OMD_Bridge_RegisterLimbScratch(limb, dmgZone);
	}

	void OMD_Bridge_RegisterLimbScratch(string limb, string dmgZone)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (OMD_Bridge_IsSutureBlockingScratchCount(limb))
		{
			OMD_Bridge_NoteUnbandagedSutureScratch(limb, 1);
			SendSoundEvent(EPlayerSoundEventID.INJURED_LIGHT);
			OMD_Bridge_ApplyScratchMinPain(limb);
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] suture scratch counter skipped limb=" + limb + " zone=" + dmgZone);
			}

			return;
		}

		BleedingSourcesManagerServer bleedManager = GetBleedingManagerServer();
		if (bleedManager)
		{
			OMD_Bridge_AttemptAddScratchBleed(bleedManager, limb, dmgZone);
		}

		int nextCount = OMD_Bridge_GetScratchCountStored(limb) + 1;
		OMD_Bridge_SetScratchCountStored(limb, nextCount);
		OMD_Bridge_NoteUnbandagedSutureScratch(limb, 1);
		SendSoundEvent(EPlayerSoundEventID.INJURED_LIGHT);
		OMD_Bridge_ApplyScratchMinPain(limb);
		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] scratch limb=" + limb + " zone=" + dmgZone + " count=" + OMD_Bridge_CountLimbScratches(limb).ToString());
		}
	}

	void OMD_Bridge_ApplyScratchMinPain(string limb)
	{
		InediaInfectedAI_PainManager painManager = InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return;
		}

		painManager.OMD_Bridge_EnsureMinPainFloorForLimb(limb);
	}

	void OMD_Bridge_RemoveAllLimbScratches(string limb)
	{
		OMD_Bridge_SetScratchCountStored(limb, 0);

		BleedingSourcesManagerServer bleedManager = GetBleedingManagerServer();
		if (!bleedManager)
		{
			return;
		}

		int safety = 0;
		while (OMD_Bridge_CountBleedingZonesForLimb(limb) > 0 && safety < 16)
		{
			OMD_Bridge_RemoveOneScratchBleed(limb);
			safety = safety + 1;
		}
	}

	void OMD_Bridge_RemoveOneScratch(string limb)
	{
		int count = OMD_Bridge_GetScratchCountStored(limb);
		if (count > 0)
		{
			OMD_Bridge_SetScratchCountStored(limb, count - 1);
		}

		OMD_Bridge_RemoveOneScratchBleed(limb);
	}

	void OMD_Bridge_RemoveOneScratchBleed(string limb)
	{
		BleedingSourcesManagerServer bleedManager = GetBleedingManagerServer();
		if (!bleedManager)
		{
			return;
		}

		if (limb == "hands")
		{
			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftForeArmRoll"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightForeArmRoll"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftForeArm"))
			{
				return;
			}

			bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightForeArm");
			return;
		}

		if (limb == "feet")
		{
			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftFoot"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightFoot"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftToeBase"))
			{
				return;
			}

			bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightToeBase");
			return;
		}

		if (limb == "head")
		{
			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("Head"))
			{
				return;
			}

			bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("Neck");
			return;
		}

		if (limb == "arms")
		{
			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftArmRoll"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightArmRoll"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftArm"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightArm"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftShoulder"))
			{
				return;
			}

			bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightShoulder");
			return;
		}

		if (limb == "legs")
		{
			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftLegRoll"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightLegRoll"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftUpLegRoll"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightUpLegRoll"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftLeg"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightLeg"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("LeftUpLeg"))
			{
				return;
			}

			bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("RightUpLeg");
			return;
		}

		if (limb == "torso")
		{
			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("Spine2"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("Spine1"))
			{
				return;
			}

			if (bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("Spine3"))
			{
				return;
			}

			bleedManager.OMD_Bridge_RemoveBleedingSourceBySelection("Pelvis");
		}
	}

	protected bool OMD_Bridge_AttemptAddScratchBleed(BleedingSourcesManagerServer bleedManager, string limb, string dmgZone)
	{
		string primarySelection = "";
		string secondarySelection = "";
		string tertiarySelection = "";
		string quaternarySelection = "";

		if (limb == "hands")
		{
			primarySelection = "RightForeArmRoll";
			secondarySelection = "LeftForeArmRoll";
			if (dmgZone == "LeftHand")
			{
				primarySelection = "LeftForeArmRoll";
				secondarySelection = "RightForeArmRoll";
			}
		}
		else if (limb == "feet")
		{
			primarySelection = "RightFoot";
			secondarySelection = "LeftFoot";
			tertiarySelection = "RightToeBase";
			quaternarySelection = "LeftToeBase";
			if (dmgZone == "LeftFoot")
			{
				primarySelection = "LeftFoot";
				secondarySelection = "RightFoot";
			}
		}
		else if (limb == "head")
		{
			primarySelection = "Head";
			secondarySelection = "Neck";
		}
		else if (limb == "arms")
		{
			primarySelection = "RightArmRoll";
			secondarySelection = "LeftArmRoll";
			tertiarySelection = "RightArm";
			quaternarySelection = "LeftArm";
			if (dmgZone == "LeftArm" || dmgZone == "LeftHand" || dmgZone == "LeftShoulder")
			{
				primarySelection = "LeftArmRoll";
				secondarySelection = "RightArmRoll";
				tertiarySelection = "LeftArm";
				quaternarySelection = "RightArm";
			}
		}
		else if (limb == "legs")
		{
			primarySelection = "RightLegRoll";
			secondarySelection = "LeftLegRoll";
			tertiarySelection = "RightLeg";
			quaternarySelection = "LeftLeg";
			if (dmgZone == "LeftLeg" || dmgZone == "LeftFoot")
			{
				primarySelection = "LeftLegRoll";
				secondarySelection = "RightLegRoll";
				tertiarySelection = "LeftLeg";
				quaternarySelection = "RightLeg";
			}
		}
		else if (limb == "torso")
		{
			primarySelection = "Spine2";
			secondarySelection = "Spine1";
			tertiarySelection = "Spine3";
			quaternarySelection = "Pelvis";
		}
		else
		{
			return false;
		}

		bool added = false;
		if (primarySelection != "")
		{
			added = bleedManager.AttemptAddBleedingSourceBySelection(primarySelection);
		}

		if (!added && secondarySelection != "")
		{
			added = bleedManager.AttemptAddBleedingSourceBySelection(secondarySelection);
		}

		if (!added && tertiarySelection != "")
		{
			added = bleedManager.AttemptAddBleedingSourceBySelection(tertiarySelection);
		}

		if (!added && quaternarySelection != "")
		{
			added = bleedManager.AttemptAddBleedingSourceBySelection(quaternarySelection);
		}

		return added;
	}

	protected void OMD_Bridge_ApplySyncedPainLevels()
	{
		InediaInfectedAI_PainManager painManager = InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return;
		}

		painManager.OMD_Bridge_ApplySyncedPainLevels(OMD_Bridge_GetSyncedHandsPainLevel(), OMD_Bridge_GetSyncedFeetPainLevel());
	}

	int OMD_Bridge_CountBleedingZonesForLimb(string limb)
	{
		if (limb == "hands")
		{
			return OMD_Bridge_CountBleedingZones("LeftForeArmRoll", "RightForeArmRoll", "LeftForeArm", "RightForeArm");
		}

		if (limb == "feet")
		{
			return OMD_Bridge_CountBleedingZones("LeftFoot", "RightFoot", "LeftToeBase", "RightToeBase");
		}

		if (limb == "head")
		{
			return OMD_Bridge_CountBleedingZones("Head", "Neck", "", "");
		}

		if (limb == "arms")
		{
			int armsCount = OMD_Bridge_CountBleedingZones("LeftShoulder", "LeftArm", "LeftArmRoll", "RightShoulder");
			armsCount = armsCount + OMD_Bridge_CountBleedingZones("RightArm", "RightArmRoll", "", "");
			return armsCount;
		}

		if (limb == "legs")
		{
			int legsCount = OMD_Bridge_CountBleedingZones("LeftLeg", "LeftLegRoll", "LeftUpLeg", "LeftUpLegRoll");
			legsCount = legsCount + OMD_Bridge_CountBleedingZones("RightLeg", "RightLegRoll", "RightUpLeg", "RightUpLegRoll");
			return legsCount;
		}

		if (limb == "torso")
		{
			int torsoCount = OMD_Bridge_CountBleedingZones("Pelvis", "Spine", "Spine1", "Spine2");
			torsoCount = torsoCount + OMD_Bridge_CountBleedingZones("Spine3", "", "", "");
			return torsoCount;
		}

		return 0;
	}

	protected int OMD_Bridge_CountBleedingZones(string zoneA, string zoneB, string zoneC, string zoneD)
	{
		BleedingSourcesManagerBase bleedManager;
		if (GetGame().IsServer())
		{
			bleedManager = GetBleedingManagerServer();
		}
		else
		{
			bleedManager = GetBleedingManagerRemote();
		}

		if (!bleedManager)
		{
			return 0;
		}

		int count = 0;
		if (zoneA != "" && bleedManager.IsBleedingSourceActive(zoneA))
		{
			count = count + 1;
		}
		if (zoneB != "" && bleedManager.IsBleedingSourceActive(zoneB))
		{
			count = count + 1;
		}
		if (zoneC != "" && bleedManager.IsBleedingSourceActive(zoneC))
		{
			count = count + 1;
		}
		if (zoneD != "" && bleedManager.IsBleedingSourceActive(zoneD))
		{
			count = count + 1;
		}

		return count;
	}

	protected int OMD_Bridge_PainLevelToInt(InediaInfectedAI_LimbPainLevels level)
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

	void OMD_Bridge_LogTerjeLevel(string zone, string effect, float value, string cause)
	{
		if (!GetGame())
		{
			return;
		}

		if (!GetGame().IsServer())
		{
			return;
		}

		if (!m_OMD_Symptom_TerjeValue)
		{
			m_OMD_Symptom_TerjeValue = new map<string, float>();
		}

		bool known;
		known = m_OMD_Symptom_TerjeValue.Contains(effect);
		float previous;
		previous = 0;
		if (known)
		{
			previous = m_OMD_Symptom_TerjeValue.Get(effect);
		}
		m_OMD_Symptom_TerjeValue.Set(effect, value);

		int nowInt;
		nowInt = (int)value;
		if (!known)
		{
			if (value <= 0)
			{
				return;
			}

			OMD_LogSymptom("TERJE", zone, nowInt, effect, "on", value, cause);
			return;
		}

		if (previous <= 0 && value > 0)
		{
			OMD_LogSymptom("TERJE", zone, nowInt, effect, "on", value, cause);
			return;
		}

		if (previous > 0 && value <= 0)
		{
			OMD_LogSymptom("TERJE", zone, 0, effect, "off", value, cause);
			return;
		}

		int prevInt;
		prevInt = (int)previous;
		if (nowInt == prevInt)
		{
			return;
		}

		string state;
		state = "off";
		if (nowInt > prevInt)
		{
			state = "on";
		}
		OMD_LogSymptom("TERJE", zone, nowInt, effect, state, value, cause);
	}
};
