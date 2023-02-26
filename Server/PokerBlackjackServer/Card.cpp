#include "Card.h"

Card::Card()
{
}

Card::Card(CardType card_type, int value): card_type(card_type), value(value)
{
}

CardType Card::get_card_type()
{
	return this->card_type;
}

int Card::get_value()
{
	return this->value;
}

void Card::set_value(int value)
{
	this->value = value;
}

void Card::set_initial_value(int iv)
{
	this->initial_value = iv;
}

void Card::set_card_type(CardType type)
{
	this->card_type = type;
}
