CC = g++
LD = g++

CFLAGS = -Wall -I include/ -lmpfr
LDFLAGS = -Wall -I include/ -lmpfr

SRCS = interval_arithmetic.cpp main.cpp
OBJECTS = $(SRCS:.cpp=.o)
EXEC = newton_polynomial

OBJS = $(addprefix ./obj/, $(OBJECTS))

$(EXEC): $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS)

./obj/%.o: ./src/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)
