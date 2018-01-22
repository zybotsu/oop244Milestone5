#ifndef SICT_DATE_H
#define SICT_DATE_H
#define NO_ERROR  0 
#define CIN_FAILED 1 
#define YEAR_ERROR 2  
#define MON_ERROR  3  
#define DAY_ERROR  4  


namespace sict {

	const int min_year = 2000;
	const int max_year = 2030;

	class Date {

		
		int year;
		int month;
		int day;
		int comparativeValue;
		int compValue()const;
		int errorState;
		int mdays(int, int)const;
		void errCode(int errorCode);
	
		


	public:
		Date();
		Date(int m_year,int m_month, int m_day);

		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		int errCode() const;
		bool bad() const; 
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;

		bool isEmpty() const;



	};

	//bool operator<<(const int Date);

	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, const Date&);



}
#endif
