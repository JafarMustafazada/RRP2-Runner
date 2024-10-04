#pragma once

namespace RRP2std {
	static const int player_limit = 31;
	static const int drum_limit = 31;
	static const char delimetr = 's';

	static const int cardsl = 11;
	static const enum cardsi {
		count, // not a card, but count of them in inventory
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
	static const enum datai {
		current_interface,

		drum,
		drum_turn,
		player_turn,

		events,
		players_alive,

		victim1,
	};

	static const int cdatal = 11;
	static const enum cdatai {
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
	static const enum eventi {
		is_reverse,
		next_blocked,
		triger_flipper,
		shot_flipper,
		reload_flipper,
		spin_flipper,
	};

	static const int interl = 7;
	static const enum interi {
		notready,
		main,
		victim,
		victim_chands,
		victim_bplayer1,
		victim_bplayer2,
		cards,
	};

	static const int pdatal = 2;
	static const enum pdatai {
		hp,
		coins,
	};

	static const int statusl = 4;
	static const enum statusi {
		hands_shaking,
		temphp,
		bounded,
		bonus_turn,
	};
}