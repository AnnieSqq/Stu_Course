CFLAGS  = -I ../includes
VPATH = ../includes
all:dao_cor.o dao_stu.o

%.o:%.cpp
	g++ $(CFLAGS) -c $^ -o ../temp/$@
.PHONY:clean
clean:
	$(RM) ../temp/*.o