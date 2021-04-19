#include "includes.h"
Resolver g_resolver{};;

LagRecord* Resolver::FindIdealRecord(AimPlayer* data) {
	LagRecord* first_valid, * current;

	if (data->m_records.empty())
		return nullptr;

	first_valid = nullptr;

	// iterate records.
	for (const auto& it : data->m_records) {
		if (it->dormant() || it->immune() || !it->valid())
			continue;

		// get current record.
		current = it.get();

		// first record that was valid, store it for later.
		if (!first_valid)
			first_valid = current;

		// try to find a record with a shot, lby update, walking or no anti-aim.
		if (it->m_shot || it->m_mode == Modes::RESOLVE_BODY || it->m_mode == Modes::RESOLVE_WALK || it->m_mode == Modes::RESOLVE_NONE)
			return current;
	}

	// none found above, return the first valid record if possible.
	return (first_valid) ? first_valid : nullptr;
}

LagRecord* Resolver::FindLastRecord(AimPlayer* data) {
	LagRecord* current;

	if (data->m_records.empty())
		return nullptr;

	// iterate records in reverse.
	for (auto it = data->m_records.crbegin(); it != data->m_records.crend(); ++it) {
		current = it->get();

		// if this record is valid.
		// we are done since we iterated in reverse.
		if (current->valid() && !current->immune() && !current->dormant())
			return current;
	}

	return nullptr;
}

void Resolver::OnBodyUpdate(Player* player, float value) {
	AimPlayer* data = &g_aimbot.m_players[player->index() - 1];

	// set data.
	data->m_old_body = data->m_body;
	data->m_body = value;
}

float Resolver::GetAwayAngle(LagRecord* record) {
	float  delta{ std::numeric_limits< float >::max() };
	vec3_t pos;
	ang_t  away;

	// other cheats predict you by their own latency.
	// they do this because, then they can put their away angle to exactly
	// where you are on the server at that moment in time.

	// the idea is that you would need to know where they 'saw' you when they created their user-command.
	// lets say you move on your client right now, this would take half of our latency to arrive at the server.
	// the delay between the server and the target client is compensated by themselves already, that is fortunate for us.

	// we have no historical origins.
	// no choice but to use the most recent one.
	//if( g_cl.m_net_pos.empty( ) ) {
	math::VectorAngles(g_cl.m_local->m_vecOrigin() - record->m_pred_origin, away);
	return away.y;
	//}

	// half of our rtt.
	// also known as the one-way delay.
	//float owd = ( g_cl.m_latency / 2.f );

	// since our origins are computed here on the client
	// we have to compensate for the delay between our client and the server
	// therefore the OWD should be subtracted from the target time.
	//float target = record->m_pred_time; //- owd;

	// iterate all.
	//for( const auto &net : g_cl.m_net_pos ) {
		// get the delta between this records time context
		// and the target time.
	//	float dt = std::abs( target - net.m_time );

		// the best origin.
	//	if( dt < delta ) {
	//		delta = dt;
	//		pos   = net.m_pos;
	//	}
	//}

	//math::VectorAngles( pos - record->m_pred_origin, away );
	//return away.y;
}

void Resolver::MatchShot(AimPlayer* data, LagRecord* record) {
	// do not attempt to do this in nospread mode.
	if (g_menu.main.config.mode.get() == 1)
		return;

	float shoot_time = -1.f;

	Weapon* weapon = data->m_player->GetActiveWeapon();
	if (weapon) {
		// with logging this time was always one tick behind.
		// so add one tick to the last shoot time.
		shoot_time = weapon->m_fLastShotTime() + g_csgo.m_globals->m_interval;
	}

	// this record has a shot on it.
	if (game::TIME_TO_TICKS(shoot_time) == game::TIME_TO_TICKS(record->m_sim_time)) {
		if (record->m_lag <= 2)
			record->m_shot = true;

		// more then 1 choke, cant hit pitch, apply prev pitch.
		else if (data->m_records.size() >= 2) {
			LagRecord* previous = data->m_records[1].get();

			if (previous && !previous->dormant())
				record->m_eye_angles.x = previous->m_eye_angles.x;
		}
	}
}

void Resolver::SetMode(LagRecord* record) {
	float speed = record->m_velocity.length_2d();

	if ((record->m_flags & FL_ONGROUND) && speed > 1.f && !record->m_fake_walk && !GetAsyncKeyState(g_menu.main.aimbot.override.get()))
		record->m_mode = Modes::RESOLVE_WALK;

	// if on ground, not moving or fakewalking.
	if ((record->m_flags & FL_ONGROUND) && (speed < 1.f || record->m_fake_walk) && !GetAsyncKeyState(g_menu.main.aimbot.override.get()))
		record->m_mode = Modes::RESOLVE_STAND;

	// if not on ground.
	else if (!(record->m_flags & FL_ONGROUND) && !GetAsyncKeyState(g_menu.main.aimbot.override.get()))
		record->m_mode = Modes::RESOLVE_AIR;

	else if (GetAsyncKeyState(g_menu.main.aimbot.override.get()))
		record->m_mode = Modes::RESOLVE_OVERRIDE;
}

void Resolver::ResolveAngles(Player* player, LagRecord* record) {
	AimPlayer* data = &g_aimbot.m_players[player->index() - 1];

	// mark this record if it contains a shot.
	MatchShot(data, record);

	// next up mark this record with a resolver mode that will be used.
	SetMode(record);

	if (g_menu.main.config.mode.get() == 1)
		record->m_eye_angles.x = 90.f;

	// we arrived here we can do the acutal resolve.
	if (record->m_mode == Modes::RESOLVE_WALK)
		ResolveWalk(data, record);

	else if (record->m_mode == Modes::RESOLVE_STAND)
		ResolveStand(data, record, player);

	else if (record->m_mode == Modes::RESOLVE_AIR)
		ResolveAir(data, record, player);

	else if (record->m_mode == Modes::RESOLVE_OVERRIDE)
		ResolveOverride(player, record, data);

	// normalize the eye angles, doesn't really matter but its clean.
	math::NormalizeAngle(record->m_eye_angles.y);
}

void Resolver::ResolveWalk(AimPlayer* data, LagRecord* record) {
	// apply lby to eyeangles.
	record->m_eye_angles.y = record->m_body;

	// delay body update.
	//data->m_body_update = record->m_anim_time + 0.22f;

	// reset stand and body index.
	data->m_stand_index = 0;
	data->m_stand_index2 = 0;
	data->m_body_index = 0;
	data->m_last_move = 0;
	data->m_unknown_move = 0;

	record->m_resolver_mode = "LBY";
	// copy the last record that this player was walking
	// we need it later on because it gives us crucial data.
	std::memcpy(&data->m_walk_record, record, sizeof(LagRecord));
}

float Resolver::GetLBYRotatedYaw(float lby, float yaw)
{
	float delta = math::NormalizedAngle(yaw - lby);
	if (fabs(delta) < 25.f)
		return lby;

	if (delta > 0.f)
		return yaw + 25.f;

	return yaw;
}

bool Resolver::IsYawSideways(Player* entity, float yaw)
{
	auto local_player = g_cl.m_local;
	if (!local_player)
		return false;

	const auto at_target_yaw = math::CalcAngle(local_player->m_vecOrigin(), entity->m_vecOrigin()).y;
	const float delta = fabs(math::NormalizedAngle(at_target_yaw - yaw));

	return delta > 20.f && delta < 160.f;
}

void Resolver::ResolveYawBruteforce(LagRecord* record, Player* player, AimPlayer* data)
{
	auto local_player = g_cl.m_local;
	if (!local_player)
		return;

	record->m_mode = Modes::RESOLVE_STAND;

	const float at_target_yaw = math::CalcAngle(player->m_vecOrigin(), local_player->m_vecOrigin()).y;

	switch (data->m_stand_index % 8)
	{
	case 0:
		record->m_eye_angles.y = record->m_body;
		break;
	case 1:
		record->m_eye_angles.y = -145.f;
		break;
	case 2:
		record->m_eye_angles.y = -75.f;
		break;
	case 3:
		record->m_eye_angles.y = 50.f;
		break;
	case 4:
		record->m_eye_angles.y = -165.f;
		break;
	case 5:
		record->m_eye_angles.y = 165.f;
		break;
	case 6:
		record->m_eye_angles.y = -90.f;
		break;
	case 7:
		record->m_eye_angles.y = -50.f;
		break;
	}
}

float Resolver::GetDirectionAngle(int index, Player* player) {
	const auto left_thickness = g_cl.m_left_thickness[index];
	const auto right_thickness = g_cl.m_right_thickness[index];
	const auto at_target_angle = g_cl.m_at_target_angle[index];

	auto angle = 0.f;

	if ((left_thickness >= 350 && right_thickness >= 350) || (left_thickness <= 50 && right_thickness <= 50) || (std::fabs(left_thickness - right_thickness) <= 7)) {
		angle = math::normalize_float(at_target_angle + 180.f);
	}
	else {
		if (left_thickness > right_thickness) {
			angle = math::normalize_float(at_target_angle - 90.f);
		}
		else if (left_thickness == right_thickness) {
			angle = math::normalize_float(at_target_angle + 180.f);
		}
		else {
			angle = math::normalize_float(at_target_angle + 90.f);
		}
	}
	return angle;
}

void Resolver::LastMoveLby(LagRecord* record, AimPlayer* data, Player* player)
{
	// for no-spread call a seperate resolver.
	if (g_menu.main.config.mode.get() == 1) {
		StandNS(data, record);
		return;
	}

	// pointer for easy access.
	LagRecord* move = &data->m_walk_record;

	// get predicted away angle for the player.
	float away = GetAwayAngle(record);

	C_AnimationLayer* curr = &record->m_layers[3];
	int act = data->m_player->GetSequenceActivity(curr->m_sequence);

	float diff = math::NormalizedAngle(record->m_body - move->m_body);
	float delta = record->m_anim_time - move->m_anim_time;

	ang_t vAngle = ang_t(0, 0, 0);
	math::CalcAngle3(player->m_vecOrigin(), g_cl.m_local->m_vecOrigin(), vAngle);

	float flToMe = vAngle.y;

	const float at_target_yaw = math::CalcAngle(g_cl.m_local->m_vecOrigin(), player->m_vecOrigin()).y;

	g_visuals.fakeangels = true;

	/*for (int i = 1; i <= 32; i++)
	{
		Player* pEnemy = g_csgo.m_entlist->GetClientEntity< Player* >(i);
		const auto freestanding_record = player_resolve_records[i].m_sAntiEdge;

		AntiFreestand(player, record->m_eye_angles.y, freestanding_record.left_damage, freestanding_record.right_damage, freestanding_record.right_fraction, freestanding_record.left_fraction, flToMe, data->m_last_move);
	}*/

	//const auto freestanding_record = player_resolve_records[player->index()].m_sAntiEdge;

	// we have a valid moving record.
	if (move->m_sim_time > 0.f) {
		vec3_t delta = move->m_origin - record->m_origin;

		// check if moving record is close.
		if (delta.length() <= 128.f) {
			// indicate that we are using the moving lby.
			data->m_moved = true;
		}
	}

	if (!data->m_moved) {

		record->m_mode = Modes::RESOLVE_UNKNOWM;

		ResolveYawBruteforce(record, player, data);

		if (data->m_body != data->m_old_body)
		{
			record->m_eye_angles.y = record->m_body;

			data->m_body_update = record->m_anim_time + 1.125f;

			g_visuals.fakeangels = false;
			record->m_mode = Modes::RESOLVE_BODY;
		}
	}
	else if (data->m_moved) {
	

		record->m_mode = Modes::RESOLVE_LASTMOVE;
		float diff = math::NormalizedAngle(record->m_body - move->m_body);
		float delta = record->m_anim_time - move->m_anim_time;
		const float at_target_yaw = math::CalcAngle(g_cl.m_local->m_vecOrigin(), player->m_vecOrigin()).y;

		if (IsYawSideways(player, move->m_body)) // anti-urine
			record->m_eye_angles.y = move->m_body;
		else
			record->m_eye_angles.y = away + 180.f;

		if (data->m_last_move >= 1)
			ResolveYawBruteforce(record, player, data);

		//record->m_eye_angles.y = GetDirectionAngle(player->index(), player);

		if (data->m_body != data->m_old_body)
		{
			auto lby = math::normalize_float(record->m_body);
			if (fabsf(record->m_eye_angles.y - lby) <= 150.f && fabsf(record->m_eye_angles.y - lby) >= 35.f) {
				record->m_eye_angles.y ? lby -= 25.f : lby += 25.f;
			}
			record->m_eye_angles.y = lby;
			player->SetAbsAngles(ang_t(0.f, lby, 0.f));

			data->m_body_update = record->m_anim_time + 1.125f;
			g_visuals.fakeangels = false;
			record->m_mode = Modes::RESOLVE_BODY;
		}
		else
		{
			// LBY SHOULD HAVE UPDATED HERE.
			if (record->m_anim_time >= data->m_body_update) {
				// only shoot the LBY flick 3 times.
				// if we happen to miss then we most likely mispredicted
				if (data->m_body_index < 1) {
					// set angles to current LBY.
					record->m_eye_angles.y = record->m_body;

					data->m_body_update = record->m_anim_time + 1.125f;

					// set the resolve mode.
					g_visuals.fakeangels = false;
					record->m_mode = Modes::RESOLVE_BODY;
				}
			}
		}
		//if (data->m_last_move > 1)
			//AntiFreestand(player, record->m_eye_angles.y, freestanding_record.left_damage, freestanding_record.right_damage, freestanding_record.right_fraction, freestanding_record.left_fraction, flToMe, data->m_last_move);
	}
}

void Resolver::ResolveStand(AimPlayer* data, LagRecord* record, Player* player) {
	// for no-spread call a seperate resolver.
	if (g_menu.main.config.mode.get() == 1) {
		StandNS(data, record);
		return;
	}

	// get predicted away angle for the player.
	float away = GetAwayAngle(record);

	// pointer for easy access.
	LagRecord* move = &data->m_walk_record;
	float delta = record->m_anim_time - move->m_anim_time;

	// we have a valid moving record.
	if (move->m_sim_time > 0.f && !move->dormant() && !record->dormant()) {
		vec3_t delta = move->m_origin - record->m_origin;

		// check if moving record is close.
		if (delta.length() <= 128.f) {
			// indicate that we are using the moving lby.
			data->m_moved = true;
		}
	}

	if (delta < .22f) // can't flick if they moved .22 seconds ago so its just their lby
	{
		record->m_eye_angles.y = move->m_body;

		record->m_mode = Modes::RESOLVE_STOPPED_MOVING;
		record->m_resolver_mode = "STOPPED";
	}
	else if (data->m_body != data->m_old_body && data->m_body_index <= 5) // flick prediction, has .22 flick predict
	{
		record->m_eye_angles.y = data->m_body;

		data->m_body_update = record->m_anim_time + 1.1f;

		record->m_mode = Modes::RESOLVE_LBY_UPDATE;
		record->m_resolver_mode = "LBY UPDATE";
	}
	else if (data->m_moved && data->m_moving_index < 1) // last moving if we havn't missed it
	{
		float diff = math::NormalizedAngle(record->m_body - move->m_body);
		float delta = record->m_anim_time - move->m_anim_time;
		const float at_target_yaw = math::CalcAngle(g_cl.m_local->m_vecOrigin(), player->m_vecOrigin()).y;

		if (IsYawSideways(player, move->m_body)) // anti-urine
			record->m_eye_angles.y = move->m_body;
		else
			record->m_eye_angles.y = away + 180.f;

		if (data->m_last_move >= 1)
			ResolveYawBruteforce(record, player, data);

		//record->m_eye_angles.y = GetDirectionAngle(player->index(), player);

		if (data->m_body != data->m_old_body)
		{
			auto lby = math::normalize_float(record->m_body);
			if (fabsf(record->m_eye_angles.y - lby) <= 150.f && fabsf(record->m_eye_angles.y - lby) >= 35.f) {
				record->m_eye_angles.y ? lby -= 25.f : lby += 25.f;
			}
			record->m_eye_angles.y = lby;
			player->SetAbsAngles(ang_t(0.f, lby, 0.f));

			data->m_body_update = record->m_anim_time + 1.125f;
			g_visuals.fakeangels = false;
			record->m_mode = Modes::RESOLVE_BODY;
		}
		else
		{
			// LBY SHOULD HAVE UPDATED HERE.
			if (record->m_anim_time >= data->m_body_update) {
				// only shoot the LBY flick 3 times.
				// if we happen to miss then we most likely mispredicted
				if (data->m_body_index < 1) {
					// set angles to current LBY.
					record->m_eye_angles.y = record->m_body;

					data->m_body_update = record->m_anim_time + 1.125f;

					// set the resolve mode.
					g_visuals.fakeangels = false;
					record->m_mode = Modes::RESOLVE_BODY;
				}
			}
		}

		record->m_mode = Modes::RESOLVE_LASTMOVE;
		record->m_resolver_mode = "LAST MOVING";
	}
	else if (!data->m_moved || data->m_moving_index >= 1 && data->m_freestanding_index <= 3) // freestanding if we have gone through that shit or missed last moving
	{
		AntiFreestand(record);

		record->m_mode = Modes::RESOLVE_FREESTAND;
		record->m_resolver_mode = "FREESTANDING";
	}
	else // bruteforce as a last fallback
	{
		switch (data->m_stand_index2 % 6)
		{
		case 1:
			record->m_eye_angles.y = away + 180;
			break;

		case 2:
			record->m_eye_angles.y = away + 110;
			break;

		case 3:
			record->m_eye_angles.y = away - 110;
			break;

		case 4:
			record->m_eye_angles.y = away + data->m_body;
			break;

		case 5:
			record->m_eye_angles.y = away - data->m_body;
			break;

		case 6:
			record->m_eye_angles.y = away;
			break;
		}

		record->m_mode = Modes::RESOLVE_BRUTEFORCE;
		record->m_resolver_mode = "BRUTEFORCE";
	}
}

void Resolver::StandNS(AimPlayer* data, LagRecord* record) {
	// get away angles.
	float away = GetAwayAngle(record);

	switch (data->m_shots % 8) {
	case 0:
		record->m_eye_angles.y = away + 180.f;
		break;

	case 1:
		record->m_eye_angles.y = away + 90.f;
		break;
	case 2:
		record->m_eye_angles.y = away - 90.f;
		break;

	case 3:
		record->m_eye_angles.y = away + 45.f;
		break;
	case 4:
		record->m_eye_angles.y = away - 45.f;
		break;

	case 5:
		record->m_eye_angles.y = away + 135.f;
		break;
	case 6:
		record->m_eye_angles.y = away - 135.f;
		break;

	case 7:
		record->m_eye_angles.y = away + 0.f;
		break;

	default:
		break;
	}

	// force LBY to not fuck any pose and do a true bruteforce.
	record->m_body = record->m_eye_angles.y;
}

void Resolver::ResolveAir(AimPlayer* data, LagRecord* record, Player* player) {
	// for no-spread call a seperate resolver.
	if (g_menu.main.config.mode.get() == 1) {
		AirNS(data, record);
		return;
	}

	// else run our matchmaking air resolver.
	if (record->m_velocity.length_2d() < 60.f) {
		record->m_mode = Modes::RESOLVE_STAND;

		// invoke our stand resolver.
		ResolveStand(data, record, player);

		return;
	}

	// try to predict the direction of the player based on his velocity direction.
	// this should be a rough estimation of where he is looking.
	float velyaw = math::rad_to_deg(std::atan2(record->m_velocity.y, record->m_velocity.x));

	switch (data->m_missed_shots % 3) {
	case 0:
		record->m_eye_angles.y = velyaw + 180.f;
		break;

	case 1:
		record->m_eye_angles.y = velyaw - 90.f;
		break;

	case 2:
		record->m_eye_angles.y = velyaw + 90.f;
		break;
	}

	record->m_resolver_mode = "AIR";
}

void Resolver::AirNS(AimPlayer* data, LagRecord* record) {
	// get away angles.
	float away = GetAwayAngle(record);

	switch (data->m_shots % 10) {
	case 0:
		record->m_eye_angles.y = away + 180.f;
		break;
	case 1:
		record->m_eye_angles.y = away + 180.f;
		break;

	case 2:
		record->m_eye_angles.y = away + 150.f;
		break;
	case 3:
		record->m_eye_angles.y = away - 150.f;
		break;

	case 4:
		record->m_eye_angles.y = away + 165.f;
		break;
	case 5:
		record->m_eye_angles.y = away - 165.f;
		break;

	case 6:
		record->m_eye_angles.y = away + 135.f;
		break;
	case 7:
		record->m_eye_angles.y = away - 135.f;
		break;

	case 8:
		record->m_eye_angles.y = away + 90.f;
		break;
	case 9:
		record->m_eye_angles.y = away - 90.f;
		break;

	default:
		break;
	}
}

void Resolver::ResolvePoses(Player* player, LagRecord* record) {
	AimPlayer* data = &g_aimbot.m_players[player->index() - 1];

	// only do this bs when in air.
	if (record->m_mode == Modes::RESOLVE_AIR) {
		// ang = pose min + pose val x ( pose range )

		// lean_yaw
		player->m_flPoseParameter()[2] = g_csgo.RandomInt(0, 4) * 0.25f;

		// body_yaw
		player->m_flPoseParameter()[11] = g_csgo.RandomInt(1, 3) * 0.25f;
	}
}

void Resolver::ResolveOverride(Player* player, LagRecord* record, AimPlayer* data) {

	g_visuals.fakeangels = true;

	// get predicted away angle for the player.
	float away = GetAwayAngle(record);

	// pointer for easy access.
	LagRecord* move = &data->m_walk_record;

	C_AnimationLayer* curr = &record->m_layers[3];
	int act = data->m_player->GetSequenceActivity(curr->m_sequence);

	if (g_input.GetKeyState(g_menu.main.aimbot.override.get())) {
		ang_t                          viewangles;
		g_csgo.m_engine->GetViewAngles(viewangles);

		//auto yaw = math::clamp (g_cl.m_local->GetAbsOrigin(), Player->origin()).y;
		const float at_target_yaw = math::CalcAngle(g_cl.m_local->m_vecOrigin(), player->m_vecOrigin()).y;

		if (fabs(math::NormalizedAngle(viewangles.y - at_target_yaw)) > 30.f)
			return ResolveStand(data, record, player);

		record->m_eye_angles.y = (math::NormalizedAngle(viewangles.y - at_target_yaw) > 0) ? at_target_yaw + 90.f : at_target_yaw - 90.f;

		if (math::NormalizedAngle(viewangles.y - at_target_yaw) > 0.5)
			at_target_yaw + 90.f;

		else if (math::NormalizedAngle(viewangles.y - at_target_yaw) < 0.5)
			at_target_yaw + 90.f;

		else
			at_target_yaw + 180.f;

		//return UTILS::GetLBYRotatedYaw(entity->m_flLowerBodyYawTarget(), (math::NormalizedAngle(viewangles.y - at_target_yaw) > 0) ? at_target_yaw + 90.f : at_target_yaw - 90.f);

		record->m_mode = Modes::RESOLVE_OVERRIDE;
		record->m_resolver_mode = "OVERRIDE";
	}

	bool did_lby_flick{ false };

	if (data->m_body != data->m_old_body)
	{
		record->m_eye_angles.y = record->m_body;

		data->m_body_update = record->m_anim_time + 1.125f;

		g_visuals.fakeangels = false;
		record->m_mode = Modes::RESOLVE_BODY;
	}
	else
	{
		// LBY SHOULD HAVE UPDATED HERE.
		if (record->m_anim_time >= data->m_body_update) {
			// only shoot the LBY flick 3 times.
			// if we happen to miss then we most likely mispredicted
			if (data->m_body_index < 1) {
				// set angles to current LBY.
				record->m_eye_angles.y = record->m_body;

				data->m_body_update = record->m_anim_time + 1.125f;

				// set the resolve mode.
				g_visuals.fakeangels = false;
				record->m_mode = Modes::RESOLVE_BODY;
			}
		}
	}

	// we have a valid moving record.
	if (move->m_sim_time > 0.f) {
		vec3_t delta = move->m_origin - record->m_origin;

		// check if moving record is close.
		if (delta.length() <= 128.f) {
			// indicate that we are using the moving lby.
			data->m_moved = true;
		}
	}

	// a valid moving context was found
	if (data->m_moved) {
		float diff = math::NormalizedAngle(record->m_body - move->m_body);
		float delta = record->m_anim_time - move->m_anim_time;

		// it has not been time for this first update yet.
		if (delta < 0.22f) {
			// set angles to current LBY.
			record->m_eye_angles.y = move->m_body;

			// set resolve mode.
			record->m_mode = Modes::RESOLVE_STOPPED_MOVING;

			// exit out of the resolver, thats it.
			return;
		}

		// LBY SHOULD HAVE UPDATED HERE.
		else if (record->m_anim_time >= data->m_body_update) {
			// only shoot the LBY flick 3 times.
			// if we happen to miss then we most likely mispredicted.
			if (data->m_body_index < 1) {
				// set angles to current LBY.
				record->m_eye_angles.y = data->m_body;

				// predict next body update.
				data->m_body_update = record->m_anim_time + 1.1f;

				// set the resolve mode.
				record->m_mode = Modes::RESOLVE_BODY;

				return;
			}
		}
	}
}

void Resolver::AntiFreestand(LagRecord* record) {
	// constants
	constexpr float STEP{ 4.f };
	constexpr float RANGE{ 32.f };

	// best target.
	vec3_t enemypos = record->m_player->GetShootPosition();
	float away = GetAwayAngle(record);

	// construct vector of angles to test.
	std::vector< AdaptiveAngle > angles{ };
	angles.emplace_back(away - 180.f);
	angles.emplace_back(away + 90.f);
	angles.emplace_back(away - 90.f);

	// start the trace at the your shoot pos.
	vec3_t start = g_cl.m_local->GetShootPosition();

	// see if we got any valid result.
	// if this is false the path was not obstructed with anything.
	bool valid{ false };

	// iterate vector of angles.
	for (auto it = angles.begin(); it != angles.end(); ++it) {

		// compute the 'rough' estimation of where our head will be.
		vec3_t end{ enemypos.x + std::cos(math::deg_to_rad(it->m_yaw)) * RANGE,
			enemypos.y + std::sin(math::deg_to_rad(it->m_yaw)) * RANGE,
			enemypos.z };

		// draw a line for debugging purposes.
		// g_csgo.m_debug_overlay->AddLineOverlay( start, end, 255, 0, 0, true, 0.1f );

		// compute the direction.
		vec3_t dir = end - start;
		float len = dir.normalize();

		// should never happen.
		if (len <= 0.f)
			continue;

		// step thru the total distance, 4 units per step.
		for (float i{ 0.f }; i < len; i += STEP) {
			// get the current step position.
			vec3_t point = start + (dir * i);

			// get the contents at this point.
			int contents = g_csgo.m_engine_trace->GetPointContents(point, MASK_SHOT_HULL);

			// contains nothing that can stop a bullet.
			if (!(contents & MASK_SHOT_HULL))
				continue;

			float mult = 1.f;

			// over 50% of the total length, prioritize this shit.
			if (i > (len * 0.5f))
				mult = 1.25f;

			// over 90% of the total length, prioritize this shit.
			if (i > (len * 0.75f))
				mult = 1.25f;

			// over 90% of the total length, prioritize this shit.
			if (i > (len * 0.9f))
				mult = 2.f;

			// append 'penetrated distance'.
			it->m_dist += (STEP * mult);

			// mark that we found anything.
			valid = true;
		}
	}

	if (!valid) {
		return;
	}

	// put the most distance at the front of the container.
	std::sort(angles.begin(), angles.end(),
		[](const AdaptiveAngle& a, const AdaptiveAngle& b) {
			return a.m_dist > b.m_dist;
		});

	// the best angle should be at the front now.
	AdaptiveAngle* best = &angles.front();

	record->m_eye_angles.y = best->m_yaw;
}

bool Resolver::IdealFreestand(Player* entity, float& yaw, int damage_tolerance)    /// perfect resolving if is not urine
{
	if (!(entity->m_fFlags() & FL_ONGROUND))
		return false;

	auto local_player = g_csgo.m_entlist->GetClientEntity< Player* >(g_csgo.m_engine->GetLocalPlayer());
	if (!local_player || local_player->alive() != 0)
		return false;

	std::vector<Player*> enemies;

	const float height = 64;

	float leftdamage = 0.f, rightdamage = 0.f, backdamage = 0.f;

	std::vector<vec3_t> last_eye_positions;

	last_eye_positions.insert(last_eye_positions.begin(), local_player->m_vecOrigin() + local_player->m_vecViewOffset());
	if (last_eye_positions.size() > 128)
		last_eye_positions.pop_back();

	auto nci = g_csgo.m_engine->GetNetChannelInfo();
	if (!nci)
		return false;

	const int latency_ticks = game::TIME_TO_TICKS(nci->GetLatency(INetChannel::FLOW_OUTGOING));
	const auto latency_based_eye_pos = last_eye_positions.size() <= latency_ticks ? last_eye_positions.back() : last_eye_positions[latency_ticks];

	vec3_t direction_1, direction_2, direction_3;
	math::AngleVectors(ang_t(0.f, math::CalcAngle(local_player->m_vecOrigin(), entity->m_vecOrigin()).y - 90.f, 0.f), &direction_1);
	math::AngleVectors(ang_t(0.f, math::CalcAngle(local_player->m_vecOrigin(), entity->m_vecOrigin()).y + 90.f, 0.f), &direction_2);
	math::AngleVectors(ang_t(0.f, math::CalcAngle(local_player->m_vecOrigin(), entity->m_vecOrigin()).y + 180.f, 0.f), &direction_3);

	const auto left_eye_pos = entity->m_vecOrigin() + vec3_t(0, 0, height) + (direction_1 * 16.f);
	const auto right_eye_pos = entity->m_vecOrigin() + vec3_t(0, 0, height) + (direction_2 * 16.f);
	const auto back_eye_pos = entity->m_vecOrigin() + vec3_t(0, 0, height) + (direction_3 * 16.f);


	//resolve_record.anti_freestanding_record.right_damage = FEATURES::RAGEBOT::autowall.CalculateDamage(latency_based_eye_pos,
	//right_eye_pos, local_player, entity, 1).damage;


	penetration::scale(entity, leftdamage, 1.f, HITGROUP_CHEST);
	penetration::scale(entity, rightdamage, 1.f, HITGROUP_CHEST);
	penetration::scale(entity, backdamage, 1.f, HITGROUP_CHEST);
	//damage = penetration::scale(player, damage, 1.f, HITGROUP_CHEST);

	//leftdamage = autowall->CalculateDamage(latency_based_eye_pos,
	//	left_eye_pos, local_player, entity).damage;
		//	rightdamage = autowall->CalculateDamage(latency_based_eye_pos,
	//		right_eye_pos, local_player, entity).damage;
			//	backdamage = autowall->CalculateDamage(latency_based_eye_pos,
		//	back_eye_pos, local_player, entity).damage;

	int right_damage = rightdamage;
	int left_damage = leftdamage;
	int back_damage = backdamage;

	float at_target_yaw = math::CalcAngle(entity->m_vecOrigin(), local_player->m_vecOrigin()).y;
	const float right_yaw = at_target_yaw - 90.f;
	const float left_yaw = at_target_yaw + 90.f;
	auto head_position = entity->m_vecOrigin() + vec3_t(0, 0, 74.f);

	float calculated_yaw;

	/// Find the lowest fov enemy
	Entity* closest_enemy = nullptr;
	float lowest_fov = 360.f;
	for (int i = 0; i <= 64; i++)
	{
		Player* ent = g_csgo.m_entlist->GetClientEntity< Player* >(i);
		if (!ent || ent->dormant() || ent->m_iTeamNum() == entity->m_iTeamNum() || ent->m_iHealth() <= 0 || !ent->alive())
			continue;

		const float current_fov = fabs(math::NormalizedAngle(math::CalcAngle(entity->m_vecOrigin(), ent->m_vecOrigin()).y - at_target_yaw));
		if (current_fov < lowest_fov)
		{
			lowest_fov = current_fov;
			closest_enemy = ent;
		}

		enemies.push_back(ent);
	}

	if (closest_enemy == nullptr)
		return false;

	auto RotateAndExtendPosition = [](vec3_t position, float yaw, float distance) -> vec3_t
	{
		vec3_t direction;
		math::AngleVectors(ang_t(0, yaw, 0), &direction);

		return position + (direction * distance);
	};

	auto right_head_position = RotateAndExtendPosition(head_position, right_yaw, 17.f);
	auto left_head_position = RotateAndExtendPosition(head_position, left_yaw, 17.f);

	auto CalcDamage = [entity, enemies](vec3_t point) -> int
	{
		int damage = 0;
		for (auto& enemy : enemies)
		{
			damage += (penetration::scale(enemy, damage, 1.0f, HITGROUP_CHEST),
				penetration::scale(enemy, damage, 1.0f, HITGROUP_CHEST));
		}

		return damage;
	};

	auto RotateLBYAndYaw = [right_yaw, left_yaw, entity](int right_damage, int left_damage, float& yaw, bool prefect_angle = false) -> bool
	{
		bool prefer_right = right_damage < left_damage;

		yaw = prefer_right ? right_yaw : left_yaw;

		/// If not moving
		if (prefect_angle)
			yaw = g_resolver.GetLBYRotatedYaw(entity->m_flLowerBodyYawTarget(), yaw);

		return true;
	};

	if (left_damage >= damage_tolerance && right_damage >= damage_tolerance && back_damage >= damage_tolerance)
		return false;

	if (left_damage >= damage_tolerance && right_damage >= damage_tolerance && back_damage < damage_tolerance)
		calculated_yaw = at_target_yaw + 180.f;
	else if (right_damage == left_damage)
	{
		if (math::NormalizedAngle(math::CalcAngle(entity->m_vecOrigin(), local_player->m_vecOrigin()).x) > 15.f && back_damage < damage_tolerance)
			calculated_yaw = at_target_yaw + 180.f;
		else
		{
			right_head_position = RotateAndExtendPosition(head_position, right_yaw, 50.f);
			left_head_position = RotateAndExtendPosition(head_position, left_yaw, 50.f);

			right_damage = CalcDamage(right_head_position), left_damage = CalcDamage(left_head_position);

			if (right_damage == left_damage)
			{
				/// just return the side closest to a wall
				//right_head_position = UTILS::TraceToEnd(head_position, RotateAndExtendPosition(head_position, right_yaw, 17.f));
				//left_head_position = UTILS::TraceToEnd(head_position, RotateAndExtendPosition(head_position, left_yaw, 17.f));

				const auto left_head_position = entity->m_vecOrigin() + vec3_t(0, 0, height) + (direction_1 * 16.f);
				const auto right_head_position = entity->m_vecOrigin() + vec3_t(0, 0, height) + (direction_2 * 16.f);

				float distance_1, distance_2;
				CGameTrace trace;
				Ray ray;
				CTraceFilterWorldOnly filter;

				auto end_pos = local_player->m_vecOrigin() + vec3_t(0, 0, 64.f);

				/// right position
				Ray first_ray(right_head_position, end_pos);
				//ray.Init(right_head_position, end_pos);
				g_csgo.m_engine_trace->TraceRay(first_ray, MASK_ALL, &filter, &trace);
				distance_1 = (right_head_position - trace.m_endpos).length_2d();

				/// left position
				Ray second_ray(left_head_position, end_pos);
				//ray.Init(left_head_position, end_pos);
				g_csgo.m_engine_trace->TraceRay(second_ray, MASK_ALL, &filter, &trace);
				distance_2 = (left_head_position - trace.m_endpos).length_2d();

				if (fabs(distance_1 - distance_2) > 15.f)
					RotateLBYAndYaw(distance_1, distance_2, calculated_yaw);
				else
					calculated_yaw = at_target_yaw + 180;
			}
			else
				RotateLBYAndYaw(right_damage, left_damage, calculated_yaw);
		}
	}
	else
	{
		if (math::NormalizedAngle(math::CalcAngle(entity->m_vecOrigin(), local_player->m_vecOrigin()).x) > 15.f && back_damage < damage_tolerance)
			calculated_yaw = at_target_yaw + 180.f;
		else
		{
			bool prefer_right = (right_damage < left_damage);
			calculated_yaw = prefer_right ? right_yaw : left_yaw;
		}
	}

	yaw = calculated_yaw;
	return true;
}

void Resolver::resolve(Player* entity, LagRecord* record)
{
	auto local_player = g_csgo.m_entlist->GetClientEntity< Player* >(g_csgo.m_engine->GetLocalPlayer());

	//shots_missed[entity->index()] = shots_fired[entity->index()] - shots_hit[entity->index()];

	int i = entity->index();

	static float oldlby[65], predict[65], lastmovelby[65], laststandlby[65];

	// pitch fix
	record->m_eye_angles.x = math::NormalizedAngle(record->m_eye_angles.x);

	if (entity->m_vecVelocity().length_2d() > 15 && !record->m_fake_walk && entity->m_fFlags() & FL_ONGROUND)
	{
		record->m_eye_angles.y = entity->m_flLowerBodyYawTarget();
		lastmovelby[i] = entity->m_flLowerBodyYawTarget();
		predict[i] = entity->m_flSimulationTime() + 0.22;
		//SETTINGS::settings.resolvermode = "Moving LBY";
	}
	else
	{
		laststandlby[i] = entity->m_flLowerBodyYawTarget();

		for (int j = 0; j < 15; j++)
		{
			const int activity = entity->GetSequenceActivity(entity->m_AnimOverlay()[j].m_sequence);

			if (activity == 979 && entity->m_AnimOverlay()[3].m_weight == 0)
			{
				record->m_eye_angles.y = entity->m_flLowerBodyYawTarget();
				predict[i] = entity->m_flSimulationTime() + g_csgo.m_globals->m_interval + 1.1;
				//SETTINGS::settings.resolvermode = "LBY Backtrack";
			}
			else if (activity == 973)
			{
				record->m_eye_angles.y = entity->m_flLowerBodyYawTarget();
				predict[i] = entity->m_flSimulationTime() + g_csgo.m_globals->m_interval + 1.1;
				//SETTINGS::settings.resolvermode = "LBY Change";
			}
			else if (entity->m_flSimulationTime() >= predict[i])
			{
				record->m_eye_angles.y = entity->m_flLowerBodyYawTarget();
				predict[i] = entity->m_flSimulationTime() + g_csgo.m_globals->m_interval + 1.1;
				//SETTINGS::settings.resolvermode = "LBY Prediction";
			}
			else if (activity == 980 && entity->m_AnimOverlay()[3].m_weight == 0)
			{
				record->m_eye_angles.y = entity->m_flLowerBodyYawTarget();
				//SETTINGS::settings.resolvermode = "LBY 980";
			}
			else if (activity == 980 && entity->m_AnimOverlay()[3].m_weight == 1)
			{
				record->m_eye_angles.y = laststandlby[i];
				//SETTINGS::settings.resolvermode = "LastStand LBY";
			}
			else
			{
				record->m_eye_angles.y = lastmovelby[i];
				//SETTINGS::settings.resolvermode = "LastMove LBY";
			}
		}
	}
}

bool Resolver::lby_updated(LagRecord* a, AimPlayer* b, Player* entity) {

	if (b->m_body != b->m_old_body) return true;

	if ((entity->m_flSimulationTime() + 1.1f + g_csgo.m_globals->m_interval) < entity->m_flSimulationTime()) return true;

	bool set = true;

	C_AnimationLayer _previous;

	for (int i = 0; i < 13; i++)
	{
		C_AnimationLayer layer = entity->m_AnimOverlay()[i];
		if (set) {
			_previous = layer;
			set = false;
		}
		const int activity = entity->GetSequenceActivity(layer.m_sequence);
		const int previous_act = entity->GetSequenceActivity(_previous.m_sequence);

		if (activity == 979 && previous_act == 979) {
			if ((_previous.m_cycle != layer.m_cycle) || layer.m_weight == 1.f)
			{
				float
					flAnimTime = layer.m_cycle,
					flSimTime = entity->m_flSimulationTime();

				if (flAnimTime < 0.01f && _previous.m_cycle > 0.01f)
				{
					return true;
				}
			}
		}
		_previous = layer;
	}

	return false;
}

void Resolver::lby_update_checks(Player* entity, LagRecord* a, AimPlayer* b) {

	// pointer for easy access.
	LagRecord* move = &b->m_walk_record;
	float ave_moving_lby = move->m_body;

	float _delta_a = abs(a->m_eye_angles.y - ave_moving_lby);
	float _delta_b = abs(a->m_body - ave_moving_lby);
	float _delta_c = abs(b->m_body - ave_moving_lby);

	if (_delta_a <= _delta_b && _delta_a <= _delta_c && _delta_a <= 20) {
		return;
	}

	if (b->m_body, ave_moving_lby, 20) (a->m_body, ave_moving_lby, 20); {
		float ave = b->m_body + a->m_body;

		if (ave != 0) ave /= 2;
		a->m_eye_angles.y = ave;
		return;
	}

	if (_delta_b < _delta_c && _delta_b <= 20) {
		a->m_eye_angles.y = b->m_body;
		return;
	}

	if (_delta_c < _delta_b && _delta_c <= 20) {
		a->m_eye_angles.y = a->m_body;
		return;
	}

	a->m_eye_angles.y = entity->GetAbsAngles().y;
}

bool Resolver::can_backtrack(Player* entity) {
	float lby_update_time = entity->m_flSimulationTime();
	float current_time = g_csgo.m_globals->m_curtime;

	return ((current_time - lby_update_time) <= 0.2f);
}