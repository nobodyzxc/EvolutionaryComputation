
.PRECIOUS: %.exe
MKD_DIR   = mkd
SRC_FILES = $(wildcard *.cc)
EXE_FILES = $(SRC_FILES:%.cc=%.exe)
MKD_FILES = $(SRC_FILES:%.cc=$(MKD_DIR)/%.md)
RPT_FILE  = report.md
TPL_FILES = prebuilt/template.md prebuilt/print.md

all: $(RPT_FILE)

$(RPT_FILE): $(MKD_DIR) $(MKD_FILES) $(TPL_FILES)
	python render.py > $(RPT_FILE)

%.exe: %.cc
	g++ -o $@ $<

$(MKD_DIR):
	mkdir $(MKD_DIR)

$(MKD_DIR)/%.md: %.exe
	./$< > $@

format:
	clang-format -i $(SRC_FILES)

clean:
	rm -rf $(EXE_FILES) $(MKD_DIR)
