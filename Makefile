export CFLAGS = -I./
export LDLIBS = -lcurl -lssl -lcrypto -lz -lidn -lrt

obj-app = transit
srcs = $(wildcard *.c)
srcs += $(wildcard parson/*.c)
#obj-dep += $(APP_COMMON)/nvram_flash.o daemon.o dhcphotbackup.o
obj-dep += $(patsubst %.c, %.o, $(srcs))
#obj-dep += $(APP_COMMON)/nvram_flash.o

###############################################################
# X86 start
###############################################################
ifeq ($(BOARD_TYPE),GW_X86)
LIB_SUBDIR=x86

CFLAGS += -g -I$(APP_INCLUDE) -I$(BASE)/app/open/curl/curl-7.29.0/include/curl $(AP_FLAG) -DGW_X86 -DX86 -O2
CFLAGS += -I$(PWD)
LDFLAGS = -Wall -L$(ROOT)/app/open/curl/curl/lib
DEST_PATH = $(DEST_SBIN_PATH)
DEST_NAME = $(obj-app)

all: build

build: $(obj-dep)
	@echo "BUILD         $(obj-app)"
	@echo "$(obj-dep) $(CFLAGS) $(LDFLAGS)"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(obj-app) $(obj-dep) $(LDLIBS)
	@$(STRIP) -d $(obj-app)

install:
	@echo "INSTALL       $(obj-app)"
	@cp -rf $(obj-app) $(DEST_PATH)/$(DEST_NAME)

clean:
	@echo "CLEAN         $(obj-app)"
	@rm -rf $(obj-app) $(obj-dep)
###############################################################
# X86 end
###############################################################
else
build:
install:
clean:
endif
