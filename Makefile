build:
	g++ -std=c++11 -o project2.out src/*.cpp
run:
	./project2.out
tasks:
	./project2.out output/part11.tga input/circles.tga multiply input/layer1.tga
	./project2.out output/part12.tga input/layer1.tga flip 
	./project2.out output/part13.tga input/layer1.tga subtract input/layer2.tga
	./project2.out output/part14.tga input/car.tga flip flip flip flip
	./project2.out output/part15.tga input/car.tga subtract input/layer1.tga multiply input/circles.tga flip
	./project2.out output/part16.tga input/car.tga scaleblue 3 scalered 2 greenscale 0


	







