#ifndef __PERSON_H__
#define __PERSON_H__

using namespace std;
#include <iostream>

class Person {
protected:
	string name;
	string phoneNumber;

	//Person(const Person& other);
	//Person(Person&& other);

	//const Person& operator=(const Person& other);
	//const Person& operator=(Person&& other);

private:
	void setName(const string& name) noexcept(false);

public:
	// ctor
	Person(const string& name, const string& phoneNumber) noexcept(false);

	// dtor
	virtual ~Person();

	// operators
	virtual bool operator==(const Person& other) const;

	// getters
	const string& getName() const { return name; }
	const string& getPhoneNumber() const { return phoneNumber; }

	// setters
	void setPhoneNumber(const string& phoneNumber) noexcept(false);

	// functions
	virtual void toOs(ostream& os) const = 0;
	friend ostream& operator<<(ostream& os, const Person& person);
};

#endif