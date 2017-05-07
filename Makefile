net_CC_remote: ./build/main.o ./build/net.o ./build/sendata.o ./build/list.o ./build/joy.o 
	cc ./build/list.o ./build/joy.o ./build/net.o ./build/sendata.o ./build/main.o -o net_CC_remote
./build/list.o: ./src/list.c ./include/includes.h
	cc -c ./src/list.c -o ./build/list.o
./build/net.o: ./src/net.c ./include/includes.h
	cc -c ./src/net.c -o ./build/net.o
./build/sendata.o: ./src/sendata.c ./include/includes.h
	cc -c ./src/sendata.c -o ./build/sendata.o
./build/joy.o: ./src/joy.c ./include/includes.h
	cc -c ./src/joy.c -o ./build/joy.o
./build/main.o: ./src/main.c ./include/includes.h
	cc -c ./src/main.c -o ./build/main.o

clean:
	rm ./build/*.o net_CC_remote
