.PHONY : all 51 clean

all :
	#gcc -O2 -Wall --shared -o protobuf.dll -I../.. -I/usr/local/include -L/usr/local/bin -L../../build pbc-lua.c -lpbc -llua52

51 :
	gcc -g3 -Wall --shared -o protobuf.so -I../.. -L../../build pbc-lua.c -lpbc -llua
#	gcc -O2 -Wall --shared -o protobuf.dll -I../.. -I/d/project/luajit-2.0/src -L/usr/local/bin -L../../build pbc-lua.c -lpbc -llua51
#	gcc -O2 -Wall --shared -o protobuf.dll -I../.. -I/d/project/lua-5.1.4/src -L/usr/local/bin -L../../build pbc-lua.c -lpbc -llua51

jit :
	gcc -g3 -Wall --shared -o protobuf.so -I../.. -L../../build pbc-lua.c -lpbc -lluajit-5.1

clean :
#	rm protobuf.dll
	rm protobuf.so
