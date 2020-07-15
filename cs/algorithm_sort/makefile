SRCDIR = 
OBJDIR = obj/

SRC = $(wildcard ${SRCDIR}*.cpp)
OBJ = $(patsubst ${SRCDIR}%.cpp, ${OBJDIR}%.o, ${SRC})

all: $(OBJ)
	g++ -o sort.exe $(OBJ) -g

$(OBJ): $(OBJDIR)%.o : ${SRCDIR}%.cpp
	g++ -o $@ -c $<

clean: cleanobj cleanexe

cleanobj:
	rm $(OBJDIR)*.o

cleanexe:
	rm *.exe