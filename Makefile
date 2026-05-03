CC = gcc
CFLAGS = -Wall -Wextra -g
SRCS = todo.c src/file_handler.c
OBJS = $(SRCS:.c=.o)

TARGET = todo

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@




clean:
	rm -f $(OBJS) $(TARGET) tododata .tododata
