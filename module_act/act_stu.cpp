#include "stru_stu.h"
#include "dao_stu.h"
#include <iostream>
StuNode *addStu()
{
    puts("addStu");
    insertStu("");
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
