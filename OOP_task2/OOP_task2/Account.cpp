#include "Account.h"

Account::Account(Person** persons, int count, double balance) {
	m_persons = new Person * [count];
	m_totalPersons = count;
	m_balance = balance;
	for (int i = 0; i < count; i++) {
		m_persons[i] = new Person(*persons[i]);
	}
}
Account::Account(const Person& person, double balance) {
	m_totalPersons = 1;
	m_balance = balance;
	m_persons = new Person * [1];
	m_persons[0] = new Person(person);
}
Account::Account(const Account& other);
Account::~Account();

void Account::SetPersons(Person** persons, int count);
void Account::SetAccountNumber(int number);
void Account::SetBalance(double balance);
void Account::SetTransactions(Transaction** newTransaction, int count);
Transaction** Account::GetTransactions();
int	Account::GetNumOfTransactions();
Person** Account::GetPersons() const;
int	Account::GetTotalPersons()const;
int	Account::GetAccountNumber() const;
double Account::GetBalance() const;

void Account::Withdraw(double amount, const char* date);
void Account::Deposit(double amount, const char* date);
void Account::AddPerson(const Person& newPerson, double	amount);
void Account::DeletePerson(const Person& oldPerson);
void Account::AddTransaction(const Transaction& newTransaction);

void Account::clearTransactions();
void Account::clearPersons();