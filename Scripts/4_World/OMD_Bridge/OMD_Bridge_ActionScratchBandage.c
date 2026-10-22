class OMD_Bridge_ActionScratchBandageCB: ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(3);
	}
};

class OMD_Bridge_ActionScratchBandage: ActionContinuousBase
{
	string m_OMD_Bridge_PainLimb;
	string m_OMD_Bridge_TextKey;

	void OMD_Bridge_ActionScratchBandage()
	{
		m_CallbackClass = OMD_Bridge_ActionScratchBandageCB;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchTorso";

		if (!HasTarget())
		{
			m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
		}
		else
		{
			m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
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

		if (!player || !item)
		{
			return false;
		}

		if (!OMD_BridgeTreatment.ItemAllowsScratch(item))
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

		return OMD_BridgeTreatment.CanScratchBandageOnLimb(targetPlayer, m_OMD_Bridge_PainLimb);
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

		return OMD_BridgeTreatment.CanScratchBandageOnLimb(targetPlayer, m_OMD_Bridge_PainLimb);
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

		if (!OMD_BridgeTreatment.TryApplyScratchOnLimb(action_data.m_MainItem, targetPlayer, m_OMD_Bridge_PainLimb))
		{
			return;
		}

		OMD_BridgeTreatment.AddMedicineBandageExp(action_data.m_Player);
		OMD_BridgeTreatment.ConsumeBandageItem(action_data.m_MainItem);
	}
};

class OMD_Bridge_ActionScratchBandageSelf: OMD_Bridge_ActionScratchBandage
{
	override bool HasTarget()
	{
		return false;
	}
};

class OMD_Bridge_ActionScratchBandageTarget: OMD_Bridge_ActionScratchBandage
{
	override bool HasTarget()
	{
		return true;
	}
};

class OMD_Bridge_ActionScratchBandageTorsoSelf: OMD_Bridge_ActionScratchBandageSelf
{
	void OMD_Bridge_ActionScratchBandageTorsoSelf()
	{
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchTorso";
	}
};

class OMD_Bridge_ActionScratchBandageTorsoTarget: OMD_Bridge_ActionScratchBandageTarget
{
	void OMD_Bridge_ActionScratchBandageTorsoTarget()
	{
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchTorso";
	}
};

class OMD_Bridge_ActionScratchBandageHeadSelf: OMD_Bridge_ActionScratchBandageSelf
{
	void OMD_Bridge_ActionScratchBandageHeadSelf()
	{
		m_OMD_Bridge_PainLimb = "head";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchHead";
	}
};

class OMD_Bridge_ActionScratchBandageHeadTarget: OMD_Bridge_ActionScratchBandageTarget
{
	void OMD_Bridge_ActionScratchBandageHeadTarget()
	{
		m_OMD_Bridge_PainLimb = "head";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchHead";
	}
};

class OMD_Bridge_ActionScratchBandageArmsSelf: OMD_Bridge_ActionScratchBandageSelf
{
	void OMD_Bridge_ActionScratchBandageArmsSelf()
	{
		m_OMD_Bridge_PainLimb = "arms";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchArms";
	}
};

class OMD_Bridge_ActionScratchBandageArmsTarget: OMD_Bridge_ActionScratchBandageTarget
{
	void OMD_Bridge_ActionScratchBandageArmsTarget()
	{
		m_OMD_Bridge_PainLimb = "arms";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchArms";
	}
};

class OMD_Bridge_ActionScratchBandageHandsSelf: OMD_Bridge_ActionScratchBandageSelf
{
	void OMD_Bridge_ActionScratchBandageHandsSelf()
	{
		m_OMD_Bridge_PainLimb = "hands";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchHands";
	}
};

class OMD_Bridge_ActionScratchBandageHandsTarget: OMD_Bridge_ActionScratchBandageTarget
{
	void OMD_Bridge_ActionScratchBandageHandsTarget()
	{
		m_OMD_Bridge_PainLimb = "hands";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchHands";
	}
};

class OMD_Bridge_ActionScratchBandageLegsSelf: OMD_Bridge_ActionScratchBandageSelf
{
	void OMD_Bridge_ActionScratchBandageLegsSelf()
	{
		m_OMD_Bridge_PainLimb = "legs";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchLegs";
	}
};

class OMD_Bridge_ActionScratchBandageLegsTarget: OMD_Bridge_ActionScratchBandageTarget
{
	void OMD_Bridge_ActionScratchBandageLegsTarget()
	{
		m_OMD_Bridge_PainLimb = "legs";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchLegs";
	}
};

class OMD_Bridge_ActionScratchBandageFeetSelf: OMD_Bridge_ActionScratchBandageSelf
{
	void OMD_Bridge_ActionScratchBandageFeetSelf()
	{
		m_OMD_Bridge_PainLimb = "feet";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchFeet";
	}
};

class OMD_Bridge_ActionScratchBandageFeetTarget: OMD_Bridge_ActionScratchBandageTarget
{
	void OMD_Bridge_ActionScratchBandageFeetTarget()
	{
		m_OMD_Bridge_PainLimb = "feet";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_ScratchFeet";
	}
};

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(OMD_Bridge_ActionScratchBandageTorsoSelf);
		actions.Insert(OMD_Bridge_ActionScratchBandageTorsoTarget);
		actions.Insert(OMD_Bridge_ActionScratchBandageHeadSelf);
		actions.Insert(OMD_Bridge_ActionScratchBandageHeadTarget);
		actions.Insert(OMD_Bridge_ActionScratchBandageArmsSelf);
		actions.Insert(OMD_Bridge_ActionScratchBandageArmsTarget);
		actions.Insert(OMD_Bridge_ActionScratchBandageHandsSelf);
		actions.Insert(OMD_Bridge_ActionScratchBandageHandsTarget);
		actions.Insert(OMD_Bridge_ActionScratchBandageLegsSelf);
		actions.Insert(OMD_Bridge_ActionScratchBandageLegsTarget);
		actions.Insert(OMD_Bridge_ActionScratchBandageFeetSelf);
		actions.Insert(OMD_Bridge_ActionScratchBandageFeetTarget);
	}
};
