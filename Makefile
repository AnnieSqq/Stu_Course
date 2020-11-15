CFLAGS  = -I includes
VPATH = includes:temp

all:main.out

main.out: main.o lib #act_cor.o act_stu.o dao_cor.o dao_stu.o
	mkdir release || exit 0
	g++ temp/*.o -o release/$@ -lstdc++

lib:
	make -C module_dao
	make -C module_act

main.o: main.cpp
	mkdir temp || exit 0
	g++ $(CFLAGS) -c $^ -o temp/$@

,PHONY:clean
clean:
	$(RM) temp/*.o release/*.out