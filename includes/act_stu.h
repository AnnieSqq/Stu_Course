#include "stru_stu.h"
#ifndef MYPROJECT_ACT_STU_H
#define MYPROJECT_ACT_STU_H
StuNode *makeStu(const char* content);
StuNode *addStu();             //添加一个学生，命令行询问学生信息，返回添加的学生，失败返回0
StuNode *deleteStu();    //根据学号删除，返回被删除的学生。失败返回0
StuNode *modifyStu();    //根据id修改学生信息，命令行形式询问修改的值
StuNode *lookStu();  //根据id查看学生，返回学生，打印学生
int listStus();                //列出所有学生，返回学生数量，异常返回-1
#endif
