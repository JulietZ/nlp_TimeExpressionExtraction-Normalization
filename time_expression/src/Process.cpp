#include "Utils.h"
using namespace std;

void processSentence(string sentence){
  string token;
  while (sentence != ""){
    trim(sentence);
    token = getToken(sentence);
    if (token != ""){
      processKeywords(sentence, token);
    }
  }
}

void processKeywords(string& sentence, string token){
  trim(sentence);

  if(searchVector(token,1,MONTHS) != 1){
    processKeywordMonth(sentence, token);
  }

  transform(token.begin(), token.end(), token.begin(), ::tolower);
  if(token=="on"){
    processKeywordOn(sentence);
  }else if(token=="in"){
    processKeywordIn(sentence);
  }else if(token=="at"){
    processKeywordAt(sentence);
  }else if(token=="tommorrow" || token=="yesterday" || token=="today"){
    processKeywordSingleDay(sentence, token);
  }else if(token=="this" || token=="that" || token=="next" || token=="last"){
    processKeywordOrder(sentence, token);
  }else if(searchVector(token,1,NUMBERS) != 1){
    processKeywordNumber(sentence, token);
  }
}

void processKeywordOn(string& sentence){
  string month;
  string day;
  string weekday;
  string number;

  //pre-processing
  trimWord(sentence, "the");
  trimWord(sentence, "a");
  trimWord(sentence, "an");

  //match weekday
  if ((day=trimVector(sentence, WEEKDAY)) != ""){
    cout << "Got: On " << day;
    cout << "(" <<dateToString(countWeekDay(day)) << ")" << endl;

  //match holiday
  }else if ((day=trimVector(sentence, HOLIDAY)) != ""){
    cout << "Got: On " << day;
    cout << "(" << dateToString(countHoliday(day)) << ")" << endl;

  //match format : Octorber 1st
  }else if ((month=trimVector(sentence, MONTHS)) != ""){
    trimWord(sentence, "the");
    if ((number=trimVector(sentence, NUMBERS)) != ""){
      cout << "Got: On " << month << " " << number;
      cout << "(" << dateToString(countMonthDay(month, number)) << ")" << endl;
    }

  }else if ((number=trimVector(sentence, NUMBERS)) != ""){
    weekday=trimVector(sentence, WEEKDAY);
    if (trimWord(sentence, "of")){
      if ((month=trimVector(sentence, MONTHS)) != ""){
        //  the second Friday of Dec.
        if (weekday != ""){
          cout << "Got: On " << number << " " << weekday << " of " << month;
          cout << "(" << dateToString(countWeekMonth(number,weekday, month)) << ")" << endl;
        //  the first of Octorber
        }else{
          cout << "Got: On " << number << " of " << month;
          cout << "(" << dateToString(countMonthDay(month, number)) << ")" << endl;
        }
      }
    }
  }
}

void processKeywordIn(string& sentence){
  string month;
  string year;
  string number;
  string generalTime;

  //pre-processing
  trimWord(sentence, "the");

  //match format in January
  if ((month=trimVector(sentence, MONTHS)) != ""){
    cout << "Got: In " << month;
    int m = atoi(MONTH_MAP[month].c_str());
    tm t = {0,0,0,1,m-1,currentDay.tm_year};
    if ((year=trimYear(sentence)) != ""){
      int y = atoi(year.c_str());
      t.tm_year = y-1900;
      cout << " " << year;
    }
    cout <<"(" << dateToString(t) << ")" << endl;

  //match format in 2014
  }else if ((year=trimYear(sentence)) != ""){
    cout << "Got: In " << year;
    int y = atoi(year.c_str());
    tm t = {0,0,0,1,0,y-1900};
    cout <<"(" << dateToString(t) << ")" << endl;

  }else if ((number=trimVector(sentence, NUMBERS)) != ""){
    if ((generalTime=trimVector(sentence, GENERALTIMES)) != ""){
      int diffDay=0;
      int diffMonth=0;
      int diffYear=0;
      int count=atoi(NUMBER_MAP[number].c_str());
      tellGeneralTime(count, generalTime, diffDay, diffMonth, diffYear);
      cout << "Got: In " << number << " " << generalTime;
      cout <<"(" << dateToString(getNewDate(currentDay, diffDay, diffMonth, diffYear)) << ")" << endl;
    }
  }
}

void processKeywordAt(string& sentence){
  string day;
  string duringday;
  string generalTime;

  trimWord(sentence, "the");
  trimWord(sentence, "a");
  trimWord(sentence, "an");

  int index;
  if ((day=trimVector(sentence, WEEKDAY)) != ""){
    if ((duringday=trimVector(sentence, DURINGDAY)) != ""){
      cout << "Got: At " << day << " " << duringday;
      cout << "(" <<dateToString(countWeekDay(day)) << ")" << endl;
    }
  }else if ((day=trimVector(sentence, HOLIDAY)) != ""){
    if ((duringday=trimVector(sentence, DURINGDAY)) != ""){
      cout << "Got: At " << day << " " << duringday;
      cout << "(" <<dateToString(countHoliday(day)) << ")" << endl;
    }
  }else if ((duringday=trimVector(sentence, DURINGDAY)) != ""){
    if (trimWord(sentence, "of")){
      if ((day=trimVector(sentence, WEEKDAY)) != "") {
        cout << "Got: At " << duringday << " of " << day;
        cout << "(" <<dateToString(countWeekDay(day)) << ")" << endl;
      }else if ((day=trimVector(sentence, HOLIDAY)) != "") {
        cout << "Got: At " << duringday << " of " << day;
        cout << "(" <<dateToString(countHoliday(day)) << ")" << endl;
      }
    }
  }
}

void processKeywordOrder(string& sentence, string token){
  string day;
  string generalTime;
  string number;
  string month;
  int diff=0;

  if (token=="last"){
    diff=-1;
  }else if(token=="next"){
    diff=1;
  }

  if ((day=trimVector(sentence, WEEKDAY)) != ""){
    cout << "Got: " << token << " " << day;
    tm t = getNewDate(countWeekDay(day),7*diff,0,0);
    cout << "(" <<dateToString(t) << ")" << endl;
  }else if ((day=trimVector(sentence, HOLIDAY)) != ""){
    cout << "Got: " << token << " " << day;
    tm t = getNewDate(countHoliday(day),0,0,diff);
    cout << "(" <<dateToString(t) << ")" << endl;
  }else if ((day=trimVector(sentence, DURINGDAY)) != ""){
    cout << "Got: " << token << " " << day;
    tm t = getNewDate(currentDay,diff,0,0);
    cout << "(" << dateToString(t) << ")" << endl;
  }else if ((month=trimVector(sentence, MONTHS)) != ""){
    cout << "Got: " << token << " " << month;
    tm t = getNewDate(countMonth(month),0,0,diff);
    cout << "(" <<dateToString(t) << ")" << endl;
  }else if ((generalTime=trimVector(sentence, GENERALTIMES)) != ""){

    int diffDay=0;
    int diffMonth=0;
    int diffYear=0;
    tellGeneralTime(1, generalTime, diffDay, diffMonth, diffYear);
    diffDay*=diff;
    diffMonth*=diff;
    diffYear*=diff;

    cout << "Got: " << token << " " << generalTime;
    cout <<"(" << dateToString(getNewDate(currentDay, diffDay, diffMonth, diffYear)) << ")" << endl;
  }
}

void processKeywordSingleDay(string& sentence, string token){
  tm t;
  if(token=="tommorrow"){
    t=getNewDate(currentDay, 1, 0, 0);
  }else if (token=="yesterday"){
    t=getNewDate(currentDay, -1, 0, 0);
  }else if (token=="today"){
    t=currentDay;
  }
  cout << "Got: " << token;
  cout << "(" << dateToString(t) << ")" << endl;
}

void processKeywordNumber(string& sentence, string token){
  string generalTime;
  string keyword;
  int diffDay=0;
  int diffMonth=0;
  int diffYear=0;
  int count=atoi(NUMBER_MAP[token].c_str());

  if ((generalTime=trimVector(sentence, GENERALTIMES)) != ""){
    tellGeneralTime(count, generalTime, diffDay, diffMonth, diffYear);
    if (trimWord(sentence,"ago")){
      cout << "Got: " << token << " " << generalTime << " ago";
      diffDay*=-1;
      diffMonth*=-1;
      diffYear*=-1;
      cout <<"(" << dateToString(getNewDate(currentDay, diffDay, diffMonth, diffYear)) << ")" << endl;
    }else if (trimWord(sentence,"later")){
      cout << "Got: " << token << " " << generalTime << " later";
      cout <<"(" << dateToString(getNewDate(currentDay, diffDay, diffMonth, diffYear)) << ")" << endl;
    }
  }
}

void processKeywordMonth(string& sentence, string token){
  string number;
  string year;

  if ((number=trimVector(sentence, NUMBERS)) != ""){
    tm t =countMonthDay(token, number);
    if ((year=trimYear(sentence)) != ""){
      int y = atoi(year.c_str());
      t.tm_year=y-1900;
      cout << "Got: " << token << " " << number << " " << year;
      cout << "(" << dateToString(t) << ")" << endl;
    }else{
      cout << "Got: " << token << " " << number;
      cout << "(" << dateToString(t) << ")" << endl;
    }
  }

}
