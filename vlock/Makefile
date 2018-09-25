CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -Os
LDFLAGS =

OUTPUT = bin

SRC = src

SOURCES = $(wildcard $(SRC)/*.c)
#OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
#http://bbs.chinaunix.net/thread-1692258-1-1.html
#OBJS_NAME = $(notdir $(patsubst %.c,%.o,$(SOURCES)))
OBJS = $(addprefix $(OUTPUT)/,$(notdir $(patsubst %.c,%.o,$(SOURCES))))

TARGET = bin/vlock

CFLAGS += `pkg-config --cflags glib-2.0`
LDFLAGS += `pkg-config --libs glib-2.0` -lpcre

#libcurl
LIBCURL_STATICLIB :=  lib/libcurl.a
LIBCURL_INC :=  lib/libcurl/include

all : libcurl

.PHONY : libcurl

CURL_STATICLIB := $(LIBCURL_STATICLIB)

$(LIBCURL_STATICLIB):lib/libcurl/Makefile
	cd lib/libcurl && $(MAKE) CC=$(CC)
	cp lib/libcurl/lib/.libs/libcurl.a lib

lib/libcurl/buildconf:
	cd lib/libcurl && ./configure
	
lib/libcurl/Makefile: | lib/libcurl/buildconf
	cd lib/libcurl && ./buildconf

libcurl : $(CURL_STATICLIB)

#libcurl

#libopenssl
LIBOPENSSL_STATICLIB :=  lib/libssl.a
LIBCURL_INC :=  lib/libopenssl/include

all : libopenssl

.PHONY : libopenssl

OPENSSL_STATICLIB := $(LIBOPENSSL_STATICLIB)

$(LIBOPENSSL_STATICLIB):lib/libopenssl/Makefile
	cd lib/libopenssl && $(MAKE) CC=$(CC)
	cp lib/libopenssl/libssl.a lib

lib/libcurl/buildconf:
	cd lib/libcurl && ./configure
	
lib/libcurl/Makefile: | lib/libcurl/buildconf
	cd lib/libcurl && ./config

libopenssl : $(OPENSSL_STATICLIB)

#libopenssl

LDFLAGS += $(OPENSSL_STATICLIB) -lcrypto

LDFLAGS += $(CURL_STATICLIB) -lz -lrt -lm

all: $(TARGET)

$(TARGET):$(OUTPUT) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)
$(OBJS):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ -c -g $(filter %$(*F).c,$(SOURCES)) -I$(LIBCURL_INC)
#$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)
install:
	cp $(TARGET) /usr/bin 
uninstall:  
	rm -rf /usr/bin/$(TARGET)