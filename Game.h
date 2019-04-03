/* Mark */

/* Gal  */
#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Card.h"

class Game {
private:
	//private members and functions
	int cards_num, players_num;

	Player current_player;
	vector <Player> players_arr;
	Game(const Game& g){}
	Game&operator=(const Game& g){};


public:
	int mDirection;
	//public members and functions
	void start();
	Game(){}


	void msg_players_num();
	void msg_cards_num();
	void set_players_name();

	//cards.
	void card_dealing(Player& player); // 1


	bool find_winner();
	void set_round_player(const int&);
	void show_gameStatus_stamp(const Player&, const Card&);

	int get_input_key();


	//Card select - Cases: 
	bool valid_select(const Player&, const Card&, const Card&, const int&);
	bool invalid_select(const Player&, const Card&, const Card&, const int&);
	bool pass_select(Player&,const int&);

	//Direction of the game
	void change_direction(const Card&, int&);
	int validate_move(const int&);
	
	//Players turn
	int get_player_turn_case(int,const Card&);
	void caseHandler(const int&, int&,int&,Card&);
	//DEBUG
	void DEBUG_PRINT_PLAYERS();
	void GAME_LOG(const int&);
};
#endif




