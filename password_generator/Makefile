
TARGET = gen_password.elf

CFLAGS += -I$(SDKSTAGE)/usr/include/

LDFLAGS += -L$(SDKSTAGE)/usr/lib/ 
LDFLAGS += -lc -lpthread -lcrypt

SRC = 
SRC += gen_password.c

include Makefile.include
