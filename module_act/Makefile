CFLAGS  = -I ../includes
VPATH = ../includes

all: act_cor.o act_stu.o

%.o:%.cpp
	g++ $(CFLAGS) -c $^ -o ../temp/$@