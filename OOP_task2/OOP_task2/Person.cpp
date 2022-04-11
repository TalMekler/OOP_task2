#include "Person.h"

Person::Person(){
	m_name = nullptr;
	m_id = 0;
}

Person::Person(const char* name, int id) {
	m_id = id;
	SetName(name);
}
Person::Person(const Person& other) {
	m_id = other.m_id;
	SetName(other.m_name);
}
Person::~Person() {
	delete[] m_name;
}

void Person::SetName(const char* newName) {
	int i;
	m_name = new char[strlen(newName) + 1];
	for (i = 0; i < strlen(newName); i++) {
		m_name[i] = newName[i];
	}
	m_name[i] = '\0';
}
void Person::SetId(int newId) {
	m_id = newId;
}
char* Person::GetName() const {
	return m_name;
}
int Person::GetId() const {
	return m_id;
}