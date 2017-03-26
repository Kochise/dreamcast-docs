# Small makefile to generate the output formats
# Probably requires Linux, BSD, or a well-stocked Cygwin

all: archives clean

kgl:
	-rm -rf kgl_html
	lyx kgl.lyx -e latex
	sed -e '4d' < kgl.tex > kgl2.tex
	mv kgl2.tex kgl.tex
	mkdir kgl_html
	latex2html -split 4 -local_icons -white -dir kgl_html kgl.tex
	-rm -f kgl_html/images.* kgl_html/*.pl kgl_html/WARNINGS kgl_html/kgl.html
	-rm -f kos.pdf
	latex kgl.tex
	latex kgl.tex
	pdflatex kgl.tex
	-rm -f kgl.tex kgl.toc kgl.dvi

kos:
	-rm -rf kos_html
	mkdir kos_html
	latex2html -split 4 -local_icons -white -dir kos_html kos.tex
	-rm -f kos_html/images.* kos_html/*.pl kos_html/WARNINGS kos_html/kos.html
	-rm -f kos.pdf
	latex kos.tex
	latex kos.tex
	pdflatex kos.tex
	-rm -f kos.toc kos.dvi

archives: kgl kos
	zip -r kos_html.zip kos_html/
	zip -r kgl_html.zip kgl_html/

clean:
	-rm -rf kos_html kgl_html *.aux *.log *.toc kgl.tex
