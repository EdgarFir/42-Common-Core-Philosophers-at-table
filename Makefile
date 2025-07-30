NAME = philo

SRCS = philo_cleaner.c philo_mutex.c philo_routine.c philo_simulation.c \
	   philo_utils.c philo_validator.c philo.c

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

RM = rm -rf

all: $(NAME)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re