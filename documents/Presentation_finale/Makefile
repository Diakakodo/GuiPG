CC=pdflatex
doc=Presentation
RM=rm -f

all: $(doc).pdf

$(doc).pdf: $(doc).tex Garde.tex Intro.tex\
            Initial.tex Final.tex Probleme.tex Bilan.tex\
            Conclu.tex
	$(CC) $< ; $(CC) $< 

clean:
	$(RM) *.aux *.log *.out *.toc *.nav *.snm $(doc).synctex.gz $(doc).pdf

