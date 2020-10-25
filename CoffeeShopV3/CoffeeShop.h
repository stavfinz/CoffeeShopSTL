#ifndef __COFFEESHOP_H__
#define __COFFEESHOP_H__

#include <iostream>
#include <vector>
using namespace std;

#include "Address.h"
class Person;
class Customer;
class Employee;
class Shift;
class Product;
class Date;

class CoffeeShop {
private:
	string name;
	Address address;

	vector<Customer*> customers;
	vector<Employee*> employees;
	vector<Shift*> shifts;
	vector<Product*> products;

public:
	// ctor
	CoffeeShop(const string& name, const Address& address) noexcept(false);

	// copy ctor
	CoffeeShop(const CoffeeShop& other) = delete;

	// move ctor
	CoffeeShop(CoffeeShop&& other);
	CoffeeShop(const string& name, Address&& address);

	// assignment operator
	const CoffeeShop& operator=(const CoffeeShop& other) = delete;
	// move assignment operator
	const CoffeeShop& operator=(CoffeeShop&& other) = delete;
	// dtor
	~CoffeeShop();

	// getters
	const string& getName() const { return name; }
	int getNumCustomers() const { return customers.size(); }
	int getNumEmployees() const { return employees.size(); }
	int getNumShifts() const { return shifts.size(); }
	int getNumProducts() const { return products.size(); }
	const Address* getAddress() const { return &address; }
	const vector<Customer*> getCustomers() const { return customers; }
	const vector<Employee*> getEmployees() const { return employees; }
	const vector<Shift*> getShifts() const { return shifts; }
	const vector<Product*> getProducts() const { return products; }

	// setters
	void setName(const string& name) noexcept(false);

	// functions
	bool addNewEmployee(const Employee& employee);
	bool addNewEmployee(Employee&& employee);
	bool addNewProduct(const Product& product);
	bool addNewCustomer(const Customer& customer);
	bool addNewCustomer(Customer&& customer);
	bool openShift(double clubDiscountPercent, const Date& date);
	Shift* getShiftByDate(const Date& date) const;
	friend ostream& operator<<(ostream& os, const CoffeeShop& coffeeShop);

	bool isEmployeeExists(const Person& employee) const;
	bool isCustomerExists(const Person& employee) const;
	bool isProductExists(const Product& product) const;
	bool isShiftExists(const Date& date) const;
};

#endif