#pragma once
#include<iostream>
class Date {
	int day;
	int month;
	int year;
public:
	Date(int d, int m, int y) : day(d), month(m), year(y) {}
	bool isValid(); // doda³em tê metodê nie ma jej na diagramie
	int calcDiff(const Date& other){}
};

bool Date::isValid(){
	return (day >= 1 && day <= 31) && (month >= 1 && month <= 12) && (year >= 0);
}

int Date::calcDiff(const Date& other) // tak na testa do poprawy ejszcze trzeba uwzglednic ró¿ne miesiace
{ 	
	if (!isValid() || !other.isValid()) {
		std::cerr << "Invalid date.\n";
		return -1;
	}
	const int daysPerMonth = 30;
	int daysDifference = (other.year - year) * 12 * daysPerMonth +
		(other.month - month) * daysPerMonth +
		(other.day - day);

	return daysDifference;
}

class Payment {
	float due;
	bool accepted;
public:
	virtual void pay() = 0;
};

class PayBlik : public Payment {
	int code;
public:
	void pay() override;
};
void PayBLik::pay() override {
	do
	{
		std::cout << "Paying with Blik. Enter code: ";
		std::cin >> code;

		if (code >= 100000 && code <= 999999)
		{
			std::cout << "Blik payment successful!\n"; // If the Blik code is valid, exit the loop
			break;
		}
		else { std::cout << "Invalid Blik code. Please enter a 6-digit code.\n"; }

	} while (true); // Keep looping until a valid Blik code is entered
}

class PayCard : public Payment {
	int CVV;
	std::string cardNumber;
	Date expiryDate;
public:
	void pay() override;
};

void PayCard::pay() override {
	do {
		sstd::cout << "Paying with Card. Enter card number, CVV, and expiry date: ";
		std::cin >> cardNumber >> CVV >> expiryDate.day >> expiryDate.month >> expiryDate.year;
		int n = cardNumber.size()

			if (n == 16 && (CVV > 99 && CVV < 1000) && expiryDate.isValid())
			{
				std::cout << "Card payment successful!";
				break;
			}

			else { std::cout << "Invalid card data. Please enter new data.\n"; }

	} while (true);
}

class PayTransfer : public Payment {
	int accountNumber;
	std::string subject;
	std::string addres;
public:
	void pay() override;
};

void PayTransfer::pay() override {
	do {
		std::cout << "Paying with Transfer. Enter account number, subject, and address: ";
		std::cin >> accountNumber >> subject >> address;
		// Implement Transfer payment logic
		std::cout << "Transfer payment successful!\n";

	} while (true);
}
