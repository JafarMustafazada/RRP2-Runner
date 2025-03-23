#pragma once

namespace RRP2std {
	static const int player_limit = 31;
	static const int drum_limit = 31;
	static const char delimetr = 's';


	static const int cardl = 11;
	enum cardi {
		count,
		spin,
		skip,
		curse_hands,

		add_2bullets,
		temp_hp,
		block_next,

		reverse,
		coins5050,
		bond_players,

		add_turn,
	};

	static const int datal = 7;
	enum datai {
		current_interface,

		drum,
		drum_turn,
		player_turn,

		events,
		players_alive,

		victim1,
	};

	static const int cdatal = 11;
	enum cdatai {
		card_max,
		drum_max,

		starts_bullets,
		shot_damage,
		shot_cost,
		coins_pershot,

		start_hp,
		temphp_percard,

		temphp_dur,
		handshake_dur,
		bounded_dur,
	};

	static const int eventl = 6;
	enum eventi {
		is_reverse,
		next_blocked,
		cocking_flipper,
		shot_flipper,
		reload_flipper,
		spin_flipper,
	};

	static const int interl = 7;
	enum interi {
		notready,
		main,
		victim,
		victim_chands,
		victim_bplayer1,
		victim_bplayer2,
		cards,
	};

	static const int pdatal = 2;
	enum pdatai {
		hp,
		coins,
	};

	static const int statusl = 4;
	enum statusi {
		hands_shaking,
		temphp,
		bounded,
		bonus_turn,
	};

	static const char* getEnumName(const char* type, int value = 0) {
		if (type == "cardi") {
			switch (value) {
			case RRP2std::cardi::count:				return "count";
			case RRP2std::cardi::spin:				return "spin";
			case RRP2std::cardi::skip:				return "skip";
			case RRP2std::cardi::curse_hands:		return "curse_hands";
			case RRP2std::cardi::add_2bullets:		return "add_2bullets";
			case RRP2std::cardi::temp_hp:			return "temp_hp";
			case RRP2std::cardi::block_next:		return "block_next";
			case RRP2std::cardi::reverse:			return "reverse";
			case RRP2std::cardi::coins5050:			return "coins5050";
			case RRP2std::cardi::bond_players:		return "bond_players";
			case RRP2std::cardi::add_turn:			return "add_turn";
			}
		}
		else if (type == "datai") {
			switch (value) {
			case RRP2std::datai::current_interface:	return "current_interface";
			case RRP2std::datai::drum:				return "drum";
			case RRP2std::datai::drum_turn:			return "drum_turn";
			case RRP2std::datai::player_turn:		return "player_turn";
			case RRP2std::datai::events:			return "events";
			case RRP2std::datai::players_alive:		return "players_alive";
			case RRP2std::datai::victim1:			return "victim1";
			}
		}
		else if (type == "cdatai") {
			switch (value) {
			case RRP2std::cdatai::card_max:			return "card_max";
			case RRP2std::cdatai::drum_max:			return "drum_max";
			case RRP2std::cdatai::starts_bullets:	return "starts_bullets";
			case RRP2std::cdatai::shot_damage:		return "shot_damage";
			case RRP2std::cdatai::shot_cost:		return "shot_cost";
			case RRP2std::cdatai::coins_pershot:	return "coins_pershot";
			case RRP2std::cdatai::start_hp:			return "start_hp";
			case RRP2std::cdatai::temphp_percard:	return "temphp_percard";
			case RRP2std::cdatai::temphp_dur:		return "temphp_dur";
			case RRP2std::cdatai::handshake_dur:	return "handshake_dur";
			case RRP2std::cdatai::bounded_dur:		return "bounded_dur";
			}
		}
		else if (type == "pdatai") {
			switch (value) {
			case RRP2std::pdatai::hp:				return "hp";
			case RRP2std::pdatai::coins:			return "coins";
			}
		}
		else if (type == "statusi") {
			switch (value) {
			case RRP2std::statusi::hands_shaking:	return "hands_shaking";
			case RRP2std::statusi::temphp:			return "temphp";
			case RRP2std::statusi::bounded:			return "bounded";
			case RRP2std::statusi::bonus_turn:		return "bonus_turn";
			}
		}
		return "unknown-enum";
	}
}