all: app
run: run_app to_jpg clean_ppm

convert: to_jpg clean_ppm

app:
	gcc -o vector-graphica *.c -std=c99 -Ofast -lm
run_app:
	./vector-graphica
to_jpg:
	convert renders/*.ppm -set filename: "%t" renders/%[filename:].jpg


clean_ppm:
	rm renders/*.ppm 
clean_renders:
	rm renders/*.jpg
clean:
	rm vector-graphica 
wipe: clean clean_renders clean_ppm

move:
	mv *.jpg ./renders/
