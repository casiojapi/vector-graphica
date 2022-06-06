all: app run ppm clean_ppm

app:
	gcc -o app *.c -lm
run:
	./app
ppm:
	convert *.ppm *.jpg
clean_ppm:
	rm ./renders/ppm/*.ppm 
clean_jpg:
	rm ./renders/jpg/*.jpg
clean:
	rm app 
wipe: clean clean_jpg
