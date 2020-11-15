#include "stru_cor.h"
#include "dao_cor.h"
#include <iostream>
CorNode *addCourse()
{
    puts("addCourse");
    insertCor("");
    return NULL;
} //添加一个课程，命令行询问课程信息，返回添加的课程
CorNode *deleteCourse(int id)
{
    puts("deleteCourse");
    return NULL;
} //根据id删除课程，返回删除的课程，失败返回0
CorNode *modifyCourse(int id)
{
    puts("modifyCourse");
    return NULL;
} //根据id修改课程，命令行询问修改项目，返回修改后的，失败返回0
CorNode *lookCourse(int id)
{
    puts("lookCourse");
    return NULL;
} //根据id查看课程，命令行打出，返回课程。失败返回0
int listCourses()
{
    puts("listCourse");
    return 0;
} //列出所有课程，返回课程数量，异常返回-1
