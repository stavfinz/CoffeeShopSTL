#pragma warning(disable : 4996)

#include <exception>
#include <ctime>
#include "Employee.h"
#include "Date.h"
#include "utils.h"

Employee::Employee(const string& name, const string& phoneNumber, double shiftSalary, const Date& hireDate) : Person(name, phoneNumber), hireDate(hireDate)
{
	if (hireDate > getTodayDate())
		throw exception("Date can not be greater than today.");
	setShiftSalary(shiftSalary);
}

bool Employee::operator<(const Employee& other) const
{
	return this->getSeniority() < other.getSeniority();
}

bool Employee::operator>(const Employee& other) const
{
	return this->getSeniority() > other.getSeniority();
}

void Employee::setShiftSalary(double shiftSalary)
{
	if (shiftSalary <= 0)						//	salary should be greater than zero
		throw exception("Invalid Shift Salary");

	this->shiftSalary = shiftSalary;
}

void Employee::setHireDate(Date& hireDate)
{
	this->hireDate = hireDate;
}

//	calculate a rough estimate of the number of days from hire date to today
int Employee::getSeniority() const
{
	Date today = getTodayDate();

	int num = (today.getYear() - hireDate.getYear()) * 365 +
		(today.getMonth() - hireDate.getMonth()) * 31 +
		(today.getDay() - hireDate.getDay());

	return num;
}

void Employee::toOs(ostream& os) const
{
	os << ", Salary: " << this->getShiftSalary() << ", Seniority: " << this->getSeniority() << ", Hired date: " << this->hireDate;
}