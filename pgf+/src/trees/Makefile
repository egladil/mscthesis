CC = g++
CCFLAGS = -g
FLEX = flex
BISON = bison
LATEX = latex
DVIPS = dvips

all: testTrees Trees.ps

clean:
	rm -f *.o Trees.dvi Trees.aux Trees.log Trees.ps testTrees

distclean:
	 rm -f *.o Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H Trees.l Trees.y Trees.tex Trees.dvi Trees.aux Trees.log Trees.ps testTrees Makefile

testTrees: Absyn.o Lexer.o Parser.o Printer.o Test.o
	@echo "Linking testTrees..."
	${CC} ${CCFLAGS} *.o -o testTrees
        
Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: Trees.l
	${FLEX} -oLexer.C Trees.l

Parser.C: Trees.y
	${BISON} Trees.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C 

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.C

Test.o: Test.C Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.C

Trees.dvi: Trees.tex
	${LATEX} Trees.tex

Trees.ps: Trees.dvi
	${DVIPS} Trees.dvi -o Trees.ps

