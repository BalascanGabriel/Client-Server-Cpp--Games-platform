#pragma once

#include "CardType.h"
#include "Card.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class DeckUtil
{
public:
	static std::vector<Card*> generate_deck(bool blackjack) {
		std::vector<CardType> all_types;
		all_types.push_back(CardType::CLUBS);
		all_types.push_back(CardType::DIAMONDS);
		all_types.push_back(CardType::HEARTS);
		all_types.push_back(CardType::SPADES);

		std::vector<Card*> deck;

		if (blackjack) {
			for (int i = 2; i <= 14; i++) {
				for (int j = 0; j < all_types.size(); j++) {
					Card* card = new Card(all_types[j], (i >= 10) ? 10 : i); // conditie ? ce_se_returneaza_daca_true : ce_se_returneaza_daca_false
					card->set_initial_value(i);
					deck.push_back(card);
				}
			}
		}
		else {
			for (int i = 2; i <= 14; i++) {
				for (int j = 0; j < all_types.size(); j++) {
					Card* card = new Card(all_types[j], (i >= 10) ? 0 : i); // conditie ? ce_se_returneaza_daca_true : ce_se_returneaza_daca_false
					card->set_initial_value(i);
					deck.push_back(card);
				}
			}
		}

		auto rng = std::default_random_engine{};
		rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
		std::shuffle(std::begin(deck), std::end(deck), rng);
		return deck;
	}
};

