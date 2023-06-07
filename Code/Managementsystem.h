#pragma once
#include<iostream>
using namespace std;
class Admin {
	static int count;
	string name;
	string username;
	string email;
	string password;
public:
	Admin(string name = "admin123", string username = "admin123", string email = "admin123gmail.com", string password = "12345678")
	{
		this->name = name;
		this->username = username;
		this->email = email;
		this->password = password;
	}
	void InputName(string name);
	void InputUsername(string username);
	void InputEmail(string email);
	void InputPassword(string password);
	string getName();
	string getUsername();
	string getEmail();
	string getPassword();
	void Addgames();
};
struct Players {
	static int count;
	string name;
	string username;
	string email;
	string password;
	float BalanceAmount;
	char Rank;
	float WinLossRatio;
public:
	Players(string name = "admin123", string username = "admin123", string email = "admin123gmail.com", string password = "12345678", float BalanceAmount = 0, char Rank = 'E', float WinLossRatio = 0)
	{
		this->name = name;
		this->username = username;
		this->email = email;
		this->password = password;
		this->BalanceAmount = BalanceAmount;
		this->Rank = Rank;
		this->WinLossRatio = WinLossRatio;
	}
	void InputName(string name);
	void InputUsername(string username);
	
	string getName();
	string getUsername();
	string getEmail();
	string getPassword();
	void AddBalance(float amount);
	float getBalance();
	float getWinLossRatio();
	void ChangePassword();
	void RankUpgradeReq();
	void DeleteAccount();
	

};
class Earnings {
	float maintainence;
	float bills;
	float profit;
	float loss;
	float GameEarning;
	float tournamentsBudget;
	float merchandise;
};
struct scn2
{
	bool email = false;
	bool password = false;
};
struct scn3
{
	bool email = false;
	bool confirmEmail = false;
	bool password = false;
	bool confirmPassword = false;
};
struct scn9
{
	bool email = false;
	bool password = false;
};
struct scn4
{
	bool cash = 0;
};

