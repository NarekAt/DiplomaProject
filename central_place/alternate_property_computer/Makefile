SUBDIRS=exceptions graph_types common package main argument_parser mediator io base property_counters randomizers task_managers lib

.PHONY : compile debug clean

compile:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir compile;\
	done

debug:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir debug;\
	done

clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean;\
	done
