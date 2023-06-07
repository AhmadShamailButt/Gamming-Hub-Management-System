//#include "Managementsystem.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include "textbox.h"
#include"Managementsystem.h"

void Admin::InputName(string name) {
	this->name = name;
}
void Admin::InputUsername(string username) {
	this->username = username;
}
void Admin::InputEmail(string email) {
	this->email = email;
}
void Admin::InputPassword(string password) {
	this->password = password;
}
string Admin::getName() {
	return name;
}
string Admin::getUsername() {
	return username;
}
string Admin::getEmail() {
	return email;
}
string Admin::getPassword() {
	return password;
}
void Admin::Addgames() {
	//functionalty not provided yet
}
void Players::InputName(string name) {
	this->name = name;
}
void Players::InputUsername(string username) {
	this->username = username;
}
string Players::getName() {
	return name;
}
string Players::getUsername() {
	return username;
}
string Players::getEmail() {
	return email;
}
string Players::getPassword() {
	return password;
}
void Players::AddBalance(float amount) {
	BalanceAmount += amount;
}
float Players::getBalance() {
	return BalanceAmount;
}
void Players::ChangePassword() {
	//functionality will be provided using SFML in upcoming evaluations
}
void Players::RankUpgradeReq() {
	//functionality will be provided using SFML in upcoming evaluations
}
float Players::getWinLossRatio() {
	return WinLossRatio;
}
void Players::DeleteAccount() {
	// functionalty in later stages
}
