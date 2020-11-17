#include <map>
#ifndef MYPROJECT_DAO_COR_H
#define MYPROJECT_DAO_COR_H
using namespace std;
int insertCor(char* content);
int removeCor(int line);
int changeCor(int line,char* content);
int findCorLines(int col, const char *keys, map<int, int> &lines);
string findCor(int line);
#endif
