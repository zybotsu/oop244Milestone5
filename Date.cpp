// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include<iostream>
#include<iomanip>
#include "Date.h"

using namespace std;

namespace sict {



	Date::Date() {

		

		 this->year =0;
	     this->month =0;
		 this->day = 0;
		 this->comparativeValue = 0;



		errCode(NO_ERROR);
		
	}

	Date::Date( int y, int m, int d) {



		if (m < 13 && m >0)

		{
			month = m;
			if (y > 0)
			{
				year = y;
				if (d > 0 && d <= mdays(m, y))

				{
					day = d;
				}
				else {

					errCode(DAY_ERROR);
					year = 0;
					month = 0;
					day = 0;
				}

				if ((y > 0) && (m < 32 && m>0) && (d > 0 && d < 32))
				{
					comparativeValue = year * 372 + month * 13 + day;

				}
			}
			else
			{
				errCode(YEAR_ERROR);
				year = 0;
				month = 0;
				day = 0;

			}
			
		}
		else
		{
			errCode(MON_ERROR);
			year = 0;
			month = 0;
			day = 0;
		}
		
		

	}



	int Date::compValue()const {
		return year * 372 + month* 31 + day;
	}

	bool Date::operator==(const Date& rhs) const
	{

		if (!isEmpty() && !rhs.isEmpty())
		{
			if (compValue() == rhs.compValue())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	 }

	bool Date::operator!=(const Date& rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty())
		{
			if (compValue() != rhs.compValue())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;

	}

	bool Date::operator<(const Date& rhs) const
	{

		if (!isEmpty() && !rhs.isEmpty())
		{
			if (compValue() < rhs.compValue())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	bool Date::operator>(const Date& rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty())
		{
			if (compValue() > rhs.compValue())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;

	}

	bool Date::operator<=(const Date& rhs) const
	{

		if (!isEmpty() && !rhs.isEmpty())
		{
			if (compValue() <= rhs.compValue())
			{
				return true;
			}
			else
			{
				return false;
			}
			
		}
		return false;

	}

	bool Date::operator>=(const Date& rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty())
		{
			if (compValue() >= rhs.compValue())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;

	}

	int Date::errCode()const
	{

		return errorState;

	}

	bool Date::bad()const
	{
		

		if (errorState != NO_ERROR)

			return true;
		else
			return false;

	}

	std::istream & Date::read(std::istream & istr)
	{
		char dataA;
		istr.clear();
		errCode(NO_ERROR);
		istr >> year >> dataA >> month>> dataA >> day;
		if (istr.fail()) {
			year = 0;
			month = 0;
			day = 0;

			errCode(CIN_FAILED);
		}
		else if (min_year > year || year > max_year) {
			year = 0;
			month = 0;
			day = 0;

			errCode(YEAR_ERROR);
		}
		else if (1 > month || month > 12) {
			year = 0;
			month = 0;
			day = 0;

			errCode(MON_ERROR);
		}
		else if (day> mdays(month, year)) {
			year = 0;
			month = 0;
			day = 0;

			errCode(DAY_ERROR);
		}

		istr.clear();

		return istr;
	}

	std::ostream & sict::Date::write(std::ostream & ostr) const
	{
	
		ostr << year << '/' << setw(2) << setfill('0')  << month  << '/' << setw(2) << setfill('0') << day;
		
		return ostr;
	}

	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}



	void Date::errCode(int errorCode) {

	
		errorState = errorCode;

	}


	bool Date :: isEmpty()const {

		if (year == 0 && month == 0 && day == 0) {

			return true;
		}
		else {

			return false;
		}


	}

	

	istream & operator>>(std::istream &ist, Date & s)
	{
		  return s.read(ist);
	}

	ostream & operator<<(std::ostream &ost, const Date & k)
	{
		return k.write(ost);
	}

}