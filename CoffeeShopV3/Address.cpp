#pragma warning(disable : 4996)

#include "Address.h"
#include "IllegalValue.h"
#include "utils.h"

Address::Address(const string& city, const string& streetName, int streetNumber)
{
	setCity(city);
	setStreetName(streetName);
	setStreetNumber(streetNumber);
}

void Address::setCity(const string& city)
{
	if (city.size() < 2)						//	if the city name is too short
		throw IllegalValue("City is too short.");
	if (!isAlphaOnly(city))						//	if the city name contains non-alphaber characters
		throw IllegalValue("City must be characters only.");

	this->city = city;
}

void Address::setStreetName(const string& street)
{
	if (street.size() < 2)						//	if the street name is too short
		throw IllegalValue("Street name is too short.");
	if (!isAlphaOnly(street))					//	if the street name contains non-alphaber characters
		throw IllegalValue("Street name must be characters only.");

	this->streetName = street;
}

void Address::setStreetNumber(int num)
{
	if (num <= 0)								// street number must be greater than zero
		throw IllegalValue("Street Number");
	this->streetNumber = num;
}

// functions
ostream& operator<<(ostream& os, const Address& address)
{
	os << address.streetName << " " << address.streetNumber << ", " << address.city;
	return os;
}