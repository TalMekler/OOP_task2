/*
	Name: Tal Mekler
	ID: 318811122
*/

#include "Account.h"

Account::Account() {
	m_transactionList = NULL;
	m_numberOfTransaction = 0;
	m_persons = NULL;
	m_totalPersons = 0;
	m_accountNumber = 0;
	m_balance = 0;
}

Account::Account(Person** persons, int count, double balance) {
	// Ctor - list of persons
	m_balance = balance;
	SetPersons(persons, count);
	m_transactionList = nullptr;
	m_numberOfTransaction = 0;
	m_accountNumber = 0;
	for (int i = 0; i < m_totalPersons; i++) {
		m_accountNumber += m_persons[i]->GetId();
	}
}
Account::Account(const Person& person, double balance) {
	// Ctor - 1 person
	m_totalPersons = 1;
	m_balance = balance;
	m_persons = new Person * [1];
	m_persons[0] = new Person(person);
	m_transactionList = nullptr;
	m_numberOfTransaction = 0;
	m_accountNumber = 0;
	for (int i = 0; i < m_totalPersons; i++) {
		m_accountNumber += m_persons[i]->GetId();
	}
}
Account::Account(const Account& other) {
	// Copy Ctor
	if (other.m_transactionList)
		SetTransactions(other.m_transactionList, other.m_numberOfTransaction);
	if (other.m_persons)
		SetPersons(other.m_persons, other.m_totalPersons);
	m_accountNumber = other.m_accountNumber;
	m_balance = other.m_balance;
}
Account::~Account() {
	for (int i = 0; i < m_numberOfTransaction; i++) {
		delete[] m_transactionList[i]->GetDate();
	}
	//delete[] m_transactionList;
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
	for (int i = 0; i < m_totalPersons; i++) {
		if (newPerson.GetId() == m_persons[i]->GetId())
			return; // newPerson exist in the account -> Do NOTHING
	}

	// newPerson isn't in the account -> Add him
	Person** tmp = new Person * [m_totalPersons + 1];
	int i;
	for (i = 0; i < m_totalPersons; i++) {
		tmp[i] = new Person(*m_persons[i]);
	}
	tmp[i] = new Person(newPerson);
	clearPersons();
	m_totalPersons++;
	m_balance += amount;
	m_persons = tmp; // tmp point to DMA
}
void Account::DeletePerson(const Person& oldPerson) {
	int flag = 0;
	for (int i = 0; i < m_totalPersons; i++) {
		if (oldPerson.GetId() == m_persons[i]->GetId()) {
			// oldPerson in the bank
			flag = 1;
			break;
		}
	}
	if (!flag) return; // Person not in the bank -> Do NOTHING

	// Person in the bank - delete him
	Person** tmp = new Person * [m_totalPersons - 1];
	int i, j;
	for (i = 0, j = 0; i < m_totalPersons; i++) {
		if (oldPerson.GetId() != m_persons[i]->GetId()) {
			// Copy person to tmp arr if this isn't the person we want to delete
			tmp[j] = new Person(*m_persons[i]);
			j++;
		}
	}
	clearPersons();
	m_totalPersons--;
	m_persons = tmp;
}
void Account::AddTransaction(const Transaction& newTransaction) {
	int i;
	Transaction** tmp = new Transaction * [newTransaction.GetSource()->GetNumOfTransactions() + 1];
	for (i = 0; i < newTransaction.GetSource()->GetNumOfTransactions(); i++) {
		tmp[i] = new Transaction(*newTransaction.GetSource()->GetTransactions()[i]);
	}
	tmp[i] = new Transaction(newTransaction); // add the new transaction
	newTransaction.GetSource()->clearTransactions();
	newTransaction.GetSource()->SetTransactions(tmp, newTransaction.GetSource()->GetNumOfTransactions() + 1);
	for (i = 0; i < m_numberOfTransaction; i++) {
		m_transactionList[i] = new Transaction(*tmp[i]);
		delete tmp[i]; // delete tmp list
	}
	delete[] tmp;

	// If source and destination are different add -> Add the transaction to the destination account
	if (newTransaction.GetDes() != newTransaction.GetSource()) {
		tmp = new Transaction * [newTransaction.GetDes()->GetNumOfTransactions() + 1];
		for (i = 0; i < newTransaction.GetDes()->GetNumOfTransactions(); i++) {
			tmp[i] = new Transaction(*newTransaction.GetDes()->GetTransactions()[i]);
		}
		tmp[i] = new Transaction(newTransaction); // add the new transaction
		newTransaction.GetDes()->clearTransactions();
		newTransaction.GetDes()->SetTransactions(tmp, newTransaction.GetDes()->GetNumOfTransactions() + 1);
		for (i = 0; i < m_numberOfTransaction; i++) {
			m_transactionList[i] = new Transaction(*tmp[i]);
			delete tmp[i]; // delete tmp list
		}
		delete[] tmp;
	}
	newTransaction.GetSource()->SetBalance(newTransaction.GetSource()->GetBalance() - newTransaction.GetAmount());
	newTransaction.GetDes()->SetBalance(newTransaction.GetDes()->GetBalance() + newTransaction.GetAmount());
}

void Account::clearTransactions() {
	for (int i = 0; i < m_numberOfTransaction; i++) {
		delete[] m_transactionList[i]->GetDate();
	}
	delete[] m_transactionList;
}
void Account::clearPersons() {
	if (m_totalPersons > 0) {
		for (int i = 0; i < m_totalPersons; i++) {
			delete m_persons[i];
		}
		delete[] m_persons;
	}
}