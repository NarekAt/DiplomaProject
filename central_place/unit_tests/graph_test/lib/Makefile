TARGET=graph_test.exe

include ../../common.mk

SUBDIRS=../graph_algo_test ../test_main ../../../graph/base
OBJS=$(wildcard $(join $(SUBDIRS), $(DIR)/*.o))
LFLAGS+=


$(TARGET) : $(OBJS)
	@for dir in $(SUBDIRS); do\
		cp $$dir/$(DIR)/*.o ./;\
	done
	$(GCC) *.o $(CXXFLAGS) $(LFLAGS) -o $@

