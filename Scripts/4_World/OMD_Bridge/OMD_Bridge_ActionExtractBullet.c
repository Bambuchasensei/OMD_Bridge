modded class InediaInfectedAI_ActionExtractBullet
{
	bool OMD_Bridge_ExtractBulletCondition(PlayerBase player, ActionTarget target, ItemBase item, bool hasTarget, string textKey)
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

		if (!player.InediaInfectedAI_GetPainManager().LimbsBulletSystemIsActive())
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
			int animationId = GetGame().ConfigGetInt("CfgVehicles " + item.GetType() + " InediaPain ExtractBulletItemActionAnimationId");
			if (animationId > 0)
			{
				m_CommandUID = animationId;
			}
			else
			{
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_STITCHUPSELF;
			}
		}

		m_Text = "#" + textKey;
		if (hasTarget)
		{
			m_Text = m_Text + " [#STR_inediainfectedai_other_player]";
		}

		if (!OMD_BridgeTreatment.CanExtractBulletOnLimb(targetPlayer, m_InediaInfectedAI_PainLimb))
		{
			return false;
		}

		if (targetPlayer.InediaInfectedAI_GetPainManager().IsLimbDeepWoundBandaged(m_InediaInfectedAI_PainLimb))
		{
			return false;
		}

		return true;
	}

	bool OMD_Bridge_ExtractBulletStillValid(ActionData action_data)
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

		if (!OMD_BridgeTreatment.CanExtractBulletOnLimb(targetPlayer, m_InediaInfectedAI_PainLimb))
		{
			return false;
		}

		if (targetPlayer.InediaInfectedAI_GetPainManager().IsLimbDeepWoundBandaged(m_InediaInfectedAI_PainLimb))
		{
			return false;
		}

		return true;
	}
};

class OMD_Bridge_ActionExtractBulletHandsSelf: InediaInfectedAI_ActionExtractBulletSelf
{
	void OMD_Bridge_ActionExtractBulletHandsSelf()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_ExtractBulletCondition(player, target, item, false, "STR_OMD_Bridge_ExtractBulletHands");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_ExtractBulletStillValid(action_data);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_ExtractBulletStillValid(action_data))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionExtractBulletHandsTarget: InediaInfectedAI_ActionExtractBulletTarget
{
	void OMD_Bridge_ActionExtractBulletHandsTarget()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_ExtractBulletCondition(player, target, item, true, "STR_OMD_Bridge_ExtractBulletHands");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_ExtractBulletStillValid(action_data);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_ExtractBulletStillValid(action_data))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionExtractBulletFeetSelf: InediaInfectedAI_ActionExtractBulletSelf
{
	void OMD_Bridge_ActionExtractBulletFeetSelf()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_ExtractBulletCondition(player, target, item, false, "STR_OMD_Bridge_ExtractBulletFeet");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_ExtractBulletStillValid(action_data);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_ExtractBulletStillValid(action_data))
		{
			return;
		}

		super.OnFinishProgressServer(action_data);
	}
};

class OMD_Bridge_ActionExtractBulletFeetTarget: InediaInfectedAI_ActionExtractBulletTarget
{
	void OMD_Bridge_ActionExtractBulletFeetTarget()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return OMD_Bridge_ExtractBulletCondition(player, target, item, true, "STR_OMD_Bridge_ExtractBulletFeet");
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		return OMD_Bridge_ExtractBulletStillValid(action_data);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!OMD_Bridge_ExtractBulletStillValid(action_data))
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
		actions.Insert(OMD_Bridge_ActionExtractBulletHandsSelf);
		actions.Insert(OMD_Bridge_ActionExtractBulletHandsTarget);
		actions.Insert(OMD_Bridge_ActionExtractBulletFeetSelf);
		actions.Insert(OMD_Bridge_ActionExtractBulletFeetTarget);
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

		if (m_InediaInfectedAI_IsExtractBulletItem == 1)
		{
			AddAction(OMD_Bridge_ActionExtractBulletHandsSelf);
			AddAction(OMD_Bridge_ActionExtractBulletFeetSelf);
			AddAction(OMD_Bridge_ActionExtractBulletHandsTarget);
			AddAction(OMD_Bridge_ActionExtractBulletFeetTarget);
		}
	}
};
