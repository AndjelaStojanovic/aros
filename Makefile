CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2

BIN_DIR = bin
SRC_DIR = src

SENDER = $(BIN_DIR)/sender
RECEIVER = $(BIN_DIR)/receiver

all: dirs $(SENDER) $(RECEIVER)

dirs:
	mkdir -p $(BIN_DIR)

$(SENDER): $(SRC_DIR)/sender.c $(SRC_DIR)/ipc_common.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/sender.c

$(RECEIVER): $(SRC_DIR)/receiver.c $(SRC_DIR)/ipc_common.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/receiver.c

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean dirs
