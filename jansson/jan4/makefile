LD=-Wall -ljansson
LG=-g
CO=policyjans.o
all:run 
run:$(CO)
	gcc $(CO) $(LD) -o run $(LG)
%.o:%.c
	gcc -c $< -o $@ $(LG)
clean::
	rm -f *.o run


