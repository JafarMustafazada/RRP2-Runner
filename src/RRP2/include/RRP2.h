#pragma once
#include "RRP2std.h"
#include <string>
#include <vector>

class RRP2
{
public:
	struct RRP2config {
		int player_max = 2;
		int data[RRP2std::cdatal] = {
			5,	//card_max,
			6,	//drum_max,
			1,	//start_bullets,
			1,	//shot_damage,
			1,	//shot_cost,
			1,	//coins_pershot,
			1,	//start_hp,
			1,	//temphp_percard,
			1,	//temphp_dur,
			1,	//handshake_dur,
			1,	//bounded_dur,
		};
		int card_freq[RRP2std::cardsl] = {
			0,	//count,
			1,	//spin,
			1,	//skip,
			1,	//curse_hands,
			1,	//add_2bullets,
			1,	//temp_hp,
			1,	//block_next,
			1,	//reverse,
			1,	//coins5050,
			1,	//bond_players,
			1,	//add_turn,	
		};
	};

protected:
	struct RRP2player {
		bool isalive = true;
		int data[RRP2std::pdatal] = { 0 };
		int status[RRP2std::statusl] = { 0 };
		int cards[RRP2std::cardsl] = { 0 };
	};

	RRP2config config;
	int data[RRP2std::datal] = { 0 };
	std::vector<RRP2player> players;

	void add_bullet(bool one_only = false);
	void reset_drum();
	void deal_damage(int p_index, int damage, bool ignore_bound = false);
	void add_hp(RRP2player& player, int hp);
	bool make_shot(int victim_index, int p_index);

	void before_pturn(int p_index);
	void after_pturn(int p_index);
	int next_player();

	static void renew_cards(const RRP2config& config, RRP2player& player);
	void dekrement_card(RRP2player& player, int card);
	void run_card(RRP2player& player, int card, bool& action_made);

	void main_interface(int input, bool& action_made);
	bool victim_interface(int& input);
	RRP2() = default;

public:
	int gameio(int input = 0);

	void start_new_game(RRP2config& config);
	void start_new_game();

	std::string save_game();
	bool load_game(const std::string& data);

	RRP2(RRP2config& config);
	RRP2(const std::string& data);

	// for better interface
	int isgame_over();
	int is_data_different(const RRP2& object2) const;


	int get_pmax() const;
	std::string get_config_string() const;
	int get_pturn() const;
	int get_dturn() const;
	int get_events() const;
	int get_cinterface() const;

	std::string get_player_string(int p_index);
	//std::vector<int> get_pdata(int p_index) const;
	//std::vector<int> get_pstatus(int p_index) const;
	//std::vector<int> get_pcards(int p_index) const;
};
