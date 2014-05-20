#LD=-Wall -lssl -ldl -pthread
LD=-Wall -lssl -ldl -pthread -lcurl -ljansson
CO1=state_cpu.o state_memory.o state_net.o state_disk.o computerstate.o
CO2=seekkey.o judgeftype.o my_syslog.o event.o tool.o 
CO3=filenamelog.o ssl_client.o 
CO4=acsmx.o matchjans.o policyjans.o
CO=$(CO1) $(CO2) $(CO3) $(CO4)
LG=-g
all:cli rewritekey
cli:$(CO)
	gcc $(CO) $(LD) -o cli $(LG)
%.o:%.c
	gcc -c $< -o $@ $(LG)

rewritekey:rewritekey.o
	gcc rewritekey.o -o rewritekey
rewritekey.o:rewritekey.c
	gcc -c rewritekey.c
clean::
	rm -f *.o cli rewritekey
