CC = gcc
PUB = /lab/theory/pub
HW = hw8

binsearch: binsearch.c
	${CC} -o binsearch binsearch.c

binsearch_demo: binsearch
	cp binsearch binsearch_demo

seqsearch: seqsearch.c
	${CC} -o seqsearch seqsearch.c

dummysearch: seqsearch.c
	${CC} -o dummysearch dummysearch.c

#Data Generation
random_words: random_words.c
	${CC} -o random_words random_words.c

gen_input: random_words
	cat test1.in > test2.in
	./random_words >> test2.in

test: binsearch
	./binsearch < test1.in > test1.out
	diff test1.out ch_test1.out

time_test: binsearch
	./binsearch < test2.in > test2.out
	diff test2.out ch_test2.out

test_test: seqsearch
	./seqsearch < test2.in > s-test2.out
	./binsearch < test2.in > b-test2.out
	./hash < test2.in > h-test2.out
	diff s-test2.out b-test2.out
	diff s-test2.out h-test2.out

test3:
	./binsearch < test3.in > b-test3.out
	./hash < test3.in > h-test3.out

${HW}.zip: README.pdf Makefile check binsearch_demo test1.in test2.in words.dat
	chmod 755 binsearch_demo
	zip ${HW}.zip README.pdf Makefile test1.in test2.in ch_test1.out ch_test2.out binsearch_demo words.dat

pub: ${HW}.zip
	cp ${HW}.zip ${PUB}/ds_hws/${HW}.zip
	chmod 644 ${PUB}/ds_hws/${HW}.zip

sync:
	rsync -rtv --delete . linux2.ce.hongik.ac.kr:hw/${HW}/ #timestamp preserving

README.pdf: README.tex
	pdflatex README.tex

check: binsearch_demo test1.in test2.in
	./binsearch_demo < test1.in > ch_test1.out
	./binsearch_demo < test2.in > ch_test2.out

clean: 
	rm binsearch binsearch_demo *.o ch_*.out *.aux *.log *.zip
