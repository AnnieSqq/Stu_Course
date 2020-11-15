#ifndef MYPROJECT_STRU_COR_H
#define MYPROJECT_STRU_COR_H
struct course{
      int id;//课程号
      char *name;//课程名
      char *property;///课程性质
      int hours;//课程学时
      int credit;//课程学分
      int choosedBy;//已选人数
      int maxChoose;//最大选课人数
};
typedef struct course CorNode;
typedef CorNode* Corp;
#endif
