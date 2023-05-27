#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


#define MAX_SIZE 26
#define MIN_SYMBOLS 4
#define MAX_SYMBOLS 6

struct Time {
    int hour;
    int minute;
};


struct Time calculate_time_difference(struct Time initial_time, struct Time final_time);


int aleatoire(int min, int max);

void print_menu();

void init_board(int size_row,int size_col,int num_symbols);

void print_board(int size_col,int size_row);

int is_valid_move(char board[MAX_SIZE][MAX_SIZE],int sizerow,int size_col, int x1, int y1, int x2, int y2);

int remove_matches(char board[MAX_SIZE][MAX_SIZE],int size_row,int size_col);

void apply_gravity(int size_col,int size_row,char board[MAX_SIZE][MAX_SIZE]);

int play_game(int size_row, int size_col,int num_symbols);

void vide_buffer();

//void includeFile(const char* filePath);
void save_user();
void includeFile(const char* filePath);


