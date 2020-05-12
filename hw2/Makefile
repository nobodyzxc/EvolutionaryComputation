
.PRECIOUS: %.exe
SRC_FILES = $(wildcard *.cc)
EXE_FILES = $(SRC_FILES:%.cc=%.exe)
MKD_FILES = $(SRC_FILES:%.cc=%.mkd)
RPT_FILE  = report.md

all: $(SUM_FILE)

$(RPT_FILE): $(MKD_FILES)
	./render.py > $(RPT_FILE)

%.exe: %.cc
	g++ -o $@ $<

%.csv: %.exe
	./$< > $@

format:
	clang-format -i $(SRC_FILES)

clean:
	rm -rf $(EXE_FILES)
