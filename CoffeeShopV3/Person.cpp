#pragma warning(disable : 4996)

#include <exception>
#include "Person.h"
#include "utils.h"

// ctor
Person::Person(const string& name, const string& phoneNumber) : name(""), phoneNumber("")
{
	setName(name);
	setPhoneNumber(phoneNumber);
}

// operators
bool Person::operator==(const Person& other) const
{
	return (name == other.name) && (phoneNumber == other.phoneNumber);		//	return true if both equals, false otherwise
}

void Person::setName(const string& name)
{
	if (name.size() < 2)						//	if the name is too short
		throw exception("Name should be at least 2 characters.");
	if (!isAlphaOnly(name))						//	if the name contains non-alphabetic characters
		throw exception("Name should be characters only.");

	this->name = name;
	this->name[0] = toupper(name[0]);			//	upper case the first letter
}


void Person::setPhoneNumber(const string& phoneNumber)
{
	if (phoneNumber.size() < 9)				//	if phone number is too short
		throw exception("Phone Number should contain at least 9 digits");
	if (!isDigitsOnly(phoneNumber))				//	if phone number contains non-digits characters
		throw exception("Phone Number");

	this->phoneNumber = phoneNumber;
}

ostream& operator<<(ostream& os, const Person& person)
{
	os << person.name << ", " << person.phoneNumber;
	person.toOs(os);
	return os;
}