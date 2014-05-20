LD=-Wall -ljansson
LG=-g
CO=get_jans.o  str_type_jansson.o object_iter_jansson.o
all:run 
run:$(CO)
	gcc $(CO) $(LD) -o run $(LG)
%.o:%.c
	gcc -c $< -o $@ $(LG)
clean::
	rm -f *.o run


