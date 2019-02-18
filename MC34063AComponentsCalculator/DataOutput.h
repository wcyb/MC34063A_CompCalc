/*
 Name:		DataOutput.h
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#pragma once
#include "pch.h"

class DataOutput final
{
public:
	/// <summary>
	/// Prints calculated values of components
	/// </summary>
	/// <param name="cT">Timing capacitor</param>
	/// <param name="rSc">Sense resistor</param>
	/// <param name="lMin">Inductor</param>
	/// <param name="cOut">Filter capacitor</param>
	/// <param name="Ipeak">Peak switching current</param>
	/// <returns>Output formated as strings vector with all calculated values</returns>
	static std::vector<std::string> formatCalculatedValues(float cT, float rSc, float lMin, float cOut, float Ipeak);

	/// <summary>
	/// Prints real values of components from E series.
	/// </summary>
	/// <param name="cT">Timing capacitor</param>
	/// <param name="rSc">Sense resistor</param>
	/// <param name="lMin">Inductor</param>
	/// <param name="cOut">Filter capacitor</param>
	/// <returns>Output formated as strings vector with all components values</returns>
	static std::vector<std::string> formatRealValues(float cT, float rSc, float lMin, float cOut);

	/// <summary>
	/// Calculates R2 value based on given R1 for voltage reference
	/// </summary>
	/// <param name="r1Value">Value of R1 resistor</param>
	/// <param name="vOut">Output voltage</param>
	/// <returns>Returns calculated and closest real values</returns>
	static std::vector<std::string> getR2value(float r1Value, float vOut);

private:
	/// <summary>
	/// Prints real values of components (R,L,C) that can be found in E series
	/// </summary>
	/// <param name="componentType">R,L or C</param>
	/// <param name="calculatedValue">calculated value of component</param>
	/// <returns>Output formated as strings vector with given component values</returns>
	static std::vector<std::string> formatNearestRealValues(char componentType, float calculatedValue);

	/// <summary>
	/// Finds two closest values in E series to given value
	/// </summary>
	/// <param name="value">needed value</param>
	/// <returns>Output formated as strings vector with two nearest values from E series</returns>
	static std::vector<std::string> findClosestValues(float value);

private:
	DataOutput() {}
	DataOutput(DataOutput& dat) {}
	DataOutput& operator=(DataOutput& dat) {}
};

