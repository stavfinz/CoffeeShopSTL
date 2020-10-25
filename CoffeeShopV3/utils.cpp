#pragma warning(disable : 4996)

using namespace std;
#include <iostream>
#include <ctime>
#include "utils.h"

/// <summary>
/// Checks that a string contains only characters or space
/// </summary>
/// <param name="str">String to check</param>
/// <returns>True if the string contains only characters or a space.</returns>
bool isAlphaOnly(const string& str)
{
	string::const_iterator  it = str.begin();
	string::const_iterator end = str.end();
	for (; it != str.end(); ++it)
	{
		char ch = *it;
		if (!isalpha(ch) && ch != ' ')
		{
			return false;
		}
	}
	return true;
}

/// <summary>
/// Checks that a string contains only digits
/// </summary>
/// <param name="str">String to check</param>
/// <returns>True if the string contains only digit, false otherwise</returns>
bool isDigitsOnly(const string& str)
{
	string::const_iterator  it = str.begin();
	string::const_iterator end = str.end();
	for (; it != str.end(); ++it)
	{
		if (!isdigit(*it))
			return false;
	}
	return true;
}

/// <summary>
/// Clean the input buffer
/// </summary>
void cleanBuffer()
{
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/// <summary>
/// Create Date object with the date of today
/// </summary>
/// <returns>Date object</returns>
Date getTodayDate()
{
	time_t now = time(0);
	tm* dateStruct = localtime(&now);
	return Date(dateStruct->tm_mday, dateStruct->tm_mon + SYSTEM_MONTH_FACTOR, dateStruct->tm_year + SYSTEM_YEAR_FACTOR);
}

/// <summary>
/// Create a date by users input
/// </summary>
/// <returns>Date object</returns>
Date createDate()
{
	int day, month, year;
	cout << "day: " << endl;
	while (!(cin >> day) || day <= 0 || day > 31)
	{
		cleanBuffer();
		cout << "Numbers only, please try again: ";
	}
	cout << "month: " << endl;
	while (!(cin >> month) || month <= 0 || month > 12)
	{
		cleanBuffer();
		cout << "Only numbers between 1-12, please try again: ";
	}
	cout << "year: " << endl;
	while (!(cin >> year) || year < SYSTEM_YEAR_FACTOR)
	{
		cleanBuffer();
		cout << "Only numbers (1900-" << getTodayDate().getYear() << ") , please try again: ";
	}

	return Date(day, month, year);
}