#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include "Date.h"

static const int SYSTEM_YEAR_FACTOR = 1900;
static const int SYSTEM_MONTH_FACTOR = 1;

bool isAlphaOnly(const string& str);

bool isDigitsOnly(const string& str);

void cleanBuffer();

Date getTodayDate();

Date createDate() noexcept(false);

template <class T>
void printVector(const vector<T>& vec)
{
	auto it = vec.begin();
	auto end = vec.end();
	int i = 1;
	for (; it != end; ++it, i++)
		cout << "\t" << i << ". " << *(*it) << endl;
}

#endif // !__UTILS_H__