CC =g++
FLAG =-std=c++0x

src = $(wildcard *.cpp)
obj = $(src:.c = .o)

a: $(obj)
	$(CC) $(FLAG) $^
