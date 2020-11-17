#include <map>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
int getCorLines()
{
    FILE *fp = NULL;
    //首先获取当前的行数
    int lines = 0;
    if (!(fp = fopen("../dbs/courses", "a+")))
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
} //获取课程表的行数
int insertCor(char *content)
{
    FILE *fp = NULL;
    //首先获取当前的行数
    int lines = getCorLines();
    //不必查找是否重复，因为课程号由操作端自动分配，因此不会存在重复课程号的情况
    if (!(fp = fopen("../dbs/courses", "a+")))
        return -1;
    //格式应该也不会错，因为是操作端传过来的
    //判断末尾是否有回车
    string record = content;
    if (content[strlen(content) - 1] != '\n')
        record = record + "\n";
    const char *p = record.data();
    char buff[1024] = {0};
    sprintf(buff, "echo -n '%s' | tee -a ../dbs/courses", p);
    system(buff);
    fclose(fp);
    puts("insertCor\n----------------------------------");
    return lines + 1;
} //添加一条记录，返回行号，失败返回1。
int removeCor(int line)
{
    //首先获取当前的行数
    int lines = getCorLines();
    if (line <= 0 || line > lines)
    {
        //行数不对
        return -1;
    }
    char buff[1024] = {0};
    sprintf(buff, "sed -n -i '%dd;p' ../dbs/courses", line);
    // cout<<buff<<endl;
    system(buff);
    puts("removeCor\n----------------------------------");
    return lines - 1;
} //根据记录的行号删除，返回当前行数，失败返回-1
int changeCor(int line, char *content)
{
    //首先获取当前的行数
    int lines = getCorLines();
    if (line <= 0 || line > lines)
    {
        //行数不对
        return -1;
    }
    char buff[1024] = {0};
    //这里不用touch因为前面有获取行数，因此文件一定存在
    sprintf(buff, "sed -i '%dc %s' ../dbs/courses", line, content);
    system(buff);
    puts("changeCor\n-------------------------------");
    return lines;
} //根据行号覆盖修改内容，返回当前行数，失败返回-1
int findCorLines(int col, char *keys, map<int, int> &lines)
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
    //在操作表之前先touch一下以防不存在
    system("touch ../dbs/courses");
    sprintf(buff, "cat ../dbs/courses\
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
    puts("findCorLines\n--------------------------------");
    return lines.size();
} //查找col列的匹配keys的内容的行号到集合lines中，返回搜寻到的数量，失败返回-1。参数map必须为空

string findCor(int line)
{
    char buff[1024] = {0};
    //首先获取当前的行数
    int lines = getCorLines();
    if (line <= 0 || line > lines)
    {
        //行数不对
        return "";
    }
    //将制定行的内容写到temp.txt中
    sprintf(buff, "sed -n '%dp' ../dbs/courses > temp.txt", line);
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

int static mainDaoCor(void)
{
    // cout<<insertCor("454883-计算机网络-必修课-56-3.5-64-80")<<endl;
    // cout<<removeCor(18)<<endl;
    // cout<<changeCor(13,"456123-老王-02：25：66-62")<<endl;
    map<int, int> lines;
    // lines[555] = 666;
    cout<<findCorLines(2,"计",lines)<<endl;
    cout<<lines.size()<<endl;
    // if(findCor(lines[2]).empty()){
    //     cout<<"没找到"<<endl;
    // }else{
    //     cout<<"找到了"<<endl;
    // }
    return 0;
}
