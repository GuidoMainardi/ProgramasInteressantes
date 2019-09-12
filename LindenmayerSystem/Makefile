SOURCE  = LindenmayerSystem.c
OBJECTS = $(SOURCE:.c=.o)

UNAME = `uname`

all: $(TARGET)
	-@make $(UNAME)

Linux: $(OBJECTS)
	gcc $(OBJECTS) -lGL -lGLU -lglut -lm -o LonSys

clean:
	-@ rm -f $(OBJECTS) LinSys