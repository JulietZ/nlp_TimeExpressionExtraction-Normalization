#include "Utils.h"
using namespace std;

tm getDate(string inputday){
  int day;
  int month;
  int year;
  day=((int)inputday[0]-48)*10+((int)inputday[1]-48);
  month=((int)inputday[2]-48)*10+((int)inputday[3]-48);
  year=((int)inputday[4]-48)*1000+((int)inputday[5]-48)*100+((int)inputday[6]-48)*10+((int)inputday[7]-48)-1900;
  struct tm a={0,0,0,day,month-1,year};
  return a;
}

double dateDiff(tm a,tm b){
  time_t x=mktime(&a);
  time_t y=mktime(&b);
  if ( x != (time_t)(-1) && y != (time_t)(-1) ){
    double difference = difftime(y, x) / (60 * 60 * 24);
    return difference;
  }
  return 0;
}

int getWeekday (tm today){
  time_t x=mktime(&today);
  tm const *time_out=localtime(&x);
  int n=time_out->tm_wday;
  return n;
}

tm getNewDate (tm inputday, int diffDay, int diffMon, int diffYear){
  inputday.tm_mday +=diffDay;
  inputday.tm_mon +=diffMon;
  inputday.tm_year +=diffYear;
  time_t newDay=mktime(&inputday);
  tm t = *localtime(&newDay);
  return inputday;
}

tm countWeekDay(string weekday){
  int currentWeekday=getWeekday(currentDay);
  int inputWeekday=atoi(WEEKDAY_MAP[weekday].c_str());
  int diff=inputWeekday-currentWeekday;
  return getNewDate(currentDay,diff,0,0);
}

tm countHoliday(string holiday){
  string day=HOLIDAY_MAP[holiday];
  if (day[0] <= '9' && day[0] >= '0'){
    return getDate(day+to_string(currentDay.tm_year+1900));
  }

  string number=getToken(day);
  string weekday=getToken(day);
  getToken(day);
  string month=getToken(day);

  return countWeekMonth(number, weekday, month);
}

tm countMonth(string month){
  int m=atoi(MONTH_MAP[month].c_str());
  tm t = {0,0,1,1,m-1,currentDay.tm_year};
  return t;
}

tm countMonthDay(string month, string day){
  int m=atoi(MONTH_MAP[month].c_str());
  int d=atoi(NUMBER_MAP[day].c_str());

  tm t = {0,0,0,d,m-1,currentDay.tm_year};
  return t;
}

tm countWeekMonth(string n, string wd, string m){
  int number=atoi(NUMBER_MAP[n].c_str());
  int weekday=atoi(WEEKDAY_MAP[wd].c_str());
  int month=atoi(MONTH_MAP[m].c_str());

  tm firstDayOfMonth={0,0,1,month-1,currentDay.tm_year};
  int weekdayOfFirstDay=getWeekday(firstDayOfMonth);

  int diff=number*7+weekday-weekdayOfFirstDay;
  if (weekdayOfFirstDay<weekday){
    diff-=7;
  }

  return getNewDate(firstDayOfMonth, diff, 0, 0);
}

void tellGeneralTime(int count, string generalTime, int& diffDay, int& diffMonth, int& diffYear){
  if (generalTime=="day" || generalTime=="days"){
    diffDay=count;
  }else if (generalTime=="month" || generalTime=="months"){
    diffMonth=count;
  }else if (generalTime=="year" || generalTime=="years"){
    diffYear=count;
  }else if (generalTime=="decade" || generalTime=="decades"){
    diffYear=count*20;
  }else if (generalTime=="week" || generalTime=="weeks"){
    diffDay=7*count;
  }
}

string dateToString(tm date){
  stringstream ss_day;
  ss_day << setw(2) << setfill('0') << date.tm_mday;
  string day = ss_day.str();

  stringstream ss_month;
  ss_month << setw(2) << setfill('0') << date.tm_mon+1;
  string month = ss_month.str();

  string year=to_string(date.tm_year+1900);

  return day+month+year;
}


