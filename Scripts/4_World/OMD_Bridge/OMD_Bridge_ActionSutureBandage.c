class OMD_Bridge_ActionSutureBandageCB: ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(3);
	}
};

class OMD_Bridge_ActionSutureBandageBase: ActionContinuousBase
{
	string m_OMD_Bridge_PainLimb;
	string m_OMD_Bridge_TextKey;
	bool m_OMD_Bridge_DirtyOnly;

	void OMD_Bridge_ActionSutureBandageBase()
	{
		m_CallbackClass = OMD_Bridge_ActionSutureBandageCB;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageTorso";
		m_OMD_Bridge_DirtyOnly = false;

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

	bool OMD_Bridge_CanApplyOnLimb(PlayerBase targetPlayer)
	{
		if (m_OMD_Bridge_DirtyOnly)
		{
			return OMD_BridgeTreatment.CanDirtySutureBandageOnLimb(targetPlayer, m_OMD_Bridge_PainLimb);
		}

		return OMD_BridgeTreatment.CanSutureBandageOnLimb(targetPlayer, m_OMD_Bridge_PainLimb);
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

		if (!OMD_BridgeTreatment.ItemAllowsDeepWoundBandage(item))
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

		return OMD_Bridge_CanApplyOnLimb(targetPlayer);
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

		return OMD_Bridge_CanApplyOnLimb(targetPlayer);
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

		bool applied = false;
		if (m_OMD_Bridge_DirtyOnly)
		{
			applied = OMD_BridgeTreatment.TryApplySutureDirtyOnLimb(action_data.m_MainItem, targetPlayer, m_OMD_Bridge_PainLimb);
		}
		else
		{
			applied = OMD_BridgeTreatment.TryApplySutureUnbandagedOnLimb(action_data.m_MainItem, targetPlayer, m_OMD_Bridge_PainLimb);
		}

		if (!applied)
		{
			return;
		}

		OMD_BridgeTreatment.AddMedicineBandageExp(action_data.m_Player);
		OMD_BridgeTreatment.ConsumeBandageItem(action_data.m_MainItem);
	}
};

class OMD_Bridge_ActionSutureBandageSelf: OMD_Bridge_ActionSutureBandageBase
{
	override bool HasTarget()
	{
		return false;
	}
};

class OMD_Bridge_ActionSutureBandageTarget: OMD_Bridge_ActionSutureBandageBase
{
	override bool HasTarget()
	{
		return true;
	}
};

class OMD_Bridge_ActionSutureBandageTorsoSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureBandageTorsoSelf()
	{
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageTorso";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageTorsoTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureBandageTorsoTarget()
	{
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageTorso";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageHeadSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureBandageHeadSelf()
	{
		m_OMD_Bridge_PainLimb = "head";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageHead";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageHeadTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureBandageHeadTarget()
	{
		m_OMD_Bridge_PainLimb = "head";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageHead";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageArmsSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureBandageArmsSelf()
	{
		m_OMD_Bridge_PainLimb = "arms";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageArms";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageArmsTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureBandageArmsTarget()
	{
		m_OMD_Bridge_PainLimb = "arms";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageArms";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageHandsSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureBandageHandsSelf()
	{
		m_OMD_Bridge_PainLimb = "hands";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageHands";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageHandsTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureBandageHandsTarget()
	{
		m_OMD_Bridge_PainLimb = "hands";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageHands";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageLegsSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureBandageLegsSelf()
	{
		m_OMD_Bridge_PainLimb = "legs";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageLegs";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageLegsTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureBandageLegsTarget()
	{
		m_OMD_Bridge_PainLimb = "legs";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageLegs";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageFeetSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureBandageFeetSelf()
	{
		m_OMD_Bridge_PainLimb = "feet";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageFeet";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureBandageFeetTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureBandageFeetTarget()
	{
		m_OMD_Bridge_PainLimb = "feet";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureBandageFeet";
		m_OMD_Bridge_DirtyOnly = false;
	}
};

class OMD_Bridge_ActionSutureDirtyTorsoSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureDirtyTorsoSelf()
	{
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyTorso";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyTorsoTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureDirtyTorsoTarget()
	{
		m_OMD_Bridge_PainLimb = "torso";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyTorso";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyHeadSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureDirtyHeadSelf()
	{
		m_OMD_Bridge_PainLimb = "head";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyHead";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyHeadTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureDirtyHeadTarget()
	{
		m_OMD_Bridge_PainLimb = "head";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyHead";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyArmsSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureDirtyArmsSelf()
	{
		m_OMD_Bridge_PainLimb = "arms";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyArms";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyArmsTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureDirtyArmsTarget()
	{
		m_OMD_Bridge_PainLimb = "arms";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyArms";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyHandsSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureDirtyHandsSelf()
	{
		m_OMD_Bridge_PainLimb = "hands";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyHands";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyHandsTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureDirtyHandsTarget()
	{
		m_OMD_Bridge_PainLimb = "hands";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyHands";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyLegsSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureDirtyLegsSelf()
	{
		m_OMD_Bridge_PainLimb = "legs";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyLegs";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyLegsTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureDirtyLegsTarget()
	{
		m_OMD_Bridge_PainLimb = "legs";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyLegs";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyFeetSelf: OMD_Bridge_ActionSutureBandageSelf
{
	void OMD_Bridge_ActionSutureDirtyFeetSelf()
	{
		m_OMD_Bridge_PainLimb = "feet";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyFeet";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

class OMD_Bridge_ActionSutureDirtyFeetTarget: OMD_Bridge_ActionSutureBandageTarget
{
	void OMD_Bridge_ActionSutureDirtyFeetTarget()
	{
		m_OMD_Bridge_PainLimb = "feet";
		m_OMD_Bridge_TextKey = "STR_OMD_Bridge_SutureDirtyFeet";
		m_OMD_Bridge_DirtyOnly = true;
	}
};

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(OMD_Bridge_ActionSutureBandageTorsoSelf);
		actions.Insert(OMD_Bridge_ActionSutureBandageTorsoTarget);
		actions.Insert(OMD_Bridge_ActionSutureBandageHeadSelf);
		actions.Insert(OMD_Bridge_ActionSutureBandageHeadTarget);
		actions.Insert(OMD_Bridge_ActionSutureBandageArmsSelf);
		actions.Insert(OMD_Bridge_ActionSutureBandageArmsTarget);
		actions.Insert(OMD_Bridge_ActionSutureBandageHandsSelf);
		actions.Insert(OMD_Bridge_ActionSutureBandageHandsTarget);
		actions.Insert(OMD_Bridge_ActionSutureBandageLegsSelf);
		actions.Insert(OMD_Bridge_ActionSutureBandageLegsTarget);
		actions.Insert(OMD_Bridge_ActionSutureBandageFeetSelf);
		actions.Insert(OMD_Bridge_ActionSutureBandageFeetTarget);
		actions.Insert(OMD_Bridge_ActionSutureDirtyTorsoSelf);
		actions.Insert(OMD_Bridge_ActionSutureDirtyTorsoTarget);
		actions.Insert(OMD_Bridge_ActionSutureDirtyHeadSelf);
		actions.Insert(OMD_Bridge_ActionSutureDirtyHeadTarget);
		actions.Insert(OMD_Bridge_ActionSutureDirtyArmsSelf);
		actions.Insert(OMD_Bridge_ActionSutureDirtyArmsTarget);
		actions.Insert(OMD_Bridge_ActionSutureDirtyHandsSelf);
		actions.Insert(OMD_Bridge_ActionSutureDirtyHandsTarget);
		actions.Insert(OMD_Bridge_ActionSutureDirtyLegsSelf);
		actions.Insert(OMD_Bridge_ActionSutureDirtyLegsTarget);
		actions.Insert(OMD_Bridge_ActionSutureDirtyFeetSelf);
		actions.Insert(OMD_Bridge_ActionSutureDirtyFeetTarget);
	}
};
