all: app run ppm

app:
	gcc -o app *.c -lm
run:
	./app
ppm:
	convert ./renders/ppm/*.ppm ./renders/jpg/*.jpg
clean:
	rm a.out app ./renders/jpg/*.jpg ./renders/ppm/*.ppm 