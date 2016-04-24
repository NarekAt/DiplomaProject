SUBDIRS=base utilities testing lib
LIBDIR=base

.PHONY : compile debug lib clean

compile:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir compile;\
	done

debug:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir debug;\
	done

lib:
	@for dir in $(LIBDIR); do\
		$(MAKE) -C $$dir lib;\
	done

clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean;\
	done
