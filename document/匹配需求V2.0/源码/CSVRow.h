#pragma once
#ifndef CSVROW_H
#define CSVROW_H
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVRow
{
public:
	std::string const& operator[](std::size_t index) const
	{
		return m_data[index];
	}
	std::size_t size() const
	{
		return m_data.size();
	}
	std::istream& readNextRow(std::istream& str)
	{
		std::string         line;
		std::getline(str, line);
		std::stringstream   lineStream(line);
		std::string         cell;
		m_data.clear();
		while (std::getline(lineStream, cell, ','))
		{
			m_data.push_back(cell);
		}
		// This checks for a trailing comma with no data after it.
		if (!lineStream && cell.empty())
		{
			// If there was a trailing comma then add an empty element.
			m_data.push_back("");
		}
		return str;
	}
private:
	std::vector<std::string> m_data;
};

#endif // !CSVROW_H

