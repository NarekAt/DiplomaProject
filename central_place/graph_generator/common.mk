GCC=mpic++

OGDFPATH=/home/elchyan/Downloads/OGDF/_release

CXXFLAGS=-std=c++11 -g -O0
IFLAGS=
LFLAGS=-lstdc++ -Wl,-Bstatic -lboost_serialization -lboost_graph -lboost_regex -lboost_system -lboost_filesystem -lboost_mpi -lboost_program_options -Wl,-Bdynamic -lm -L/home/elchyan/boost/boost_1_53_0/stage/lib -lm -L/usr/local/lib
LFLAGS+=-L$(OGDFPATH) -lOGDF -lCOIN -pthread

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
