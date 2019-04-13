
SRC_PATH	= ./src
DIRS		= $(shell find $(SRC_PATH) -maxdepth 4 -type d) 
SOURCE		+= $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
DEMO_PATH	= ./demo
OBJECT		= $(subst .c,.o,$(SOURCE))

INCLUDE		= -I./inc -I./src

BUILD		= ./build

TARGET_LIB	= $(BUILD)/lib/liblist.a

default: libstatic test

libstatic:$(OBJECT)
	$(AR) rcs $(TARGET_LIB) $(OBJECT)

$(OBJECT):%.o:%.c
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $< 

test:
	make -C $(DEMO_PATH) 

clean:
	-rm $(OBJECT)
	-rm $(TARGET_LIB)
	cd $(DEMO_PATH);make clean

tag:
	ctags -R *

.PHONY:default libstatic test clean
