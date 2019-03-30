#include "Player.h"

Player::Player(const string& n){
    this->name = n;
}

 string Player::get_name() const{
    return this->name;
}

void Player::set_name( string input_name){
    this->name = input_name;
}

vector<Card> Player::get_cards_vec(){
    return this->cards_vec;
}
void Player::set_cards_vec(const vector<Card> tmp_vec){
    this->cards_vec = tmp_vec;
}

void Player::insert_card(const Card& c){
    this->cards_vec.push_back(c);
}


void Player::cards_print(){
    for(int i = 0; i < this->cards_vec.size(); ++i)
    {
        if( i == 0 ){
            cout<<"(1) " << this->cards_vec.at(i);
        }else{
            cout << " , "<< "(" << i+1 << ")"<< this->cards_vec.at(i);
        }
    }
    cout << endl;
}

int Player::get_cardVec_size(){
    return this->cards_vec.size();
}

void Player::pop_card(int index){
    this->cards_vec.erase(this->cards_vec.begin() + index);
}


