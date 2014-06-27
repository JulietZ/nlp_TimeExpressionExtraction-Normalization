#include "Utils.h"
using namespace std;

int BUFFER_SIZE=10000;

vector<string> MONTHS;
vector<string> NUMBERS;
vector<string> HOLIDAY;
vector<string> WEEKDAY;
vector<string> DURINGDAY;
vector<string> GENERALTIMES;
vector<string> ORDERS;
map<string, string> HOLIDAY_MAP;
map<string, string> WEEKDAY_MAP;
map<string, string> MONTH_MAP;
map<string, string> NUMBER_MAP;

tm currentDay;
vector<tm> diffDays;

int main(int argc, char ** argv){

  loadDictionary();
  ifstream infile;
  infile.open("../input");
  if (!infile) {
    cout << "Fail to open infile" << endl;
    exit(0);
  }

  currentDay = getDate("02052014");

  char * buffer = new char[BUFFER_SIZE];
  while (!infile.eof()) {
    infile.read(buffer,BUFFER_SIZE);

    //get sentence
    char * sentence = strtok(buffer,".,?\n");
    while (sentence != NULL){
      //tokenize sentence
      string s(sentence);
      processSentence(s);
      sentence = strtok(NULL, ".,?\n");
    }
  }

  return 0;
}
