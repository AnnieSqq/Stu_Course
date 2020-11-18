#include "stru_stu.h"
#include "dao_stu.h"
#include "dao_cor.h"
#include <iostream>
#include <string.h>
#include "stru_cor.h"
#include "act_cor.h"
using namespace std;
int stuidMaker = 11111;
StuNode *makeStu(const char *content)
{
    StuNode *stup = (StuNode *)malloc(sizeof(StuNode));
    if (content == "")
    {
        map<int,int> lines;
        stup->id = findStuLines(1,"",lines) + stuidMaker;
        stup->name = "";
        stup->choose = {0};
        stup->allCredit = 0;
        stup->choosecnt = 0;
        return stup;
    }
    if (getDashCnt(content, '-') != 4)
    {
        free(stup);
        return NULL;
    }
    char *stupros[10];
    // sscanf(content,"%s-%s-%s-%s-%s-%s-%s",stupros);
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
        stupros[i] = p;
        ++i;
    } while (1);
    stup->id = atoi(stupros[1]);
    stup->name = stupros[2];
    stup->choose = {0};
    //处理选课数组
    strcpy(str, stupros[3]);
    int *cp;
    int clen = getDashCnt(stupros[3], ':') + 1;
    i = 1;
    cp = (int *)malloc(sizeof(int) * 20);
    do
    {
        char *tmp = strtok(i == 1 ? str : NULL, ":");
        if (!tmp)
            break;
        cp[i] = atoi(tmp);
        ++i;
    } while (1);
    stup->choose = cp;
    stup->allCredit = atoi(stupros[4]);
    stup->choosecnt = clen;
    return stup;
} //通过字符串来构造学生节点指针。
StuNode *addStu()
{
    char stupros[10][50];
    puts("请输入姓名：");
    cin >> stupros[1];
    string corkey = "";
    char chooses[50] = "";
    int credits = 0;
    int clen = 0;
    while (1)
    {
        puts("请输入已选课程号或关键词，结束请输入#号：");
        cin >> corkey;
        if (corkey == "#")
        {
            break;
        }
        map<int, int> corlines;
        //如果输入的是以不为零的数字开头，则在课程号中找，否则在课程名中查找
        int col = atoi(corkey.data()) == 0 ? 2 : 1;
        findCorLines(col, corkey.data(), corlines);
        // cout<<"size："<<corlines.size()<<endl;
        if (corlines.size() < 1)
        {
            puts("没找到类似的课程哦！");
            continue;
        }
        puts("你要找的是以下哪个？");
        string cornum = "";
        for (int i = 1; i <= corlines.size(); ++i)
        {
            cout << i << "：" << findCor(corlines[i]) << endl;
        }
        puts("请输入序号，都不是请输入0");
        cin >> cornum;
        if (atoi(cornum.data()) <= 0 || atoi(cornum.data()) > corlines.size())
        {
            puts("下一个");
            continue;
        }

        CorNode *corp = makeCor(findCor(corlines[atoi(cornum.data())]).data());
        strcat(chooses, (to_string(corp->id) + ":").data());
        credits += corp->credit;
        clen++;
        free(corp);
    }
    //去除末尾冒号
    if (chooses[strlen(chooses) - 1] == ':')
    {
        chooses[strlen(chooses) - 1] = '\0';
    }
    cout << chooses << endl;
    cout << credits << endl;
    StuNode *stup = makeStu("");
    char buff[1024] = {0};
    sprintf(buff, "%d-%s-%s-%d-%d", stup->id, stupros[1], chooses, credits, clen);
    cout << buff << endl;
    free(stup);
    stup = makeStu(buff);
    if (insertStu(buff) == -1)
    {
        free(stup);
        return NULL;
    }
    puts("addStu");
    return stup;
} //添加一个课程，命令行询问课程信息，返回添加的课程
StuNode *deleteStu()
{
    char stuid[50] = {0};
    puts("请输入要删除的学生号");
    cin >> stuid;
    map<int, int> lines;
    int lcnt = findStuLines(1, stuid, lines);
    cout << lines.size() << endl;
    if (lcnt <= 0)
    {
        puts("没有找到您输入的学生号，删除终止");
        return NULL;
    }
    else if (lcnt > 1)
    {
        puts("输入的学生号相似的找到不止一个，删除终止");
        return NULL;
    }
    puts("您想要删除的学生是：");
    cout << findStu(lines[1]) << endl;
    puts("您确定要删除这个学生吗：(y/n)");
    string check;
    cin >> check;
    if (check != "y" && check != "Y" && check != "yes")
    {
        puts("删除取消");
        return NULL;
    }
    StuNode *stup = makeStu(findStu(lines[1]).data());
    if (removeStu(lines[1]) < 0)
    {
        puts("删除失败");
        return NULL;
    }
    puts("deleteStu");
    return stup;
} //根据id删除学生，返回删除的学生，失败返回0
StuNode *modifyStu()
{
    char stuid[50] = {0};
    puts("请输入要修改的学生号");
    cin >> stuid;
    map<int, int> lines;
    int lcnt = findStuLines(1, stuid, lines);
    cout << lines.size() << endl;
    if (lcnt <= 0)
    {
        puts("没有找到您输入的学号，修改终止");
        return NULL;
    }
    else if (lcnt > 1)
    {
        puts("输入的学号相似的找到不止一个，修改终止");
        return NULL;
    }
    StuNode *stup = makeStu(findStu(lines[1]).data());

    string input;
    printf("学生姓名（输入\"u\"保持不变）（%s）：", stup->name);
    cin >> input;
    cout << input << endl;
    if (input != "u")
    {
        strcpy(stup->name, input.data());
    }
    string corkey = "";
    char chooses[50] = "";
    int credits = 0;
    //初始化chooses
    for (int i = 1; i <= stup->choosecnt; ++i)
    {
        strcat(chooses, (to_string(stup->choose[i]) + ":").data());
    }

    while (1)
    {
        puts("请输入添加的选课程号或关键词，结束请输入#号：");
        cin >> corkey;
        if (corkey == "#")
        {
            break;
        }
        map<int, int> corlines;
        //如果输入的是以不为零的数字开头，则在课程号中找，否则在课程名中查找
        int col = atoi(corkey.data()) == 0 ? 2 : 1;
        findCorLines(col, corkey.data(), corlines);
        // cout<<"size："<<corlines.size()<<endl;
        if (corlines.size() < 1)
        {
            puts("没找到类似的课程哦！");
            continue;
        }
        puts("你要找的是以下哪个？");
        string cornum = "";
        for (int i = 1; i <= corlines.size(); ++i)
        {
            cout << i << "：" << findCor(corlines[i]) << endl;
        }
        puts("请输入序号，都不是请输入0");
        cin >> cornum;
        if (atoi(cornum.data()) <= 0 || atoi(cornum.data()) > corlines.size())
        {
            puts("下一个");
            continue;
        }

        CorNode *corp = makeCor(findCor(corlines[atoi(cornum.data())]).data());
        strcat(chooses, (to_string(corp->id) + ":").data());
        stup->allCredit += corp->credit;
        stup->choosecnt++;
        stup->choose[stup->choosecnt] = corp->id;
        free(corp);
    }
    //去除末尾空格
    if (chooses[strlen(chooses) - 1] == ':')
    {
        chooses[strlen(chooses) - 1] = '\0';
    }
    //将学生修改到数据库
    char buff[100] = {0};
    sprintf(buff, "%d-%s-%s-%d-%d",
            stup->id,
            stup->name,
            chooses,
            stup->allCredit,
            stup->choosecnt);
    cout << buff << endl;
    if (changeStu(lines[1], buff) == -1)
    {
        puts("修改失败");
        free(stup);
        return NULL;
    }
    puts("modifyStu");
    return stup;
} //修改学生，命令行询问修改项目，返回修改后的，失败返回0
StuNode *lookStu()
{

    puts("请输入要查看的学生(学生编号或学生姓名)：");
    string stukey;
    cin >> stukey;
    map<int, int> stulines;
    //如果输入的是以不为零的数字开头，则在学生号中找，否则在学生名中查找
    int col = atoi(stukey.data()) == 0 ? 2 : 1;
    if (findStuLines(col, stukey.data(), stulines) <= 0)
    {
        puts("没找到");
        return NULL;
    }
    printf("学生编号\t学生姓名\t选课列表\n");
    for (int i = 1; i <= stulines.size(); ++i)
    {
        StuNode *stup = makeStu(findStu(stulines[i]).data());
        printf("%10d\t%8s\t",
               stup->id,
               stup->name);

        for (int i = 1; i <= stup->choosecnt; ++i)
        {
            map<int, int> lines;
            if (findCorLines(1, to_string(stup->choose[i]).data(), lines) == 1)
            {
                CorNode *corp = makeCor(findCor(lines[1]).data());
                printf("%8s\t", corp->name);
                free(corp);
            }
        }
        puts("");
        free(stup);
    }
    puts("lookStu");
    return NULL;
} //根据查看学生，命令行打出，返回学生。失败返回0

int listStus()
{
    map<int, int> stulines;
    if (findStuLines(1, "", stulines) <= 0)
    {
        puts("没有");
        return NULL;
    }
    printf("学生编号\t学生姓名\t选课列表\n");
    for (int i = 1; i <= stulines.size(); ++i)
    {
        StuNode *stup = makeStu(findStu(stulines[i]).data());
        printf("%10d\t%8s\t",
               stup->id,
               stup->name);

        for (int i = 1; i <= stup->choosecnt; ++i)
        {
            map<int, int> lines;
            if (findCorLines(1, to_string(stup->choose[i]).data(), lines) == 1)
            {
                CorNode *corp = makeCor(findCor(lines[1]).data());
                printf("%8s\t", corp->name);
                free(corp);
            }
        }
        puts("");
        free(stup);
    }
    puts("listStu");
    return 0;
} //列出所有学生，返回学生数量，异常返回-1
