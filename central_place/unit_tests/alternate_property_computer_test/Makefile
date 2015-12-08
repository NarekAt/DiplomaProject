SUBDIRS=property_counters_test randomizers_test io_test ../../alternate_property_computer/graph_types ../../alternate_property_computer/common ../../alternate_property_computer/property_counters ../../alternate_property_computer/io test_main lib

.PHONY : compile clean

compile:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir;\
	done

clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean;\
	done
