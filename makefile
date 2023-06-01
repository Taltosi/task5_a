CC = gcc
CFLAGS = -Wall -pthread
LIBS = -pthread -lm

SRCS = ThreadSafeQueue.c st_pipeline.c activeObject.c
OBJS = $(SRCS:.c=.o)

TARGET = st_pipeline

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) isPrime.o