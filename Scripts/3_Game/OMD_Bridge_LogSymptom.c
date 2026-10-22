class OMD_SymptomDebug
{
	static bool s_NewDamageDebug;
};

void OMD_SetNewDamageSymptomDebug(bool enabled)
{
	OMD_SymptomDebug.s_NewDamageDebug = enabled;
}

void OMD_LogSymptom(string src, string zone, int level, string effect, string state, float value, string cause)
{
	bool allow;
	allow = false;
	if (src == "OMD")
	{
		allow = OMD_SymptomDebug.s_NewDamageDebug;
	}
	else if (src == "VANILLA")
	{
		allow = OMD_SymptomDebug.s_NewDamageDebug;
	}
	else
	{
		allow = OMD_BridgeConfig.IsDebugEnabled();
	}

	if (!allow)
	{
		return;
	}

	string line;
	line = "[OMD][SYMPTOM] src=" + src;
	line = line + " zone=" + zone;
	line = line + " level=" + level.ToString();
	line = line + " effect=" + effect;
	line = line + " state=" + state;
	line = line + " value=" + value.ToString();
	line = line + " cause=" + cause;
	Print(line);
}
