all: pbm pgm
	
pbm:
	convert ./samples/iteration_1/pbm/*.pbm ./samples/iteration_1/jpg/*.jpg
pgm:
	convert ./samples/iteration_2/pgm/*.pgm ./samples/iteration_2/jpg/*.jpg
	
clean:
	rm a.out ./samples/iteration_*/jpg/*.jpg*