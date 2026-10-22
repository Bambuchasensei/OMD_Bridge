modded class ActionDisinfectBandagedWoundSelf
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (super.ActionCondition(player, target, item))
		{
			return true;
		}

		if (!OMD_BridgeConfig.IsActive() || !OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			return false;
		}

		if (!OMD_BridgeTreatment.IsSutureDisinfectantItem(item))
		{
			return false;
		}

		return OMD_BridgeTreatment.ShouldShowTerjeAutoDisinfect(player);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (OMD_BridgeConfig.IsActive() && action_data && action_data.m_MainItem && action_data.m_Player)
		{
			if (OMD_BridgeTreatment.ShouldShowTerjeAutoDisinfect(action_data.m_Player))
			{
				if (OMD_BridgeTreatment.TryDisinfectSutureBandage(action_data.m_MainItem, action_data.m_Player))
				{
					Apply(action_data);
					return;
				}
			}
		}

		super.OnFinishProgressServer(action_data);
	}
};

modded class ActionDisinfectBandagedWoundTarget
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (super.ActionCondition(player, target, item))
		{
			return true;
		}

		if (!OMD_BridgeConfig.IsActive() || !OMD_BridgeConfig.IsSutureBandageEnabled())
		{
			return false;
		}

		if (!OMD_BridgeTreatment.IsSutureDisinfectantItem(item))
		{
			return false;
		}

		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (!otherPlayer)
		{
			return false;
		}

		return OMD_BridgeTreatment.ShouldShowTerjeAutoDisinfect(otherPlayer);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (OMD_BridgeConfig.IsActive() && action_data && action_data.m_MainItem && action_data.m_Target)
		{
			PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
			if (target && CanReceiveAction(action_data.m_Target))
			{
				if (OMD_BridgeTreatment.ShouldShowTerjeAutoDisinfect(target))
				{
					if (OMD_BridgeTreatment.TryDisinfectSutureBandage(action_data.m_MainItem, target))
					{
						Apply(action_data);
						return;
					}
				}
			}
		}

		super.OnFinishProgressServer(action_data);
	}
};
