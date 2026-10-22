modded class InediaInfectedAI_PainManager
{
	override void InitConfig()
	{
		super.InitConfig();

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (m_InediaPainLimbs.Find("hands") == -1)
		{
			m_InediaPainLimbs.Insert("hands");
		}

		if (m_InediaPainLimbs.Find("feet") == -1)
		{
			m_InediaPainLimbs.Insert("feet");
		}

		m_InediaPainLimbMainBleedingZoneName["hands"] = "RightForeArmRoll";
		m_InediaPainLimbAllBleedingZonesNames["hands"] = {"LeftForeArmRoll", "RightForeArmRoll"};
		m_InediaPainLimbsEquipSlots["hands"] = {"Gloves"};
		m_AllowBreakPainDropBelowBadlySeconds["hands"] = 0;
		m_AllowDeepWoundPainDropBelowBadlySeconds["hands"] = 0;
		m_LimbsBreakRegenerationLevels["hands"] = 0;
		m_LimbsDeepWoundRegenerationLevels["hands"] = 0;
		OMD_Bridge_InitFeetLimbConfig();
	}

	override bool CanLimbBeBrokenAfterHit(string limb, float receivedDamage)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (OMD_BridgeConfig.GetFeetBreakDurationSeconds() <= 0)
			{
				return false;
			}
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (OMD_BridgeConfig.GetHandsBreakDurationSeconds() <= 0)
			{
				return false;
			}
		}

		return super.CanLimbBeBrokenAfterHit(limb, receivedDamage);
	}

	override bool ActivateBreakForLimb(string limb, float notMoreFrequentlyThanSeconds = 0, bool enableSound = true, bool spawnUsedItemIfStabilizationActive = true)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			return OMD_Bridge_ActivateBreakForFeet(notMoreFrequentlyThanSeconds, enableSound, spawnUsedItemIfStabilizationActive);
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			return OMD_Bridge_ActivateBreakForHands(notMoreFrequentlyThanSeconds, enableSound, spawnUsedItemIfStabilizationActive);
		}

		return super.ActivateBreakForLimb(limb, notMoreFrequentlyThanSeconds, enableSound, spawnUsedItemIfStabilizationActive);
	}

	override void DeactivateBreakForLimb(string limb, bool spawnUsedItemIfStabilizationActive = true)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_DeactivateBreakForFeet(spawnUsedItemIfStabilizationActive);
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_DeactivateBreakForHands(spawnUsedItemIfStabilizationActive);
			return;
		}

		super.DeactivateBreakForLimb(limb, spawnUsedItemIfStabilizationActive);
	}

	override bool IsLimbBroken(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return false;
			}

			return m_Player.OMD_Bridge_GetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BREAK);
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return false;
			}

			return m_Player.OMD_Bridge_GetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BREAK);
		}

		return super.IsLimbBroken(limb);
	}

	override void ActivateBreakStabilizeForLimb(string limb, float shockReductionMultiplier = 1, float regenerationMultiplier = 1, EntityAI item = null)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_ActivateBreakStabilizeForFeet(shockReductionMultiplier, regenerationMultiplier);
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_ActivateBreakStabilizeForHands(shockReductionMultiplier, regenerationMultiplier);
			return;
		}

		super.ActivateBreakStabilizeForLimb(limb, shockReductionMultiplier, regenerationMultiplier, item);
	}

	override void DeactivateBreakStabilizeForLimb(string limb, bool spawnUsedItem = true)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_DeactivateBreakStabilizeForFeet(spawnUsedItem);
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_DeactivateBreakStabilizeForHands(spawnUsedItem);
			return;
		}

		super.DeactivateBreakStabilizeForLimb(limb, spawnUsedItem);
	}

	override bool IsLimbStabilized(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return false;
			}

			return m_Player.OMD_Bridge_GetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_STABILIZE);
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return false;
			}

			return m_Player.OMD_Bridge_GetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_STABILIZE);
		}

		return super.IsLimbStabilized(limb);
	}

	override void SetBreakTimeRemainingSecondsForLimb(string limb, float seconds)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return;
			}

			m_BreakFeetTimeRemainingSeconds = seconds;
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return;
			}

			m_BreakHandsTimeRemainingSeconds = seconds;
			return;
		}

		super.SetBreakTimeRemainingSecondsForLimb(limb, seconds);
	}

	override float GetBreakTimeRemainingSecondsForLimb(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return 0;
			}

			return m_BreakFeetTimeRemainingSeconds;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return 0;
			}

			return m_BreakHandsTimeRemainingSeconds;
		}

		return super.GetBreakTimeRemainingSecondsForLimb(limb);
	}

	override void SetBreakStabilizationShockReductionMultiplierForLimb(string limb, float shockReductionMultiplier = 1)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return;
			}

			if (shockReductionMultiplier < 1)
			{
				shockReductionMultiplier = 1;
			}

			m_FeetBreakStabilizationItemShockReductionMultiplier = shockReductionMultiplier;
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return;
			}

			if (shockReductionMultiplier < 1)
			{
				shockReductionMultiplier = 1;
			}

			m_HandsBreakStabilizationItemShockReductionMultiplier = shockReductionMultiplier;
			return;
		}

		super.SetBreakStabilizationShockReductionMultiplierForLimb(limb, shockReductionMultiplier);
	}

	override float GetBreakStabilizationShockReductionMultiplierForLimb(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return 1;
			}

			return m_FeetBreakStabilizationItemShockReductionMultiplier;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return 1;
			}

			return m_HandsBreakStabilizationItemShockReductionMultiplier;
		}

		return super.GetBreakStabilizationShockReductionMultiplierForLimb(limb);
	}

	override void SetBreakStabilizationRegenerationMultiplierForLimb(string limb, float regenerationMultiplier = 1)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return;
			}

			if (regenerationMultiplier < 1)
			{
				regenerationMultiplier = 1;
			}

			m_FeetBreakStabilizationItemRegenerationMultiplier = regenerationMultiplier;
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return;
			}

			if (regenerationMultiplier < 1)
			{
				regenerationMultiplier = 1;
			}

			m_HandsBreakStabilizationItemRegenerationMultiplier = regenerationMultiplier;
			return;
		}

		super.SetBreakStabilizationRegenerationMultiplierForLimb(limb, regenerationMultiplier);
	}

	override float GetBreakStabilizationRegenerationMultiplierForLimb(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return 1;
			}

			return m_FeetBreakStabilizationItemRegenerationMultiplier;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBreakSystemIsActive())
			{
				return 1;
			}

			return m_HandsBreakStabilizationItemRegenerationMultiplier;
		}

		return super.GetBreakStabilizationRegenerationMultiplierForLimb(limb);
	}

	override float GetDeepWoundMaxDurationSecondsForLimb(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!m_Player.m_InediaInfectedAI_ConfigPlayers || !LimbsDeepWoundSystemIsActive())
			{
				return 0;
			}

			return OMD_BridgeConfig.GetFeetDeepWoundDurationSeconds();
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!m_Player.m_InediaInfectedAI_ConfigPlayers || !LimbsDeepWoundSystemIsActive())
			{
				return 0;
			}

			return OMD_BridgeConfig.GetHandsDeepWoundDurationSeconds();
		}

		return super.GetDeepWoundMaxDurationSecondsForLimb(limb);
	}

	override bool ActivateDeepWoundForLimb(string limb, float bleedingRateMultiplier = 1, int bleedingZoneIndex = -1, float notMoreFrequentlyThanSeconds = 0, bool enableSound = true, bool spawnUsedRagIfBandageActive = true)
	{
		bool activated = false;
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			activated = OMD_Bridge_ActivateDeepWoundForFeet(bleedingRateMultiplier, bleedingZoneIndex, notMoreFrequentlyThanSeconds, enableSound, spawnUsedRagIfBandageActive);
		}
		else if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			activated = OMD_Bridge_ActivateDeepWoundForHands(bleedingRateMultiplier, bleedingZoneIndex, notMoreFrequentlyThanSeconds, enableSound, spawnUsedRagIfBandageActive);
		}
		else
		{
			activated = super.ActivateDeepWoundForLimb(limb, bleedingRateMultiplier, bleedingZoneIndex, notMoreFrequentlyThanSeconds, enableSound, spawnUsedRagIfBandageActive);
		}

		if (activated)
		{
			OMD_Bridge_SyncDeepWoundSeverityForLimb(limb);
		}

		return activated;
	}

	override void DeactivateDeepWoundForLimb(string limb, bool spawnUsedRagIfBandageActive = true)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_DeactivateDeepWoundForFeet(spawnUsedRagIfBandageActive);
			OMD_Bridge_SyncDeepWoundSeverityForLimb(limb);
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_DeactivateDeepWoundForHands(spawnUsedRagIfBandageActive);
			OMD_Bridge_SyncDeepWoundSeverityForLimb(limb);
			return;
		}

		super.DeactivateDeepWoundForLimb(limb, spawnUsedRagIfBandageActive);
		OMD_Bridge_SyncDeepWoundSeverityForLimb(limb);
	}

	override bool IsLimbDeepWounded(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return false;
			}

			return m_Player.OMD_Bridge_GetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_DEEP_WOUND);
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return false;
			}

			return m_Player.OMD_Bridge_GetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_DEEP_WOUND);
		}

		return super.IsLimbDeepWounded(limb);
	}

	override void SetDeepWoundTimeRemainingSecondsForLimb(string limb, float seconds)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return;
			}

			m_FeetDeepWoundTimeRemainingSeconds = seconds;
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return;
			}

			m_HandsDeepWoundTimeRemainingSeconds = seconds;
			return;
		}

		super.SetDeepWoundTimeRemainingSecondsForLimb(limb, seconds);
	}

	override float GetDeepWoundTimeRemainingSecondsForLimb(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return 0;
			}

			return m_FeetDeepWoundTimeRemainingSeconds;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return 0;
			}

			return m_HandsDeepWoundTimeRemainingSeconds;
		}

		return super.GetDeepWoundTimeRemainingSecondsForLimb(limb);
	}

	override void SetDeepWoundBleedingRateForLimb(string limb, float bleedingRate)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return;
			}

			m_FeetDeepWoundBleedingRate = bleedingRate;
			OMD_Bridge_SyncDeepWoundSeverityForLimb(limb);
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return;
			}

			m_HandsDeepWoundBleedingRate = bleedingRate;
			OMD_Bridge_SyncDeepWoundSeverityForLimb(limb);
			return;
		}

		super.SetDeepWoundBleedingRateForLimb(limb, bleedingRate);
		OMD_Bridge_SyncDeepWoundSeverityForLimb(limb);
	}

	override float GetDeepWoundBleedingRateForLimb(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return 0;
			}

			return m_FeetDeepWoundBleedingRate;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return 0;
			}

			return m_HandsDeepWoundBleedingRate;
		}

		return super.GetDeepWoundBleedingRateForLimb(limb);
	}

	override void ActivateDeepWoundBandageForLimb(string limb, float effectiveDuration, float regenerationMultiplier = 1)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_ActivateDeepWoundBandageForFeet(effectiveDuration, regenerationMultiplier);
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_ActivateDeepWoundBandageForHands(effectiveDuration, regenerationMultiplier);
			return;
		}

		super.ActivateDeepWoundBandageForLimb(limb, effectiveDuration, regenerationMultiplier);
	}

	override void DeactivateDeepWoundBandageForLimb(string limb, bool spawnUsedRag = true)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_DeactivateDeepWoundBandageForFeet(spawnUsedRag);
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_DeactivateDeepWoundBandageForHands(spawnUsedRag);
			return;
		}

		super.DeactivateDeepWoundBandageForLimb(limb, spawnUsedRag);
	}

	override bool IsLimbDeepWoundBandaged(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return false;
			}

			return m_Player.OMD_Bridge_GetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BANDAGE);
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return false;
			}

			return m_Player.OMD_Bridge_GetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BANDAGE);
		}

		return super.IsLimbDeepWoundBandaged(limb);
	}

	override void SetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb(string limb, float effectiveDuration)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return;
			}

			if (effectiveDuration < 0)
			{
				effectiveDuration = 0;
			}

			m_FeetDeepWoundBandageItemEffectivenessTimeRemainingSeconds = effectiveDuration;
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return;
			}

			if (effectiveDuration < 0)
			{
				effectiveDuration = 0;
			}

			m_HandsDeepWoundBandageItemEffectivenessTimeRemainingSeconds = effectiveDuration;
			return;
		}

		super.SetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb(limb, effectiveDuration);
	}

	override float GetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return 0;
			}

			return m_FeetDeepWoundBandageItemEffectivenessTimeRemainingSeconds;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return 0;
			}

			return m_HandsDeepWoundBandageItemEffectivenessTimeRemainingSeconds;
		}

		return super.GetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb(limb);
	}

	override void SetDeepWoundBandageEffectivenessForLimb(string limb, bool isEffective)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return;
			}

			if (!isEffective && IsLimbDeepWoundBandageEffective(limb))
			{
				m_Player.InediaInfectedAI_PlaySoundServer(InediaInfectedAI_PlayerBaseSoundTypes.DEEP_WOUND);
			}

			m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BANDAGE_EFFECTIVE, isEffective);
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return;
			}

			if (!isEffective && IsLimbDeepWoundBandageEffective(limb))
			{
				m_Player.InediaInfectedAI_PlaySoundServer(InediaInfectedAI_PlayerBaseSoundTypes.DEEP_WOUND);
			}

			m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BANDAGE_EFFECTIVE, isEffective);
			return;
		}

		super.SetDeepWoundBandageEffectivenessForLimb(limb, isEffective);
	}

	override bool IsLimbDeepWoundBandageEffective(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return false;
			}

			return m_Player.OMD_Bridge_GetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BANDAGE_EFFECTIVE);
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return false;
			}

			return m_Player.OMD_Bridge_GetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BANDAGE_EFFECTIVE);
		}

		return super.IsLimbDeepWoundBandageEffective(limb);
	}

	override void SetDeepWoundBandageRegenerationMultiplierForLimb(string limb, float regenerationMultiplier = 1)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return;
			}

			if (regenerationMultiplier < 1)
			{
				regenerationMultiplier = 1;
			}

			m_FeetDeepWoundBandageItemRegenerationMultiplier = regenerationMultiplier;
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return;
			}

			if (regenerationMultiplier < 1)
			{
				regenerationMultiplier = 1;
			}

			m_HandsDeepWoundBandageItemRegenerationMultiplier = regenerationMultiplier;
			return;
		}

		super.SetDeepWoundBandageRegenerationMultiplierForLimb(limb, regenerationMultiplier);
	}

	override float GetDeepWoundBandageRegenerationMultiplierForLimb(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return 1;
			}

			return m_FeetDeepWoundBandageItemRegenerationMultiplier;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsDeepWoundSystemIsActive())
			{
				return 1;
			}

			return m_HandsDeepWoundBandageItemRegenerationMultiplier;
		}

		return super.GetDeepWoundBandageRegenerationMultiplierForLimb(limb);
	}

	override void SetBulletCountInLimb(string limb, int count, float notMoreFrequentlyThanSeconds = 0)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_SetBulletCountForFeet(count, notMoreFrequentlyThanSeconds);
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			OMD_Bridge_SetBulletCountForHands(count, notMoreFrequentlyThanSeconds);
			return;
		}

		super.SetBulletCountInLimb(limb, count, notMoreFrequentlyThanSeconds);
	}

	override int GetBulletCountInLimb(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			return OMD_Bridge_GetFeetBulletCount();
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBulletSystemIsActive())
			{
				return 0;
			}

			int bit1 = 0;
			int bit2 = 0;
			if (m_Player.OMD_Bridge_GetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BULLET_BIT1))
			{
				bit1 = 1;
			}
			if (m_Player.OMD_Bridge_GetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BULLET_BIT2))
			{
				bit2 = 1;
			}

			return ((bit1 << 1) | bit2);
		}

		return super.GetBulletCountInLimb(limb);
	}

	override void SetBulletInBodySecondsForLimb(string limb, float time)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBulletSystemIsActive())
			{
				return;
			}

			m_FeetBulletInBodySeconds = time;
			return;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBulletSystemIsActive())
			{
				return;
			}

			m_HandsBulletInBodySeconds = time;
			return;
		}

		super.SetBulletInBodySecondsForLimb(limb, time);
	}

	override float GetBulletInBodySecondsForLimb(string limb)
	{
		if (limb == "feet" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBulletSystemIsActive())
			{
				return 0;
			}

			return m_FeetBulletInBodySeconds;
		}

		if (limb == "hands" && OMD_BridgeConfig.IsActive())
		{
			if (!LimbsBulletSystemIsActive())
			{
				return 0;
			}

			return m_HandsBulletInBodySeconds;
		}

		return super.GetBulletInBodySecondsForLimb(limb);
	}

	override float GetDeepWoundsBleedingRateWithMultipliers()
	{
		float bloodLossRatePerSec = super.GetDeepWoundsBleedingRateWithMultipliers();

		if (!OMD_BridgeConfig.IsActive() || !LimbsDeepWoundSystemIsActive())
		{
			return bloodLossRatePerSec;
		}

		if (m_InediaPainLimbs.Find("hands") == -1)
		{
			bloodLossRatePerSec = bloodLossRatePerSec + OMD_Bridge_GetBridgeLimbDeepWoundBleed("hands");
		}

		if (m_InediaPainLimbs.Find("feet") == -1)
		{
			bloodLossRatePerSec = bloodLossRatePerSec + OMD_Bridge_GetBridgeLimbDeepWoundBleed("feet");
		}

		if (bloodLossRatePerSec > 0)
		{
			bloodLossRatePerSec = bloodLossRatePerSec * OMD_BridgeSkills.GetThickBloodBleedMultiplier(m_Player);
		}

		return bloodLossRatePerSec;
	}

	protected bool OMD_Bridge_ActivateBreakForHands(float notMoreFrequentlyThanSeconds, bool enableSound, bool spawnUsedItemIfStabilizationActive)
	{
		if (!m_Player.m_InediaInfectedAI_ConfigPlayers || !m_Player.GetAllowDamage())
		{
			return false;
		}

		if (!LimbsBreakSystemIsActive())
		{
			return false;
		}

		float fractureTimeRemainingSeconds = OMD_BridgeConfig.GetHandsBreakDurationSeconds();
		if (fractureTimeRemainingSeconds <= 0)
		{
			return false;
		}

		if (notMoreFrequentlyThanSeconds > 0 && (GetGame().GetTickTime() - m_BreakHandsLastActivateTime) <= notMoreFrequentlyThanSeconds)
		{
			return false;
		}

		m_BreakHandsLastActivateTime = GetGame().GetTickTime();
		m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BREAK, true);

		if (enableSound)
		{
			m_Player.InediaInfectedAI_PlaySoundServer(InediaInfectedAI_PlayerBaseSoundTypes.FRACTURE);
		}

		DeactivateBreakStabilizeForLimb("hands", spawnUsedItemIfStabilizationActive);
		SetBreakTimeRemainingSecondsForLimb("hands", fractureTimeRemainingSeconds);
		return true;
	}

	protected void OMD_Bridge_DeactivateBreakForHands(bool spawnUsedItemIfStabilizationActive)
	{
		if (!LimbsBreakSystemIsActive())
		{
			return;
		}

		m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BREAK, false);
		DeactivateBreakStabilizeForLimb("hands", spawnUsedItemIfStabilizationActive);
		SetBreakTimeRemainingSecondsForLimb("hands", 0);
	}

	protected void OMD_Bridge_ActivateBreakStabilizeForHands(float shockReductionMultiplier, float regenerationMultiplier)
	{
		if (!LimbsBreakSystemIsActive())
		{
			return;
		}

		if (IsLimbStabilized("hands"))
		{
			return;
		}

		m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_STABILIZE, true);
		SetBreakStabilizationRegenerationMultiplierForLimb("hands", regenerationMultiplier);
		SetBreakStabilizationShockReductionMultiplierForLimb("hands", shockReductionMultiplier);
	}

	protected void OMD_Bridge_DeactivateBreakStabilizeForHands(bool spawnUsedItem)
	{
		if (!LimbsBreakSystemIsActive())
		{
			return;
		}

		if (!IsLimbStabilized("hands"))
		{
			return;
		}

		m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_STABILIZE, false);

		if (spawnUsedItem)
		{
			ItemBase rag = ItemBase.Cast(m_Player.SpawnEntityOnGroundPos("Rag", m_Player.GetPosition() + 0.6 * m_Player.GetDirection()));
			if (rag)
			{
				rag.SetQuantity(1);
				rag.SetHealth("", "", rag.GetMaxHealth("", "") * GameConstants.DAMAGE_RUINED_VALUE);
			}
		}
	}

	protected bool OMD_Bridge_ActivateDeepWoundForHands(float bleedingRateMultiplier, int bleedingZoneIndex, float notMoreFrequentlyThanSeconds, bool enableSound, bool spawnUsedRagIfBandageActive)
	{
		if (!LimbsDeepWoundSystemIsActive() || m_Player.InediaInfectedAI_IsNPC() || !m_Player.GetAllowDamage())
		{
			return false;
		}

		if (bleedingRateMultiplier > 0)
		{
			float bloodRate = bleedingRateMultiplier * DEEP_WOUND_BLEEDING_RATE_HIT;
			if (IsLimbDeepWounded("hands"))
			{
				bloodRate = bloodRate + GetDeepWoundBleedingRateForLimb("hands");
			}

			SetDeepWoundBleedingRateForLimb("hands", Math.Clamp(bloodRate, DEEP_WOUND_BLEEDING_RATE_MIN, DEEP_WOUND_BLEEDING_RATE_MAX));
		}

		float deepWoundMaxDurationSeconds = GetDeepWoundMaxDurationSecondsForLimb("hands");
		if (deepWoundMaxDurationSeconds <= 0)
		{
			return false;
		}

		if (notMoreFrequentlyThanSeconds > 0 && (GetGame().GetTickTime() - m_HandsDeepWoundLastActivateTime) <= notMoreFrequentlyThanSeconds)
		{
			return false;
		}

		m_HandsDeepWoundLastActivateTime = GetGame().GetTickTime();
		m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_DEEP_WOUND, true);

		if (enableSound && (m_DeepWoundLastSoundPlay <= 0 || (GetGame().GetTickTime() - m_DeepWoundLastSoundPlay) > 5))
		{
			m_Player.InediaInfectedAI_PlaySoundServer(InediaInfectedAI_PlayerBaseSoundTypes.DEEP_WOUND);
			m_DeepWoundLastSoundPlay = GetGame().GetTickTime();
		}

		m_AllowDeepWoundPainDropBelowBadlySeconds["hands"] = 0;

		if (bleedingZoneIndex >= 0)
		{
			int bleedingBit = m_Player.GetBleedingManagerServer().InediaInfectedAI_GetBitFromSelectionID(bleedingZoneIndex);
			if (bleedingBit > 0)
			{
				m_Player.m_InediaInfectedAI_DeepWoundsBleedingsSyncBits = m_Player.m_InediaInfectedAI_DeepWoundsBleedingsSyncBits | bleedingBit;
			}
		}
		else if (bleedingZoneIndex == -1)
		{
			ActivateVisualBleedingForLimbServer("hands");
		}

		DeactivateDeepWoundBandageForLimb("hands", spawnUsedRagIfBandageActive);
		SetDeepWoundTimeRemainingSecondsForLimb("hands", deepWoundMaxDurationSeconds);
		return true;
	}

	protected void OMD_Bridge_DeactivateDeepWoundForHands(bool spawnUsedRagIfBandageActive)
	{
		if (!LimbsDeepWoundSystemIsActive())
		{
			return;
		}

		m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_DEEP_WOUND, false);
		DeactivateVisualBleedingForLimbServer("hands");
		DeactivateDeepWoundBandageForLimb("hands", spawnUsedRagIfBandageActive);
		SetDeepWoundTimeRemainingSecondsForLimb("hands", 0);
	}

	protected void OMD_Bridge_ActivateDeepWoundBandageForHands(float effectiveDuration, float regenerationMultiplier)
	{
		if (!LimbsDeepWoundSystemIsActive())
		{
			return;
		}

		m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BANDAGE, true);
		SetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb("hands", effectiveDuration);
		SetDeepWoundBandageEffectivenessForLimb("hands", true);
		SetDeepWoundBandageRegenerationMultiplierForLimb("hands", regenerationMultiplier);
	}

	protected void OMD_Bridge_DeactivateDeepWoundBandageForHands(bool spawnUsedRag)
	{
		if (!LimbsDeepWoundSystemIsActive())
		{
			return;
		}

		if (!IsLimbDeepWoundBandaged("hands"))
		{
			return;
		}

		if (spawnUsedRag)
		{
			ItemBase rag = ItemBase.Cast(m_Player.SpawnEntityOnGroundPos("Rag", m_Player.GetPosition() + 0.6 * m_Player.GetDirection()));
			if (rag)
			{
				rag.SetQuantity(1);
				rag.SetHealth("", "", rag.GetMaxHealth("", "") * GameConstants.DAMAGE_RUINED_VALUE);
			}
		}

		m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BANDAGE, false);
	}

	protected void OMD_Bridge_SetBulletCountForHands(int count, float notMoreFrequentlyThanSeconds)
	{
		if (!LimbsBulletSystemIsActive() || m_Player.InediaInfectedAI_IsNPC() || !m_Player.GetAllowDamage())
		{
			return;
		}

		if (notMoreFrequentlyThanSeconds > 0 && (GetGame().GetTickTime() - m_SetBulletLastTime) <= notMoreFrequentlyThanSeconds)
		{
			return;
		}

		m_SetBulletLastTime = GetGame().GetTickTime();
		count = Math.Clamp(count, 0, BULLET_COUNT_IN_LIMB_MAX);

		if (count == GetBulletCountInLimb("hands"))
		{
			return;
		}

		int bit1 = (count >> 1) & 1;
		int bit2 = count & 1;
		m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BULLET_BIT1, bit1 != 0);
		m_Player.OMD_Bridge_SetHandsStateBit(PlayerBase.OMD_BRIDGE_HANDS_BULLET_BIT2, bit2 != 0);
	}

	void OMD_Bridge_InitFeetLimbConfig()
	{
		m_InediaPainLimbMainBleedingZoneName["feet"] = "RightFoot";
		m_InediaPainLimbAllBleedingZonesNames["feet"] = {"LeftFoot", "RightFoot", "LeftToeBase", "RightToeBase"};
		m_InediaPainLimbsEquipSlots["feet"] = {"Feet"};
		m_AllowBreakPainDropBelowBadlySeconds["feet"] = 0;
		m_AllowDeepWoundPainDropBelowBadlySeconds["feet"] = 0;
		m_LimbsBreakRegenerationLevels["feet"] = 0;
		m_LimbsDeepWoundRegenerationLevels["feet"] = 0;
	}

	protected bool OMD_Bridge_ActivateBreakForFeet(float notMoreFrequentlyThanSeconds, bool enableSound, bool spawnUsedItemIfStabilizationActive)
	{
		if (!m_Player.m_InediaInfectedAI_ConfigPlayers || !m_Player.GetAllowDamage())
		{
			return false;
		}

		if (!LimbsBreakSystemIsActive())
		{
			return false;
		}

		float fractureTimeRemainingSeconds = OMD_BridgeConfig.GetFeetBreakDurationSeconds();
		if (fractureTimeRemainingSeconds <= 0)
		{
			return false;
		}

		if (notMoreFrequentlyThanSeconds > 0 && (GetGame().GetTickTime() - m_BreakFeetLastActivateTime) <= notMoreFrequentlyThanSeconds)
		{
			return false;
		}

		m_BreakFeetLastActivateTime = GetGame().GetTickTime();
		m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BREAK, true);

		if (enableSound)
		{
			m_Player.InediaInfectedAI_PlaySoundServer(InediaInfectedAI_PlayerBaseSoundTypes.FRACTURE);
		}

		DeactivateBreakStabilizeForLimb("feet", spawnUsedItemIfStabilizationActive);
		SetBreakTimeRemainingSecondsForLimb("feet", fractureTimeRemainingSeconds);
		return true;
	}

	protected void OMD_Bridge_DeactivateBreakForFeet(bool spawnUsedItemIfStabilizationActive)
	{
		if (!LimbsBreakSystemIsActive())
		{
			return;
		}

		m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BREAK, false);
		DeactivateBreakStabilizeForLimb("feet", spawnUsedItemIfStabilizationActive);
		SetBreakTimeRemainingSecondsForLimb("feet", 0);
	}

	protected void OMD_Bridge_ActivateBreakStabilizeForFeet(float shockReductionMultiplier, float regenerationMultiplier)
	{
		if (!LimbsBreakSystemIsActive())
		{
			return;
		}

		if (IsLimbStabilized("feet"))
		{
			return;
		}

		m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_STABILIZE, true);
		SetBreakStabilizationRegenerationMultiplierForLimb("feet", regenerationMultiplier);
		SetBreakStabilizationShockReductionMultiplierForLimb("feet", shockReductionMultiplier);
	}

	protected void OMD_Bridge_DeactivateBreakStabilizeForFeet(bool spawnUsedItem)
	{
		if (!LimbsBreakSystemIsActive())
		{
			return;
		}

		if (!IsLimbStabilized("feet"))
		{
			return;
		}

		m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_STABILIZE, false);

		if (spawnUsedItem)
		{
			ItemBase rag = ItemBase.Cast(m_Player.SpawnEntityOnGroundPos("Rag", m_Player.GetPosition() + 0.6 * m_Player.GetDirection()));
			if (rag)
			{
				rag.SetQuantity(1);
				rag.SetHealth("", "", rag.GetMaxHealth("", "") * GameConstants.DAMAGE_RUINED_VALUE);
			}
		}
	}

	protected bool OMD_Bridge_ActivateDeepWoundForFeet(float bleedingRateMultiplier, int bleedingZoneIndex, float notMoreFrequentlyThanSeconds, bool enableSound, bool spawnUsedRagIfBandageActive)
	{
		if (!LimbsDeepWoundSystemIsActive() || m_Player.InediaInfectedAI_IsNPC() || !m_Player.GetAllowDamage())
		{
			return false;
		}

		if (bleedingRateMultiplier > 0)
		{
			float bloodRate = bleedingRateMultiplier * DEEP_WOUND_BLEEDING_RATE_HIT;
			if (IsLimbDeepWounded("feet"))
			{
				bloodRate = bloodRate + GetDeepWoundBleedingRateForLimb("feet");
			}

			SetDeepWoundBleedingRateForLimb("feet", Math.Clamp(bloodRate, DEEP_WOUND_BLEEDING_RATE_MIN, DEEP_WOUND_BLEEDING_RATE_MAX));
		}

		float deepWoundMaxDurationSeconds = GetDeepWoundMaxDurationSecondsForLimb("feet");
		if (deepWoundMaxDurationSeconds <= 0)
		{
			return false;
		}

		if (notMoreFrequentlyThanSeconds > 0 && (GetGame().GetTickTime() - m_FeetDeepWoundLastActivateTime) <= notMoreFrequentlyThanSeconds)
		{
			return false;
		}

		m_FeetDeepWoundLastActivateTime = GetGame().GetTickTime();
		m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_DEEP_WOUND, true);

		if (enableSound && (m_DeepWoundLastSoundPlay <= 0 || (GetGame().GetTickTime() - m_DeepWoundLastSoundPlay) > 5))
		{
			m_Player.InediaInfectedAI_PlaySoundServer(InediaInfectedAI_PlayerBaseSoundTypes.DEEP_WOUND);
			m_DeepWoundLastSoundPlay = GetGame().GetTickTime();
		}

		m_AllowDeepWoundPainDropBelowBadlySeconds["feet"] = 0;

		if (bleedingZoneIndex >= 0)
		{
			int bleedingBit = m_Player.GetBleedingManagerServer().InediaInfectedAI_GetBitFromSelectionID(bleedingZoneIndex);
			if (bleedingBit > 0)
			{
				m_Player.m_InediaInfectedAI_DeepWoundsBleedingsSyncBits = m_Player.m_InediaInfectedAI_DeepWoundsBleedingsSyncBits | bleedingBit;
			}
		}
		else if (bleedingZoneIndex == -1)
		{
			ActivateVisualBleedingForLimbServer("feet");
		}

		DeactivateDeepWoundBandageForLimb("feet", spawnUsedRagIfBandageActive);
		SetDeepWoundTimeRemainingSecondsForLimb("feet", deepWoundMaxDurationSeconds);
		return true;
	}

	protected void OMD_Bridge_DeactivateDeepWoundForFeet(bool spawnUsedRagIfBandageActive)
	{
		if (!LimbsDeepWoundSystemIsActive())
		{
			return;
		}

		m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_DEEP_WOUND, false);
		DeactivateVisualBleedingForLimbServer("feet");
		DeactivateDeepWoundBandageForLimb("feet", spawnUsedRagIfBandageActive);
		SetDeepWoundTimeRemainingSecondsForLimb("feet", 0);
	}

	protected void OMD_Bridge_ActivateDeepWoundBandageForFeet(float effectiveDuration, float regenerationMultiplier)
	{
		if (!LimbsDeepWoundSystemIsActive())
		{
			return;
		}

		m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BANDAGE, true);
		SetDeepWoundBandageEffectivenessTimeRemainingSecondsForLimb("feet", effectiveDuration);
		SetDeepWoundBandageEffectivenessForLimb("feet", true);
		SetDeepWoundBandageRegenerationMultiplierForLimb("feet", regenerationMultiplier);
	}

	protected void OMD_Bridge_DeactivateDeepWoundBandageForFeet(bool spawnUsedRag)
	{
		if (!LimbsDeepWoundSystemIsActive())
		{
			return;
		}

		if (!IsLimbDeepWoundBandaged("feet"))
		{
			return;
		}

		if (spawnUsedRag)
		{
			ItemBase rag = ItemBase.Cast(m_Player.SpawnEntityOnGroundPos("Rag", m_Player.GetPosition() + 0.6 * m_Player.GetDirection()));
			if (rag)
			{
				rag.SetQuantity(1);
				rag.SetHealth("", "", rag.GetMaxHealth("", "") * GameConstants.DAMAGE_RUINED_VALUE);
			}
		}

		m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BANDAGE, false);
	}

	protected void OMD_Bridge_SetBulletCountForFeet(int count, float notMoreFrequentlyThanSeconds)
	{
		if (!LimbsBulletSystemIsActive() || m_Player.InediaInfectedAI_IsNPC() || !m_Player.GetAllowDamage())
		{
			return;
		}

		if (notMoreFrequentlyThanSeconds > 0 && (GetGame().GetTickTime() - m_SetBulletLastTime) <= notMoreFrequentlyThanSeconds)
		{
			return;
		}

		m_SetBulletLastTime = GetGame().GetTickTime();
		count = Math.Clamp(count, 0, BULLET_COUNT_IN_LIMB_MAX);

		if (count == GetBulletCountInLimb("feet"))
		{
			return;
		}

		int bit1 = (count >> 1) & 1;
		int bit2 = count & 1;
		m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BULLET_BIT1, bit1 != 0);
		m_Player.OMD_Bridge_SetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BULLET_BIT2, bit2 != 0);
	}

	int OMD_Bridge_GetFeetBulletCount()
	{
		if (!LimbsBulletSystemIsActive())
		{
			return 0;
		}

		int bit1 = 0;
		int bit2 = 0;
		if (m_Player.OMD_Bridge_GetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BULLET_BIT1))
		{
			bit1 = 1;
		}
		if (m_Player.OMD_Bridge_GetFeetStateBit(PlayerBase.OMD_BRIDGE_FEET_BULLET_BIT2))
		{
			bit2 = 1;
		}

		return ((bit1 << 1) | bit2);
	}
};
