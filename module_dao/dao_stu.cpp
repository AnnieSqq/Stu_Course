#include <map>
#include <iostream>
using namespace std;
int insertStu(char* content){
    puts("insertStu");
    return 0;
}//添加一条记录，返回行号，失败返回0
int removeStu(int line){
    puts("removeStu");
    return 0;
}//根据记录的行号删除，返回是否成功
int changeStu(int line,char* content){
    puts("changeStu");
    return 0;
}//根据行号覆盖修改内容，返回是否成功
map<int,int>* findStu(int col,char* keys){
    puts("findStu");
    return NULL;
}//查找col列的匹配keys的内容，返回行号集合

