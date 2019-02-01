main : main.o fextract.o fmerge.o
	g++ -o main main.o fextract.o fmerge.o

main.o : main.cpp
	g++ -c main.cpp
fextract.o : fextract.cpp fucSet.h
	g++ -c fextract.cpp
fmerge.o : fmerge.cpp fucSet.h
	g++ -c fmerge.cpp

clean : 
	rm main main.o fextract.o fmerge.o
oclean :
	rm ./ioFile/China.txt ./ioFile/English.txt ./ioFile/pure.txt	   
