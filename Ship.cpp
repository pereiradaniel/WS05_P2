#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Ship.h"

using namespace std;

namespace sdds {
	Ship::Ship()
	{
		m_type[0] = '\0';
		m_engCnt = 0;
		m_engines = nullptr;
	}

	Ship::Ship(const char* type, const Engine engines[], int cnt)
	{
		bool valid = type != nullptr && engines != nullptr && cnt > 0;
		if (valid)
		{
			// Set data members for current object:
			strcpy(m_type, type);
			m_engCnt = cnt;

			// Allocate dynamic memory:
			m_engines = new Engine[cnt];

			// Assign engines to the current object:
			for (int i = 0; i < cnt; i++)
			{
				m_engines[i] = engines[i];
			}
		}
		else
		{
			// Set default state:
			m_type[0] = '\0';
			m_engCnt = 0;
			m_engines = nullptr;
		}
	}

	Ship::operator bool() const
	{
		bool valid = true;

		if (m_type[0] == '\0' && m_engCnt == 0)
		{
			valid = false;
		}

		return valid;
	}

	bool Ship::operator<(double power) const
	{
		bool under_power = false;

		if (calculatePower() < power) {
			under_power = true;
		}

		return under_power;

	}

	double Ship::calculatePower() const {
		double total_power = 0;

		// Iterate through Ship's engines and add to total_power:
		for (int i = 0; i < m_engCnt; i++) {
			total_power += (double)((double)m_engines[i].get() * (double)5);
		}

		return total_power;
	}


	void Ship::display() const {
		if (*this) {
			// Display engines:
			cout << m_type << " - " << calculatePower() << endl;
			for (int i = 0; i < m_engCnt; i++) {
				m_engines[i].display();
			}
		}
		else
		{
			// Display message if no engine:
			cout << "No available data" << endl;
		}
	}

	Ship& Ship::operator+=(Engine engine) {
		// Check if engine count more than 0:
		if (m_engCnt > 0) {

			// Check if Ship is valid:
			if (m_type[0] == '\0')
			{
				cout << "The object is not valid! Engine cannot be added!" << endl;
			}
			else {
				// If engine is valid, create temp_engines to back up m_engines;
				
				Engine* temp_engines = new Engine[m_engCnt + 1];
				// Stuff m_engines into temp_engines:
				for (int i = 0; i < m_engCnt; i++)
				{
					temp_engines[i] = m_engines[i];
				}
				
				// Increase engine count:
				m_engCnt++;

				// Add the new engine:
				temp_engines[m_engCnt] = engine;

				// Re-allocate memory to m_engines:
				if (m_engines != nullptr)
				{
					delete[] m_engines;
					m_engines = new Engine[m_engCnt];
				}
				// Rebuild m_engines using temp_engines:
				for (int i = 0; i < m_engCnt; i++)
				{
					m_engines[i] = temp_engines[i];
				}

				delete[] temp_engines;
			}
		}

		return *this;
	}

	bool operator<(double power, const Ship& ship)
	{
		bool under_powered = false;

		if (ship.calculatePower() > power) {
			under_powered = true;
		}

		return under_powered;
	}


}