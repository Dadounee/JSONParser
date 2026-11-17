CC=c++
CFLAGS=-Wall -Wextra -Werror -std=c++98 -g
INCLUDES=-Iincludes
SRC= \
	main.cpp \
	srcs/Token.cpp \
	interpreter/interpreter.cpp \
	interpreter/displayJson.cpp

OBJ=$(SRC:.cpp=.o)
NAME=test

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

.PHONY: all, clean, fclean, re
