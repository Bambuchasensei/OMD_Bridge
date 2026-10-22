modded class BleedingSourcesManagerServer
{
	override bool TerjeOverrideProcessHit_BearTrap(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		return true;
	}
};
