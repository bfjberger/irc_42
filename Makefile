NAME = ircserv

CC = c++
#FLAGS = -Wall -Wextra -Werror -fsanitize=address -fpermissive -std=c++98 -I./srcs
FLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 -I./srcs
RM = /bin/rm -rf

BLUE = \033[0;34m
RED = \033[0;31m
WHITE = \033[0;97m

SRC_PATH = ./srcs/
FILES = main.cpp

SRCS = ${addprefix ${SRC_PATH}, ${FILES}}

OBJ_DIR = ./objs/
OBJS = $(FILES:.cpp=.o)
OBJ = ${addprefix ${OBJ_DIR}, ${OBJS}}

DIR_DUP = @mkdir -p ${@D}

${OBJ_DIR}%.o: ${SRC_PATH}%.cpp
	@${DIR_DUP}
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@($(CC) $(FLAGS) $(OBJ) -o $(NAME))
	@echo "${BLUE}Compiled executable${WHITE}"

clean:
	@(${RM} $(OBJ_DIR))
	@echo "${RED}Clean objects files${WHITE}"

fclean: clean
	@(${RM} $(NAME))
	@echo "${RED}Clean executable files${WHITE}"

re: fclean all

.PHONY: all clean fclean re