#pragma warning(disable : 4996)

#include "Order.h"
#include "Product.h"
#include "Employee.h"
#include "Customer.h"
#include "utils.h"

const int DEFAULT_ARRAY_SIZE = 20;

Order::Order(const Employee& employee, const Customer& customer) : employee(employee), customer(customer)
{
	items = vector<Product*>();
	items.reserve(DEFAULT_ARRAY_SIZE);
}

Order::Order(const Order& other) : employee(other.employee), customer(other.customer)
{
	*this = other;
}

Order::~Order()
{
	vector<Product*>::iterator it = items.begin();
	vector<Product*>::iterator end = items.end();

	for (; it != end; ++it)
	{
		delete* it;
	}
}

const Order& Order::operator=(const Order& other)
{
	if (this != &other)
	{
		vector<Product*>::const_iterator it = items.begin();
		vector<Product*>::const_iterator end = items.end();

		for (; it != end; ++it)
		{
			delete* it;
		}

		items = vector<Product*>();
		items.reserve(DEFAULT_ARRAY_SIZE);

		for (int i = 0; i < other.getNumItems(); i++)	//	iterate over the other order array and copy it's items
		{
			*this += other[i];
		}
	}
	return *this;
}

//	add an item to the order
Order& Order::operator+=(const Product& product)
{
	addItem(product);
	return *this;
}

bool Order::addItem(const Product& product)
{
	//if (numItems == itemsMaxSize)			//	if the array is full -> double it's size
	//{
	//	itemsMaxSize *= 2;
	//	Product** tempArr = new Product * [itemsMaxSize];
	//	memcpy(tempArr, items, numItems * sizeof(Product*));
	//	std::swap(tempArr, items);
	//	delete[] tempArr;
	//}
	//items[numItems++] = product.clone();	//	copy the product into the array

	items.push_back(product.clone());
	return true;
}

int Order::getTotalCalories() const
{
	int totalCalories = 0;

	vector<Product*>::const_iterator it = items.begin();
	vector<Product*>::const_iterator end = items.end();

	for (; it != end; ++it)
		totalCalories += (*it)->getCalories();

	return totalCalories;
}

double Order::getOrderProfit() const
{
	double sumProfit = 0;

	vector<Product*>::const_iterator it = items.begin();
	vector<Product*>::const_iterator end = items.end();

	for (; it != end; ++it)
		sumProfit += ((*it)->getPrice() - (*it)->getCost());

	return sumProfit;
}

ostream& operator<<(ostream& os, const Order& order)
{
	os << "Employee: " << order.getEmployee().getName()
		<< ", Customer: " << order.getCustomer().getName()
		<< ", Number of products: " << order.getNumItems()
		<< ", Profit: " << order.getOrderProfit();
	return os;
}