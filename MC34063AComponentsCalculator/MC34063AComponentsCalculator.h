/*
 Name:		MC34063AComponentsCalculator.h
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#pragma once

/// <summary>
/// Clears stdin.
/// </summary>
void clearInput(void);

/// <summary>
/// Parses input data by splitting string on spaces.
/// </summary>
std::vector<std::string> parseInput(std::string inputData);

/// <summary>
/// Converts vector of strings to vector of floats.
/// </summary>
std::vector<float> convertToFloat(std::vector<std::string> inputData);

/// <summary>
/// Shows help.
/// </summary>
void help(void);

/// <summary>
/// Calculates component values and displays them.
/// </summary>
void componentCalculations(void);

/// <summary>
/// Calculates R2 value and displays it.
/// </summary>
void r2Calculations(void);