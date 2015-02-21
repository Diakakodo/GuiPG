CC=pdflatex
doc=CR_Groupe-2015-02-20
RM=rm -f

all: $(doc).pdf

$(doc).pdf: $(doc).tex ../../res/CR-projet.cls
	$(CC) $<
	$(CC) $<

clean:
	$(RM) *.aux *.log *.out *.toc $(doc).synctex.gz $(doc).pdf

