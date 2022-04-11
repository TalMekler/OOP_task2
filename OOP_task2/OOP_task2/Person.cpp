#define _CRT_SECURE_NO_WARNINGS
#include "Person.h"

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
	if (m_name)
		delete[] m_name;
	m_name = new char[strlen(newName) + 1];
	strcpy(m_name, newName);
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