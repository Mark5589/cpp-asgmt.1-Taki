CC =g++
FLAG =-std=c++11

src = $(wildcard *.cpp)
obj = $(src:.c = .o)

myprog: $(obj)
	$(CC) $(FLAG) -o $@ $^
