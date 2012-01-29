TARGET=Simulator
CFLAGS=-c -ggdb -Wall `wx-config --cppflags`
COMPILER=g++

$(TARGET): main.o option.o simulation.o windows.o plot.o mathplot.o
	$(COMPILER) $^ -o $@ `wx-config --libs`

main.o: main.h main.cpp windows.h
	$(COMPILER) $(CFLAGS) main.cpp

option.o: option.cpp option.h simulation.h
	$(COMPILER) $(CFLAGS) option.cpp

simulation.o: simulation.cpp simulation.h mathplot.h
	$(COMPILER) $(CFLAGS) simulation.cpp

windows.o: windows.h windows.cpp option.h
	$(COMPILER) $(CFLAGS) windows.cpp

plot.o: plot.h plot.cpp windows.h simulation.h
	$(COMPILER) $(CFLAGS) plot.cpp

mathplot.o: mathplot.cpp mathplot.h
	$(COMPILER) $(CFLAGS) mathplot.cpp

clear:
	rm *.o $(TARGET)
