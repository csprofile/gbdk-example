CC	= ./bin/lcc -Wa-l -Wl-m -Wl-j -Wl-yt1 

ROM_BUILD_DIR = build/gb
MAIN_FILE = src/main.c
GAME_NAME = game.gb

GAME_FILE = $(ROM_BUILD_DIR)/$(GAME_NAME)
all:	$(GAME_FILE)

#compile.bat: Makefile
#	@make clean > compile.bat
#	@echo "REM Automatically generated from Makefile" > compile.bat
#	@make -sn | sed y/\\//\\\\/ | grep -v make >> compile.bat

# Compile and link single file in one pass
$(GAME_FILE):	$(MAIN_FILE)
	mkdir -p $(ROM_BUILD_DIR)
	$(CC) -o $@ $^

clean:
	cd $(ROM_BUILD_DIR); rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi

build:	clean all
