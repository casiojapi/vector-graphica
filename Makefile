pbm:
	convert ./iteration_1_samples/pbm/*.pbm ./iteration_1_samples/jpg/*.jpg
pgm:
	convert ./iteration_2_samples/pgm/*.pgm ./iteration_2_samples/jpg/*.jpg
	
clean:
	rm a.out