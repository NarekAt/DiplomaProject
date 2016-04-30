TARGET=community_detector.exe
include ../common.mk

SUBDIRS=../graph_types ../detector /home/natayan/libs_space/libxl-3.6.5.0/lib64 ../writer ../common ../io ../main
OBJS=$(wildcard $(join $(SUBDIRS), $(DIR)/*.o))

$(TARGET) : $(OBJS)
	@for dir in $(SUBDIRS); do \
		if [ -d "$$dir/$(DIR)" ]; then cp $$dir/$(DIR)/*.o ./; fi \
	done
	$(GCC) *.o $(CXXFLAGS) $(LFLAGS) -o $@

