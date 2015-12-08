SUBDIRS=alternate_property_computer graph_converter graph graph_generator core
BIN=bin

.PHONY : install clean

install:
	@mkdir -p $(BIN)
	@for dir in $(SUBDIRS); do\
		cp ../$$dir/lib/*.exe $(BIN)/;\
	done

clean:
	rm -rf $(BIN)/*.exe
