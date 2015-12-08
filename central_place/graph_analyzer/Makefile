SUBDIRS=main parallel_property_counters ../alternate_property_computer/graph_types ../alternate_property_computer/common ../alternate_property_computer/io lib 

.PHONY : compile clean

compile:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir;\
	done

clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean;\
	done
