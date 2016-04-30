SUBDIRS=graph_types detector writer common io main lib

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
