CC=c++
CFLAGS=-Wall -Wextra -Werror -std=c++98 -g
INCLUDES=-Iincludes
SRC= \
	srcs/Token.cpp \
	srcs/Json.cpp \
	srcs/parser.cpp \
	srcs/interpreter.cpp \
	srcs/displayJson.cpp

OBJ = $(SRC:.cpp=.o)
NAME = libjson.a

all: $(NAME)

test: $(NAME) test.cpp
	$(CC) $(CFLAGS) $(INCLUDES) test.cpp -L. -ljson -o test

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) test

re: fclean all

$(NAME): $(OBJ)
	ar rcs $(NAME) $^

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

.PHONY: all, clean, fclean, re
