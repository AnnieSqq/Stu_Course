#include "stru_cor.h"
#include "dao_cor.h"
#include <iostream>
#include <map>
#include <string.h>
using namespace std;
int coridMaker = 22222;
int getDashCnt(const char *content, char ch)
{
    int cnt = 0;
    for (int i = 0; i < strlen(content); ++i)
    {
        if (content[i] == ch)
        {
            cnt++;
        }
    }
    return cnt;
} //获取某一字符串中，某一字符的出现个数
CorNode *makeCor(const char *content)
{
    CorNode *corp = (CorNode *)malloc(sizeof(CorNode));
    if (content == "")
    {
        map<int,int> lines;
        corp->id = findCorLines(1,"",lines) + coridMaker;
        corp->name = "";
        corp->property = "默认";
        corp->hours = 0;
        corp->credit = 0;
        corp->choosedBy = 0;
        corp->maxChoose = 0;
        return corp;
    }
    if (getDashCnt(content, '-') != 6)
    {
        free(corp);
        return NULL;
    }
    char *corpros[10];
    // sscanf(content,"%s-%s-%s-%s-%s-%s-%s",corpros);
    char str[100] = {0};
    strcpy(str, content);
    const char *delim = "-";
    char *p;
    int i = 1;
    do
    {
        p = (char *)malloc(30);
        char *tmp = strtok(i == 1 ? str : NULL, delim);
        if (tmp)
            strcpy(p, tmp);
        else
            break;
        corpros[i] = p;
        ++i;
    } while (1);
    corp->id = atoi(corpros[1]);
    corp->name = corpros[2];
    corp->property = corpros[3];
    corp->hours = atoi(corpros[4]);
    corp->credit = atoi(corpros[5]);
    corp->choosedBy = atoi(corpros[6]);
    corp->maxChoose = atoi(corpros[7]);
    return corp;
} //通过字符串来构造课程节点指针。
CorNode *addCourse()
{
    CorNode *corp = makeCor("");
    if (corp == NULL)
    {
        puts("对不起，现在无法添加课程");
        return NULL;
    }
    char corpros[10][50];
    puts("请输入课程名：");
    cin >> corpros[2];
    puts("请输入课程类别：");
    cin >> corpros[3];
    puts("请输入课程学时：");
    cin >> corpros[4];
    puts("请输入课程学分：");
    cin >> corpros[5];
    puts("请输入课程最大选课人数：");
    cin >> corpros[7];
    corp->name = corpros[2];
    corp->property = corpros[3];
    corp->hours = atoi(corpros[4]);
    corp->credit = atoi(corpros[5]);
    corp->maxChoose = atoi(corpros[7]);
    cout << corp->maxChoose << endl;
    //将课程添加到数据库
    char buff[100] = {0};
    sprintf(buff, "%d-%s-%s-%d-%d-%d-%d",
            corp->id,
            corp->name,
            corp->property,
            corp->hours,
            corp->credit,
            corp->choosedBy,
            corp->maxChoose);
    cout << buff << endl;
    if (insertCor(buff) == -1)
    {
        free(corp);
        return NULL;
    }
    puts("addCourse");
    return corp;
} //添加一个课程，命令行询问课程信息，返回添加的课程
CorNode *deleteCourse()
{
    char corid[50] = {0};
    puts("请输入要删除的课程号");
    cin >> corid;
    map<int, int> lines;
    int lcnt = findCorLines(1, corid, lines);
    cout << lines.size() << endl;
    if (lcnt <= 0)
    {
        puts("没有找到您输入的课程号，删除终止");
        return NULL;
    }
    else if (lcnt > 1)
    {
        puts("输入的课程号相似的找到不止一个，删除终止");
        return NULL;
    }
    puts("您想要删除的课程是：");
    cout << findCor(lines[1]) << endl;
    puts("您确定要删除这个课程吗：(y/n)");
    string check;
    cin >> check;
    if (check != "y" && check != "Y" && check != "yes")
    {
        puts("删除取消");
        return NULL;
    }
    CorNode *corp = makeCor(findCor(lines[1]).data());
    if (removeCor(lines[1]) < 0)
    {
        puts("删除失败");
        return NULL;
    }
    puts("deleteCourse");
    return corp;
} //根据id删除课程，返回删除的课程，失败返回0
CorNode *modifyCourse()
{
    char corid[50] = {0};
    puts("请输入要修改的课程号");
    cin >> corid;
    map<int, int> lines;
    int lcnt = findCorLines(1, corid, lines);
    cout << lines.size() << endl;
    if (lcnt <= 0)
    {
        puts("没有找到您输入的课程号，修改终止");
        return NULL;
    }
    else if (lcnt > 1)
    {
        puts("输入的课程号相似的找到不止一个，修改终止");
        return NULL;
    }
    CorNode *corp = makeCor(findCor(lines[1]).data());
    string input;
    printf("课程名（输入\"u\"保持不变）（%s）：", corp->name);
    cin >> input;
    cout << input << endl;
    if (input != "u")
    {
        strcpy(corp->name, input.data());
    }
    printf("课程类型（输入\"u\"保持不变）（%s）：", corp->property);
    cin >> input;
    cout << input << endl;
    if (input != "u")
    {
        strcpy(corp->property, input.data());
    }
    printf("课程学时（输入\"u\"保持不变）（%d）：", corp->hours);
    cin >> input;
    cout << input << endl;
    if (input != "u")
    {
        corp->hours = atoi(input.data()) >= 0 ? atoi(input.data()) : corp->hours;
    }
    printf("课程学分（输入\"u\"保持不变）（%d）：", corp->credit);
    cin >> input;
    cout << input << endl;
    if (input != "u")
    {
        corp->credit = atoi(input.data()) >= 0 ? atoi(input.data()) : corp->credit;
    }
    printf("课程最大选课人数（输入\"u\"保持不变）（%d）：", corp->maxChoose);
    cin >> input;
    cout << input << endl;
    if (input != "u")
    {
        corp->maxChoose = atoi(input.data()) >= 0 ? atoi(input.data()) : corp->maxChoose;
    }
    //将课程修改到数据库
    char buff[100] = {0};
    sprintf(buff, "%d-%s-%s-%d-%d-%d-%d",
            corp->id,
            corp->name,
            corp->property,
            corp->hours,
            corp->credit,
            corp->choosedBy,
            corp->maxChoose);
    cout << buff << endl;
    if (changeCor(lines[1], buff) == -1)
    {
        puts("修改失败");
        free(corp);
        return NULL;
    }
    puts("modifyCourse");
    return corp;
} //根据id修改课程，命令行询问修改项目，返回修改后的，失败返回0
CorNode *lookCourse()
{
    puts("请输入要查看的课程(课程号或课程名)：");
    string corkey;
    cin >> corkey;
    map<int, int> corlines;
    //如果输入的是以不为零的数字开头，则在课程号中找，否则在课程名中查找
    int col = atoi(corkey.data()) == 0 ? 2 : 1;
    if(findCorLines(col, corkey.data(), corlines)<=0){
        puts("没找到");
        return NULL;
    }
    printf("课程编号\t课程名称\t课程类型\t课程学时\t课程学分\t已选人数\t最大人数\n");
    for(int i = 1;i<=corlines.size();++i){
        CorNode *corp = makeCor(findCor(corlines[i]).data());
        printf("%10d\t%8s\t%8s\t%10d\t%10d\t%10d\t%10d\n",
            corp->id,
            corp->name,
            corp->property,
            corp->hours,
            corp->credit,
            corp->choosedBy,
            corp->maxChoose
        );
        free(corp);
    }
    puts("lookCourse");
    return NULL;
} //根据id查看课程，命令行打出，返回课程。失败返回0
int listCourses()
{
    map<int, int> corlines;
    //如果输入的是以不为零的数字开头，则在课程号中找，否则在课程名中查找
    if(findCorLines(1, "", corlines)<=0){
        puts("没有");
        return 0;
    }
    printf("课程编号\t课程名称\t课程类型\t课程学时\t课程学分\t已选人数\t最大人数\n");
    for(int i = 1;i<=corlines.size();++i){
        CorNode *corp = makeCor(findCor(corlines[i]).data());
        printf("%10d\t%10s\t%10s\t%10d\t%10d\t%10d\t%10d\n",
            corp->id,
            corp->name,
            corp->property,
            corp->hours,
            corp->credit,
            corp->choosedBy,
            corp->maxChoose
        );
    }
    puts("listCourse");
    return 0;
} //列出所有课程，返回课程数量，异常返回-1
