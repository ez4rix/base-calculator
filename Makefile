CXX = g++
EXEC = a
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
COMPILER_FLAG = -Wall -Werror
LINKER_FLAG = -Iinclude -Llib -lraylib -lwinmm -lgdi32

all : $(EXEC)
	cls

%.o : %.cpp
	$(CXX) -o $@ -c $^ $(COMPILER_FLAG)

$(EXEC) : $(OBJ)
	$(CXX) -o $(EXEC) $^ $(COMPILER_FLAG) $(LINKER_FLAG)
