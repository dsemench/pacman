NAME = Pacman

FLAGS = -Wall -Wextra -Werror -F.

SRC = main.cpp Map.cpp Balls.cpp Enemy.cpp Pacman.cpp Text.cpp functions.cpp

OB = $(SRC:.cpp=.o)

FR = -framework SDL2_image -framework SDL2 -framework SDL2_ttf

all: $(NAME)

$(NAME): $(OB)
			@clang++ $(OB) $(FLAGS) $(FR) -o $(NAME)
			@ echo "                                        "'\r\c'
			@echo "Project was compiled"

%.o: %.cpp
			@clang++ -c -o $@ $< $(FLAGS)
			@ echo "Compile $<" '\r\c'

clean:
			@rm -f $(OB)
			@echo "Deleted *.o"

fclean: clean
			@rm -f $(NAME)
			@echo "Deleted all"

re: clean all


