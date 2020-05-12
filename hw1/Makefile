
.PRECIOUS: %.exe
IMG_DIR   = img
SRC_FILES = $(wildcard *.cc)
EXE_FILES = $(SRC_FILES:%.cc=%.exe)
CSV_FILES = $(SRC_FILES:%.cc=$(IMG_DIR)/%.csv)
PNG_FILE  = $(IMG_DIR)/summary.png
RPT_FILE  = report.md

all: $(RPT_FILE)

$(RPT_FILE): $(PNG_FILE)
	cp prebuilt/template.md $(RPT_FILE)

$(IMG_DIR):
	mkdir $(IMG_DIR)

$(PNG_FILE): $(IMG_DIR) $(CSV_FILES)
	python ./plot.py

%.exe: %.cc
	g++ -o $@ $<

$(IMG_DIR)/%.csv: %.exe
	./$< > $@

format:
	clang-format -i $(SRC_FILES)

clean:
	rm -rf $(EXE_FILES) $(IMG_DIR) $(RPT_FILE)
