/*
	Author: Jiajiang Xie
    cite:http://www.cplusplus.com/reference/ctime/localtime/
 */
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

class JulianDate {
private:
    static int EPOCH;
    int mon, day, year, hour, min, sec;
    const static int cumulativeDaysUpToMonth[12];
    const static string monthNames[12];
    // this representation would make difference VERY UGLY
    // diff between Jan. 1 2001 12:03:04  and Feb 26 2028 11:19:02
    double jday; // number of days since epoch
    JulianDate(double julday) : jday(julday), year(getYear()), mon(getMonth()), day(getDay()), hour(getHour()), min(getMin()), sec(getSec()){}
public:
    JulianDate(int year, int mon, int day, int hour, int min, int sec) : year(year), mon(mon), day(day), hour(hour), min(min), sec(sec){
        int dy = year - 2000; // daysperyear = 365.2425
        int days = 365*dy + dy / 4 - dy / 100 + dy / 400 + 1;
        days += cumulativeDaysUpToMonth[mon-1];
        jday = days + day - 1;
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
            if(mon < 3){
                jday--;
            }
        }
        int secs = hour * 3600 + min * 60 + sec;
        jday += double(secs)/86400;
    }
    JulianDate(){
        time_t t;
        struct tm *locoal;
        t = time(nullptr);
        locoal = localtime(&t);
        year = locoal->tm_year + 1900;
        mon = locoal->tm_mon + 1;
        day = locoal->tm_mday;
        hour = locoal->tm_hour;
        min = locoal->tm_min;
        sec = locoal->tm_sec;
        int dy = year - 2000; // daysperyear = 365.2425
        int days = 365*dy + dy / 4 - dy / 100 + dy / 400 + 1;
        days += cumulativeDaysUpToMonth[mon-1];
        jday = days + day - 1;
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
            if(mon < 3){
                jday--;
            }
        }
        int secs = hour * 3600 + min * 60 + sec;
        jday += double(secs)/86400;
    }
    friend double operator -(const JulianDate& a, const JulianDate& b){
        return a.jday - b.jday;
    }
    friend JulianDate operator +(const JulianDate& a, int b){
        return {a.jday + b};
    }


    int getYear(){
        year = 2000+jday/365.2422;
        return year;
    }

    int getMonth(){
        getYear();
        int dy = year - 2000;
        int days = 0;
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
            days = int(jday) - (365*dy + dy / 4 - dy / 100 + dy / 400);
            if(days >=0 && days <= 30){
                mon = 1;
            } else if(days >= 31 && days <= 59){
                mon = 2;
            } else{
                for(int i = 2; i < 12; i++){
                    if(days > cumulativeDaysUpToMonth[i])
                        mon = i + 1;
                }
            }
        }
        else{
            days = int(jday) - (365*dy + dy / 4 - dy / 100 + dy / 400 + 1);
            for(int i = 0; i < 12; i++) {
                if (days >= cumulativeDaysUpToMonth[i]) {
                    mon = i + 1;
                }
            }
        }
        return mon;
    }
    int getDay(){
        int dy = year - 2000;
        int days = 365*dy + dy / 4 - dy / 100 + dy / 400 + 1;
        days += cumulativeDaysUpToMonth[mon-1];
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
            if(mon < 3){
                days--;
            }
        }
        day = int(jday) - days + 1;
        return day;
    }
    int getHour(){
        double i = jday - int(jday);
        hour = int((i * 86400 )/ 3600);
        return hour;
    }
    int getMin(){
        double i = jday - int(jday);
        min = int((i*86400 - hour*3600)/60);
        return min;
    }
    int getSec(){
        double i = jday - int(jday);
        sec = (int)round(i*86400 - hour*3600 - min*60);
        return sec;
    }
    friend ostream& operator <<(ostream& s, JulianDate a){
        return s << monthNames[a.getMonth()-1] << ". " << a.getDay()
        << " " << a.getYear() << " " << a.getHour() << ":" << a.getMin()
        << ":" << a.getSec();
    }
};

int JulianDate::EPOCH = 2000; // Jan.1 2000, 00:00:00 = 0
const int JulianDate::cumulativeDaysUpToMonth[12] =
        {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
const string JulianDate::monthNames[12] =
        {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int main() {
    JulianDate newyear(2018, 1, 1, 0,0,0);
    JulianDate valentine(2018, 2, 14, 12,0,0); // 0.5
    JulianDate today; // get it from the system time: time(nullptr)
    // localtime

    double days = valentine - newyear;
    JulianDate due = today + 7;
    cout << due << '\n';

    cout << "\nyear: " << newyear.getYear()
         << "\nmonth: " << newyear.getMonth()
         << "\nday: " << newyear.getDay()
         << "\nhour: " << newyear.getHour()
         << "\nmin: " << newyear.getMin()
         << "\nsec: " << newyear.getSec() << '\n';
    JulianDate d1(2019, 1, 1, 0,0,0);
    for (int i = 0; i < 100; i++)
        cout << d1 + i;
}

