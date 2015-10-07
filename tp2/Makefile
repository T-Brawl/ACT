OPTIONS = -W -Wall -g -std=c++11
Link_OPT = -W -Wall -c -std=c++11
CC = g++

all : svg

svg: Svg.cpp Polyline.o Polyline.h PointNode.o PointNode.h Point.o Point.h
	$(CC) $(OPTIONS) -o svg Svg.cpp Polyline.o PointNode.o Point.o


Polyline.o: Polyline.h PointNode.o PointNode.h Point.o Point.h

PointNode.o: PointNode.h Point.o Point.h

Point.o: Point.h

%.o : %.cpp
	$(CC) $(Link_OPT) $< 

clean:
	rm *.o *~ svg
