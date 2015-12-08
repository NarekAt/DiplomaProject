TARGET=graph_analyzer.exe
include ../common.mk

SUBDIRS=../main ../parallel_property_counters ../../alternate_property_computer/graph_types ../../alternate_property_computer/io ../../alternate_property_computer/common 
OBJS=$(wildcard $(join $(SUBDIRS), $(DIR)/*.o))

$(TARGET) : $(OBJS)
	@for dir in $(SUBDIRS); do \
		if [ -d "$$dir/$(DIR)" ]; then cp $$dir/$(DIR)/*.o ./; fi \
	done
	$(GCC) *.o $(CXXFLAGS) $(LFLAGS) -o $@

