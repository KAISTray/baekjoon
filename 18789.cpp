#include <iostream>
#include <Windows.h>

#include <algorithm>
#include <functional>
#include <random>
#include <ctime>

#include <set>
#include <vector>
#include <tuple>

#define fastio cin.sync_with_stdio(false), cin.tie(0), std::cout.tie(0)

using namespace std;

HWND cwindow = GetConsoleWindow();
bool exit_requested = false;

// �ܼ� ���� �ֱ� (���� ���� Ƚ���� ����)
const int FRAME_RATE = 150;

void hide_cursor() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };

	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


// !-- Variables and data structures --!

struct DFSNode {
	int depth;
	int x, y;
	int padding;
};

// ���� �����͸� ��Ƽ������ �̿�
template<typename Ty>
class VectorStack {
private:
	vector<Ty> stack;
	size_t peek = 0;

public:
	VectorStack(size_t initial_capacity = 8) {
		stack.resize(initial_capacity);
	}

	bool empty() {
		return peek <= 0;
	}

	template<typename... Args>
	void push(Args&& ...args) {
		if (peek >= stack.capacity()) {
			stack.resize(stack.capacity() << 1ULL);
		}
		stack[peek++] = Ty{ std::forward<Args>(args)... };
	}

	Ty pop() {
		if (peek <= 0) throw out_of_range("Stack is empty!");
		return stack[--peek];
	}

	Ty top() {
		if (peek <= 0) throw out_of_range("Stack is empty!");
		return stack[peek - 1];
	}

	size_t size() {
		return peek;
	}

	void clear() {
		peek = 0;
	}
};

// ���̺��� ũ��
const int width = 14, height = 8;

using pos_t = set<pair<int, int>>;
struct table_t {
	int data[height][width]; 
	pos_t positions[10]; // 0 ~ 9 �ڸ������� ��� ��ǥ�� ��ġ���ִ��� �����ϱ� ���� set
};

// ���̺� ���� ������
table_t __t1, __t2;

// ���� ���̺�(current, e1)�� ���̵� ���̺�(sandbox, e2)�� ���� ��ü�� ���� ���̺� ������
table_t* current = &__t1, * sandbox = &__t2;

// ������� ���̵� ���̺� �� ���� �ְ������� �� ���̺��� ������ ������ �迭
int maximal[height][width];

// ���̺��� ������ ���ϱ� ���� ���� DFS Ʈ���� ���
VectorStack<DFSNode> branches;

/**
* ������ ������ �������� Ž���� DFS ���� ������ ��ǥ�� ��´�.
* 
* e.g. ���� 3049������ �����ϰ� 3050������ ������ �������� ���, Ž�� ���̰� 3�̰� ���̺� ���� '5'�� ��ǥ���� ����
*/
set<pair<int, int>> failed_at;

// ������ ���� �ڸ����� �����Ͽ� ������ ĳ�� �迭
// ������ i(i >= 1)��° �ڸ����� �ش� �迭�� i - 1��° �ε����� ����ȴ�.
int digits[64];
int digit_len = 0;

/**
* �־��� num�� ���� ���� �ڸ��� ���� ����� ���� ���� digits�� �����Ѵ�.
* 
* @effect global digits num�� ���� �ڸ����� ������ ���
* @effect global digit_len num�� ���� �ڸ����� ����
*/
void get_digits(int num) {
	digits[0] = 0, digit_len = 0;

	do
	{
		digits[digit_len++] = num % 10;
		num /= 10;
	} while (num > 0);
}

/**
* cin���κ��� ���� �迭�� ���� �� ���� ����, �� ������ �޾� table�� �Է¹��� ���� �����Ѵ�.
*/
void read_table(table_t& table) {
	pos_t(&pos)[10] = table.positions;

	char read;
	pair<int, int> pair;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			cin >> read;
			read -= '0';
			table.data[y][x] = read;
			pos[read].emplace(x, y);
		}
	}
}

// ������ ������ ��ȸ�� �� ����ϴ� �ε��� �����ֵ� (������ y ������, �� ������ x ������)
namespace adjacent {
	const int revolve[] = { -1, -1, -1, 0, 0, 1, 1, 1, -1, 0, 1, -1, 1, -1, 0, 1 };

	const int revolve_nw[] = { 0, 1, 1, 1, 0, 1 };
	const int revolve_ne[] = { 0, 1, 1, -1, -1, 0 };
	const int revolve_sw[] = { -1, -1, 0, 0, 1, 1 };
	const int revolve_se[] = { -1, -1, 0, -1, 0, -1 };

	const int revolve_n[] = { 0, 0, 1, 1, 1, -1, 1, -1, 0, 1 };
	const int revolve_e[] = { -1, -1, 0, 1, 1, -1, 0, -1, -1, 0 };
	const int revolve_w[] = { -1, -1, 0, 1, 1, 0, 1, 1, 0, 1 };
	const int revolve_s[] = { -1, -1, -1, 0, 0, -1, 0, 1, -1, 1 };
}

/**
* ��ǥ (x, y)�� �־��� ��, ���̺� ������ ���� ������ ���� ������ �������� ��ȯ�Ѵ�.
* (x, y) ���� ������ ���� ��ǥ�� (x + offset[i + length], y + offset[i])�̴�.
* 
* @returns (������ �������� ����, ������ �迭)
*/
pair<int, const int*> adjacent_range(const int x, const int y) {
	if (x == 0) {
		if (y == 0) {
			return make_pair(3, adjacent::revolve_nw);
		}
		else if (y >= height - 1) {
			return make_pair(3, adjacent::revolve_sw);
		}
		else return make_pair(5, adjacent::revolve_w);
	}
	else if (x >= width - 1) {
		if (y == 0) {
			return make_pair(3, adjacent::revolve_ne);
		}
		else if (y >= height - 1) {
			return make_pair(3, adjacent::revolve_se);
		}
		else return make_pair(5, adjacent::revolve_e);
	}
	else if (y == 0) {
		return make_pair(5, adjacent::revolve_n);
	}
	else if (y >= height - 1) {
		return make_pair(5, adjacent::revolve_s);
	}
	else return make_pair(8, adjacent::revolve);
}


// !-- Random generators and probability --!

// ���� ���ø��� ���� �õ�
const int random_seed = (int)time(0);

mt19937 mt(random_seed);

// ���� �ڸ��� ���� ���� ����
uniform_int_distribution<> sample(0, 9);

// ���̺� �� ���� ��ǥ ����
uniform_int_distribution<> rand_x(0, width - 1);
uniform_int_distribution<> rand_y(0, height - 1);

// Unbiased coin flip�� ���� [0, 1] �յ� ����
uniform_real_distribution<> uniform(0, 1);


// !-- Heuristics --!

/**
* �޸���ƽ �Լ��� Ÿ���� ������ ���� ������ ������ � ���ڸ� �����ؾ� ���� �����ϴ� �Լ���.
* 
* @param x �޸���ƽ �Լ��� ������� ������ ���� x ��ǥ
* @param y �޸���ƽ �Լ��� ������� ������ ���� y ��ǥ
* @param origin �޸���ƽ �Լ��� �����ϱ� ������ ���̺� ����
* @param score �޸���ƽ �Լ��� �����ϱ� ������ ���̺��� ���� ����
* 
* �߰������� �޸���ƽ �Լ��� �ۼ��� �� ����� �� �ִ� ���� ������ ������ ����.
* 
* @global failed_at ���� ���̺����� ������ ������ ���� ������ ��ǥ
*/
using heuristic_func = std::function<int(const int&, const int&, const table_t&, const int&)>;

// �޸���ƽ �Լ� ����
namespace heuristic {

	int random(const int& x, const int& y, const table_t& origin, const int& score) {
		return sample(mt) : origin.data[y][x];
	}
	
}

/**
* ������ �� ���� ���� ���̺��� origin, ���� ���̺��� ������ score�� ������� ���̵� sandbox ���̺��� ���� ������ ���ϴ� �Լ�
* �޸���ƽ �Լ��� heuristic�� ���� ���̸� �����Ѵ�.
* 
* @effect sandbox �޸���ƽ �Լ��� ���� �ش� ���̺��� �� ��ǥ���� �ڸ��� ���̸� �����Ѵ�.
*/
void mutate(table_t& sandbox, const table_t& origin, const int& score, heuristic_func const&& heuristic) {
	pos_t(&pos)[10] = sandbox.positions;

	int prev, next;
	pair<int, int> pair;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			prev = sandbox.data[y][x], next = heuristic(x, y, origin, score);

			if (prev != next) {
				pair.first = x;
				pair.second = y;

				auto it = pos[prev].find(pair);
				if (it != pos[prev].end()) {
					pos[prev].erase(it);
				}

				pos[next].emplace(x, y);

				sandbox.data[y][x] = next;
			}
		}
	}
}

// ���� �������� ���̺� �� �ڸ����� �����Ѵ�.
void random_twist(table_t& table) {
	mutate(table, *current, 0, heuristic::random);
}


// !-- Simulated annealing and evaluation function --!

// ������� ���������� �ְ� ������ ������ �� �ڸ����� ����
int current_score = 0, current_maxlen = 1;

// ���� �Լ��� ���� ���̸� �õ��� �� Ƚ��
unsigned long long generation = 0;

/**
* �־��� ���̺��� num�� �ڸ����� ������ �� �ִ� sequence�� �ִ��� DFS�� �˻��Ѵ�.
* 
* @return table ������ num sequence�� ���� ����
* 
* @effect global failed_at ���� ������ ���̺����� ������ �����ϰ� �� ����(�Ϲ������� ���� ���̺��� �ְ����� + 1)�� ������ ���� ������ ��� �����Ѵ�.
*/
bool has_value(const table_t &table, int num) {
	const pos_t (&pos)[10] = table.positions;

	get_digits(num);
	failed_at.clear();

	if (digit_len == 1) {
		if (pos[digits[0]].empty()) {
			return false;
		}
		return true;
	}

	branches.clear();
	for (auto& start : pos[digits[digit_len - 1]]) {
		branches.push(1, start.first, start.second);
	}

	int x, y, i;
	bool terminal;

	while (!branches.empty())
	{
		terminal = true;
		DFSNode branch = branches.pop();

		pair<int, const int*> adj = adjacent_range(branch.x, branch.y);

		for (i = 0; i < adj.first; ++i) {
			x = branch.x + adj.second[adj.first + i];
			y = branch.y + adj.second[i];

			// if (x < 0 || y < 0 || x >= width || y >= height) continue;

			if (table.data[y][x] == digits[digit_len - 1 - branch.depth]) {
				terminal = false;

				if (branch.depth + 1 >= digit_len) {
					return true;
				}
				else {
					branches.push(branch.depth + 1, x, y);
				}
			}
		}
		
		i = table.data[branch.y][branch.x];

		// We can assume that there should exist an unmatched branch at last score.
		if (num > current_score && terminal && i == (num / 10) % 10 && branch.depth == current_maxlen - 1) {
			failed_at.emplace(branch.x, branch.y);
		}
	}
	return false;
}

// ���̺��� ���� ������ ���Ѵ�.
int evaluate(const table_t &table) {
	int score = 1;
	bool exist;

	while (exist = has_value(table, score)) {
		if (exist) ++score;
	}

	return score - 1;
}

/**
* ���� �Լ��κ��� ���� �����ظ� �����س��� ���� simulated annealing �˰������� �����Ѵ�.
* 
* Simulated annealing �˰������� �ʱ� �µ��� �־�����, �µ��� ������(decay)���� �����Ͽ� �Ѱ���(limit)���� �������� ���� ������ ���� ���μ����� �����Ѵ�.
* 
* 1. ���� ����(current)�� �� ��(current ���̺��� ����)�� ����Ѵ�.
* 2. ���� ���¿� ������ �޸���ƽ �Լ��� ���̸� �����Ͽ� ���� ���̺�(sandbox)�� �����Ѵ�.
* 3. ���� ���̺��� �� ������ ����Ѵ�.
* 
* 4. �� ������ ���� ������ ���� ���Ŀ� �ִ´�. (�� ������ �������� �� �ð����� ������)
* 
* p = P(���̵� ���̺��� ä���� Ȯ������) = e^[ {����(sandbox) - ����(current)} / (�µ� * ������ ���) ]
* 
* 5. �� p�� ���� ���� ���̺��� ���̵� ���̺��� ���� ��ü������ ���ΰ� �����Ѵ�.
* ���� ���̵� ���̺�(sandbox)�� ������ �� ���� ���, e�� �����δ� ����� �Ǿ� p�� 1�� �Ѱ� �ȴ�.
* (��, ������ ���̸� ä���ϰ� �ȴ�.)
* 
* �� �̿ܿ��� p�� ���� ���̸� ä������ ���� Ȯ�������� �����Ѵ�.
*
* 6. �µ�(temperature)�� �Ѱ� �µ�(limit)�� �ٴٸ� ������ 1 ~ 5 ������ �ݺ��Ѵ�.
* 
* ��� ���̵� ���̺��� ���� �������� ������, *�Ǵٸ� ���� �����ذ� ���� �����غ��� ���� ���ɼ��� �����Ƿ� �װ� �븮�� �˰������̴�.*
* (��, �ð����⵵�� ��û ���� Ǯ�� ����� ���������� ��Ʈ��ŷ���� ����)
* 
* ���⼭ ������ ������ ���� ���̴� i) ���� ���� ����, ii) ���� �µ��� ����, iii) ������ ����� �������� �� �Ͼ��.
* �޸���ƽ�� �� ¥�� �͵� ���� �߿�������, ������ �Ӱ� �µ�, ������ ����� ã�� ������ ��Ʈ��ŷ ������ �����ŭ ����� ���� �����ϴ� �͵� �߿��ϴ�!
*
* @param temperature �ʱ� �µ� (> 0)
* @param decay �µ��� ������ (0 < decay < 1)
* @param limit �Ӱ� �µ� (< temperature)
* @param boltzmann ������ ��� (> 0)
*/
int annealing(double temperature, double decay, double limit, double boltzmann = 10.0) {

	// �� ������ ���� ���� (�� ������ ���)
	int e1, e2;
	table_t* temp;

	// ��� ���ſ�
	int fps = 0;
	COORD reset_pos = { 0, 0 };

	// �ʱ� ���̺� ���� ���
	e1 = evaluate(*current);

	if (e1 > current_score) {
		current_score = e1;
		current_maxlen = digit_len;
		memcpy(maximal, current, sizeof(int) * width * height);
	}

	// ����� �µ��� �Ѱ� �µ��� �ٴٸ� ������ (Ȥ�� ESC�� �ߴ� ����)
	while (!exit_requested && temperature > limit) {

		exit_requested = (GetAsyncKeyState(VK_ESCAPE) && (GetForegroundWindow() == cwindow));

		// Mutate the sandbox table using some heuristic functions.
		// �̰��� ������ �޸���ƽ�� �־� sandbox ���̺��� ���̽�Ų��.

		e2 = evaluate(*sandbox);
		
		// ���̵� ���̺��� ä���� Ȯ���� ������ ���� ����Ѵ�.
		double prob = exp((e2 - e1) / (boltzmann * temperature));
		if (uniform(mt) <= prob) {
			temp = current;
			current = sandbox;
			sandbox = temp;

			e1 = e2;
		}
		temperature *= decay; // �µ��� ������(decay)��ŭ ���������� �ٿ�������.
		++generation;

		// �ְ����� ���� ����
		if (e2 > current_score) {
			current_score = e2;
			current_maxlen = digit_len;

			memcpy(maximal, current, sizeof(int) * width * height);
		}

		// prints realtime debugging data
		if (++fps >= FRAME_RATE) {
			fps = 0;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), reset_pos);
			
			std::cout << current_score << '\n';
			
			std::cout << "Currently tracked: "  << e1 << '\n';
			std::cout << "Current temperature: " << temperature << '\n';
			
			std::cout << "Generations: " << generation << "        \n";
		}
	}

	return current_score;
}

int main() {
	hide_cursor();

	FILE *stream = freopen("test.txt", "r", stdin);

	double temperature, decay, limit, boltzmann;
	std::cin >> temperature >> decay >> limit >> boltzmann;

	read_table(*current);
	
	fclose(stream);
	
	if (stream != nullptr)
	
	clock_t start = clock(), end;

	int score = annealing(temperature, decay, limit, boltzmann);
	std::cout << '\n';

	end = clock();

	std::cout << "[�ְ����� ���̺�]\n\n";
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			std::cout << (int)maximal[y][x];
		}
		std::cout << '\n';
	}

	std::cout << "\n\n[������� ���̵� ���̺�]\n\n";
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			std::cout << (int)current->data[y][x];
		}
		std::cout << '\n';
	}
	
	std::cout << '\n';
	std::cout << "�ְ�����: " << score << '\n';
	std::cout << "�ɸ� �ð�: " << (end - start) << " ms\n";

	return 0;
}
