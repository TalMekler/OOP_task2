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

void Account::Withdraw(double amount, const char* date)
{
	Transaction newT(this, this, amount, date);
	AddTransaction(newT);
	m_balance -= amount; // Update the balance
}
void Account::Deposit(double amount, const char* date) {
	Transaction newT(this, this, amount, date);
	AddTransaction(newT);
	m_balance += amount; // Update the balance
}
void Account::AddPerson(const Person& newPerson, double	amount) {
	Person** tmp = new Person * [m_totalPersons + 1];
	int i, flag = 1;
	for (i = 0; i < m_totalPersons; i++) {
		tmp[i] = new Person(*m_persons[i]);
		if (tmp[i]->GetId() == newPerson.GetId() && strcmp(tmp[i]->GetName(), newPerson.GetName()) == 0) {
			// Person in the account
			flag = 0;
		}
	}

	clearPersons();
	if (flag) {
		tmp[i] = new Person(newPerson);
		m_totalPersons++;
		m_persons = new Person * [m_totalPersons];
	}
	for (i = 0; i < m_totalPersons; i++) {
		m_persons[i] = new Person(*tmp[i]);
		delete tmp[i];
	}
	delete[] tmp;
}
void Account::DeletePerson(const Person& oldPerson) {
	Person** tmp = new Person * [m_totalPersons + 1];
	int i, flag = 0;
	for (i = 0; i < m_totalPersons; i++) {
		tmp[i] = new Person(*m_persons[i]);
		if (tmp[i]->GetId() == oldPerson.GetId() && strcmp(tmp[i]->GetName(), oldPerson.GetName()) == 0) {
			flag = 1;
		}
	}
	clearPersons();
	if (flag)
		m_persons = new Person * [m_totalPersons - 1];
	for (i = 0; i < m_totalPersons; i++) {
		if (tmp[i]->GetId() != oldPerson.GetId() && strcmp(tmp[i]->GetName(), oldPerson.GetName()) != 0) {
			m_persons[i] = new Person(*tmp[i]);
			delete tmp[i];
		}
	}
	delete[] tmp;
	if (flag)
		m_totalPersons--;
	if (m_totalPersons == 0)
		delete[] m_persons;
}
void Account::AddTransaction(const Transaction& newTransaction) {
	Transaction** tmp = new Transaction * [m_numberOfTransaction + 1];
	int i;
	// Copy transaction list to tmp list
	for (i = 0; i < m_numberOfTransaction; i++) {
		tmp[i] = new Transaction(*m_transactionList[i]);
	}
	tmp[i] = new Transaction(newTransaction); // add the new transaction
	clearTransactions();
	// Copy the tmp list to the transactionList
	m_numberOfTransaction++;
	m_transactionList = new Transaction * [m_numberOfTransaction];
	for (i = 0; i < m_numberOfTransaction; i++) {
		m_transactionList[i] = new Transaction(*tmp[i]);
		delete tmp[i]; // delete tmp list
	}
	delete[] tmp;
}

void Account::clearTransactions() {
	for (int i = 0; i < m_numberOfTransaction; i++) {
		delete m_transactionList[i];
	}
	delete[] m_transactionList;
}
void Account::clearPersons() {
	for (int i = 0; i < m_totalPersons; i++) {
		delete m_persons[i];
	}
	delete[] m_persons;
}