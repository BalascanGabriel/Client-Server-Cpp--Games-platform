#pragma once
#include <iostream>
#include <string>
#include <vector>


using namespace std;


class User
{
private:
	int id; // {get, set}
	string username;
	string password;
public:
	User();
	User(int id, string username, string password);
	User(string username, string password);

	int get_id();
	void set_id(int id);
	void set_username(string username);
	string get_username();
	void set_password(string password);
	string get_password();

};

