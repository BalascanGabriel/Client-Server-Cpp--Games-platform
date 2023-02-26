#include "User.h"

User::User()
{
}

User::User(int id, string username, string password)  : id(id), username(username), password(password)
{
}

User::User(string username, string password) : username(username), password(password)
{
}

int User::get_id()
{
	return this->id; 
}

void User::set_id(int id)
{
	this->id = id;
}

void User::set_username(string username)
{
	this->username = username;
}

string User::get_username()
{
	return this->username;
}

void User::set_password(string password)
{
	this->password = password;
}

string User::get_password()
{
	return this->password;
}
