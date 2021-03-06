#include "stru_cor.h"
#ifndef MYPROJECT_ACT_COR_H
#define MYPROJECT_ACT_COR_H
int getDashCnt(const char *content, char ch);
CorNode *makeCor(const char *content);
CorNode *addCourse();//添加一个课程，命令行询问课程信息，返回添加的课程
CorNode *deleteCourse();//根据id删除课程，返回删除的课程，失败返回0
CorNode *modifyCourse();//根据id删除课程，返回删除的课程，失败返回0
CorNode *lookCourse();//根据id查看课程，命令行打出，返回课程。失败返回0
int listCourses();//列出所有课程，返回课程数量，异常返回-1
#endif
