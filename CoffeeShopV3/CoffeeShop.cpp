#pragma warning(disable : 4996)

#include "CoffeeShop.h"
#include "Customer.h"
#include "Employee.h"
#include "Shift.h"
#include "Product.h"
#include "Date.h"
#include "utils.h"
#include "IllegalValue.h"

const int DEFAULT_ARRAY_SIZE = 20;

// ctor
CoffeeShop::CoffeeShop(const string& name, const Address& address) : name(""), address(address), customers()
{
	setName(name);

	this->employees = vector<Employee*>();
	this->employees.reserve(DEFAULT_ARRAY_SIZE);

	this->shifts = vector<Shift*>();
	this->shifts.reserve(DEFAULT_ARRAY_SIZE);

	this->products = vector<Product*>();
	this->products.reserve(DEFAULT_ARRAY_SIZE);
}

CoffeeShop::CoffeeShop(const string& name, Address&& address) : name(""), address(std::move(address)), customers()
{
	setName(name);

	this->employees = vector<Employee*>();
	this->employees.reserve(DEFAULT_ARRAY_SIZE);

	this->shifts = vector<Shift*>();
	this->shifts.reserve(DEFAULT_ARRAY_SIZE);

	this->products = vector<Product*>();
	this->products.reserve(DEFAULT_ARRAY_SIZE);
}

CoffeeShop::CoffeeShop(CoffeeShop&& other) : name(std::move(other.name)), address(std::move(other.address)),
											customers(std::move(other.customers)), employees(NULL), shifts(NULL), products(NULL)
{
	employees = std::move(other.employees);
	shifts = std::move(other.shifts);
	products = std::move(other.products);
}

// dtor
CoffeeShop::~CoffeeShop()
{
	vector<Shift*>::iterator it_shifts = shifts.begin();
	vector<Shift*>::iterator end_shifts = shifts.end();
	for (; it_shifts != end_shifts; ++it_shifts)
	{
		delete* it_shifts;
	}

	vector<Employee*>::iterator it_empl = employees.begin();
	vector<Employee*>::iterator end_empl = employees.end();
	for (; it_empl != end_empl; ++it_empl)
	{
		delete* it_empl;
	}

	vector<Product*>::iterator it_prod = products.begin();
	vector<Product*>::iterator end_prod = products.end();
	for (; it_prod != end_prod; ++it_prod)
	{
		delete* it_prod;
	}
}

// setters
void CoffeeShop::setName(const string& name)
{
	if (name.size() < 2)								//	if name is too short
		throw IllegalValue("Name is too short.");
	if (!isAlphaOnly(name))								//	if name contains non-alphabet characters
		throw IllegalValue("Name should contain characters only.");
	this->name = name;
}

// functions
bool  CoffeeShop::addNewEmployee(const Employee& employee)
{
	if (isEmployeeExists(employee))
		return false;

	employees.push_back(new Employee(employee));				//	copy employee
	return true;
}

bool  CoffeeShop::addNewEmployee(Employee&& employee)
{
	if (isEmployeeExists(employee))
		return false;

	employees.push_back(new Employee(std::move(employee)));		//	move employee
	return true;
}

bool  CoffeeShop::addNewProduct(const Product& product)
{
	if (isProductExists(product))
		return false;

	products.push_back(product.clone());						//	copy product
	return true;
}

bool  CoffeeShop::addNewCustomer(const Customer& customer)
{		
	return customers.add(new Customer(customer));				//	copy customer
}

bool  CoffeeShop::addNewCustomer(Customer&& customer)
{;		
	return customers.add(new Customer(std::move(customer)));	//	move customer
}

bool  CoffeeShop::openShift(double clubDiscountPercent, const Date& date)
{
	if (isShiftExists(date))
		return false;		//	false -> shift already exists with this date

	shifts.push_back(new Shift(clubDiscountPercent, date));		//	create new shift
	return true;
}

Shift* CoffeeShop::getShiftByDate(const Date& date) const
{
	vector<Shift*>::const_iterator it = shifts.begin();
	vector<Shift*>::const_iterator end = shifts.end();
	for (; it != end; ++it)
	{
		const Date* currDate = (*it)->getShiftDate();		//	get current shift's date
		if (date == *currDate)								//	if equals to the desire date
			return *it;										//	return current shift
	}
	return NULL;			//	shift with this date does not exists
}

bool CoffeeShop::isEmployeeExists(const Person& employee) const
{
	vector<Employee*>::const_iterator it = employees.begin();
	vector<Employee*>::const_iterator end = employees.end();
	for (; it != end; ++it)
		if (*(*it) == employee)
			return true;

	return false;
}

bool CoffeeShop::isProductExists(const Product& product) const
{
	vector<Product*>::const_iterator it = products.begin();
	vector<Product*>::const_iterator end = products.end();
	for (; it != end; ++it)
		if (*(*it) == product)
			return true;

	return false;
}

bool CoffeeShop::isShiftExists(const Date& date) const
{
	return (this->getShiftByDate(date) != NULL);
}

ostream& operator<<(ostream& os, const CoffeeShop& coffeeShop)
{
	cout << "Name: " << coffeeShop.getName() << ", Address: " << *coffeeShop.getAddress() << endl;
	cout << endl << "Employees:" << endl;
	if (coffeeShop.getNumEmployees() == 0)
		cout << "No employess." << endl;
	printVector(coffeeShop.getEmployees());

	cout << endl << "Products:" << endl;
	if (coffeeShop.getNumProducts() == 0)
		cout << "No products." << endl;
	printVector(coffeeShop.getProducts());

	cout << endl << "Customers:" << endl;
	if (coffeeShop.getNumCustomers() == 0)
		cout << "No customers." << endl;
	cout << coffeeShop.getCustomers() << endl;


	cout << endl << "Shifts:" << endl;
	if (coffeeShop.getNumShifts() == 0)
		cout << "No shifts." << endl;
	printVector(coffeeShop.getShifts());

	return os;
}