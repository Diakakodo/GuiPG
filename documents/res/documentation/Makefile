CC=pdflatex
doc=documentation_univ-projet
RM=rm -f

all: $(doc).pdf

$(doc).pdf: $(doc).tex
	$(CC) $<

clean:
	$(RM) *.aux *.log *.out *.toc
cleanAll: clean
	$(RM) $(doc).pdf

