modded class CAContinuousMineWood
{
	override void DamagePlayersHands(PlayerBase player)
	{
		if (!player || !OMD_BridgeConfig.IsActive())
		{
			super.DamagePlayersHands(player);
			return;
		}

		int handsBleedsBefore = player.OMD_Bridge_CountBleedingZonesForLimb("hands");
		super.DamagePlayersHands(player);

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
				Print("[OMD_Bridge] hands scratch from bush/mine vanilla bleed count=" + player.OMD_Bridge_CountLimbScratches("hands").ToString());
			}

			OMD_Bridge_TryHandsDeepWoundFromScratches(player);
			if (painManager)
			{
				painManager.OMD_Bridge_BlockSutureTearScratchBoost("hands", sutureWasActive, scratchesBefore);
			}

			return;
		}

		ItemBase gloves = ItemBase.Cast(player.FindAttachmentBySlotName("Gloves"));
		if (gloves && !gloves.IsDamageDestroyed())
		{
			return;
		}

		float bushChance = OMD_BridgeConfig.GetHandsScratchFromBushChancePercent();
		if (player.OMD_Bridge_AddLimbScratchFromSource("hands", "RightHand", bushChance))
		{
			OMD_Bridge_TryHandsDeepWoundFromScratches(player);
			if (painManager)
			{
				painManager.OMD_Bridge_BlockSutureTearScratchBoost("hands", sutureWasActive, scratchesBefore);
			}
		}
	}

	protected void OMD_Bridge_TryHandsDeepWoundFromScratches(PlayerBase player)
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
};
