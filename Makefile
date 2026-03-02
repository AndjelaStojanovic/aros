CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2

BIN_DIR = bin
SRC_DIR = src

SENDER = $(BIN_DIR)/sender
RECEIVER = $(BIN_DIR)/receiver
CLEANUP = $(BIN_DIR)/cleanup

all: dirs $(SENDER) $(RECEIVER) $(CLEANUP)

dirs:
	mkdir -p $(BIN_DIR)

$(SENDER): $(SRC_DIR)/sender.c $(SRC_DIR)/ipc_common.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/sender.c

$(RECEIVER): $(SRC_DIR)/receiver.c $(SRC_DIR)/ipc_common.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/receiver.c

$(CLEANUP): $(SRC_DIR)/cleanup.c $(SRC_DIR)/ipc_common.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/cleanup.c

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean dirs
