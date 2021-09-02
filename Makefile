all: pbm pgm
	
pbm:
	convert ./renders/iteration_1/pbm/*.pbm ./renders/iteration_1/jpg/*.jpg
pgm:
	convert ./renders/iteration_2/pgm/*.pgm ./renders/iteration_2/jpg/*.jpg
ppm:
	convert ./renders/iteration_3.5/ppm/*.ppm ./renders/iteration_3.5/jpg/*.jpg
	
clean:
	rm a.out app ./renders/iteration_*/jpg/*.jpg*