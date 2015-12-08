TARGET=graph_converter.exe
include ../common.mk

SUBDIRS=../converter ../main 
OBJS=$(wildcard $(join $(SUBDIRS), $(DIR)/*.o))

$(TARGET) : $(OBJS)
	@for dir in $(SUBDIRS); do\
		cp $$dir/$(DIR)/*.o ./;\
	done
	$(GCC) *.o $(CXXFLAGS) $(LFLAGS) -o $@

