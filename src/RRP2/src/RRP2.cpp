#include "RRP2.h"
#include "RRP2std.h"
#include "JDevTools.h"
#include <string>
#include <vector>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RRP2::isgame_over() {
	if (this->data[RRP2std::players_alive] > 1) return 0;
	else {
		return this->gameio(-1);
	}
}
int RRP2::is_data_different(const RRP2& object2) const {
	int index = 0;
	for (int i = 0; i < RRP2std::cdatal; i++, index++)
	{
		if (this->config.data[i] != object2.config.data[i]) return index;
	}
	for (int i = 0; i < RRP2std::cardsl; i++, index++)
	{
		if (this->config.card_freq[i] != object2.config.card_freq[i]) return index;
	}
	for (int i = 0; i < RRP2std::datal; i++, index++)
	{
		if (this->data[i] != object2.data[i]) return index;
	}

	for (int i = 0; i < this->config.player_max; i++)
	{
		for (int j = 0; j < RRP2std::pdatal; j++)
		{
			if (this->players[i].data[j] != object2.players[i].data[j]) return index;
		}
		for (int j = 0; j < RRP2std::statusl; j++)
		{
			if (this->players[i].status[j] != object2.players[i].status[j]) return index;
		}
		for (int j = 0; j < RRP2std::cardsl; j++)
		{
			if (this->players[i].cards[j] != object2.players[i].cards[j]) return index;
		}
	}

	return -1;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RRP2::get_pmax() const {
	return this->config.player_max;
}
std::string RRP2::get_config_string() const {
	std::string result = std::to_string(this->config.player_max);

	for (int i = 0; i < RRP2std::cdatal; i++)
	{
		result += RRP2std::delimetr + std::to_string(this->config.data[i]);
	}

	return result;
}
int RRP2::get_pturn() const {
	return this->data[RRP2std::datai::player_turn];
}
int RRP2::get_dturn() const {
	return this->data[RRP2std::datai::drum_turn];
}
int RRP2::get_events() const {
	return this->data[RRP2std::datai::events];
}
int RRP2::get_cinterface() const {
	return this->data[RRP2std::datai::current_interface];
}
std::string RRP2::get_player_string(int p_index) {
	RRP2player& player = this->players[p_index];
	std::string data = player.isalive ? "1" : "0";
	
	for (int j = 0; j < RRP2std::pdatal; j++)
	{
		data += RRP2std::delimetr + std::to_string(player.data[j]);
	}
	for (int j = 0; j < RRP2std::statusl; j++)
	{
		data += RRP2std::delimetr + std::to_string(player.status[j]);
	}
	for (int j = 0; j < RRP2std::cardsl; j++)
	{
		data += RRP2std::delimetr + std::to_string(player.cards[j]);
	}

	return data;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string RRP2::save_game() {
	std::string data = "" + std::to_string(this->config.player_max);

	for (int i = 0; i < RRP2std::cdatal; i++)
	{
		data += RRP2std::delimetr + std::to_string(this->config.data[i]);
	}
	for (int i = 0; i < RRP2std::cardsl; i++)
	{
		data += RRP2std::delimetr + std::to_string(this->config.card_freq[i]);
	}
	for (int i = 0; i < RRP2std::datal; i++)
	{
		data += RRP2std::delimetr + std::to_string(this->data[i]);
	}
	for (int i = 0; i < this->config.player_max; i++)
	{
		data += RRP2std::delimetr + this->get_player_string(i);
	}

	return data;
}
bool RRP2::load_game(const std::string& data) {
	RRP2 result;

	try
	{
		std::vector<std::string> digits = JDevTools::split(data.data(), RRP2std::delimetr);
		result.config.player_max = std::stoi(digits[0]);
		int index = 1;

		for (int i = 0; i < RRP2std::cdatal; i++, index++)
		{
			result.config.data[i] = std::stoi(digits[index]);
		}
		for (int i = 0; i < RRP2std::cardsl; i++, index++)
		{
			result.config.card_freq[i] = std::stoi(digits[index]);
		}
		for (int i = 0; i < RRP2std::datal; i++, index++)
		{
			result.data[i] = std::stoi(digits[index]);
		}

		result.players.resize(result.config.player_max);
		for (int i = 0; i < result.config.player_max; i++)
		{
			result.players[i].isalive = (digits[index] == "0" ? false : true);
			index++;

			for (int j = 0; j < RRP2std::pdatal; j++, index++)
			{
				result.players[i].data[j] = std::stoi(digits[index]);
			}
			for (int j = 0; j < RRP2std::statusl; j++, index++)
			{
				result.players[i].status[j] = std::stoi(digits[index]);
			}
			for (int j = 0; j < RRP2std::cardsl; j++, index++)
			{
				result.players[i].cards[j] = std::stoi(digits[index]);
			}
		}

		*this = result;
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RRP2::renew_cards(const RRP2config& config, RRP2player& player) {
	player.cards[0] += config.data[RRP2std::cdatai::card_max];
	for (int i = 0; i < config.data[RRP2std::cdatai::card_max]; i++)
	{
		player.cards[JDevTools::randi(RRP2std::cardsl, config.card_freq)]++;
	}
}
void RRP2::dekrement_card(RRP2player& player, int card) {
	player.cards[card]--;
	player.cards[0]--;
	if (player.cards[0] == 0) this->renew_cards(this->config, player);
}
void RRP2::run_card(RRP2player& player, int card, bool& action_made) {
	switch (card)
	{
	case RRP2std::cardsi::spin:
		this->data[RRP2std::datai::drum_turn] = JDevTools::rando(this->config.data[RRP2std::cdatai::drum_max]) - 1;
		this->data[RRP2std::datai::events] ^= (1 << RRP2std::eventi::spin_flipper);
		this->dekrement_card(player, card);
		break;
	case RRP2std::cardsi::skip:
		action_made = true;
		this->dekrement_card(player, card);
		break;
	case RRP2std::cardsi::curse_hands:
		this->data[RRP2std::datai::current_interface] = RRP2std::interi::victim_chands;
		break;
	case RRP2std::cardsi::add_2bullets:
		this->add_bullet();
		this->add_bullet();
		this->dekrement_card(player, card);
		break;
	case RRP2std::cardsi::temp_hp:
		player.status[RRP2std::statusi::temphp] += this->config.data[RRP2std::cdatai::temphp_dur];
		this->add_hp(player, this->config.data[RRP2std::cdatai::temphp_percard]);
		this->dekrement_card(player, card);
		break;
	case RRP2std::cardsi::block_next:
		this->data[RRP2std::datai::events] |= (1 << RRP2std::eventi::next_blocked);
		action_made = true;
		this->dekrement_card(player, card);
		break;
	case RRP2std::cardsi::reverse:
		this->data[RRP2std::datai::events] ^= (1 << RRP2std::eventi::is_reverse);
		action_made = true;
		this->dekrement_card(player, card);
		break;
	case RRP2std::cardsi::coins5050:
		if (JDevTools::rando(2) == 2) player.data[RRP2std::pdatai::coins] *= 2;
		else player.data[RRP2std::pdatai::coins] /= 2;
		this->dekrement_card(player, card);
		break;
	case RRP2std::cardsi::bond_players:
		this->data[RRP2std::datai::current_interface] = RRP2std::interi::victim_bplayer1;
		break;
	case RRP2std::cardsi::add_turn:
		player.status[RRP2std::statusi::bonus_turn]++;
		this->dekrement_card(player, card);
		break;
	default:
		return;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RRP2::add_hp(RRP2player& player, int hp) {
	player.data[RRP2std::pdatai::hp] += hp;
	if (player.data[RRP2std::pdatai::hp] > 0 && !player.isalive) {
		player.isalive = true;
		this->data[RRP2std::datai::players_alive]++;
	}
}
void RRP2::deal_damage(int p_index, int damage, bool ignore_bound) {
	if (ignore_bound)
	{
		this->players[p_index].data[RRP2std::pdatai::hp] -= damage;
		if (this->players[p_index].data[RRP2std::pdatai::hp] < 1) {
			this->data[RRP2std::datai::players_alive]--;
			this->players[p_index].isalive = false;
		}
	}
	else if (this->players[p_index].status[RRP2std::statusi::bounded]) {
		for (int i = 0; i < this->config.player_max; i++)
		{
			this->deal_damage(i, damage, true);
		}
	}
	else this->deal_damage(p_index, damage, true);
}
void RRP2::add_bullet(bool one_only) {
	int temp = this->data[RRP2std::datai::drum], index = 0;
	std::vector<int> empty_chambers;

	for (; temp; index++, temp >>= 1)
	{
		if (!(temp & 1)) empty_chambers.push_back(index);
	}
	for (; index < this->config.data[RRP2std::cdatai::drum_max]; index++)
	{
		empty_chambers.push_back(index);
	}

	temp = empty_chambers.size();
	const int start = this->config.data[RRP2std::cdatai::drum_max] -
		this->config.data[RRP2std::cdatai::starts_bullets];
	if ((!temp) || (one_only && temp <= start)) return;

	temp = JDevTools::rando(temp) - 1;
	this->data[RRP2std::datai::drum] |= (1 << empty_chambers[temp]);
}
void RRP2::reset_drum() {
	int temp, howmuch = this->config.data[RRP2std::cdatai::starts_bullets];
	this->data[RRP2std::datai::drum] = 0;
	this->data[RRP2std::datai::events] ^= (1 << RRP2std::eventi::reload_flipper);
	if (howmuch > this->config.data[RRP2std::cdatai::drum_max]) {
		howmuch = this->config.data[RRP2std::cdatai::drum_max];
	}

	while (howmuch)
	{
		temp = (1 << (JDevTools::rando(this->config.data[RRP2std::cdatai::drum_max]) - 1));
		if (!(this->data[RRP2std::datai::drum] & temp)) {
			howmuch--;
			this->data[RRP2std::datai::drum] |= temp;
		}
	}
}
bool RRP2::make_shot(int victim_index, int p_index) {
	bool was_shot = false;
	this->data[RRP2std::datai::events] ^= (1 << RRP2std::eventi::triger_flipper);

	if ((this->data[RRP2std::datai::drum] & (1 << this->data[RRP2std::datai::drum_turn]))) {
		was_shot = true;
		this->data[RRP2std::datai::events] ^= (1 << RRP2std::shot_flipper);

		if (p_index == victim_index ||
			(!this->players[p_index].status[RRP2std::statusi::hands_shaking])) {
			this->deal_damage(victim_index, this->config.data[RRP2std::cdatai::shot_damage]);
		}

		this->data[RRP2std::datai::drum] &= ~(1 << this->data[RRP2std::datai::drum_turn]);
		if (!this->data[RRP2std::datai::drum]) this->reset_drum();
	}

	this->data[RRP2std::datai::drum_turn]++;
	if (this->data[RRP2std::datai::drum_turn] >= this->config.data[RRP2std::cdatai::drum_max]) {
		this->data[RRP2std::datai::drum_turn] = 0;
	}

	return was_shot;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void RRP2::RRP2config::clear() {
//	RRP2config empty;
//	RRP2config& obj = *this;
//	empty.data[RRP2std::cdatai::card_max] = 5;
//	empty.data[RRP2std::cdatai::drum_max] = 6;
//	empty.data[RRP2std::cdatai::shot_damage] = 1;
//	empty.data[RRP2std::cdatai::shot_cost] = 1;
//	empty.data[RRP2std::cdatai::coins_pershot] = 1;
//	empty.data[RRP2std::cdatai::start_hp] = 1;
//	empty.data[RRP2std::cdatai::temphp_percard] = 1;
//	empty.data[RRP2std::cdatai::temphp_dur] = 1;
//	empty.data[RRP2std::cdatai::handshake_dur] = 1;
//	empty.data[RRP2std::cdatai::bounded_dur] = 1;
//	obj = empty;
//}
//void RRP2::RRP2player::clear() {
//	//int index = 0;
//	//for (; index < RRP2std::pdatal; index++)
//	//{
//	//	this->data[index] = 0;
//	//	this->status[index] = 0;
//	//	this->cards[index] = 0;
//	//}
//	//for (; index < RRP2std::statusl; index++)
//	//{
//	//	this->status[index] = 0;
//	//	this->cards[index] = 0;
//	//}
//	//for (; index < RRP2std::cardsl; index++)
//	//{
//	//	this->cards[index] = 0;
//	//}
//}
void RRP2::start_new_game(RRP2config& config) { // TODO: include every insane case of config
	if (config.player_max < 2 ||
		config.player_max > RRP2std::player_limit ||
		config.data[RRP2std::cdatai::drum_max] < 0 ||
		config.data[RRP2std::cdatai::drum_max] > RRP2std::drum_limit) {
		this->data[RRP2std::datai::players_alive] = 1;
		this->players.resize(this->config.player_max);
	}
	else {
		this->config = config;
		this->start_new_game();
	}
}
void RRP2::start_new_game() {
	this->players.resize(this->config.player_max);
	for (int i = 0; i < RRP2std::datal; i++) this->data[i] = 0;

	this->data[RRP2std::datai::players_alive] = this->config.player_max;
	this->data[RRP2std::datai::current_interface] = RRP2std::interi::main;

	for (int i = 0; i < this->config.player_max; i++)
	{
		this->players[i] = RRP2player();
		this->renew_cards(this->config, this->players[i]);
		this->players[i].data[RRP2std::pdatai::hp] =
			this->config.data[RRP2std::cdatai::start_hp];
	}

	this->reset_drum();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RRP2::RRP2(RRP2config& config) {
	this->start_new_game(config);
}
RRP2::RRP2(const std::string& data) {
	if (!this->load_game(data)) {
		RRP2config defaultone;
		defaultone.player_max = 1;
		this->start_new_game(defaultone);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RRP2::main_interface(int input, bool& action_made) {
	/*
		1. shot self
		2. shot player (-1)
		3. use card
	*/
	int pturn = this->data[RRP2std::datai::player_turn];
	switch (input)
	{
	case 1:
		this->make_shot(pturn, pturn);
		this->players[pturn].data[RRP2std::pdatai::coins] += this->config.data[RRP2std::cdatai::coins_pershot];
		action_made = true;
		return;
	case 2:
		if (this->players[pturn].data[RRP2std::pdatai::coins] >= this->config.data[RRP2std::cdatai::shot_cost]) {
			this->data[RRP2std::datai::current_interface] = RRP2std::interi::victim;
		}
		return;
	case 3:
		this->data[RRP2std::datai::current_interface] = RRP2std::interi::cards;
		return;
	default:
		return;
	}
}
bool RRP2::victim_interface(int& input) {
	if (input > this->config.player_max || input < 1) {
		this->data[RRP2std::datai::current_interface] = RRP2std::interi::main;
		return true;
	}
	input--; // players start from 1, player index from 0
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RRP2::next_player() {
	int increment = (this->data[RRP2std::datai::events] & (1 << RRP2std::eventi::is_reverse)) ? (-1) : (1),
		incsurance = this->config.player_max,
		p_turn = this->data[RRP2std::datai::player_turn],
		block = (1 << RRP2std::eventi::next_blocked);

	do
	{
		p_turn += increment;
		if (p_turn >= this->config.player_max) p_turn = 0;
		else if (p_turn < 0) p_turn = this->config.player_max;

		if (this->players[p_turn].isalive) {
			if ((this->data[RRP2std::datai::events] & block)) {
				this->data[RRP2std::datai::events] &= ~block;
				incsurance = this->config.player_max;
			}
			else incsurance = 0;
		}
		else incsurance--;
	} while (incsurance);

	return p_turn;
}
void RRP2::after_pturn(int p_index) { // debufs
	RRP2player& player = this->players[p_index];

	if (player.status[RRP2std::statusi::hands_shaking]) player.status[RRP2std::statusi::hands_shaking]--;
	if (player.status[RRP2std::statusi::bounded]) player.status[RRP2std::statusi::bounded]--;
}
void RRP2::before_pturn(int p_index) { // bufs
	RRP2player& player = this->players[p_index];

	if (player.status[RRP2std::statusi::temphp]) {
		player.status[RRP2std::statusi::temphp]--;

		if ((!player.status[RRP2std::statusi::temphp]) &&
			(player.data[RRP2std::pdatai::hp] > this->config.data[RRP2std::cdatai::start_hp])) {
			player.data[RRP2std::pdatai::hp] = this->config.data[RRP2std::cdatai::start_hp];
		}
	}
}
int RRP2::gameio(int input) {
	bool action_made = false;
	if (this->data[RRP2std::datai::players_alive] < 2) {
		return this->next_player() + 1;
	}
	else if (input < 0) return -1;

	RRP2player& player = this->players[this->data[RRP2std::datai::player_turn]];
	int old_interface = this->data[RRP2std::datai::current_interface];

	switch (this->data[RRP2std::datai::current_interface])
	{
	case RRP2std::interi::main:
		this->main_interface(input, action_made);
		break;

	case RRP2std::interi::victim:
		if (this->victim_interface(input)) break;
		this->make_shot(input, this->data[RRP2std::datai::player_turn]);
		player.data[RRP2std::pdatai::coins]--;
		action_made = true;
		break;

	case RRP2std::interi::victim_chands:
		if (this->victim_interface(input)) break;
		this->players[input].status[RRP2std::statusi::hands_shaking] +=
			this->config.data[RRP2std::cdatai::handshake_dur];
		this->dekrement_card(player, RRP2std::cardsi::curse_hands);
		break;

	case RRP2std::interi::victim_bplayer1:
		if (this->victim_interface(input)) break;
		this->data[RRP2std::datai::victim1] = input;
		this->data[RRP2std::datai::current_interface] = RRP2std::interi::victim_bplayer2;
		break;

	case RRP2std::interi::victim_bplayer2:
		if (this->victim_interface(input)) break;

		this->players[this->data[RRP2std::datai::victim1]].
			status[RRP2std::statusi::bounded] += this->config.data[RRP2std::cdatai::bounded_dur];

		this->players[input].status[RRP2std::statusi::bounded] +=
			this->config.data[RRP2std::cdatai::bounded_dur];

		this->dekrement_card(player, RRP2std::cardsi::bond_players);
		break;

	case RRP2std::interi::cards:
		if (input < 1 || input >= RRP2std::cardsl || player.cards[input] == 0) {
			this->data[RRP2std::datai::current_interface] = RRP2std::interi::main;
		}
		else this->run_card(player, input, action_made);
		break;

	default:
		return -2; // interface error
	}

	if (old_interface == this->data[RRP2std::datai::current_interface]) {
		this->data[RRP2std::datai::current_interface] = RRP2std::interi::main;
	}

	if (action_made)
	{
		if (player.status[RRP2std::statusi::bonus_turn]) {
			player.status[RRP2std::statusi::bonus_turn]--;
		}
		else {
			this->after_pturn(this->data[RRP2std::datai::player_turn]);
			this->data[RRP2std::datai::player_turn] = this->next_player();
			this->before_pturn(this->data[RRP2std::datai::player_turn]);
		}
	}

	return 0;
}
