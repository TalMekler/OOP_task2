/*
	Name: Tal Mekler
	ID: 318811122
*/

#include "Transaction.h"
Transaction::Transaction(Account* s, Account* d, double amount, const char* date) {
	SetSource(s);
	SetDes(d);
	SetAmount(amount);
	SetDate(date);
}
Transaction::Transaction(const Transaction& other) {
	m_source = other.GetSource();
	m_destination = other.GetDes();
	m_amount = other.GetAmount();
	SetDate(other.GetDate());
}
void Transaction::SetSource(Account* src) {
	m_source = src;
}
void Transaction::SetDes(Account* dst) {
	m_destination = dst;
}
void Transaction::SetAmount(double amount) {
	m_amount = amount;
}
void Transaction::SetDate(const char* date) {
	int i;
	m_date = new char[strlen(date) + 1];
	for (i = 0; i < strlen(date); i++) {
		m_date[i] = date[i];
	}
	m_date[i] = '\0';
}
Account* Transaction::GetSource() const {
	return m_source;
}
Account* Transaction::GetDes() const {
	return m_destination;
}
double Transaction::GetAmount() const {
	return m_amount;
}
char* Transaction::GetDate() const {
	return m_date;
}