# Jacob Schneck
# CS 120
# Module Four - Open Ended Project

CC := g++ -std=c++17
libs := -lglut -lGL

make: 
	${CC} *.cpp -o graphics ${libs}
	./graphics
	rm graphics