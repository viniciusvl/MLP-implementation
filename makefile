all: lisrun
	
lisrun:
	g++ *.cpp -o mlp -O3

run:
	start ./mlp

clean:
	rm ./mlp