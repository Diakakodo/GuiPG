CC=pdflatex
doc1=CDR_Livraison1
doc2=CDR_Livraison2
RM=rm -f

all: $(doc1).pdf $(doc2).pdf

$(doc2).pdf: $(doc2).tex ../res/structures.sty ../res/univ-projet.cls
	$(CC) $<
	$(CC) $<

$(doc1).pdf: $(doc1).tex ../res/structures.sty ../res/univ-projet.cls
	$(CC) $<
	$(CC) $<

clean:
	$(RM) *.aux *.log *.out *.toc $(doc1).synctex.gz $(doc1).pdf
	$(RM) *.aux *.log *.out *.toc $(doc2).synctex.gz $(doc2).pdf

