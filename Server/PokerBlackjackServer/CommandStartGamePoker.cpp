#include "CommandStartGamePoker.h"

CommandStartGamePoker::CommandStartGamePoker(SOCKET& socket) : Response(socket)
{
	this->comType = CommandType::START_GAME_POKER;
}

std::string* CommandStartGamePoker::execute()
{

	std::cout << "Playing poker" << std::endl;
	std::vector<Card*> deck = DeckUtil::generate_deck(false);

	bool continue_playing = true;
	while (continue_playing) {
		continue_playing = iteratie_joc(deck);
	}
	// this->iteratie_joc(deck);

	std::cout << "GAME OVER OR PLAYER REQUESTED END OF GAME - baccarat over" << std::endl;
	return nullptr;
}

bool CommandStartGamePoker::iteratie_joc(std::vector<Card*>& deck) {
	vector<string> options;
	options.push_back("tie");
	options.push_back("banker");
	options.push_back("player");
	options.push_back("banker_pair");
	options.push_back("player_pair");


	std::string* message_from_client = this->get_message(this->socket);
	std::stringstream ss(*message_from_client);
	std::string user_choice;

	

	ss >> user_choice;
	int amount_to_bet;
	int id_user;
	ss >> amount_to_bet;
	ss >> id_user;

	//std::string* user_choice = this->get_message(this->socket);
	vector<Card*> bank_cards;
	vector<Card*> player_cards;

	Card* card_bank_1 = deck.back();
	bank_cards.push_back(card_bank_1);
	deck.pop_back();
	
	Card* card_bank_2 = deck.back();
	bank_cards.push_back(card_bank_2);
	deck.pop_back();

	
	Card*  card_player_1 = deck.back();
	player_cards.push_back(card_player_1);
	deck.pop_back();


	Card*  card_player_2 = deck.back();
	player_cards.push_back(card_player_2);
	deck.pop_back();

	std::string message = card_bank_1->to_string_object() + " " + card_bank_2->to_string_object() + " " + card_player_1->to_string_object() + " " + card_player_2->to_string_object();
	int score_bank = (card_bank_1->get_value() + card_bank_2->get_value()) % 10;
	int score_player = (card_player_1->get_value() + card_player_2->get_value()) % 10;
	std::cout << "Score bank: " << score_bank << " Score player: " << score_player << std::endl;

	bool pair_banker = card_bank_1->get_value() == card_bank_2->get_value();
	bool pair_player = card_player_1->get_value() == card_player_2->get_value();


	if (user_choice.compare("end") == 0) {
		return false;
	}

	bool you_won = false;
	if (user_choice.compare("tie") == 0) {
		you_won = score_bank == score_player;
	}
	else if (user_choice.compare("banker") == 0) {
		you_won = score_bank > score_player;

	}
	else if (user_choice.compare("player") == 0) {
		you_won = score_bank < score_player;
	}
	else if (user_choice.compare("banker_pair") == 0) {
		you_won = pair_banker;
	}
	else if (user_choice.compare("player_pair") == 0) {
		you_won = pair_player;
	}


	message += " ";
	message += (you_won ? "YOU_WON" : "YOU_LOST");

	UserDB::update_player_budget(id_user, amount_to_bet, you_won);
	this->send_message(this->socket, "" + message);


	

	std::string* continue_message_from_client = this->get_message(this->socket);
	if (continue_message_from_client->compare("continue") == 0) {
		return true;
	}
	return false;


}
