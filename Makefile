all: pbm pgm ppm

app:
	gcc -o app *.c -lm
pbm:
	convert ./renders/iteration_1/pbm/*.pbm ./renders/iteration_1/jpg/*.jpg
pgm:
	convert ./renders/iteration_2/pgm/*.pgm ./renders/iteration_2/jpg/*.jpg
ppm:
	convert ./renders/iteration_5/ppm/*.ppm ./renders/iteration_5/jpg/*.jpg
	
clean:
	rm a.out app ./renders/iteration_*/jpg/*.jpg*