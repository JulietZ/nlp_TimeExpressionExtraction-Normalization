#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <ctime>

extern int BUFFER_SIZE;

extern std::vector<std::string> MONTHS;
extern std::vector<std::string> NUMBERS;
extern std::vector<std::string> ORDERS;
extern std::vector<std::string> WEEKDAY;
extern std::vector<std::string> HOLIDAY;
extern std::vector<std::string> DURINGDAY;
extern std::vector<std::string> GENERALTIMES;
extern std::map<std::string, std::string> HOLIDAY_MAP;
extern std::map<std::string, std::string> WEEKDAY_MAP;
extern std::map<std::string, std::string> MONTH_MAP;
extern std::map<std::string, std::string> NUMBER_MAP;

extern std::vector<std::tm> diffDays;
extern std::tm currentDay;

void loadDictionary();
void readList(std::string filename, std::vector<std::string>& v);
void readMap(std::string filename, std::map<std::string, std::string>& m);
std::string getNthToken(std::string& s, int n);
std::string getToken(std::string& s);
void trim(std::string& s);
bool isDelimeter(char c);
bool trimWord(std::string& s, std::string word);
std::string trimVector(std::string& s, std::vector<std::string> v);
std::string trimYear(std::string& s);
int searchVector(std::string sentence, int limit, std::vector<std::string> v);


void processSentence(std::string s);
void processKeywords(std::string& s, std::string token);
void processKeywordOn(std::string& s);
void processKeywordAt(std::string& s);
void processKeywordIn(std::string& s);
void processKeywordSingleDay(std::string& s, std::string token);
void processKeywordOrder(std::string& s, std::string token);
void processKeywordNumber(std::string& sentence, std::string token);
void processKeywordMonth(std::string& sentence, std::string token);

std::tm getDate(std::string inputday);
double dateDiff(std::tm a,std::tm b);
int getWeekday (std::tm today);
std::tm getNewDate (std::tm inputday, int diffDay, int diffMonth, int diffYear);
std::tm countWeekDay(std::string weekDay);
std::tm countHoliday(std::string holiday);
std::tm countMonth(std::string month);
std::tm countMonthDay(std::string month, std::string day);
std::tm countWeekMonth(std::string n, std::string wd, std::string m);
std::string dateToString(std::tm date);
void tellGeneralTime(int count, std::string generalTime, int& diffDay, int& diffMonth, int& diffYear);
