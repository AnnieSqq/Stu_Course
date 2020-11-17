#include <map>
#ifndef MYPROJECT_DAO_STU_H
#define MYPROJECT_DAO_STU_H
using namespace std;
int insertStu(char* content);
int removeStu(int line);
int changeStu(int line,char* content);
int findStuLines(int col, const char *keys, map<int, int> &lines);
string findStu(int line);
#endif

