OUTPUT = alpha_blending.out

CFILES = main.cpp hub.cpp calcs.cpp graphics.cpp

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OPT_FLAG = -mavx2 -O1

CFLAGS = -Wshadow    						\
	-Winit-self 						\
	-Wredundant-decls 					\
	-Wcast-align						\
	-Wundef 						\
	-Wfloat-equal 						\
	-Winline 						\
	-Wunreachable-code 					\
	-Wmissing-declarations 					\
	-Wmissing-include-dirs 					\
	-Wswitch-enum 						\
	-Wswitch-default 					\
	-Weffc++ 						\
	-Wmain 							\
	-Wextra 						\
	-Wall 							\
	-g 							\
	-pipe 							\
	-fexceptions 						\
	-Wcast-qual 						\
	-Wconversion 						\
	-Wctor-dtor-privacy 					\
	-Wempty-body 						\
	-Wformat-security 					\
	-Wformat=2 						\
	-Wignored-qualifiers 					\
	-Wlogical-op 						\
	-Wmissing-field-initializers 				\
	-Wnon-virtual-dtor 					\
	-Woverloaded-virtual 					\
	-Wpointer-arith 					\
	-Wsign-promo 						\
	-Wstack-usage=8192 					\
	-Wstrict-aliasing 					\
	-Wstrict-null-sentinel 					\
	-Wtype-limits 						\
	-Wwrite-strings 					\
	-D_DEBUG 						\
	-D_EJUDGE_CLIENT_SIDE

all:
	@ clear
	g++ -o $(OUTPUT) -mavx2 -O3 $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio $(CFILES)
	@ echo Compiled c-files

.PHONY: run
run:
	@ ./$(OUTPUT) imgs/AskhatCat.bmp imgs/Table.bmp 1

def:
	@ g++ -E $(OUTPUT) $(CFLAGS) $(CFILES) >> defines.txt
