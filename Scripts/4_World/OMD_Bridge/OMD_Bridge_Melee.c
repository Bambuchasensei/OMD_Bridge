modded class DayZPlayerMeleeFightLogic_LightHeavy
{
	override protected void DamageHands(DayZPlayer DZPlayer, ClothingBase gloves, InventoryItem itemInHands)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			super.DamageHands(DZPlayer, gloves, itemInHands);
			return;
		}

		PlayerBase player = PlayerBase.Cast(DZPlayer);
		if (!player || !player.InediaInfectedAI_GetPainManager())
		{
			super.DamageHands(DZPlayer, gloves, itemInHands);
			return;
		}

		if (m_HitType == EMeleeHitType.KICK)
		{
			int feetScratchesBefore = player.OMD_Bridge_CountFeetScratches();
			int feetBleedsBefore = player.OMD_Bridge_CountBleedingZonesForLimb("feet");
			super.DamageHands(DZPlayer, gloves, itemInHands);
			OMD_Bridge_RemoveKickFeetScratches(player, feetScratchesBefore, feetBleedsBefore);
			OMD_Bridge_ApplyLimbAttackShock(player, "feet");
			return;
		}

		int handsBleedsBefore = player.OMD_Bridge_CountBleedingZonesForLimb("hands");
		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		painManager.OMD_Bridge_BeginArmsToHandsRedirect();
		super.DamageHands(DZPlayer, gloves, itemInHands);
		painManager.OMD_Bridge_EndArmsToHandsRedirect();

		OMD_Bridge_ApplyBareHandMeleeScratch(player, gloves, itemInHands, handsBleedsBefore);
		OMD_Bridge_ApplyLimbAttackShock(player, "hands");
	}

	protected void OMD_Bridge_ApplyBareHandMeleeScratch(PlayerBase player, ClothingBase gloves, InventoryItem itemInHands, int handsBleedsBefore)
	{
		if (!player || !GetGame().IsServer())
		{
			return;
		}

		if (itemInHands)
		{
			return;
		}

		if (gloves && gloves.GetHealthLevel() < GameConstants.STATE_RUINED)
		{
			return;
		}

		EntityAI target = m_MeleeCombat.GetTargetEntity();
		if (!target)
		{
			return;
		}

		int handsBleedsAfter = player.OMD_Bridge_CountBleedingZonesForLimb("hands");
		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		int scratchesBefore = player.OMD_Bridge_CountLimbScratches("hands");
		bool sutureWasActive = false;
		if (painManager)
		{
			sutureWasActive = painManager.OMD_Bridge_IsLimbSutured("hands");
		}

		if (handsBleedsAfter > handsBleedsBefore)
		{
			player.OMD_Bridge_BumpScratchCount("hands", handsBleedsAfter - handsBleedsBefore);
			player.OMD_Bridge_ApplyScratchMinPain("hands");
			if (OMD_BridgeConfig.IsDebugEnabled())
			{
				Print("[OMD_Bridge] hands scratch from melee vanilla bleed count=" + player.OMD_Bridge_CountLimbScratches("hands").ToString());
			}

			OMD_Bridge_TryHandsScratchDeepWound(player);
			if (painManager)
			{
				painManager.OMD_Bridge_BlockSutureTearScratchBoost("hands", sutureWasActive, scratchesBefore);
			}

			return;
		}

		if (player.OMD_Bridge_AddLimbScratchFromSource("hands", "RightHand", -1))
		{
			OMD_Bridge_TryHandsScratchDeepWound(player);
			if (painManager)
			{
				painManager.OMD_Bridge_BlockSutureTearScratchBoost("hands", sutureWasActive, scratchesBefore);
			}
		}
	}

	protected void OMD_Bridge_TryHandsScratchDeepWound(PlayerBase player)
	{
		if (!player)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return;
		}

		painManager.OMD_Bridge_TryDeepWoundFromScratches("hands", player.OMD_Bridge_CountLimbScratches("hands"));
	}

	protected void OMD_Bridge_RemoveKickFeetScratches(PlayerBase player, int feetScratchesBefore, int feetBleedsBefore)
	{
		if (!player)
		{
			return;
		}

		int feetScratchesAfter = player.OMD_Bridge_CountFeetScratches();
		while (feetScratchesAfter > feetScratchesBefore)
		{
			player.OMD_Bridge_RemoveOneScratch("feet");
			feetScratchesAfter = feetScratchesAfter - 1;
		}

		int feetBleedsAfter = player.OMD_Bridge_CountBleedingZonesForLimb("feet");
		while (feetBleedsAfter > feetBleedsBefore)
		{
			player.OMD_Bridge_RemoveOneScratchBleed("feet");
			feetBleedsAfter = feetBleedsAfter - 1;
		}
	}

	protected void OMD_Bridge_ApplyLimbAttackShock(PlayerBase player, string limb)
	{
		if (!player || !GetGame().IsServer())
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager || !painManager.PainSystemIsActive())
		{
			return;
		}

		InediaInfectedAI_LimbPainLevels painLevel = painManager.GetPainWithBuffsLevelForLimb(limb);
		float shockAmount = 0;
		if (limb == "hands")
		{
			if (painLevel >= InediaInfectedAI_LimbPainLevels.BADLY)
			{
				shockAmount = OMD_BridgeConfig.GetHandsDebuffAttackShockBadly();
			}
			else if (painLevel >= InediaInfectedAI_LimbPainLevels.MEDIUM)
			{
				shockAmount = OMD_BridgeConfig.GetHandsDebuffAttackShockMedium();
			}
		}
		else if (limb == "feet")
		{
			if (painLevel >= InediaInfectedAI_LimbPainLevels.BADLY)
			{
				shockAmount = OMD_BridgeConfig.GetFeetDebuffAttackShockBadly();
			}
			else if (painLevel >= InediaInfectedAI_LimbPainLevels.MEDIUM)
			{
				shockAmount = OMD_BridgeConfig.GetFeetDebuffAttackShockMedium();
			}
		}

		if (shockAmount <= 0)
		{
			return;
		}

		float shockMultiplier = painManager.GetActionsShockMultiplierForLimb(limb);
		player.DecreaseHealth("GlobalHealth", "Shock", shockAmount * shockMultiplier);

		if (OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] attack shock limb=" + limb + " amount=" + (shockAmount * shockMultiplier).ToString());
		}
	}
};
