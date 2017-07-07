#include <standalone_snake_game.h>
#include <keyboard_communicator.h>
#include <queue.h>

static int head_x;
static int head_y;
static int len;

static int is[MAX_ROW + 10][MAX_COL + 10];

static int snake_x[(int)1e3];
static int snake_y[(int)1e3];

static int food_x;
static int food_y;
static int random_x;
static int random_y;

static const int FIELD_LEN = MAX_COL - 10;
static const int FIELD_HEIGHT = MAX_ROW;

static const char FENCE = '#';
static const char SNAKE_HEAD = '0';
static const char SNAKE_BODY = '*';
static const char FOOD = '$';

static int ok = 1;

static int points = 0;

static void drow_food(int i) {
	if (i % 5 == 0)  {
		putchar_cl(FOOD, 4);
		return;
	}
	if (i % 5 == 1)  {
		putchar_cl(FOOD, 6);
		return;
	}
	if (i % 5 == 2)  {
		putchar_cl(FOOD, 10);
		return;
	}
	if (i % 5 == 3)  {
		putchar_cl(FOOD, 5);
		return;
	}
	putchar_cl(FOOD, 9);
	
}

static void drow_field() {
	fast_clear_screen();
	for (int i = 0; i < FIELD_LEN; i++) putchar_cl(FENCE, BLUE);
	putchar('\n');
	for (int i = 1; i < FIELD_HEIGHT - 1; i++) {
		putchar_cl(FENCE, BLUE);
		for (int j = 1; j < FIELD_LEN - 1; j++) {
			if (j == head_x && i == head_y) putchar(SNAKE_HEAD);
			else if (i == food_y && j == food_x) drow_food(i + j); // 4 2 5 6 8 
			else if (is[i][j] == 1) putchar(SNAKE_BODY);
			else putchar(' ');
		}
		putchar_cl(FENCE, BLUE);
		putchar('\n');
	}
	for (int i = 0; i < FIELD_LEN; i++) putchar_cl(FENCE, BLUE);
	putchar('\n');
}

static void drow() {
	drow_field();
}

static char get_key_pressed_demo() {
	static int cnt = 0;
	cnt++;
	if (cnt >= 16 && 27 > cnt) return 's';
	if (cnt >= 27 && 45 > cnt) return 'a';
	if (cnt >= 45 && 60 > cnt) return 'w';
	if (cnt == 60) cnt = 0;
	return 'd';	
}

static char prev = 'd';

static int is_to_back(char button) {
	if ((prev == 'd' && button == 'a') || (prev == 'a' && button == 'd')) return 1;
	if ((prev == 'w' && button == 's') || (prev == 's' && button == 'w')) return 1;
	return 0;
}

static char get_key_pressed() {
	char button = get_pressed_button();
	if (button != prev && button != 0) {
		if (is_to_back(button)) return prev;
		prev = button;
	}
	return prev;
}

static void update_snake(int *snake, int new_head) {
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

	is[snake_y[len - 1]][snake_x[len - 1]] = 0;
	update_snake(&snake_x[0], head_x);
	update_snake(&snake_y[0], head_y);
	is[snake_y[0]][snake_x[0]] = 1;
}

static void give_food() {
	food_x = 1 + (snake_x[len / 2] + 101 + random_x) % (FIELD_LEN - 2);
	food_y = 1 + (snake_y[len / 2] + 97 + random_y) % (FIELD_HEIGHT - 2);
	while (is[food_x][food_y] != 0) {
		food_x = 1 + (food_x + snake_x[len / 2] + 37 + random_x) % (FIELD_LEN - 2);
		food_y = 1 + (food_y + snake_y[len / 2] + 37 + random_y) % (FIELD_HEIGHT - 2);
	}
	
}

static void snake_grow() {
	snake_x[len] = snake_x[len - 1];
	snake_y[len] = snake_y[len - 1];
	len++;
}

static int check() {
	if (head_x <= 0 || head_x >= FIELD_LEN - 1 || head_y <= 0 || head_y >= FIELD_HEIGHT - 1 || ok <= 0) return 0;
	if (head_x == food_x && head_y == food_y) {
		points++;
		snake_grow();
		give_food();
	}
	return 1;
}

static void init() {
	head_x = FIELD_LEN / 2;
	head_y = FIELD_HEIGHT / 2;
	random_x = 13;
	random_y = 17;
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

static void very_bad_sleep(int x) {
	int j = 0;
	for (int i = 0; i < x * (int) 2e6; i++) {
		j++;
		if ((x == 1) && (i % 5 == 0)) {
			char new_key = check_io_port();
			if (new_key > 0 && new_key != prev && !is_to_back(new_key)) {
				queue_push(new_key);
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
	}
}

void start_snake() {
	init();

	int stop = 0;
	for(;;) {
		very_bad_sleep(1);

		queue_push(get_key_pressed());
		while ((get_size() > 0) && (stop <= 0)) {
			move(queue_pop());
			if (check() <= 0) stop = 1;
		}
		drow();
		if (stop) break;
	}
	drow();
	very_bad_sleep(2);
	clear_screen();
}

static inline void show_message(char word[]) {
	for (int i = 0; word[i] != '$'; i++) putchar(word[i]);
}

static inline void show_message2(char word[]) {
	for (int i = 0; word[i] != '$'; i++) putchar_cl(word[i], BLUE);
}

int restart_option() {
	char b = 0;
	show_message("\nTo restart press r\n $");
	while (1) {
		b = get_key_pressed();
		if (b == 'r') {
			return 1;
		}
	}
}

void show_points() {
	show_message("Congratulations!\nYour points: $");
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

void snake_menu() {
	for (int i = 0; i < (MAX_COL / 2) - 10; i++) putchar(' ');
	show_message2("STANDALONE SNAKE OS\n\n\n$");	
	show_message2("Controlling during the game:\n$");
	show_message("	w, a, s, d - for mouving\n$");
	show_message("	r - for pause\n$");
	show_message2("Press r to start!!!\n$");
	for (int i = 0; i < MAX_ROW - 10; i++) putchar('\n');
	for (int i = 0; i < MAX_COL - 50; i++) putchar(' ');
	show_message("v1.0, made by Antonov, Glotov, Toropin$");
	char b = 0;
	while (1) {
		b = get_key_pressed();
		if (b == 'r') {
			clear_screen();
			for (int i = 0; i < (MAX_ROW / 2) - 1; i++) putchar('\n');
			for (int i = 0; i < (MAX_COL / 2) - 5; i++) putchar(' ');
			show_message("Good luck!$");
			very_bad_sleep(50);
			return;
		}
	}

}