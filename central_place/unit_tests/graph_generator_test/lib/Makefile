TARGET=graph_generator_test.exe

include ../../common.mk

SUBDIRS=../generator ../test_main ../../../graph_generator/generator ../../../graph_generator/graph_types ../../../graph_generator/common
OBJS=$(wildcard $(join $(SUBDIRS), $(DIR)/*.o))
LFLAGS+=


$(TARGET) : $(OBJS)
	@for dir in $(SUBDIRS); do\
		cp $$dir/$(DIR)/*.o ./;\
	done
	$(GCC) *.o $(CXXFLAGS) $(LFLAGS) -o $@

