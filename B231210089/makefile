all: derle bagla calistir

derle:
	g++ -c -I "./include" ./src/BagliListe.cpp -o ./lib/BagliListe.o
	g++ -c -I "./include" ./src/Dugum.cpp -o ./lib/Dugum.o
	g++ -c -I "./include" ./src/IkiliAgac.cpp -o ./lib/IkiliAgac.o
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o


bagla:
	g++ ./lib/BagliListe.o ./lib/Dugum.o ./lib/IkiliAgac.o ./lib/main.o -o ./bin/RASTGELE

calistir:
	./bin/RASTGELE
