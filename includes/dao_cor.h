#include <map>
#ifndef MYPROJECT_DAO_COR_H
#define MYPROJECT_DAO_COR_H
using namespace std;
int insertCor(char* content);
int removeCor(int line);
int changeCor(int line,char*);
map<int,int> findCor(int col,char* keys);
#endif
