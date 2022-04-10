#include "Bank.h"

Bank::Bank(const char* name, int code) {
	m_bankCode = code;
	SetBankName(name);
}
Bank::~Bank();

void Bank::SetBankName(const char* name) {
	if (m_name)
		delete[] m_name;
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);
}
void Bank::SetAccount(Account** account, int numbeOfAccounts) {
	m_account = new Account * [numbeOfAccounts];
	m_numbeOfAccounts = numbeOfAccounts;
	int i;
	for (i = 0; i < numbeOfAccounts; i++) {
		m_account[i] = new Account(*account[i]);
	}
}
void Bank::SetTotal(double total) {
	m_totalBalance = total;
}
void Bank::SetCode(int code) {
	m_bankCode = code;
}
const char* Bank::GetBankName() const {
	return m_name;
}
Account** Bank::GetAccounts() const {
	return m_account;
}
int	Bank::GetNumberOfAccounts() const {
	return m_numbeOfAccounts;
}
double Bank::GetTotal() const {
	return m_totalBalance;
}
int	Bank::GetCode() const {
	return m_bankCode;
}

void Bank::AddAccount(const Account& account);
void Bank::AddAccount(const Person& per, double amount);
void Bank::AddPerson(const Person& newPerson, const Account& account, double amount);
void Bank::DeleteAccount(const Account& account);
void Bank::DeletePerson(const Person& p);