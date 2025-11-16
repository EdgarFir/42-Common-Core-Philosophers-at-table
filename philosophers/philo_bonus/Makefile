NAME = philo_bonus

SRCS = philo_bonus.c philo_utils_bonus.c philo_validator_bonus.c philo_simulation_bonus.c \
	   philo_semaphores_bonus.c philo_sem_name_bonus.c philo_monitors_bonus.c

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread #-fsanitize=thread

all: $(NAME)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
