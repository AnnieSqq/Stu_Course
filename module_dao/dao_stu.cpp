#include <map>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
int insertStu(char *content)
{
    FILE *fp = NULL;
    //首先获取当前的行数
    int lines = 0;
    if(!(fp = fopen("../dbs/students","a+")))return -1;
    while(!feof(fp)){
        char ch = fgetc(fp);
        if(ch=='\n'){
            ++lines;
        }
    }
    //不必查找是否重复，因为学号由操作端自动分配，因此不会存在重复学号的情况
    fseek(fp,0,SEEK_SET);
    //格式应该也不会错，因为是操作端传过来的
    //判断末尾是否由回车
    cout<<content<<endl;
    string record = content;
    if(content[strlen(content)-1]!='\n')record = record+"\n";
    cout<<record<<endl;
    const char* p = record.data();
    char buff[1024] = {0};
    sprintf(buff,"echo -n '%s' | tee -a ../dbs/students",p);
    system(buff);
    fclose(fp);
    puts("insertStu\n----------------------------------");
    return lines+1;
} //添加一条记录，返回行号，失败返回1。如果添加重复，返回-2
int removeStu(int line)
{
    FILE *fp = NULL;
    //首先获取当前的行数
    int lines = 0;
    if(!(fp = fopen("../dbs/students","a+")))return -1;
    while(!feof(fp)){
        char ch = fgetc(fp);
        if(ch=='\n'){
            ++lines;
        }
    }
    if(line<=0||line>lines){
        //行数不对
        return -1;
    }
    char buff[1024] = {0};
    sprintf(buff,"sed -n -i '%dd;p' ../dbs/students",line);
    cout<<buff<<endl;
    system(buff);
    fclose(fp);
    puts("removeStu");
    return 0;
} //根据记录的行号删除，返回是否成功
int changeStu(int line, char *content)
{
    puts("changeStu");
    return 0;
} //根据行号覆盖修改内容，返回是否成功
map<int, int> *findStu(int col, char *keys)
{
    puts("findStu");
    return NULL;
} //查找col列的匹配keys的内容，返回行号集合

int main(void){
    // cout<<insertStu("456123-张三-02：25：66-62")<<endl;
    cout<<removeStu(2)<<endl;
    cout<<changeStu(0,"")<<endl;
    cout<<findStu(0,"")<<endl;
}