GCC=mpic++

ARCH = $(shell getconf LONG_BIT)
ifeq ($(ARCH), 32)
  XLLIBPATH =/home/natayan/libs_space/libxl-3.6.5.0/lib
else
  XLLIBPATH =/home/natayan/libs_space/libxl-3.6.5.0/lib64
endif

CXXFLAGS=-std=c++11 -O3
IFLAGS=
LFLAGS=-lstdc++ -Wl,-Bstatic -lboost_serialization -lboost_graph -lboost_regex -lboost_system -lboost_filesystem -lboost_mpi -lboost_program_options -Wl,-Bdynamic -lm -L/home/natayan/boost/boost_1_53_0/stage/lib -lm -L/usr/local/lib -ligraph
LFLAGS+=-L$(XLLIBPATH) -lxl

DIR=objs

SOURCES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, $(DIR)/%.o, $(SOURCES))

compile: $(TARGET)

.PHONY: compile clean

$(TARGET) : $(OBJS)

$(DIR)/%.o : %.cpp
	@mkdir -p $(DIR)
	$(GCC) $(CXXFLAGS) $(IFLAGS) $(LFLAGS) -c -o $@ $<

debug: CXXFLAGS=-std=c++11 -g -O0
debug: compile

clean :
	rm -rf $(DIR)/*.o $(TARGET)
	rm -rf *.o
