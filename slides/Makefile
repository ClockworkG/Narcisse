PDF = pogl-le_bih_r.pdf

all:
	pandoc \
	--toc \
	-t beamer \
	slides.md \
	-V theme:Copenhagen \
	--include-in-header header.tex \
	-o $(PDF)

clean:
	$(RM) $(PDF)
