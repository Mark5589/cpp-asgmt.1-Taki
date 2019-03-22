#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Card.h"
class Game {
private:
	//private members and functions
	int cards_num, players_num;
	Card current_card;
	Card players_card_select;
	Player current_player;
	Player* players_arr;
	int mDirection = 1;
public:
	//public members and functions
	void start();

	void msg_welcome();
	void msg_rules();
	void msg_players_num();
	void msg_cards_num();
	void set_players_name();

	//cards.
	void set_game_initial_gamecard();
	void card_dealing(Player& player); // 1


	bool find_winner();
	void set_round_player(const int&);
	void show_gameStatus_stamp(const Player&);

	int get_input_key();

	int check_card_validity(int&, const int&);

	//Card select - Cases: 
	bool valid_select(const Player&, const Card&, const Card&, const int&);
	bool invalid_select(const Player&, const Card&, const Card&, const int&);
	bool pass_select(Player&,const int&);

	//Direction of the game
	void change_direction(const Card&);
	
	//Players turn
	int get_player_turn_case(int , int&);	
	void caseHandler(const int&, int&,int&);
	//DEBUG
	void DEBUG_PRINT_PLAYERS();
};
#endif




