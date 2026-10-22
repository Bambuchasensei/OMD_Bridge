modded class BleedingSourcesManagerServer
{
	bool OMD_Bridge_RemoveBleedingSourceBySelection(string selectionName)
	{
		if (!m_Player)
		{
			return false;
		}

		int bit = InediaInfectedAI_GetBitFromSelectionName(selectionName);
		if (bit == 0)
		{
			return false;
		}

		if ((m_Player.GetBleedingBits() & bit) == 0)
		{
			return false;
		}

		return RemoveBleedingSource(bit);
	}
};
