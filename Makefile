
OBJS=main.o util.o
SRCS=$(OBJS:%.0=%.c)
CFLAGS=-g -Wall
LDLIBS=
TARGET=pman
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)
