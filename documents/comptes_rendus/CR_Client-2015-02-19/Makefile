CC=pdflatex
doc=CR_Client-2015-02-19
RM=rm -f

all: $(doc).pdf

$(doc).pdf: $(doc).tex CR-projet.cls
	$(CC) $<
	$(CC) $<

clean:
	$(RM) *.aux *.log *.out *.toc $(doc).synctex.gz $(doc).pdf

