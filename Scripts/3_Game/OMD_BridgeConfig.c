class OMD_BridgeConfig
{
	protected static const string CONFIG_DIR = "$profile:omd";
	protected static const string CONFIG_PATH = "$profile:omd/OMD_Bridge.json";
	protected static ref OMD_BridgeConfigData s_Data;

	static OMD_BridgeConfigData Get()
	{
		if (!s_Data)
		{
			Load();
		}

		return s_Data;
	}

	static void Load()
	{
		if (!s_Data)
		{
			s_Data = new OMD_BridgeConfigData();
		}

		if (!FileExist(CONFIG_DIR))
		{
			MakeDirectory(CONFIG_DIR);
		}

		if (!FileExist(CONFIG_PATH))
		{
			SeedDefaults();
			Save();
			return;
		}

		OMD_BridgeConfigData loaded = new OMD_BridgeConfigData();
		JsonFileLoader<OMD_BridgeConfigData>.JsonLoadFile(CONFIG_PATH, loaded);
		s_Data = loaded;
		EnsurePainkillersDefaults();
		EnsureTreatmentsDefaults();
		EnsureDeepWoundSeverityDefaults();
		EnsureSutureDefaults();
		EnsureScratchesToDeepWoundDefaults();
		EnsureSutureBandageDefaults();
		EnsureTreatmentSelectionModeDefaults();
		EnsureServiceHitAmmoDefaults();
		EnsureArmorScratchDefaults();
		Save();
	}

	static void Save()
	{
		if (!s_Data)
		{
			s_Data = new OMD_BridgeConfigData();
		}

		if (!FileExist(CONFIG_DIR))
		{
			MakeDirectory(CONFIG_DIR);
		}

		JsonFileLoader<OMD_BridgeConfigData>.JsonSaveFile(CONFIG_PATH, s_Data);
	}

	static void SeedDefaults()
	{
		s_Data = new OMD_BridgeConfigData();
		s_Data.activeEnabled = true;
		s_Data.debugEnabled = true;
		s_Data.terjePainDisabled = true;
		s_Data.terjeBulletsDisabled = true;
		s_Data.terjeStubsDisabled = true;
		EnsurePainkillersDefaults();
		EnsureTreatmentsDefaults();
		EnsureDeepWoundSeverityDefaults();
		EnsureSutureDefaults();
		EnsureScratchesToDeepWoundDefaults();
		EnsureSutureBandageDefaults();
		EnsureTreatmentSelectionModeDefaults();
		s_Data.handsBreakDurationSeconds = 1800;
		s_Data.handsDeepWoundDurationSeconds = 1800;
		s_Data.feetBreakDurationSeconds = 1800;
		s_Data.feetDeepWoundDurationSeconds = 1800;
		s_Data.barefootFeetPainPercent = 10;
		s_Data.barefootFeetPainChanceMultiplier = 1.0;
		s_Data.feetDamagedShoesScratchChanceMultiplier = 0.5;
		s_Data.feetScratchChancePercent = 35;
		s_Data.handsScratchChancePercent = 50;
		s_Data.handsScratchFromBushChancePercent = 35;
		s_Data.headScratchChancePercent = 35;
		s_Data.armsScratchChancePercent = 40;
		s_Data.legsScratchChancePercent = 40;
		s_Data.torsoScratchChancePercent = 35;
		s_Data.handsScratchMinPainPercent = 30;
		s_Data.feetScratchMinPainPercent = 30;
		s_Data.headScratchMinPainPercent = 30;
		s_Data.armsScratchMinPainPercent = 30;
		s_Data.legsScratchMinPainPercent = 30;
		s_Data.torsoScratchMinPainPercent = 30;
		s_Data.scratchesToDeepWoundEnabled = true;
		s_Data.treatmentSelectionMode = "manual";
		s_Data.scratchesToDeepWoundCount = 3;
		s_Data.scratchesDeepWoundRate = 12;
		s_Data.scratchesDeepWoundRateBoostCount = 2;
		s_Data.scratchesDeepWoundRateBoost = 5;
		s_Data.scratchesToDeepWoundCooldownSeconds = 0;
		s_Data.handsDebuffAttackShockMedium = 2;
		s_Data.handsDebuffAttackShockBadly = 4;
		s_Data.handsDebuffAdsShockLow = 0.35;
		s_Data.handsDebuffAdsShockMedium = 0.7;
		s_Data.handsDebuffAdsShockBadly = 1.4;
		s_Data.feetDebuffAttackShockMedium = 3;
		s_Data.feetDebuffAttackShockBadly = 5;
		s_Data.feetDebuffWalkShockMedium = 0.05;
		s_Data.feetDebuffWalkShockBadly = 0.1;
		s_Data.fallFeetOnlyHeightMeters = 3;
		s_Data.fallFeetAndLegsHeightMeters = 5;
		s_Data.handsDebuffAimShakeLow = 2;
		s_Data.handsDebuffAimShakeMedium = 4;
		s_Data.handsDebuffAimShakeBadly = 8;
		s_Data.handsDebuffActionTimeLow = 1.15;
		s_Data.handsDebuffActionTimeMedium = 1.3;
		s_Data.handsDebuffActionTimeBadly = 1.5;
		s_Data.handsDebuffActionTimeCritical = 1.8;
		s_Data.handsDebuffDropChancePerPainPercent = 0.5;
		s_Data.handsDebuffDropChanceOnFracture = 35;
		s_Data.feetDebuffRunShockMedium = 0.1;
		s_Data.feetDebuffRunShockBadly = 0.2;
		s_Data.feetDebuffBlockSprintOnFracture = true;
		s_Data.feetDebuffBlockRunOnFracture = false;
		s_Data.handsGlovesProtectionBreakCoef = 1.0;
		s_Data.handsGlovesProtectionWoundCoef = 1.0;
		s_Data.handsGlovesProtectionBulletCoef = 1.0;
		s_Data.feetBootsProtectionBreakCoef = 1.0;
		s_Data.feetBootsProtectionWoundCoef = 1.0;
		s_Data.feetBootsProtectionBulletCoef = 1.0;
		s_Data.xpBandage = 50;
		s_Data.xpBandageFail = 25;
		s_Data.xpSurgeryWound = 500;
		s_Data.xpSurgeryWoundFail = 125;
		s_Data.xpSurgeryBullet = 750;
		s_Data.xpSurgeryBulletFail = 190;
		s_Data.xpSurgeryInternal = 1000;
		s_Data.xpSurgeryInternalFail = 250;
		s_Data.xpSplint = 100;
		s_Data.xpSplintFail = 50;
		s_Data.sutureHealSeconds = 1800;
		s_Data.sutureTearBaseChance = 10;
		s_Data.sutureTearChancePerDamage = 1.5;
		s_Data.sutureTearMaxChance = 85;
		s_Data.sutureTearChanceFromScratch = 100;
		s_Data.sutureBandageEnabled = true;
		s_Data.sutureBandageDirtySeconds = 600;
		s_Data.sutureRagDirtySeconds = 300;
		s_Data.sutureDirtySepsisChancePerMinute = 0.3;
		s_Data.sutureDirtyFromMedium = true;
		s_Data.sutureBandageDirtyPerDamage = 3;
		s_Data.sutureBandageDirtyPerDamageMax = 50;
		s_Data.sutureBandageDirtyPerScratch = 25;
		s_Data.sutureTearChanceFromScratchDirtyBandage = 50;
		s_Data.sutureDirtyBandageInfectionChance = 15;
		s_Data.sutureDirtyHealModifier = 0.5;
		s_Data.deepWoundSeverityLightMax = 17;
		s_Data.deepWoundSeverityMediumMax = 24;
		s_Data.deepWoundRegenLightOpen = 0.6;
		s_Data.deepWoundRegenLightControlled = 0.67;
		s_Data.deepWoundRegenMediumOpen = 0.43;
		s_Data.deepWoundRegenMediumControlled = 0.53;
		s_Data.deepWoundRegenHeavyOpen = 0.3;
		s_Data.deepWoundRegenHeavyControlled = 0.4;
		s_Data.deepWoundSeverityColorLight = ARGB(255, 255, 230, 0);
		s_Data.deepWoundSeverityColorMedium = ARGB(255, 255, 140, 0);
		s_Data.deepWoundSeverityColorHeavy = ARGB(255, 255, 40, 40);
		s_Data.tourniquetEnabled = false;
		s_Data.serviceHitAmmo = new array<string>;
		s_Data.serviceHitAmmo.Insert("OMD_Ammo_Blunt");
		s_Data.armorBlocksScratch = true;
		FillArmorScratchBlockAmmoDefaults();
	}

	static void EnsureSutureDefaults()
	{
		if (!s_Data)
		{
			return;
		}

		if (s_Data.sutureHealSeconds <= 0)
		{
			s_Data.sutureHealSeconds = 1800;
		}

		if (s_Data.sutureTearBaseChance < 0 || s_Data.sutureTearBaseChance > 100)
		{
			s_Data.sutureTearBaseChance = 10;
		}

		if (s_Data.sutureTearChancePerDamage < 0)
		{
			s_Data.sutureTearChancePerDamage = 1.5;
		}

		if (s_Data.sutureTearMaxChance < 0 || s_Data.sutureTearMaxChance > 100)
		{
			s_Data.sutureTearMaxChance = 85;
		}

		if (s_Data.sutureTearChanceFromScratch < 0 || s_Data.sutureTearChanceFromScratch > 100)
		{
			s_Data.sutureTearChanceFromScratch = 100;
		}
	}

	static void EnsureScratchesToDeepWoundDefaults()
	{
		if (!s_Data)
		{
			return;
		}

		if (s_Data.scratchesToDeepWoundCount <= 0)
		{
			s_Data.scratchesToDeepWoundCount = 3;
		}

		if (s_Data.scratchesDeepWoundRate <= 0)
		{
			s_Data.scratchesDeepWoundRate = 12;
		}

		if (s_Data.scratchesDeepWoundRateBoostCount <= 0)
		{
			s_Data.scratchesDeepWoundRateBoostCount = 2;
		}

		if (s_Data.scratchesDeepWoundRateBoost <= 0)
		{
			s_Data.scratchesDeepWoundRateBoost = 5;
		}

		if (s_Data.scratchesToDeepWoundCooldownSeconds < 0)
		{
			s_Data.scratchesToDeepWoundCooldownSeconds = 0;
		}
	}

	static void EnsureSutureBandageDefaults()
	{
		if (!s_Data)
		{
			return;
		}

		if (s_Data.sutureBandageDirtySeconds <= 0)
		{
			s_Data.sutureBandageDirtySeconds = 600;
		}

		if (s_Data.sutureRagDirtySeconds <= 0)
		{
			s_Data.sutureRagDirtySeconds = 300;
		}

		if (s_Data.sutureDirtySepsisChancePerMinute < 0)
		{
			s_Data.sutureDirtySepsisChancePerMinute = 0.3;
		}

		if (s_Data.sutureBandageDirtyPerDamage < 0)
		{
			s_Data.sutureBandageDirtyPerDamage = 3;
		}

		if (s_Data.sutureBandageDirtyPerDamageMax < 0)
		{
			s_Data.sutureBandageDirtyPerDamageMax = 50;
		}

		if (s_Data.sutureBandageDirtyPerScratch < 0 || s_Data.sutureBandageDirtyPerScratch > 100)
		{
			s_Data.sutureBandageDirtyPerScratch = 25;
		}

		if (s_Data.sutureTearChanceFromScratchDirtyBandage < 0 || s_Data.sutureTearChanceFromScratchDirtyBandage > 100)
		{
			s_Data.sutureTearChanceFromScratchDirtyBandage = 50;
		}

		if (s_Data.sutureDirtyBandageInfectionChance < 0 || s_Data.sutureDirtyBandageInfectionChance > 100)
		{
			s_Data.sutureDirtyBandageInfectionChance = 15;
		}

		if (s_Data.sutureDirtyHealModifier < 0 || s_Data.sutureDirtyHealModifier > 1)
		{
			s_Data.sutureDirtyHealModifier = 0.5;
		}

		if (!s_Data.sutureDisinfectantClasses)
		{
			s_Data.sutureDisinfectantClasses = new array<string>;
		}

		if (s_Data.sutureDisinfectantClasses.Count() == 0)
		{
			s_Data.sutureDisinfectantClasses.Insert("DisinfectantAlcohol");
			s_Data.sutureDisinfectantClasses.Insert("IodineTincture");
			s_Data.sutureDisinfectantClasses.Insert("DisinfectantSpray");
			s_Data.sutureDisinfectantClasses.Insert("TerjeAmpouleAlcohol");
		}
	}

	static void EnsureDeepWoundSeverityDefaults()
	{
		if (!s_Data)
		{
			return;
		}

		if (s_Data.deepWoundSeverityLightMax <= 0)
		{
			s_Data.deepWoundSeverityLightMax = 17;
		}

		if (s_Data.deepWoundSeverityMediumMax <= 0)
		{
			s_Data.deepWoundSeverityMediumMax = 24;
		}

		if (s_Data.deepWoundRegenLightOpen <= 0)
		{
			s_Data.deepWoundRegenLightOpen = 0.6;
		}

		if (s_Data.deepWoundRegenLightControlled <= 0)
		{
			s_Data.deepWoundRegenLightControlled = 0.67;
		}

		if (s_Data.deepWoundRegenMediumOpen <= 0)
		{
			s_Data.deepWoundRegenMediumOpen = 0.43;
		}

		if (s_Data.deepWoundRegenMediumControlled <= 0)
		{
			s_Data.deepWoundRegenMediumControlled = 0.53;
		}

		if (s_Data.deepWoundRegenHeavyOpen <= 0)
		{
			s_Data.deepWoundRegenHeavyOpen = 0.3;
		}

		if (s_Data.deepWoundRegenHeavyControlled <= 0)
		{
			s_Data.deepWoundRegenHeavyControlled = 0.4;
		}

		if (s_Data.deepWoundSeverityColorLight == 0)
		{
			s_Data.deepWoundSeverityColorLight = ARGB(255, 255, 230, 0);
		}

		if (s_Data.deepWoundSeverityColorMedium == 0)
		{
			s_Data.deepWoundSeverityColorMedium = ARGB(255, 255, 140, 0);
		}

		if (s_Data.deepWoundSeverityColorHeavy == 0)
		{
			s_Data.deepWoundSeverityColorHeavy = ARGB(255, 255, 40, 40);
		}
	}

	static void EnsurePainkillersDefaults()
	{
		if (!s_Data)
		{
			return;
		}

		if (!s_Data.painkillers)
		{
			s_Data.painkillers = new array<ref OMD_BridgePainkillerEntry>;
		}

		AppendPainkillerDefault("PainkillerTablets", 1, 300);
		AppendPainkillerDefault("TerjePillsPainkillerTablets", 1, 300);
		AppendPainkillerDefault("TerjePillsAnalgin", 1, 500);
		AppendPainkillerDefault("TerjePillsNimesulid", 1, 600);
		AppendPainkillerDefault("TerjePillsParacetamol", 1, 200);
		AppendPainkillerDefault("TerjePillsIbuprofen", 1, 600);
		AppendPainkillerDefault("TerjePillsNurofen", 1, 350);
		AppendPainkillerDefault("TerjePillsNoopept", 1, 380);
		AppendPainkillerDefault("TerjeAmpouleKetarol", 1, 1200);
		AppendPainkillerDefault("TerjeAmpouleNovacaine", 2, 1200);
		AppendPainkillerDefault("TerjeInjectorPropital", 2, 180);
		AppendPainkillerDefault("Morphine", 3, 300);
		AppendPainkillerDefault("TerjeAmpouleMorphine", 3, 850);
		AppendPainkillerDefault("TerjeAmpouleGexobarbital", 3, 900);
		AppendPainkillerDefault("TerjeAmpouleKetamin", 3, 600);
		AppendPainkillerDefault("TerjeInjectorPromidol", 3, 600);
		AppendPainkillerDefault("TerjeInjectorReanimatal", 3, 240);
	}

	static void AppendPainkillerDefault(string className, int level, float durationSeconds)
	{
		if (!s_Data)
		{
			return;
		}

		if (!s_Data.painkillers)
		{
			s_Data.painkillers = new array<ref OMD_BridgePainkillerEntry>;
		}

		int i;
		OMD_BridgePainkillerEntry existing;
		for (i = 0; i < s_Data.painkillers.Count(); i++)
		{
			existing = s_Data.painkillers.Get(i);
			if (!existing)
			{
				continue;
			}

			if (existing.className == className)
			{
				return;
			}
		}

		OMD_BridgePainkillerEntry entry = new OMD_BridgePainkillerEntry();
		entry.className = className;
		entry.level = level;
		entry.durationSeconds = durationSeconds;
		s_Data.painkillers.Insert(entry);
	}

	static void EnsureTreatmentsDefaults()
	{
		if (!s_Data)
		{
			return;
		}

		if (!s_Data.treatments)
		{
			s_Data.treatments = new array<ref OMD_BridgeTreatmentEntry>;
		}

		AppendTreatmentDefault("TerjePlaster", "scratch", 0, 1, 1, 1);
		AppendTreatmentDefault("BandageDressing", "bandage", 600, 1.5, 1, 1);
		AppendTreatmentDefault("TerjeBandageHemostatic", "bandage", 900, 2, 1, 1);
		AppendTreatmentDefault("Rag", "bandage", 300, 1, 1, 1);
		AppendTreatmentDefault("Bandana_ColorBase", "bandage", 300, 1, 1, 1);
		AppendTreatmentDefault("TerjeSurgicalKit", "surgery", 0, 1, 1, 1);
		AppendTreatmentDefault("TerjeSurgicalTool_ColorBase", "surgery", 0, 1, 1, 1);
		AppendTreatmentDefault("Splint", "splint", 0, 1, 1.5, 1.5);
	}

	static void AppendTreatmentDefault(string className, string healType, float bandageDuration, float bandageRegen, float splintShock, float splintRegen)
	{
		if (!s_Data)
		{
			return;
		}

		if (!s_Data.treatments)
		{
			s_Data.treatments = new array<ref OMD_BridgeTreatmentEntry>;
		}

		int i;
		OMD_BridgeTreatmentEntry existing;
		for (i = 0; i < s_Data.treatments.Count(); i++)
		{
			existing = s_Data.treatments.Get(i);
			if (!existing)
			{
				continue;
			}

			if (existing.className == className)
			{
				return;
			}
		}

		OMD_BridgeTreatmentEntry entry = new OMD_BridgeTreatmentEntry();
		entry.className = className;
		entry.healType = healType;
		entry.bandageEffectiveDurationSeconds = bandageDuration;
		entry.bandageRegenerationMultiplier = bandageRegen;
		entry.splintShockReductionMultiplier = splintShock;
		entry.splintRegenerationMultiplier = splintRegen;
		s_Data.treatments.Insert(entry);
	}

	static bool TryGetTreatmentEntry(string className, out OMD_BridgeTreatmentEntry entry)
	{
		entry = null;

		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return false;
		}

		if (!data.treatments)
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

			if (candidate.className != className)
			{
				continue;
			}

			entry = candidate;
			return true;
		}

		return false;
	}

	static bool IsActive()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return false;
		}

		return data.activeEnabled;
	}

	static bool IsDebugEnabled()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return false;
		}

		return data.debugEnabled;
	}

	static bool OMD_Bridge_IsServiceHitAmmo(string ammo)
	{
		if (ammo == "")
		{
			return false;
		}

		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return false;
		}

		if (!data.serviceHitAmmo)
		{
			return false;
		}

		int i;
		int count;
		string entry;
		count = data.serviceHitAmmo.Count();
		for (i = 0; i < count; i++)
		{
			entry = data.serviceHitAmmo.Get(i);
			if (entry == ammo)
			{
				return true;
			}
		}

		return false;
	}

	static bool IsArmorScratchBlockEnabled()
	{
		OMD_BridgeConfigData data;
		data = Get();
		if (!data)
		{
			return false;
		}

		return data.armorBlocksScratch;
	}

	static bool OMD_Bridge_IsArmorScratchBlockAmmo(string ammo)
	{
		if (ammo == "")
		{
			return false;
		}

		OMD_BridgeConfigData data;
		data = Get();
		if (!data)
		{
			return false;
		}

		if (!data.armorScratchBlockAmmo)
		{
			return false;
		}

		int i;
		int count;
		string entry;
		count = data.armorScratchBlockAmmo.Count();
		for (i = 0; i < count; i++)
		{
			entry = data.armorScratchBlockAmmo.Get(i);
			if (entry == "")
			{
				continue;
			}

			if (ammo.IndexOf(entry) == 0)
			{
				return true;
			}

			if (GetGame())
			{
				if (GetGame().IsKindOf(ammo, entry))
				{
					return true;
				}
			}
		}

		return false;
	}

	static bool IsTerjePainDisabled()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return true;
		}

		return data.terjePainDisabled;
	}

	static bool IsTerjeBulletsDisabled()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return true;
		}

		return data.terjeBulletsDisabled;
	}

	static bool IsTerjeStubsDisabled()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return true;
		}

		return data.terjeStubsDisabled;
	}

	static bool TryGetPainkillerEntry(string className, out int level, out float durationSeconds)
	{
		level = 0;
		durationSeconds = 0;

		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return false;
		}

		if (!data.painkillers)
		{
			return false;
		}

		int i;
		OMD_BridgePainkillerEntry entry;
		for (i = 0; i < data.painkillers.Count(); i++)
		{
			entry = data.painkillers.Get(i);
			if (!entry)
			{
				continue;
			}

			if (entry.className != className)
			{
				continue;
			}

			level = entry.level;
			durationSeconds = entry.durationSeconds;
			return true;
		}

		return false;
	}

	static float GetHandsBreakDurationSeconds()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1800;
		}

		return data.handsBreakDurationSeconds;
	}

	static float GetHandsDeepWoundDurationSeconds()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1800;
		}

		return data.handsDeepWoundDurationSeconds;
	}

	static float GetFeetBreakDurationSeconds()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1800;
		}

		return data.feetBreakDurationSeconds;
	}

	static float GetFeetDeepWoundDurationSeconds()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1800;
		}

		return data.feetDeepWoundDurationSeconds;
	}

	static float GetBarefootFeetPainPercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 10;
		}

		return data.barefootFeetPainPercent;
	}

	static float GetBarefootFeetPainChanceMultiplier()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.0;
		}

		return data.barefootFeetPainChanceMultiplier;
	}

	static float GetFeetDamagedShoesScratchChanceMultiplier()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 0.5;
		}

		return data.feetDamagedShoesScratchChanceMultiplier;
	}

	static float GetFeetScratchChancePercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 35;
		}

		return data.feetScratchChancePercent;
	}

	static float GetHandsScratchChancePercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 50;
		}

		return data.handsScratchChancePercent;
	}

	static float GetHandsScratchFromBushChancePercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 35;
		}

		return data.handsScratchFromBushChancePercent;
	}

	static float GetHandsScratchMinPainPercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 30;
		}

		return data.handsScratchMinPainPercent;
	}

	static float GetFeetScratchMinPainPercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 30;
		}

		return data.feetScratchMinPainPercent;
	}

	static float GetHeadScratchChancePercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 35;
		}

		return data.headScratchChancePercent;
	}

	static float GetArmsScratchChancePercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 40;
		}

		return data.armsScratchChancePercent;
	}

	static float GetLegsScratchChancePercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 40;
		}

		return data.legsScratchChancePercent;
	}

	static float GetTorsoScratchChancePercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 35;
		}

		return data.torsoScratchChancePercent;
	}

	static float GetHeadScratchMinPainPercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 30;
		}

		return data.headScratchMinPainPercent;
	}

	static float GetArmsScratchMinPainPercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 30;
		}

		return data.armsScratchMinPainPercent;
	}

	static float GetLegsScratchMinPainPercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 30;
		}

		return data.legsScratchMinPainPercent;
	}

	static float GetTorsoScratchMinPainPercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 30;
		}

		return data.torsoScratchMinPainPercent;
	}

	static float GetScratchChancePercentForLimb(string limb)
	{
		if (limb == "hands")
		{
			return GetHandsScratchChancePercent();
		}

		if (limb == "feet")
		{
			return GetFeetScratchChancePercent();
		}

		if (limb == "head")
		{
			return GetHeadScratchChancePercent();
		}

		if (limb == "arms")
		{
			return GetArmsScratchChancePercent();
		}

		if (limb == "legs")
		{
			return GetLegsScratchChancePercent();
		}

		if (limb == "torso")
		{
			return GetTorsoScratchChancePercent();
		}

		return 0;
	}

	static float GetScratchMinPainPercentForLimb(string limb)
	{
		if (limb == "hands")
		{
			return GetHandsScratchMinPainPercent();
		}

		if (limb == "feet")
		{
			return GetFeetScratchMinPainPercent();
		}

		if (limb == "head")
		{
			return GetHeadScratchMinPainPercent();
		}

		if (limb == "arms")
		{
			return GetArmsScratchMinPainPercent();
		}

		if (limb == "legs")
		{
			return GetLegsScratchMinPainPercent();
		}

		if (limb == "torso")
		{
			return GetTorsoScratchMinPainPercent();
		}

		return 0;
	}

	static void EnsureTreatmentSelectionModeDefaults()
	{
		if (!s_Data)
		{
			return;
		}

		if (s_Data.treatmentSelectionMode == "")
		{
			s_Data.treatmentSelectionMode = "manual";
			return;
		}

		if (s_Data.treatmentSelectionMode == "manual")
		{
			return;
		}

		if (s_Data.treatmentSelectionMode == "auto")
		{
			return;
		}

		s_Data.treatmentSelectionMode = "manual";
	}

	static void EnsureServiceHitAmmoDefaults()
	{
		if (!s_Data)
		{
			return;
		}

		if (!FileExist(CONFIG_PATH))
		{
			return;
		}

		FileHandle handle;
		handle = OpenFile(CONFIG_PATH, FileMode.READ);
		if (!handle)
		{
			return;
		}

		string line;
		bool foundKey;
		foundKey = false;
		while (FGets(handle, line) >= 0)
		{
			if (line.Contains("serviceHitAmmo"))
			{
				foundKey = true;
				break;
			}
		}

		CloseFile(handle);

		if (foundKey)
		{
			return;
		}

		s_Data.serviceHitAmmo = new array<string>;
		s_Data.serviceHitAmmo.Insert("OMD_Ammo_Blunt");
	}

	static void EnsureArmorScratchDefaults()
	{
		if (!s_Data)
		{
			return;
		}

		if (!FileExist(CONFIG_PATH))
		{
			return;
		}

		FileHandle handle;
		handle = OpenFile(CONFIG_PATH, FileMode.READ);
		if (!handle)
		{
			return;
		}

		string line;
		bool foundFlag;
		bool foundAmmo;
		foundFlag = false;
		foundAmmo = false;
		while (FGets(handle, line) >= 0)
		{
			if (line.Contains("armorBlocksScratch"))
			{
				foundFlag = true;
			}

			if (line.Contains("armorScratchBlockAmmo"))
			{
				foundAmmo = true;
			}
		}

		CloseFile(handle);

		if (!foundFlag)
		{
			s_Data.armorBlocksScratch = true;
		}

		if (foundAmmo)
		{
			return;
		}

		FillArmorScratchBlockAmmoDefaults();
	}

	static void FillArmorScratchBlockAmmoDefaults()
	{
		if (!s_Data)
		{
			return;
		}

		s_Data.armorScratchBlockAmmo = new array<string>;
		s_Data.armorScratchBlockAmmo.Insert("MeleeSharpLight");
		s_Data.armorScratchBlockAmmo.Insert("MeleeSharpHeavy");
		s_Data.armorScratchBlockAmmo.Insert("MeleeBlunt");
		s_Data.armorScratchBlockAmmo.Insert("MeleeLightBlunt");
		s_Data.armorScratchBlockAmmo.Insert("MeleeWoodBlunt");
		s_Data.armorScratchBlockAmmo.Insert("MeleeBat");
		s_Data.armorScratchBlockAmmo.Insert("MeleeFist");
		s_Data.armorScratchBlockAmmo.Insert("MeleeSoft");
		s_Data.armorScratchBlockAmmo.Insert("MeleeCrafted");
		s_Data.armorScratchBlockAmmo.Insert("MeleeWAxe");
		s_Data.armorScratchBlockAmmo.Insert("MeleeMachete");
		s_Data.armorScratchBlockAmmo.Insert("MeleeSickle");
		s_Data.armorScratchBlockAmmo.Insert("MeleeFireExtinguisher");
		s_Data.armorScratchBlockAmmo.Insert("MeleeInfected");
		s_Data.armorScratchBlockAmmo.Insert("MeleeZombie");
		s_Data.armorScratchBlockAmmo.Insert("MeleePoliceInfected");
		s_Data.armorScratchBlockAmmo.Insert("MeleeSoldierInfected");
		s_Data.armorScratchBlockAmmo.Insert("MeleeMummyInfected");
	}

	static bool IsManualTreatmentSelection()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return true;
		}

		if (data.treatmentSelectionMode == "")
		{
			return true;
		}

		if (data.treatmentSelectionMode == "manual")
		{
			return true;
		}

		if (data.treatmentSelectionMode == "auto")
		{
			return false;
		}

		return true;
	}

	static float GetFallFeetOnlyHeightMeters()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 3;
		}

		return data.fallFeetOnlyHeightMeters;
	}

	static float GetFallFeetAndLegsHeightMeters()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 5;
		}

		return data.fallFeetAndLegsHeightMeters;
	}

	static float GetHandsDebuffAimShakeLow()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 2;
		}

		return data.handsDebuffAimShakeLow;
	}

	static float GetHandsDebuffAimShakeMedium()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 4;
		}

		return data.handsDebuffAimShakeMedium;
	}

	static float GetHandsDebuffAimShakeBadly()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 8;
		}

		return data.handsDebuffAimShakeBadly;
	}

	static float GetHandsDebuffActionTimeLow()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.15;
		}

		return data.handsDebuffActionTimeLow;
	}

	static float GetHandsDebuffActionTimeMedium()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.3;
		}

		return data.handsDebuffActionTimeMedium;
	}

	static float GetHandsDebuffActionTimeBadly()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.5;
		}

		return data.handsDebuffActionTimeBadly;
	}

	static float GetHandsDebuffActionTimeCritical()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.8;
		}

		return data.handsDebuffActionTimeCritical;
	}

	static float GetHandsDebuffDropChancePerPainPercent()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 0.5;
		}

		return data.handsDebuffDropChancePerPainPercent;
	}

	static float GetHandsDebuffDropChanceOnFracture()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 35;
		}

		return data.handsDebuffDropChanceOnFracture;
	}

	static float GetFeetDebuffRunShockMedium()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 0.1;
		}

		return data.feetDebuffRunShockMedium;
	}

	static float GetFeetDebuffRunShockBadly()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 0.2;
		}

		return data.feetDebuffRunShockBadly;
	}

	static bool GetFeetDebuffBlockSprintOnFracture()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return true;
		}

		return data.feetDebuffBlockSprintOnFracture;
	}

	static bool GetFeetDebuffBlockRunOnFracture()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return false;
		}

		return data.feetDebuffBlockRunOnFracture;
	}

	static float GetHandsGlovesProtectionBreakCoef()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.0;
		}

		return data.handsGlovesProtectionBreakCoef;
	}

	static float GetHandsGlovesProtectionWoundCoef()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.0;
		}

		return data.handsGlovesProtectionWoundCoef;
	}

	static float GetHandsGlovesProtectionBulletCoef()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.0;
		}

		return data.handsGlovesProtectionBulletCoef;
	}

	static float GetFeetBootsProtectionBreakCoef()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.0;
		}

		return data.feetBootsProtectionBreakCoef;
	}

	static float GetFeetBootsProtectionWoundCoef()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.0;
		}

		return data.feetBootsProtectionWoundCoef;
	}

	static float GetFeetBootsProtectionBulletCoef()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.0;
		}

		return data.feetBootsProtectionBulletCoef;
	}

	static int GetXpBandage()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 50;
		}

		return data.xpBandage;
	}

	static int GetXpBandageFail()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 25;
		}

		return data.xpBandageFail;
	}

	static int GetXpSurgeryWound()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 500;
		}

		return data.xpSurgeryWound;
	}

	static int GetXpSurgeryWoundFail()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 125;
		}

		return data.xpSurgeryWoundFail;
	}

	static int GetXpSurgeryBullet()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 750;
		}

		return data.xpSurgeryBullet;
	}

	static int GetXpSurgeryBulletFail()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 190;
		}

		return data.xpSurgeryBulletFail;
	}

	static int GetXpSurgeryInternal()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1000;
		}

		return data.xpSurgeryInternal;
	}

	static int GetXpSurgeryInternalFail()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 250;
		}

		return data.xpSurgeryInternalFail;
	}

	static int GetXpSplint()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 100;
		}

		return data.xpSplint;
	}

	static int GetXpSplintFail()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 50;
		}

		return data.xpSplintFail;
	}

	static float GetSutureHealSeconds()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1800;
		}

		return data.sutureHealSeconds;
	}

	static float GetSutureTearBaseChance()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 10;
		}

		return data.sutureTearBaseChance;
	}

	static float GetSutureTearChancePerDamage()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.5;
		}

		return data.sutureTearChancePerDamage;
	}

	static float GetSutureTearMaxChance()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 85;
		}

		return data.sutureTearMaxChance;
	}

	static float GetSutureTearChanceFromScratch()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 100;
		}

		return data.sutureTearChanceFromScratch;
	}

	static bool IsScratchesToDeepWoundEnabled()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return true;
		}

		return data.scratchesToDeepWoundEnabled;
	}

	static int GetScratchesToDeepWoundCount()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.scratchesToDeepWoundCount <= 0)
		{
			return 3;
		}

		return data.scratchesToDeepWoundCount;
	}

	static float GetHandsDebuffAttackShockMedium()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 2;
		}

		return data.handsDebuffAttackShockMedium;
	}

	static float GetHandsDebuffAttackShockBadly()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 4;
		}

		return data.handsDebuffAttackShockBadly;
	}

	static float GetHandsDebuffAdsShockLow()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 0.35;
		}

		return data.handsDebuffAdsShockLow;
	}

	static float GetHandsDebuffAdsShockMedium()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 0.7;
		}

		return data.handsDebuffAdsShockMedium;
	}

	static float GetHandsDebuffAdsShockBadly()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 1.4;
		}

		return data.handsDebuffAdsShockBadly;
	}

	static float GetFeetDebuffAttackShockMedium()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 3;
		}

		return data.feetDebuffAttackShockMedium;
	}

	static float GetFeetDebuffAttackShockBadly()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 5;
		}

		return data.feetDebuffAttackShockBadly;
	}

	static float GetFeetDebuffWalkShockMedium()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 0.05;
		}

		return data.feetDebuffWalkShockMedium;
	}

	static float GetFeetDebuffWalkShockBadly()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return 0.1;
		}

		return data.feetDebuffWalkShockBadly;
	}

	static float GetScratchesDeepWoundRate()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.scratchesDeepWoundRate <= 0)
		{
			return 12;
		}

		return data.scratchesDeepWoundRate;
	}

	static int GetScratchesDeepWoundRateBoostCount()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.scratchesDeepWoundRateBoostCount <= 0)
		{
			return 2;
		}

		return data.scratchesDeepWoundRateBoostCount;
	}

	static float GetScratchesDeepWoundRateBoost()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.scratchesDeepWoundRateBoost <= 0)
		{
			return 5;
		}

		return data.scratchesDeepWoundRateBoost;
	}

	static bool IsSutureBandageEnabled()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return true;
		}

		return data.sutureBandageEnabled;
	}

	static float GetSutureBandageDirtySeconds()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.sutureBandageDirtySeconds <= 0)
		{
			return 600;
		}

		return data.sutureBandageDirtySeconds;
	}

	static float GetSutureRagDirtySeconds()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.sutureRagDirtySeconds <= 0)
		{
			return 300;
		}

		return data.sutureRagDirtySeconds;
	}

	static float GetSutureDirtySepsisChancePerMinute()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.sutureDirtySepsisChancePerMinute < 0)
		{
			return 0.3;
		}

		return data.sutureDirtySepsisChancePerMinute;
	}

	static bool GetSutureDirtyFromMedium()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return true;
		}

		return data.sutureDirtyFromMedium;
	}

	static float GetSutureBandageDirtyPerDamage()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.sutureBandageDirtyPerDamage < 0)
		{
			return 3;
		}

		return data.sutureBandageDirtyPerDamage;
	}

	static float GetSutureBandageDirtyPerDamageMax()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.sutureBandageDirtyPerDamageMax < 0)
		{
			return 50;
		}

		return data.sutureBandageDirtyPerDamageMax;
	}

	static float GetSutureBandageDirtyPerScratch()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.sutureBandageDirtyPerScratch < 0 || data.sutureBandageDirtyPerScratch > 100)
		{
			return 25;
		}

		return data.sutureBandageDirtyPerScratch;
	}

	static float GetSutureTearChanceFromScratchDirtyBandage()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.sutureTearChanceFromScratchDirtyBandage < 0 || data.sutureTearChanceFromScratchDirtyBandage > 100)
		{
			return 50;
		}

		return data.sutureTearChanceFromScratchDirtyBandage;
	}

	static float GetSutureDirtyBandageInfectionChance()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.sutureDirtyBandageInfectionChance < 0 || data.sutureDirtyBandageInfectionChance > 100)
		{
			return 15;
		}

		return data.sutureDirtyBandageInfectionChance;
	}

	static float GetSutureDirtyHealModifier()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.sutureDirtyHealModifier < 0 || data.sutureDirtyHealModifier > 1)
		{
			return 0.5;
		}

		return data.sutureDirtyHealModifier;
	}

	static array<string> GetSutureDisinfectantClasses()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return null;
		}

		return data.sutureDisinfectantClasses;
	}

	static float GetDeepWoundSeverityLightMax()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundSeverityLightMax <= 0)
		{
			return 17;
		}

		return data.deepWoundSeverityLightMax;
	}

	static float GetDeepWoundSeverityMediumMax()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundSeverityMediumMax <= 0)
		{
			return 24;
		}

		return data.deepWoundSeverityMediumMax;
	}

	static float GetDeepWoundRegenLightOpen()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundRegenLightOpen <= 0)
		{
			return 0.6;
		}

		return data.deepWoundRegenLightOpen;
	}

	static float GetDeepWoundRegenLightControlled()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundRegenLightControlled <= 0)
		{
			return 0.67;
		}

		return data.deepWoundRegenLightControlled;
	}

	static float GetDeepWoundRegenMediumOpen()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundRegenMediumOpen <= 0)
		{
			return 0.43;
		}

		return data.deepWoundRegenMediumOpen;
	}

	static float GetDeepWoundRegenMediumControlled()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundRegenMediumControlled <= 0)
		{
			return 0.53;
		}

		return data.deepWoundRegenMediumControlled;
	}

	static float GetDeepWoundRegenHeavyOpen()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundRegenHeavyOpen <= 0)
		{
			return 0.3;
		}

		return data.deepWoundRegenHeavyOpen;
	}

	static float GetDeepWoundRegenHeavyControlled()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundRegenHeavyControlled <= 0)
		{
			return 0.4;
		}

		return data.deepWoundRegenHeavyControlled;
	}

	static int GetDeepWoundSeverityColorLight()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundSeverityColorLight == 0)
		{
			return ARGB(255, 255, 230, 0);
		}

		return data.deepWoundSeverityColorLight;
	}

	static int GetDeepWoundSeverityColorMedium()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundSeverityColorMedium == 0)
		{
			return ARGB(255, 255, 140, 0);
		}

		return data.deepWoundSeverityColorMedium;
	}

	static int GetDeepWoundSeverityColorHeavy()
	{
		OMD_BridgeConfigData data = Get();
		if (!data || data.deepWoundSeverityColorHeavy == 0)
		{
			return ARGB(255, 255, 40, 40);
		}

		return data.deepWoundSeverityColorHeavy;
	}

	static bool IsTourniquetEnabled()
	{
		OMD_BridgeConfigData data = Get();
		if (!data)
		{
			return false;
		}

		return data.tourniquetEnabled;
	}
};
