#pragma warning(disable : 4996)

#include "Shift.h"
#include "Employee.h"
#include "Customer.h"
#include "Order.h"
#include "Product.h"
#include "utils.h"
#include "IllegalValue.h"

const int DEFAULT_ITEMS_SIZE = 10;
const int DEFUALT_EMPLOYEES_SIZE = 5;
const int DEFAULT_ORDERS_SIZE = 50;

Shift::Shift(double clubDiscountPercent, const Date& shiftDate) :shiftDate(shiftDate)
{
	setClubDiscountPercent(clubDiscountPercent);

	dailyMenu = vector<Product*>();
	dailyMenu.reserve(DEFAULT_ITEMS_SIZE);

	employees = vector<const Employee*>();
	employees.reserve(DEFUALT_EMPLOYEES_SIZE);

	orders = vector<Order*>();
	orders.reserve(DEFAULT_ORDERS_SIZE);
}

Shift::~Shift()
{
	vector<Product*>::iterator it_prod = dailyMenu.begin();
	vector<Product*>::iterator end_prod = dailyMenu.end();

	for (; it_prod != end_prod; ++it_prod)
	{
		delete* it_prod;
	}

	vector<Order*>::iterator it_orders = orders.begin();
	vector<Order*>::iterator end_orders = orders.end();

	for (; it_orders != end_orders; ++it_orders)
	{
		delete* it_orders;
	}

	//delete[] employees;
}

void Shift::setClubDiscountPercent(double clubDiscountPercent)
{
	if (clubDiscountPercent < 0 || clubDiscountPercent > 100)	//	discount should be between 0 to 100
		throw IllegalValue("Illegal discount precentage.");
	this->clubDiscountPercent = clubDiscountPercent;
}

bool Shift::isProductExists(const Product& product) const
{
	/*vector<const Product*>::const_iterator found = find(dailyMenu.begin(), dailyMenu.end(), product);
	return (found != dailyMenu.end());*/

	vector<Product*>::const_iterator it = dailyMenu.begin();
	vector<Product*>::const_iterator end = dailyMenu.end();
	for (; it != end; ++it)
		if (*(*it) == product)
			return true;

	return false;
}

bool Shift::isEmployeeExists(const Person& employee) const
{
	/*vector<const Employee* >::const_iterator found = find(employees.begin(), employees.end(), employee);
	return (found != employees.end());*/

	vector<const Employee*>::const_iterator it = employees.begin();
	vector<const Employee*>::const_iterator end = employees.end();
	for (; it != end; ++it)
		if (*(*it) == employee)
			return true;

	return false;
}

bool Shift::addProductToMenu(const Product& product)
{
	if (isProductExists(product))
		return false;

	dailyMenu.push_back(product.clone());		//	clone the product
	return true;
}

bool Shift::addEmployeeToShift(const Employee& employee)
{
	if (isEmployeeExists(employee))
		return false;

	employees.push_back(&employee);				//	save pointer to the employee
	return true;
}

void Shift::addOrder(const Order& order)
{
	orders.push_back(new Order(order));				//	copy order into the array
}

//	iterate over the employee's array and find the one with the greatest seniority
const Employee* Shift::getShiftManager() const
{														
	int maxSeniorty = 0;
	const Employee* shiftManager = nullptr;

	vector<const Employee*>::const_iterator it = employees.begin();
	vector<const Employee*>::const_iterator end = employees.end();

	for (; it != end; ++it)									//	iterate over the employees array
	{				
		int currSeniority = (*it)->getSeniority();			//	calculate current employee's seniority
		if (currSeniority > maxSeniorty)					//	if greater than the max -> save it, and the employee
		{
			maxSeniorty = currSeniority;
			shiftManager = *it;
		}
	}
	return shiftManager;									//	return employee with greatest seniority
}

double Shift::getShiftProfit() const
{
	double profitSum = 0;
	double temp = 0;

	vector<Order*>::const_iterator it = orders.begin();
	vector<Order*>::const_iterator end = orders.end();

	for (; it != end; ++it)									//	iterate over the orders 				
	{
		temp = (*it)->getOrderProfit();						//	get the profit of the current order

		if ((*it)->getCustomer().isClubMember())				//	if the customer of the order is a club member, he got a discount
			temp *= (1 - (clubDiscountPercent / 100));		//	reduce profit with the discount
		profitSum += temp;
	}
	return profitSum;
}

ostream& operator<<(ostream& os, const Shift& shift)
{
	os << "Shift Date: " << *shift.getShiftDate() << ", Profit: " << shift.getShiftProfit();
	return os;
}