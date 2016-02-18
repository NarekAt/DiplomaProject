TARGET=alternate_property_counter_test.exe

include ../overrides.mk

SUBDIRS=../base_test ../property_counters_test ../randomizers_test ../io_test ../test_main ../../../alternate_property_computer/base ../../../alternate_property_computer/io ../../../alternate_property_computer/property_counters ../../../alternate_property_computer/randomizers ../../../alternate_property_computer/graph_types ../../../alternate_property_computer/common
OBJS=$(wildcard $(join $(SUBDIRS), $(DIR)/*.o))
LFLAGS+=


$(TARGET) : $(OBJS)
	@for dir in $(SUBDIRS); do\
		cp $$dir/$(DIR)/*.o ./;\
	done
	$(GCC) *.o $(CXXFLAGS) $(LFLAGS) -o $@

