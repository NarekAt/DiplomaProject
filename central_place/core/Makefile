SUBDIRS=cmd cmd_arg cmd_base cmd_processor exceptions main lib

.PHONY : compile clean

compile:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir;\
	done

clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean;\
	done
