NAME = ircserv

FILES = srcs/main.cpp

OBJS = $(FILES:.cpp=.o)

#FLAGS = -Wall -Wextra -Werror -fsanitize=address -fpermissive -std=c++98 -I./srcs
FLAGS  -Wall -Wextra - Werror - pedantic -std=c98 -I./srcs

CC = c++

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re