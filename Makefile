NAME	= rt

CC	= g++

RM	= rm -f

SRCDIR	= src/

INCDIR	= inc/

OBJDIR	= obj/

SRCS	= main.cpp \
				Parser.cpp \
				Parsable.cpp \
				Rt.cpp \
				SceneObj.cpp \
				Camera.cpp \
				Sphere.cpp \
				Window.cpp \
				Math.cpp \
				Light.cpp \
				LightModel.cpp \
				Rectangle.cpp \
				Color.cpp

OBJS	= $(addprefix $(OBJDIR), $(SRCS:.cpp=.o))

CXXFLAGS	= -O2 -march=native -std=c++14 -g

INCOMP = -I $(INCDIR)

LDFLAGS	= -lsfml-graphics -lsfml-window -lsfml-system -lm

dummy	:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o:	$(SRCDIR)%.cpp
	$(CC) $(CXXFLAGS) $(INCOMP) -o $@ -c $<

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(LDFLAGS) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
