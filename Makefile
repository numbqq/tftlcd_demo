export CROSS_COMPILE=aarch64-linux-gnu-
CC := $(CROSS_COMPILE)gcc

CFLAGS += -ltftlcd

TFTLCD_TEST_OBJ = tftlcd_test.o
TFTLCD_TEST = tftlcd_test

.PHONY: clean

# rules
all: $(TFTLCD_TEST)

%.o: %.c
	$(CC) -c -fPIC  $(CFLAGS) $^ -o $@

$(TFTLCD_TEST): $(TFTLCD_TEST_OBJ)
	$(CC) $^ $(CFLAGS)  -o $@

clean:
	rm -rf *.o *.so ${TFTLCD_TEST} ${TFTLCD_TEST_OBJ}

