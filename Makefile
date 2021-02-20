NAME = recat

$(NAME):
	gcc -o $(NAME) main.c

all: $(NAME)

clean:
	rm $(NAME)

re: clean all

.PHONY: all clean re
