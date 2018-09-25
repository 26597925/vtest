CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -Os -Wall -D _XOPEN_SOURCE 
LDFLAGS = -ldl

OUTPUT = bin

SRC = src

SOURCES = $(wildcard $(SRC)/*/*.c)
#OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
#http://bbs.chinaunix.net/thread-1692258-1-1.html
#OBJS_NAME = $(notdir $(patsubst %.c,%.o,$(SOURCES)))
OBJS = $(addprefix $(OUTPUT)/,$(notdir $(patsubst %.c,%.o,$(SOURCES))))

TARGET = bin/vpeer

CFLAGS += `pkg-config --cflags glib-2.0`
LDFLAGS += `pkg-config --libs glib-2.0`

all: $(TARGET)

$(TARGET):$(OUTPUT) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)
$(OBJS):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ -c $(filter %$(*F).c,$(SOURCES))
#$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)
install:
	cp $(TARGET) /usr/bin 
uninstall:  
	rm -rf /usr/bin/$(TARGET)