#Top level makefile
#DIRS=source/ev3 \
#	eg/dc \
#	eg/drive \
#	eg/hello \
#	eg/io \
#	eg/light \
#	eg/port \
#	eg/poweroff \
#	eg/rcx_led \
#	eg/remote \
#	eg/sensor \
#	eg/servo \
#	eg/tacho \
##	eg/tacho_cpp

DIRS=source/ev3 eg/*/

all::
	@for i in ${DIRS}; \
	do \
	make -C $${i}; \
	done

clean::
	@for i in ${DIRS}; \
	do \
	make -C $${i} clean; \
	done
	
lib::
	make -C source/ev3

shared-lib::
	make -C source/ev3 shared
	
install-lib::
	make -C source/ev3 install
	
install-shared-lib::
	make -C source/ev3 shared-install
	
eg/*::
	make -C $@;