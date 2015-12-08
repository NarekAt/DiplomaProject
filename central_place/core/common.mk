GCC=color-gcc

CXXFLAGS=-std=c++11
IFLAGS=
LFLAGS=-lstdc++ -lm

DIR=objs

SOURCES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, $(DIR)/%.o, $(SOURCES))

compile: $(TARGET)

.PHONY: compile clean

$(TARGET) : $(OBJS)

$(DIR)/%.o : %.cpp
	@mkdir -p $(DIR)
	$(GCC) $(CXXFLAGS) $(IFLAGS) $(LFLAGS) -c -o $@ $<


clean :
	rm -rf $(DIR)/*.o $(TARGET)
	rm -rf *.o
