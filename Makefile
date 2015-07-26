all:
	g++-4.9 -I. sinoid.cpp main.cpp note.cpp instrument.cpp synthetizer.cpp -o soundPon -ISFML-2.3.1/include -lsfml-audio -lsfml-system -LSFML-2.3.1/lib -std=c++11 -g -O2
