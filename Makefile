CC = g++
LD = g++

CFLAGS = -Wall -ggdb -I include/ -lmpfr -D_REENTRANT -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
LDFLAGS = -Wall -ggdb -I include/ -lmpfr -D_REENTRANT -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED

SRCS = interval_arithmetic.cpp main.cpp programclass.cpp
OBJECTS = $(SRCS:.cpp=.o)
EXEC = newton_polynomial
INCPATH = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4
LIBS = -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread

OBJS = $(addprefix ./obj/, $(OBJECTS))

$(EXEC): $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)

./obj/%.o: ./src/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(INCPATH)

clean:
	rm -f $(OBJS) $(EXEC)
