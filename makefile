vpath %.c source/
vpath %.h include/

CPPFLAGS += $(addprefix -I,include/) -std=c11 -g

cstring: main.o cstring.o

clean:
	rm *.o cstring
