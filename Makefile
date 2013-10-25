CPP      = g++
CPPFLAGS = -Wall -g -O0
LIBS     = -lSDL2main -lSDL2

TITLE    = bullshit
OBJS     = main.o engine.o errors.o utils.o

all: $(TITLE)

$(TITLE): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LIBS)

main.o: main.h engine.h errors.h
engine.o: engine.h errors.h utils.h
errors.o: errors.h utils.h
utils.o: utils.h

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(TITLE) $(OBJS)
