NAME	= rt

CC	= g++

RM	= rm -f

SRCDIR	= src/

INCDIR	= inc/

OBJDIR	= obj/

SRCS	= main.cpp \
				Parser.cpp \
				Sphere.cpp

OBJS	= $(addprefix $(OBJDIR), $(SRCS:.cpp=.o))

CFLAGS	= -O2 -march=native -std=c++1y

LDFLAGS	= -lm -I $(INCDIR)

dummy	:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o:	$(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
