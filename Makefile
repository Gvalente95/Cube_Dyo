BASIC_DIR = cube_basic 
BONUS_DIR = cube_bonus

all:
	make -C $(BASIC_DIR)
	echo compiling cub3d

clean:
	@if [ ls $(BASIC_DIR)/* | grep objs ]; then rm cube3d; fi || @if [ls $(BONUS_DIR)/*]; then rm cube3d_bonus; fi
	@if [ $? = 0]; then echo "nothing to remove" fi



