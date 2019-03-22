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
	int num_of_cards;
	//vector of cards
	vector<Card> cards_vec;
	//private members

public:
	//public members
	bool play(Card&);
	string get_name() const;
	void set_name(string name);
	vector<Card> get_cards_vec();
	void set_cards_vec(const vector<Card> tmp_vec);
	void insert_card(const Card&);
	void pop_card(int&);
	void card_vector_toString();
	void cards_print();
	int get_cardVec_size();
};
#endif



