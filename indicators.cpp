#include "includes.h"

hud_indicators g_indicators{ };

// Hardcoded too much
// indicators
void hud_indicators::Indicators()
{
	//if (!g_csgo.m_engine->IsInGame())
		//return;

	if (!g_menu.main.misc.indicators.get())
		return;

	g_csgo.m_engine->GetScreenSize(m_width, m_height);

	Color color = g_gui.m_color;
	int	x{ 8 };

	static unsigned int s, v, i;
	static float h, r, g, b, f, p, q, t;

	h = g_csgo.m_globals->m_realtime * 0.1f;
	s = 1;
	v = 1;

	i = floor(h * 6);
	f = h * 6 - i;
	p = v * (1 - s);
	q = v * (1 - f * s);
	t = v * (1 - (1 - f) * s);

	switch (i % 6)
	{
	case 0: r = v, g = t, b = p; break;
	case 1: r = q, g = v, b = p; break;
	case 2: r = p, g = v, b = t; break;
	case 3: r = p, g = q, b = v; break;
	case 4: r = t, g = p, b = v; break;
	case 5: r = v, g = p, b = q; break;
	}

	r = round(r * 255), g = round(g * 255), b = round(b * 255);

	// main window
	// alien calculations heh

	render::rect_filled(x + 10, m_height / 2 + 10, 200, 65, { 10, 10, 10, 160 });
	// overlay black.
	render::rect_filled(x + 10, m_height / 2 + 10, 200, 15 + 2, { 10, 10, 10, 200 });
	// line.
	//GradientLine2(x + 10, m_height / 2 + 10, 200, 2, Color(g, b, r, 255), Color(r, g, b, 255));
	//GradientLine2(x + 10, m_height / 2 + 10, 200, 2, Color(r, g, b, 255), Color(b, r, g, 255));
	if (g_menu.main.misc.rainbow_menu_type.get() == 0) {
		render::rect_filled(x + 10, m_height / 2 + 10, 200, 2, g_gui.m_color);
	}
	else if (g_menu.main.misc.rainbow_menu_type.get() == 1) {
		render::rect_filled(x + 10, m_height / 2 + 10, 200, 2, Color(r, g, b, 255));
	}
	else if (g_menu.main.misc.rainbow_menu_type.get() == 2) {
		render::gradient_line(x + 10, m_height / 2 + 10, 200, 2, Color(g, b, r, 255), Color(r, g, b, 255));
	}

	// black outline.
	render::rect(x + 10 - 1, m_height / 2 + 9, 202, 65 + 1, { 10, 10, 10, 200 });
	// text.
	render::hud.string(x + 10 + 100, m_height / 2 + 14, { 255, 255, 255, 255 }, "hotkeys", render::ALIGN_CENTER);
	render::hud.string(x + 10 + 6, m_height / 2 + 30, { 255, 255, 255, 255 }, "fake latency", render::ALIGN_LEFT);
	render::hud.string(x + 10 + 6, m_height / 2 + 40, { 255, 255, 255, 255 }, "body aim on key", render::ALIGN_LEFT);
	render::hud.string(x + 10 + 6, m_height / 2 + 50, { 255, 255, 255, 255 }, "damage override", render::ALIGN_LEFT);
	render::hud.string(x + 10 + 6, m_height / 2 + 60, { 255, 255, 255, 255 }, "gay-walk", render::ALIGN_LEFT);

	if (g_menu.main.misc.rainbow_menu_type.get()) {
		// condition dt if (g_menu.main.antiaim.desync_mode.get() != 0 || !g_menu.main.antiaim.desync.get())
		if (!g_aimbot.m_fake_latency)
			render::hud.string(x + 10 + 195, m_height / 2 + 30, { 255, 0, 0, 255 }, "disabled", render::ALIGN_RIGHT);
		else
			render::hud.string(x + 10 + 195, m_height / 2 + 30, Color(r, g, b, 255), "toggled", render::ALIGN_RIGHT);

		// baim
		if (!g_aimbot.m_baim_toggle)
			render::hud.string(x + 10 + 195, m_height / 2 + 40, { 255, 0, 0, 255 }, "disabled", render::ALIGN_RIGHT);
		else
			render::hud.string(x + 10 + 195, m_height / 2 + 40, Color(r, g, b, 255), "toggled", render::ALIGN_RIGHT);

		// min dmg
		if (!g_aimbot.m_damage_toggle)
			render::hud.string(x + 10 + 195, m_height / 2 + 50, { 255, 0, 0, 255 }, "disabled", render::ALIGN_RIGHT);
		else
			render::hud.string(x + 10 + 195, m_height / 2 + 50, Color(r, g, b, 255), "toggled", render::ALIGN_RIGHT);

		if (!g_aimbot.m_double_tap)
			render::hud.string(x + 10 + 195, m_height / 2 + 60, { 255, 0, 0, 255 }, "disabled", render::ALIGN_RIGHT);
		else
			render::hud.string(x + 10 + 195, m_height / 2 + 60, Color(r, g, b, 255), "toggled", render::ALIGN_RIGHT);
	}
	else {
		// condition dt if (g_menu.main.antiaim.desync_mode.get() != 0 || !g_menu.main.antiaim.desync.get())
		if (!g_aimbot.m_fake_latency)
			render::hud.string(x + 10 + 195, m_height / 2 + 30, { 255, 0, 0, 255 }, "disabled", render::ALIGN_RIGHT);
		else
			render::hud.string(x + 10 + 195, m_height / 2 + 30, g_gui.m_color, "toggled", render::ALIGN_RIGHT);

		// baim
		if (!g_aimbot.m_baim_toggle)
			render::hud.string(x + 10 + 195, m_height / 2 + 40, { 255, 0, 0, 255 }, "disabled", render::ALIGN_RIGHT);
		else
			render::hud.string(x + 10 + 195, m_height / 2 + 40, g_gui.m_color, "toggled", render::ALIGN_RIGHT);

		// min dmg
		if (!g_aimbot.m_damage_toggle)
			render::hud.string(x + 10 + 195, m_height / 2 + 50, { 255, 0, 0, 255 }, "disabled", render::ALIGN_RIGHT);
		else
			render::hud.string(x + 10 + 195, m_height / 2 + 50, g_gui.m_color, "toggled", render::ALIGN_RIGHT);

		if (!g_aimbot.m_double_tap)
			render::hud.string(x + 10 + 195, m_height / 2 + 60, { 255, 0, 0, 255 }, "disabled", render::ALIGN_RIGHT);
		else
			render::hud.string(x + 10 + 195, m_height / 2 + 60, g_gui.m_color, "toggled", render::ALIGN_RIGHT);
	}
}

void hud_indicators::StateIndicators()
{
	if (!g_csgo.m_engine->IsInGame())
		return;

	if (!g_menu.main.misc.indicators_status.get())
		return;

	g_csgo.m_engine->GetScreenSize(m_width, m_height);

	Color color = g_gui.m_color;

	int	x{ 8 };

	// what we are btw trying to draw...
	float dsync_height = g_cl.m_local->m_flPoseParameter()[11] * 58;	// this?
	float choke_value = g_csgo.m_cl->m_choked_commands;

	// dsync

	// outline
	render::rect_filled(x + 10, m_height / 1.6, 97, 6, { 10, 10, 10, 160 });
	// line.
	render::rect_filled(x + 10, m_height / 1.6, dsync_height * 1.67, 6, { color.r(), color.g(), color.b(), 255 });	// 97/58


	// outline
	render::rect_filled(x + 10, m_height / 1.6 + 35, 97, 6, { 10, 10, 10, 160 });
	// line.
	render::rect_filled(x + 10, m_height / 1.6 + 35, choke_value * (97 / 14.f), 6, { color.r(), color.g(), color.b(), 255 });
}
