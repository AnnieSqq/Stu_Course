CFLAGS  = -I ../includes
VPATH = ../includes
all:dao_cor.o dao_stu.o
	mkdir ../dbs || exit 0
%.o:%.cpp
	mkdir ../temp || exit 0
	g++ $(CFLAGS) -c $^ -o ../temp/$@
.PHONY:clean
clean:
	$(RM) ../temp/*.o