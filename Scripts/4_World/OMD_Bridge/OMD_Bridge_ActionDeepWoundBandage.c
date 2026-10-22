modded class InediaInfectedAI_ActionDeepWoundBandage
{
	bool OMD_Bridge_DeepWoundBandageCondition(PlayerBase player, ActionTarget target, ItemBase item, bool hasTarget, int requiredTier, string textKey)
	{
		PlayerBase targetPlayer;
		if (!hasTarget)
		{
			targetPlayer = player;
		}
		else
		{
			if (target)
			{
				targetPlayer = PlayerBase.Cast(target.GetObject());
			}
		}

		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		if (!player || !player.InediaInfectedAI_GetPainManager())
		{
			return false;
		}

		if (!player.InediaInfectedAI_GetPainManager().LimbsDeepWoundSystemIsActive())
		{
			return false;
		}

		if (!targetPlayer || !targetPlayer.IsAlive())
		{
			return false;
		}

		if (!item)
		{
			return false;
		}

		if (!OMD_BridgeTreatment.ItemAllowsDeepWoundBandage(item))
		{
			return false;
		}

		if (!hasTarget)
		{
			int animationId = GetGame().ConfigGetInt("CfgVehicles " + item.GetType() + " InediaPain DeepWoundBandageItemActionAnimationId");
			if (animationId > 0)
			{
				m_CommandUID = animationId;
			}
			else
			{
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
			}
		}

		m_Text = "#" + textKey;
		if (hasTarget)
		{
			m_Text = m_Text + " [#STR_inediainfectedai_other_player]";
		}

		if (!OMD_BridgeTreatment.CanDeepWoundBandageOnLimb(targetPlayer, m_InediaInfectedAI_PainLimb, requiredTier))
		{
			return false;
		}

		return true;
	}

	bool OMD_Bridge_DeepWoundBandageStillValid(ActionData action_data, int requiredTier)
	{
		if (!action_data)
		{
			return false;
		}

		PlayerBase targetPlayer;
		if (!HasTarget())
		{
			targetPlayer = action_data.m_Player;
		}
		else
		{
			if (action_data.m_Target)
			{
				targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
			}
		}

		if (!targetPlayer)
		{
			return false;
		}

		return OMD_BridgeTreatment.CanDeepWoundBandageOnLimb(targetPlayer, m_InediaInfectedAI_PainLimb, requiredTier);
	}
};

class OMD_Bridge_ActionDeepWoundBandageHeavyHandsSelf: InediaInfectedAI_ActionDeepWoundBandageSelf
{
	void OMD_Bridge_ActionDeepWoundBandageHeavyHandsSelf()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, false, 3, "STR_OMD_Bridge_BandageDeepWoundHeavyHands");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 3);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 3))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageHeavyHandsTarget: InediaInfectedAI_ActionDeepWoundBandageTarget
{
	void OMD_Bridge_ActionDeepWoundBandageHeavyHandsTarget()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, true, 3, "STR_OMD_Bridge_BandageDeepWoundHeavyHands");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 3);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 3))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageHeavyFeetSelf: InediaInfectedAI_ActionDeepWoundBandageSelf
{
	void OMD_Bridge_ActionDeepWoundBandageHeavyFeetSelf()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, false, 3, "STR_OMD_Bridge_BandageDeepWoundHeavyFeet");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 3);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 3))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageHeavyFeetTarget: InediaInfectedAI_ActionDeepWoundBandageTarget
{
	void OMD_Bridge_ActionDeepWoundBandageHeavyFeetTarget()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, true, 3, "STR_OMD_Bridge_BandageDeepWoundHeavyFeet");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 3);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 3))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageMediumHandsSelf: InediaInfectedAI_ActionDeepWoundBandageSelf
{
	void OMD_Bridge_ActionDeepWoundBandageMediumHandsSelf()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, false, 2, "STR_OMD_Bridge_BandageDeepWoundMediumHands");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 2);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 2))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageMediumHandsTarget: InediaInfectedAI_ActionDeepWoundBandageTarget
{
	void OMD_Bridge_ActionDeepWoundBandageMediumHandsTarget()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, true, 2, "STR_OMD_Bridge_BandageDeepWoundMediumHands");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 2);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 2))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageMediumFeetSelf: InediaInfectedAI_ActionDeepWoundBandageSelf
{
	void OMD_Bridge_ActionDeepWoundBandageMediumFeetSelf()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, false, 2, "STR_OMD_Bridge_BandageDeepWoundMediumFeet");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 2);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 2))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageMediumFeetTarget: InediaInfectedAI_ActionDeepWoundBandageTarget
{
	void OMD_Bridge_ActionDeepWoundBandageMediumFeetTarget()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, true, 2, "STR_OMD_Bridge_BandageDeepWoundMediumFeet");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 2);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 2))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageLightHandsSelf: InediaInfectedAI_ActionDeepWoundBandageSelf
{
	void OMD_Bridge_ActionDeepWoundBandageLightHandsSelf()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, false, 1, "STR_OMD_Bridge_BandageDeepWoundLightHands");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 1);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 1))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageLightHandsTarget: InediaInfectedAI_ActionDeepWoundBandageTarget
{
	void OMD_Bridge_ActionDeepWoundBandageLightHandsTarget()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, true, 1, "STR_OMD_Bridge_BandageDeepWoundLightHands");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 1);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 1))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageLightFeetSelf: InediaInfectedAI_ActionDeepWoundBandageSelf
{
	void OMD_Bridge_ActionDeepWoundBandageLightFeetSelf()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, false, 1, "STR_OMD_Bridge_BandageDeepWoundLightFeet");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 1);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 1))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionDeepWoundBandageLightFeetTarget: InediaInfectedAI_ActionDeepWoundBandageTarget
{
	void OMD_Bridge_ActionDeepWoundBandageLightFeetTarget()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_DeepWoundBandageCondition(player, target, item, true, 1, "STR_OMD_Bridge_BandageDeepWoundLightFeet");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_DeepWoundBandageStillValid(action_data, 1);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_DeepWoundBandageStillValid(action_data, 1))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageHeavyHandsSelf);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageHeavyHandsTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageHeavyFeetSelf);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageHeavyFeetTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageMediumHandsSelf);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageMediumHandsTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageMediumFeetSelf);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageMediumFeetTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageLightHandsSelf);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageLightHandsTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageLightFeetSelf);
		actions.Insert(OMD_Bridge_ActionDeepWoundBandageLightFeetTarget);
	}
};

modded class ItemBase
{
	override void InediaInfectedAI_SetActions()
	{
		super.InediaInfectedAI_SetActions();

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (m_InediaInfectedAI_IsDeepWoundBandageItem == 1 || OMD_BridgeTreatment.ItemAllowsDeepWoundBandage(this))
		{
			AddAction(OMD_Bridge_ActionDeepWoundBandageHeavyHandsSelf);
			AddAction(OMD_Bridge_ActionDeepWoundBandageHeavyFeetSelf);
			AddAction(OMD_Bridge_ActionDeepWoundBandageHeavyHandsTarget);
			AddAction(OMD_Bridge_ActionDeepWoundBandageHeavyFeetTarget);
			AddAction(OMD_Bridge_ActionDeepWoundBandageMediumHandsSelf);
			AddAction(OMD_Bridge_ActionDeepWoundBandageMediumFeetSelf);
			AddAction(OMD_Bridge_ActionDeepWoundBandageMediumHandsTarget);
			AddAction(OMD_Bridge_ActionDeepWoundBandageMediumFeetTarget);
			AddAction(OMD_Bridge_ActionDeepWoundBandageLightHandsSelf);
			AddAction(OMD_Bridge_ActionDeepWoundBandageLightFeetSelf);
			AddAction(OMD_Bridge_ActionDeepWoundBandageLightHandsTarget);
			AddAction(OMD_Bridge_ActionDeepWoundBandageLightFeetTarget);
		}

		if (OMD_BridgeTreatment.ItemAllowsDeepWoundBandage(this) && OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			AddAction(OMD_Bridge_ActionSutureBandageTorsoSelf);
			AddAction(OMD_Bridge_ActionSutureBandageHeadSelf);
			AddAction(OMD_Bridge_ActionSutureBandageArmsSelf);
			AddAction(OMD_Bridge_ActionSutureBandageHandsSelf);
			AddAction(OMD_Bridge_ActionSutureBandageLegsSelf);
			AddAction(OMD_Bridge_ActionSutureBandageFeetSelf);
			AddAction(OMD_Bridge_ActionSutureBandageTorsoTarget);
			AddAction(OMD_Bridge_ActionSutureBandageHeadTarget);
			AddAction(OMD_Bridge_ActionSutureBandageArmsTarget);
			AddAction(OMD_Bridge_ActionSutureBandageHandsTarget);
			AddAction(OMD_Bridge_ActionSutureBandageLegsTarget);
			AddAction(OMD_Bridge_ActionSutureBandageFeetTarget);
			AddAction(OMD_Bridge_ActionSutureDirtyTorsoSelf);
			AddAction(OMD_Bridge_ActionSutureDirtyHeadSelf);
			AddAction(OMD_Bridge_ActionSutureDirtyArmsSelf);
			AddAction(OMD_Bridge_ActionSutureDirtyHandsSelf);
			AddAction(OMD_Bridge_ActionSutureDirtyLegsSelf);
			AddAction(OMD_Bridge_ActionSutureDirtyFeetSelf);
			AddAction(OMD_Bridge_ActionSutureDirtyTorsoTarget);
			AddAction(OMD_Bridge_ActionSutureDirtyHeadTarget);
			AddAction(OMD_Bridge_ActionSutureDirtyArmsTarget);
			AddAction(OMD_Bridge_ActionSutureDirtyHandsTarget);
			AddAction(OMD_Bridge_ActionSutureDirtyLegsTarget);
			AddAction(OMD_Bridge_ActionSutureDirtyFeetTarget);
		}

		if (OMD_BridgeTreatment.ItemAllowsScratch(this))
		{
			AddAction(OMD_Bridge_ActionScratchBandageTorsoSelf);
			AddAction(OMD_Bridge_ActionScratchBandageHeadSelf);
			AddAction(OMD_Bridge_ActionScratchBandageArmsSelf);
			AddAction(OMD_Bridge_ActionScratchBandageHandsSelf);
			AddAction(OMD_Bridge_ActionScratchBandageLegsSelf);
			AddAction(OMD_Bridge_ActionScratchBandageFeetSelf);
			AddAction(OMD_Bridge_ActionScratchBandageTorsoTarget);
			AddAction(OMD_Bridge_ActionScratchBandageHeadTarget);
			AddAction(OMD_Bridge_ActionScratchBandageArmsTarget);
			AddAction(OMD_Bridge_ActionScratchBandageHandsTarget);
			AddAction(OMD_Bridge_ActionScratchBandageLegsTarget);
			AddAction(OMD_Bridge_ActionScratchBandageFeetTarget);
		}
	}
};
