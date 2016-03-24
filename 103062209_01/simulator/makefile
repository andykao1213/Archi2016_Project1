main : main.o loadfile.o decode.o
	gcc -o main main.o loadfile.o decode.o
main.o : main.c loadfile.h decode.h global.h
	gcc -c main.c
loadfile.o : loadfile.c loadfile.h global.h
	gcc -c loadfile.c
decode.o : decode.c decode.h global.h
	gcc -c decode.c
clean :
	rm -f main main.o loadfile.o decode.o
