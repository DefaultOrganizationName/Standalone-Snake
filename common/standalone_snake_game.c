#include <standalone_snake_game.h>

static int head_x;
static int head_y;
static int len;

static int is[MAX_ROW + 10][MAX_COL + 10];

static int snake_x[(int)1e3];
static int snake_y[(int)1e3];

static int food_x;
static int food_y;

static const int FIELD_LEN = MAX_COL - 10;
static const int FIELD_HEIGHT = MAX_ROW;

static const char FENCE = '#';
static const char SNAKE_HEAD = '0';
static const char SNAKE_BODY = '*';
static const char FOOD = '$';

static int ok = 1;

static int points = 0;

static void drow_field() {
	fast_clear_screen();
	for (int i = 0; i < FIELD_LEN; i++) putchar_cl(FENCE, BLUE);
	putchar('\n');
	for (int i = 1; i < FIELD_HEIGHT - 1; i++) {
		putchar_cl(FENCE, BLUE);
		for (int j = 1; j < FIELD_LEN - 1; j++) {
			if (j == head_x && i == head_y) putchar(SNAKE_HEAD);
			else if (i == food_y && j == food_x) putchar(FOOD);
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
static char codes[300];

char get_pressed_button() {
	static int codes_got = 0;
	if (codes_got == 0) {
		codes_got = 1;
		for (int i = 0; i < 300; i++) codes[i] = 0;
		codes[0x1e] = 'a';
		codes[0x1f] = 's';
		codes[0x20] = 'd';
		codes[0x11] = 'w';
	}
	return codes[queue_pop()];

}
static char prev = 'd';
static char get_key_pressed() {
	char button = get_pressed_button();
	if (button != prev && button != 0) {
		if ((prev == 'd' && button == 'a') || (prev == 'a' && button == 'd')) return prev;
		if ((prev == 'w' && button == 's') || (prev == 's' && button == 'w')) return prev;
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

static void move() {
	char button = get_key_pressed();
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
	food_x = 1 + (snake_x[len / 2] + 100) % (FIELD_LEN - 2);
	food_y = 1 + (snake_y[len / 2] + 100) % (FIELD_HEIGHT - 2);
	// food_x = 1 + (head_x + 1) % (FIELD_LEN - 2);
	// food_y = head_y;
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


#define MAXQUEUEVALUE 5

int data[MAXQUEUEVALUE];
int first;
int size;

void queue_init()
    {
        int first = -1;
        int size = 0;
    }
void queue_push(int val) 
    {
        int position;
        if (first == -1) 
        {
            first = position = 0;
        } else {
            position = (first + size) % MAXQUEUEVALUE;
        }
        if (size == MAXQUEUEVALUE) 
        {
            first = (first + 1) % MAXQUEUEVALUE;
        } else {
            size++;
        }
        data[position] = val;
    }
int queue_pop() 
    {
        size--;
        int old_first = first;
        first = (first + 1) % MAXQUEUEVALUE;
        return data[old_first];
    }


static void init() {
	head_x = FIELD_LEN / 2;
	head_y = FIELD_HEIGHT / 2;
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
	queue_init();

}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}




static void very_bad_sleep(int x) {
	int j = 0;
	int c = 0;
	for (int i = 0; i < x * (int) 2e6; i++) {
		if (inb(0x60) != c)	{
			c = inb(0x60);
			if (c > 0) queue_push(c);
		}
		j++;
	}
}




void start_snake() {
	init();
	for(;;) {
		very_bad_sleep(1);
		move();
		if (check() <= 0) {
			break;
		}
		drow();
	}
	drow();
	very_bad_sleep(2);
	clear_screen();
}

int restart_option() {
	char b = 0;
	char word[] = {"\nTo restart press r\n $"};
	for (int i = 0; word[i] != '$'; i++) putchar(word[i]);
	while (1) {
		b = get_key_pressed();
		if (b == 'r') {
			return 1;
		}
	}
}

void show_points() {
	char word[] = {"Congratulations!\nYour points: $"};
	for (int i = 0; word[i] != '$'; i++) putchar(word[i]);
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