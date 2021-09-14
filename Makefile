all: ppm

app:
	gcc -o app *.c -lm
ppm:
	convert ./renders/ppm/*.ppm ./renders/jpg/*.jpg
clean:
	rm a.out app ./renders/iteration_*/jpg/*.jpg