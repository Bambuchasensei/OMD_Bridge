class OMD_Bridge_ActionDeepWoundUnbandageEffectiveHandsSelf: InediaInfectedAI_ActionDeepWoundUnbandageEffectiveSelf
{
	void OMD_Bridge_ActionDeepWoundUnbandageEffectiveHandsSelf()
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
};

class OMD_Bridge_ActionDeepWoundUnbandageEffectiveHandsTarget: InediaInfectedAI_ActionDeepWoundUnbandageEffectiveTarget
{
	void OMD_Bridge_ActionDeepWoundUnbandageEffectiveHandsTarget()
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
};

class OMD_Bridge_ActionDeepWoundUnbandageEffectiveFeetSelf: InediaInfectedAI_ActionDeepWoundUnbandageEffectiveSelf
{
	void OMD_Bridge_ActionDeepWoundUnbandageEffectiveFeetSelf()
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
};

class OMD_Bridge_ActionDeepWoundUnbandageEffectiveFeetTarget: InediaInfectedAI_ActionDeepWoundUnbandageEffectiveTarget
{
	void OMD_Bridge_ActionDeepWoundUnbandageEffectiveFeetTarget()
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
};

class OMD_Bridge_ActionDeepWoundUnbandageIneffectiveHandsSelf: InediaInfectedAI_ActionDeepWoundUnbandageIneffectiveSelf
{
	void OMD_Bridge_ActionDeepWoundUnbandageIneffectiveHandsSelf()
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
};

class OMD_Bridge_ActionDeepWoundUnbandageIneffectiveHandsTarget: InediaInfectedAI_ActionDeepWoundUnbandageIneffectiveTarget
{
	void OMD_Bridge_ActionDeepWoundUnbandageIneffectiveHandsTarget()
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
};

class OMD_Bridge_ActionDeepWoundUnbandageIneffectiveFeetSelf: InediaInfectedAI_ActionDeepWoundUnbandageIneffectiveSelf
{
	void OMD_Bridge_ActionDeepWoundUnbandageIneffectiveFeetSelf()
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
};

class OMD_Bridge_ActionDeepWoundUnbandageIneffectiveFeetTarget: InediaInfectedAI_ActionDeepWoundUnbandageIneffectiveTarget
{
	void OMD_Bridge_ActionDeepWoundUnbandageIneffectiveFeetTarget()
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
};

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(OMD_Bridge_ActionDeepWoundUnbandageEffectiveHandsTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundUnbandageEffectiveHandsSelf);
		actions.Insert(OMD_Bridge_ActionDeepWoundUnbandageEffectiveFeetTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundUnbandageEffectiveFeetSelf);
		actions.Insert(OMD_Bridge_ActionDeepWoundUnbandageIneffectiveHandsTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundUnbandageIneffectiveHandsSelf);
		actions.Insert(OMD_Bridge_ActionDeepWoundUnbandageIneffectiveFeetTarget);
		actions.Insert(OMD_Bridge_ActionDeepWoundUnbandageIneffectiveFeetSelf);
	}
};
