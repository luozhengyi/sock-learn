CC := gcc
CXX := g++

SUBDIRS := chap1 chap2 chap3 chap4 chap5 chap6

.PHONY: ALL

ALL: subdir

subdir:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir; \
	done
