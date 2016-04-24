SUBDIRS=base utilities testing lib
LIBDIR=base

.PHONY : compile lib clean

compile:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir;\
	done

lib:
	@for dir in $(LIBDIR); do\
		$(MAKE) -C $$dir lib;\
	done

clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean;\
	done
