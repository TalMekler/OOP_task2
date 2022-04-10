#include "Account.h"

Account::Account(Person** persons, int count, double balance) {
	// Ctor - list of persons
	m_balance = balance;
	SetPersons(persons, count);
}
Account::Account(const Person& person, double balance) {
	// Ctor - 1 person
	m_totalPersons = 1;
	m_balance = balance;
	m_persons = new Person * [1];
	m_persons[0] = new Person(person);
}

Account::Account(const Account& other) {
	// Copy Ctor
	SetTransactions(other.m_transactionList, other.m_numberOfTransaction);
	SetPersons(other.m_persons, other.m_totalPersons);
	m_accountNumber = other.m_accountNumber;
	m_balance = other.m_balance;
}
Account::~Account() {
	clearTransactions();
	clearPersons();
}

void Account::SetPersons(Person** persons, int count) {
	m_totalPersons = count;
	m_persons = new Person * [count];
	for (int i = 0; i < count; i++) {
		m_persons[i] = new Person(*persons[i]);
	}
}

void Account::SetAccountNumber(int number) {
	m_accountNumber = number;
}

void Account::SetBalance(double balance) {
	m_balance = balance;
}

void Account::SetTransactions(Transaction** newTransaction, int count) {
	m_transactionList = new Transaction * [count];
	m_numberOfTransaction = count;
	for (int i = 0; i < count; i++) {
		m_transactionList[i] = new Transaction(*newTransaction[i]);
	}
}

Transaction** Account::GetTransactions() {
	return m_transactionList;
}

int	Account::GetNumOfTransactions() {
	return m_numberOfTransaction;
}
Person** Account::GetPersons() const {
	return m_persons;
}
int	Account::GetTotalPersons()const {
	return m_totalPersons;
}
int	Account::GetAccountNumber() const {
	return m_accountNumber;
}
double Account::GetBalance() const {
	return m_balance;
}

void Account::Withdraw(double amount, const char* date);
void Account::Deposit(double amount, const char* date);
void Account::AddPerson(const Person& newPerson, double	amount);
void Account::DeletePerson(const Person& oldPerson);
void Account::AddTransaction(const Transaction& newTransaction);

void Account::clearTransactions() {
	for (int i = 0; i < m_numberOfTransaction; i++) {
		delete m_transactionList[i];
	}
	delete[] m_transactionList;
	m_numberOfTransaction = 0;
}
void Account::clearPersons() {
	for (int i = 0; i < m_totalPersons; i++) {
		delete m_persons[i];
	}
	delete[] m_persons;
	m_totalPersons = 0;
}