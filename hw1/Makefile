
.PRECIOUS: %.exe
SRC_FILES = $(wildcard *.cc)
EXE_FILES = $(SRC_FILES:%.cc=%.exe)
CSV_FILES = $(SRC_FILES:%.cc=%.csv)
PNG_FILE  = summary.png
RPT_FILE  = report.md
IMG_DIR   = img

all: $(RPT_FILE)

$(RPT_FILE): $(PNG_FILE)
	cp prebuilt/template.md $(RPT_FILE)

$(IMG_DIR):
	mkdir $(IMG_DIR)

$(PNG_FILE): $(IMG_DIR) $(CSV_FILES)
	python ./plot.py

%.exe: %.cc
	g++ -o $@ $<

%.csv: %.exe
	./$< > $@

format:
	clang-format -i $(SRC_FILES)

clean:
	rm -rf $(CSV_FILES) $(EXE_FILES) $(IMG_DIR) $(RPT_FILE)
