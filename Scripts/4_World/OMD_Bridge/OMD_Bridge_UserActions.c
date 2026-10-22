modded class CAContinuousTime
{
	override void Setup(ActionData action_data)
	{
		super.Setup(action_data);

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!action_data || !action_data.m_Player)
		{
			return;
		}

		float timeMultiplier = action_data.m_Player.OMD_Bridge_GetHandsActionTimeMultiplier();
		if (timeMultiplier <= 1)
		{
			return;
		}

		if (m_AdjustedTimeToComplete < 0)
		{
			return;
		}

		m_AdjustedTimeToComplete = m_AdjustedTimeToComplete * timeMultiplier;
	}
};

modded class CAContinuousRepeat
{
	override void Setup(ActionData action_data)
	{
		super.Setup(action_data);

		if (!OMD_BridgeConfig.IsActive())
		{
			return;
		}

		if (!action_data || !action_data.m_Player)
		{
			return;
		}

		float timeMultiplier = action_data.m_Player.OMD_Bridge_GetHandsActionTimeMultiplier();
		if (timeMultiplier <= 1)
		{
			return;
		}

		m_TimeToComplete = m_TimeToComplete * timeMultiplier;
	}
};
