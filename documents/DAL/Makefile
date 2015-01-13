CC=pdflatex
doc=DAL
RM=rm -f

all: $(doc).pdf

$(doc).pdf: $(doc).tex ../res/structures.sty ../res/univ-projet.cls ../res/tikz-uml.sty
	$(CC) $<
	$(CC) $<

clean:
	$(RM) *.aux *.log *.out *.toc $(doc).synctex.gz $(doc).pdf

