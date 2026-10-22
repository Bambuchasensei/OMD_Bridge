class OMD_BridgePainkillerEntry
{
	string className;
	int level;
	float durationSeconds;
};

class OMD_BridgeTreatmentEntry
{
	string className;
	string healType;
	float bandageEffectiveDurationSeconds;
	float bandageRegenerationMultiplier;
	float splintShockReductionMultiplier;
	float splintRegenerationMultiplier;
};

class OMD_BridgeConfigData
{
	bool activeEnabled = true;
	bool debugEnabled = true;

	bool terjePainDisabled = true;
	bool terjeBulletsDisabled = true;
	bool terjeStubsDisabled = true;

	ref array<ref OMD_BridgePainkillerEntry> painkillers;
	ref array<ref OMD_BridgeTreatmentEntry> treatments;

	float handsBreakDurationSeconds = 1800;
	float handsDeepWoundDurationSeconds = 1800;
	float feetBreakDurationSeconds = 1800;
	float feetDeepWoundDurationSeconds = 1800;

	float barefootFeetPainPercent = 10;
	float barefootFeetPainChanceMultiplier = 1.0;
	float feetDamagedShoesScratchChanceMultiplier = 0.5;
	float feetScratchChancePercent = 35;
	float handsScratchChancePercent = 50;
	float handsScratchFromBushChancePercent = 35;
	float headScratchChancePercent = 35;
	float armsScratchChancePercent = 40;
	float legsScratchChancePercent = 40;
	float torsoScratchChancePercent = 35;
	float handsScratchMinPainPercent = 30;
	float feetScratchMinPainPercent = 30;
	float headScratchMinPainPercent = 30;
	float armsScratchMinPainPercent = 30;
	float legsScratchMinPainPercent = 30;
	float torsoScratchMinPainPercent = 30;
	bool scratchesToDeepWoundEnabled = true;
	int scratchesToDeepWoundCount = 3;
	float scratchesDeepWoundRate = 12;
	int scratchesDeepWoundRateBoostCount = 2;
	float scratchesDeepWoundRateBoost = 5;
	float scratchesToDeepWoundCooldownSeconds = 0;

	float handsDebuffAttackShockMedium = 2;
	float handsDebuffAttackShockBadly = 4;
	float handsDebuffAdsShockLow = 0.35;
	float handsDebuffAdsShockMedium = 0.7;
	float handsDebuffAdsShockBadly = 1.4;
	float feetDebuffAttackShockMedium = 3;
	float feetDebuffAttackShockBadly = 5;
	float feetDebuffWalkShockMedium = 0.05;
	float feetDebuffWalkShockBadly = 0.1;

	float fallFeetOnlyHeightMeters = 3;
	float fallFeetAndLegsHeightMeters = 5;

	float handsDebuffAimShakeLow = 2;
	float handsDebuffAimShakeMedium = 4;
	float handsDebuffAimShakeBadly = 8;
	float handsDebuffActionTimeLow = 1.15;
	float handsDebuffActionTimeMedium = 1.3;
	float handsDebuffActionTimeBadly = 1.5;
	float handsDebuffActionTimeCritical = 1.8;
	float handsDebuffDropChancePerPainPercent = 0.5;
	float handsDebuffDropChanceOnFracture = 35;

	float feetDebuffRunShockMedium = 0.1;
	float feetDebuffRunShockBadly = 0.2;
	bool feetDebuffBlockSprintOnFracture = true;
	bool feetDebuffBlockRunOnFracture = false;

	float handsGlovesProtectionBreakCoef = 1.0;
	float handsGlovesProtectionWoundCoef = 1.0;
	float handsGlovesProtectionBulletCoef = 1.0;
	float feetBootsProtectionBreakCoef = 1.0;
	float feetBootsProtectionWoundCoef = 1.0;
	float feetBootsProtectionBulletCoef = 1.0;

	int xpBandage = 50;
	int xpBandageFail = 25;
	int xpSurgeryWound = 500;
	int xpSurgeryWoundFail = 125;
	int xpSurgeryBullet = 750;
	int xpSurgeryBulletFail = 190;
	int xpSurgeryInternal = 1000;
	int xpSurgeryInternalFail = 250;
	int xpSplint = 100;
	int xpSplintFail = 50;

	float sutureHealSeconds = 1800;
	float sutureTearBaseChance = 10;
	float sutureTearChancePerDamage = 1.5;
	float sutureTearMaxChance = 85;
	float sutureTearChanceFromScratch = 100;
	bool sutureBandageEnabled = true;
	float sutureBandageDirtySeconds = 600;
	float sutureRagDirtySeconds = 300;
	float sutureDirtySepsisChancePerMinute = 0.3;
	bool sutureDirtyFromMedium = true;
	float sutureBandageDirtyPerDamage = 3;
	float sutureBandageDirtyPerDamageMax = 50;
	float sutureBandageDirtyPerScratch = 25;
	float sutureTearChanceFromScratchDirtyBandage = 50;
	float sutureDirtyBandageInfectionChance = 15;
	float sutureDirtyHealModifier = 0.5;
	ref array<string> sutureDisinfectantClasses;

	float deepWoundSeverityLightMax = 17;
	float deepWoundSeverityMediumMax = 24;
	float deepWoundRegenLightOpen = 0.6;
	float deepWoundRegenLightControlled = 0.67;
	float deepWoundRegenMediumOpen = 0.43;
	float deepWoundRegenMediumControlled = 0.53;
	float deepWoundRegenHeavyOpen = 0.3;
	float deepWoundRegenHeavyControlled = 0.4;
	int deepWoundSeverityColorLight = 0;
	int deepWoundSeverityColorMedium = 0;
	int deepWoundSeverityColorHeavy = 0;
	bool tourniquetEnabled = false;
	string treatmentSelectionMode = "manual";
	ref array<string> serviceHitAmmo;
	bool armorBlocksScratch = true;
	ref array<string> armorScratchBlockAmmo;
};
