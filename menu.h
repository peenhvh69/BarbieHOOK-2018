#pragma once

class AimbotTab : public Tab {
public:
	// col1.
	Checkbox	  enable;
	Checkbox	  silent;
	Dropdown	  selection;
	Dropdown	  weaponselect;

	MultiDropdown general_hitboxes;
	MultiDropdown general_multipoint;
	Slider        general_headscale;
	Slider        general_bodyscale;
	Slider        general_mindmg;
	Checkbox	  general_autowall;
	Slider		  general_awallmindmg;

	MultiDropdown pistol_hitboxes;
	MultiDropdown pistol_multipoint;
	Slider        pistol_headscale;
	Slider        pistol_bodyscale;
	Slider        pistol_mindmg;
	Checkbox	  pistol_autowall;
	Slider		  pistol_awallmindmg;

	MultiDropdown heavypistol_hitboxes;
	MultiDropdown heavypistol_multipoint;
	Slider        heavypistol_headscale;
	Slider        heavypistol_bodyscale;
	Slider        heavypistol_mindmg;
	Checkbox	  heavypistol_autowall;
	Slider		  heavypistol_awallmindmg;

	MultiDropdown scout_hitboxes;
	MultiDropdown scout_multipoint;
	Slider        scout_headscale;
	Slider        scout_bodyscale;
	Slider        scout_mindmg;
	Checkbox	  scout_autowall;
	Slider		  scout_awallmindmg;

	MultiDropdown auto_hitboxes;
	MultiDropdown auto_multipoint;
	Slider        auto_headscale;
	Slider        auto_bodyscale;
	Slider        auto_mindmg;
	Checkbox	  auto_autowall;
	Slider		  auto_awallmindmg;

	MultiDropdown awp_hitboxes;
	MultiDropdown awp_multipoint;
	Slider        awp_headscale;
	Slider        awp_bodyscale;
	Slider        awp_mindmg;
	Checkbox	  awp_autowall;
	Slider		  awp_awallmindmg;

	Checkbox      knifebot;
	Checkbox	  zeusbot;
	Slider        zeusbot_hitchance;
	Checkbox      debugaim;
	Keybind       override_dmg_key;
	Slider        override_dmg_value;

	// col2.
	Dropdown      zoom;
	Checkbox      nospread;
	Checkbox      norecoil;

	Checkbox      general_hitchance;
	Slider		  general_hitchanceval;

	Checkbox      pistol_hitchance;
	Slider		  pistol_hitchanceval;

	Checkbox      heavypistol_hitchance;
	Slider		  heavypistol_hitchanceval;

	Checkbox      scout_hitchance;
	Slider		  scout_hitchanceval;

	Checkbox      auto_hitchance;
	Slider		  auto_hitchanceval;

	Checkbox      awp_hitchance;
	Slider		  awp_hitchanceval;

	Checkbox      ignor_limbs;
	Checkbox      lagfix;
	Checkbox	  correct;

	MultiDropdown general_preferhead;
	MultiDropdown general_preferbaim;
	MultiDropdown general_forcebaim;
	Slider        general_forcehealth;

	MultiDropdown pistol_preferhead;
	MultiDropdown pistol_preferbaim;
	MultiDropdown pistol_forcebaim;
	Slider        pistol_forcehealth;

	MultiDropdown heavypistol_preferhead;
	MultiDropdown heavypistol_preferbaim;
	MultiDropdown heavypistol_forcebaim;
	Slider        heavypistol_forcehealth;

	MultiDropdown scout_preferhead;
	MultiDropdown scout_preferbaim;
	MultiDropdown scout_forcebaim;
	Slider        scout_forcehealth;

	MultiDropdown auto_preferhead;
	MultiDropdown auto_preferbaim;
	MultiDropdown auto_forcebaim;
	Slider        auto_forcehealth;

	MultiDropdown awp_preferhead;
	MultiDropdown awp_preferbaim;
	MultiDropdown awp_forcebaim;
	Slider        awp_forcehealth;

	Keybind       baim_key;
	Keybind       override;
	Keybind		  doubletap;


public:
	void init() {
		// title.
		SetTitle(XOR("aimbot"));

		enable.setup(XOR("enable"), XOR("enable"));
		RegisterElement(&enable);

		silent.setup(XOR("silent aimbot"), XOR("silent"));
		RegisterElement(&silent);

		selection.setup(XOR("target selection"), XOR("selection"), { XOR("distance"), XOR("damage"), XOR("health"), XOR("lag"), XOR("height") });
		RegisterElement(&selection);

		weaponselect.setup(XOR("weapon select"), XOR("weaponselect"), { XOR("general"), XOR("pistol"), XOR("heavy pistol"), XOR("scout"), XOR("auto"), XOR("awp") });
		RegisterElement(&weaponselect);

		general_hitboxes.setup(XOR("hitboxes"), XOR("general_hitboxes"), { XOR("head"), XOR("upper chest"), XOR("chest"), XOR("body"), XOR("pelvis"), XOR("arms"), XOR("legs"), XOR("feet") });
		general_hitboxes.AddShowCallback(callbacks::GeneralCategory);
		RegisterElement(&general_hitboxes);

		general_multipoint.setup(XOR("multipoint"), XOR("general_multipoint"), { XOR("head"), XOR("chest"), XOR("body"), XOR("legs") });
		general_multipoint.AddShowCallback(callbacks::GeneralCategory);
		RegisterElement(&general_multipoint);

		general_headscale.setup(XOR("head multipoint"), XOR("general_headscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		general_headscale.AddShowCallback(callbacks::GeneralCategory);
		general_headscale.AddShowCallback(callbacks::GeneralHeadScale);
		RegisterElement(&general_headscale);

		general_bodyscale.setup(XOR("body multipoint"), XOR("general_bodyscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		general_bodyscale.AddShowCallback(callbacks::GeneralCategory);
		general_bodyscale.AddShowCallback(callbacks::GeneralBodyScale);
		RegisterElement(&general_bodyscale);

		general_mindmg.setup(XOR("minimum damage"), XOR("general_mindmg"), 1.f, 130.f, true, 0, 40.f, 1.f);
		general_mindmg.AddShowCallback(callbacks::GeneralCategory);
		RegisterElement(&general_mindmg);

		general_autowall.setup(XOR("autowall"), XOR("general_autowall"));
		general_autowall.AddShowCallback(callbacks::GeneralCategory);
		RegisterElement(&general_autowall);

		general_awallmindmg.setup("", XOR("general_awallmindmg"), 1.f, 130.f, false, 0, 40.f, 1.f);
		general_awallmindmg.AddShowCallback(callbacks::GeneralCategory);
		general_awallmindmg.AddShowCallback(callbacks::GeneralAutowall);
		RegisterElement(&general_awallmindmg);

		pistol_hitboxes.setup(XOR("hitboxes"), XOR("pistol_hitboxes"), { XOR("head"), XOR("upper chest"), XOR("chest"), XOR("body"), XOR("pelvis"), XOR("arms"), XOR("legs"), XOR("feet") });
		pistol_hitboxes.AddShowCallback(callbacks::PistolCategory);
		RegisterElement(&pistol_hitboxes);

		pistol_multipoint.setup(XOR("multipoint"), XOR("pistol_multipoint"), { XOR("head"), XOR("chest"), XOR("body"), XOR("legs") });
		pistol_multipoint.AddShowCallback(callbacks::PistolCategory);
		RegisterElement(&pistol_multipoint);

		pistol_headscale.setup(XOR("head multipoint"), XOR("pistol_headscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		pistol_headscale.AddShowCallback(callbacks::PistolCategory);
		pistol_headscale.AddShowCallback(callbacks::PistolHeadScale);
		RegisterElement(&pistol_headscale);

		pistol_bodyscale.setup(XOR("body multipoint"), XOR("pistol_bodyscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		pistol_bodyscale.AddShowCallback(callbacks::PistolCategory);
		pistol_bodyscale.AddShowCallback(callbacks::PistolBodyScale);
		RegisterElement(&pistol_bodyscale);

		pistol_mindmg.setup(XOR("minimum damage"), XOR("pistol_mindmg"), 1.f, 130.f, true, 0, 40.f, 1.f);
		pistol_mindmg.AddShowCallback(callbacks::PistolCategory);
		RegisterElement(&pistol_mindmg);

		pistol_autowall.setup(XOR("autowall"), XOR("pistol_autowall"));
		pistol_autowall.AddShowCallback(callbacks::PistolCategory);
		RegisterElement(&pistol_autowall);

		pistol_awallmindmg.setup("", XOR("pistol_awallmindmg"), 1.f, 130.f, false, 0, 40.f, 1.f);
		pistol_awallmindmg.AddShowCallback(callbacks::PistolCategory);
		pistol_awallmindmg.AddShowCallback(callbacks::PistolAutowall);
		RegisterElement(&pistol_awallmindmg);

		heavypistol_hitboxes.setup(XOR("hitboxes"), XOR("heavypistol_hitboxes"), { XOR("head"), XOR("upper chest"), XOR("chest"), XOR("body"), XOR("pelvis"), XOR("arms"), XOR("legs"), XOR("feet") });
		heavypistol_hitboxes.AddShowCallback(callbacks::HeavyCategory);
		RegisterElement(&heavypistol_hitboxes);

		heavypistol_multipoint.setup(XOR("multipoint"), XOR("heavypistol_multipoint"), { XOR("head"), XOR("chest"), XOR("body"), XOR("legs") });
		heavypistol_multipoint.AddShowCallback(callbacks::HeavyCategory);
		RegisterElement(&heavypistol_multipoint);

		heavypistol_headscale.setup(XOR("head multipoint"), XOR("heavypistol_headscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		heavypistol_headscale.AddShowCallback(callbacks::HeavyCategory);
		heavypistol_headscale.AddShowCallback(callbacks::HeavyHeadScale);
		RegisterElement(&heavypistol_headscale);

		heavypistol_bodyscale.setup(XOR("body multipoint"), XOR("heavypistol_bodyscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		heavypistol_bodyscale.AddShowCallback(callbacks::HeavyCategory);
		heavypistol_bodyscale.AddShowCallback(callbacks::HeavyBodyScale);
		RegisterElement(&heavypistol_bodyscale);

		heavypistol_mindmg.setup(XOR("minimum damage"), XOR("heavypistol_mindmg"), 1.f, 130.f, true, 0, 40.f, 1.f);
		heavypistol_mindmg.AddShowCallback(callbacks::HeavyCategory);
		RegisterElement(&heavypistol_mindmg);

		heavypistol_autowall.setup(XOR("autowall"), XOR("heavypistol_autowall"));
		heavypistol_autowall.AddShowCallback(callbacks::HeavyCategory);
		RegisterElement(&heavypistol_autowall);

		heavypistol_awallmindmg.setup("", XOR("heavypistol_awallmindmg"), 1.f, 130.f, false, 0, 40.f, 1.f);
		heavypistol_awallmindmg.AddShowCallback(callbacks::HeavyCategory);
		heavypistol_awallmindmg.AddShowCallback(callbacks::HeavyAutowall);
		RegisterElement(&heavypistol_awallmindmg);

		scout_hitboxes.setup(XOR("hitboxes"), XOR("scout_hitboxes"), { XOR("head"), XOR("upper chest"), XOR("chest"), XOR("body"), XOR("pelvis"), XOR("arms"), XOR("legs"), XOR("feet") });
		scout_hitboxes.AddShowCallback(callbacks::ScoutCategory);
		RegisterElement(&scout_hitboxes);

		scout_multipoint.setup(XOR("multipoint"), XOR("scout_multipoint"), { XOR("head"), XOR("chest"), XOR("body"), XOR("legs") });
		scout_multipoint.AddShowCallback(callbacks::ScoutCategory);
		RegisterElement(&scout_multipoint);

		scout_headscale.setup(XOR("head multipoint"), XOR("scout_headscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		scout_headscale.AddShowCallback(callbacks::ScoutCategory);
		scout_headscale.AddShowCallback(callbacks::ScoutHeadScale);
		RegisterElement(&scout_headscale);

		scout_bodyscale.setup(XOR("body multipoint"), XOR("scout_bodyscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		scout_bodyscale.AddShowCallback(callbacks::ScoutCategory);
		scout_bodyscale.AddShowCallback(callbacks::ScoutBodyScale);
		RegisterElement(&scout_bodyscale);

		scout_mindmg.setup(XOR("minimum damage"), XOR("scout_mindmg"), 1.f, 130.f, true, 0, 40.f, 1.f);
		scout_mindmg.AddShowCallback(callbacks::ScoutCategory);
		RegisterElement(&scout_mindmg);

		scout_autowall.setup(XOR("autowall"), XOR("scout_autowall"));
		scout_autowall.AddShowCallback(callbacks::ScoutCategory);
		RegisterElement(&scout_autowall);

		scout_awallmindmg.setup("", XOR("scout_awallmindmg"), 1.f, 130.f, false, 0, 40.f, 1.f);
		scout_awallmindmg.AddShowCallback(callbacks::ScoutCategory);
		scout_awallmindmg.AddShowCallback(callbacks::ScoutAutowall);
		RegisterElement(&scout_awallmindmg);

		auto_hitboxes.setup(XOR("hitboxes"), XOR("auto_hitboxes"), { XOR("head"), XOR("upper chest"), XOR("chest"), XOR("body"), XOR("pelvis"), XOR("arms"), XOR("legs"), XOR("feet") });
		auto_hitboxes.AddShowCallback(callbacks::AutoCategory);
		RegisterElement(&auto_hitboxes);

		auto_multipoint.setup(XOR("multipoint"), XOR("auto_multipoint"), { XOR("head"), XOR("chest"), XOR("body"), XOR("legs") });
		auto_multipoint.AddShowCallback(callbacks::AutoCategory);
		RegisterElement(&auto_multipoint);

		auto_headscale.setup(XOR("head multipoint"), XOR("auto_headscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		auto_headscale.AddShowCallback(callbacks::AutoCategory);
		auto_headscale.AddShowCallback(callbacks::AutoHeadScale);
		RegisterElement(&auto_headscale);

		auto_bodyscale.setup(XOR("body multipoint"), XOR("auto_bodyscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		auto_bodyscale.AddShowCallback(callbacks::AutoCategory);
		auto_bodyscale.AddShowCallback(callbacks::AutoBodyScale);
		RegisterElement(&auto_bodyscale);

		auto_mindmg.setup(XOR("minimum damage"), XOR("auto_mindmg"), 1.f, 130.f, true, 0, 40.f, 1.f);
		auto_mindmg.AddShowCallback(callbacks::AutoCategory);
		RegisterElement(&auto_mindmg);

		auto_autowall.setup(XOR("autowall"), XOR("auto_autowall"));
		auto_autowall.AddShowCallback(callbacks::AutoCategory);
		RegisterElement(&auto_autowall);

		auto_awallmindmg.setup("", XOR("auto_awallmindmg"), 1.f, 130.f, false, 0, 40.f, 1.f);
		auto_awallmindmg.AddShowCallback(callbacks::AutoCategory);
		auto_awallmindmg.AddShowCallback(callbacks::AutoAutowall);
		RegisterElement(&auto_awallmindmg);

		awp_hitboxes.setup(XOR("hitboxes"), XOR("awp_hitboxes"), { XOR("head"), XOR("upper chest"), XOR("chest"), XOR("body"), XOR("pelvis"), XOR("arms"), XOR("legs"), XOR("feet") });
		awp_hitboxes.AddShowCallback(callbacks::AwpCategory);
		RegisterElement(&awp_hitboxes);

		awp_multipoint.setup(XOR("multipoint"), XOR("awp_multipoint"), { XOR("head"), XOR("chest"), XOR("body"), XOR("legs") });
		awp_multipoint.AddShowCallback(callbacks::AwpCategory);
		RegisterElement(&awp_multipoint);

		awp_headscale.setup(XOR("head multipoint"), XOR("awp_headscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		awp_headscale.AddShowCallback(callbacks::AwpCategory);
		awp_headscale.AddShowCallback(callbacks::AwpHeadScale);
		RegisterElement(&awp_headscale);

		awp_bodyscale.setup(XOR("body multipoint"), XOR("awp_bodyscale"), 1.f, 100.f, true, 0, 40.f, 1.f);
		awp_bodyscale.AddShowCallback(callbacks::AwpCategory);
		awp_bodyscale.AddShowCallback(callbacks::AwpBodyScale);
		RegisterElement(&awp_bodyscale);

		awp_mindmg.setup(XOR("minimum damage"), XOR("awp_mindmg"), 1.f, 130.f, true, 0, 40.f, 1.f);
		awp_mindmg.AddShowCallback(callbacks::AwpCategory);
		RegisterElement(&awp_mindmg);

		awp_autowall.setup(XOR("autowall"), XOR("awp_autowall"));
		awp_autowall.AddShowCallback(callbacks::AwpCategory);
		RegisterElement(&awp_autowall);

		awp_awallmindmg.setup("", XOR("awp_awallmindmg"), 1.f, 130.f, false, 0, 40.f, 1.f);
		awp_awallmindmg.AddShowCallback(callbacks::AwpCategory);
		awp_awallmindmg.AddShowCallback(callbacks::AwpAutowall);
		RegisterElement(&awp_awallmindmg);

		knifebot.setup(XOR("aimbot with knife"), XOR("knifebot"));
		RegisterElement(&knifebot);

		zeusbot.setup(XOR("zeusbot"), XOR("zeusbot"));
		RegisterElement(&zeusbot);

		zeusbot_hitchance.setup("", XOR("zeusbot_hitchance"), 1.f, 100.f, false, 0, 30.f, 1.f, XOR(L"%"));
		zeusbot_hitchance.AddShowCallback(callbacks::IsZeusBot);
		RegisterElement(&zeusbot_hitchance);

		debugaim.setup(XOR("aimbot hitchams"), XOR("debugaim"));
		RegisterElement(&debugaim);

		// col2.
		zoom.setup(XOR("auto scope"), XOR("zoom"), { XOR("off"), XOR("always"), XOR("hitchance fail") });
		RegisterElement(&zoom, 1);

		nospread.setup(XOR("compensate spread"), XOR("nospread"));
		nospread.AddShowCallback(callbacks::IsConfigNS);
		RegisterElement(&nospread, 1);

		norecoil.setup(XOR("compensate recoil"), XOR("norecoil"));
		RegisterElement(&norecoil, 1);

		general_hitchance.setup(XOR("hitchance"), XOR("general_hitchance"));
		general_hitchance.AddShowCallback(callbacks::GeneralCategory);
		RegisterElement(&general_hitchance, 1);

		general_hitchanceval.setup("", XOR("general_hitchanceval"), 1.f, 100.f, false, 0, 40.f, 1.f);
		general_hitchanceval.AddShowCallback(callbacks::GeneralCategory);
		general_hitchanceval.AddShowCallback(callbacks::GeneralHitchance);
		RegisterElement(&general_hitchanceval, 1);

		pistol_hitchance.setup(XOR("hitchance"), XOR("pistol_hitchance"));
		pistol_hitchance.AddShowCallback(callbacks::PistolCategory);
		RegisterElement(&pistol_hitchance, 1);

		pistol_hitchanceval.setup("", XOR("pistol_hitchanceval"), 1.f, 100.f, false, 0, 40.f, 1.f);
		pistol_hitchanceval.AddShowCallback(callbacks::PistolCategory);
		pistol_hitchanceval.AddShowCallback(callbacks::PistolHitchance);
		RegisterElement(&pistol_hitchanceval, 1);

		heavypistol_hitchance.setup(XOR("hitchance"), XOR("heavypistol_hitchance"));
		heavypistol_hitchance.AddShowCallback(callbacks::HeavyCategory);
		RegisterElement(&heavypistol_hitchance, 1);

		heavypistol_hitchanceval.setup("", XOR("heavypistol_hitchanceval"), 1.f, 100.f, false, 0, 40.f, 1.f);
		heavypistol_hitchanceval.AddShowCallback(callbacks::HeavyCategory);
		heavypistol_hitchanceval.AddShowCallback(callbacks::HeavyHitchance);
		RegisterElement(&heavypistol_hitchanceval, 1);

		auto_hitchance.setup(XOR("hitchance"), XOR("auto_hitchance"));
		auto_hitchance.AddShowCallback(callbacks::AutoCategory);
		RegisterElement(&auto_hitchance, 1);

		auto_hitchanceval.setup("", XOR("auto_hitchanceval"), 1.f, 100.f, false, 0, 40.f, 1.f);
		auto_hitchanceval.AddShowCallback(callbacks::AutoCategory);
		auto_hitchanceval.AddShowCallback(callbacks::AutoHitchance);
		RegisterElement(&auto_hitchanceval, 1);

		scout_hitchance.setup(XOR("hitchance"), XOR("scout_hitchance"));
		scout_hitchance.AddShowCallback(callbacks::ScoutCategory);
		RegisterElement(&scout_hitchance, 1);

		scout_hitchanceval.setup("", XOR("scout_hitchanceval"), 1.f, 100.f, false, 0, 40.f, 1.f);
		scout_hitchanceval.AddShowCallback(callbacks::ScoutCategory);
		scout_hitchanceval.AddShowCallback(callbacks::ScoutHitchance);
		RegisterElement(&scout_hitchanceval, 1);

		awp_hitchance.setup(XOR("hitchance"), XOR("awp_hitchance"));
		awp_hitchance.AddShowCallback(callbacks::AwpCategory);
		RegisterElement(&awp_hitchance, 1);

		awp_hitchanceval.setup("", XOR("awp_hitchanceval"), 1.f, 100.f, false, 0, 40.f, 1.f);
		awp_hitchanceval.AddShowCallback(callbacks::AwpCategory);
		awp_hitchanceval.AddShowCallback(callbacks::AwpHitchance);
		RegisterElement(&awp_hitchanceval, 1);

		ignor_limbs.setup(XOR("ignore limbs when moving"), XOR("ignor_limbs"));
		RegisterElement(&ignor_limbs, 1);

		lagfix.setup(XOR("predict fake-lag"), XOR("lagfix"));
		RegisterElement(&lagfix, 1);

		correct.setup(XOR("correct anti-aim"), XOR("correct"));
		RegisterElement(&correct, 1);

		general_preferhead.setup(XOR("prefer head aim"), XOR("general_preferhead"), { XOR("always"), XOR("running"), XOR("resolved"), XOR("in air") });
		general_preferhead.AddShowCallback(callbacks::GeneralCategory);
		RegisterElement(&general_preferhead, 1);

		general_preferbaim.setup(XOR("prefer body-aim"), XOR("general_preferbaim"), { XOR("always"), XOR("lethal"), XOR("lethal x2"), XOR("fake"), XOR("in air") });
		general_preferbaim.AddShowCallback(callbacks::GeneralCategory);
		RegisterElement(&general_preferbaim, 1);

		general_forcebaim.setup(XOR("force body-aim"), XOR("general_forcebaim"), { XOR("always"), XOR("health"), XOR("fake"), XOR("in air") });
		general_forcebaim.AddShowCallback(callbacks::GeneralCategory);
		RegisterElement(&general_forcebaim, 1);

		general_forcehealth.setup("", XOR("general_forcehealth"), 1.f, 100.f, false, 0, 40.f, 1.f);
		general_forcehealth.AddShowCallback(callbacks::GeneralCategory);
		general_forcehealth.AddShowCallback(callbacks::GeneralForceHealth);
		RegisterElement(&general_forcehealth, 1);

		pistol_preferhead.setup(XOR("prefer head aim"), XOR("pistol_preferhead"), { XOR("always"), XOR("running"), XOR("resolved"), XOR("in air") });
		pistol_preferhead.AddShowCallback(callbacks::PistolCategory);
		RegisterElement(&pistol_preferhead, 1);

		pistol_preferbaim.setup(XOR("prefer body-aim"), XOR("pistol_preferbaim"), { XOR("always"), XOR("lethal"), XOR("lethal x2"), XOR("fake"), XOR("in air") });
		pistol_preferbaim.AddShowCallback(callbacks::PistolCategory);
		RegisterElement(&pistol_preferbaim, 1);

		pistol_forcebaim.setup(XOR("force body-aim"), XOR("pistol_forcebaim"), { XOR("always"), XOR("health"), XOR("fake"), XOR("in air") });
		pistol_forcebaim.AddShowCallback(callbacks::PistolCategory);
		RegisterElement(&pistol_forcebaim, 1);

		pistol_forcehealth.setup("", XOR("pistol_forcehealth"), 1.f, 100.f, false, 0, 40.f, 1.f);
		pistol_forcehealth.AddShowCallback(callbacks::PistolCategory);
		pistol_forcehealth.AddShowCallback(callbacks::PistolForceHealth);
		RegisterElement(&pistol_forcehealth, 1);

		heavypistol_preferhead.setup(XOR("prefer head aim"), XOR("heavypistol_preferhead"), { XOR("always"), XOR("running"), XOR("resolved"), XOR("in air") });
		heavypistol_preferhead.AddShowCallback(callbacks::HeavyCategory);
		RegisterElement(&heavypistol_preferhead, 1);

		heavypistol_preferbaim.setup(XOR("prefer body-aim"), XOR("heavypistol_preferbaim"), { XOR("always"), XOR("lethal"), XOR("lethal x2"), XOR("fake"), XOR("in air") });
		heavypistol_preferbaim.AddShowCallback(callbacks::HeavyCategory);
		RegisterElement(&heavypistol_preferbaim, 1);

		heavypistol_forcebaim.setup(XOR("force body-aim"), XOR("heavypistol_forcebaim"), { XOR("always"), XOR("health"), XOR("fake"), XOR("in air") });
		heavypistol_forcebaim.AddShowCallback(callbacks::HeavyCategory);
		RegisterElement(&heavypistol_forcebaim, 1);

		heavypistol_forcehealth.setup("", XOR("heavypistol_forcehealth"), 1.f, 100.f, false, 0, 40.f, 1.f);
		heavypistol_forcehealth.AddShowCallback(callbacks::HeavyCategory);
		heavypistol_forcehealth.AddShowCallback(callbacks::HeavyForceHealth);
		RegisterElement(&heavypistol_forcehealth, 1);

		scout_preferhead.setup(XOR("prefer head aim"), XOR("scout_preferhead"), { XOR("always"), XOR("running"), XOR("resolved"), XOR("in air") });
		scout_preferhead.AddShowCallback(callbacks::ScoutCategory);
		RegisterElement(&scout_preferhead, 1);

		scout_preferbaim.setup(XOR("prefer body-aim"), XOR("scout_preferbaim"), { XOR("always"), XOR("lethal"), XOR("lethal x2"), XOR("fake"), XOR("in air") });
		scout_preferbaim.AddShowCallback(callbacks::ScoutCategory);
		RegisterElement(&scout_preferbaim, 1);

		scout_forcebaim.setup(XOR("force body-aim"), XOR("scout_forcebaim"), { XOR("always"), XOR("health"), XOR("fake"), XOR("in air") });
		scout_forcebaim.AddShowCallback(callbacks::ScoutCategory);
		RegisterElement(&scout_forcebaim, 1);

		scout_forcehealth.setup("", XOR("scout_forcehealth"), 1.f, 100.f, false, 0, 40.f, 1.f);
		scout_forcehealth.AddShowCallback(callbacks::ScoutCategory);
		scout_forcehealth.AddShowCallback(callbacks::ScoutForceHealth);
		RegisterElement(&scout_forcehealth, 1);

		auto_preferhead.setup(XOR("prefer head aim"), XOR("auto_preferhead"), { XOR("always"), XOR("running"), XOR("resolved"), XOR("in air") });
		auto_preferhead.AddShowCallback(callbacks::AutoCategory);
		RegisterElement(&auto_preferhead, 1);

		auto_preferbaim.setup(XOR("prefer body-aim"), XOR("auto_preferbaim"), { XOR("always"), XOR("lethal"), XOR("lethal x2"), XOR("fake"), XOR("in air") });
		auto_preferbaim.AddShowCallback(callbacks::AutoCategory);
		RegisterElement(&auto_preferbaim, 1);

		auto_forcebaim.setup(XOR("force body-aim"), XOR("auto_forcebaim"), { XOR("always"), XOR("health"), XOR("fake"), XOR("in air") });
		auto_forcebaim.AddShowCallback(callbacks::AutoCategory);
		RegisterElement(&auto_forcebaim, 1);

		auto_forcehealth.setup("", XOR("auto_forcehealth"), 1.f, 100.f, false, 0, 40.f, 1.f);
		auto_forcehealth.AddShowCallback(callbacks::AutoCategory);
		auto_forcehealth.AddShowCallback(callbacks::AutoForceHealth);
		RegisterElement(&auto_forcehealth, 1);

		awp_preferhead.setup(XOR("prefer head aim"), XOR("awp_preferhead"), { XOR("always"), XOR("running"), XOR("resolved"), XOR("in air") });
		awp_preferhead.AddShowCallback(callbacks::AwpCategory);
		RegisterElement(&awp_preferhead, 1);

		awp_preferbaim.setup(XOR("prefer body-aim"), XOR("awp_preferbaim"), { XOR("always"), XOR("lethal"), XOR("lethal x2"), XOR("fake"), XOR("in air") });
		awp_preferbaim.AddShowCallback(callbacks::AwpCategory);
		RegisterElement(&awp_preferbaim, 1);

		awp_forcebaim.setup(XOR("force body-aim"), XOR("awp_forcebaim"), { XOR("always"), XOR("health"), XOR("fake"), XOR("in air") });
		awp_forcebaim.AddShowCallback(callbacks::AwpCategory);
		RegisterElement(&awp_forcebaim, 1);

		awp_forcehealth.setup("", XOR("awp_forcehealth"), 1.f, 100.f, false, 0, 40.f, 1.f);
		awp_forcehealth.AddShowCallback(callbacks::AwpCategory);
		awp_forcehealth.AddShowCallback(callbacks::AwpForceHealth);
		RegisterElement(&awp_forcehealth, 1);

		baim_key.setup(XOR("body aim on key"), XOR("body aim on key"));
		baim_key.SetToggleCallback(callbacks::ToggleBAIM);
		RegisterElement(&baim_key, 1);

		override.setup(XOR("resolver override"), XOR("override"));
		RegisterElement(&override, 1);

		override_dmg_key.setup(XOR("override damage"), XOR("override_dmg"));
		override_dmg_key.SetToggleCallback(callbacks::ToggleDMG);
		RegisterElement(&override_dmg_key, 1);

		override_dmg_value.setup(" ", XOR("dmg_override"), 1.f, 100.f, false, 0, 1.f, 1.f, XOR(L"hp"));
		override_dmg_value.AddShowCallback(callbacks::IsOverrideDamage);
		RegisterElement(&override_dmg_value, 1);

		doubletap.setup(XOR("gay-walk"), XOR("doubletap"));
		doubletap.SetToggleCallback(callbacks::ToggleDT);
		RegisterElement(&doubletap, 1);
	}
};

class AntiAimTab : public Tab {
public:
	// col 1.
	Checkbox enable;
	Checkbox edge;
	Dropdown mode;

	Dropdown pitch_stand;
	Dropdown yaw_stand;
	Slider   distortion_speed;
	Slider   distortion_swap_amount;
	//Checkbox drake_n_josh_randomizedangle;
	//Slider   drakenjoshrange;
	//Slider   drake_n_josh_range2;
	Slider   jitter_range_stand;
	Slider   rot_range_stand;
	Slider   rot_speed_stand;
	Slider   rand_update_stand;
	Dropdown dir_stand;
	Slider   dir_time_stand;
	Slider   dir_custom_stand;
	Checkbox dir_lock;
	Dropdown pitch_fake_stand;
	Slider   custom_fake_pitch;
	Checkbox body_fake_stand_fakewalk;
	Dropdown base_angle_stand;
	Dropdown body_fake_stand;
	Slider	 body_fake_stand_custom;

	Dropdown pitch_walk;
	Dropdown yaw_walk;
	Slider   jitter_range_walk;
	Slider   rot_range_walk;
	Slider   rot_speed_walk;
	Slider   rand_update_walk;
	Dropdown dir_walk;
	Slider	 dir_time_walk;
	Slider   dir_custom_walk;
	Dropdown base_angle_walk;


	Dropdown pitch_air;
	Dropdown yaw_air;
	Slider   jitter_range_air;
	Slider   rot_range_air;
	Slider   rot_speed_air;
	Slider   rand_update_air;
	Dropdown dir_air;
	Slider   dir_time_air;
	Slider   dir_custom_air;
	Dropdown base_angle_air;
	Dropdown body_fake_air;


	// col 2.
	Dropdown fake_yaw;
	Slider	 fake_relative;
	Slider	 fake_jitter_range;

	Checkbox      lag_enable;
	MultiDropdown lag_active;
	Dropdown      lag_mode;
	Slider        lag_limit;
	Checkbox      lag_land;
	Keybind  disablefakelagonkey;

	Keybind fakeduck;

public:
	void init() {
		SetTitle(XOR("anti-aim"));

		enable.setup(XOR("enable"), XOR("enable"));
		RegisterElement(&enable);

		edge.setup(XOR("edge"), XOR("edge"));
		RegisterElement(&edge);

		mode.setup("", XOR("mode"), { XOR("stand"), XOR("walk"), XOR("air") }, false);
		RegisterElement(&mode);

		// stand.
		pitch_stand.setup(XOR("pitch"), XOR("pitch_stnd"), { XOR("off"), XOR("down"), XOR("up"), XOR("random"), XOR("ideal") });
		pitch_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		RegisterElement(&pitch_stand);

		yaw_stand.setup(XOR("yaw"), XOR("yaw_stnd"), { XOR("off"), XOR("direction"), XOR("jitter"), XOR("rotate"), XOR("random"), XOR("distortion"), XOR("drake n josh v2") });
		yaw_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		RegisterElement(&yaw_stand);

		jitter_range_stand.setup("", XOR("jitter_range_stnd"), 1.f, 180.f, false, 0, 45.f, 5.f, XOR(L"?"));
		jitter_range_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		jitter_range_stand.AddShowCallback(callbacks::IsStandYawJitter);
		RegisterElement(&jitter_range_stand);

		rot_range_stand.setup("", XOR("rot_range_stnd"), 0.f, 360.f, false, 0, 360.f, 5.f, XOR(L"?"));
		rot_range_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		rot_range_stand.AddShowCallback(callbacks::IsStandYawRotate);
		RegisterElement(&rot_range_stand);

		rot_speed_stand.setup("", XOR("rot_speed_stnd"), 1.f, 100.f, false, 0, 10.f, 1.f, XOR(L"%"));
		rot_speed_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		rot_speed_stand.AddShowCallback(callbacks::IsStandYawRotate);
		RegisterElement(&rot_speed_stand);

		rand_update_stand.setup("", XOR("rand_update_stnd"), 0.f, 1.f, false, 1, 0.f, 0.1f);
		rand_update_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		rand_update_stand.AddShowCallback(callbacks::IsStandYawRnadom);
		RegisterElement(&rand_update_stand);

		dir_stand.setup(XOR("direction"), XOR("dir_stnd"), { XOR("auto"), XOR("backwards"), XOR("left"), XOR("right"), XOR("custom") });
		dir_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		dir_stand.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&dir_stand);

		dir_time_stand.setup("", XOR("dir_time_stnd"), 0.f, 10.f, false, 0, 0.f, 1.f, XOR(L"s"));
		dir_time_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		dir_time_stand.AddShowCallback(callbacks::HasStandYaw);
		dir_time_stand.AddShowCallback(callbacks::IsStandDirAuto);
		RegisterElement(&dir_time_stand);

		dir_custom_stand.setup("", XOR("dir_custom_stnd"), -180.f, 180.f, false, 0, 0.f, 5.f, XOR(L"?"));
		dir_custom_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		dir_custom_stand.AddShowCallback(callbacks::HasStandYaw);
		dir_custom_stand.AddShowCallback(callbacks::IsStandDirCustom);
		RegisterElement(&dir_custom_stand);

		base_angle_stand.setup(XOR("base angle"), XOR("base_angle_stand"), { XOR("off"), XOR("static"), XOR("away crosshair"), XOR("away distance") });
		base_angle_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		base_angle_stand.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&base_angle_stand);

		dir_lock.setup(XOR("lock direction"), XOR("dir_lock"));
		dir_lock.AddShowCallback(callbacks::IsAntiAimModeStand);
		dir_lock.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&dir_lock);

		body_fake_stand.setup(XOR("fake body"), XOR("body_fake_stnd"), { XOR("off"), XOR("left"), XOR("right"), XOR("opposite"), XOR("z"), XOR("custom"), XOR("twist"), XOR("fatman") });
		body_fake_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		body_fake_stand.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&body_fake_stand);

		body_fake_stand_custom.setup(XOR("lby custom"), XOR("body_fake_stand_custom"), -70, 70, false, 0, 0, 1.f, XOR(L"?"));
		body_fake_stand_custom.AddShowCallback(callbacks::IsAntiAimModeStand);
		//body_fake_stand_custom.AddShowCallback(callbacks::HasStandYaw);
		body_fake_stand_custom.AddShowCallback(callbacks::IsCustomLby);
		RegisterElement(&body_fake_stand_custom);

		/*body_fake_stand_fakewalk.setup(XOR("disable fake body on fakewalk"), XOR("body_fake_stand_fakewalk"));
		body_fake_stand_fakewalk.AddShowCallback(callbacks::IsAntiAimModeStand);
		body_fake_stand_fakewalk.AddShowCallback(callbacks::HasStandYaw);
		RegisterElement(&body_fake_stand_fakewalk);


		/*dir_time_stand.setup("", XOR("dir_time_stnd"), 0.f, 10.f, false, 0, 0.f, 1.f, XOR(L"s"));
		dir_time_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		dir_time_stand.AddShowCallback(callbacks::HasStandYaw);
		dir_time_stand.AddShowCallback(callbacks::IsStandDirAuto);
		RegisterElement(&dir_time_stand);
		lag_limit.setup(XOR("limit"), XOR("lag_limit"), 2, 16, true, 0, 2, 1.f);*/


		// walk.
		pitch_walk.setup(XOR("pitch"), XOR("pitch_walk"), { XOR("off"), XOR("down"), XOR("up"), XOR("random"), XOR("ideal") });
		pitch_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		RegisterElement(&pitch_walk);

		yaw_walk.setup(XOR("yaw"), XOR("yaw_walk"), { XOR("off"), XOR("direction"), XOR("jitter"), XOR("rotate"), XOR("random") });
		yaw_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		RegisterElement(&yaw_walk);

		jitter_range_walk.setup("", XOR("jitter_range_walk"), 1.f, 180.f, false, 0, 45.f, 5.f, XOR(L"?"));
		jitter_range_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		jitter_range_walk.AddShowCallback(callbacks::IsWalkYawJitter);
		RegisterElement(&jitter_range_walk);

		rot_range_walk.setup("", XOR("rot_range_walk"), 0.f, 360.f, false, 0, 360.f, 5.f, XOR(L"?"));
		rot_range_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		rot_range_walk.AddShowCallback(callbacks::IsWalkYawRotate);
		RegisterElement(&rot_range_walk);

		rot_speed_walk.setup("", XOR("rot_speed_walk"), 1.f, 100.f, false, 0, 10.f, 1.f, XOR(L"%"));
		rot_speed_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		rot_speed_walk.AddShowCallback(callbacks::IsWalkYawRotate);
		RegisterElement(&rot_speed_walk);

		rand_update_walk.setup("", XOR("rand_update_walk"), 0.f, 1.f, false, 1, 0.f, 0.1f);
		rand_update_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		rand_update_walk.AddShowCallback(callbacks::IsWalkYawRandom);
		RegisterElement(&rand_update_walk);

		dir_walk.setup(XOR("direction"), XOR("dir_walk"), { XOR("auto"), XOR("backwards"), XOR("left"), XOR("right"), XOR("custom") });
		dir_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		dir_walk.AddShowCallback(callbacks::WalkHasYaw);
		RegisterElement(&dir_walk);

		dir_time_walk.setup("", XOR("dir_time_walk"), 0.f, 10.f, false, 0, 0.f, 1.f, XOR(L"s"));
		dir_time_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		dir_time_walk.AddShowCallback(callbacks::WalkHasYaw);
		dir_time_walk.AddShowCallback(callbacks::IsWalkDirAuto);
		RegisterElement(&dir_time_walk);

		dir_custom_walk.setup("", XOR("dir_custom_walk"), -180.f, 180.f, false, 0, 0.f, 5.f, XOR(L"?"));
		dir_custom_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		dir_custom_walk.AddShowCallback(callbacks::WalkHasYaw);
		dir_custom_walk.AddShowCallback(callbacks::IsWalkDirCustom);
		RegisterElement(&dir_custom_walk);

		base_angle_walk.setup(XOR("base angle"), XOR("base_angle_walk"), { XOR("off"), XOR("static"), XOR("away crosshair"), XOR("away distance") });
		base_angle_walk.AddShowCallback(callbacks::IsAntiAimModeWalk);
		base_angle_walk.AddShowCallback(callbacks::WalkHasYaw);
		RegisterElement(&base_angle_walk);

		// air.
		pitch_air.setup(XOR("pitch"), XOR("pitch_air"), { XOR("off"), XOR("down"), XOR("up"), XOR("random"), XOR("ideal") });
		pitch_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		RegisterElement(&pitch_air);

		yaw_air.setup(XOR("yaw"), XOR("yaw_air"), { XOR("off"), XOR("direction"), XOR("jitter"), XOR("rotate"), XOR("random") });
		yaw_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		RegisterElement(&yaw_air);

		jitter_range_air.setup("", XOR("jitter_range_air"), 1.f, 180.f, false, 0, 45.f, 5.f, XOR(L"?"));
		jitter_range_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		jitter_range_air.AddShowCallback(callbacks::IsAirYawJitter);
		RegisterElement(&jitter_range_air);

		rot_range_air.setup("", XOR("rot_range_air"), 0.f, 360.f, false, 0, 360.f, 5.f, XOR(L"?"));
		rot_range_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		rot_range_air.AddShowCallback(callbacks::IsAirYawRotate);
		RegisterElement(&rot_range_air);

		rot_speed_air.setup("", XOR("rot_speed_air"), 1.f, 100.f, false, 0, 10.f, 1.f, XOR(L"%"));
		rot_speed_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		rot_speed_air.AddShowCallback(callbacks::IsAirYawRotate);
		RegisterElement(&rot_speed_air);

		rand_update_air.setup("", XOR("rand_update_air"), 0.f, 1.f, false, 1, 0.f, 0.1f);
		rand_update_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		rand_update_air.AddShowCallback(callbacks::IsAirYawRandom);
		RegisterElement(&rand_update_air);

		dir_air.setup(XOR("direction"), XOR("dir_air"), { XOR("auto"), XOR("backwards"), XOR("left"), XOR("right"), XOR("custom") });
		dir_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		dir_air.AddShowCallback(callbacks::AirHasYaw);
		RegisterElement(&dir_air);

		dir_time_air.setup("", XOR("dir_time_air"), 0.f, 10.f, false, 0, 0.f, 1.f, XOR(L"s"));
		dir_time_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		dir_time_air.AddShowCallback(callbacks::AirHasYaw);
		dir_time_air.AddShowCallback(callbacks::IsAirDirAuto);
		RegisterElement(&dir_time_air);

		dir_custom_air.setup("", XOR("dir_custom_air"), -180.f, 180.f, false, 0, 0.f, 5.f, XOR(L"?"));
		dir_custom_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		dir_custom_air.AddShowCallback(callbacks::AirHasYaw);
		dir_custom_air.AddShowCallback(callbacks::IsAirDirCustom);
		RegisterElement(&dir_custom_air);

		base_angle_air.setup(XOR("base angle"), XOR("base_angle_air"), { XOR("off"), XOR("static"), XOR("away crosshair"), XOR("away distance") });
		base_angle_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		base_angle_air.AddShowCallback(callbacks::AirHasYaw);
		RegisterElement(&base_angle_air);

		body_fake_air.setup(XOR("fake body"), XOR("body_fake_air"), { XOR("off"), XOR("left"), XOR("right"), XOR("opposite") });
		body_fake_air.AddShowCallback(callbacks::IsAntiAimModeAir);
		body_fake_air.AddShowCallback(callbacks::AirHasYaw);
		RegisterElement(&body_fake_air);

		// col2.
		fake_yaw.setup(XOR("fake yaw"), XOR("fake_yaw"), { XOR("off"), XOR("default"), XOR("relative"), XOR("jitter"), XOR("rotate"), XOR("random"), XOR("local view"), XOR("opposite"), XOR("spinter") });
		RegisterElement(&fake_yaw, 1);

		fake_relative.setup("", XOR("fake_relative"), -90.f, 90.f, false, 0, 0.f, 5.f, XOR(L"?"));
		fake_relative.AddShowCallback(callbacks::IsFakeAntiAimRelative);
		RegisterElement(&fake_relative, 1);

		fake_jitter_range.setup("", XOR("fake_jitter_range"), 1.f, 90.f, false, 0, 0.f, 5.f, XOR(L"?"));
		fake_jitter_range.AddShowCallback(callbacks::IsFakeAntiAimJitter);
		RegisterElement(&fake_jitter_range, 1);

		pitch_fake_stand.setup(XOR("fake pitch"), XOR("pitch_fake_stand"), { XOR("off"), XOR("up") });
		pitch_fake_stand.AddShowCallback(callbacks::IsAntiAimModeStand);
		pitch_fake_stand.AddShowCallback(callbacks::HasStandYaw);
		//RegisterElement(&pitch_fake_stand, 1);

		// col 2.
		lag_enable.setup(XOR("fake-lag"), XOR("lag_enable"));
		RegisterElement(&lag_enable, 1);

		lag_active.setup("", XOR("lag_active"), { XOR("always") ,XOR("move"), XOR("air"), XOR("crouch") }, false);
		RegisterElement(&lag_active, 1);

		lag_mode.setup("", XOR("lag_mode"), { XOR("max"), XOR("break"), XOR("random"), XOR("break step") }, false);
		RegisterElement(&lag_mode, 1);

		lag_limit.setup(XOR("limit"), XOR("lag_limit"), 2, 16, true, 0, 2, 1.f);
		RegisterElement(&lag_limit, 1);

		lag_land.setup(XOR("on land"), XOR("lag_land"));
		RegisterElement(&lag_land, 1);

		disablefakelagonkey.setup(XOR("disable fake-lag on key"), XOR("disable fake-lag on key"));
		RegisterElement(&disablefakelagonkey, 1);

		/*fakeduck.setup(XOR("fake duck"), XOR("fakeduck"));
		RegisterElement(&fakeduck);*/
	}
};

class PlayersTab : public Tab {
public:
	Checkbox      box;
	Colorpicker   box_enemy;
	Checkbox      dormant;
	Checkbox      offscreen;
	Colorpicker   offscreen_color;
	Checkbox      name;
	Colorpicker   name_color;
	Checkbox      health;
	MultiDropdown flags_enemy;
	Checkbox      weapon;
	MultiDropdown weapon_mode;
	Checkbox      ammo;
	Checkbox      distance;
	Colorpicker   ammo_color;
	Checkbox      lby_update;
	Colorpicker   lby_update_color;

	// col2.
	Checkbox      skeleton;
	Colorpicker   skeleton_enemy;
	Checkbox      glow;
	Colorpicker   glow_enemy;
	Slider        glow_blend;
	Dropdown	  chams_selection;
	MultiDropdown chams_enemy;
	Colorpicker   chams_enemy_vis;
	Colorpicker   chams_enemy_invis;
	Slider        chams_enemy_blend;
	Checkbox      chams_enemy_history;
	Colorpicker   chams_enemy_history_col;
	Slider        chams_enemy_history_blend;
	Colorpicker   overlay_base_color_enemy_vis;
	Colorpicker   overlay_base_color_enemy_xqz;
	Checkbox      chams_local;
	Colorpicker   chams_local_col;
	Slider        chams_local_blend;
	Checkbox      chams_local_scope;
	Colorpicker   overlay_base_color_local;
	Checkbox      chams_fake;
	Dropdown	  chams_fake_mat;
	Colorpicker   chams_fake_col;
	Slider        chams_fake_blend;
	Checkbox      chams_custom_texture_local;
	Dropdown      chamstype_local;
	Checkbox      chams_custom_texture_enemy;
	Dropdown      chamstype_enemy;

public:
	void init() {
		SetTitle(XOR("players"));

		box.setup(XOR("box"), XOR("box"));
		RegisterElement(&box);

		box_enemy.setup(XOR("box color"), XOR("box_enemy"), colors::white);
		box_enemy.AddShowCallback(callbacks::IsBoxOn);
		RegisterElement(&box_enemy);

		dormant.setup(XOR("dormant enemies"), XOR("dormant"));
		RegisterElement(&dormant);

		offscreen.setup(XOR("enemy offscreen esp"), XOR("offscreen"));
		RegisterElement(&offscreen);

		offscreen_color.setup(XOR("offscreen esp color"), XOR("offscreen_color"), colors::white);
		offscreen_color.AddShowCallback(callbacks::IsOffscreenOn);
		RegisterElement(&offscreen_color);

		name.setup(XOR("name"), XOR("name"));
		RegisterElement(&name);

		name_color.setup(XOR("name color"), XOR("name_color"), colors::white);
		name_color.AddShowCallback(callbacks::IsNameOn);
		RegisterElement(&name_color);

		health.setup(XOR("health"), XOR("health"));
		RegisterElement(&health);

		flags_enemy.setup(XOR("flags enemy"), XOR("flags_enemy"), { XOR("money"), XOR("armor"), XOR("scoped"), XOR("flashed"), XOR("reloading"), XOR("bomb"), XOR("fake"), XOR("resolver mode") });
		RegisterElement(&flags_enemy);

		weapon.setup(XOR("weapon"), XOR("weapon"));
		RegisterElement(&weapon);

		weapon_mode.setup("", XOR("weapon_mode"), { XOR("text"), XOR("icon") }, false);
		weapon_mode.AddShowCallback(callbacks::IsWeaponOn);
		RegisterElement(&weapon_mode);

		distance.setup(XOR("distance"), XOR("distance"));
		RegisterElement(&distance);

		ammo.setup(XOR("ammo"), XOR("ammo"));
		RegisterElement(&ammo);

		ammo_color.setup(XOR("color"), XOR("ammo_color"), colors::light_blue);
		RegisterElement(&ammo_color);

		lby_update.setup(XOR("lby update"), XOR("lby_update"));
		RegisterElement(&lby_update);

		lby_update_color.setup(XOR("color"), XOR("lby_update_color"), colors::purple);
		RegisterElement(&lby_update_color);

		// col2.
		chams_selection.setup(XOR("player chams"), XOR("chams_selection"), { XOR("local"), XOR("enemy") });
		RegisterElement(&chams_selection, 1);

		chams_enemy.setup(XOR("chams"), XOR("chams_enemy"), { XOR("visible"), XOR("invisible") });
		chams_enemy.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&chams_enemy, 1);

		chams_enemy_vis.setup(XOR("color visible"), XOR("chams_enemy_vis"), { 150, 200, 60 });
		chams_enemy_vis.AddShowCallback(callbacks::IsChamsVisible);
		chams_enemy_vis.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&chams_enemy_vis, 1);

		chams_enemy_invis.setup(XOR("color invisible"), XOR("chams_enemy_invis"), { 60, 180, 225 });
		chams_enemy_invis.AddShowCallback(callbacks::IsChamsInvisible);
		chams_enemy_invis.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&chams_enemy_invis, 1);

		overlay_base_color_enemy_vis.setup(XOR("base vis"), XOR("overlay_base_color_enemy_vis"), { 0, 0, 0 });
		overlay_base_color_enemy_vis.AddShowCallback(callbacks::IsEnemyChams);
		overlay_base_color_enemy_vis.AddShowCallback(callbacks::IsGlowOverlayOnEnemy);
		RegisterElement(&overlay_base_color_enemy_vis, 1);

		overlay_base_color_enemy_xqz.setup(XOR("base xqz"), XOR("overlay_base_color_enemy_xqz"), { 0, 0, 0 });
		overlay_base_color_enemy_xqz.AddShowCallback(callbacks::IsEnemyChams);
		overlay_base_color_enemy_xqz.AddShowCallback(callbacks::IsGlowOverlayOnEnemy);
		RegisterElement(&overlay_base_color_enemy_xqz, 1);

		chams_enemy_blend.setup("", XOR("chams_enemy_blend"), 0.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		chams_enemy_blend.AddShowCallback(callbacks::IsChamsVisibleOrInvisible);
		chams_enemy_blend.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&chams_enemy_blend, 1);

		chams_enemy_history.setup(XOR("chams history"), XOR("chams_history"));
		chams_enemy_history.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&chams_enemy_history, 1);

		chams_enemy_history_col.setup(XOR("color"), XOR("chams_history_col"), { 255, 255, 255 });
		chams_enemy_history_col.AddShowCallback(callbacks::IsHistoryOn);
		chams_enemy_history_col.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&chams_enemy_history_col, 1);

		chams_enemy_history_blend.setup("", XOR("chams_history_blend"), 0.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		chams_enemy_history_blend.AddShowCallback(callbacks::IsHistoryOn);
		chams_enemy_history_blend.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&chams_enemy_history_blend, 1);

		skeleton.setup(XOR("skeleton"), XOR("skeleton"));
		skeleton.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&skeleton, 1);

		skeleton_enemy.setup(XOR("color"), XOR("skeleton_enemy"), { 255, 255, 255 });
		skeleton_enemy.AddShowCallback(callbacks::IsSkeletonOn);
		skeleton_enemy.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&skeleton_enemy, 1);

		glow.setup(XOR("glow"), XOR("glow"));
		glow.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&glow, 1);

		glow_enemy.setup(XOR("color"), XOR("glow_enemy"), { 180, 60, 120 });
		glow_enemy.AddShowCallback(callbacks::IsGlowOn);
		glow_enemy.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&glow_enemy, 1);

		glow_blend.setup("", XOR("glow_blend"), 0.f, 100.f, false, 0, 60.f, 1.f, XOR(L"%"));
		glow_blend.AddShowCallback(callbacks::IsGlowOn);
		glow_blend.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&glow_blend, 1);

		chams_local.setup(XOR("chams local"), XOR("chams_local"));
		chams_local.AddShowCallback(callbacks::IsLocalChams2);
		RegisterElement(&chams_local, 1);

		chams_local_col.setup(XOR("color"), XOR("chams_local_col"), { 255, 255, 255 });
		chams_local_col.AddShowCallback(callbacks::IsLocalChams2);
		chams_local_col.AddShowCallback(callbacks::IsLocalChams);
		RegisterElement(&chams_local_col, 1);

		overlay_base_color_local.setup(XOR("overlay base"), XOR("overlay_base_color_local"), { 0, 0, 0 });
		overlay_base_color_local.AddShowCallback(callbacks::IsLocalChams);
		overlay_base_color_local.AddShowCallback(callbacks::IsLocalChams2);
		overlay_base_color_local.AddShowCallback(callbacks::IsGlowOverlayOnLocal);
		RegisterElement(&overlay_base_color_local, 1);

		chams_local_blend.setup("", XOR("chams_local_blend"), 0.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		chams_local_blend.AddShowCallback(callbacks::IsLocalChams2);
		chams_local_blend.AddShowCallback(callbacks::IsLocalChams);
		RegisterElement(&chams_local_blend, 1);

		chams_local_scope.setup(XOR("blend when scoped"), XOR("chams_local_scope"));
		chams_local_scope.AddShowCallback(callbacks::IsLocalChams);
		chams_local_scope.AddShowCallback(callbacks::IsLocalChams2);
		RegisterElement(&chams_local_scope, 1);

		chams_fake.setup(XOR("fake chams"), XOR("chams_fake"));
		chams_fake.AddShowCallback(callbacks::IsLocalChams);
		chams_fake.AddShowCallback(callbacks::IsLocalChams2);
		RegisterElement(&chams_fake, 1);

		chams_fake_mat.setup(XOR("fake material"), XOR("chams_fake_mat"), { XOR("normal"), XOR("flat") });
		chams_fake_mat.AddShowCallback(callbacks::IsFakeChams);
		chams_fake_mat.AddShowCallback(callbacks::IsLocalChams);
		chams_fake_mat.AddShowCallback(callbacks::IsLocalChams2);
		RegisterElement(&chams_fake_mat, 1);

		chams_fake_col.setup(XOR("color"), XOR("chams_fake_col"), { 255, 255, 255 });
		chams_fake_col.AddShowCallback(callbacks::IsFakeChams);
		chams_fake_col.AddShowCallback(callbacks::IsLocalChams);
		chams_fake_col.AddShowCallback(callbacks::IsLocalChams2);
		RegisterElement(&chams_fake_col, 1);

		chams_fake_blend.setup("", XOR("chams_fake_blend"), 0.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		chams_fake_blend.AddShowCallback(callbacks::IsFakeChams);
		chams_fake_blend.AddShowCallback(callbacks::IsLocalChams);
		chams_fake_blend.AddShowCallback(callbacks::IsLocalChams2);
		RegisterElement(&chams_fake_blend, 1);

		chamstype_local.setup(XOR("chams type"), XOR("chamstype_local"), { XOR("texture"), XOR("flat"), XOR("rainbow chams"), XOR("eso chams") });
		chamstype_local.AddShowCallback(callbacks::IsLocalChams);
		chamstype_local.AddShowCallback(callbacks::IsLocalChams2);
		RegisterElement(&chamstype_local, 1);

		chamstype_enemy.setup(XOR("chams type"), XOR("chamstype_enemy"), { XOR("texture"), XOR("flat"), XOR("rainbow chams"), XOR("eso chams") });
		chamstype_enemy.AddShowCallback(callbacks::IsEnemyChams);
		RegisterElement(&chamstype_enemy, 1);
	}
};

class VisualsTab : public Tab {
public:
	Checkbox      distance;
	Checkbox      items;
	Colorpicker   item_color;
	Checkbox      ammo;
	Colorpicker   dropammo_color;
	Checkbox      proj;
	Colorpicker   proj_color;
	MultiDropdown proj_range;
	Colorpicker   proj_range_color;
	MultiDropdown planted_c4;
	Checkbox      disableteam;
	Dropdown	  world;
	Slider        night_darkness;
	//	  world_color;
	Checkbox      transparent_props;
	Slider		  transparent_props_amount;
	Checkbox      enemy_radar;
	Checkbox      chams_local_scope;
	Checkbox      draw_angles;

	// col2.
	MultiDropdown removals;
	Checkbox      fov;
	Slider        fov_amt;
	Checkbox      fov_scoped;
	Checkbox      viewmodel_fov;
	Slider        viewmodel_fov_amt;
	Checkbox      spectators;
	Checkbox      force_xhair;
	Checkbox      spread_xhair;
	Colorpicker   spread_xhair_col;
	Slider        spread_xhair_blend;
	Checkbox      pen_crosshair;
	Checkbox      pen_damage;
	//MultiDropdown indicators;
	Checkbox	  indicators;
	Dropdown      indicators_type;
	Slider		  indicators_position_y;
	Slider        indicators_position_x;
	Dropdown      lby_indicator_type;
	Checkbox      tracers;
	Checkbox      impact_beams;
	Checkbox      impact_beams_rainbow;
	Colorpicker   impact_beams_color;
	Colorpicker   impact_beams_hurt_color;
	Slider        impact_beams_time;
	Keybind       thirdperson;
	Slider		  thirdperson_distance;

public:
	void init() {
		SetTitle(XOR("visuals"));

		items.setup(XOR("dropped weapons"), XOR("items"));
		RegisterElement(&items);

		distance.setup(XOR("distance weapons"), XOR("distance"));
		RegisterElement(&distance);

		item_color.setup(XOR("color"), XOR("item_color"), colors::white);
		RegisterElement(&item_color);

		ammo.setup(XOR("dropped weapons ammo"), XOR("ammo"));
		RegisterElement(&ammo);

		dropammo_color.setup(XOR("color"), XOR("dropammo_color"), colors::light_blue);
		RegisterElement(&dropammo_color);

		proj.setup(XOR("projectiles"), XOR("proj"));
		RegisterElement(&proj);

		proj_color.setup(XOR("color"), XOR("proj_color"), colors::white);
		RegisterElement(&proj_color);

		planted_c4.setup(XOR("planted c4"), XOR("planted_c4"), { XOR("on screen (2D)"), XOR("on bomb (3D)") });
		RegisterElement(&planted_c4);

		world.setup(XOR("world"), XOR("world"), { XOR("off"), XOR("night"), XOR("fullbright") });
		world.SetCallback(Visuals::ModulateWorld);
		RegisterElement(&world);

		night_darkness.setup("", XOR("night_darkness"), 0.f, 100.f, false, 0, 10.f, 1.f, XOR(L"%"));
		night_darkness.SetCallback(Visuals::ModulateWorld);
		night_darkness.AddShowCallback(callbacks::IsNightMode);
		RegisterElement(&night_darkness);

		transparent_props.setup(XOR("transparent props"), XOR("transparent_props"));
		transparent_props.SetCallback(Visuals::ModulateWorld);
		RegisterElement(&transparent_props);

		transparent_props_amount.setup("", XOR("transparent_props_amount"), 0.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		transparent_props_amount.SetCallback(Visuals::ModulateWorld);
		transparent_props_amount.AddShowCallback(callbacks::IsTransparentProps);
		RegisterElement(&transparent_props_amount);

		enemy_radar.setup(XOR("force enemies on radar"), XOR("enemy_radar"));
		RegisterElement(&enemy_radar);

		draw_angles.setup(XOR("draw angles"), XOR("draw_angles"));
		RegisterElement(&draw_angles);

		// col2.
		removals.setup(XOR("removals"), XOR("removals"), { "recoil", "smoke", "fog", "flash", "scope" });
		RegisterElement(&removals, 1);

		fov.setup(XOR("override fov"), XOR("fov"));
		RegisterElement(&fov, 1);

		fov_amt.setup("", XOR("fov_amt"), 60.f, 140.f, false, 0, 90.f, 1.f, XOR(L"?"));
		RegisterElement(&fov_amt, 1);

		fov_scoped.setup(XOR("override fov when scoped"), XOR("fov_scoped"));
		RegisterElement(&fov_scoped, 1);

		/*	viewmodel_fov.setup(XOR("override viewmodel fov"), XOR("viewmodel_fov"));
			RegisterElement(&viewmodel_fov, 1);*/

		viewmodel_fov_amt.setup("", XOR("viewmodel_fov_amt"), 60.f, 140.f, false, 0, 90.f, 1.f, XOR(L"?"));
		RegisterElement(&viewmodel_fov_amt, 1);

		spectators.setup(XOR("show spectator list"), XOR("spectators"));
		RegisterElement(&spectators, 1);

		force_xhair.setup(XOR("force crosshair"), XOR("force_xhair"));
		RegisterElement(&force_xhair, 1);

		spread_xhair.setup(XOR("visualize spread"), XOR("spread_xhair"));
		RegisterElement(&spread_xhair, 1);

		spread_xhair_col.setup(XOR("visualize spread color"), XOR("spread_xhair_col"), colors::burgundy);
		RegisterElement(&spread_xhair_col, 1);

		spread_xhair_blend.setup("", XOR("spread_xhair_blend"), 10.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&spread_xhair_blend, 1);

		pen_crosshair.setup(XOR("penetration crosshair"), XOR("pen_xhair"));
		RegisterElement(&pen_crosshair, 1);

		pen_damage.setup(XOR("penetration crosshair damage"), XOR("pen_damage"));
		RegisterElement(&pen_damage, 1);

		indicators.setup(XOR("indicators"), XOR("indicators")/*, { XOR("lby"), XOR("lag compensation"), XOR("fake latency"), XOR("dmg override"), XOR("baim on key") }*/);
		RegisterElement(&indicators, 1);

		indicators_type.setup(XOR("indicators type"), XOR("indicators_type"), { XOR("BarbieHOOK"), XOR("supremacy") });
		indicators_type.AddShowCallback(callbacks::AreIndicatorsOn);
		//RegisterElement(&indicators_type, 1);

		lby_indicator_type.setup(XOR("lby indicator"), XOR("lby_indicator_type"), { XOR("off"), XOR("skeety"), XOR("fatality") });
		lby_indicator_type.AddShowCallback(callbacks::AreIndicatorsOn);
		//lby_indicator_type.AddShowCallback(callbacks::AreIndicatorsSupremacy);
		RegisterElement(&lby_indicator_type, 1);

		tracers.setup(XOR("grenade simulation"), XOR("tracers"));
		RegisterElement(&tracers, 1);

		impact_beams.setup(XOR("beam bullettracer"), XOR("impact_beams"));
		RegisterElement(&impact_beams, 1);

		impact_beams_rainbow.setup(XOR("rainbow bullettracer"), XOR("impact_beams_rainbow"));
		impact_beams_rainbow.AddShowCallback(callbacks::IsBulletTracerOn);
		RegisterElement(&impact_beams_rainbow, 1);

		impact_beams_color.setup(XOR("bullettracer color"), XOR("impact_beams_color"), colors::red);
		impact_beams_color.AddShowCallback(callbacks::IsBulletTracerOn);
		impact_beams_color.AddShowCallback(callbacks::IsRainbowTracerOff);
		RegisterElement(&impact_beams_color, 1);

		impact_beams_hurt_color.setup(XOR("bullettracer hurt color"), XOR("impact_beams_hurt_color"), colors::green);
		impact_beams_hurt_color.AddShowCallback(callbacks::IsBulletTracerOn);
		impact_beams_hurt_color.AddShowCallback(callbacks::IsRainbowTracerOff);
		RegisterElement(&impact_beams_hurt_color, 1);

		impact_beams_time.setup(XOR("bullettracer beam time"), XOR("impact_beams_time"), 1.f, 10.f, true, 0, 1.f, 1.f, XOR(L"s"));
		impact_beams_time.AddShowCallback(callbacks::IsBulletTracerOn);
		impact_beams_time.AddShowCallback(callbacks::IsRainbowTracerOff);
		RegisterElement(&impact_beams_time, 1);

		thirdperson.setup(XOR("thirdperson"), XOR("thirdperson"));
		thirdperson.SetToggleCallback(callbacks::ToggleThirdPerson);
		RegisterElement(&thirdperson, 1);

		thirdperson_distance.setup(XOR(" "), XOR("thirdperson_distance"), 50.f, 300.f, false, 0, 150.f, 1.f, XOR(L"?"));
		RegisterElement(&thirdperson_distance, 1);
	}
};

class MovementTab : public Tab {
public:
	Checkbox bhop;
	Checkbox airduck;
	Checkbox autostrafe;
	Keybind  cstrafe;
	Keybind  astrafe;
	Keybind  zstrafe;
	Slider   z_freq;
	Slider   z_dist;

	Keybind  fakewalk;
	Keybind  autopeek;
	Keybind  autostop;
	Checkbox autostop_always_on;

	//Checkbox auto_stop_between_shots;

public:
	void init() {
		SetTitle(XOR("move"));

		bhop.setup(XOR("automatic jump"), XOR("bhop"));
		RegisterElement(&bhop);

		airduck.setup(XOR("duck in air"), XOR("airduck"));
		RegisterElement(&airduck);

		autostrafe.setup(XOR("automatic strafe"), XOR("autostrafe"));
		RegisterElement(&autostrafe);

		cstrafe.setup(XOR("c-strafe"), XOR("cstrafe"));
		astrafe.setup(XOR("a-strafe"), XOR("astrafe"));
		zstrafe.setup(XOR("z-strafe"), XOR("zstrafe"));
		z_freq.setup("", XOR("z_freq"), 1.f, 100.f, false, 0, 50.f, 0.5f, XOR(L"hz"));
		z_dist.setup("", XOR("z_dist"), 1.f, 100.f, false, 0, 20.f, 0.5f, XOR(L"%"));

		fakewalk.setup(XOR("fake-walk"), XOR("fakewalk"));
		RegisterElement(&fakewalk, 1);

		autopeek.setup(XOR("automatic peek"), XOR("autopeek"));
		RegisterElement(&autopeek, 1);

		autostop_always_on.setup(XOR("automatic stop always on"), XOR("auto_stop_always"));
		RegisterElement(&autostop_always_on, 1);

		autostop_always_on.setup(XOR("automatic stop always on"), XOR("auto_stop_always"));
		RegisterElement(&autostop_always_on, 1);

		autostop.setup(XOR("automatic stop"), XOR("autostop"));
		autostop.AddShowCallback(callbacks::AUTO_STOP);
		RegisterElement(&autostop, 1);
	}
};

class SkinsTab : public Tab {
public:
	Checkbox enable;

	Edit     id_deagle;
	Checkbox stattrak_deagle;
	Slider   quality_deagle;
	Slider	 seed_deagle;

	Edit     id_elite;
	Checkbox stattrak_elite;
	Slider   quality_elite;
	Slider	 seed_elite;

	Edit     id_fiveseven;
	Checkbox stattrak_fiveseven;
	Slider   quality_fiveseven;
	Slider	 seed_fiveseven;

	Edit     id_glock;
	Checkbox stattrak_glock;
	Slider   quality_glock;
	Slider	 seed_glock;

	Edit     id_ak47;
	Checkbox stattrak_ak47;
	Slider   quality_ak47;
	Slider	 seed_ak47;

	Edit     id_aug;
	Checkbox stattrak_aug;
	Slider   quality_aug;
	Slider	 seed_aug;

	Edit     id_awp;
	Checkbox stattrak_awp;
	Slider   quality_awp;
	Slider	 seed_awp;

	Edit     id_famas;
	Checkbox stattrak_famas;
	Slider   quality_famas;
	Slider	 seed_famas;

	Edit     id_g3sg1;
	Checkbox stattrak_g3sg1;
	Slider   quality_g3sg1;
	Slider	 seed_g3sg1;

	Edit     id_galil;
	Checkbox stattrak_galil;
	Slider   quality_galil;
	Slider	 seed_galil;

	Edit     id_m249;
	Checkbox stattrak_m249;
	Slider   quality_m249;
	Slider	 seed_m249;

	Edit     id_m4a4;
	Checkbox stattrak_m4a4;
	Slider   quality_m4a4;
	Slider	 seed_m4a4;

	Edit     id_mac10;
	Checkbox stattrak_mac10;
	Slider   quality_mac10;
	Slider	 seed_mac10;

	Edit     id_p90;
	Checkbox stattrak_p90;
	Slider   quality_p90;
	Slider	 seed_p90;

	Edit     id_ump45;
	Checkbox stattrak_ump45;
	Slider   quality_ump45;
	Slider	 seed_ump45;

	Edit     id_xm1014;
	Checkbox stattrak_xm1014;
	Slider   quality_xm1014;
	Slider	 seed_xm1014;

	Edit     id_bizon;
	Checkbox stattrak_bizon;
	Slider   quality_bizon;
	Slider	 seed_bizon;

	Edit     id_mag7;
	Checkbox stattrak_mag7;
	Slider   quality_mag7;
	Slider	 seed_mag7;

	Edit     id_negev;
	Checkbox stattrak_negev;
	Slider   quality_negev;
	Slider	 seed_negev;

	Edit     id_sawedoff;
	Checkbox stattrak_sawedoff;
	Slider   quality_sawedoff;
	Slider	 seed_sawedoff;

	Edit     id_tec9;
	Checkbox stattrak_tec9;
	Slider   quality_tec9;
	Slider	 seed_tec9;

	Edit     id_p2000;
	Checkbox stattrak_p2000;
	Slider   quality_p2000;
	Slider	 seed_p2000;

	Edit     id_mp7;
	Checkbox stattrak_mp7;
	Slider   quality_mp7;
	Slider	 seed_mp7;

	Edit     id_mp9;
	Checkbox stattrak_mp9;
	Slider   quality_mp9;
	Slider	 seed_mp9;

	Edit     id_nova;
	Checkbox stattrak_nova;
	Slider   quality_nova;
	Slider	 seed_nova;

	Edit     id_p250;
	Checkbox stattrak_p250;
	Slider   quality_p250;
	Slider	 seed_p250;

	Edit     id_scar20;
	Checkbox stattrak_scar20;
	Slider   quality_scar20;
	Slider	 seed_scar20;

	Edit     id_sg553;
	Checkbox stattrak_sg553;
	Slider   quality_sg553;
	Slider	 seed_sg553;

	Edit     id_ssg08;
	Checkbox stattrak_ssg08;
	Slider   quality_ssg08;
	Slider	 seed_ssg08;

	Edit     id_m4a1s;
	Checkbox stattrak_m4a1s;
	Slider   quality_m4a1s;
	Slider	 seed_m4a1s;

	Edit     id_usps;
	Checkbox stattrak_usps;
	Slider   quality_usps;
	Slider	 seed_usps;

	Edit     id_cz75a;
	Checkbox stattrak_cz75a;
	Slider   quality_cz75a;
	Slider	 seed_cz75a;

	Edit     id_revolver;
	Checkbox stattrak_revolver;
	Slider   quality_revolver;
	Slider	 seed_revolver;

	Edit     id_bayonet;
	Checkbox stattrak_bayonet;
	Slider   quality_bayonet;
	Slider	 seed_bayonet;

	Edit     id_flip;
	Checkbox stattrak_flip;
	Slider   quality_flip;
	Slider	 seed_flip;

	Edit     id_gut;
	Checkbox stattrak_gut;
	Slider   quality_gut;
	Slider	 seed_gut;

	Edit     id_karambit;
	Checkbox stattrak_karambit;
	Slider   quality_karambit;
	Slider	 seed_karambit;

	Edit     id_m9;
	Checkbox stattrak_m9;
	Slider   quality_m9;
	Slider	 seed_m9;

	Edit     id_huntsman;
	Checkbox stattrak_huntsman;
	Slider   quality_huntsman;
	Slider	 seed_huntsman;

	Edit     id_falchion;
	Checkbox stattrak_falchion;
	Slider   quality_falchion;
	Slider	 seed_falchion;

	Edit     id_bowie;
	Checkbox stattrak_bowie;
	Slider   quality_bowie;
	Slider	 seed_bowie;

	Edit     id_butterfly;
	Checkbox stattrak_butterfly;
	Slider   quality_butterfly;
	Slider	 seed_butterfly;

	Edit     id_daggers;
	Checkbox stattrak_daggers;
	Slider   quality_daggers;
	Slider	 seed_daggers;

	// col 2.
	Dropdown knife;
	Dropdown glove;
	Edit	 glove_id;

public:
	void init() {
		SetTitle(XOR("skins"));

		enable.setup(XOR("enable"), XOR("skins_enable"));
		enable.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&enable);

		// weapons...
		id_deagle.setup(XOR("paintkit id"), XOR("id_deagle"), 3);
		id_deagle.SetCallback(callbacks::SkinUpdate);
		id_deagle.AddShowCallback(callbacks::DEAGLE);
		RegisterElement(&id_deagle);

		stattrak_deagle.setup(XOR("stattrak"), XOR("stattrak_deagle"));
		stattrak_deagle.SetCallback(callbacks::SkinUpdate);
		stattrak_deagle.AddShowCallback(callbacks::DEAGLE);
		RegisterElement(&stattrak_deagle);

		quality_deagle.setup(XOR("quality"), XOR("quality_deagle"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_deagle.SetCallback(callbacks::SkinUpdate);
		quality_deagle.AddShowCallback(callbacks::DEAGLE);
		RegisterElement(&quality_deagle);

		seed_deagle.setup(XOR("seed"), XOR("seed_deagle"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_deagle.SetCallback(callbacks::SkinUpdate);
		seed_deagle.AddShowCallback(callbacks::DEAGLE);
		RegisterElement(&seed_deagle);

		id_elite.setup(XOR("paintkit id"), XOR("id_elite"), 3);
		id_elite.SetCallback(callbacks::SkinUpdate);
		id_elite.AddShowCallback(callbacks::ELITE);
		RegisterElement(&id_elite);

		stattrak_elite.setup(XOR("stattrak"), XOR("stattrak_elite"));
		stattrak_elite.SetCallback(callbacks::SkinUpdate);
		stattrak_elite.AddShowCallback(callbacks::ELITE);
		RegisterElement(&stattrak_elite);

		quality_elite.setup(XOR("quality"), XOR("quality_elite"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_elite.SetCallback(callbacks::SkinUpdate);
		quality_elite.AddShowCallback(callbacks::ELITE);
		RegisterElement(&quality_elite);

		seed_elite.setup(XOR("seed"), XOR("seed_elite"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_elite.SetCallback(callbacks::SkinUpdate);
		seed_elite.AddShowCallback(callbacks::ELITE);
		RegisterElement(&seed_elite);

		id_fiveseven.setup(XOR("paintkit id"), XOR("id_fiveseven"), 3);
		id_fiveseven.SetCallback(callbacks::SkinUpdate);
		id_fiveseven.AddShowCallback(callbacks::FIVESEVEN);
		RegisterElement(&id_fiveseven);

		stattrak_fiveseven.setup(XOR("stattrak"), XOR("stattrak_fiveseven"));
		stattrak_fiveseven.SetCallback(callbacks::SkinUpdate);
		stattrak_fiveseven.AddShowCallback(callbacks::FIVESEVEN);
		RegisterElement(&stattrak_fiveseven);

		quality_fiveseven.setup(XOR("quality"), XOR("quality_fiveseven"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_fiveseven.SetCallback(callbacks::SkinUpdate);
		quality_fiveseven.AddShowCallback(callbacks::FIVESEVEN);
		RegisterElement(&quality_fiveseven);

		seed_fiveseven.setup(XOR("seed"), XOR("seed_fiveseven"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_fiveseven.SetCallback(callbacks::SkinUpdate);
		seed_fiveseven.AddShowCallback(callbacks::FIVESEVEN);
		RegisterElement(&seed_fiveseven);

		id_glock.setup(XOR("paintkit id"), XOR("id_glock"), 3);
		id_glock.SetCallback(callbacks::SkinUpdate);
		id_glock.AddShowCallback(callbacks::GLOCK);
		RegisterElement(&id_glock);

		stattrak_glock.setup(XOR("stattrak"), XOR("stattrak_glock"));
		stattrak_glock.SetCallback(callbacks::SkinUpdate);
		stattrak_glock.AddShowCallback(callbacks::GLOCK);
		RegisterElement(&stattrak_glock);

		quality_glock.setup(XOR("quality"), XOR("quality_glock"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_glock.SetCallback(callbacks::SkinUpdate);
		quality_glock.AddShowCallback(callbacks::GLOCK);
		RegisterElement(&quality_glock);

		seed_glock.setup(XOR("seed"), XOR("seed_glock"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_glock.SetCallback(callbacks::SkinUpdate);
		seed_glock.AddShowCallback(callbacks::GLOCK);
		RegisterElement(&seed_glock);

		id_ak47.setup(XOR("paintkit id"), XOR("id_ak47"), 3);
		id_ak47.SetCallback(callbacks::SkinUpdate);
		id_ak47.AddShowCallback(callbacks::AK47);
		RegisterElement(&id_ak47);

		stattrak_ak47.setup(XOR("stattrak"), XOR("stattrak_ak47"));
		stattrak_ak47.SetCallback(callbacks::SkinUpdate);
		stattrak_ak47.AddShowCallback(callbacks::AK47);
		RegisterElement(&stattrak_ak47);

		quality_ak47.setup(XOR("quality"), XOR("quality_ak47"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_ak47.SetCallback(callbacks::SkinUpdate);
		quality_ak47.AddShowCallback(callbacks::AK47);
		RegisterElement(&quality_ak47);

		seed_ak47.setup(XOR("seed"), XOR("seed_ak47"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_ak47.SetCallback(callbacks::SkinUpdate);
		seed_ak47.AddShowCallback(callbacks::AK47);
		RegisterElement(&seed_ak47);

		id_aug.setup(XOR("paintkit id"), XOR("id_aug"), 3);
		id_aug.SetCallback(callbacks::SkinUpdate);
		id_aug.AddShowCallback(callbacks::AUG);
		RegisterElement(&id_aug);

		stattrak_aug.setup(XOR("stattrak"), XOR("stattrak_aug"));
		stattrak_aug.SetCallback(callbacks::SkinUpdate);
		stattrak_aug.AddShowCallback(callbacks::AUG);
		RegisterElement(&stattrak_aug);

		quality_aug.setup(XOR("quality"), XOR("quality_aug"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_aug.SetCallback(callbacks::SkinUpdate);
		quality_aug.AddShowCallback(callbacks::AUG);
		RegisterElement(&quality_aug);

		seed_aug.setup(XOR("seed"), XOR("seed_aug"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_aug.SetCallback(callbacks::SkinUpdate);
		seed_aug.AddShowCallback(callbacks::AUG);
		RegisterElement(&seed_aug);

		id_awp.setup(XOR("paintkit id"), XOR("id_awp"), 3);
		id_awp.SetCallback(callbacks::SkinUpdate);
		id_awp.AddShowCallback(callbacks::AWP);
		RegisterElement(&id_awp);

		stattrak_awp.setup(XOR("stattrak"), XOR("stattrak_awp"));
		stattrak_awp.SetCallback(callbacks::SkinUpdate);
		stattrak_awp.AddShowCallback(callbacks::AWP);
		RegisterElement(&stattrak_awp);

		quality_awp.setup(XOR("quality"), XOR("quality_awp"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_awp.SetCallback(callbacks::SkinUpdate);
		quality_awp.AddShowCallback(callbacks::AWP);
		RegisterElement(&quality_awp);

		seed_awp.setup(XOR("seed"), XOR("seed_awp"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_awp.SetCallback(callbacks::SkinUpdate);
		seed_awp.AddShowCallback(callbacks::AWP);
		RegisterElement(&seed_awp);

		id_famas.setup(XOR("paintkit id"), XOR("id_famas"), 3);
		id_famas.SetCallback(callbacks::SkinUpdate);
		id_famas.AddShowCallback(callbacks::FAMAS);
		RegisterElement(&id_famas);

		stattrak_famas.setup(XOR("stattrak"), XOR("stattrak_famas"));
		stattrak_famas.SetCallback(callbacks::SkinUpdate);
		stattrak_famas.AddShowCallback(callbacks::FAMAS);
		RegisterElement(&stattrak_famas);

		quality_famas.setup(XOR("quality"), XOR("quality_famas"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_famas.SetCallback(callbacks::SkinUpdate);
		quality_famas.AddShowCallback(callbacks::FAMAS);
		RegisterElement(&quality_famas);

		seed_famas.setup(XOR("seed"), XOR("seed_famas"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_famas.SetCallback(callbacks::SkinUpdate);
		seed_famas.AddShowCallback(callbacks::FAMAS);
		RegisterElement(&seed_famas);

		id_g3sg1.setup(XOR("paintkit id"), XOR("id_g3sg1"), 3);
		id_g3sg1.SetCallback(callbacks::SkinUpdate);
		id_g3sg1.AddShowCallback(callbacks::G3SG1);
		RegisterElement(&id_g3sg1);

		stattrak_g3sg1.setup(XOR("stattrak"), XOR("stattrak_g3sg1"));
		stattrak_g3sg1.SetCallback(callbacks::SkinUpdate);
		stattrak_g3sg1.AddShowCallback(callbacks::G3SG1);
		RegisterElement(&stattrak_g3sg1);

		quality_g3sg1.setup(XOR("quality"), XOR("quality_g3sg1"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_g3sg1.SetCallback(callbacks::SkinUpdate);
		quality_g3sg1.AddShowCallback(callbacks::G3SG1);
		RegisterElement(&quality_g3sg1);

		seed_g3sg1.setup(XOR("seed"), XOR("seed_g3sg1"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_g3sg1.SetCallback(callbacks::SkinUpdate);
		seed_g3sg1.AddShowCallback(callbacks::G3SG1);
		RegisterElement(&seed_g3sg1);

		id_galil.setup(XOR("paintkit id"), XOR("id_galil"), 3);
		id_galil.SetCallback(callbacks::SkinUpdate);
		id_galil.AddShowCallback(callbacks::GALIL);
		RegisterElement(&id_galil);

		stattrak_galil.setup(XOR("stattrak"), XOR("stattrak_galil"));
		stattrak_galil.SetCallback(callbacks::SkinUpdate);
		stattrak_galil.AddShowCallback(callbacks::GALIL);
		RegisterElement(&stattrak_galil);

		quality_galil.setup(XOR("quality"), XOR("quality_galil"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_galil.SetCallback(callbacks::SkinUpdate);
		quality_galil.AddShowCallback(callbacks::GALIL);
		RegisterElement(&quality_galil);

		seed_galil.setup(XOR("seed"), XOR("seed_galil"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_galil.SetCallback(callbacks::SkinUpdate);
		seed_galil.AddShowCallback(callbacks::GALIL);
		RegisterElement(&seed_galil);

		id_m249.setup(XOR("paintkit id"), XOR("id_m249"), 3);
		id_m249.SetCallback(callbacks::SkinUpdate);
		id_m249.AddShowCallback(callbacks::M249);
		RegisterElement(&id_m249);

		stattrak_m249.setup(XOR("stattrak"), XOR("stattrak_m249"));
		stattrak_m249.SetCallback(callbacks::SkinUpdate);
		stattrak_m249.AddShowCallback(callbacks::M249);
		RegisterElement(&stattrak_m249);

		quality_m249.setup(XOR("quality"), XOR("quality_m249"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_m249.SetCallback(callbacks::SkinUpdate);
		quality_m249.AddShowCallback(callbacks::M249);
		RegisterElement(&quality_m249);

		seed_m249.setup(XOR("seed"), XOR("seed_m249"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_m249.SetCallback(callbacks::SkinUpdate);
		seed_m249.AddShowCallback(callbacks::M249);
		RegisterElement(&seed_m249);

		id_m4a4.setup(XOR("paintkit id"), XOR("id_m4a4"), 3);
		id_m4a4.SetCallback(callbacks::SkinUpdate);
		id_m4a4.AddShowCallback(callbacks::M4A4);
		RegisterElement(&id_m4a4);

		stattrak_m4a4.setup(XOR("stattrak"), XOR("stattrak_m4a4"));
		stattrak_m4a4.SetCallback(callbacks::SkinUpdate);
		stattrak_m4a4.AddShowCallback(callbacks::M4A4);
		RegisterElement(&stattrak_m4a4);

		quality_m4a4.setup(XOR("quality"), XOR("quality_m4a4"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_m4a4.SetCallback(callbacks::SkinUpdate);
		quality_m4a4.AddShowCallback(callbacks::M4A4);
		RegisterElement(&quality_m4a4);

		seed_m4a4.setup(XOR("seed"), XOR("seed_m4a4"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_m4a4.SetCallback(callbacks::SkinUpdate);
		seed_m4a4.AddShowCallback(callbacks::M4A4);
		RegisterElement(&seed_m4a4);

		id_mac10.setup(XOR("paintkit id"), XOR("id_mac10"), 3);
		id_mac10.SetCallback(callbacks::SkinUpdate);
		id_mac10.AddShowCallback(callbacks::MAC10);
		RegisterElement(&id_mac10);

		stattrak_mac10.setup(XOR("stattrak"), XOR("stattrak_mac10"));
		stattrak_mac10.SetCallback(callbacks::SkinUpdate);
		stattrak_mac10.AddShowCallback(callbacks::MAC10);
		RegisterElement(&stattrak_mac10);

		quality_mac10.setup(XOR("quality"), XOR("quality_mac10"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_mac10.SetCallback(callbacks::SkinUpdate);
		quality_mac10.AddShowCallback(callbacks::MAC10);
		RegisterElement(&quality_mac10);

		seed_mac10.setup(XOR("seed"), XOR("seed_mac10"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_mac10.SetCallback(callbacks::SkinUpdate);
		seed_mac10.AddShowCallback(callbacks::MAC10);
		RegisterElement(&seed_mac10);

		id_p90.setup(XOR("paintkit id"), XOR("id_p90"), 3);
		id_p90.SetCallback(callbacks::SkinUpdate);
		id_p90.AddShowCallback(callbacks::P90);
		RegisterElement(&id_p90);

		stattrak_p90.setup(XOR("stattrak"), XOR("stattrak_p90"));
		stattrak_p90.SetCallback(callbacks::SkinUpdate);
		stattrak_p90.AddShowCallback(callbacks::P90);
		RegisterElement(&stattrak_p90);

		quality_p90.setup(XOR("quality"), XOR("quality_p90"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_p90.SetCallback(callbacks::SkinUpdate);
		quality_p90.AddShowCallback(callbacks::P90);
		RegisterElement(&quality_p90);

		seed_p90.setup(XOR("seed"), XOR("seed_p90"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_p90.SetCallback(callbacks::SkinUpdate);
		seed_p90.AddShowCallback(callbacks::P90);
		RegisterElement(&seed_p90);

		id_ump45.setup(XOR("paintkit id"), XOR("id_ump45"), 3);
		id_ump45.SetCallback(callbacks::SkinUpdate);
		id_ump45.AddShowCallback(callbacks::UMP45);
		RegisterElement(&id_ump45);

		stattrak_ump45.setup(XOR("stattrak"), XOR("stattrak_ump45"));
		stattrak_ump45.SetCallback(callbacks::SkinUpdate);
		stattrak_ump45.AddShowCallback(callbacks::UMP45);
		RegisterElement(&stattrak_ump45);

		quality_ump45.setup(XOR("quality"), XOR("quality_ump45"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_ump45.SetCallback(callbacks::SkinUpdate);
		quality_ump45.AddShowCallback(callbacks::UMP45);
		RegisterElement(&quality_ump45);

		seed_ump45.setup(XOR("seed"), XOR("seed_ump45"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_ump45.SetCallback(callbacks::SkinUpdate);
		seed_ump45.AddShowCallback(callbacks::UMP45);
		RegisterElement(&seed_ump45);

		id_xm1014.setup(XOR("paintkit id"), XOR("id_xm1014"), 3);
		id_xm1014.SetCallback(callbacks::SkinUpdate);
		id_xm1014.AddShowCallback(callbacks::XM1014);
		RegisterElement(&id_xm1014);

		stattrak_xm1014.setup(XOR("stattrak"), XOR("stattrak_xm1014"));
		stattrak_xm1014.SetCallback(callbacks::SkinUpdate);
		stattrak_xm1014.AddShowCallback(callbacks::XM1014);
		RegisterElement(&stattrak_xm1014);

		quality_xm1014.setup(XOR("quality"), XOR("quality_xm1014"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_xm1014.SetCallback(callbacks::SkinUpdate);
		quality_xm1014.AddShowCallback(callbacks::XM1014);
		RegisterElement(&quality_xm1014);

		seed_xm1014.setup(XOR("seed"), XOR("seed_xm1014"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_xm1014.SetCallback(callbacks::SkinUpdate);
		seed_xm1014.AddShowCallback(callbacks::XM1014);
		RegisterElement(&seed_xm1014);

		id_bizon.setup(XOR("paintkit id"), XOR("id_bizon"), 3);
		id_bizon.SetCallback(callbacks::SkinUpdate);
		id_bizon.AddShowCallback(callbacks::BIZON);
		RegisterElement(&id_bizon);

		stattrak_bizon.setup(XOR("stattrak"), XOR("stattrak_bizon"));
		stattrak_bizon.SetCallback(callbacks::SkinUpdate);
		stattrak_bizon.AddShowCallback(callbacks::BIZON);
		RegisterElement(&stattrak_bizon);

		quality_bizon.setup(XOR("quality"), XOR("quality_bizon"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_bizon.SetCallback(callbacks::SkinUpdate);
		quality_bizon.AddShowCallback(callbacks::BIZON);
		RegisterElement(&quality_bizon);

		seed_bizon.setup(XOR("seed"), XOR("seed_bizon"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_bizon.SetCallback(callbacks::SkinUpdate);
		seed_bizon.AddShowCallback(callbacks::BIZON);
		RegisterElement(&seed_bizon);

		id_mag7.setup(XOR("paintkit id"), XOR("id_mag7"), 3);
		id_mag7.SetCallback(callbacks::SkinUpdate);
		id_mag7.AddShowCallback(callbacks::MAG7);
		RegisterElement(&id_mag7);

		stattrak_mag7.setup(XOR("stattrak"), XOR("stattrak_mag7"));
		stattrak_mag7.SetCallback(callbacks::SkinUpdate);
		stattrak_mag7.AddShowCallback(callbacks::MAG7);
		RegisterElement(&stattrak_mag7);

		quality_mag7.setup(XOR("quality"), XOR("quality_mag7"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_mag7.SetCallback(callbacks::SkinUpdate);
		quality_mag7.AddShowCallback(callbacks::MAG7);
		RegisterElement(&quality_mag7);

		seed_mag7.setup(XOR("seed"), XOR("seed_mag7"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_mag7.SetCallback(callbacks::SkinUpdate);
		seed_mag7.AddShowCallback(callbacks::MAG7);
		RegisterElement(&seed_mag7);

		id_negev.setup(XOR("paintkit id"), XOR("id_negev"), 3);
		id_negev.SetCallback(callbacks::SkinUpdate);
		id_negev.AddShowCallback(callbacks::NEGEV);
		RegisterElement(&id_negev);

		stattrak_negev.setup(XOR("stattrak"), XOR("stattrak_negev"));
		stattrak_negev.SetCallback(callbacks::SkinUpdate);
		stattrak_negev.AddShowCallback(callbacks::NEGEV);
		RegisterElement(&stattrak_negev);

		quality_negev.setup(XOR("quality"), XOR("quality_negev"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_negev.SetCallback(callbacks::SkinUpdate);
		quality_negev.AddShowCallback(callbacks::NEGEV);
		RegisterElement(&quality_negev);

		seed_negev.setup(XOR("seed"), XOR("seed_negev"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_negev.SetCallback(callbacks::SkinUpdate);
		seed_negev.AddShowCallback(callbacks::NEGEV);
		RegisterElement(&seed_negev);

		id_sawedoff.setup(XOR("paintkit id"), XOR("id_sawedoff"), 3);
		id_sawedoff.SetCallback(callbacks::SkinUpdate);
		id_sawedoff.AddShowCallback(callbacks::SAWEDOFF);
		RegisterElement(&id_sawedoff);

		stattrak_sawedoff.setup(XOR("stattrak"), XOR("stattrak_sawedoff"));
		stattrak_sawedoff.SetCallback(callbacks::SkinUpdate);
		stattrak_sawedoff.AddShowCallback(callbacks::SAWEDOFF);
		RegisterElement(&stattrak_sawedoff);

		quality_sawedoff.setup(XOR("quality"), XOR("quality_sawedoff"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_sawedoff.SetCallback(callbacks::SkinUpdate);
		quality_sawedoff.AddShowCallback(callbacks::SAWEDOFF);
		RegisterElement(&quality_sawedoff);

		seed_sawedoff.setup(XOR("seed"), XOR("seed_sawedoff"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_sawedoff.SetCallback(callbacks::SkinUpdate);
		seed_sawedoff.AddShowCallback(callbacks::SAWEDOFF);
		RegisterElement(&seed_sawedoff);

		id_tec9.setup(XOR("paintkit id"), XOR("id_tec9"), 3);
		id_tec9.SetCallback(callbacks::SkinUpdate);
		id_tec9.AddShowCallback(callbacks::TEC9);
		RegisterElement(&id_tec9);

		stattrak_tec9.setup(XOR("stattrak"), XOR("stattrak_tec9"));
		stattrak_tec9.SetCallback(callbacks::SkinUpdate);
		stattrak_tec9.AddShowCallback(callbacks::TEC9);
		RegisterElement(&stattrak_tec9);

		quality_tec9.setup(XOR("quality"), XOR("quality_tec9"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_tec9.SetCallback(callbacks::SkinUpdate);
		quality_tec9.AddShowCallback(callbacks::TEC9);
		RegisterElement(&quality_tec9);

		seed_tec9.setup(XOR("seed"), XOR("seed_tec9"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_tec9.SetCallback(callbacks::SkinUpdate);
		seed_tec9.AddShowCallback(callbacks::TEC9);
		RegisterElement(&seed_tec9);

		id_p2000.setup(XOR("paintkit id"), XOR("id_p2000"), 3);
		id_p2000.SetCallback(callbacks::SkinUpdate);
		id_p2000.AddShowCallback(callbacks::P2000);
		RegisterElement(&id_p2000);

		stattrak_p2000.setup(XOR("stattrak"), XOR("stattrak_p2000"));
		stattrak_p2000.SetCallback(callbacks::SkinUpdate);
		stattrak_p2000.AddShowCallback(callbacks::P2000);
		RegisterElement(&stattrak_p2000);

		quality_p2000.setup(XOR("quality"), XOR("quality_p2000"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_p2000.SetCallback(callbacks::SkinUpdate);
		quality_p2000.AddShowCallback(callbacks::P2000);
		RegisterElement(&quality_p2000);

		seed_p2000.setup(XOR("seed"), XOR("seed_p2000"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_p2000.SetCallback(callbacks::SkinUpdate);
		seed_p2000.AddShowCallback(callbacks::P2000);
		RegisterElement(&seed_p2000);

		id_mp7.setup(XOR("paintkit id"), XOR("id_mp7"), 3);
		id_mp7.SetCallback(callbacks::SkinUpdate);
		id_mp7.AddShowCallback(callbacks::MP7);
		RegisterElement(&id_mp7);

		stattrak_mp7.setup(XOR("stattrak"), XOR("stattrak_mp7"));
		stattrak_mp7.SetCallback(callbacks::SkinUpdate);
		stattrak_mp7.AddShowCallback(callbacks::MP7);
		RegisterElement(&stattrak_mp7);

		quality_mp7.setup(XOR("quality"), XOR("quality_mp7"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_mp7.SetCallback(callbacks::SkinUpdate);
		quality_mp7.AddShowCallback(callbacks::MP7);
		RegisterElement(&quality_mp7);

		seed_mp7.setup(XOR("seed"), XOR("seed_mp7"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_mp7.SetCallback(callbacks::SkinUpdate);
		seed_mp7.AddShowCallback(callbacks::MP7);
		RegisterElement(&seed_mp7);

		id_mp9.setup(XOR("paintkit id"), XOR("id_mp9"), 3);
		id_mp9.SetCallback(callbacks::SkinUpdate);
		id_mp9.AddShowCallback(callbacks::MP9);
		RegisterElement(&id_mp9);

		stattrak_mp9.setup(XOR("stattrak"), XOR("stattrak_mp9"));
		stattrak_mp9.SetCallback(callbacks::SkinUpdate);
		stattrak_mp9.AddShowCallback(callbacks::MP9);
		RegisterElement(&stattrak_mp9);

		quality_mp9.setup(XOR("quality"), XOR("quality_mp9"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_mp9.SetCallback(callbacks::SkinUpdate);
		quality_mp9.AddShowCallback(callbacks::MP9);
		RegisterElement(&quality_mp9);

		seed_mp9.setup(XOR("seed"), XOR("seed_mp9"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_mp9.SetCallback(callbacks::SkinUpdate);
		seed_mp9.AddShowCallback(callbacks::MP9);
		RegisterElement(&seed_mp9);

		id_nova.setup(XOR("paintkit id"), XOR("id_nova"), 3);
		id_nova.SetCallback(callbacks::SkinUpdate);
		id_nova.AddShowCallback(callbacks::NOVA);
		RegisterElement(&id_nova);

		stattrak_nova.setup(XOR("stattrak"), XOR("stattrak_nova"));
		stattrak_nova.SetCallback(callbacks::SkinUpdate);
		stattrak_nova.AddShowCallback(callbacks::NOVA);
		RegisterElement(&stattrak_nova);

		quality_nova.setup(XOR("quality"), XOR("quality_nova"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_nova.SetCallback(callbacks::SkinUpdate);
		quality_nova.AddShowCallback(callbacks::NOVA);
		RegisterElement(&quality_nova);

		seed_nova.setup(XOR("seed"), XOR("seed_nova"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_nova.SetCallback(callbacks::SkinUpdate);
		seed_nova.AddShowCallback(callbacks::NOVA);
		RegisterElement(&seed_nova);

		id_p250.setup(XOR("paintkit id"), XOR("id_p250"), 3);
		id_p250.SetCallback(callbacks::SkinUpdate);
		id_p250.AddShowCallback(callbacks::P250);
		RegisterElement(&id_p250);

		stattrak_p250.setup(XOR("stattrak"), XOR("stattrak_p250"));
		stattrak_p250.SetCallback(callbacks::SkinUpdate);
		stattrak_p250.AddShowCallback(callbacks::P250);
		RegisterElement(&stattrak_p250);

		quality_p250.setup(XOR("quality"), XOR("quality_p250"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_p250.SetCallback(callbacks::SkinUpdate);
		quality_p250.AddShowCallback(callbacks::P250);
		RegisterElement(&quality_p250);

		seed_p250.setup(XOR("seed"), XOR("seed_p250"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_p250.SetCallback(callbacks::SkinUpdate);
		seed_p250.AddShowCallback(callbacks::P250);
		RegisterElement(&seed_p250);

		id_scar20.setup(XOR("paintkit id"), XOR("id_scar20"), 3);
		id_scar20.SetCallback(callbacks::SkinUpdate);
		id_scar20.AddShowCallback(callbacks::SCAR20);
		RegisterElement(&id_scar20);

		stattrak_scar20.setup(XOR("stattrak"), XOR("stattrak_scar20"));
		stattrak_scar20.SetCallback(callbacks::SkinUpdate);
		stattrak_scar20.AddShowCallback(callbacks::SCAR20);
		RegisterElement(&stattrak_scar20);

		quality_scar20.setup(XOR("quality"), XOR("quality_scar20"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_scar20.SetCallback(callbacks::SkinUpdate);
		quality_scar20.AddShowCallback(callbacks::SCAR20);
		RegisterElement(&quality_scar20);

		seed_scar20.setup(XOR("seed"), XOR("seed_scar20"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_scar20.SetCallback(callbacks::SkinUpdate);
		seed_scar20.AddShowCallback(callbacks::SCAR20);
		RegisterElement(&seed_scar20);

		id_sg553.setup(XOR("paintkit id"), XOR("id_sg553"), 3);
		id_sg553.SetCallback(callbacks::SkinUpdate);
		id_sg553.AddShowCallback(callbacks::SG553);
		RegisterElement(&id_sg553);

		stattrak_sg553.setup(XOR("stattrak"), XOR("stattrak_sg553"));
		stattrak_sg553.SetCallback(callbacks::SkinUpdate);
		stattrak_sg553.AddShowCallback(callbacks::SG553);
		RegisterElement(&stattrak_sg553);

		quality_sg553.setup(XOR("quality"), XOR("quality_sg553"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_sg553.SetCallback(callbacks::SkinUpdate);
		quality_sg553.AddShowCallback(callbacks::SG553);
		RegisterElement(&quality_sg553);

		seed_sg553.setup(XOR("seed"), XOR("seed_sg553"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_sg553.SetCallback(callbacks::SkinUpdate);
		seed_sg553.AddShowCallback(callbacks::SG553);
		RegisterElement(&seed_sg553);

		id_ssg08.setup(XOR("paintkit id"), XOR("id_ssg08"), 3);
		id_ssg08.SetCallback(callbacks::SkinUpdate);
		id_ssg08.AddShowCallback(callbacks::SSG08);
		RegisterElement(&id_ssg08);

		stattrak_ssg08.setup(XOR("stattrak"), XOR("stattrak_ssg08"));
		stattrak_ssg08.SetCallback(callbacks::SkinUpdate);
		stattrak_ssg08.AddShowCallback(callbacks::SSG08);
		RegisterElement(&stattrak_ssg08);

		quality_ssg08.setup(XOR("quality"), XOR("quality_ssg08"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_ssg08.SetCallback(callbacks::SkinUpdate);
		quality_ssg08.AddShowCallback(callbacks::SSG08);
		RegisterElement(&quality_ssg08);

		seed_ssg08.setup(XOR("seed"), XOR("seed_ssg08"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_ssg08.SetCallback(callbacks::SkinUpdate);
		seed_ssg08.AddShowCallback(callbacks::SSG08);
		RegisterElement(&seed_ssg08);

		id_m4a1s.setup(XOR("paintkit id"), XOR("id_m4a1s"), 3);
		id_m4a1s.SetCallback(callbacks::SkinUpdate);
		id_m4a1s.AddShowCallback(callbacks::M4A1S);
		RegisterElement(&id_m4a1s);

		stattrak_m4a1s.setup(XOR("stattrak"), XOR("stattrak_m4a1s"));
		stattrak_m4a1s.SetCallback(callbacks::SkinUpdate);
		stattrak_m4a1s.AddShowCallback(callbacks::M4A1S);
		RegisterElement(&stattrak_m4a1s);

		quality_m4a1s.setup(XOR("quality"), XOR("quality_m4a1s"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_m4a1s.SetCallback(callbacks::SkinUpdate);
		quality_m4a1s.AddShowCallback(callbacks::M4A1S);
		RegisterElement(&quality_m4a1s);

		seed_m4a1s.setup(XOR("seed"), XOR("seed_m4a1s"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_m4a1s.SetCallback(callbacks::SkinUpdate);
		seed_m4a1s.AddShowCallback(callbacks::M4A1S);
		RegisterElement(&seed_m4a1s);

		id_usps.setup(XOR("paintkit id"), XOR("id_usps"), 3);
		id_usps.SetCallback(callbacks::SkinUpdate);
		id_usps.AddShowCallback(callbacks::USPS);
		RegisterElement(&id_usps);

		stattrak_usps.setup(XOR("stattrak"), XOR("stattrak_usps"));
		stattrak_usps.SetCallback(callbacks::SkinUpdate);
		stattrak_usps.AddShowCallback(callbacks::USPS);
		RegisterElement(&stattrak_usps);

		quality_usps.setup(XOR("quality"), XOR("quality_usps"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_usps.SetCallback(callbacks::SkinUpdate);
		quality_usps.AddShowCallback(callbacks::USPS);
		RegisterElement(&quality_usps);

		seed_usps.setup(XOR("seed"), XOR("seed_usps"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_usps.SetCallback(callbacks::SkinUpdate);
		seed_usps.AddShowCallback(callbacks::USPS);
		RegisterElement(&seed_usps);

		id_cz75a.setup(XOR("paintkit id"), XOR("id_cz75a"), 3);
		id_cz75a.SetCallback(callbacks::SkinUpdate);
		id_cz75a.AddShowCallback(callbacks::CZ75A);
		RegisterElement(&id_cz75a);

		stattrak_cz75a.setup(XOR("stattrak"), XOR("stattrak_cz75a"));
		stattrak_cz75a.SetCallback(callbacks::SkinUpdate);
		stattrak_cz75a.AddShowCallback(callbacks::CZ75A);
		RegisterElement(&stattrak_cz75a);

		quality_cz75a.setup(XOR("quality"), XOR("quality_cz75a"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_cz75a.SetCallback(callbacks::SkinUpdate);
		quality_cz75a.AddShowCallback(callbacks::CZ75A);
		RegisterElement(&quality_cz75a);

		seed_cz75a.setup(XOR("seed"), XOR("seed_cz75a"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_cz75a.SetCallback(callbacks::SkinUpdate);
		seed_cz75a.AddShowCallback(callbacks::CZ75A);
		RegisterElement(&seed_cz75a);

		id_revolver.setup(XOR("paintkit id"), XOR("id_revolver"), 3);
		id_revolver.SetCallback(callbacks::SkinUpdate);
		id_revolver.AddShowCallback(callbacks::REVOLVER);
		RegisterElement(&id_revolver);

		stattrak_revolver.setup(XOR("stattrak"), XOR("stattrak_revolver"));
		stattrak_revolver.SetCallback(callbacks::SkinUpdate);
		stattrak_revolver.AddShowCallback(callbacks::REVOLVER);
		RegisterElement(&stattrak_revolver);

		quality_revolver.setup(XOR("quality"), XOR("quality_revolver"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_revolver.SetCallback(callbacks::SkinUpdate);
		quality_revolver.AddShowCallback(callbacks::REVOLVER);
		RegisterElement(&quality_revolver);

		seed_revolver.setup(XOR("seed"), XOR("seed_revolver"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_revolver.SetCallback(callbacks::SkinUpdate);
		seed_revolver.AddShowCallback(callbacks::REVOLVER);
		RegisterElement(&seed_revolver);

		id_bayonet.setup(XOR("paintkit id"), XOR("id_bayonet"), 3);
		id_bayonet.SetCallback(callbacks::SkinUpdate);
		id_bayonet.AddShowCallback(callbacks::KNIFE_BAYONET);
		RegisterElement(&id_bayonet);

		stattrak_bayonet.setup(XOR("stattrak"), XOR("stattrak_bayonet"));
		stattrak_bayonet.SetCallback(callbacks::SkinUpdate);
		stattrak_bayonet.AddShowCallback(callbacks::KNIFE_BAYONET);
		RegisterElement(&stattrak_bayonet);

		quality_bayonet.setup(XOR("quality"), XOR("quality_bayonet"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_bayonet.SetCallback(callbacks::SkinUpdate);
		quality_bayonet.AddShowCallback(callbacks::KNIFE_BAYONET);
		RegisterElement(&quality_bayonet);

		seed_bayonet.setup(XOR("seed"), XOR("seed_bayonet"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_bayonet.SetCallback(callbacks::SkinUpdate);
		seed_bayonet.AddShowCallback(callbacks::KNIFE_BAYONET);
		RegisterElement(&seed_bayonet);

		id_flip.setup(XOR("paintkit id"), XOR("id_flip"), 3);
		id_flip.SetCallback(callbacks::SkinUpdate);
		id_flip.AddShowCallback(callbacks::KNIFE_FLIP);
		RegisterElement(&id_flip);

		stattrak_flip.setup(XOR("stattrak"), XOR("stattrak_flip"));
		stattrak_flip.SetCallback(callbacks::SkinUpdate);
		stattrak_flip.AddShowCallback(callbacks::KNIFE_FLIP);
		RegisterElement(&stattrak_flip);

		quality_flip.setup(XOR("quality"), XOR("quality_flip"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_flip.SetCallback(callbacks::SkinUpdate);
		quality_flip.AddShowCallback(callbacks::KNIFE_FLIP);
		RegisterElement(&quality_flip);

		seed_flip.setup(XOR("seed"), XOR("seed_flip"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_flip.SetCallback(callbacks::SkinUpdate);
		seed_flip.AddShowCallback(callbacks::KNIFE_FLIP);
		RegisterElement(&seed_flip);

		id_gut.setup(XOR("paintkit id"), XOR("id_gut"), 3);
		id_gut.SetCallback(callbacks::SkinUpdate);
		id_gut.AddShowCallback(callbacks::KNIFE_GUT);
		RegisterElement(&id_gut);

		stattrak_gut.setup(XOR("stattrak"), XOR("stattrak_gut"));
		stattrak_gut.SetCallback(callbacks::SkinUpdate);
		stattrak_gut.AddShowCallback(callbacks::KNIFE_GUT);
		RegisterElement(&stattrak_gut);

		quality_gut.setup(XOR("quality"), XOR("quality_gut"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_gut.SetCallback(callbacks::SkinUpdate);
		quality_gut.AddShowCallback(callbacks::KNIFE_GUT);
		RegisterElement(&quality_gut);

		seed_gut.setup(XOR("seed"), XOR("seed_gut"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_gut.SetCallback(callbacks::SkinUpdate);
		seed_gut.AddShowCallback(callbacks::KNIFE_GUT);
		RegisterElement(&seed_gut);

		id_karambit.setup(XOR("paintkit id"), XOR("id_karambit"), 3);
		id_karambit.SetCallback(callbacks::SkinUpdate);
		id_karambit.AddShowCallback(callbacks::KNIFE_KARAMBIT);
		RegisterElement(&id_karambit);

		stattrak_karambit.setup(XOR("stattrak"), XOR("stattrak_karambit"));
		stattrak_karambit.SetCallback(callbacks::SkinUpdate);
		stattrak_karambit.AddShowCallback(callbacks::KNIFE_KARAMBIT);
		RegisterElement(&stattrak_karambit);

		quality_karambit.setup(XOR("quality"), XOR("quality_karambit"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_karambit.SetCallback(callbacks::SkinUpdate);
		quality_karambit.AddShowCallback(callbacks::KNIFE_KARAMBIT);
		RegisterElement(&quality_karambit);

		seed_karambit.setup(XOR("seed"), XOR("seed_karambit"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_karambit.SetCallback(callbacks::SkinUpdate);
		seed_karambit.AddShowCallback(callbacks::KNIFE_KARAMBIT);
		RegisterElement(&seed_karambit);

		id_m9.setup(XOR("paintkit id"), XOR("id_m9"), 3);
		id_m9.SetCallback(callbacks::SkinUpdate);
		id_m9.AddShowCallback(callbacks::KNIFE_M9_BAYONET);
		RegisterElement(&id_m9);

		stattrak_m9.setup(XOR("stattrak"), XOR("stattrak_m9"));
		stattrak_m9.SetCallback(callbacks::SkinUpdate);
		stattrak_m9.AddShowCallback(callbacks::KNIFE_M9_BAYONET);
		RegisterElement(&stattrak_m9);

		quality_m9.setup(XOR("quality"), XOR("quality_m9"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_m9.SetCallback(callbacks::SkinUpdate);
		quality_m9.AddShowCallback(callbacks::KNIFE_M9_BAYONET);
		RegisterElement(&quality_m9);

		seed_m9.setup(XOR("seed"), XOR("seed_m9"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_m9.SetCallback(callbacks::SkinUpdate);
		seed_m9.AddShowCallback(callbacks::KNIFE_M9_BAYONET);
		RegisterElement(&seed_m9);

		id_huntsman.setup(XOR("paintkit id"), XOR("id_huntsman"), 3);
		id_huntsman.SetCallback(callbacks::SkinUpdate);
		id_huntsman.AddShowCallback(callbacks::KNIFE_HUNTSMAN);
		RegisterElement(&id_huntsman);

		stattrak_huntsman.setup(XOR("stattrak"), XOR("stattrak_huntsman"));
		stattrak_huntsman.SetCallback(callbacks::SkinUpdate);
		stattrak_huntsman.AddShowCallback(callbacks::KNIFE_HUNTSMAN);
		RegisterElement(&stattrak_huntsman);

		quality_huntsman.setup(XOR("quality"), XOR("quality_huntsman"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_huntsman.SetCallback(callbacks::SkinUpdate);
		quality_huntsman.AddShowCallback(callbacks::KNIFE_HUNTSMAN);
		RegisterElement(&quality_huntsman);

		seed_huntsman.setup(XOR("seed"), XOR("seed_huntsman"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_huntsman.SetCallback(callbacks::SkinUpdate);
		seed_huntsman.AddShowCallback(callbacks::KNIFE_HUNTSMAN);
		RegisterElement(&seed_huntsman);

		id_falchion.setup(XOR("paintkit id"), XOR("id_falchion"), 3);
		id_falchion.SetCallback(callbacks::SkinUpdate);
		id_falchion.AddShowCallback(callbacks::KNIFE_FALCHION);
		RegisterElement(&id_falchion);

		stattrak_falchion.setup(XOR("stattrak"), XOR("stattrak_falchion"));
		stattrak_falchion.SetCallback(callbacks::SkinUpdate);
		stattrak_falchion.AddShowCallback(callbacks::KNIFE_FALCHION);
		RegisterElement(&stattrak_falchion);

		quality_falchion.setup(XOR("quality"), XOR("quality_falchion"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_falchion.SetCallback(callbacks::SkinUpdate);
		quality_falchion.AddShowCallback(callbacks::KNIFE_FALCHION);
		RegisterElement(&quality_falchion);

		seed_falchion.setup(XOR("seed"), XOR("seed_falchion"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_falchion.SetCallback(callbacks::SkinUpdate);
		seed_falchion.AddShowCallback(callbacks::KNIFE_FALCHION);
		RegisterElement(&seed_falchion);

		id_bowie.setup(XOR("paintkit id"), XOR("id_bowie"), 3);
		id_bowie.SetCallback(callbacks::SkinUpdate);
		id_bowie.AddShowCallback(callbacks::KNIFE_BOWIE);
		RegisterElement(&id_bowie);

		stattrak_bowie.setup(XOR("stattrak"), XOR("stattrak_bowie"));
		stattrak_bowie.SetCallback(callbacks::SkinUpdate);
		stattrak_bowie.AddShowCallback(callbacks::KNIFE_BOWIE);
		RegisterElement(&stattrak_bowie);

		quality_bowie.setup(XOR("quality"), XOR("quality_bowie"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_bowie.SetCallback(callbacks::SkinUpdate);
		quality_bowie.AddShowCallback(callbacks::KNIFE_BOWIE);
		RegisterElement(&quality_bowie);

		seed_bowie.setup(XOR("seed"), XOR("seed_bowie"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_bowie.SetCallback(callbacks::SkinUpdate);
		seed_bowie.AddShowCallback(callbacks::KNIFE_BOWIE);
		RegisterElement(&seed_bowie);

		id_butterfly.setup(XOR("paintkit id"), XOR("id_butterfly"), 3);
		id_butterfly.SetCallback(callbacks::SkinUpdate);
		id_butterfly.AddShowCallback(callbacks::KNIFE_BUTTERFLY);
		RegisterElement(&id_butterfly);

		stattrak_butterfly.setup(XOR("stattrak"), XOR("stattrak_butterfly"));
		stattrak_butterfly.SetCallback(callbacks::SkinUpdate);
		stattrak_butterfly.AddShowCallback(callbacks::KNIFE_BUTTERFLY);
		RegisterElement(&stattrak_butterfly);

		quality_butterfly.setup(XOR("quality"), XOR("quality_butterfly"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_butterfly.SetCallback(callbacks::SkinUpdate);
		quality_butterfly.AddShowCallback(callbacks::KNIFE_BUTTERFLY);
		RegisterElement(&quality_butterfly);

		seed_butterfly.setup(XOR("seed"), XOR("seed_butterfly"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_butterfly.SetCallback(callbacks::SkinUpdate);
		seed_butterfly.AddShowCallback(callbacks::KNIFE_BUTTERFLY);
		RegisterElement(&seed_butterfly);

		id_daggers.setup(XOR("paintkit id"), XOR("id_daggers"), 3);
		id_daggers.SetCallback(callbacks::SkinUpdate);
		id_daggers.AddShowCallback(callbacks::KNIFE_SHADOW_DAGGERS);
		RegisterElement(&id_daggers);

		stattrak_daggers.setup(XOR("stattrak"), XOR("stattrak_daggers"));
		stattrak_daggers.SetCallback(callbacks::SkinUpdate);
		stattrak_daggers.AddShowCallback(callbacks::KNIFE_SHADOW_DAGGERS);
		RegisterElement(&stattrak_daggers);

		quality_daggers.setup(XOR("quality"), XOR("quality_daggers"), 1.f, 100.f, true, 0, 100.f, 1.f, XOR(L"%"));
		quality_daggers.SetCallback(callbacks::SkinUpdate);
		quality_daggers.AddShowCallback(callbacks::KNIFE_SHADOW_DAGGERS);
		RegisterElement(&quality_daggers);

		seed_daggers.setup(XOR("seed"), XOR("seed_daggers"), 0.f, 255.f, true, 0, 0.f, 1.f);
		seed_daggers.SetCallback(callbacks::SkinUpdate);
		seed_daggers.AddShowCallback(callbacks::KNIFE_SHADOW_DAGGERS);
		RegisterElement(&seed_daggers);

		// col 2.
		knife.setup(XOR("knife model"), XOR("skins_knife_model"), { XOR("off"), XOR("bayonet"), XOR("bowie"), XOR("butterfly"), XOR("falchion"), XOR("flip"), XOR("gut"), XOR("huntsman"), XOR("karambit"), XOR("m9 bayonet"), XOR("daggers") });
		knife.SetCallback(callbacks::SkinUpdate);
		RegisterElement(&knife, 1);

		glove.setup(XOR("glove model"), XOR("skins_glove_model"), { XOR("off"), XOR("bloodhound"), XOR("sport"), XOR("driver"), XOR("handwraps"), XOR("moto"), XOR("specialist") });
		glove.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&glove, 1);

		glove_id.setup(XOR("glove paintkit id"), XOR("skins_glove_id"), 5);
		glove_id.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&glove_id, 1);
	}
};

class MiscTab : public Tab {
public:
	// col1.
	MultiDropdown buy1;
	MultiDropdown buy2;
	MultiDropdown buy3;
	MultiDropdown notifications;
	Keybind       last_tick_defuse;
	Keybind       fake_latency;
	Slider		  fake_latency_amt;
	Checkbox	  debug_mode;

	// col2.
	Checkbox autoaccept;
	Checkbox unlock;
	Checkbox hitmarker;
	Dropdown hitmarker_dropdown;
	Checkbox ragdoll_force;
	Checkbox killfeed;
	Checkbox clantag;
	Checkbox killsay;
	Checkbox funny_on_death;
	Checkbox slide_walk;
	Checkbox indicators;
	Checkbox indicators_status;
	Checkbox watermark;
	Dropdown rainbow_menu_type;
	Checkbox ranks;
	Button   HiddenCvar;

	Checkbox      fov;
	Slider        fov_amt;
	Checkbox      fov_scoped;
	Checkbox      viewmodel_override;
	Slider        viewmodel_fov;
	Slider        viewmodel_offset_x;
	Slider        viewmodel_offset_y;
	Slider        viewmodel_offset_z;

public:
	void init() {
		SetTitle(XOR("misc"));

		buy1.setup(XOR("auto buy items"), XOR("auto_buy1"),
			{
				XOR("galilar"),
				XOR("famas"),
				XOR("ak47"),
				XOR("m4a1"),
				XOR("m4a1_silencer"),
				XOR("ssg08"),
				XOR("aug"),
				XOR("sg556"),
				XOR("awp"),
				XOR("scar20"),
				XOR("g3sg1"),
				XOR("nova"),
				XOR("xm1014"),
				XOR("mag7"),
				XOR("m249"),
				XOR("negev"),
				XOR("mac10"),
				XOR("mp9"),
				XOR("mp7"),
				XOR("ump45"),
				XOR("p90"),
				XOR("bizon"),
			});
		RegisterElement(&buy1);

		buy2.setup("", XOR("auto_buy2"),
			{
				XOR("glock"),
				XOR("hkp2000"),
				XOR("usp_silencer"),
				XOR("elite"),
				XOR("p250"),
				XOR("tec9"),
				XOR("fn57"),
				XOR("deagle"),
			}, false);
		RegisterElement(&buy2);

		buy3.setup("", XOR("auto_buy3"),
			{
				XOR("vest"),
				XOR("vesthelm"),
				XOR("taser"),
				XOR("defuser"),
				XOR("heavyarmor"),
				XOR("molotov"),
				XOR("incgrenade"),
				XOR("decoy"),
				XOR("flashbang"),
				XOR("hegrenade"),
				XOR("smokegrenade"),
			}, false);
		RegisterElement(&buy3);

		notifications.setup(XOR("notifications"), XOR("notifications"), { XOR("matchmaking"), XOR("damage"), XOR("harmed"), XOR("purchases") });
		RegisterElement(&notifications);

		last_tick_defuse.setup(XOR("last tick defuse"), XOR("last_tick_defuse"));
		RegisterElement(&last_tick_defuse);

		fake_latency.setup(XOR("fake latency"), XOR("fake_latency"));
		fake_latency.SetToggleCallback(callbacks::ToggleFakeLatency);
		RegisterElement(&fake_latency);

		fake_latency_amt.setup("", XOR("fake_latency_amt"), 50.f, 1000.f, false, 0, 200.f, 50.f, XOR(L"ms"));
		RegisterElement(&fake_latency_amt);

		debug_mode.setup(XOR("debug mode"), XOR("debug_mode"));
		RegisterElement(&debug_mode);

		// col2.
		autoaccept.setup(XOR("auto-accept matchmaking"), XOR("autoaccept"));

		unlock.setup(XOR("unlock inventory in-game"), XOR("unlock_inventory"));
		RegisterElement(&unlock, 1);

		hitmarker.setup(XOR("hitmarker"), XOR("hitmarker"));
		RegisterElement(&hitmarker, 1);

		hitmarker_dropdown.setup(XOR("hitmarker sound"), XOR("hitmarker_dropdown"), { XOR("skeet"), XOR("bell"), XOR("fatality"), XOR("bonk"), XOR("neverlose"), XOR("cod"), XOR("bameware") });
		hitmarker_dropdown.AddShowCallback(callbacks::IsHitmarker);
		RegisterElement(&hitmarker_dropdown, 1);

		ragdoll_force.setup(XOR("ragdoll force"), XOR("ragdoll_force"));
		RegisterElement(&ragdoll_force, 1);

		killfeed.setup(XOR("preserve killfeed"), XOR("killfeed"));
		killfeed.SetCallback(callbacks::ToggleKillfeed);
		RegisterElement(&killfeed, 1);

		clantag.setup(XOR("clantag"), XOR("clantag"));
		RegisterElement(&clantag, 1);

		watermark.setup(XOR("watermark"), XOR("watermark"));
		RegisterElement(&watermark, 1);

		rainbow_menu_type.setup(XOR("rainbow type"), XOR("rainbow_menu_type"), { XOR("off"), XOR("static"), XOR("wave") });
		rainbow_menu_type.AddShowCallback(callbacks::IsWatermarkOn);
		RegisterElement(&rainbow_menu_type, 1);

		killsay.setup(XOR("killsay"), XOR("killsay"));
		RegisterElement(&killsay, 1);

		funny_on_death.setup(XOR("funny on death"), XOR("funny_on_death"));
		RegisterElement(&funny_on_death, 1);

		slide_walk.setup(XOR("slide walk"), XOR("slide_walk"));
		RegisterElement(&slide_walk, 1);

		viewmodel_override.setup(XOR("override viewmodel"), XOR("viewmodel_override"));
		RegisterElement(&viewmodel_override, 1);

		viewmodel_fov.setup(XOR("viewmodel fov"), XOR("viewmodel_fov"), 60.f, 140.f, true, 0, 90.f, 1.f, XOR(L"?"));
		viewmodel_fov.AddShowCallback(callbacks::ViewFOVOverride);
		RegisterElement(&viewmodel_fov, 1);

		viewmodel_offset_x.setup(XOR("x offset"), XOR("viewmodel_offset_x"), -15.f, 15.f, true, 0, 0.f, 1.f, XOR(L"?"));
		viewmodel_offset_x.AddShowCallback(callbacks::ViewFOVOverride);
		RegisterElement(&viewmodel_offset_x, 1);

		viewmodel_offset_y.setup(XOR("y offset"), XOR("viewmodel_offset_y"), -15.f, 15.f, true, 0, 0.f, 1.f, XOR(L"?"));
		viewmodel_offset_y.AddShowCallback(callbacks::ViewFOVOverride);
		RegisterElement(&viewmodel_offset_y, 1);

		viewmodel_offset_z.setup(XOR("z offset"), XOR("viewmodel_offset_z"), -15.f, 15.f, true, 0, 0.f, 1.f, XOR(L"?"));
		viewmodel_offset_z.AddShowCallback(callbacks::ViewFOVOverride);
		RegisterElement(&viewmodel_offset_z, 1);

		HiddenCvar.setup(XOR("unlock hidden cvars"));
		HiddenCvar.SetCallback(callbacks::HiddenCvar);
		RegisterElement(&HiddenCvar, 1);
	}
};

class ConfigTab : public Tab {
public:
	Colorpicker menu_color;
	Dropdown agent_change;
	Checkbox enable_agent;
	Button your_dignity;
	Button mrxserver;
	Button emporium;

	Dropdown mode;
	Dropdown config;
	Keybind  key1;
	Keybind  key2;
	Keybind  key3;
	Keybind  key4;
	Keybind  key5;
	Button   save;
	Button   load;

public:

	void init() {
		SetTitle(XOR("config"));

		enable_agent.setup(XOR("enable agent changer"), XOR("enable_agent_model"));
		RegisterElement(&enable_agent);

		agent_change.setup(XOR("setup agent"), XOR("agent_changer"), { XOR("imposter"),  XOR("starwar"), XOR("bitch with tits 1"), XOR("black man"), XOR("bitch with tits 2") });
		agent_change.AddShowCallback(callbacks::IsAgentChanger);
		RegisterElement(&agent_change);

		menu_color.setup(XOR("menu color"), XOR("menu_color"), colors::red, &g_gui.m_color);
		RegisterElement(&menu_color);

		emporium.setup(XOR("Emporium"));
		emporium.SetCallback(callbacks::emporium_connect);
		RegisterElement(&emporium);

		your_dignity.setup(XOR("YourDignity"));
		your_dignity.SetCallback(callbacks::your_dignity_connect);
		RegisterElement(&your_dignity);

		mrxserver.setup(XOR("MrX"));
		mrxserver.SetCallback(callbacks::mrx_connect);
		RegisterElement(&mrxserver);

		mode.setup(XOR("safety mode"), XOR("mode"), { XOR("matchmaking"), XOR("no-spread") });
		RegisterElement(&mode, 1);

		config.setup(XOR("configuration"), XOR("cfg"), { XOR("Default"), XOR("HVH"), XOR("Extra #1"), XOR("Extra #2"), XOR("Extra #3") });
		config.RemoveFlags(ElementFlags::SAVE);
		RegisterElement(&config, 1);

		key1.setup(XOR("configuration key 1"), XOR("cfg_key1"));
		key1.RemoveFlags(ElementFlags::SAVE);
		key1.SetCallback(callbacks::SaveHotkeys);
		key1.AddShowCallback(callbacks::IsConfig1);
		key1.SetToggleCallback(callbacks::ConfigLoad1);

		key2.setup(XOR("configuration key 2"), XOR("cfg_key2"));
		key2.RemoveFlags(ElementFlags::SAVE);
		key2.SetCallback(callbacks::SaveHotkeys);
		key2.AddShowCallback(callbacks::IsConfig2);
		key2.SetToggleCallback(callbacks::ConfigLoad2);

		key3.setup(XOR("configuration key 3"), XOR("cfg_key3"));
		key3.RemoveFlags(ElementFlags::SAVE);
		key3.SetCallback(callbacks::SaveHotkeys);
		key3.AddShowCallback(callbacks::IsConfig3);
		key3.SetToggleCallback(callbacks::ConfigLoad3);

		key4.setup(XOR("configuration key 4"), XOR("cfg_key4"));
		key4.RemoveFlags(ElementFlags::SAVE);
		key4.SetCallback(callbacks::SaveHotkeys);
		key4.AddShowCallback(callbacks::IsConfig4);
		key4.SetToggleCallback(callbacks::ConfigLoad4);

		key5.setup(XOR("configuration key 5"), XOR("cfg_key5"));
		key5.RemoveFlags(ElementFlags::SAVE);
		key5.SetCallback(callbacks::SaveHotkeys);
		key5.AddShowCallback(callbacks::IsConfig5);
		key5.SetToggleCallback(callbacks::ConfigLoad5);

		save.setup(XOR("save"));
		save.SetCallback(callbacks::ConfigSave);
		RegisterElement(&save, 1);

		load.setup(XOR("load"));
		load.SetCallback(callbacks::ConfigLoad);
		RegisterElement(&load, 1);
	}
};

class MainForm : public Form {
public:
	// aimbot.
	AimbotTab    aimbot;
	AntiAimTab   antiaim;

	// visuals.
	PlayersTab	 players;
	VisualsTab	 visuals;

	// misc.
	MovementTab  movement;
	SkinsTab     skins;
	MiscTab	     misc;
	ConfigTab	 config;

public:
	void init() {
		SetPosition(50, 50);
		SetSize(520, 530);

		// aim.
		RegisterTab(&aimbot);
		aimbot.init();

		RegisterTab(&antiaim);
		antiaim.init();

		// visuals.
		RegisterTab(&players);
		players.init();

		RegisterTab(&visuals);
		visuals.init();

		// misc.
		RegisterTab(&movement);
		movement.init();

		RegisterTab(&skins);
		skins.init();

		RegisterTab(&misc);
		misc.init();

		RegisterTab(&config);
		config.init();
	}
};

class Menu {
public:
	MainForm main;

public:
	void init() {
		Colorpicker::init();

		main.init();
		g_gui.RegisterForm(&main, VK_INSERT);
	}
};

extern Menu g_menu;