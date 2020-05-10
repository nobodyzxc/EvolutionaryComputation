
.PRECIOUS: %.exe
SRC_FILES = $(wildcard *.cc)
EXE_FILES = $(SRC_FILES:%.cc=%.exe)
CSV_FILES = $(SRC_FILES:%.cc=%.csv)
PNG_FILE  = summary.png

all: $(PNG_FILE)

$(PNG_FILE): $(CSV_FILES)
	./plot.py

%.exe: %.cc
	g++ -o $@ $<

%.csv: %.exe
	./$< > $@

format:
	clang-format -i $(SRC_FILES)

clean:
	rm -rf $(CSV_FILES) $(EXE_FILES) $(PNG_FILE) *.png
