MAKEFILE_BASE = ../Makefile

.PHONY: default clean clean-binary debug debug-clean debug-clean-binary release release-clean

default: debug

clean: debug-clean

clean-binary: debug-clean-binary

debug:
	$(MAKE) -f $(MAKEFILE_BASE).Debug

debug-clean: clean
	$(MAKE) -f $(MAKEFILE_BASE).Debug clean

debug-clean-binary:
	$(MAKE) -f $(MAKEFILE_BASE).Debug clean-binary

release:
	$(MAKE) -f $(MAKEFILE_BASE).Release

release-clean:
	$(MAKE) -f $(MAKEFILE_BASE).Release clean
