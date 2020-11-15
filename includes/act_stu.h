#include "stru_stu.h"
#ifndef MYPROJECT_ACT_STU_H
#define MYPROJECT_ACT_STU_H
StuNode *addStu();             //添加一个学生，命令行询问学生信息，返回添加的学生，失败返回0
StuNode *deleteStu(int id);    //根据学号删除，返回被删除的学生。失败返回0
StuNode *modifyStu(int id);    //根据id修改学生信息，命令行形式询问修改的值
StuNode *lookStuById(int id);  //根据id查看学生，返回学生，打印学生
int lookStuByName(char *name); //根据姓名查看学生，返回学生数量，并打印信息
int listStus();                //列出所有学生，返回学生数量，异常返回-1
#endif
