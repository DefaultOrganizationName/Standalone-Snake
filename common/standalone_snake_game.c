#include <standalone_snake_game.h>

int head_x;
int head_y;
int len;

int is[MAX_ROW][MAX_COL];

int snake_x[(int)1e3];
int snake_y[(int)1e3];

int food_x;
int food_y;

int points;

const int FIELD_LEN = MAX_COL - 10;
const int FIELD_HEIGHT = MAX_ROW;

const char FENCE = '#';
const char SNAKE_HEAD = '0';
const char SNAKE_BODY = '*';
const char FOOD = '$';

int ok = 1;

static void drow_field() {
	clear_screen();
	for (int i = 0; i < FIELD_LEN; i++) putchar(FENCE);
	putchar('\n');
	for (int i = 1; i < FIELD_HEIGHT - 1; i++) {
		putchar(FENCE);
		for (int j = 1; j < FIELD_LEN - 1; j++) {
			if (j == head_x && i == head_y) putchar(SNAKE_HEAD);
			else if (i == food_y && j == food_x) putchar(FOOD);
			else if (is[i][j] == 1) putchar(SNAKE_BODY);
			else putchar(' ');
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

static char get_key_pressed() {
	static int cnt = 0;
	cnt++;
	if (cnt >=19 && 20 > cnt) return 's';
	if (cnt >= 20 && 29 > cnt) return 'a';
	if (cnt >= 29 && 45 > cnt) return 'w';
	return 'd';
}

static void update_snake(int *snake, int new_head) {
	for (int i = len - 2;; i--) {
		if (i < 0) break;
		snake[i + 1] = snake[i];
	}
	snake[0] = new_head;
}

static inline void self_eat_check(int y, int x) {
	if (is[y][x] == 1) ok = 0;
}

static void move() {
	char button = get_key_pressed();
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
	is[snake_y[len - 1]][snake_x [len- 1]] = 0;
	update_snake(&snake_x[0], head_x);
	update_snake(&snake_y[0], head_y);
	is[snake_y[0]][snake_x[0]] = 1;
	return;
}

void give_food() {
	// food_x = 1 + (head_x + 100) % (FIELD_LEN - 2);
	// food_y = 1 + (head_y + 100) % (FIELD_HEIGHT - 2);
	food_x = 1 + (head_x + 1) % (FIELD_LEN - 2);
	food_y = head_y;
}

void snake_grow() {
	snake_x[len] = snake_x[len - 1];
	snake_y[len] = snake_y[len - 1];
	len++;
}

static int check() {
	if (head_x <= 0 || head_x >= FIELD_LEN || head_y <= 0 || head_y >= FIELD_HEIGHT || ok <= 0) return 0;
	if (head_x == food_x && head_y == food_y) {
		points++;
		snake_grow();
		give_food();
	}
	return 1;
}

static void init() {
	for (int i = 0; i < (int)1e3 - 1; i++) snake_x[i] = -1;
	for (int i = 0; i < (int)1e3 - 1; i++) snake_y[i] = -1;
	head_x = FIELD_LEN / 2;
	head_y = FIELD_HEIGHT / 2;
	give_food();
	is[head_y][head_x] = 1;
	snake_x[0] = head_x;
	snake_y[0] = head_y;
	len = 1;
	points = 0;
	ok = 1;
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
		if (check() <= 0) {
			break;
		}
	}
	drow();
	very_bad_sleep();
	very_bad_sleep();
	clear_screen();
}