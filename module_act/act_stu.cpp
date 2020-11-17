#include "stru_stu.h"
#include "dao_stu.h"
#include "dao_cor.h"
#include <iostream>
#include <string.h>
int stuidMaker = 11111;
StuNode *makeStu(const char* content);//通过字符串来构造学生节点指针。
StuNode *addStu()
{
    string content = "" + to_string(stuidMaker);
    cout<<"content"<<content<<endl;
    string name = "";
    puts("请输入姓名：");
    cin >> name;
    content = content + "-" + name;
    string corkey = "";
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

        //将获取到的课程行的课程号截取出来
        int colid;
        cout<<"atoi:"<<(char *)findCor(corlines[atoi(cornum.data())]).data()<<endl;
        sscanf(findCor(corlines[atoi(cornum.data())]).data(),"%d",&colid);
        cout<<"colid:"<<colid<<endl;
        content = content + "-" + to_string(colid);
    }
    puts("addStu");
    return NULL;
} //添加一个课程，命令行询问课程信息，返回添加的课程
StuNode *deleteStu(int id)
{
    puts("deleteStu");
    return NULL;
} //根据id删除课程，返回删除的课程，失败返回0
StuNode *modifyStu(int id)
{
    puts("modifyStu");
    return NULL;
} //根据id修改课程，命令行询问修改项目，返回修改后的，失败返回0
StuNode *lookStuById(int id)
{
    puts("lookStuById");
    return NULL;
} //根据id查看课程，命令行打出，返回课程。失败返回0
int lookStuByName(char *name)
{
    puts("lookStuByName");
    return 0;
} //根据姓名查看学生，返回学生数量，并打印信息
int listStu()
{
    puts("listStu");
    return 0;
} //列出所有课程，返回课程数量，异常返回-1
