
doc=STB
RM=rm -f


all: $(doc).pdf

$(doc).pdf: $(doc).tex res/structures.sty
	xelatex -interaction=nonstopmode $<

clean:
	$(RM) *.aux *.log *.out *.toc


