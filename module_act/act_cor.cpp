#include "stru_cor.h"
#include "dao_cor.h"
#include <iostream>
#include <map>
#include <string.h>
using namespace std;
int coridMaker = 22222;
int getDashCnt(const char* content, char ch){
    int cnt = 0;
    for(int i = 0;i<strlen(content);++i){
        if(content[i]==ch){
            cnt++;
        }
    }
    return cnt;
}//获取某一字符串中，某一字符的出现个数
CorNode *makeCor(const char* content){
    CorNode* corp = (CorNode*)malloc(sizeof(CorNode));
    if(content==""){
        corp->id = coridMaker++;
        corp->name = "";
        corp->property = "默认";
        corp->hours = 0;
        corp->credit = 0;
        corp->choosedBy = 0;
        corp->maxChoose = 0;
        return corp;
    }
    if(getDashCnt(content,'-')!=6){
        free(corp);
        return NULL;
    }
    char *corpros[10];
    // sscanf(content,"%s-%s-%s-%s-%s-%s-%s",corpros);
    char str[100] = {0};
    strcpy(str,content);
    char *p;
	const char *delim = "-";
	p = strtok(str, delim);
    int i = 1;
	while(p) {
        corpros[i] = p;
		p = strtok(NULL, delim);
        ++i;
	}
    corp->id = atoi(corpros[1]);
    corp->name = corpros[2];
    corp->property = corpros[3];
    corp->hours = atoi(corpros[4]);
    corp->credit = atoi(corpros[5]);
    corp->choosedBy = atoi(corpros[6]);
    corp->maxChoose = atoi(corpros[7]);
    return corp;
}//通过字符串来构造课程节点指针。
CorNode *addCourse()
{
    CorNode* corp = makeCor("");
    if(corp==NULL){
        puts("对不起，现在无法添加课程");
        return NULL;
    }
    char corpros[10][50];
    puts("请输入课程名：");
    cin>>corpros[2];
    puts("请输入课程类别：");
    cin>>corpros[3];
    puts("请输入课程学时：");
    cin>>corpros[4];
    puts("请输入课程学分：");
    cin>>corpros[5];
    puts("请输入课程最大选课人数：");
    cin>>corpros[7];
    corp->name = corpros[2];
    corp->property = corpros[3];
    corp->hours = atoi(corpros[4]);
    corp->credit = atoi(corpros[5]);
    corp->maxChoose = atoi(corpros[7]);
    cout<<corp->maxChoose<<endl;
    //将课程添加到数据库
    char buff[100] = {0};
    sprintf(buff,"%d-%s-%s-%d-%d-%d-%d",
        corp->id,
        corp->name,
        corp->property,
        corp->hours,
        corp->credit,
        corp->choosedBy,
        corp->maxChoose);
    cout<<buff<<endl;
    if(insertCor(buff)==-1){
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
    cin>>corid;
    map<int,int> lines;
    int lcnt = findCorLines(1,corid,lines);
    if(lcnt<=0){
        puts("没有找到您输入的课程号，删除终止");
        return NULL;
    }else if(lcnt>1){
        puts("输入的课程号相似的找到不止一个，删除终止");
        return NULL;
    }
    const char* content = findCor(lines[1]).data();
    cout<<content<<endl;
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
