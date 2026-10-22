#ifndef SERVER
modded class IngameHud
{
	Widget m_OMD_Bridge_Layout;
	Widget m_OMD_Bridge_BadgesPanelWidget;
	ref map<string, ref Widget> m_OMD_Bridge_BadgesWidgetsList = new map<string, ref Widget>;
	ref map<string, bool> m_OMD_Bridge_FlashBadgesWidgetsFlashStatus = new map<string, bool>;

	bool m_OMD_Bridge_WidgetsInitialized = false;
	bool m_OMD_Bridge_InediaLimbsSwapped = false;
	float m_OMD_Bridge_UpdatePainBadgesLastTime = -1000000;
	float m_OMD_Bridge_FlashBadgesWidgetsHandlerLastTime = -1000000;
	bool m_OMD_Bridge_FlashBadgesWidgetsHandlerFlashStatus = true;
	int m_OMD_Bridge_InitWidgetsTries = 0;

	override void Init(Widget hud_panel_widget)
	{
		super.Init(hud_panel_widget);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(OMD_Bridge_InitWidgets, 150, false, hud_panel_widget);
	}

	override void Update(float timeslice)
	{
		super.Update(timeslice);
		OMD_Bridge_HideVanillaBleedingBadge();

		if (m_OMD_Bridge_WidgetsInitialized)
		{
			OMD_Bridge_UpdatePainBadges(timeslice);
			OMD_Bridge_FlashBadgesWidgetsHandler(timeslice);
		}
	}

	override void DisplayBadge(int key, int value)
	{
		super.DisplayBadge(key, value);
		OMD_Bridge_HideVanillaBleedingBadge();
	}

	void OMD_Bridge_HideVanillaBleedingBadge()
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!m_Badges)
		{
			return;
		}

		ImageWidget bleedingWidget;
		if (m_BadgesWidgets && m_BadgesWidgets.Find(NTFKEY_BLEEDISH, bleedingWidget) && bleedingWidget)
		{
			OMD_Bridge_HideWidget(bleedingWidget);
		}
		else
		{
			OMD_Bridge_HideWidget(m_Badges.FindAnyWidget("Bleeding"));
		}

		OMD_Bridge_HideWidget(m_Badges.FindAnyWidget("BleedingCount"));
	}

	void OMD_Bridge_InitWidgets(Widget hudPanelWidget)
	{
		if (m_OMD_Bridge_WidgetsInitialized)
		{
			return;
		}

		if (!hudPanelWidget)
		{
			return;
		}

		if (!m_OMD_Bridge_InediaLimbsSwapped)
		{
			if (m_InediaInfectedAI_InediaPainWidgetsInitialized)
			{
				OMD_Bridge_SwapInediaLimbs();
				m_OMD_Bridge_InediaLimbsSwapped = true;
			}
			else
			{
				m_OMD_Bridge_InitWidgetsTries = m_OMD_Bridge_InitWidgetsTries + 1;
				if (m_OMD_Bridge_InitWidgetsTries <= 10)
				{
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(OMD_Bridge_InitWidgets, 150, false, hudPanelWidget);
					return;
				}
			}
		}

		if (!m_OMD_Bridge_Layout)
		{
			m_OMD_Bridge_Layout = GetGame().GetWorkspace().CreateWidgets("OMD_Bridge/gui/layouts/omd_bridge_badges.layout");
			if (!m_OMD_Bridge_Layout)
			{
				return;
			}
		}

		if (!m_OMD_Bridge_BadgesPanelWidget)
		{
			if (m_Badges)
			{
				m_OMD_Bridge_BadgesPanelWidget = m_Badges;
			}
			else
			{
				m_OMD_Bridge_BadgesPanelWidget = hudPanelWidget.FindAnyWidget("BadgesPanel");
			}

			if (!m_OMD_Bridge_BadgesPanelWidget)
			{
				return;
			}
		}

		OMD_Bridge_RegisterPainLimbWidgets("hands");
		OMD_Bridge_RegisterPainLimbWidgets("feet");
		OMD_Bridge_RegisterBreakWidgets("hands");
		OMD_Bridge_RegisterBreakWidgets("feet");
		OMD_Bridge_RegisterDeepWoundWidgets("hands");
		OMD_Bridge_RegisterDeepWoundWidgets("feet");
		OMD_Bridge_RegisterBulletWidgets("hands");
		OMD_Bridge_RegisterBulletWidgets("feet");
		OMD_Bridge_RegisterScratchOnlyWidgets("hands");
		OMD_Bridge_RegisterScratchOnlyWidgets("feet");
		OMD_Bridge_RegisterScratchOnlyWidgets("head");
		OMD_Bridge_RegisterScratchOnlyWidgets("arms");
		OMD_Bridge_RegisterScratchOnlyWidgets("legs");
		OMD_Bridge_RegisterScratchOnlyWidgets("torso");
		OMD_Bridge_RegisterSutureWidgets("head");
		OMD_Bridge_RegisterSutureWidgets("arms");
		OMD_Bridge_RegisterSutureWidgets("legs");
		OMD_Bridge_RegisterSutureWidgets("torso");
		OMD_Bridge_RegisterSutureWidgets("hands");
		OMD_Bridge_RegisterSutureWidgets("feet");
		OMD_Bridge_ApplyHandsFeetLimbIcons();
		m_OMD_Bridge_WidgetsInitialized = true;
		OMD_Bridge_HideVanillaBleedingBadge();
	}

	protected void OMD_Bridge_RegisterPainLimbWidgets(string limb)
	{
		string frameName = "pain_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_Layout.FindAnyWidget(frameName);
		if (!frameWidget)
		{
			return;
		}

		m_OMD_Bridge_BadgesWidgetsList.Set(frameName, frameWidget);
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_limb", frameWidget.FindAnyWidget("Limb"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_pain_red", frameWidget.FindAnyWidget("PainRed"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_pain_orange", frameWidget.FindAnyWidget("PainOrange"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_pain_yellow", frameWidget.FindAnyWidget("PainYellow"));
		m_OMD_Bridge_BadgesPanelWidget.AddChild(frameWidget);
	}

	protected void OMD_Bridge_RegisterBreakWidgets(string limb)
	{
		string frameName = "break_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_Layout.FindAnyWidget(frameName);
		if (!frameWidget)
		{
			return;
		}

		m_OMD_Bridge_BadgesWidgetsList.Set(frameName, frameWidget);
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_limb", frameWidget.FindAnyWidget("Limb"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_bone_break", frameWidget.FindAnyWidget("BoneBreak"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_bone_break_splinted", frameWidget.FindAnyWidget("BoneBreakSplinted"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_tendency_first", frameWidget.FindAnyWidget("TendencyFirst"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_tendency_second", frameWidget.FindAnyWidget("TendencySecond"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_tendency_third", frameWidget.FindAnyWidget("TendencyThird"));
		m_OMD_Bridge_BadgesPanelWidget.AddChild(frameWidget);
	}

	protected void OMD_Bridge_RegisterDeepWoundWidgets(string limb)
	{
		string frameName = "deep_wound_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_Layout.FindAnyWidget(frameName);
		if (!frameWidget)
		{
			return;
		}

		m_OMD_Bridge_BadgesWidgetsList.Set(frameName, frameWidget);
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_limb", frameWidget.FindAnyWidget("Limb"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_deep_wound", frameWidget.FindAnyWidget("DeepWound"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_deep_wound_bandaged", frameWidget.FindAnyWidget("DeepWoundBandaged"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_deep_wound_bandaged_ineffective", frameWidget.FindAnyWidget("DeepWoundBandagedIneffective"));
		m_OMD_Bridge_BadgesPanelWidget.AddChild(frameWidget);
	}

	protected void OMD_Bridge_RegisterBulletWidgets(string limb)
	{
		string frameName = "bullet_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_Layout.FindAnyWidget(frameName);
		if (!frameWidget)
		{
			return;
		}

		m_OMD_Bridge_BadgesWidgetsList.Set(frameName, frameWidget);
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_limb", frameWidget.FindAnyWidget("Limb"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_counter_1", frameWidget.FindAnyWidget("Counter1"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_counter_2", frameWidget.FindAnyWidget("Counter2"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_counter_3", frameWidget.FindAnyWidget("Counter3"));
		m_OMD_Bridge_BadgesPanelWidget.AddChild(frameWidget);
	}

	protected void OMD_Bridge_RegisterScratchOnlyWidgets(string limb)
	{
		string frameName = "scratch_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_Layout.FindAnyWidget(frameName);
		if (!frameWidget)
		{
			return;
		}

		m_OMD_Bridge_BadgesWidgetsList.Set(frameName, frameWidget);
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_limb", frameWidget.FindAnyWidget("Limb"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_scratch", frameWidget.FindAnyWidget("Scratch"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_scratch_count", frameWidget.FindAnyWidget("Count"));
		OMD_Bridge_LoadScratchIcon(frameWidget.FindAnyWidget("Scratch"));
		m_OMD_Bridge_BadgesPanelWidget.AddChild(frameWidget);
	}

	protected void OMD_Bridge_RegisterSutureWidgets(string limb)
	{
		string frameName = "suture_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_Layout.FindAnyWidget(frameName);
		if (!frameWidget)
		{
			return;
		}

		m_OMD_Bridge_BadgesWidgetsList.Set(frameName, frameWidget);
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_limb", frameWidget.FindAnyWidget("Limb"));
		m_OMD_Bridge_BadgesWidgetsList.Set(frameName + "_suture", frameWidget.FindAnyWidget("Suture"));
		OMD_Bridge_LoadSutureIcon(frameWidget.FindAnyWidget("Suture"));
		m_OMD_Bridge_BadgesPanelWidget.AddChild(frameWidget);
	}

	protected void OMD_Bridge_LoadScratchIcon(Widget widget)
	{
		ImageWidget scratchImage;
		if (!Class.CastTo(scratchImage, widget))
		{
			return;
		}

		scratchImage.LoadImageFile(0, "set:TerjeMedicine_icon image:tm_scratch");
	}

	protected void OMD_Bridge_LoadSutureIcon(Widget widget)
	{
		ImageWidget sutureImage;
		if (!Class.CastTo(sutureImage, widget))
		{
			return;
		}

		sutureImage.LoadImageFile(0, "set:TerjeMedicine_icon image:tm_protectingwound");
	}

	void OMD_Bridge_UpdatePainBadges(float pDt)
	{
		if ((GetGame().GetTickTime() - m_OMD_Bridge_UpdatePainBadgesLastTime) < 1)
		{
			return;
		}

		m_OMD_Bridge_UpdatePainBadgesLastTime = GetGame().GetTickTime();

		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !player.InediaInfectedAI_GetPainManager())
		{
			return;
		}

		OMD_Bridge_RenderPainLimbWidget(player, "hands");
		OMD_Bridge_RenderPainLimbWidget(player, "feet");
		OMD_Bridge_RenderBreakWidget(player, "hands");
		OMD_Bridge_RenderBreakWidget(player, "feet");
		OMD_Bridge_RenderDeepWoundWidget(player, "hands");
		OMD_Bridge_RenderDeepWoundWidget(player, "feet");
		OMD_Bridge_ColorInediaDeepWoundIcons(player);
		OMD_Bridge_RenderBulletWidget(player, "hands");
		OMD_Bridge_RenderBulletWidget(player, "feet");
		OMD_Bridge_RenderScratchForLimb(player, "hands");
		OMD_Bridge_RenderScratchForLimb(player, "feet");
		OMD_Bridge_RenderScratchForLimb(player, "head");
		OMD_Bridge_RenderScratchForLimb(player, "arms");
		OMD_Bridge_RenderScratchForLimb(player, "legs");
		OMD_Bridge_RenderScratchForLimb(player, "torso");
		OMD_Bridge_RenderSutureForLimb(player, "head");
		OMD_Bridge_RenderSutureForLimb(player, "arms");
		OMD_Bridge_RenderSutureForLimb(player, "legs");
		OMD_Bridge_RenderSutureForLimb(player, "torso");
		OMD_Bridge_RenderSutureForLimb(player, "hands");
		OMD_Bridge_RenderSutureForLimb(player, "feet");
	}

	protected void OMD_Bridge_ApplyHandsFeetLimbIcons()
	{
		string handsPath = "InediaInfectedAI/gui/badges/inediainfectedai/arms.paa";
		string feetPath = "InediaInfectedAI/gui/badges/inediainfectedai/legs.paa";
		OMD_Bridge_LoadBridgeLimb("pain_hands_frame_limb", handsPath);
		OMD_Bridge_LoadBridgeLimb("break_hands_frame_limb", handsPath);
		OMD_Bridge_LoadBridgeLimb("deep_wound_hands_frame_limb", handsPath);
		OMD_Bridge_LoadBridgeLimb("bullet_hands_frame_limb", handsPath);
		OMD_Bridge_LoadBridgeLimb("scratch_hands_frame_limb", handsPath);
		OMD_Bridge_LoadBridgeLimb("suture_hands_frame_limb", handsPath);
		OMD_Bridge_LoadBridgeLimb("pain_feet_frame_limb", feetPath);
		OMD_Bridge_LoadBridgeLimb("break_feet_frame_limb", feetPath);
		OMD_Bridge_LoadBridgeLimb("deep_wound_feet_frame_limb", feetPath);
		OMD_Bridge_LoadBridgeLimb("bullet_feet_frame_limb", feetPath);
		OMD_Bridge_LoadBridgeLimb("scratch_feet_frame_limb", feetPath);
		OMD_Bridge_LoadBridgeLimb("suture_feet_frame_limb", feetPath);
		OMD_Bridge_LoadBridgeLimb("scratch_arms_frame_limb", "OMD_Bridge/gui/badges/arm.paa");
		OMD_Bridge_LoadBridgeLimb("scratch_legs_frame_limb", "OMD_Bridge/gui/badges/leg.paa");
		OMD_Bridge_LoadBridgeLimb("suture_arms_frame_limb", "OMD_Bridge/gui/badges/arm.paa");
		OMD_Bridge_LoadBridgeLimb("suture_legs_frame_limb", "OMD_Bridge/gui/badges/leg.paa");
	}

	protected void OMD_Bridge_LoadBridgeLimb(string key, string path)
	{
		if (!m_OMD_Bridge_BadgesWidgetsList.Contains(key))
		{
			return;
		}

		OMD_Bridge_LoadLimbImage(m_OMD_Bridge_BadgesWidgetsList.Get(key), path);
	}

	protected void OMD_Bridge_RenderPainLimbWidget(PlayerBase player, string limb)
	{
		string frameName = "pain_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_BadgesWidgetsList.Get(frameName);
		if (!frameWidget)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager.PainSystemIsActive() || !painManager.m_ShowPainBadges)
		{
			OMD_Bridge_HideWidget(frameWidget);
			return;
		}

		InediaInfectedAI_LimbPainLevels limbPainLevel = painManager.GetPainWithBuffsLevelForLimb(limb);
		if (limbPainLevel <= InediaInfectedAI_LimbPainLevels.ZERO)
		{
			OMD_Bridge_EndFlashBadgeWidget(frameName + "_pain_red");
			OMD_Bridge_HideWidget(frameWidget);
			return;
		}

		OMD_Bridge_ShowWidget(frameWidget);

		Widget painRed = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_pain_red");
		Widget painOrange = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_pain_orange");
		Widget painYellow = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_pain_yellow");

		if (limbPainLevel >= InediaInfectedAI_LimbPainLevels.CRITICAL)
		{
			OMD_Bridge_FlashBadgeWidget(frameName + "_pain_red");
			OMD_Bridge_HideWidget(painOrange);
			OMD_Bridge_HideWidget(painYellow);
		}
		else if (limbPainLevel >= InediaInfectedAI_LimbPainLevels.BADLY)
		{
			OMD_Bridge_EndFlashBadgeWidget(frameName + "_pain_red");
			OMD_Bridge_ShowWidget(painRed);
			OMD_Bridge_HideWidget(painOrange);
			OMD_Bridge_HideWidget(painYellow);
		}
		else if (limbPainLevel >= InediaInfectedAI_LimbPainLevels.MEDIUM)
		{
			OMD_Bridge_EndFlashBadgeWidget(frameName + "_pain_red");
			OMD_Bridge_ShowWidget(painOrange);
			OMD_Bridge_HideWidget(painRed);
			OMD_Bridge_HideWidget(painYellow);
		}
		else
		{
			OMD_Bridge_EndFlashBadgeWidget(frameName + "_pain_red");
			OMD_Bridge_ShowWidget(painYellow);
			OMD_Bridge_HideWidget(painRed);
			OMD_Bridge_HideWidget(painOrange);
		}
	}

	protected void OMD_Bridge_RenderBreakWidget(PlayerBase player, string limb)
	{
		string frameName = "break_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_BadgesWidgetsList.Get(frameName);
		if (!frameWidget)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		Widget tendencyFirst = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_tendency_first");
		Widget tendencySecond = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_tendency_second");
		Widget tendencyThird = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_tendency_third");

		if (!painManager.m_ShowPainBadges || !painManager.LimbsBreakSystemIsActive())
		{
			OMD_Bridge_HideWidget(frameWidget);
			OMD_Bridge_HideWidget(tendencyFirst);
			OMD_Bridge_HideWidget(tendencySecond);
			OMD_Bridge_HideWidget(tendencyThird);
			return;
		}

		if (!painManager.IsLimbBroken(limb))
		{
			OMD_Bridge_HideWidget(frameWidget);
			OMD_Bridge_HideWidget(tendencyFirst);
			OMD_Bridge_HideWidget(tendencySecond);
			OMD_Bridge_HideWidget(tendencyThird);
			return;
		}

		OMD_Bridge_ShowWidget(frameWidget);

		Widget boneBreak = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_bone_break");
		Widget boneBreakSplinted = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_bone_break_splinted");

		if (painManager.IsLimbStabilized(limb))
		{
			OMD_Bridge_ShowWidget(boneBreakSplinted);
			OMD_Bridge_HideWidget(boneBreak);
		}
		else
		{
			OMD_Bridge_ShowWidget(boneBreak);
			OMD_Bridge_HideWidget(boneBreakSplinted);
		}

		InediaInfectedAI_LimbRegenerationLevels regenLevel = painManager.GetBreakRegenerationLevelForLimbClient(limb);
		if (regenLevel >= InediaInfectedAI_LimbRegenerationLevels.HIGH)
		{
			OMD_Bridge_ShowWidget(tendencyFirst);
			if (tendencyFirst)
			{
				tendencyFirst.SetPos(0, -2);
			}
			OMD_Bridge_ShowWidget(tendencySecond);
			if (tendencySecond)
			{
				tendencySecond.SetPos(0, 2);
			}
			OMD_Bridge_ShowWidget(tendencyThird);
			if (tendencyThird)
			{
				tendencyThird.SetPos(0, 6);
			}
		}
		else if (regenLevel >= InediaInfectedAI_LimbRegenerationLevels.MEDIUM)
		{
			OMD_Bridge_ShowWidget(tendencyFirst);
			if (tendencyFirst)
			{
				tendencyFirst.SetPos(0, -2);
			}
			OMD_Bridge_ShowWidget(tendencySecond);
			if (tendencySecond)
			{
				tendencySecond.SetPos(0, 2);
			}
			OMD_Bridge_HideWidget(tendencyThird);
		}
		else if (regenLevel >= InediaInfectedAI_LimbRegenerationLevels.LOW)
		{
			OMD_Bridge_ShowWidget(tendencyFirst);
			if (tendencyFirst)
			{
				tendencyFirst.SetPos(0, -2);
			}
			OMD_Bridge_HideWidget(tendencySecond);
			OMD_Bridge_HideWidget(tendencyThird);
		}
		else
		{
			OMD_Bridge_HideWidget(tendencyFirst);
			OMD_Bridge_HideWidget(tendencySecond);
			OMD_Bridge_HideWidget(tendencyThird);
		}
	}

	protected void OMD_Bridge_RenderDeepWoundWidget(PlayerBase player, string limb)
	{
		string frameName = "deep_wound_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_BadgesWidgetsList.Get(frameName);
		if (!frameWidget)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager.m_ShowPainBadges || !painManager.LimbsDeepWoundSystemIsActive())
		{
			OMD_Bridge_HideWidget(frameWidget);
			return;
		}

		if (!painManager.IsLimbDeepWounded(limb))
		{
			OMD_Bridge_HideWidget(frameWidget);
			return;
		}

		OMD_Bridge_ShowWidget(frameWidget);

		Widget deepWound = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_deep_wound");
		Widget deepWoundBandaged = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_deep_wound_bandaged");
		Widget deepWoundBandagedIneffective = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_deep_wound_bandaged_ineffective");

		if (painManager.IsLimbDeepWoundBandaged(limb))
		{
			if (painManager.IsLimbDeepWoundBandageEffective(limb))
			{
				OMD_Bridge_ShowWidget(deepWoundBandaged);
				OMD_Bridge_HideWidget(deepWoundBandagedIneffective);
			}
			else
			{
				OMD_Bridge_ShowWidget(deepWoundBandagedIneffective);
				OMD_Bridge_HideWidget(deepWoundBandaged);
			}

			OMD_Bridge_HideWidget(deepWound);
		}
		else
		{
			OMD_Bridge_ShowWidget(deepWound);
			OMD_Bridge_HideWidget(deepWoundBandaged);
			OMD_Bridge_HideWidget(deepWoundBandagedIneffective);
		}

		int severityTier = player.OMD_Bridge_GetSyncedDeepWoundSeverityForLimb(limb);
		int severityColor = OMD_Bridge_GetDeepWoundSeverityColor(severityTier);
		OMD_Bridge_SetWidgetColor(m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_limb"), severityColor);
		OMD_Bridge_SetWidgetColor(deepWound, severityColor);
		OMD_Bridge_SetWidgetColor(deepWoundBandaged, severityColor);
		OMD_Bridge_SetWidgetColor(deepWoundBandagedIneffective, severityColor);
	}

	protected void OMD_Bridge_ColorInediaDeepWoundIcons(PlayerBase player)
	{
		OMD_Bridge_ColorInediaDeepWoundLimb(player, "head");
		OMD_Bridge_ColorInediaDeepWoundLimb(player, "arms");
		OMD_Bridge_ColorInediaDeepWoundLimb(player, "legs");
		OMD_Bridge_ColorInediaDeepWoundLimb(player, "torso");
	}

	protected void OMD_Bridge_ColorInediaDeepWoundLimb(PlayerBase player, string limb)
	{
		if (!m_InediaInfectedAI_BadgesWidgetsList)
		{
			return;
		}

		string frameKey = "deep_wound_" + limb + "_frame";
		if (!m_InediaInfectedAI_BadgesWidgetsList.Contains(frameKey))
		{
			return;
		}

		int severityTier = player.OMD_Bridge_GetSyncedDeepWoundSeverityForLimb(limb);
		int severityColor = OMD_Bridge_GetDeepWoundSeverityColor(severityTier);
		OMD_Bridge_SetWidgetColor(m_InediaInfectedAI_BadgesWidgetsList.Get(frameKey + "_limb"), severityColor);
		OMD_Bridge_SetWidgetColor(m_InediaInfectedAI_BadgesWidgetsList.Get(frameKey + "_deep_wound"), severityColor);
		OMD_Bridge_SetWidgetColor(m_InediaInfectedAI_BadgesWidgetsList.Get(frameKey + "_deep_wound_bandaged"), severityColor);
		OMD_Bridge_SetWidgetColor(m_InediaInfectedAI_BadgesWidgetsList.Get(frameKey + "_deep_wound_bandaged_ineffective"), severityColor);
	}

	protected int OMD_Bridge_GetDeepWoundSeverityColor(int tier)
	{
		if (tier == 1)
		{
			return OMD_BridgeConfig.GetDeepWoundSeverityColorLight();
		}

		if (tier == 2)
		{
			return OMD_BridgeConfig.GetDeepWoundSeverityColorMedium();
		}

		if (tier == 3)
		{
			return OMD_BridgeConfig.GetDeepWoundSeverityColorHeavy();
		}

		return ARGB(255, 255, 255, 255);
	}

	protected void OMD_Bridge_SetWidgetColor(Widget widget, int color)
	{
		if (!widget)
		{
			return;
		}

		widget.SetColor(color);
	}

	protected void OMD_Bridge_RenderBulletWidget(PlayerBase player, string limb)
	{
		string frameName = "bullet_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_BadgesWidgetsList.Get(frameName);
		if (!frameWidget)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager.m_ShowPainBadges || !painManager.LimbsBulletSystemIsActive())
		{
			OMD_Bridge_HideWidget(frameWidget);
			return;
		}

		int bulletCountInLimb = painManager.GetBulletCountInLimb(limb);
		if (bulletCountInLimb <= 0)
		{
			OMD_Bridge_HideWidget(frameWidget);
			return;
		}

		OMD_Bridge_ShowWidget(frameWidget);

		Widget counter1 = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_counter_1");
		Widget counter2 = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_counter_2");
		Widget counter3 = m_OMD_Bridge_BadgesWidgetsList.Get(frameName + "_counter_3");

		if (bulletCountInLimb >= 3)
		{
			OMD_Bridge_ShowWidget(counter3);
			OMD_Bridge_HideWidget(counter1);
			OMD_Bridge_HideWidget(counter2);
		}
		else if (bulletCountInLimb == 2)
		{
			OMD_Bridge_ShowWidget(counter2);
			OMD_Bridge_HideWidget(counter1);
			OMD_Bridge_HideWidget(counter3);
		}
		else
		{
			OMD_Bridge_ShowWidget(counter1);
			OMD_Bridge_HideWidget(counter2);
			OMD_Bridge_HideWidget(counter3);
		}
	}

	protected void OMD_Bridge_RenderScratchForLimb(PlayerBase player, string limb)
	{
		string frameKey = "scratch_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_BadgesWidgetsList.Get(frameKey);
		OMD_Bridge_HideWidget(frameWidget);
		OMD_Bridge_HideWidget(m_OMD_Bridge_BadgesWidgetsList.Get(frameKey + "_scratch"));
		OMD_Bridge_HideWidget(m_OMD_Bridge_BadgesWidgetsList.Get(frameKey + "_scratch_count"));

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager || !painManager.m_ShowPainBadges)
		{
			return;
		}

		int scratchCount = player.OMD_Bridge_CountLimbScratches(limb);
		if (scratchCount <= 0)
		{
			return;
		}

		if (!frameWidget)
		{
			return;
		}

		OMD_Bridge_ShowWidget(frameWidget);
		OMD_Bridge_ShowWidget(m_OMD_Bridge_BadgesWidgetsList.Get(frameKey + "_limb"));
		OMD_Bridge_ShowWidget(m_OMD_Bridge_BadgesWidgetsList.Get(frameKey + "_scratch"));

		TextWidget countWidget;
		if (!Class.CastTo(countWidget, m_OMD_Bridge_BadgesWidgetsList.Get(frameKey + "_scratch_count")))
		{
			return;
		}

		if (scratchCount > 1)
		{
			countWidget.SetText(scratchCount.ToString());
			OMD_Bridge_ShowWidget(countWidget);
		}
		else
		{
			OMD_Bridge_HideWidget(countWidget);
		}
	}

	protected void OMD_Bridge_RenderSutureForLimb(PlayerBase player, string limb)
	{
		string frameKey = "suture_" + limb + "_frame";
		Widget frameWidget = m_OMD_Bridge_BadgesWidgetsList.Get(frameKey);
		OMD_Bridge_HideWidget(frameWidget);
		OMD_Bridge_HideWidget(m_OMD_Bridge_BadgesWidgetsList.Get(frameKey + "_suture"));

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = player.InediaInfectedAI_GetPainManager();
		if (!painManager || !painManager.m_ShowPainBadges)
		{
			return;
		}

		if (!painManager.OMD_Bridge_IsLimbSutured(limb))
		{
			return;
		}

		if (!frameWidget)
		{
			return;
		}

		OMD_Bridge_ShowWidget(frameWidget);
		OMD_Bridge_ShowWidget(m_OMD_Bridge_BadgesWidgetsList.Get(frameKey + "_limb"));
		Widget sutureWidget = m_OMD_Bridge_BadgesWidgetsList.Get(frameKey + "_suture");
		OMD_Bridge_ShowWidget(sutureWidget);

		if (painManager.OMD_Bridge_IsSutureBandaged(limb))
		{
			if (painManager.OMD_Bridge_IsSutureBandageDirty(limb))
			{
				OMD_Bridge_LoadSutureBandageDirtyIcon(sutureWidget);
				OMD_Bridge_SetWidgetColor(sutureWidget, ARGB(255, 180, 90, 40));
			}
			else
			{
				OMD_Bridge_LoadSutureBandageCleanIcon(sutureWidget);
				OMD_Bridge_SetWidgetColor(sutureWidget, ARGB(255, 220, 220, 220));
			}
		}
		else
		{
			OMD_Bridge_LoadSutureIcon(sutureWidget);
			OMD_Bridge_SetWidgetColor(sutureWidget, ARGB(255, 255, 255, 255));
		}
	}

	protected void OMD_Bridge_LoadSutureBandageCleanIcon(Widget widget)
	{
		ImageWidget sutureImage;
		if (!Class.CastTo(sutureImage, widget))
		{
			return;
		}

		sutureImage.LoadImageFile(0, "set:TerjeMedicine_icon image:tm_bandagedclean_2");
	}

	protected void OMD_Bridge_LoadSutureBandageDirtyIcon(Widget widget)
	{
		ImageWidget sutureImage;
		if (!Class.CastTo(sutureImage, widget))
		{
			return;
		}

		sutureImage.LoadImageFile(0, "set:TerjeMedicine_icon image:tm_bandageddirty_2");
	}

	protected void OMD_Bridge_SwapInediaLimbs()
	{
		OMD_Bridge_SwapInediaLimb("arms", "OMD_Bridge/gui/badges/arm.paa");
		OMD_Bridge_SwapInediaLimb("legs", "OMD_Bridge/gui/badges/leg.paa");
	}

	protected void OMD_Bridge_SwapInediaLimb(string limb, string path)
	{
		OMD_Bridge_LoadListedLimb("pain_" + limb + "_frame_limb", path);
		OMD_Bridge_LoadListedLimb("deep_wound_" + limb + "_frame_limb", path);
		OMD_Bridge_LoadListedLimb("break_" + limb + "_frame_limb", path);

		string bulletKey = "bullet_" + limb + "_frame";
		if (!m_InediaInfectedAI_BadgesWidgetsList.Contains(bulletKey))
		{
			return;
		}

		Widget bulletFrame = m_InediaInfectedAI_BadgesWidgetsList.Get(bulletKey);
		if (!bulletFrame)
		{
			return;
		}

		OMD_Bridge_LoadLimbImage(bulletFrame.FindAnyWidget("Limb"), path);
	}

	protected void OMD_Bridge_LoadListedLimb(string key, string path)
	{
		if (!m_InediaInfectedAI_BadgesWidgetsList.Contains(key))
		{
			return;
		}

		OMD_Bridge_LoadLimbImage(m_InediaInfectedAI_BadgesWidgetsList.Get(key), path);
	}

	protected void OMD_Bridge_LoadLimbImage(Widget widget, string path)
	{
		ImageWidget image;
		if (!Class.CastTo(image, widget))
		{
			return;
		}

		image.LoadImageFile(0, path);
	}

	void OMD_Bridge_FlashBadgesWidgetsHandler(float pDt)
	{
		if ((GetGame().GetTickTime() - m_OMD_Bridge_FlashBadgesWidgetsHandlerLastTime) < 0.35)
		{
			return;
		}

		m_OMD_Bridge_FlashBadgesWidgetsHandlerLastTime = GetGame().GetTickTime();
		m_OMD_Bridge_FlashBadgesWidgetsHandlerFlashStatus = !m_OMD_Bridge_FlashBadgesWidgetsHandlerFlashStatus;

		foreach (string badgeWidgetName, bool isFlashing: m_OMD_Bridge_FlashBadgesWidgetsFlashStatus)
		{
			if (isFlashing)
			{
				Widget flashWidget = m_OMD_Bridge_BadgesWidgetsList.Get(badgeWidgetName);
				if (flashWidget)
				{
					flashWidget.Show(m_OMD_Bridge_FlashBadgesWidgetsHandlerFlashStatus);
				}
			}
		}
	}

	void OMD_Bridge_FlashBadgeWidget(string badgeWidgetName)
	{
		m_OMD_Bridge_FlashBadgesWidgetsFlashStatus.Set(badgeWidgetName, true);
	}

	void OMD_Bridge_EndFlashBadgeWidget(string badgeWidgetName)
	{
		m_OMD_Bridge_FlashBadgesWidgetsFlashStatus.Set(badgeWidgetName, false);
	}

	void OMD_Bridge_ShowWidget(Widget widget)
	{
		if (!widget)
		{
			return;
		}

		if (!widget.IsVisible())
		{
			widget.Show(true);
		}
	}

	void OMD_Bridge_HideWidget(Widget widget)
	{
		if (!widget)
		{
			return;
		}

		if (widget.IsVisible())
		{
			widget.Show(false);
		}
	}
};
#endif
