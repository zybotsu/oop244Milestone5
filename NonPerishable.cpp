#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <istream>
#include <iomanip>
#include <cstring>
#include "ErrorMessage.h"
#include "NonPerishable.h"

using namespace std;
namespace sict
{

	
	void NonPerishable::name(const char *n) {


		if (n == nullptr) {
			delete[] m_productName;
	
		}
		else {
			m_productName = new char[strlen(n) + 1];
			strncpy(m_productName, n, (strlen(n) + 1));
			m_productName[strlen(n) + 1] = '\0';
		}
	}

	const char *NonPerishable::name() const
	{
		if (m_productName == nullptr)
			return nullptr;
		else return m_productName;
	}



	void NonPerishable::message(const char *error)
	{
		e.message(error);

	}

	const char* NonPerishable::sku()const {
		return m_productSku;
	}


	const char* NonPerishable::unit()const {
		return m_productUnit;
	}
	bool NonPerishable::isClear()const {
		if (e.isClear())

			return true;
		else
			return false;
	}
	NonPerishable::NonPerishable(char type)
	{
	
		m_productType = type;       
		m_productSku[0] = '\0';
		m_productName = nullptr;
		m_productUnit[0] = '\0';
		m_currentQuantity = 0;
		m_quantityNeeded = 0;
		m_price = 0;
		m_taxable = true;
	}


	NonPerishable::NonPerishable(const char* productSku, const char*productName, const char*productUnit, int qty, bool taxable, double pricePreTax, int qtyNeeded)
	{
		//assign
		m_productType = '\0';
		m_productSku[0] = '\0';
		m_productName = nullptr;
		m_productUnit[0] = '\0';
		m_currentQuantity = 0;
		m_quantityNeeded = 0;
		m_price = 0.0;

		strncpy(m_productSku, productSku, +1);
		m_productName = new char[strlen(productName) + 1];
		strncpy(m_productName, productName, max_name_length);
		strncpy(m_productUnit, productUnit, max_unit_length +1);
		m_taxable = taxable;
		m_currentQuantity = qty;
		m_quantityNeeded = qtyNeeded;
		m_price = pricePreTax;
	}

	NonPerishable::NonPerishable(const NonPerishable& other)
	{
		m_productName = nullptr;
		*this = other;

	}
	NonPerishable & NonPerishable::operator=(const NonPerishable & other)
	{

		if (this != &other) {
			sku(other.m_productSku);
			name(other.m_productName);
			strcpy(m_productUnit, other.m_productUnit );
			m_currentQuantity = other.m_currentQuantity;
			m_quantityNeeded = other.m_quantityNeeded;
			m_taxable = other.m_taxable;
			m_price = other.m_price;

			return *this;

		}
		else
			m_productSku[0] = '\0';
		m_productName = nullptr;
		m_productUnit[0] = '\0';
		m_currentQuantity = 0;
		m_quantityNeeded = 0;
		m_taxable = false;

		return *this;
	}


	NonPerishable::~NonPerishable()
	{
		e.clear();
	}



	fstream & NonPerishable::store(fstream& file, bool newLine) const
	{

		file << m_productType << ',' << m_productSku << ',' << m_productName << ',' << m_price << ',' << m_taxable << ',' << m_currentQuantity
			<< ',' << m_productUnit << ',' << m_quantityNeeded;
		if (newLine) {
			file << endl;
		}
		return file;
	}

	fstream& NonPerishable::load(fstream& file)
	{
	    char temp_sku[max_sku_length +1], temp_name[max_name_length +1],
		temp_unit[max_unit_length +1];
		double temp_price;
		int temp_qty, temp_qtyN, temp_tax;
		if (file.is_open()) {
			file.getline(temp_sku, max_sku_length, ',');
			sku(temp_sku);
			file.getline(temp_name, max_name_length + 1, ',');

			name(temp_name);

			file >> temp_price;
			file.ignore();
			m_price = temp_price;

			file >> temp_tax;
			file.ignore();
			m_taxable = temp_tax;

			file >> temp_qty;
			file.ignore();
			m_currentQuantity = temp_qty;


			file.getline(temp_unit, max_unit_length + 1, ',');
			unit(temp_unit);

			file >> temp_qtyN;
			file.ignore();
			m_quantityNeeded = temp_qtyN;
		}
		return file;
	}

		std::ostream &NonPerishable::write(std::ostream & os, bool linear) const
		{

			if (!(e.isClear())) {
				os << e.message();
			}
			else if (linear) {
				os << left << setw(max_sku_length) << setfill(' ') << sku() << "|"
					<< left << setw(20) << setfill(' ') << name() << "|";
			
					os << right << fixed << setfill(' ') << setw(7) << setprecision(2) << cost() << "|";
				
				
				os << right << setw(4) << setfill(' ') << fixed << quantity() << "|"
					<< left << setw(10) << setfill(' ')<< unit() << "|"
					<< right << setw(4) << setfill(' ') << fixed << qtyNeeded() << "|";
			}
			else {
				os << "Sku: " << m_productSku << endl;
				os << "Name: " << m_productName<< endl;
				os << "Price: " << m_price << endl;
				os << "Price after tax: ";
				if (taxed()) {
					os << cost() << endl;
				}
				else {
					os << "N/A" << endl;
				}
				os << "Quantity On Hand: " << quantity() << ' ' << m_productUnit << endl;
				os << "Quantity Needed: " << qtyNeeded();
			}
			return os;
	}

		std::istream& NonPerishable::read(std::istream& is) {

			char tempSku[max_sku_length +1];
			char tempName[max_name_length + 1];
			char tempUnit[max_unit_length +1];

			char taxChar;
			double tempPrice;
			int tempCurrentQty;
			int tempQtyNeeded;

			if (!is.fail()) {
				e.clear();
				cout << " Sku: ";
				is >> tempSku;
				cin.ignore();
				sku(tempSku);

				cout << " Name: ";
				is.getline(tempName, max_name_length + 1);
				name(tempName);

				cout << " Unit: ";
				is.getline(tempUnit, max_unit_length -1);
				unit( tempUnit);

				cout << " Taxed? (y/n): ";
				is >> taxChar;
				if (is.fail() || !(taxChar == 'Y' || taxChar == 'y' || taxChar == 'N' || taxChar=='n')) {
					e.message("Only (Y)es or (N)o are acceptable");
					is.setstate(std::ios::failbit);
					return is;
				}
				else {
					if (taxChar == 'Y' || taxChar == 'y')
					{
						setTaxable(true);
					}
					else
					{
						setTaxable(false);
					}

				}
				cout << " Price: ";
				if (e.isClear()) {
					is >> tempPrice;
					if (is.fail()) {

						e.message("Invalid Price Entry");
						is.setstate(ios::failbit);			
						return is;
					}
					else {
						m_price = tempPrice;
					}
				}
				if (e.isClear()) {
					cout << "Quantity On hand: ";
					is >> tempCurrentQty;
					if (is.fail()) {

						e.message("Invalid Quantity Entry");
						is.setstate(ios::failbit);
						return is;
					}
					else
					{
						m_currentQuantity = tempCurrentQty;
					}
				}
				if (e.isClear()) {
					cout << "Quantity Needed: ";
					is >> tempQtyNeeded;
					if (is.fail()) {

						e.message("Invalid Quantity Needed Entry");
						is.setstate(ios::failbit);
						return is;

					}
					else {
						m_quantityNeeded = tempQtyNeeded;
					}
					return is;
				}
			};
			return is;
		}

		bool NonPerishable::operator==(const char*fooSku) const
		{
			if (strcmp(m_productSku, fooSku) == 0)
				return true;
			else
				return false;
		}
		
		double NonPerishable::total_cost() const {
		 
		
			double totalcost;

			totalcost = m_currentQuantity * cost();


			return totalcost;

		}

		double NonPerishable::cost() const {


			double sum = m_price;
			if (m_taxable)
				return sum *= taxRate + 1;
			else
				return sum;
		}
			
		bool NonPerishable::isEmpty() const {
			if ( m_productName == nullptr) 
				return true;
			else
				return false;
			}

				int NonPerishable::quantity() const {

					return  m_currentQuantity;
				}

				int NonPerishable::qtyNeeded() const {
					return m_quantityNeeded;
				}

				bool NonPerishable::operator>(const char* item) const {
					int a = strcmp(m_productSku, item);
					if (a > 0)
						return true;
					else
						return false;
				}

				int NonPerishable::operator+=(int add) {
					if (add > 0)
					{
						m_currentQuantity += add;
						return m_currentQuantity;
					}
					else
						return m_currentQuantity;
				}

				bool NonPerishable::operator>(const Product& name) const
				{
					int a = strcmp(m_productSku, name.name());
					if (a > 0)
						return true;
					else
						return false;
				}

				std::ostream& operator<<(std::ostream&os, const Product& I)
				{
					
					return I.write(os, true);
				
				}

				std::istream& operator >> (std::istream& i, Product& p) {
				
					return p.read(i);
					
				}

				double operator+=(double& l, const Product& item) {
				
					return l += item.total_cost();
					
				
				}
				Product * CreateProduct()
				{
					Product* p = nullptr;
					p = new NonPerishable();
					return p;
				}

				//Setters

				
				bool NonPerishable::taxed() const {
					return m_taxable;
				}

				void NonPerishable::setTaxable(bool b) {

					m_taxable = b;
				}

				void NonPerishable::sku(const char* sku) {
					strncpy(m_productSku, sku, max_sku_length + 1);
				}

				void NonPerishable::unit(const char * unit)
				{
					strncpy(m_productUnit, unit, max_unit_length + 1);
				}


				void NonPerishable::quantity(int b)
				{
					m_currentQuantity = b;
				}

}

