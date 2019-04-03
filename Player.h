/* Mark  */

/* Gal  */
#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;
class Player {
private:
	string name;
	//vector of cards
	vector<Card> cards_vec;
	int numOfCards;
	//private members

public:
	//public members
	Player(const string& n);
    Player(const string& n, int cardsNum);
    Player(const Player& player);

    Player(){}
	string get_name() const;
	void set_name(string name);
	vector<Card> get_cards_vec();

	void set_cards_vec(const vector<Card> tmp_vec);
	void insert_card(const Card&);
	void pop_card(int);
	void cards_print();
	int get_cardVec_size();
	int const const_card_size() const;

	bool play(Card&);
    Player& operator=(Player const&);
	friend ostream&operator <<(ostream& os,  Player& player);
};
#endif



