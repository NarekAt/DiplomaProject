SUBDIRS=generator test_main ../../graph_generator/graph_types ../../graph_generator/common ../../graph_generator/generator lib

.PHONY : compile clean

compile:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir;\
	done

clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean;\
	done
