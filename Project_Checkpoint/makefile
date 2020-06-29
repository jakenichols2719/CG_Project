EXE=final
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-Wall
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# CSCI Library Dependencies
ex13.o: ex13.c CSCIx229.h
fatal.o: fatal.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
print.o: print.c CSCIx229.h
project.o: project.c CSCIx229.h
errcheck.o: errcheck.c CSCIx229.h

#  Create CSCI library archive
CSCIx229.a:fatal.o loadtexbmp.o print.o project.o errcheck.o
	ar -rcs $@ $^

main.o: main.cpp objects.o
objects.o: CSCIx229.a objects.h objects.cpp
shaderfunc.o: CSCIx229.a shaderfunc.h shaderfunc.cpp

.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

final: main.o objects.o shaderfunc.o CSCIx229.a
	g++ -o $@ $^ $(LIBS)

clean:
	$(CLEAN)
