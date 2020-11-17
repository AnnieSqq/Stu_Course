#include <map>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
int getStuLines()
{
    FILE *fp = NULL;
    //首先获取当前的行数
    int lines = 0;
    if (!(fp = fopen("dbs/students", "a+")))
        return -1;
    while (!feof(fp))
    {
        char ch = fgetc(fp);
        if (ch == '\n')
        {
            ++lines;
        }
    }
    fclose(fp);
    return lines;
} //获取学生表的行数
int insertStu(char *content)
{
    FILE *fp = NULL;
    //首先获取当前的行数
    int lines = getStuLines();
    //不必查找是否重复，因为学号由操作端自动分配，因此不会存在重复学号的情况
    if (!(fp = fopen("dbs/students", "a+")))
        return -1;
    //格式应该也不会错，因为是操作端传过来的
    //判断末尾是否有回车
    string record = content;
    if (content[strlen(content) - 1] != '\n')
        record = record + "\n";
    const char *p = record.data();
    char buff[1024] = {0};
    sprintf(buff, "echo -n '%s' | tee -a dbs/students", p);
    system(buff);
    fclose(fp);
    puts("insertStu\n----------------------------------");
    return lines + 1;
} //添加一条记录，返回行号，失败返回1。如果添加重复，返回-2
int removeStu(int line)
{
    //首先获取当前的行数
    int lines = getStuLines();
    if (line <= 0 || line > lines)
    {
        //行数不对
        return -1;
    }
    char buff[1024] = {0};
    sprintf(buff, "sed -n -i '%dd;p' dbs/students", line);
    // cout<<buff<<endl;
    system(buff);
    puts("removeStu\n----------------------------------");
    return lines - 1;
} //根据记录的行号删除，返回当前行数，失败返回-1
int changeStu(int line, char *content)
{
    //首先获取当前的行数
    int lines = getStuLines();
    if (line <= 0 || line > lines)
    {
        //行数不对
        return -1;
    }
    char buff[1024] = {0};
    // cout<<content<<endl;
    sprintf(buff, "sed -i '%dc %s' dbs/students", line, content);
    system(buff);
    // cout<<buff<<endl;
    puts("changeStu\n-------------------------------");
    return lines;
} //根据行号覆盖修改内容，返回当前行数，失败返回-1
int findStuLines(int col, char *keys, map<int, int> &lines)
{
    //如果传入的map不为空，也失败
    if (!lines.empty())
    {
        return -1;
    }
    //如果栏位不对，也失败
    if (col <= 0 || col > 4)
    {
        return -1;
    }
    char buff[1024] = {0};
    sprintf(buff, "cat dbs/students\
           |awk -F '-' '{print $%d}'\
           |grep -n '%s'\
           |awk -F ':' '{print $1}' > temp.txt",
            col, keys);
    system(buff);
    //开始读取搜索到的行文件
    FILE *fp = NULL;
    if ((fp = fopen("temp.txt", "r")) == NULL)
        return -1;
    //按行读取
    int line = 0, i = 1;
    while (fgets(buff, 1023, fp))
    {
        cout << buff;
        if (!(line = atoi(buff)))
            return -1;
        lines[i++] = line;
    }
    //删除文件temp.txt
    system("rm -f temp.txt");
    fclose(fp);
    puts("findStuLines\n--------------------------------");
    return lines.size();
} //查找col列的匹配keys的内容的行号到集合lines中，返回搜寻到的数量，失败返回-1。参数map必须为空

string findStu(int line)
{
    char buff[1024] = {0};
    //首先获取当前的行数
    int lines = getStuLines();
    if (line <= 0 || line > lines)
    {
        //行数不对
        return "";
    }
    //将制定行的内容写到temp.txt中
    sprintf(buff, "sed -n '%dp' dbs/students > temp.txt", line);
    system(buff);
    //读取获取到的那一行的内容
    FILE *fp = NULL;
    if (!(fp = fopen("temp.txt", "r")))
        return "";
    fgets(buff, 1023, fp);
    fclose(fp);
    //结尾有换行符，影响操作，因此将换行符去掉
    if (buff[strlen(buff) - 1] == '\n')
        buff[strlen(buff) - 1] = '\0';
    //删除文件temp.txt
    system("rm -f temp.txt");
    string res = buff;
    return res;
} //根据行号返回该行的内容，失败返回空串

int static mainDaoStu(void)
{
    // cout<<insertStu("456123-小红-02：25：66-62")<<endl;
    // cout<<removeStu(18)<<endl;
    // cout<<changeStu(13,"456123-老王-02：25：66-62")<<endl;
    map<int, int> lines;
    // lines[555] = 666;
    cout<<findStuLines(2,"王",lines)<<endl;
    cout<<lines.size()<<endl;
    // if(findStu(lines[2]).empty()){
    //     cout<<"没找到"<<endl;
    // }else{
    //     cout<<"找到了"<<endl;
    // }
    return 0;
}
