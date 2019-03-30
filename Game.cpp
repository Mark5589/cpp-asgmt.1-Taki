#include "Game.h"
//#define DEBUG
#define LOG(x) cout<< x << endl;

// 1-GAME STARTER!
void Game::start(){

    /*
     * THIS IS FIRST GAME STEPS, just settings.
     * */
    //welcome messages
    msg_welcome(); // welcome message.
    msg_rules(); // rules - optional.
    msg_players_num(); // set number of players.
    msg_cards_num(); // set number of cards.
    set_players_name(); // set the names of the players. NOTE: AND DEAL CARDS.
    set_game_initial_gamecard(); // select random initial-game card
//    GAME_LOG(0);
//    cout << "PRINTING PLAYERS..." << endl;
//    DEBUG_PRINT_PLAYERS();
    bool gameOn = true;
    int turn_counter = 0;
    set_round_player(turn_counter);

    // Game keeps going until some player use all his cards.
    while(gameOn){
//        GAME_LOG(turn_counter);
//        cout << this->current_player.get_name() << " " << this->current_player.get_cardVec_size() << endl;
//        LOG(turn_counter);
        // check if some one finished his cards.
        if(find_winner()){
            break;
        }
        //pickup the next player 
//        set_round_player(turn_counter);
        //show his card
        show_gameStatus_stamp(this->current_player);
        // read the input, player select his card from his card_vec. TODO: pass here the $player and the $turn_counter
        int key_select = get_input_key();
        int player_case = get_player_turn_case(key_select);
        while(player_case == 2 ){
            cout << "You can\'t put " << this->current_player.get_cards_vec().at(key_select-1) << " on "<< this->current_card << endl;
            int key_select = get_input_key();
            player_case = get_player_turn_case(key_select);
        }
        caseHandler(player_case, turn_counter, key_select);


    }


    // DEBUG-ZONE
    #ifdef DEBUG
        DEBUG_PRINT_PLAYERS();
    #endif
}

void Game::msg_rules(){
    cout<< "RULES" <<endl;
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
    for(int i = 0 ; i < this->players_num ; ++i){
        cout << "Player number " << i+1 << " name?" << endl;
        string input_name;
        cin >> input_name;
        Player p = Player(input_name);
        this->players_arr.push_back(p);
        //set array of cards to the players
        card_dealing(this->players_arr.at(i));
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
        if(this->players_arr.at(i).get_cardVec_size() == 0) return true;
    }
    return false;
}
void Game::set_round_player(const int& turn_count){

    if(turn_count == 0){
        this->current_player = this->players_arr.at(0);

    }else if(turn_count < 0) {
        int turn = turn_count;
        while(turn < 0){
            turn = turn + this->players_num;
        }
        this->current_player = this->players_arr.at((turn%this->players_num));
    }
    else{
        this->current_player = this->players_arr.at((turn_count%this->players_num));
    }
}
void Game::show_gameStatus_stamp(const Player&){
    cout << "current: " << this->current_card << endl;
    cout << this->current_player.get_name() << ", you turn - " << endl;
    cout << "Your cards: ";
    this->current_player.cards_print();
    cout << endl;
}




int Game::get_input_key(){
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

void Game::change_direction(const Card& card, int& turn){
    sign s = card.get_sign();
    if(s == sign::PLUS){ // +, turn stays on the current player
        turn = turn;
    }else if(s == sign::CD){ // -><- , change direction, 
        this->mDirection = this->mDirection * -1;
        turn = turn + this->mDirection;
    }else if(s == sign::STOP) { // STOP , hop one player, turn goes up by two. (pass the next player)
        turn = turn + this->mDirection * 2;
    }else { // every other card. , turn increased by one.
        turn = turn + this->mDirection;
    }
}

int Game::get_player_turn_case(int key_select){
     if (pass_select(this->current_player, key_select))
        {   // case-3 is it 0 or bigger then he has - pass turn
//            LOG("PASS SELECT ");
            return 3;
        }
        else if (invalid_select(this->current_player, this->current_card, this->current_player.get_cards_vec().at(key_select - 1), key_select))
        { // invalid?
//            LOG("INVALID SELECT ");
            return 2;
        }
        else if (valid_select(this->current_player, this->current_card, this->current_player.get_cards_vec().at(key_select - 1), key_select))
        { // Valid
//            LOG("VALID SELECT ");
            return 1;
        }
        else
        { // some error?...
            cout << "some thing went wrong in : Game::get_player_turn_case " << endl;
            return -1;
        }
}

void Game::caseHandler(const int& player_case, int& turn_count, int& key_selected){ // TODO : VALIDATE THE player_index if its negative
    int player_index =   turn_count % this->players_num;

    if(player_case == 3) { // pass the turn, add new card to players vec
        Card tmp = Card::generate_card();
//        this->current_player.insert_card(tmp);
        this->players_arr.at(player_index).insert_card(tmp);
        turn_count = turn_count + this->mDirection;
        turn_count = validate_move(turn_count);
        set_round_player(turn_count);
    }else if(player_case == 1){ // valid, change card  | change direction
        Card c = this->current_player.get_cards_vec().at(key_selected-1);
//        cout << "THE CARD THAT U SELECTED IS : " << c << endl;
        this->players_arr.at(player_index).pop_card(key_selected-1);
//        this->current_player.cards_print();
        this->current_card = c;
        change_direction(this->current_card, turn_count);
        turn_count = validate_move(turn_count);
        set_round_player(turn_count);
    }else{// some thing wrong
        cout << "something went wrong: caseHandler" << endl;
    }  
}



//DEBUG
void Game::DEBUG_PRINT_PLAYERS(){
    string tamplate_player = " Player: ";
//    string tamplate_cards = " Cards: ";
    for(int i = 0 ; i < this->players_num ; ++i){
        
        cout <<tamplate_player<< i + 1 << " " << this->players_arr.at(i).get_name()<< endl;
//        this->players_arr[i].cards_print();

        // red color terminal print
        //  cout << "\033[1;31mbold red text\033[0m\n";

    }
}

void Game::GAME_LOG(const int& counter) {
    cout << "GAME LOG:" << endl;
    cout << "turn counter: " << counter << endl;
    cout << "Game current player: " << this->current_player.get_name() << endl;
    cout << "Players cards: " << endl; this->current_player.cards_print();
    cout << "Game current Card: " << this->current_card << endl;
    cout << "other players name and cards: "<< endl;
    for(int i = 0 ; i < this->players_num ; ++i){
        cout << "player: " << this->players_arr.at(i).get_name() << endl;
        this->players_arr.at(i).cards_print();
    }

    cout << "--- END LOG --- " << endl;
}

int Game::validate_move(const int& turn_index_vec) {
    int tmp = turn_index_vec;
    if(tmp == 0){
        return 0;
    }
    else if(tmp < 0) {
        while(tmp < 0){
            tmp = tmp + 4;
        }
        tmp = tmp % this->players_num;
        return tmp;
    }
    else{ // tmp > 0
        return (tmp % this->players_num);
    }
}

