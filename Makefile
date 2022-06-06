all: app run ppm clean_ppm

app:
	gcc -o app *.c -lm
run:
	./app
ppm:
	convert *.ppm -set filename: "%t" %[filename:].jpg


clean_ppm:
	rm *.ppm 
clean_jpg:
	rm *.jpg
clean:
	rm app 
wipe: clean_jpg clean clean_ppm

move:
	mv *.jpg ./renders/
