#ifndef MYPROJECT_STRU_STU_H
#define MYPROJECT_STRU_STU_H
struct student{
    int id;//学号
    char *name;//姓名
    int *choose;//已选课程号数组
    int allCredit;//总学分
};
typedef struct student StuNode;
typedef StuNode* Stup;
#endif
