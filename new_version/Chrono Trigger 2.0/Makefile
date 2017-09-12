OBJS_NAME = game.c utils/util.c elements/background.c \
			elements/player.c utils/move.c utils/collision.c elements/monster.c utils/battle.c

CC = gcc

COMPILER_FLAGS = -w -std=c99

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = 'bin/Chrono Trigger'


Chrono_Trigger : $(OBJS_NAME)
	@echo 'Building $@..'
	$(CC) $(OBJS_NAME) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
	@echo 'Finished'
