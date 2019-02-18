/*
 Name:		DataOutput.cpp
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#include "pch.h"
#include "DataOutput.h"
#include "eSeries.h"

std::vector<std::string> DataOutput::formatCalculatedValues(float cT, float rSc, float lMin, float cOut, float Ipeak)
{
	std::vector<std::string> calcValues;
	std::stringstream sstr;

	calcValues.push_back("Calculated values:");
	sstr << std::setprecision(3) << "Ct = " << cT << "[F]";
	calcValues.push_back(sstr.str());
	sstr.str(std::string());
	if (Ipeak < 1.5f)
	{
		sstr << "Ipk = " << Ipeak << "[A]";
	}
	else
	{
		sstr << "Ipk = " << Ipeak << "[A]" << " (1.5A MAX ALLOWED)";
	}
	calcValues.push_back(sstr.str());
	sstr.str(std::string());

	sstr << "Rsc = " << rSc << "[Ohm]";
	calcValues.push_back(sstr.str());
	sstr.str(std::string());

	sstr << "Lmin = " << lMin << "[H]";
	calcValues.push_back(sstr.str());
	sstr.str(std::string());

	sstr << "Co = " << cOut << "[F]";
	calcValues.push_back(sstr.str());
	sstr.str(std::string());

	return calcValues;
}

std::vector<std::string> DataOutput::formatRealValues(float cT, float rSc, float lMin, float cOut)
{
	std::vector<std::string> res;
	std::vector<std::string> vals;

	res.push_back("\n");
	res.push_back("Real values for current sense resistor:");
	vals = formatNearestRealValues('R', rSc);
	res.insert(res.end(), vals.begin(), vals.end());
	res.push_back("\n");

	res.push_back("Real values for timing capacitor:");
	vals = formatNearestRealValues('C', cT);
	res.insert(res.end(), vals.begin(), vals.end());
	res.push_back("\n");

	res.push_back("Real values for inductor:");
	vals = formatNearestRealValues('L', lMin);
	res.insert(res.end(), vals.begin(), vals.end());
	res.push_back("\n");

	res.push_back("Real values for output capacitor:");
	vals = formatNearestRealValues('C', cOut);
	res.insert(res.end(), vals.begin(), vals.end());

	return res;
}

std::vector<std::string> DataOutput::getR2value(float r1Value, float vOut)
{
	std::vector<std::string> res;
	std::vector<std::string> vals;
	std::stringstream sstr;

	if (vOut > 0)
	{
		float r2Val = ((abs(vOut) / 1.25f) - 1.0f) * r1Value;
		sstr << std::fixed << std::setprecision(0) << "Calculated R2 value for R1=" << r1Value << "[Ohm]:";
		res.push_back(sstr.str());
		vals = formatNearestRealValues('R', r2Val);
		res.insert(res.end(), vals.begin(), vals.end());
	}
	else
	{
		res.push_back("Vout must be greater than 0!");
	}

	return res;
}

std::vector<std::string> DataOutput::formatNearestRealValues(char componentType, float calculatedValue)
{
	std::string unit;
	std::string prefix = "";
	std::vector<std::string> res;
	std::stringstream sstr;

	if (componentType == 'L') unit = "H";
	else if (componentType == 'C') unit = "F";
	else if (componentType == 'R') unit = "Ohm";

	if (pow(10, 9) > calculatedValue && calculatedValue >= pow(10, 6))// for M
	{
		calculatedValue *= static_cast<float>(pow(10, -6));//multiply value to get rid of decimal places
		prefix = "M";
	}
	else if (pow(10, 6) > calculatedValue && calculatedValue >= pow(10, 3))// for k
	{
		calculatedValue *= static_cast<float>(pow(10, -3));
		prefix = "k";
	}
	else if (1 > calculatedValue && calculatedValue >= pow(10, -3))// for m
	{
		calculatedValue *= static_cast<float>(pow(10, 3));
		prefix = "m";
	}
	else if (pow(10, -3) > calculatedValue && calculatedValue >= pow(10, -6))// u
	{
		calculatedValue *= static_cast<float>(pow(10, 6));
		prefix = "u";
	}
	else if (pow(10, -6) > calculatedValue && calculatedValue >= pow(10, -9))// n
	{
		calculatedValue *= static_cast<float>(pow(10, 9));
		prefix = "n";
	}
	else if (pow(10, -9) > calculatedValue && calculatedValue >= pow(10, -12))// p
	{
		calculatedValue *= static_cast<float>(pow(10, 12));
		prefix = "p";
	}

	sstr << std::fixed << std::setprecision(2) << "Needed value is: " << calculatedValue << "[" << prefix << unit << "]" << std::endl;
	res.push_back(sstr.str());
	res.push_back("All values are in [" + prefix + unit + "]:");
	std::vector<std::string> vals = findClosestValues(calculatedValue);
	res.insert(res.end(), vals.begin(), vals.end());

	return res;
}

std::vector<std::string> DataOutput::findClosestValues(float value)
{
	float divider = 1.0f;
	double closestValue = std::numeric_limits<double>::max();
	double lastClosestValue = std::numeric_limits<double>::max();
	short closestValuePosition = 0;
	short lastClosestValuePosition = 0;

	short valueSeries = 6; //starting val series
	short seriesTolerance = 20;
	short const* currentSeriesArray = nullptr;

	std::vector<std::string> values;
	std::stringstream sstr;
	sstr << std::fixed;

	if (value < 10.0f) divider = 0.01f;  //divide by 100 to change scale of values, to change ranges only divider needs to change
	else if (value < 100.0f) divider = 0.1f;
	else if (value > 10000.0f) divider = 100.0f;
	else if (value > 1000.0f) divider = 10.0f;

	while (valueSeries <= 96)
	{
		switch (valueSeries)
		{
		case 6:
			currentSeriesArray = e6;
			break;
		case 12:
			currentSeriesArray = e12;
			break;
		case 24:
			currentSeriesArray = e24;
			break;
		case 48:
			currentSeriesArray = e48;
			break;
		case 96:
			currentSeriesArray = e96;
			break;
		}

		for (int i = 0; i < valueSeries; i++)
		{
			double tmp = std::abs((static_cast<double>(currentSeriesArray[i]) * divider) - value); //get difference between value from array and calculated

			if (tmp < closestValue)
			{
				lastClosestValue = closestValue; //save latest closest value
				closestValue = tmp; //save new closest value
				lastClosestValuePosition = closestValuePosition; //save position of latest closest value in array
				closestValuePosition = i; //save position of new closest value in array
			}
		}
		sstr << "E" << valueSeries << "(+-" << seriesTolerance << "%) first closest value : " << std::setprecision(2)
			<< (currentSeriesArray[closestValuePosition] * divider) << std::endl << "(" << std::setprecision(1)
			<< ((closestValue / value) * 100) << "% difference from calculated value)" << std::endl;
		if (((lastClosestValue / value) * 100) < 50)//show second value only if difference is less than 50%
		{
			sstr << "E" << valueSeries << "(+-" << seriesTolerance << "%) second closest value: " << std::setprecision(2)
				<< (currentSeriesArray[lastClosestValuePosition] * divider) << std::endl << "(" << std::setprecision(1)
				<< ((lastClosestValue / value) * 100) << "% difference from calculated value)" << std::endl;
		}

		values.push_back(sstr.str());
		sstr.str(std::string());

		valueSeries *= 2;
		seriesTolerance /= 2;
		closestValue = std::numeric_limits<double>::max();
		lastClosestValue = std::numeric_limits<double>::max();
		closestValuePosition = 0;
		lastClosestValuePosition = 0;//reset vars
	}
	return values;
}
