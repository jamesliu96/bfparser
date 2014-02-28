bfparser: bfparser.c bfparser.h
	cc -o bfparser bfparser.c
	chmod +x bfparser

.PHONY: test clean install uninstall
test: bfparser
	./bfparser xmas.bf
clean: bfparser
	rm -f bfparser
install: bfparser
	cp -f bfparser /usr/bin/bfparser
uninstall: /usr/bin/bfparser
	rm -f /usr/bin/bfparser
