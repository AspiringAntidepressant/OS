

all: myshell my-cat my-uniq my-wc


myshell: myshell.c
	gcc -o myshell myshell.c -Wall -Werror -lreadline

my-cat: my-cat.c
	gcc -o my-cat my-cat.c -Wall -Werror

my-uniq: my-uniq.c
	gcc -o my-uniq my-uniq.c -Wall -Werror

my-wc: my-wc.c
	gcc -o my-wc my-wc.c -Wall -Werror

clean:
	rm -f myshell mysort my-cat my-uniq my-wc
