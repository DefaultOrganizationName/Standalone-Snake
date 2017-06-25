#include <standalone_snake_game.h>

int head_x;
int head_y;
int len;

int is_x[MAX_COL]; //1 if it is snake on this pos
int is_y[MAX_ROW]; //1 if it is snake on this pos

int snake_x[(int)1e3];
int snake_y[(int)1e3];

const int FIELD_LEN = MAX_COL - 10;
const int FIELD_HEIGHT = MAX_ROW;

const char FENCE = '#';
const char SNAKE_HEAD = '0';
const char SNAKE_BODY = '*';

static void drow_field() {
	clear_screen();
	for (int i = 0; i < FIELD_LEN; i++) putchar(FENCE);
	putchar('\n');
	for (int i = 1; i < FIELD_HEIGHT - 1; i++) {
		putchar(FENCE);
		for (int j = 1; j < FIELD_LEN - 1; j++) {
			if (is_x[j] == 1 && is_y[i] == 1) {
				if (j == head_x && i == head_y) putchar(SNAKE_HEAD);
				else putchar(SNAKE_BODY);
			} else putchar(' ');
		}
		putchar(FENCE);
		putchar('\n');
	}
	for (int i = 0; i < FIELD_LEN; i++) putchar(FENCE);
	putchar('\n');
}

static void drow() {
	drow_field();
}

char get_key_pressed() {
	return 's';
}

void update(int *snake, int *is) {
	is[snake[len - 1]] = 0;
	for (int i = len - 2;; i--) {
		if (i < 0) break;
		snake[i + 1] = snake[i];
	}
}

static void move() {
	char button = get_key_pressed();
	if (button == 'w') head_y--;
	else if (button == 's') head_y++;
	else if (button == 'd') head_x++;
	else if (button == 'a') head_x--;
	update(&snake_x[0], &is_x[0]);
	update(&snake_y[0], &is_y[0]);
	snake_x[0] = head_x;
	snake_y[0] = head_y;
	is_x[head_x] = 1;
	is_y[head_y] = 1;
	return;
}

static int check() {
	if (head_x <= 0 || head_x >= FIELD_LEN || head_y <= 0 || head_y >= FIELD_HEIGHT) return 0;
	return 1;
}

static void init() {
	for (int i = 0; i < (int)1e3 - 1; i++) snake_x[i] = -1;
	for (int i = 0; i < (int)1e3 - 1; i++) snake_y[i] = -1;
	head_x = FIELD_LEN / 2;
	head_y = FIELD_HEIGHT / 2;
	is_y[head_y] = 1;
	is_x[head_x] = 1;
	snake_x[0] = head_x;
	snake_y[0] = head_y;
	len = 1;
}

void very_bad_sleep() {
	int j = 0;
	for (int i = 0; i < (int) 2e7; i++) {
		j++;
	}
}

void start_snake() {
	init();
	for(;;) {
		very_bad_sleep();
		drow();
		move();
		if (check() <= 0) break;
	}
	clear_screen();
}