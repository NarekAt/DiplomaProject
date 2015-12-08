TARGET=graph.exe
include ../common.mk

SUBDIRS=../base ../utilities ../testing
OBJS=$(wildcard $(join $(SUBDIRS), $(DIR)/*.o))

$(TARGET) : $(OBJS)
	@for dir in $(SUBDIRS); do \
		if [ -d "$$dir/$(DIR)" ]; then cp $$dir/$(DIR)/*.o ./; fi \
	done
	$(GCC) *.o $(CXXFLAGS) $(LFLAGS) -o $@

