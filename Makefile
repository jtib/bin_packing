rapport.pdf: rapport.tex
	pdflatex rapport.tex
	bibtex rapport
	pdflatex rapport.tex
	pdflatex rapport.tex
