TARGET=graph_generator.exe
include ../common.mk

SUBDIRS=../argument_parser ../graph_types ../generator ../writer ../coordinator ../package ../main
OBJS=$(wildcard $(join $(SUBDIRS), $(DIR)/*.o))

$(TARGET) : $(OBJS)
	@for dir in $(SUBDIRS); do \
		if [ -d "$$dir/$(DIR)" ]; then cp $$dir/$(DIR)/*.o ./; fi \
	done
	$(GCC) *.o $(CXXFLAGS) $(LFLAGS) -o $@

