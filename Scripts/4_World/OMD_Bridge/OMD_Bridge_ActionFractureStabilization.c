class OMD_Bridge_ActionFractureStabilizationHandsSelf: InediaInfectedAI_ActionFractureStabilizationSelf
{
	void OMD_Bridge_ActionFractureStabilizationHandsSelf()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		return OMD_Bridge_FractureStabilizationCondition(player, target, item, false);
	}
};

class OMD_Bridge_ActionFractureStabilizationHandsTarget: InediaInfectedAI_ActionFractureStabilizationTarget
{
	void OMD_Bridge_ActionFractureStabilizationHandsTarget()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		return OMD_Bridge_FractureStabilizationCondition(player, target, item, true);
	}
};

class OMD_Bridge_ActionFractureStabilizationFeetSelf: InediaInfectedAI_ActionFractureStabilizationSelf
{
	void OMD_Bridge_ActionFractureStabilizationFeetSelf()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		return OMD_Bridge_FractureStabilizationCondition(player, target, item, false);
	}
};

class OMD_Bridge_ActionFractureStabilizationFeetTarget: InediaInfectedAI_ActionFractureStabilizationTarget
{
	void OMD_Bridge_ActionFractureStabilizationFeetTarget()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		return OMD_Bridge_FractureStabilizationCondition(player, target, item, true);
	}
};

modded class InediaInfectedAI_ActionFractureStabilization
{
	bool OMD_Bridge_FractureStabilizationCondition(PlayerBase player, ActionTarget target, ItemBase item, bool hasTarget)
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

		if (!player || !player.InediaInfectedAI_GetPainManager().LimbsBreakSystemIsActive())
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

		if (!hasTarget)
		{
			int animationId = GetGame().ConfigGetInt("CfgVehicles " + item.GetType() + " InediaPain FractureStabilizationItemActionAnimationId");
			if (animationId > 0)
			{
				m_CommandUID = animationId;
			}
			else
			{
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
			}
		}

		m_InediaInfectedAI_Text = "[#STR_inediainfectedai_" + m_InediaInfectedAI_PainLimb + "]";
		if (hasTarget)
		{
			m_InediaInfectedAI_Text = m_InediaInfectedAI_Text + " [#STR_inediainfectedai_other_player]";
		}

		string actionText;
		GetGame().ConfigGetText("CfgVehicles " + item.GetType() + " InediaPain FractureStabilizationItemActionText", actionText);
		if (actionText != "")
		{
			m_InediaInfectedAI_Text = m_InediaInfectedAI_Text + " " + actionText;
		}
		else
		{
			m_InediaInfectedAI_Text = m_InediaInfectedAI_Text + " #STR_inediainfectedai_stabilize_break";
		}

		string tips = "";
		if (targetPlayer.InediaInfectedAI_GetPainManager().m_ShowMedicationInfo && GetGame().ConfigGetInt("CfgVehicles " + item.GetType() + " InediaPain ShowTips") == 1)
		{
			float shockReductionMultiplier = GetGame().ConfigGetFloat("CfgVehicles " + item.GetType() + " InediaPain FractureStabilizationItemShockReductionMultiplier");
			if (shockReductionMultiplier < 1)
			{
				shockReductionMultiplier = 1;
			}

			if (shockReductionMultiplier > 1)
			{
				tips = tips + " [#STR_inediainfectedai_shock_reduction: x" + shockReductionMultiplier + "]";
			}

			float regenerationMultiplier = GetGame().ConfigGetFloat("CfgVehicles " + item.GetType() + " InediaPain FractureStabilizationItemRegenerationMultiplier");
			if (regenerationMultiplier < 1)
			{
				regenerationMultiplier = 1;
			}

			if (regenerationMultiplier > 1)
			{
				tips = tips + " [#STR_inediainfectedai_regeneration_bone: x" + regenerationMultiplier + "]";
			}
		}

		m_Text = m_InediaInfectedAI_Text + tips;

		if (!targetPlayer.InediaInfectedAI_GetPainManager().IsLimbBroken(m_InediaInfectedAI_PainLimb))
		{
			return false;
		}

		if (targetPlayer.InediaInfectedAI_GetPainManager().IsLimbStabilized(m_InediaInfectedAI_PainLimb))
		{
			return false;
		}

		return true;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);

		if (!OMD_BridgeConfig.IsActive() || !OMD_BridgeConfig.IsDebugEnabled())
		{
			return;
		}

		if (!action_data)
		{
			return;
		}

		Print("[OMD_Bridge] splint applied limb=" + m_InediaInfectedAI_PainLimb);
	}
};

class OMD_Bridge_ActionFractureUnstabilizationHandsSelf: InediaInfectedAI_ActionFractureUnstabilizationSelf
{
	void OMD_Bridge_ActionFractureUnstabilizationHandsSelf()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		return super.ActionCondition(player, target, item);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);

		if (OMD_BridgeConfig.IsActive() && OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] splint removed limb=hands");
		}
	}
};

class OMD_Bridge_ActionFractureUnstabilizationHandsTarget: InediaInfectedAI_ActionFractureUnstabilizationTarget
{
	void OMD_Bridge_ActionFractureUnstabilizationHandsTarget()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		return super.ActionCondition(player, target, item);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);

		if (OMD_BridgeConfig.IsActive() && OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] splint removed limb=hands");
		}
	}
};

class OMD_Bridge_ActionFractureUnstabilizationFeetSelf: InediaInfectedAI_ActionFractureUnstabilizationSelf
{
	void OMD_Bridge_ActionFractureUnstabilizationFeetSelf()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		return super.ActionCondition(player, target, item);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);

		if (OMD_BridgeConfig.IsActive() && OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] splint removed limb=feet");
		}
	}
};

class OMD_Bridge_ActionFractureUnstabilizationFeetTarget: InediaInfectedAI_ActionFractureUnstabilizationTarget
{
	void OMD_Bridge_ActionFractureUnstabilizationFeetTarget()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		return super.ActionCondition(player, target, item);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);

		if (OMD_BridgeConfig.IsActive() && OMD_BridgeConfig.IsDebugEnabled())
		{
			Print("[OMD_Bridge] splint removed limb=feet");
		}
	}
};

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(OMD_Bridge_ActionFractureStabilizationHandsTarget);
		actions.Insert(OMD_Bridge_ActionFractureStabilizationHandsSelf);
		actions.Insert(OMD_Bridge_ActionFractureStabilizationFeetTarget);
		actions.Insert(OMD_Bridge_ActionFractureStabilizationFeetSelf);
		actions.Insert(OMD_Bridge_ActionFractureUnstabilizationHandsTarget);
		actions.Insert(OMD_Bridge_ActionFractureUnstabilizationHandsSelf);
		actions.Insert(OMD_Bridge_ActionFractureUnstabilizationFeetTarget);
		actions.Insert(OMD_Bridge_ActionFractureUnstabilizationFeetSelf);
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

		if (m_InediaInfectedAI_IsFractureStabilizationItem == 1)
		{
			AddAction(OMD_Bridge_ActionFractureStabilizationHandsSelf);
			AddAction(OMD_Bridge_ActionFractureStabilizationFeetSelf);
			AddAction(OMD_Bridge_ActionFractureStabilizationHandsTarget);
			AddAction(OMD_Bridge_ActionFractureStabilizationFeetTarget);
		}
	}
};
