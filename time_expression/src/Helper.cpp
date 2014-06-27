#include "Utils.h"
using namespace std;

void loadDictionary(){
  readList("../dictionary/MONTHS.list", MONTHS);
  readList("../dictionary/NUMBERS.list", NUMBERS);
  readList("../dictionary/ORDERS.list", ORDERS);
  readList("../dictionary/HOLIDAYS.list", HOLIDAY);
  readList("../dictionary/WEEKDAYS.list", WEEKDAY);
  readList("../dictionary/DURINGDAY.list", DURINGDAY);
  readList("../dictionary/GENERALTIMES.list", GENERALTIMES);
  readMap("../dictionary/HOLIDAYS.map", HOLIDAY_MAP);
  readMap("../dictionary/WEEKDAYS.map", WEEKDAY_MAP);
  readMap("../dictionary/MONTHS.map", MONTH_MAP);
  readMap("../dictionary/NUMBERS.map", NUMBER_MAP);
}

void readList(string filename, vector<string>& v){
  ifstream infile;
  infile.open(filename);
  if (!infile) {
    cout << "Fail to open infile" << filename << endl;
    exit(0);
  }

  string line;
  while (!infile.eof()){
    getline(infile,line);
    v.push_back(line);
  }
}

void readMap(string filename, map<string, string>& m){
  ifstream infile;
  infile.open(filename);
  if (!infile) {
    cout << "Fail to open infile" << filename << endl;
    exit(0);
  }

  string line;
  while (!infile.eof()){
    getline(infile,line);

    //read map
    stringstream ss(line);
    string key;
    string value;
    getline(ss, key, '\t');
    getline(ss, value, '\t');

    m[key] = value;
  }
}

string getToken(string& s){
  int i=0;
  int len=s.length();

  //get token
  while (i<len && s[i]!=' '){
    i++;
  }
  string token=s.substr(0,i);
  s.erase(0,i);
  trim(s);
  return token;
}

string getNthToken(string& s, int n){
  string token;
  for (int i=0; i<n+1; i++){
    token=getToken(s);
  }
  return token;
}

void trim(string& s){
  int i=0;
  int len=s.length();

  //skip space
  while (i<len && s[i]==' '){
    i++;
  }
  s.erase(0,i);
}

bool trimWord(string& s, string word){
  int lenS = s.length();
  int lenW = word.length();
  if (lenS>=lenW && !s.compare(0,lenW,word)
       && !isDelimeter(s[lenW+1])){
    s.erase(0,word.length());
    trim(s);
    return true;
  }
  return false;
}

bool isDelimeter(char c){
  string delimeter = " .,;!?'\"\n\r\t";
  for (int i=0; i<delimeter.length(); i++){
    if (c == delimeter[i]){
      return true;
    }
  }
  return false;
}

string trimVector(string& s, vector<string> v){
  for (vector<string>::iterator it=v.begin(); it!=v.end(); ++it){
    if (trimWord(s, (*it))){
      trim(s);
      return (*it);
    }
  }
  return "";
}

string trimYear(string& s){
  string token = getToken(s);
  bool flag = true;
  if (token.length()==4){
    for (int i=0; i<4; i++){
      if (token[i] < '0' || token[i] > '9'){
        flag = false;
      }
    }
  }else {
    flag = false;
  }

  if (flag){
    return token;
  }else{
    s=token+" "+s;
    return "";
  }
}

int searchVector(string s, int limit, vector<string> v){
  //search only five tokens
  int i=0;

  for (; i<limit; i++){
    if (trimVector(s, v) != ""){
      return i;
    }else{
      getToken(s);
    };
  }
  return i;
}
