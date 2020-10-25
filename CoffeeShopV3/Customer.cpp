#pragma warning(disable : 4996)

#include "Customer.h"

// ctor
Customer::Customer(const string& name, const string& phoneNumber, bool clubMember) : Person(name, phoneNumber), clubMember(clubMember)
{
}

// setters
void Customer::setClubMember(bool clubMember)
{
	this->clubMember = clubMember;
}

// functions
void Customer::toOs(ostream& os) const
{
	os << (clubMember ? ", a club member" : "");
}