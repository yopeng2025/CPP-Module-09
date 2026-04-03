NAME = PmergeMe

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror

SRC = main.cpp
INCLUDES = PmergeMe.hpp
OBJ = $(SRC:.o=.cpp)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
