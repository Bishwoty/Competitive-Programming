#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using namespace std::rel_ops;

// From date.cc by Howard Cheng
struct Date {

  int yyyy;
  int mm;
  int dd;

  // no dates before 1753
  static int const BASE_YEAR = 1753;

  // Enumerated type for names of the days of the week
  enum dayName { SUN, MON, TUE, WED, THU, FRI, SAT };

  // Is a date valid
  static bool validDate(int yr, int mon, int day) {
    return yr >= BASE_YEAR && mon >= 1 && mon <= 12 && day > 0 &&
           day <= daysIn(mon, yr);
  }

  bool isValid() const { return validDate(yyyy, mm, dd); }

  // Constructor to create a specific date.  If the date is invalid,
  // the behaviour is undefined
  Date(int yr = 1970, int mon = 1, int day = 1) {
    yyyy = yr;
    mm = mon;
    dd = day;
  }

  // Returns the day of the week for this
  dayName dayOfWeek() const {
    int a = (14 - mm) / 12;
    int y = yyyy - a;
    int m = mm + 12 * a - 2;
    return (dayName)((dd + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7);
  }

  // comparison operators
  bool operator==(const Date &d) const {
    return dd == d.dd && mm == d.mm && yyyy == d.yyyy;
  }

  bool operator<(const Date &d) const {
    return yyyy < d.yyyy || (yyyy == d.yyyy && mm < d.mm) ||
           (yyyy == d.yyyy && mm == d.mm && dd < d.dd);
  }

  // Returns true if yr is a leap year
  static bool leapYear(int y) {
    return (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0));
  }

  // number of days in this month
  static int daysIn(int m, int y) {
    switch (m) {
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
    case 2:
      if (leapYear(y)) {
        return 29;
      } else {
        return 28;
      }
    default:
      return 31;
    }
  }

  // increment by day, month, or year
  //
  // Use negative argument to decrement
  //
  // If adding a month/year results in a date before BASE_YEAR, the result
  // is undefined.
  //
  // If adding a month/year results in an invalid date (Feb 29 on a non-leap
  // year, Feb 31, Jun 31, etc.), the results are automatically "rounded down"
  // to the last valid date

  // add n days to the date: complexity is about n/30 iterations
  void addDay(int n = 1) {
    dd += n;
    while (dd > daysIn(mm, yyyy)) {
      dd -= daysIn(mm, yyyy);
      if (++mm > 12) {
        mm = 1;
        yyyy++;
      }
    }

    while (dd < 1) {
      if (--mm < 1) {
        mm = 12;
        yyyy--;
      }
      dd += daysIn(mm, yyyy);
    }
  }

  // add n months to the date: complexity is about n/12 iterations
  void addMonth(int n = 1) {
    mm += n;
    while (mm > 12) {
      mm -= 12;
      yyyy++;
    }

    while (mm < 1) {
      mm += 12;
      yyyy--;
    }

    if (dd > daysIn(mm, yyyy)) {
      dd = daysIn(mm, yyyy);
    }
  }

  // add n years to the date
  void addYear(int n = 1) {
    yyyy += n;
    if (!leapYear(yyyy) && mm == 2 && dd == 29) {
      dd = 28;
    }
  }

  // number of days since 1753/01/01, including the current date
  int daysFromStart() const {
    int c = 0;
    Date d(BASE_YEAR, 1, 1);
    Date d2(d);

    d2.addYear(1);
    while (d2 < *this) {
      c += leapYear(d.yyyy) ? 366 : 365;
      d = d2;
      d2.addYear(1);
    }

    d2 = d;
    d2.addMonth(1);
    while (d2 < *this) {
      c += daysIn(d.mm, d.yyyy);
      d = d2;
      d2.addMonth(1);
    }
    while (d <= *this) {
      d.addDay();
      c++;
    }
    return c;
  }
};

// Reads a date in yyyy/mm/dd format, assumes date is valid and in the
// right format
istream &operator>>(istream &is, Date &d) {
  char c;
  return is >> d.yyyy >> c >> d.mm >> c >> d.dd;
}

// print date in mm/dd/yyyy format
ostream &operator<<(ostream &os, const Date &d) {
  char t = os.fill('0');
  os << setw(2) << d.mm << '/' << setw(2) << d.dd << '/' << setw(4) << d.yyyy;
  os.fill(t);
  return os;
}

////////////////////////////////////////////////////////////////////////////////

vector<pair<Date, string>> signs;

void makeTable() {
  signs.push_back(make_pair(Date(2000, 1, 21), "aquarius"));
  signs.push_back(make_pair(Date(2000, 2, 20), "pisces"));
  signs.push_back(make_pair(Date(2000, 3, 21), "aries"));
  signs.push_back(make_pair(Date(2000, 4, 21), "taurus"));
  signs.push_back(make_pair(Date(2000, 5, 22), "gemini"));
  signs.push_back(make_pair(Date(2000, 6, 22), "cancer"));
  signs.push_back(make_pair(Date(2000, 7, 23), "leo"));
  signs.push_back(make_pair(Date(2000, 8, 22), "virgo"));
  signs.push_back(make_pair(Date(2000, 9, 24), "libra"));
  signs.push_back(make_pair(Date(2000, 10, 24), "scorpio"));
  signs.push_back(make_pair(Date(2000, 11, 23), "sagittarius"));
  signs.push_back(make_pair(Date(2000, 12, 23), "capricorn"));
}

string getSign(Date date) {
  for (int i = 0; i < signs.size(); i++) {
    if (date.mm < signs.at(i).first.mm ||
        (date.mm == signs.at(i).first.mm && date.dd < signs.at(i).first.dd)) {
      return signs.at((i + 11) % 12).second;
    }
  }
}

int main() {
  makeTable();
  int datasets, setNum = 0;
  cin >> datasets;
  for (int i = 0; i < datasets; i++) {
    setNum++;
    string rawDate;
    cin >> rawDate;
    Date date(stoi(rawDate.substr(4, 4)), stoi(rawDate.substr(0, 2)),
              stoi(rawDate.substr(2, 2)));
    date.addDay(280);
    cout << setNum << ' ' << date << ' ' << getSign(date) << endl;
  }
  return 0;
}