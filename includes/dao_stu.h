int insertStu(char* content);//添加一条记录，返回行号，失败返回0
int removeStu(int line);//根据记录的行号删除，返回是否成功
int changeStu(int line,char* content);//根据行号覆盖修改内容，返回是否成功
int* findStu(int col,char* keys);//查找col列的匹配keys的内容，返回行号集合
