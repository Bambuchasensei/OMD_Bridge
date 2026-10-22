class OMD_Bridge_ActionDisinfectSutureCB: ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DEFAULT);
	}
};

class OMD_Bridge_ActionDisinfectSutureBase: ActionDisinfectBase
{
	string m_OMD_Bridge_PainLimb;
	string m_OMD_Bridge_TextKey;

	void OMD_Bridge_ActionDisinfectSutureBase()
	{
		m_CallbackClass = OMD_Bridge_ActionDisinfectSutureCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureTorso";

		if (!HasTarget())
		{
			m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_STITCHUPSELF;
		}
		else
		{
			m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		}
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined();

		if (!HasTarget())
		{
			m_ConditionTarget = new CCTSelf();
		}
		else
		{
			m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		}
	}

	PlayerBase OMD_Bridge_GetTargetPlayer(PlayerBase player, ActionTarget target)
	{
		if (!HasTarget())
		{
			return player;
		}

		if (!target)
		{
			return null;
		}

		return PlayerBase.Cast(target.GetObject());
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!OMD_BridgeConfig.IsActive())
		{
			return false;
		}

		if (!OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			return false;
		}

		if (!player || !item)
		{
			return false;
		}

		if (!OMD_BridgeTreatment.IsSutureDisinfectantItem(item))
		{
			return false;
		}

		PlayerBase targetPlayer = OMD_Bridge_GetTargetPlayer(player, target);
		if (!targetPlayer || !targetPlayer.IsAlive())
		{
			return false;
		}

		m_Text = "#" + m_OMD_Bridge_TextKey;
		if (HasTarget())
		{
			m_Text = m_Text + " [#STR_inediainfectedai_other_player]";
		}

		return OMD_BridgeTreatment.CanDisinfectSutureOnLimb(targetPlayer, m_OMD_Bridge_PainLimb);
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		if (!action_data)
		{
			return false;
		}

		PlayerBase targetPlayer = OMD_Bridge_GetTargetPlayer(action_data.m_Player, action_data.m_Target);
		if (!targetPlayer)
		{
			return false;
		}

		return OMD_BridgeTreatment.CanDisinfectSutureOnLimb(targetPlayer, m_OMD_Bridge_PainLimb);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!GetGame().IsServer())
		{
			return;
		}

		if (!action_data || !action_data.m_MainItem || !action_data.m_Player)
		{
			return;
		}

		PlayerBase targetPlayer = OMD_Bridge_GetTargetPlayer(action_data.m_Player, action_data.m_Target);
		if (!targetPlayer)
		{
			return;
		}

		if (HasTarget())
		{
			if (!CanReceiveAction(action_data.m_Target))
			{
				return;
			}
		}

		if (!OMD_BridgeTreatment.TryDisinfectSutureBandageOnLimb(action_data.m_MainItem, targetPlayer, m_OMD_Bridge_PainLimb))
		{
			return;
		}

		Apply(action_data);
	}
};

class OMD_Bridge_ActionDisinfectSutureSelf: OMD_Bridge_ActionDisinfectSutureBase
{
	override bool HasTarget()
	{
		return false;
	}
};

class OMD_Bridge_ActionDisinfectSutureTarget: OMD_Bridge_ActionDisinfectSutureBase
{
	override bool HasTarget()
	{
		return true;
	}
};

class OMD_Bridge_ActionDisinfectSutureTorsoSelf: OMD_Bridge_ActionDisinfectSutureSelf
{
	void OMD_Bridge_ActionDisinfectSutureTorsoSelf()
	{
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureTorso";
	}
};

class OMD_Bridge_ActionDisinfectSutureTorsoTarget: OMD_Bridge_ActionDisinfectSutureTarget
{
	void OMD_Bridge_ActionDisinfectSutureTorsoTarget()
	{
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureTorso";
	}
};

class OMD_Bridge_ActionDisinfectSutureHeadSelf: OMD_Bridge_ActionDisinfectSutureSelf
{
	void OMD_Bridge_ActionDisinfectSutureHeadSelf()
	{
		m_OMD_Bridge_PainLimb = "head";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureHead";
	}
};

class OMD_Bridge_ActionDisinfectSutureHeadTarget: OMD_Bridge_ActionDisinfectSutureTarget
{
	void OMD_Bridge_ActionDisinfectSutureHeadTarget()
	{
		m_OMD_Bridge_PainLimb = "head";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureHead";
	}
};

class OMD_Bridge_ActionDisinfectSutureArmsSelf: OMD_Bridge_ActionDisinfectSutureSelf
{
	void OMD_Bridge_ActionDisinfectSutureArmsSelf()
	{
		m_OMD_Bridge_PainLimb = "arms";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureArms";
	}
};

class OMD_Bridge_ActionDisinfectSutureArmsTarget: OMD_Bridge_ActionDisinfectSutureTarget
{
	void OMD_Bridge_ActionDisinfectSutureArmsTarget()
	{
		m_OMD_Bridge_PainLimb = "arms";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureArms";
	}
};

class OMD_Bridge_ActionDisinfectSutureHandsSelf: OMD_Bridge_ActionDisinfectSutureSelf
{
	void OMD_Bridge_ActionDisinfectSutureHandsSelf()
	{
		m_OMD_Bridge_PainLimb = "hands";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureHands";
	}
};

class OMD_Bridge_ActionDisinfectSutureHandsTarget: OMD_Bridge_ActionDisinfectSutureTarget
{
	void OMD_Bridge_ActionDisinfectSutureHandsTarget()
	{
		m_OMD_Bridge_PainLimb = "hands";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureHands";
	}
};

class OMD_Bridge_ActionDisinfectSutureLegsSelf: OMD_Bridge_ActionDisinfectSutureSelf
{
	void OMD_Bridge_ActionDisinfectSutureLegsSelf()
	{
		m_OMD_Bridge_PainLimb = "legs";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureLegs";
	}
};

class OMD_Bridge_ActionDisinfectSutureLegsTarget: OMD_Bridge_ActionDisinfectSutureTarget
{
	void OMD_Bridge_ActionDisinfectSutureLegsTarget()
	{
		m_OMD_Bridge_PainLimb = "legs";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureLegs";
	}
};

class OMD_Bridge_ActionDisinfectSutureFeetSelf: OMD_Bridge_ActionDisinfectSutureSelf
{
	void OMD_Bridge_ActionDisinfectSutureFeetSelf()
	{
		m_OMD_Bridge_PainLimb = "feet";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureFeet";
	}
};

class OMD_Bridge_ActionDisinfectSutureFeetTarget: OMD_Bridge_ActionDisinfectSutureTarget
{
	void OMD_Bridge_ActionDisinfectSutureFeetTarget()
	{
		m_OMD_Bridge_PainLimb = "feet";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_DisinfectSutureFeet";
	}
};

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureTorsoSelf);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureTorsoTarget);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureHeadSelf);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureHeadTarget);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureArmsSelf);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureArmsTarget);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureHandsSelf);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureHandsTarget);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureLegsSelf);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureLegsTarget);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureFeetSelf);
		actions.Insert(OMD_Bridge_ActionDisinfectSutureFeetTarget);
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

		if (!OMD_BridgeTreatment.IsSutureDisinfectantItem(this))
		{
			return;
		}

		AddAction(OMD_Bridge_ActionDisinfectSutureTorsoSelf);
		AddAction(OMD_Bridge_ActionDisinfectSutureHeadSelf);
		AddAction(OMD_Bridge_ActionDisinfectSutureArmsSelf);
		AddAction(OMD_Bridge_ActionDisinfectSutureHandsSelf);
		AddAction(OMD_Bridge_ActionDisinfectSutureLegsSelf);
		AddAction(OMD_Bridge_ActionDisinfectSutureFeetSelf);
		AddAction(OMD_Bridge_ActionDisinfectSutureTorsoTarget);
		AddAction(OMD_Bridge_ActionDisinfectSutureHeadTarget);
		AddAction(OMD_Bridge_ActionDisinfectSutureArmsTarget);
		AddAction(OMD_Bridge_ActionDisinfectSutureHandsTarget);
		AddAction(OMD_Bridge_ActionDisinfectSutureLegsTarget);
		AddAction(OMD_Bridge_ActionDisinfectSutureFeetTarget);
	}
};
