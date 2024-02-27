TARGET = libBigInt.a
CC = gcc
CFLAGS = -Wall -g

PREF_SRC = ./src/
PREF_OBJ = ./obj/
PREF_TEST = ./tests/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))

TEST_SRC = $(wildcard $(PREF_TEST)*.c)
TEST_OBJ = $(patsubst $(PREF_TEST)%.c, $(PREF_OBJ)%.o, $(TEST_SRC))

$(TARGET) : $(OBJ)
	ar rcs $(TARGET) $(OBJ)

$(PREF_OBJ)%.o : $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

test : $(TEST_OBJ) $(TARGET)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o test -L. -lBigInt

$(PREF_OBJ)%.o : $(PREF_TEST)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(TARGET) $(PREF_OBJ)*.o $(TEST_OBJ)*.o test 

