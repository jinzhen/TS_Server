target = app
src	= $(wildcard *.c)
obj	= $(patsubst %.c, %.o, $(src))

CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	= 

$(target):$(obj)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) $< -c -o $@
clean:
	-rm -rf *.o $(target)
.PHONY:clean
