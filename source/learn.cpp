#include <iostream>
#include <string>
#include <vector>

void learn() {
	std::ios_base::sync_with_stdio(false);
		// Create a vector containing integers
	std::vector<std::string> v = {"7", "5", "16", "8"};

		// Add two more integers to vector
	v.push_back("25");
	v.push_back("13");

		// Iterate and print values of vector
	for (auto &i : v) {
		std::cout << i << std::endl;
	}

	int var = 15;
	int *pVar = &var;
	const char *str = "Hello there!"; // When using C
	std::string strCpp = "Hello there!"; // When using C++
	std::string *pStrCpp = &strCpp;

	std::cout << "Value of str                       = " << str << std::endl;
	std::cout << "Address of str                     = " << &str << std::endl;

	std::cout << "Value of strCpp                    = " << strCpp << std::endl;
	std::cout << "pStrCpp points to strCpp's address = " << pStrCpp << std::endl;
	std::cout << "*pStrCpp points to strCpp's value  = " << *pStrCpp << std::endl;
	std::cout << "Address of strCpp                  = " << &strCpp << std::endl;
	std::cout << "Address of pStrCpp                 = " << &pStrCpp << std::endl;

	std::cout << "Value of var                       = " << var << std::endl;
	std::cout << "pVar points to var's address       = " << pVar << std::endl;
	std::cout << "*pVar points to var's value        = " << *pVar << std::endl;
	std::cout << "Address of var                     = " << &var << std::endl;
	std::cout << "Address of pVar                    = " << &pVar << std::endl;

	std::ios_base::sync_with_stdio(true);
}
