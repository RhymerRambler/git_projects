OBJS = my_string.o my_string_wrap.o

mystring.so: $(OBJS)
	g++ -o my_string.so -shared $(OBJS)
    
mystring_main: $(OBJS) main.o
	g++ -o mystring_main $(OBJS) main.o -L/usr/lib/x86_64-linux-gnu/ -ltcl8.6

main.o: main.cpp
	g++ -c -I/usr/include/tcl8.6 main.cpp

my_string_wrap.cpp: my_string.i
	swig -c++ -tcl8 -o my_string_wrap.cpp my_string.i

my_string_wrap.o: my_string_wrap.cpp
	g++ -fPIC -std=c++11 -c my_string_wrap.cpp -I/usr/include/tcl8.6

my_string.o: my_string.cpp
	g++ -fPIC -std=c++11 -c my_string.cpp

clean:
	rm -f *.o *.so mystring_main my_string_wrap.cpp
