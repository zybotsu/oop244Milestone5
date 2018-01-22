#include <iostream>
#include <iomanip>
#include <fstream>
#include "Date.h"
#include "NonPerishable.h"
#include "Perishable.h"

namespace sict {

	Perishable::Perishable():NonPerishable('P')
	{
		e.clear();
	}

	std::fstream & Perishable::store(std::fstream & file, bool newLine) const
	{
		
	
			NonPerishable::store(file, false);
			file << "," << m_expiry << std::endl;
			return file;
	}


	std::fstream & Perishable::load(std::fstream & file)
		{
		NonPerishable::load(file);
		m_expiry.read(file);
		file.ignore();

			return file;
		}


	std::ostream & sict::Perishable::write(std::ostream & os, bool linear) const
	{
		NonPerishable::write(os, linear);
		if (isClear() && !isEmpty()) {
			if (linear == true) {
				m_expiry.write(os);
			}
			else {
				os << "\nExpiry date: ";
				m_expiry.write(os);
			}
		}
		return os;
	}


	std::istream &Perishable::read(std::istream & is)
	{
	
		is.clear();
		NonPerishable::read(is);

		if (e.isClear()) {
			std::cout << "Expiry date (YYYY/MM/DD): ";
			m_expiry.read(is);
		}

		if (m_expiry.errCode() == CIN_FAILED) {
			e.clear();
			e.message("Invalid Date Entry");
		}
		if (m_expiry.errCode() == YEAR_ERROR) {
			e.message("Invalid Year in Date Entry");
		}
		if (m_expiry.errCode() == MON_ERROR) {
			e.clear();
			e.message("Invalid Month in Date Entry");
		}
		if (m_expiry.errCode() == DAY_ERROR) {
			e.clear();
			e.message("Invalid Day in Date Entry");
		}
		if (m_expiry.errCode()) {
			is.setstate(std::ios::failbit);
		}
		if (m_expiry.errCode() != CIN_FAILED && m_expiry.errCode() != YEAR_ERROR && m_expiry.errCode() != MON_ERROR && m_expiry.errCode() != DAY_ERROR) {
			e.clear();  //clear if there is no errorcode.
		}

		return is;
	}


	const Date &Perishable::expiry () const
	{
		return m_expiry;
	}



	Product * CreatePerishable()
	{
		Product *product = new Perishable();
		return product;
	}


}





