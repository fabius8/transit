LDLIBS = -lcurl -lssl -lcrypto -lz -lidn -lrt -levent
obj-app = transit
srcs = $(wildcard *.c)
srcs += $(wildcard parson/*.c)
obj-dep += $(patsubst %.c, %.o, $(srcs))

CFLAGS  += -I. -I/iniparser -I/usr/include/curl -g
LDFLAGS +=

all: build

build: $(obj-dep)
	@echo "BUILD $<"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(obj-app) $(obj-dep) $(LDLIBS)

clean:
	@rm $(obj-dep) $(obj-app)
