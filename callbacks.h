#pragma once

namespace callbacks {
	void SkinUpdate();
	void ForceFullUpdate();
	void ToggleThirdPerson();
	void ToggleFakeLatency();
	void ToggleKillfeed();
	void SaveHotkeys();
	void ConfigLoad1();
	void ConfigLoad2();
	void ConfigLoad3();
	void ConfigLoad4();
	void ConfigLoad5();
	void ConfigLoad6();
	void ConfigLoad();
	void HiddenCvar();
	void ConfigSave();
	void emporium_connect();
	void your_dignity_connect();
	void mrx_connect();
	bool IsRainbowMenu();
	bool IsHitmarker();
	bool ViewFOVOverride();
	bool FOVOverride();

	// aimbot
	bool IsZeusBot();

	// general
	bool GeneralCategory();
	bool GeneralHeadScale();
	bool GeneralBodyScale();
	bool GeneralAutowall();
	bool GeneralHitchance();
	bool GeneralForceHealth();

	// pistol
	bool PistolCategory();
	bool PistolHeadScale();
	bool PistolBodyScale();
	bool PistolAutowall();
	bool PistolHitchance();
	bool PistolForceHealth();

	// heavypistol
	bool HeavyCategory();
	bool HeavyHeadScale();
	bool HeavyBodyScale();
	bool HeavyAutowall();
	bool HeavyHitchance();
	bool HeavyForceHealth();

	// scout
	bool ScoutCategory();
	bool ScoutHeadScale();
	bool ScoutBodyScale();
	bool ScoutAutowall();
	bool ScoutHitchance();
	bool ScoutForceHealth();

	// auto
	bool AutoCategory();
	bool AutoHeadScale();
	bool AutoBodyScale();
	bool AutoAutowall();
	bool AutoHitchance();
	bool AutoForceHealth();

	// awp
	bool AwpCategory();
	bool AwpHeadScale();
	bool AwpBodyScale();
	bool AwpAutowall();
	bool AwpHitchance();
	bool AwpForceHealth();

	bool IsAntiAimModeStand();
	bool HasStandYaw();
	bool IsCustomPitch();
	bool IsDistortion();
	bool IsStandYawJitter();
	bool IsStandYawRotate();
	bool IsStandYawRnadom();
	bool IsStandDirAuto();
	bool IsStandDirCustom();
	bool IsAntiAimModeWalk();
	bool WalkHasYaw();
	bool IsWalkYawJitter();
	bool IsWalkYawRotate();
	bool IsWalkYawRandom();
	bool IsWalkDirAuto();
	bool IsWalkDirCustom();
	bool IsAntiAimModeAir();
	bool AirHasYaw();
	bool IsAirYawJitter();
	bool IsAirYawRotate();
	bool IsAirYawRandom();
	bool IsAirDirAuto();
	bool IsAirDirCustom();
	bool IsFakeAntiAimRelative();
	bool IsFakeAntiAimJitter();
	bool IsNightMode();

	bool IsConfigMM();
	bool IsConfigNS();
	bool IsConfig1();
	bool IsConfig2();
	bool IsConfig3();
	bool IsConfig4();
	bool IsConfig5();
	bool IsConfig6();

	bool IsAgentChanger();
	bool IsTransparentProps();
	bool IsSkyBoxChange();
	bool IsDamageVisible();
	bool IsDamageInVisible();
	bool IsCustomLby();

	// weapon cfgs.
	bool DEAGLE();
	bool ELITE();
	bool FIVESEVEN();
	bool GLOCK();
	bool AK47();
	bool AUG();
	bool AWP();
	bool FAMAS();
	bool G3SG1();
	bool GALIL();
	bool M249();
	bool M4A4();
	bool MAC10();
	bool P90();
	bool UMP45();
	bool XM1014();
	bool BIZON();
	bool MAG7();
	bool NEGEV();
	bool SAWEDOFF();
	bool TEC9();
	bool P2000();
	bool MP7();
	bool MP9();
	bool NOVA();
	bool P250();
	bool SCAR20();
	bool SG553();
	bool SSG08();
	bool M4A1S();
	bool USPS();
	bool CZ75A();
	bool REVOLVER();
	bool KNIFE_BAYONET();
	bool KNIFE_FLIP();
	bool KNIFE_GUT();
	bool KNIFE_KARAMBIT();
	bool KNIFE_M9_BAYONET();
	bool KNIFE_HUNTSMAN();
	bool KNIFE_FALCHION();
	bool KNIFE_BOWIE();
	bool KNIFE_BUTTERFLY();
	bool KNIFE_SHADOW_DAGGERS();
	void ToggleBAIM();
	bool IsOverrideDamage();
	void ToggleDMG();
	void ToggleDT();
	bool AUTO_STOP();
	bool IsFakeChams();
	bool IsLocalChams();
}