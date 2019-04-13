#Makefile for Demo

BUILD		= ../build
MODULE		= list
TARGET 		= $(BUILD)/bin/$(MODULE)_demo
LIBS		= -L $(BUILD)/lib/ \
			  -llist

INCLUDE		= -I ../src

SOURCE		= main.o

.PHONY: all clean
all:$(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(INCLUDE) $(LIBS) 

$(SOURCE):%.o:%.c
	$(CC) $(INCLUDE) -c -o $@ $<

clean:
	-@rm *.o
