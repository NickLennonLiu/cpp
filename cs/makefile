check: menu.txt check.cpp
	g++ -o check.exe check.cpp

menu.txt:
	echo 01 goat 123 > menu.txt

debug: *.cpp
	g++ -g -o $@ $^


cleanall: cleanexe cleano cleantxt

cleanexe:
	@-rm *.exe

cleano:
	@-rm *.o

cleantxt:
	@-rm *.txt