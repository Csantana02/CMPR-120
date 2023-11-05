// Main.cpp
// Christopher Santana
// 11/02/2023
// CMPR
// EXERCISE #7 - Payroll Processing - Files

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const double SOCIAL_SECURITY_TAX = 0.042;
const double MEDICARE_TAX = 0.0145;
const double FEDERAL_TAX_UNDER_1150 = 0.20;
const double FEDERAL_TAX_OVER_1150 = 0.25;
const double FEDERAL_TAX_LIMIT = 1150.0;

int main()
{
	// variable declarations
	string inputFileName;
	string outputFileName;
	ifstream inputFile;
	ofstream outputFile;

	// get the name of the input file from the user
	do
	{
		// prompt the user to enter the file name
		cout << "Enter the name of the input payroll file: " << endl;
		getline(cin, inputFileName);
		cin.ignore(99, '\n');

		// validate the input
		if (inputFileName.length() == 0)
		{
			cout << "Error: File name cannot be empty. Please try again." << endl;
			continue;
		}

		// program is opening the input file
		inputFile.open(inputFileName);
		if (!inputFile)
		{
			cout << "Error: Unable to open the input file. Please try again." << endl;
			continue;
		}

		break; // valid input for the file name
	} while (true);

	// get the name of the output file from the user
	do
	{
		// prompt the user to enter the payroll file
		cout << "Enter the name of the payroll report file: ";
		getline(cin, outputFileName);
		cin.ignore(99, '\n');

		//validate the input
		if (outputFileName.length() == 0)
		{
			cout << "Error: File name cannot be empty. Please try again." << endl;
			continue;
		}

		outputFile.open(outputFileName);
		if (!outputFile)
		{
			cout << "Error: Unable to open the output file. Please try again." << endl;
			continue;
		}

		break; // Valid output file name
	} while (true);

	// program is setting up numerical formating
	cout << setprecision(2) << fixed << showpoint;
	outputFile << setprecision(2) << fixed << showpoint;

	// program is displaying the report headings
	cout << left << setw(10) << "EMPLOYEE ID" << setw(15) << "FIRST NAME";
	cout << setw(15) << "LAST NAME" << right << setw(15) << "GROSS PAY";
	cout << setw(15) << "SOCIAL SECURITY TAX" << setw(10) << "MEDICARE TAX";
	cout << setw(10) << "TOTAL FICA" << setw(10) << "FEDERAL TAX";
	cout << setw(15) << "NET PAY" << endl;

	outputFile << left << setw(10) << "EMPLOYEE ID" << setw(15) << "FIRST NAME";
	outputFile << setw(15) << "LAST NAME" << right << setw(15) << "GROSS PAY";
	outputFile << setw(15) << "SOCIAL SECURITY TAX" << setw(10) << "MEDICARE TAX";
	outputFile << setw(10) << "TOTAL FICA" << setw(10) << "FEDERAL TAX";
	outputFile << setw(15) << "NET PAY" << endl;

	// program is prcoessing the file
	while (true)
	{
		string employeeID;
		string firstName;
		string lastName;
		double hourlyRate;
		double hoursWorked;
		double grossPay;
		double medicareTax;
		double socialSecurityTax;
		double federalTax;
		double totalFICATax;
		double netPay;

		// program is reading a line from the file
		inputFile >> employeeID >> firstName >> lastName >> hourlyRate >> hoursWorked;

		if (inputFile.fail())
		{
			break;
		}

		// calculating gross pay 
		grossPay = (hoursWorked <= 40) ? hourlyRate * hoursWorked : (hourlyRate * 40) + (hourlyRate * 2 * (hoursWorked - 40));

		// calculating the witholding
		socialSecurityTax = grossPay * SOCIAL_SECURITY_TAX;
		medicareTax = grossPay * MEDICARE_TAX;
		totalFICATax = socialSecurityTax + medicareTax;
		federalTax = (grossPay <= FEDERAL_TAX_LIMIT) ? grossPay * FEDERAL_TAX_UNDER_1150 : grossPay * FEDERAL_TAX_OVER_1150;

		// calculating net pay
		netPay = grossPay - totalFICATax;

		// display the results to the console
		cout << left << setw(10) << employeeID << setw(15) << firstName;
		cout << setw(15) << lastName << right << setw(15) << grossPay;
		cout << setw(15) << socialSecurityTax << setw(10) << medicareTax;
		cout << setw(10) << totalFICATax << setw(10) << federalTax;
		cout << setw(15) << netPay << endl;

		// display results to the file 
		outputFile << left << setw(10) << employeeID << setw(15) << firstName;
		outputFile << setw(15) << lastName << right << setw(15) << grossPay;
		outputFile << setw(15) << socialSecurityTax << setw(10) << medicareTax;
		outputFile << setw(10) << totalFICATax << setw(10) << federalTax;
		outputFile << setw(15) << netPay << endl;
	}

	// close the file
	inputFile.close();
	outputFile.close();

	return 0;
}