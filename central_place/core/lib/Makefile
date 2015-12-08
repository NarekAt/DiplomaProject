TARGET=core.exe

include ../common.mk

SUBDIRS=../cmd ../cmd_arg ../cmd_base ../cmd_processor ../exceptions ../main 
OBJS=$(wildcard $(join $(SUBDIRS), $(DIR)/*.o))
LFLAGS+=


$(TARGET) : $(OBJS)
	@for dir in $(SUBDIRS); do\
		cp $$dir/$(DIR)/*.o ./;\
	done
	$(GCC) *.o $(CXXFLAGS) $(LFLAGS) -o $@

