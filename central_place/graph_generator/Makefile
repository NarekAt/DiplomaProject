SUBDIRS=argument_parser graph_types generator writer coordinator package main lib 

.PHONY : compile clean

compile:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir;\
	done

clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean;\
	done
