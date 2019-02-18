/*
 Name:		MC34063AComponentsCalculator.cpp
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#include "pch.h"
#include "MC34063AComponentsCalculator.h"
#include "DataOutput.h"
#include "Mc34063aStepUp.h"
#include "Mc34063aStepDown.h"
#include "Mc34063aInverting.h"

int main(int argc, char** argv)
{
	short selectedOption = 0;

	std::cout << "MC34063A components calculator v1.0" << std::endl;
	std::cout << "Calculates component values for switching regulator based on MC34063A." << std::endl;
	std::cout << "(c) 2016-2019 Wojciech Cybowski. All rights reserved." << std::endl;

	while (true)
	{
		std::cout << "Select option:" << std::endl << "1. Help" << std::endl
			<< "2. Calculate components" << std::endl << "3. Calculate R2 current sense resistor" << std::endl << "4. Exit" << std::endl;
		std::cin >> selectedOption; //read one char and check if valid
		switch (selectedOption)
		{
		case 1://help
			help();
			break;
		case 2://components
			clearInput();
			componentCalculations();
			break;
		case 3://r2
			clearInput();
			r2Calculations();
			break;
		case 4://exit
			return 0;
		default:
			std::cout << "No such option." << std::endl;
		}
	}
	return 0;
}

void clearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::vector<std::string> parseInput(std::string inputData)
{
	std::vector<std::string> res;
	size_t pos = 0;

	while ((pos = inputData.find(" ")) != std::string::npos)
	{
		res.push_back(inputData.substr(0, pos));
		inputData.erase(0, pos + 1);//+1 to remove space delimiter
	}
	res.push_back(inputData);
	return res;
}

std::vector<float> convertToFloat(std::vector<std::string> inputData)
{
	std::vector<float> res;
	try
	{
		for (std::string f : inputData)
		{
			res.push_back(std::stof(f, nullptr));
		}
	}
	catch (...)//in case something went wrong
	{
		return std::vector<float>();//return empty list
	}
	return res;
}

void help(void)
{
	std::cout << "Option 2:" << std::endl;
	std::cout << "Performs calculation of needed component values, based on input values in following order:" << std::endl <<
		"Vf - Forward voltage drop of the output rectifier diode[V]" << std::endl <<
		"Vsat - Saturation voltage of switching transistor" << std::endl <<
		"Vin - Nominal input voltage[V]" << std::endl <<
		"VinMin - Minimum input voltage[V]" << std::endl <<
		"Vout - Desired output voltage[V]" << std::endl <<
		"Iout - Desired output current[A]" << std::endl <<
		"fmin - Minimum desired output switching frequency at the selected values of Vin and Io(Hz)" << std::endl <<
		"Vripple - Desired peak - to - peak output ripple voltage[V]" << std::endl <<
		"RegType - 1 - Step-up, 2 - Step-down, 3 - Inverting" << std::endl << std::endl <<
		"Example: 0.4 0.7 5 4.5 15 0.1 100000 0.1 1" << std::endl << std::endl;

	std::cout << "Option 3:" << std::endl;
	std::cout << "Finds needed R2 value, based on given R1 and Vout" << std::endl << std::endl <<
		"Example: 10000 15.5" << std::endl << std::endl;
}

void componentCalculations(void)
{
	std::string data;

	std::cout << "Enter parameters: ";
	std::getline(std::cin, data);
	std::vector<float> parsedData = convertToFloat(parseInput(data));

	if (parsedData.size() != 9) { std::cout << "Wrong parameters." << std::endl << std::endl; return; }

	Mc34063a* mc = nullptr;
	if (parsedData[8] == 1)
	{
		mc = new Mc34063aStepUp(parsedData[0], parsedData[1], parsedData[2], parsedData[3],
			parsedData[4], parsedData[5], parsedData[6], parsedData[7]);
	}
	else if (parsedData[8] == 2)
	{
		mc = new Mc34063aStepDown(parsedData[0], parsedData[1], parsedData[2], parsedData[3],
			parsedData[4], parsedData[5], parsedData[6], parsedData[7]);
	}
	else if (parsedData[8] == 3)
	{
		mc = new Mc34063aInverting(parsedData[0], parsedData[1], parsedData[2], parsedData[3],
			parsedData[4], parsedData[5], parsedData[6], parsedData[7]);
	}
	else { std::cout << "Wrong type of switching regulator." << std::endl << std::endl; return; }

	std::vector<float> calculatedComponents = mc->calculateComponentsValues();
	for (std::string s : DataOutput::formatCalculatedValues(calculatedComponents[0], calculatedComponents[1], calculatedComponents[2],
		calculatedComponents[3], calculatedComponents[4]))
	{
		std::cout << s << std::endl;
	}

	for (std::string s : DataOutput::formatRealValues(calculatedComponents[0], calculatedComponents[1], calculatedComponents[2], calculatedComponents[3]))
	{
		std::cout << s << std::endl;
	}
	delete mc;
}

void r2Calculations(void)
{
	std::string data;

	std::cout << "Enter parameters for R2 calculation: ";
	std::getline(std::cin, data);
	std::vector<float> parsedData = convertToFloat(parseInput(data));

	if (parsedData.size() != 2) { std::cout << "Wrong parameters." << std::endl << std::endl; return; }

	for (std::string s : DataOutput::getR2value(parsedData[0], parsedData[1]))
	{
		std::cout << s << std::endl;
	}
}
