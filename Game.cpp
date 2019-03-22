#include "Game.h"
#define DEBUG
#define LOG(x) cout<< x << endl;

// 1-GAME STARTER!
void Game::start(){
    //welcome messages
    msg_welcome(); // welcome message.
    msg_rules(); // rules - optional.
    msg_players_num(); // set number of players.
    msg_cards_num(); // set number of cards.
    set_players_name(); // set the names of the players. NOTE: AND DEAL CARDS.

    // select random initial-game card 
    set_game_initial_gamecard();

    bool gameOn = true;
    int turn_counter = 0;
    // Game keeps going until some player use all his cards.
    while(gameOn){
        // check if some one finished his cards.
        if(find_winner()){
            break;
        }
        //pickup the next player 
        set_round_player(turn_counter);
        //show his card
        show_gameStatus_stamp(this->current_player);
        // read the input, player select his card from his card_vec. TODO: pass here the $player and the $turn_counter
        int key_select = get_input_key();

       

        //TODO KEEP FROM HERE, 
        // check validity of the pickup card 1-good 2-bad 3-pass
        // check_card_validity(turn_counter, key_select);
    }


    // DEBUG-ZONE
    #ifdef DEBUG
        DEBUG_PRINT_PLAYERS();
    #endif
}

void Game::msg_rules(){
    cout<< "Please enter Player name: " <<endl;
}
void Game::msg_welcome(){
    cout << "Welcome to Taki" << endl;
}

void Game::msg_players_num(){
    cout<<"How many Players" << endl;
    int x; // TODO: check if x is good-input?
    cin >> x;
    this->players_num = x;
    cout << this->players_num << endl;
}
void Game::msg_cards_num(){
    cout<<"How many Cards?" << endl;
    int x; // TODO: check if x is good-input?
    cin >> x;
    this->cards_num = x;
    cout << this->cards_num << endl;
}

void Game::set_players_name(){
    this->players_arr = new Player[sizeof(Player) * this->players_num];

    for(int i = 0 ; i < this->players_num ; ++i){
        cout << "Player number " << i+1 << " name?" << endl;
        string input_name;
        cin >> input_name;
        this->players_arr[i].set_name(input_name);
        //set array of cards to the players
        card_dealing(this->players_arr[i]);
    }
}

void Game::set_game_initial_gamecard(){
    this->current_card = Card::generate_card();
}
void Game::card_dealing(Player& player){
    
    for(int i = 0; i < this->cards_num; ++i)
    {
        Card tmp = Card::generate_card();
        player.insert_card(tmp);
    }
    
}

bool Game::find_winner(){
    for(int i = 0; i < this->players_num; i++)
    {
        if(this->players_arr[i].get_cardVec_size() == 0) return true;
    }
    return false;
}
void Game::set_round_player(const int& turn_count){
    if(turn_count == 0){
        this->current_player = this->players_arr[0];
    }else{
        this->current_player = this->players_arr[(turn_count%this->players_num)];
    }
}
void Game::show_gameStatus_stamp(const Player&){
    cout << "curretn: " << this->current_card << endl;
    cout << this->current_player.get_name() << ", you turn - " << endl;
    cout << "Your cards: ";
    this->current_player.cards_print();
    cout << endl;
}


//Check if the card that was selected by the player is: 1)valid 2)invalid 3)pass
int Game::check_card_validity(int& turn_count, const int& key){
    cout << key << endl;
    return 0;
}

int Game::get_input_key()
{
	int ret_integer;
	string str_number;

	while(true) {

		
		getline(cin, str_number); //get string input
		stringstream convert(str_number); //turns the string into a stream

		//checks for complete conversion to integer and checks for minimum value
		if(convert >> ret_integer && !(convert >> str_number)) return ret_integer;

		cin.clear(); //just in case an error occurs with cin (eof(), etc)
		
	}
}

	bool Game::valid_select(const Player& cur_player, const Card& cur_game_card, const Card& player_card, const int& key){
        if(cur_game_card.is_legal(player_card)){
            return true;
        }
        return false;
    }
	bool Game::invalid_select(const Player& cur_player, const Card& cur_game_card, const Card& player_card, const int& key){
        if(!cur_game_card.is_legal(player_card)){
            return true;
        }
        return false;
    }
	bool Game::pass_select(Player& cur_player, const int& key){
        if(key > cur_player.get_cardVec_size() || key == 0){
            return true;
        }
        return false;
    }

void Game::change_direction(){
    this->mDirection * -1 ;
}

int Game::get_player_turn_case(int key_select, int& turn_counter){
     if (pass_select(this->current_player, key_select))
        {   // case-3 is it 0 or bigger then he has - pass turn
            LOG("PASS SELECT ");
            return 3;
        }
        else if (invalid_select(this->current_player, this->current_card, this->current_player.get_cards_vec().at(key_select - 1), key_select))
        { // invalid?
            LOG("INVALID SELECT ");
            return 2;
        }
        else if (valid_select(this->current_player, this->current_card, this->current_player.get_cards_vec().at(key_select - 1), key_select))
        { // Valid
            LOG("VALID SELECT ");
            return 1;
        }
        else
        { // some error?...
            cout << "some thing went wrong" << endl;
            return -1;
        }
}

void Game::caseHandler(const int& player_case, int& turn_count, int& card_num){
    if(player_case == 3) { // pass the turn, add new card to players vec
        Card tmp = Card::generate_card();
        this->current_player.insert_card(tmp);
        turn_count = turn_count + this->mDirection;
        set_round_player(turn_count);
    }else if(player_case == 1){ // valid, change card  | change direction
        this->current_player.pop_card(card_num);
        this->current_card = this->players_card_select;
        change_direction(this->current_card);

    }else{// some thing wrong
        cout << "something went wrong: caseHandler" << endl;
    }  
}



//DEBUG
void Game::DEBUG_PRINT_PLAYERS(){
    string tamplate_player = " Player: ";
    string tamplate_cards = " Cards: ";
    for(int i = 0 ; i < this->players_num ; ++i){
        
        cout <<tamplate_player<< i + 1 << " " << this->players_arr[i].get_name()<< endl;
        this->players_arr[i].cards_print();

        // red color terminal print
        //  cout << "\033[1;31mbold red text\033[0m\n";

    }
}

