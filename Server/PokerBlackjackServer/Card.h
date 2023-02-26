#pragma once
#include <iostream>
#include <string>
#include "CardType.h"
using namespace std;
class Card
{
private:
protected:
	string name;
	CardType card_type;
	int value;
	int initial_value;
public:

	Card();
	Card(CardType card_type, int value);

	CardType get_card_type();
	int get_value();
	void set_value(int value);
	void set_initial_value(int iv);
	void set_card_type(CardType type);

	static std::string* card_type_string(CardType ct) {

		std::string* result = NULL;
		switch (ct) {
		case CardType::CLUBS:
			result = new string("CLUBS");
			break;
		case CardType::DIAMONDS:
			result = new string("DIAMONDS");
			break;
		case CardType::HEARTS:
			result = new string("HEARTS");
			break;
		case CardType::SPADES:
			result = new string("SPADES");
			break;
		}
		return result;
	}

	static std::string card_specific_name_from_value(int value) {

		if (value == 11) {
			return "ACE";
		}

		if (value == 12) {
			return "JACK";
		}
		if (value == 13) {
			return "QUEEN";
		}
		if (value == 14) {
			return "KING";
		}
		return std::to_string(value);
	}

	std::string to_string_object() {
		std::string card_name = card_specific_name_from_value(this->initial_value) + "_of_"+ (*Card::card_type_string(this->card_type)) ;
		std::string result = card_name + " " + to_string(this->value);
		return result;

	}
};

