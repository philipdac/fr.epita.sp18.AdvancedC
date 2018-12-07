TARGET_FILE = km
BUILD_DIR = ./build
SRC_DIRS = ./src
INCL_DIRS = ./include

# add .c file here
SRCS_FILE = city.c List.c main.c map_read_data_file.c map_search.c status.c string_ext.c vertex.c

SRCS = $(SRCS_FILE:%=$(SRC_DIRS)/%)
OBJS = $(SRCS_FILE:%.c=$(BUILD_DIR)/%.o)
CC = gcc

INCL_FLAG = -I $(INCL_DIRS)
DEBUG_FLAG = -g -lm
# DEBUG_FLAG = -g -lm -D DEBUG

$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c
	$(CC) -c $< -o $@ $(INCL_FLAG) $(DEBUG_FLAG)

$(TARGET_FILE): $(OBJS)
	$(CC) $(OBJS) -o $@  $(DEBUG_FLAG)