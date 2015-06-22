#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define get_tri_length(x) ((1+x)*x/2)
#define get_below_position(c,s) (c+s)
#define get_diagonal_position(c,s) (c+s+1)
#define max(x,y) ((x>y) ? x:y)

int max_sum = 0;
int max_count = 0;
int max_step = 0;
int move_sum_max_step = 0;
int elements[5050];
int cache[5050];

int move_sum(int next_pos, int next_step);
void move_count(int next_pos, int next_step, int current_sum);

int main() {
	int tc_count;
	int tri_length;
	int index;
	int next_pos;
	int sum;

	scanf(" %d", &tc_count);
	while (tc_count--) {
		// initialize
		memset(elements, -1, sizeof(elements));
		memset(cache, -1, sizeof(cache));
		max_sum = 0;
		max_count = 0;
		scanf(" %d", &max_step);
		move_sum_max_step = max_step - 1;
		// set triangle elements
		tri_length = get_tri_length(max_step);
		for (index = 0; index < tri_length; index++) {
			scanf(" %d", &(elements[index]));
		}
		// calculate maximum sum before bottom line
		sum = move_sum(0, 1);
		printf("[max_sum]%d\n", sum);
		next_pos = tri_length - max_step - (max_step - 1);
		// TODO : 전달할 sum 파악 필요 cache 해당 index 는 아님
		move_count(next_pos, move_sum_max_step, cache[next_pos]);
		printf("[max_count]%d\n", max_count);
	}
	return 0;
}

int move_sum(int next_pos, int next_step) {
	int below_sum = 0;
	int diagonal_sum = 0;
	int below_position;
	int diagonal_position;

	if (next_step == max_step) {
		return elements[next_pos];
	}
	if (cache[next_pos] != -1) {
		return cache[next_pos];
	}
	below_position = get_below_position(next_pos, next_step);
	diagonal_position = get_diagonal_position(next_pos, next_step);
	below_sum = move_sum(below_position, next_step + 1);
	diagonal_sum = move_sum(diagonal_position, next_step + 1);
	cache[next_pos] = elements[next_pos] + max(below_sum, diagonal_sum);

	return cache[next_pos];
}

void move_count(int next_pos, int next_step, int current_sum) {
	int sum;
	int below_position;
	int diagonal_position;
	int below_sum;
	int diagonal_sum;
	int index = 0;
	int count = 1;

	for (index = 0; index < next_step; index++) {
		below_position = get_below_position(next_pos, next_step);
		diagonal_position = get_diagonal_position(next_pos, next_step);
		below_sum = current_sum + elements[below_position];
		diagonal_sum = current_sum + elements[diagonal_position];

		sum = max(below_sum, diagonal_sum);
		if (below_sum == diagonal_sum) {
			count = 2;
		}
		else {
			count = 1;
		}
		if (sum > max_sum) {
			max_sum = sum;
			max_count = count;
		}
		else if (sum == max_sum) {
			max_count += count;
		}
		next_pos++;
	}
}
