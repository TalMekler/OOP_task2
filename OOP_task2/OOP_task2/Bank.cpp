#include "Bank.h"

Bank::Bank() {
	m_name = nullptr;
	m_account = nullptr;
	m_bankCode = 0;
	m_numbeOfAccounts = 0;
	m_totalBalance = 0;
}

Bank::Bank(const char* name, int code) {
	m_bankCode = code;
	SetBankName(name);
	m_account = nullptr;
	m_totalBalance = 0;
}
Bank::~Bank() {
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		delete m_account[i];
	}
	delete[] m_account;
	delete[] m_name;

}

void Bank::SetBankName(const char* name) {
	int i;
	m_name = new char[strlen(name) + 1];
	for (i = 0; i < strlen(name); i++) {
		m_name[i] = name[i];
	}
	m_name[i] = '\0';
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

void Bank::AddAccount(const Account& account) {
	Account** tmp = new Account * [m_numbeOfAccounts + 1];
	int i, flag = 1;
	for (i = 0; i < m_numbeOfAccounts; i++) {
		if (account.GetAccountNumber() == m_account[i]->GetAccountNumber()) {

			flag = 0;
		}
		tmp[i] = new Account(*m_account[i]);
		//DeleteAccount(*m_account[i]);
	}
	delete[] m_account;
	if (flag) {
		tmp[i] = new Account(account);
		m_numbeOfAccounts++;
		m_totalBalance += account.GetBalance();
	}
	SetAccount(tmp, m_numbeOfAccounts);
	for (i = 0; i < m_numbeOfAccounts; i++) {
		delete tmp[i];
	}
	delete[] tmp;

}
void Bank::AddAccount(const Person& per, double amount) {
	Account* newA = new Account(per, amount);
	AddAccount(*newA);
	delete newA;
}
void Bank::AddPerson(const Person& newPerson, const Account& account, double amount) {
	int flag = 1;
	AddAccount(account);
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		if (account.GetAccountNumber() == m_account[i]->GetAccountNumber()) {
			for (int j = 0; j < m_account[i]->GetTotalPersons(); j++) {
				if (newPerson.GetId() == m_account[i]->GetPersons()[j]->GetId() &&
					0 == strcmp(newPerson.GetName(), m_account[i]->GetPersons()[j]->GetName())) {
					flag = 0;
				}
			}
			if (flag) {
				m_account[i]->AddPerson(newPerson, amount);
			}
		}
	}
}
void Bank::DeleteAccount(const Account& account) {
	Account** tmp = new Account * [m_numbeOfAccounts];
	int i, flag = 0;
	for (i = 0; i < m_numbeOfAccounts; i++) {
		if (m_account[i]->GetAccountNumber() != account.GetAccountNumber()) {
			tmp[i] = new Account(*m_account[i]);
			delete m_account[i];
		}
		else {
			flag = 1;
		}
	}
	if (flag) {
		m_numbeOfAccounts--;
	}
	SetAccount(tmp, m_numbeOfAccounts);
	for (i = 0; i < m_numbeOfAccounts; i++) {
		delete tmp[i];
	}
	delete[] tmp;
}
void Bank::DeletePerson(const Person& p) {
	int i;
	for (i = 0; i < m_numbeOfAccounts; i++) {
		m_account[i]->DeletePerson(p);
		if (m_account[i]->GetTotalPersons() == 0) {
			DeleteAccount(*m_account[i]);
		}
	}
}