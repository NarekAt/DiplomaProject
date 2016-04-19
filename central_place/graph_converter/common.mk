GCC=gcc	

CXXFLAGS=-std=c++11
IFLAGS=
LFLAGS=-lstdc++ -Wl,-Bstatic -lboost_graph -lboost_serialization -Wl,-Bdynamic -lm -L/home/elchyan/boost/boost_1_53_0/stage/lib

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
