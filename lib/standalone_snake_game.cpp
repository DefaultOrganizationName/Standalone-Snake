#include "standalone_snake_game.h"
#include "easy_printf.h"
#include "time.h"
#include "execution_states.h"
#include <stdint.h>

static uint8_t head_x;
static uint8_t head_y;
static int len;

static bool is[MAX_ROW + 10][MAX_COL + 10];

static uint8_t snake_x[(int)1e3];
static uint8_t snake_y[(int)1e3];

static uint8_t food_x;
static uint8_t food_y;
static uint8_t random_x;
static uint8_t random_y;

static const uint8_t FIELD_LEN = MAX_COL - 10;
static const uint8_t FIELD_HEIGHT = MAX_ROW;

static const char FENCE = '#';
static const char SNAKE_HEAD = '0';
static const char SNAKE_BODY = '*';
static const char FOOD = '$';

static int ok = 1;

static int points = 0;

static void drow_food(int i) {
	switch (i % 5) {
		case 0:
			putchar_cl(FOOD, VGA_COLOR_RED);
			return;
		case 1:
			putchar_cl(FOOD, VGA_COLOR_BROWN);
			return;
		case 2:
			putchar_cl(FOOD, VGA_COLOR_LIGHT_GREEN);
			return;
		case 3:
			putchar_cl(FOOD, VGA_COLOR_MAGENTA);
			return;
		default:
			putchar_cl(FOOD, VGA_COLOR_LIGHT_BLUE);
			return;
	}	
}

static void drow_field() {
	fast_clear_screen();
	for (int i = 0; i < FIELD_LEN; i++) putchar_cl(FENCE, VGA_COLOR_CYAN);
	putchar(' ');
	putchar(' ');
	printf(points);
	putchar('\n');
	for (int i = 1; i < FIELD_HEIGHT - 1; i++) {
		putchar_cl(FENCE, VGA_COLOR_CYAN);
		for (int j = 1; j < FIELD_LEN - 1; j++) {
			if (j == head_x && i == head_y) putchar(SNAKE_HEAD);
			else if (i == food_y && j == food_x) drow_food(i + j); // 4 2 5 6 8 
			else if (is[i][j]) putchar(SNAKE_BODY);
			else putchar(' ');
		}
		putchar_cl(FENCE, VGA_COLOR_CYAN);
		putchar('\n');
	}
	for (int i = 0; i < FIELD_LEN; i++) putchar_cl(FENCE, VGA_COLOR_CYAN);
	putchar('\n');
}

static void drow() {
	drow_field();
}

static char prev = 'd';

static int is_to_back(char button) {
	if ((prev == 'd' && button == 'a') || (prev == 'a' && button == 'd')) return 1;
	if ((prev == 'w' && button == 's') || (prev == 's' && button == 'w')) return 1;
	return 0;
}

static void update_snake(uint8_t *snake, uint8_t new_head) {
	for (int i = len - 2;; i--) {
		if (i < 0) break;
		snake[i + 1] = snake[i];
	}
	snake[0] = new_head;
}

int need_update;
static inline void self_eat_check(int y, int x) {
	if (is[y][x] == 1) ok = 0;
	need_update = 1;
}

static void give_food() {
	food_x = 1 + (snake_x[len / 2] + 101 + random_x) % (FIELD_LEN - 2);
	food_y = 1 + (snake_y[len / 2] + 97 + random_y) % (FIELD_HEIGHT - 2);	
}

static void snake_grow() {
	snake_x[len] = snake_x[len - 1];
	snake_y[len] = snake_y[len - 1];
	len++;
}

static bool check() {
	if (head_x <= 0 || head_x >= FIELD_LEN - 1 || head_y <= 0 || head_y >= FIELD_HEIGHT - 1 || ok <= 0) return 0;
	if (head_x == food_x && head_y == food_y) {
		points++;
		snake_grow();
		give_food();
	}
	return 1;
}

static void fast_redraw() {
	putchar_coord(' ', snake_y[len - 1], snake_x[len - 1]);
	putchar_coord(SNAKE_BODY, snake_y[1], snake_x[1]);
	putchar_coord(SNAKE_HEAD, head_y, head_x);
}

static bool mooved_on_frame;

static void move(char button) {
	need_update = 0;
	if (button == 'w')	{
		self_eat_check(head_y - 1, head_x);
		head_y--;	
	}
	else if (button == 's')	{
		self_eat_check(head_y + 1, head_x);
		head_y++;
	}
	else if (button == 'd') {
		self_eat_check(head_y, head_x + 1);
		head_x++;
	}
	else if (button == 'a') {
		self_eat_check(head_y, head_x - 1);
		head_x--;
	}
	if (need_update == 0) return;

	mooved_on_frame = true;
	is[snake_y[len - 1]][snake_x[len - 1]] = 0;
	update_snake(&snake_x[0], head_x);
	update_snake(&snake_y[0], head_y);
	is[snake_y[0]][snake_x[0]] = 1;
	// if (len > 1) fast_redraw();
}

static int stop = 0;

static void init() {
	head_x = FIELD_LEN / 2;
	head_y = FIELD_HEIGHT / 2;
	random_x = 13;
	random_y = 17;
	stop = 0;
	update_state(GAME);
	give_food();
	is[head_y][head_x] = 1;
	for (int i = 0; i < MAX_ROW + 10; i++) for (int j = 0;j < MAX_COL + 10; j++) is[i][j] = 0;
	for (int i = 0; i < (int)1e3; i++) {
		snake_x[i] = 0;
		snake_y[i] = 0;
	}
	snake_x[0] = head_x;
	snake_y[0] = head_y;
	len = 1;
	points = 0;
	ok = 1;
	prev = 'd';
}

void game::on_key_pressed(char new_key) {
	if (new_key > 0 && new_key != prev && !is_to_back(new_key)) {
		move(new_key);
		if (!check()) stop = 1;
		prev = new_key;
		if (new_key % 2 == 0) 
		{
			random_x = (random_x + new_key) % 55;
		}
		else
		{
			random_y = (random_y + new_key) % 55;
		}
	}
}

void game::start_snake() {
	init();

	for(;;) {
		mooved_on_frame = false;

		sleep(1);

		if (!mooved_on_frame) {
			move(prev);
		}
		if (!check() || stop) break;
		drow();
	}
	drow();
	sleep(5);
	clear_screen();
}

int game::restart_option() {
	printf("\nTo restart press r\n");
	wait_for_button_press('r');
	return 1;
}

void game::show_points() {
	printf("Congratulations!\nYour points:");
	int p = points;
	int arr[10];
	len = 0;
	while (p > 0) {
		arr[len++] = p % 10;
		p /= 10;
	}
	for (int i = len - 1; i >= 0; i--) {
		char c = arr[i] + '0';
		putchar(c);
	}
	if (len == 0) putchar('0');
}

void game::snake_menu() {
	for (int i = 0; i < (MAX_COL / 2) - 10; i++) putchar(' ');
	printf("STANDALONE SNAKE OS\n\n\n", VGA_COLOR_CYAN);	
	printf("Controlling during the game:\n", VGA_COLOR_CYAN);
	printf("	w, a, s, d - for mouving\n");
	printf("	r - for pause\n");
	printf("Press r to start!!!\n", VGA_COLOR_CYAN);
	for (int i = 0; i < MAX_ROW - 10; i++) putchar('\n');
	for (int i = 0; i < MAX_COL - 50; i++) putchar(' ');
	printf("v1.0, made by Antonov, Glotov, Toropin");
	wait_for_button_press('r');
	clear_screen();
	for (int i = 0; i < (MAX_ROW / 2) - 1; i++) putchar('\n');
	for (int i = 0; i < (MAX_COL / 2) - 5; i++) putchar(' ');
	printf("Good luck!");
	sleep(5);
	return;
}