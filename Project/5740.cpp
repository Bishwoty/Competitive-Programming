#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using namespace std::rel_ops;

// Date class from date.cc (slightly modified)
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

// Reads a date in mm/dd/yyyy format, assumes date is valid and in the
// right format
istream &operator>>(istream &is, Date &d) {
  char c;
  return is >> d.mm >> c >> d.dd >> c >> d.yyyy;
}

// print date in mm/dd/yyyy format
ostream &operator<<(ostream &os, const Date &d) {
  os << d.mm << '/' << d.dd << '/' << d.yyyy;
  return os;
}

int works(Date citizenshipDay, Date resident, Date landing,
          vector<pair<Date, Date>> &trips);

int main() {
  Date resident, landing;
  int numTrips;
  while (cin >> resident >> landing >> numTrips) {
    vector<pair<Date, Date>> trips;
    trips.reserve(numTrips);
    Date low = landing;
    low.addDay(1095);
    low.addDay((landing.daysFromStart() - resident.daysFromStart()) / -2);
    for (int i = 0; i < numTrips; i++) {
      Date travStart, travEnd;
      cin >> travStart >> travEnd;
      trips.push_back(make_pair(travStart, travEnd));
    }
    int daysOff;
    while (true) {
      daysOff = works(low, resident, landing, trips);
      if (daysOff <= 0) {
        break;
      }
      low.addDay(daysOff);
    }
    cout << low << endl;
  }
  return 0;
}

int works(Date citizenshipDay, Date resident, Date landing,
          vector<pair<Date, Date>> &trips) {
  Date start = citizenshipDay;
  start.addDay(-1460);
  vector<int> days(1460);
  Date index = start;
  for (int i = 0; i < days.size(); i++) {
    if (index < resident) {
      days[i] = 0;
    } else if (index < landing) {
      days[i] = 1;
    } else {
      days[i] = 2;
    }
    index.addDay(1);
  }
  for (auto trip : trips) {
    if (trip.first >= start && trip.second < citizenshipDay) {
      for (int i = trip.first.daysFromStart() - start.daysFromStart();
           i <= trip.second.daysFromStart() - start.daysFromStart(); i++) {
        days[i] = 0;
      }
    } else if (trip.first < start && trip.second < citizenshipDay) {
      for (int i = 0; i <= trip.second.daysFromStart() - start.daysFromStart();
           i++) {
        days[i] = 0;
      }
    } else if (trip.first >= start && trip.second >= citizenshipDay) {
      for (int i = trip.first.daysFromStart() - start.daysFromStart();
           i < days.size(); i++) {
        days[i] = 0;
      }
    } else if (trip.first < start && trip.second >= citizenshipDay) {
      for (int i = 0; i < days.size(); i++) {
        days[i] = 0;
      }
    }
  }
  int count = 0;
  for (int i = 0; i < days.size(); i++) {
    count += days[i];
    // cout << days[i] << ' ';
  }
  // cout << endl;
  // cout << citizenshipDay << ": " << count / 2 << endl;
  return 1095 - count / 2;
}