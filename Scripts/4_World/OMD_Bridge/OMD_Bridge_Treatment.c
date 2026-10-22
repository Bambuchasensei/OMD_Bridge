class OMD_BridgeTreatment
{
	static const string HEAL_SCRATCH = "scratch";
	static const string HEAL_BANDAGE = "bandage";
	static const string HEAL_SURGERY = "surgery";
	static const string HEAL_SPLINT = "splint";

	static ref array<string> s_Limbs;

	static array<string> GetLimbs()
	{
		if (!s_Limbs)
		{
			s_Limbs = new array<string>;
			s_Limbs.Insert("torso");
			s_Limbs.Insert("head");
			s_Limbs.Insert("arms");
			s_Limbs.Insert("hands");
			s_Limbs.Insert("legs");
			s_Limbs.Insert("feet");
		}

		return s_Limbs;
	}

	static int GetLimbTieBreakIndex(string limb)
	{
		array<string> limbs = GetLimbs();
		int i;
		for (i = 0; i < limbs.Count(); i++)
		{
			if (limbs.Get(i) == limb)
			{
				return i;
			}
		}

		return 999;
	}

	static InediaInfectedAI_PainManager GetPainManager(PlayerBase player)
	{
		if (!player)
		{
			return null;
		}

		return player.InediaInfectedAI_GetPainManager();
	}

	static bool TryFindTreatmentEntryForItem(ItemBase item, out OMD_BridgeTreatmentEntry entry)
	{
		entry = null;
		if (!item)
		{
			return false;
		}

		if (OMD_BridgeConfig.TryGetTreatmentEntry(item.GetType(), entry))
		{
			return true;
		}

		OMD_BridgeConfigData data = OMD_BridgeConfig.Get();
		if (!data || !data.treatments)
		{
			return false;
		}

		int i;
		OMD_BridgeTreatmentEntry candidate;
		for (i = 0; i < data.treatments.Count(); i++)
		{
			candidate = data.treatments.Get(i);
			if (!candidate)
			{
				continue;
			}

			if (candidate.className == "")
			{
				continue;
			}

			if (!item.IsKindOf(candidate.className))
			{
				continue;
			}

			entry = candidate;
			return true;
		}

		return false;
	}

	static string GetHealTypeForItem(ItemBase item)
	{
		OMD_BridgeTreatmentEntry entry;
		if (TryFindTreatmentEntryForItem(item, entry))
		{
			if (entry && entry.healType != "")
			{
				return entry.healType;
			}
		}

		if (item && item.IsKindOf("TerjePlaster"))
		{
			return HEAL_SCRATCH;
		}

		if (item && item.IsKindOf("BandageDressing"))
		{
			return HEAL_BANDAGE;
		}

		if (item && item.IsKindOf("Rag"))
		{
			return HEAL_BANDAGE;
		}

		if (item && item.IsKindOf("Bandana_ColorBase"))
		{
			return HEAL_BANDAGE;
		}

		if (item && item.IsKindOf("Splint"))
		{
			return HEAL_SPLINT;
		}

		if (item && item.IsKindOf("TerjeSurgicalKit"))
		{
			return HEAL_SURGERY;
		}

		if (item && item.IsKindOf("TerjeSurgicalTool_ColorBase"))
		{
			return HEAL_SURGERY;
		}

		return "";
	}

	static bool ItemAllowsScratch(ItemBase item)
	{
		string healType = GetHealTypeForItem(item);
		if (healType == HEAL_SCRATCH)
		{
			return true;
		}

		if (healType == HEAL_BANDAGE)
		{
			return true;
		}

		return false;
	}

	static bool ItemAllowsDeepWoundBandage(ItemBase item)
	{
		string healType = GetHealTypeForItem(item);
		if (healType == HEAL_BANDAGE)
		{
			return true;
		}

		return false;
	}

	static bool HasOpenDeepWound(PlayerBase player, string limb)
	{
		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return false;
		}

		if (!painManager.IsLimbDeepWounded(limb))
		{
			return false;
		}

		if (painManager.IsLimbDeepWoundBandaged(limb))
		{
			return false;
		}

		return true;
	}

	static bool HasScratch(PlayerBase player, string limb)
	{
		if (!player)
		{
			return false;
		}

		if (player.OMD_Bridge_CountLimbScratches(limb) > 0)
		{
			return true;
		}

		return false;
	}

	static bool HasOperableBullet(PlayerBase player, string limb)
	{
		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return false;
		}

		if (painManager.GetBulletCountInLimb(limb) <= 0)
		{
			return false;
		}

		if (painManager.IsLimbDeepWounded(limb) && painManager.IsLimbDeepWoundBandaged(limb))
		{
			return false;
		}

		return true;
	}

	static bool HasUnstabilizedBreak(PlayerBase player, string limb)
	{
		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return false;
		}

		if (!painManager.IsLimbBroken(limb))
		{
			return false;
		}

		if (painManager.IsLimbStabilized(limb))
		{
			return false;
		}

		return true;
	}

	static bool HasClosableDeepWound(PlayerBase player, string limb)
	{
		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return false;
		}

		if (!painManager.IsLimbDeepWounded(limb))
		{
			return false;
		}

		if (painManager.IsLimbDeepWoundBandaged(limb))
		{
			return false;
		}

		return true;
	}

	static bool HasUnbandagedSuture(PlayerBase player, string limb)
	{
		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return false;
		}

		if (!OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			return false;
		}

		return painManager.OMD_Bridge_IsSutureUnbandaged(limb);
	}

	static bool HasDirtySutureBandage(PlayerBase player, string limb)
	{
		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return false;
		}

		if (!OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			return false;
		}

		if (!painManager.OMD_Bridge_IsLimbSutured(limb))
		{
			return false;
		}

		return painManager.OMD_Bridge_IsSutureBandageDirty(limb);
	}

	static bool IsSutureDisinfectantItem(ItemBase item)
	{
		if (!item)
		{
			return false;
		}

		array<string> classes = OMD_BridgeConfig.GetSutureDisinfectantClasses();
		if (!classes)
		{
			return false;
		}

		int i;
		string className;
		for (i = 0; i < classes.Count(); i++)
		{
			className = classes.Get(i);
			if (className == "")
			{
				continue;
			}

			if (item.IsKindOf(className))
			{
				return true;
			}
		}

		return false;
	}

	static string PickBestLimbByPain(PlayerBase player, array<string> candidates)
	{
		if (!candidates || candidates.Count() == 0)
		{
			return "";
		}

		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		string bestLimb = candidates.Get(0);
		float bestPain = 0;
		int bestTie = GetLimbTieBreakIndex(bestLimb);
		if (painManager)
		{
			bestPain = painManager.GetPainPercentForLimb(bestLimb);
		}

		int i;
		string limb;
		float pain;
		int tie;
		for (i = 1; i < candidates.Count(); i++)
		{
			limb = candidates.Get(i);
			pain = 0;
			if (painManager)
			{
				pain = painManager.GetPainPercentForLimb(limb);
			}

			tie = GetLimbTieBreakIndex(limb);
			if (pain > bestPain)
			{
				bestPain = pain;
				bestLimb = limb;
				bestTie = tie;
			}
			else if (pain == bestPain && tie < bestTie)
			{
				bestLimb = limb;
				bestTie = tie;
			}
		}

		return bestLimb;
	}

	static string SelectLimbForPredicate(PlayerBase player, bool checkOpenDeepWound, bool checkScratch, bool checkBullet, bool checkBreak, bool checkClosableDeepWound)
	{
		array<string> limbs = GetLimbs();
		array<string> candidates = new array<string>;
		int i;
		string limb;

		if (checkOpenDeepWound)
		{
			for (i = 0; i < limbs.Count(); i++)
			{
				limb = limbs.Get(i);
				if (HasOpenDeepWound(player, limb))
				{
					candidates.Insert(limb);
				}
			}

			if (candidates.Count() > 0)
			{
				return PickBestLimbByPain(player, candidates);
			}
		}

		if (checkClosableDeepWound)
		{
			candidates.Clear();
			for (i = 0; i < limbs.Count(); i++)
			{
				limb = limbs.Get(i);
				if (HasClosableDeepWound(player, limb))
				{
					candidates.Insert(limb);
				}
			}

			if (candidates.Count() > 0)
			{
				return PickBestLimbByPain(player, candidates);
			}
		}

		if (checkBullet)
		{
			candidates.Clear();
			for (i = 0; i < limbs.Count(); i++)
			{
				limb = limbs.Get(i);
				if (HasOperableBullet(player, limb))
				{
					candidates.Insert(limb);
				}
			}

			if (candidates.Count() > 0)
			{
				return PickBestLimbByPain(player, candidates);
			}
		}

		if (checkBreak)
		{
			candidates.Clear();
			for (i = 0; i < limbs.Count(); i++)
			{
				limb = limbs.Get(i);
				if (HasUnstabilizedBreak(player, limb))
				{
					candidates.Insert(limb);
				}
			}

			if (candidates.Count() > 0)
			{
				return PickBestLimbByPain(player, candidates);
			}
		}

		if (checkScratch)
		{
			candidates.Clear();
			for (i = 0; i < limbs.Count(); i++)
			{
				limb = limbs.Get(i);
				if (HasScratch(player, limb))
				{
					candidates.Insert(limb);
				}
			}

			if (candidates.Count() > 0)
			{
				return PickBestLimbByPain(player, candidates);
			}
		}

		return "";
	}

	static string SelectLimbForBandageItem(PlayerBase player, ItemBase item)
	{
		bool allowDeep = ItemAllowsDeepWoundBandage(item);
		bool allowScratch = ItemAllowsScratch(item);
		bool allowSuture = ItemAllowsDeepWoundBandage(item) && OMD_BridgeConfig.IsSutureBandageEnabled();

		if (!allowDeep && !allowScratch && !allowSuture)
		{
			return "";
		}

		if (allowDeep)
		{
			string deepLimb = SelectLimbForPredicate(player, true, false, false, false, false);
			if (deepLimb != "")
			{
				return deepLimb;
			}
		}

		if (allowSuture)
		{
			string unbandagedSutureLimb = SelectLimbForSutureBandage(player, true, false);
			if (unbandagedSutureLimb != "")
			{
				return unbandagedSutureLimb;
			}

			string dirtySutureLimb = SelectLimbForSutureBandage(player, false, true);
			if (dirtySutureLimb != "")
			{
				return dirtySutureLimb;
			}
		}

		if (allowScratch)
		{
			return SelectLimbForPredicate(player, false, true, false, false, false);
		}

		return "";
	}

	static string SelectLimbForSutureBandage(PlayerBase player, bool checkUnbandaged, bool checkDirty)
	{
		array<string> limbs = GetLimbs();
		array<string> candidates = new array<string>;
		int i;
		string limb;

		for (i = 0; i < limbs.Count(); i++)
		{
			limb = limbs.Get(i);
			if (checkUnbandaged && HasUnbandagedSuture(player, limb))
			{
				candidates.Insert(limb);
			}
			else if (checkDirty && HasDirtySutureBandage(player, limb))
			{
				candidates.Insert(limb);
			}
		}

		if (candidates.Count() > 0)
		{
			return PickBestLimbByPain(player, candidates);
		}

		return "";
	}

	static string SelectLimbForSutureDisinfect(PlayerBase player)
	{
		return SelectLimbForSutureBandage(player, false, true);
	}

	static string SelectLimbForSurgeryBullet(PlayerBase player)
	{
		return SelectLimbForPredicate(player, false, false, true, false, false);
	}

	static string SelectLimbForSurgeryStub(PlayerBase player)
	{
		return SelectLimbForPredicate(player, false, false, false, false, true);
	}

	static string SelectLimbForSplint(PlayerBase player)
	{
		return SelectLimbForPredicate(player, false, false, false, true, false);
	}

	static bool IsManualTreatmentSelection()
	{
		return OMD_BridgeConfig.IsManualTreatmentSelection();
	}

	static int GetSeverityTier(PlayerBase player, string limb)
	{
		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return 0;
		}

		return painManager.OMD_Bridge_GetDeepWoundSeverityTierForLimb(limb);
	}

	static bool CanDeepWoundBandageOnLimb(PlayerBase player, string limb, int requiredTier)
	{
		if (!HasOpenDeepWound(player, limb))
		{
			return false;
		}

		if (GetSeverityTier(player, limb) != requiredTier)
		{
			return false;
		}

		return true;
	}

	static bool CanScratchBandageOnLimb(PlayerBase player, string limb)
	{
		return HasScratch(player, limb);
	}

	static bool CanSutureBandageOnLimb(PlayerBase player, string limb)
	{
		return HasUnbandagedSuture(player, limb);
	}

	static bool CanDirtySutureBandageOnLimb(PlayerBase player, string limb)
	{
		return HasDirtySutureBandage(player, limb);
	}

	static bool CanExtractBulletOnLimb(PlayerBase player, string limb)
	{
		return HasOperableBullet(player, limb);
	}

	static bool CanSplintOnLimb(PlayerBase player, string limb)
	{
		return HasUnstabilizedBreak(player, limb);
	}

	static bool CanDisinfectSutureOnLimb(PlayerBase player, string limb)
	{
		return HasDirtySutureBandage(player, limb);
	}

	static bool CanClosureOnLimb(PlayerBase player, string limb)
	{
		return HasClosableDeepWound(player, limb);
	}

	static bool IsKnownTreatmentLimb(string limb)
	{
		array<string> limbs = GetLimbs();
		int i;
		for (i = 0; i < limbs.Count(); i++)
		{
			if (limbs.Get(i) == limb)
			{
				return true;
			}
		}

		return false;
	}

	static bool HasUncoveredBandageCase(PlayerBase player, ItemBase item)
	{
		string limb = SelectLimbForBandageItem(player, item);
		if (limb == "")
		{
			return false;
		}

		if (IsKnownTreatmentLimb(limb))
		{
			return false;
		}

		return true;
	}

	static bool HasUncoveredSurgeryBulletCase(PlayerBase player)
	{
		string limb = SelectLimbForSurgeryBullet(player);
		if (limb == "")
		{
			return false;
		}

		if (IsKnownTreatmentLimb(limb))
		{
			return false;
		}

		return true;
	}

	static bool HasUncoveredSurgeryStubCase(PlayerBase player)
	{
		string limb = SelectLimbForSurgeryStub(player);
		if (limb == "")
		{
			return false;
		}

		if (IsKnownTreatmentLimb(limb))
		{
			return false;
		}

		return true;
	}

	static bool HasUncoveredSplintCase(PlayerBase player)
	{
		string limb = SelectLimbForSplint(player);
		if (limb == "")
		{
			return false;
		}

		if (IsKnownTreatmentLimb(limb))
		{
			return false;
		}

		return true;
	}

	static bool HasUncoveredDisinfectCase(PlayerBase player)
	{
		string limb = SelectLimbForSutureDisinfect(player);
		if (limb == "")
		{
			return false;
		}

		if (IsKnownTreatmentLimb(limb))
		{
			return false;
		}

		return true;
	}

	static bool ShouldShowTerjeAutoBandage(PlayerBase player, ItemBase item)
	{
		if (!CanApplyBandage(player, item))
		{
			return false;
		}

		if (!IsManualTreatmentSelection())
		{
			return true;
		}

		return HasUncoveredBandageCase(player, item);
	}

	static bool ShouldShowTerjeAutoSurgeryBullet(PlayerBase player)
	{
		if (!CanApplySurgeryBullet(player))
		{
			return false;
		}

		if (!IsManualTreatmentSelection())
		{
			return true;
		}

		return HasUncoveredSurgeryBulletCase(player);
	}

	static bool ShouldShowTerjeAutoSurgeryStub(PlayerBase player)
	{
		if (!CanApplySurgeryStub(player))
		{
			return false;
		}

		if (!IsManualTreatmentSelection())
		{
			return true;
		}

		return HasUncoveredSurgeryStubCase(player);
	}

	static bool ShouldShowTerjeAutoSplint(PlayerBase player)
	{
		if (!CanApplySplint(player))
		{
			return false;
		}

		if (!IsManualTreatmentSelection())
		{
			return true;
		}

		return HasUncoveredSplintCase(player);
	}

	static bool ShouldShowTerjeAutoDisinfect(PlayerBase player)
	{
		if (!CanDisinfectSutureBandage(player))
		{
			return false;
		}

		if (!IsManualTreatmentSelection())
		{
			return true;
		}

		return HasUncoveredDisinfectCase(player);
	}

	static bool CanApplyBandage(PlayerBase player, ItemBase item)
	{
		if (SelectLimbForBandageItem(player, item) != "")
		{
			return true;
		}

		return false;
	}

	static bool CanApplySurgeryBullet(PlayerBase player)
	{
		if (SelectLimbForSurgeryBullet(player) != "")
		{
			return true;
		}

		return false;
	}

	static bool CanApplySurgeryStub(PlayerBase player)
	{
		if (SelectLimbForSurgeryStub(player) != "")
		{
			return true;
		}

		return false;
	}

	static bool CanApplySplint(PlayerBase player)
	{
		if (SelectLimbForSplint(player) != "")
		{
			return true;
		}

		return false;
	}

	static void GetBandageParams(ItemBase item, out float effectiveDuration, out float regenerationMultiplier)
	{
		effectiveDuration = 600;
		regenerationMultiplier = 1.5;

		if (!item)
		{
			return;
		}

		float configDuration = GetGame().ConfigGetFloat("CfgVehicles " + item.GetType() + " InediaPain DeepWoundBandageItemEffectiveDurationSeconds");
		float configRegen = GetGame().ConfigGetFloat("CfgVehicles " + item.GetType() + " InediaPain DeepWoundBandageItemRegenerationMultiplier");
		if (configDuration > 0)
		{
			effectiveDuration = configDuration;
		}

		if (configRegen >= 1)
		{
			regenerationMultiplier = configRegen;
		}

		OMD_BridgeTreatmentEntry entry;
		if (!TryFindTreatmentEntryForItem(item, entry))
		{
			return;
		}

		if (!entry)
		{
			return;
		}

		if (configDuration <= 0 && entry.bandageEffectiveDurationSeconds > 0)
		{
			effectiveDuration = entry.bandageEffectiveDurationSeconds;
		}

		if (configRegen < 1 && entry.bandageRegenerationMultiplier >= 1)
		{
			regenerationMultiplier = entry.bandageRegenerationMultiplier;
		}
	}

	static void GetSplintParams(ItemBase item, out float shockReductionMultiplier, out float regenerationMultiplier)
	{
		shockReductionMultiplier = 1.5;
		regenerationMultiplier = 1.5;

		if (!item)
		{
			return;
		}

		float configShock = GetGame().ConfigGetFloat("CfgVehicles " + item.GetType() + " InediaPain FractureStabilizationItemShockReductionMultiplier");
		float configRegen = GetGame().ConfigGetFloat("CfgVehicles " + item.GetType() + " InediaPain FractureStabilizationItemRegenerationMultiplier");
		if (configShock >= 1)
		{
			shockReductionMultiplier = configShock;
		}

		if (configRegen >= 1)
		{
			regenerationMultiplier = configRegen;
		}

		OMD_BridgeTreatmentEntry entry;
		if (!TryFindTreatmentEntryForItem(item, entry))
		{
			return;
		}

		if (!entry)
		{
			return;
		}

		if (configShock < 1 && entry.splintShockReductionMultiplier >= 1)
		{
			shockReductionMultiplier = entry.splintShockReductionMultiplier;
		}

		if (configRegen < 1 && entry.splintRegenerationMultiplier >= 1)
		{
			regenerationMultiplier = entry.splintRegenerationMultiplier;
		}
	}

	static void ConsumeBandageItem(ItemBase item)
	{
		if (!item)
		{
			return;
		}

		if (item.HasQuantity())
		{
			item.AddQuantity(-1, true);
		}
		else
		{
			item.Delete();
		}
	}

	static void ConsumeSurgeryItem(ItemBase item)
	{
		if (!item)
		{
			return;
		}

		if (item.HasQuantity())
		{
			float consumeQuantity = 0;
			if (GetTerjeGameConfig())
			{
				consumeQuantity = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + item.GetType() + " terjeOverrideSurgeryConsumeQuantity");
			}

			if (consumeQuantity > 0)
			{
				item.AddQuantity(-consumeQuantity, true);
			}
			else
			{
				item.AddQuantity(-1, true);
			}
		}
		else
		{
			item.Delete();
		}
	}

	static void ConsumeSplintItem(ItemBase item, PlayerBase target, string limb)
	{
		if (!item)
		{
			return;
		}

		if (limb == "legs")
		{
			item.Delete();
			return;
		}

		if (item.HasQuantity())
		{
			item.AddQuantity(-1, true);
		}
		else
		{
			item.Delete();
		}
	}

	static void AddMedicineBandageExp(PlayerBase operator)
	{
		OMD_BridgeSkills.AddMedicineExperience(operator, OMD_BridgeConfig.GetXpBandage());
	}

	static void AddMedicineBulletSurgeryExp(PlayerBase operator)
	{
		OMD_BridgeSkills.AddMedicineExperience(operator, OMD_BridgeConfig.GetXpSurgeryBullet());
	}

	static void AddMedicineStubSurgeryExp(PlayerBase operator)
	{
		OMD_BridgeSkills.AddMedicineExperience(operator, OMD_BridgeConfig.GetXpSurgeryWound());
	}

	static void AddMedicineSplintExp(PlayerBase operator)
	{
		OMD_BridgeSkills.AddMedicineExperience(operator, OMD_BridgeConfig.GetXpSplint());
	}

	static bool TryApplyBandage(ItemBase item, PlayerBase player)
	{
		if (!GetGame().IsServer())
		{
			return false;
		}

		if (!item || !player)
		{
			return false;
		}

		string limb = SelectLimbForBandageItem(player, item);
		if (limb == "")
		{
			return false;
		}

		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return false;
		}

		if (HasOpenDeepWound(player, limb) && ItemAllowsDeepWoundBandage(item))
		{
			float effectiveDuration;
			float regenerationMultiplier;
			GetBandageParams(item, effectiveDuration, regenerationMultiplier);
			if (regenerationMultiplier < 1)
			{
				regenerationMultiplier = 1;
			}

			painManager.ActivateDeepWoundBandageForLimb(limb, effectiveDuration, regenerationMultiplier);
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] bandage deep wound limb=" + limb + " item=" + item.GetType() + " duration=" + effectiveDuration.ToString());
			}

			return true;
		}

		if (ItemAllowsDeepWoundBandage(item) && OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			if (HasUnbandagedSuture(player, limb) || HasDirtySutureBandage(player, limb))
			{
				bool usedRag = false;
				if (item.IsKindOf("Rag"))
				{
					usedRag = true;
				}

				painManager.OMD_Bridge_ActivateSutureBandageForLimb(limb, usedRag);
				return true;
			}
		}

		if (HasScratch(player, limb) && ItemAllowsScratch(item))
		{
			player.OMD_Bridge_RemoveAllLimbScratches(limb);
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] bandage scratch limb=" + limb + " item=" + item.GetType());
			}

			return true;
		}

		return false;
	}

	static bool TryApplyDeepWoundBandageOnLimb(ItemBase item, PlayerBase player, string limb)
	{
		if (!GetGame().IsServer())
		{
			return false;
		}

		if (!item || !player)
		{
			return false;
		}

		if (limb == "")
		{
			return false;
		}

		if (!ItemAllowsDeepWoundBandage(item))
		{
			return false;
		}

		if (!HasOpenDeepWound(player, limb))
		{
			return false;
		}

		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return false;
		}

		float effectiveDuration;
		float regenerationMultiplier;
		GetBandageParams(item, effectiveDuration, regenerationMultiplier);
		if (regenerationMultiplier < 1)
		{
			regenerationMultiplier = 1;
		}

		painManager.ActivateDeepWoundBandageForLimb(limb, effectiveDuration, regenerationMultiplier);
		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] bandage deep wound limb=" + limb + " item=" + item.GetType() + " duration=" + effectiveDuration.ToString());
		}

		return true;
	}

	static bool TryApplyScratchOnLimb(ItemBase item, PlayerBase player, string limb)
	{
		if (!GetGame().IsServer())
		{
			return false;
		}

		if (!item || !player)
		{
			return false;
		}

		if (limb == "")
		{
			return false;
		}

		if (!ItemAllowsScratch(item))
		{
			return false;
		}

		if (!HasScratch(player, limb))
		{
			return false;
		}

		player.OMD_Bridge_RemoveAllLimbScratches(limb);
		if (player.OMD_Bridge_CountBleedingZonesForLimb(limb) > 0)
		{
			return false;
		}

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] bandage all scratches limb=" + limb + " item=" + item.GetType());
		}

		return true;
	}

	static bool TryApplySutureBandageOnLimb(ItemBase item, PlayerBase player, string limb)
	{
		if (!GetGame().IsServer())
		{
			return false;
		}

		if (!item || !player)
		{
			return false;
		}

		if (limb == "")
		{
			return false;
		}

		if (!ItemAllowsDeepWoundBandage(item))
		{
			return false;
		}

		if (!OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			return false;
		}

		if (!HasUnbandagedSuture(player, limb) && !HasDirtySutureBandage(player, limb))
		{
			return false;
		}

		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return false;
		}

		bool usedRag = false;
		if (item.IsKindOf("Rag"))
		{
			usedRag = true;
		}

		painManager.OMD_Bridge_ActivateSutureBandageForLimb(limb, usedRag);
		return true;
	}

	static bool TryApplySutureUnbandagedOnLimb(ItemBase item, PlayerBase player, string limb)
	{
		if (!HasUnbandagedSuture(player, limb))
		{
			return false;
		}

		return TryApplySutureBandageOnLimb(item, player, limb);
	}

	static bool TryApplySutureDirtyOnLimb(ItemBase item, PlayerBase player, string limb)
	{
		if (!HasDirtySutureBandage(player, limb))
		{
			return false;
		}

		return TryApplySutureBandageOnLimb(item, player, limb);
	}

	static bool TryDisinfectSutureBandageOnLimb(ItemBase item, PlayerBase player, string limb)
	{
		if (!GetGame().IsServer())
		{
			return false;
		}

		if (!item || !player)
		{
			return false;
		}

		if (limb == "")
		{
			return false;
		}

		if (!OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			return false;
		}

		if (!IsSutureDisinfectantItem(item))
		{
			return false;
		}

		if (!HasDirtySutureBandage(player, limb))
		{
			return false;
		}

		InediaInfectedAI_PainManager painManager = GetPainManager(player);
		if (!painManager)
		{
			return false;
		}

		painManager.OMD_Bridge_DisinfectSutureBandageForLimb(limb);
		return true;
	}

	static bool TryDisinfectSutureBandage(ItemBase item, PlayerBase player)
	{
		if (!GetGame().IsServer())
		{
			return false;
		}

		if (!item || !player)
		{
			return false;
		}

		if (!OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			return false;
		}

		if (!IsSutureDisinfectantItem(item))
		{
			return false;
		}

		string limb = SelectLimbForSutureDisinfect(player);
		if (limb == "")
		{
			return false;
		}

		return TryDisinfectSutureBandageOnLimb(item, player, limb);
	}

	static bool CanDisinfectSutureBandage(PlayerBase player)
	{
		if (SelectLimbForSutureDisinfect(player) != "")
		{
			return true;
		}

		return false;
	}

	static bool TryApplySurgeryBullet(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (!GetGame().IsServer())
		{
			return false;
		}

		if (!item || !target)
		{
			return false;
		}

		string limb = SelectLimbForSurgeryBullet(target);
		if (limb == "")
		{
			return false;
		}

		InediaInfectedAI_PainManager painManager = GetPainManager(target);
		if (!painManager)
		{
			return false;
		}

		if (!HasOperableBullet(target, limb))
		{
			return false;
		}

		if (painManager.LimbsDeepWoundSystemIsActive())
		{
			painManager.ActivateDeepWoundForLimb(limb, 0.2);
		}

		bool success = false;
		if (Math.RandomFloat01() < item.GetTerjeSurgeryBulletEffectivity(operator))
		{
			int bulletCount = painManager.GetBulletCountInLimb(limb);
			if (bulletCount > 0)
			{
				painManager.SetBulletCountInLimb(limb, bulletCount - 1);
				success = true;
				if (OMD_BridgeConfig.IsDebugEnabled())
				{
					Print("[OMD_Bridge] surgery bullet removed limb=" + limb + " left=" + (bulletCount - 1).ToString());
				}
			}

			if (success && operator && operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 8, "#STR_TERJEMED_SURGERY_SUCCESS", "#STR_TERJEMED_SURGERY_BULLET_SUCCESS", "set:TerjePerk_icon image:tp_surgerybullet");
			}

			if (success)
			{
				AddMedicineBulletSurgeryExp(operator);
			}
		}
		else
		{
			if (target.GetSymptomManager())
			{
				target.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
			}

			if (target.GetTerjeHealth())
			{
				target.GetTerjeHealth().DecreaseHealth(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FAILED_HEALTH_LOSE), TerjeDamageSource.SURGERY_BULLETS);
				target.GetTerjeHealth().DecreaseBlood(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FAILED_BLOOD_LOSE), TerjeDamageSource.SURGERY_BULLETS);
				target.GetTerjeHealth().DecreaseShock(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FAILED_SHOCK_LOSE), TerjeDamageSource.SURGERY_BULLETS);
			}

			if (operator && operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 10, "#STR_TERJEMED_SURGERY_FAILED", "#STR_TERJEMED_SURGERY_BULLET_FAILED", "set:TerjePerkBlack_icon image:tp_surgerybullet");
			}
		}

		return true;
	}

	static bool TryApplySurgeryStub(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (!GetGame().IsServer())
		{
			return false;
		}

		if (!item || !target)
		{
			return false;
		}

		string limb = SelectLimbForSurgeryStub(target);
		if (limb == "")
		{
			return false;
		}

		if (!HasClosableDeepWound(target, limb))
		{
			return false;
		}

		bool success = false;
		if (Math.RandomFloat01() < item.GetTerjeSurgeryStubEffectivity(operator))
		{
			InediaInfectedAI_PainManager painManager = GetPainManager(target);
			if (painManager)
			{
				int woundTier = painManager.OMD_Bridge_GetDeepWoundSeverityTierForLimb(limb);
				painManager.DeactivateDeepWoundForLimb(limb, false);
				painManager.OMD_Bridge_ActivateSutureForLimb(limb, woundTier);
				success = true;
				if (OMD_BridgeConfig.IsDebugEnabled())
				{
					Print("[OMD_Bridge] surgery stub closed deep wound limb=" + limb);
				}
			}

			if (success && operator && operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 8, "#STR_TERJEMED_SURGERY_SUCCESS", "#STR_TERJEMED_SURGERY_WOUND_SUCCESS", "set:TerjePerk_icon image:tp_surgerystab");
			}

			if (success)
			{
				AddMedicineStubSurgeryExp(operator);
			}
		}
		else
		{
			if (target.GetSymptomManager())
			{
				target.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
			}

			if (target.GetTerjeHealth())
			{
				target.GetTerjeHealth().DecreaseHealth(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_FAILED_HEALTH_LOSE), TerjeDamageSource.SURGERY_STUBS);
				target.GetTerjeHealth().DecreaseBlood(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_FAILED_BLOOD_LOSE), TerjeDamageSource.SURGERY_STUBS);
				target.GetTerjeHealth().DecreaseShock(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_FAILED_SHOCK_LOSE), TerjeDamageSource.SURGERY_STUBS);
			}

			if (operator && operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 10, "#STR_TERJEMED_SURGERY_FAILED", "#STR_TERJEMED_SURGERY_WOUND_FAILED", "set:TerjePerkBlack_icon image:tp_surgerystab");
			}
		}

		return true;
	}

	static bool TryApplySplint(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (!GetGame().IsServer())
		{
			return false;
		}

		if (!item || !target)
		{
			return false;
		}

		string limb = SelectLimbForSplint(target);
		if (limb == "")
		{
			return false;
		}

		InediaInfectedAI_PainManager painManager = GetPainManager(target);
		if (!painManager)
		{
			return false;
		}

		float shockReductionMultiplier;
		float regenerationMultiplier;
		GetSplintParams(item, shockReductionMultiplier, regenerationMultiplier);
		if (shockReductionMultiplier < 1)
		{
			shockReductionMultiplier = 1;
		}

		if (regenerationMultiplier < 1)
		{
			regenerationMultiplier = 1;
		}

		painManager.ActivateBreakStabilizeForLimb(limb, shockReductionMultiplier, regenerationMultiplier, item);
		ConsumeSplintItem(item, target, limb);
		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] splint stabilize limb=" + limb);
		}

		return true;
	}
};

modded class ActionBandageBase
{
	override void ApplyBandage(ItemBase item, PlayerBase player)
	{
		if (OMD_BridgeConfig.IsActive() && OMD_BridgeTreatment.ShouldShowTerjeAutoBandage(player, item))
		{
			if (OMD_BridgeTreatment.TryApplyBandage(item, player))
			{
				if (item)
				{
					item.ApplyTerjeConsumableEffects(player, 1);
					CheckInfectionBandaging(item, player);
					PlayerBase operator = PlayerBase.Cast(item.GetHierarchyRootPlayer());
					OMD_BridgeTreatment.AddMedicineBandageExp(operator);
					OMD_BridgeTreatment.ConsumeBandageItem(item);
				}

				return;
			}
		}

		super.ApplyBandage(item, player);
	}

	override void ApplySurgeryBullet(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (OMD_BridgeConfig.IsActive() && OMD_BridgeTreatment.ShouldShowTerjeAutoSurgeryBullet(target))
		{
			if (OMD_BridgeTreatment.TryApplySurgeryBullet(item, target, operator))
			{
				CheckInfectionSurgery(item, target, operator);
				OMD_BridgeTreatment.ConsumeSurgeryItem(item);
			}

			return;
		}

		if (OMD_BridgeConfig.IsActive() && OMD_BridgeTreatment.IsManualTreatmentSelection())
		{
			return;
		}

		super.ApplySurgeryBullet(item, target, operator);
	}

	override void ApplySurgeryStub(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (OMD_BridgeConfig.IsActive() && OMD_BridgeTreatment.ShouldShowTerjeAutoSurgeryStub(target))
		{
			if (OMD_BridgeTreatment.TryApplySurgeryStub(item, target, operator))
			{
				CheckInfectionSurgery(item, target, operator);
				OMD_BridgeTreatment.ConsumeSurgeryItem(item);
			}

			return;
		}

		if (OMD_BridgeConfig.IsActive() && OMD_BridgeTreatment.IsManualTreatmentSelection())
		{
			return;
		}

		super.ApplySurgeryStub(item, target, operator);
	}
};

modded class ActionBandageSelf
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (item && item.HasQuantity() && item.IsTerjeEmptyQuantity())
		{
			return false;
		}

		if (OMD_BridgeConfig.IsActive() && OMD_BridgeTreatment.ShouldShowTerjeAutoBandage(player, item))
		{
			return true;
		}

		return super.ActionCondition(player, target, item);
	}
};

modded class ActionBandageTarget
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (item && item.HasQuantity() && item.IsTerjeEmptyQuantity())
		{
			return false;
		}

		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (OMD_BridgeConfig.IsActive() && otherPlayer && OMD_BridgeTreatment.ShouldShowTerjeAutoBandage(otherPlayer, item))
		{
			return true;
		}

		return super.ActionCondition(player, target, item);
	}
};

modded class ActionSurgeryBulletSelf
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (item && item.HasQuantity() && item.IsTerjeEmptyQuantity())
		{
			return false;
		}

		if (OMD_BridgeConfig.IsActive() && OMD_BridgeTreatment.ShouldShowTerjeAutoSurgeryBullet(player))
		{
			return true;
		}

		return super.ActionCondition(player, target, item);
	}
};

modded class ActionSurgeryBulletTarget
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (item && item.HasQuantity() && item.IsTerjeEmptyQuantity())
		{
			return false;
		}

		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (OMD_BridgeConfig.IsActive() && otherPlayer && OMD_BridgeTreatment.ShouldShowTerjeAutoSurgeryBullet(otherPlayer))
		{
			return true;
		}

		return super.ActionCondition(player, target, item);
	}
};

modded class ActionSurgeryStubSelf
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (item && item.HasQuantity() && item.IsTerjeEmptyQuantity())
		{
			return false;
		}

		if (OMD_BridgeConfig.IsActive() && OMD_BridgeTreatment.ShouldShowTerjeAutoSurgeryStub(player))
		{
			return true;
		}

		return super.ActionCondition(player, target, item);
	}
};

modded class ActionSurgeryStubTarget
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (item && item.HasQuantity() && item.IsTerjeEmptyQuantity())
		{
			return false;
		}

		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (OMD_BridgeConfig.IsActive() && otherPlayer && OMD_BridgeTreatment.ShouldShowTerjeAutoSurgeryStub(otherPlayer))
		{
			return true;
		}

		return super.ActionCondition(player, target, item);
	}
};

modded class ActionSplintSelf
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (OMD_BridgeConfig.IsActive() && OMD_BridgeTreatment.ShouldShowTerjeAutoSplint(player))
		{
			return true;
		}

		return super.ActionCondition(player, target, item);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (OMD_BridgeConfig.IsActive() && action_data && action_data.m_MainItem && action_data.m_Player)
		{
			if (OMD_BridgeTreatment.ShouldShowTerjeAutoSplint(action_data.m_Player))
			{
				if (OMD_BridgeTreatment.TryApplySplint(action_data.m_MainItem, action_data.m_Player, action_data.m_Player))
				{
					OMD_BridgeTreatment.AddMedicineSplintExp(action_data.m_Player);
					return;
				}

				return;
			}

			if (OMD_BridgeTreatment.IsManualTreatmentSelection())
			{
				return;
			}
		}

		super.OnFinishProgressServer(action_data);
	}
};

modded class ActionSplintTarget
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (OMD_BridgeConfig.IsActive() && otherPlayer && OMD_BridgeTreatment.ShouldShowTerjeAutoSplint(otherPlayer))
		{
			return true;
		}

		return super.ActionCondition(player, target, item);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (OMD_BridgeConfig.IsActive() && action_data && action_data.m_MainItem && action_data.m_Player && action_data.m_Target)
		{
			PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
			if (target && CanReceiveAction(action_data.m_Target))
			{
				if (OMD_BridgeTreatment.ShouldShowTerjeAutoSplint(target))
				{
					if (OMD_BridgeTreatment.TryApplySplint(action_data.m_MainItem, target, action_data.m_Player))
					{
						OMD_BridgeTreatment.AddMedicineSplintExp(action_data.m_Player);
						return;
					}

					return;
				}

				if (OMD_BridgeTreatment.IsManualTreatmentSelection())
				{
					return;
				}
			}
		}

		super.OnFinishProgressServer(action_data);
	}
};
