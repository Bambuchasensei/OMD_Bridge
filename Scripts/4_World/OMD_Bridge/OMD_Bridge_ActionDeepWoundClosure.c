modded class InediaInfectedAI_ActionDeepWoundClosure
{
	override void OnFinishProgressServer(ActionData action_data)
	{
		string limb = m_InediaInfectedAI_PainLimb;
		PlayerBase targetPlayer;
		bool wasWounded = false;
		int woundTier = 0;

		if (action_data)
		{
			PlayerBase player = action_data.m_Player;
			if (!HasTarget())
			{
				targetPlayer = player;
			}
			else
			{
				if (action_data.m_Target)
				{
					targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
				}
			}

			if (targetPlayer)
			{
				if (targetPlayer.InediaInfectedAI_GetPainManager())
				{
					wasWounded = targetPlayer.InediaInfectedAI_GetPainManager().IsLimbDeepWounded(limb);
					if (wasWounded)
					{
						woundTier = targetPlayer.InediaInfectedAI_GetPainManager().OMD_Bridge_GetDeepWoundSeverityTierForLimb(limb);
					}
				}
			}
		}

		super.OnFinishProgressServer(action_data);

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!GetGame().IsServer())
		{
			return;
		}

		if (!wasWounded)
		{
			return;
		}

		if (!targetPlayer)
		{
			return;
		}

		InediaInfectedAI_PainManager painManager = targetPlayer.InediaInfectedAI_GetPainManager();
		if (!painManager)
		{
			return;
		}

		if (painManager.IsLimbDeepWounded(limb))
		{
			return;
		}

		painManager.OMD_Bridge_ActivateSutureForLimb(limb, woundTier);
	}
};

class OMD_Bridge_ActionDeepWoundClosureHandsSelf: InediaInfectedAI_ActionDeepWoundClosureSelf
{
	void OMD_Bridge_ActionDeepWoundClosureHandsSelf()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}
};

class OMD_Bridge_ActionDeepWoundClosureHandsTarget: InediaInfectedAI_ActionDeepWoundClosureTarget
{
	void OMD_Bridge_ActionDeepWoundClosureHandsTarget()
	{
		m_InediaInfectedAI_PainLimb = "hands";
	}
};

class OMD_Bridge_ActionDeepWoundClosureFeetSelf: InediaInfectedAI_ActionDeepWoundClosureSelf
{
	void OMD_Bridge_ActionDeepWoundClosureFeetSelf()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}
};

class OMD_Bridge_ActionDeepWoundClosureFeetTarget: InediaInfectedAI_ActionDeepWoundClosureTarget
{
	void OMD_Bridge_ActionDeepWoundClosureFeetTarget()
	{
		m_InediaInfectedAI_PainLimb = "feet";
	}
};

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(OMD_Bridge_ActionDeepWoundClosureHandsTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundClosureHandsSelf);
		actions.Insert(OMD_Bridge_ActionDeepWoundClosureFeetTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundClosureFeetSelf);
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

		if (m_InediaInfectedAI_IsDeepWoundClosureItem == 1)
		{
			AddAction(OMD_Bridge_ActionDeepWoundClosureHandsSelf);
			AddAction(OMD_Bridge_ActionDeepWoundClosureFeetSelf);
			AddAction(OMD_Bridge_ActionDeepWoundClosureHandsTarget);
			AddAction(OMD_Bridge_ActionDeepWoundClosureFeetTarget);
		}
	}
};
