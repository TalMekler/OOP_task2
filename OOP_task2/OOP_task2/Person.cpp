#include "Person.h"

Person::Person(const char* name, int id) {
	m_id = id;
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);
}
Person::Person(const Person& other);
Person::~Person();



void Person::SetName(const char* newName);
void Person::SetId(int newId);
char* Person::GetName() const;
int Person::GetId() const;