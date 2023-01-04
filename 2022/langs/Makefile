SHELL   = /bin/bash
ROOTDIR = $(CURDIR)

INPUT ?= $(CURDIR)/../input

all:
	@

d1:
	@./day1.bash < ${INPUT}/day1.txt

d2:
	@echo -n "Part 1: "
	@jq -nRf ./day2-1.jq ${INPUT}/day2.txt
	@echo -n "Part 2: "
	@jq -nRf ./day2-2.jq ${INPUT}/day2.txt

d3:
	@./day3-1.lua < ${INPUT}/day3.txt
	@./day3-2.lua < ${INPUT}/day3.txt

clean:
	$(RM) -r core *~ *.o *.out *.exe 

distclean: clean
	$(RM)