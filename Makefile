CXX = g++
EXEC = a
SRC = $(wildcard *.cpp)
OBJ_DIR = build
OBJ = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC))

COMPILER_FLAG = -Wall -Werror
LINKER_FLAG = -Iinclude -Llib -lraylib -lwinmm -lgdi32

all: $(EXEC)
	cls

# Rule to compile all
$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(COMPILER_FLAG) $(LINKER_FLAG)

# Rule to compile .cpp to .o in the build directory
$(OBJ_DIR)/%.o: %.cpp
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(CXX) -o $@ -c $< $(COMPILER_FLAG)

clean:
	rm -rf $(OBJ_DIR) $(EXEC)
