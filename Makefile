net_CC_remote: main.o net.o sendata.o list.o joy.o 
	$(CC) $(LDFLAGS) list.o joy.o net.o sendata.o main.o -o net_CC_remote
list.o: list.c
	$(CC) $(CFLAGS) -c list.c
net.o: net.c
	$(CC) $(CFLAGS) -c net.c
sendata.o: sendata.c
	$(CC) $(CFLAGS) -c sendata.c
joy.o: joy.c
	$(CC) $(CFLAGS) -c joy.c
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm *.o net_CC_remote
