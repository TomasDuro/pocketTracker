runtracker: runtracker.o kcftracker.o fhog.o
runtracker.o kcftracker.o fhog.o: *.hpp

CXXFLAGS = -g
LDLIBS = -lopencv_core -lopencv_highgui -lopencv_imgproc -lm -lstdc++

clean:
	rm -f *.o
