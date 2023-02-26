#include "CommandStartGameBlackJack.h"


CommandStartGameBlackJack::CommandStartGameBlackJack(SOCKET& socket) : Response(socket)
{
	this->comType = CommandType::START_GAME;
}

std::string* CommandStartGameBlackJack::execute()
{

	std::cout << "STARTING BLACK JACK GAME" << std::endl;

	std::vector<Card*> deck = DeckUtil::generate_deck(true);
	bool continue_playing = true;
	while (continue_playing) {
		continue_playing = iteratie_joc(deck);
	}
	
	


	std::cout << "GAME OVER OR PLAYER REQUESTED END OF GAME - blackjack over" << std::endl;

	
	//std::string* username = this->get_message(this->socket);
	//// std::string* email = this->get_message(this->socket);
	//std::string* password = this->get_message(this->socket);
	//User user_nou(*username, *password);
	//int id_user = UserDB::insert_user(user_nou);
	//std::cout << "REGISTERING WITH: " << *username << " PASSWORD: " << *password << std::endl;
	//this->send_message(this->socket, "" + to_string(id_user));

	return nullptr;
}

bool CommandStartGameBlackJack::iteratie_joc(std::vector<Card*>& deck)
{

	// ---- start iteratie ---- 
	std::cout << "===========================iteratie============================" << std::endl;
	Card* card_dealer_visibile = deck.back();
	deck.pop_back();


	Card* card_dealer_hidden = deck.back();
	deck.pop_back();

	vector<Card*> player_hand;
	vector<Card*> dealer_hand;

	dealer_hand.push_back(card_dealer_visibile);
	dealer_hand.push_back(card_dealer_hidden);

	Card* card_player1 = deck.back();
	deck.pop_back();

	Card* card_player2 = deck.back();
	deck.pop_back();

	player_hand.push_back(card_player1);
	player_hand.push_back(card_player2);

	std::cout << "TO STRING OBJECT ARATA ASA: " << std::endl;
	std::cout << "==========================================================" << std::endl;
	std::cout << "Your cards: " << std::endl;
	std::cout << card_player1->to_string_object() << std::endl;
	std::cout << card_player2->to_string_object() << std::endl;
	std::cout << "Dealer cards: " << std::endl;
	std::cout << card_dealer_visibile->to_string_object() << std::endl;
	std::cout << card_dealer_hidden->to_string_object() << std::endl;

	std::string message = card_player1->to_string_object() + " " + card_player2->to_string_object() + " " + card_dealer_visibile->to_string_object();
	this->send_message(this->socket, "" + message);
	std::string* player_action = this->get_message(this->socket);

	bool player_lost = false;
	int total_card_value = 0;

	if (player_action->compare("end") == 0) {
		return false;
	}

	while (player_action->find("hit") != std::string::npos  ) {

		std::stringstream ss(*player_action);
		std::string temp;

		ss >> temp;
		int amount_to_bet;
		int id_user;
		ss >> amount_to_bet;
		ss >> id_user;

		std::cout << "PLAYER WANTS HIT" << std::endl;
		std::cout << "Amount bet: " << amount_to_bet << std::endl;
		std::cout << "User that played: " << id_user << std::endl;
		Card* newcard = deck.back();
		deck.pop_back();
		player_hand.push_back(newcard);


		total_card_value = 0;
		for (int i = 0; i < player_hand.size(); i++) {
			Card* card_in_hand = player_hand[i];
			total_card_value += card_in_hand->get_value();
		}
		std::string player_hand_message = "";

		for (int i = 0; i < player_hand.size(); i++) {
			Card* card = player_hand[i];
			player_hand_message += card->to_string_object() + " ";
		}

		if (total_card_value > 21) {
			std::cout << "TOTAL_CARD_VALUE: " << total_card_value << std::endl;
			player_hand_message += "GAME OVER/BUST";
			UserDB::update_player_budget(id_user, amount_to_bet, false);

			player_lost = true;
		}

		this->send_message(this->socket, "" + player_hand_message);
		player_action = this->get_message(this->socket);
	}

	if (player_lost) {
		std::cout << "PLAYER LOST" << std::endl;
	}
	else {
		std::cout << "PLAYER WANTS STAND" << std::endl;

		std::stringstream ss(*player_action);
		std::string temp;
		ss >> temp;
		int amount_to_bet;
		ss >> amount_to_bet;

		int id_user;
		ss >> id_user;
		std::cout << "User that played: " << id_user << std::endl;

		
		std::cout << "Amount bet: " << amount_to_bet << std::endl;

		int total_card_value_dealer_before_draw_rest = 0;
		for (int i = 0; i < dealer_hand.size(); i++) {
			Card* dealer_card = dealer_hand[i];
			total_card_value_dealer_before_draw_rest += dealer_card->get_value();
		}
		while (total_card_value_dealer_before_draw_rest < 17) {
			Card* dealer_new_card = deck.back();
			dealer_hand.push_back(dealer_new_card);
			deck.pop_back();
			total_card_value_dealer_before_draw_rest += dealer_new_card->get_value();
		}

		std::string dealer_hand_message = "";

		for (int i = 0; i < dealer_hand.size(); i++) {
			Card* card = dealer_hand[i];
			dealer_hand_message += card->to_string_object() + " ";
		}

		total_card_value = 0;
		for (int i = 0; i < player_hand.size(); i++) {
			Card* card_in_hand = player_hand[i];
			total_card_value += card_in_hand->get_value();
		}
		std::cout << "TOTAL CARD VALUE PLAYER: " << total_card_value << std::endl;
		std::cout << "Number of cards in player hand: " << player_hand.size() << std::endl;

		if (total_card_value_dealer_before_draw_rest <= 21) {
			std::cout << "OUR TOTAL: " << total_card_value << " DEALER TOTAL " << total_card_value_dealer_before_draw_rest << std::endl;
			if (total_card_value > total_card_value_dealer_before_draw_rest) {
				dealer_hand_message += "GAME OVER/YOU WON";
				UserDB::update_player_budget(id_user, amount_to_bet, true);
				std::cout << "GAME OVER/YOU WON" << std::endl;
			}
			else {
				if (total_card_value == total_card_value_dealer_before_draw_rest) {
					dealer_hand_message += "GAME OVER/PUSH";
					std::cout << "GAME OVER/PUSH" << std::endl;

				}
				else {
					dealer_hand_message += "GAME OVER/DEALER WON";
					UserDB::update_player_budget(id_user, amount_to_bet, false);
					std::cout << "GAME OVER/DEALER WON" << std::endl;
				}
			}
			
		}
		else {
			dealer_hand_message += "GAME OVER/DEALER BUST";
			std::cout << "GAME OVER/DEALER BUST" << std::endl;
			UserDB::update_player_budget(id_user, amount_to_bet, true);
		}

		this->send_message(this->socket, "" + dealer_hand_message);
		std::string* continue_message_from_client = this->get_message(this->socket);
		if (continue_message_from_client->compare("continue") == 0) {
			return true;
		}
		return false;
		// ...
	}

	// ---- end iteratie ---- 
}
