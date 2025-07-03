#include <iostream>
#include <conio.h>
#include <deque>
#include <vector>
#include <queue>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

struct Point {
    int x, y;
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Point& other) const { return !(*this == other); }
};

bool gameOver = false;
bool isAI = false;
Point food;
deque<Point> snake;
int score = 0;

void Setup() {
    gameOver = false;
    dir = STOP;
    score = 0;
    snake.clear();
    snake.push_back({ WIDTH / 2, HEIGHT / 2 });
    food = { rand() % WIDTH, rand() % HEIGHT };
}

void Draw() {
    system("cls");
    for (int i = 0; i < WIDTH + 2; ++i) cout << "#";
    cout << "\n";

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            Point p = { x, y };
            if (x == 0) cout << "#";

            if (p == snake.front()) cout << "O";
            else if (find(snake.begin(), snake.end(), p) != snake.end()) cout << "o";
            else if (p == food) cout << "F";
            else cout << " ";

            if (x == WIDTH - 1) cout << "#";
        }
        cout << "\n";
    }

    for (int i = 0; i < WIDTH + 2; ++i) cout << "#";
    cout << "\n";
    cout << "Score: " << score << "\n";
    cout << "Mode: " << (isAI ? "AI" : "Manual") << " | Press 'm' to toggle mode, 'x' to exit.\n";
}

bool bfsAI(Point start, Point target, Point& nextMove) {
    queue<Point> q;
    vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
    vector<vector<Point>> parent(HEIGHT, vector<Point>(WIDTH, { -1, -1 }));

    q.push(start);
    visited[start.y][start.x] = true;

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    while (!q.empty()) {
        Point current = q.front(); q.pop();
        if (current == target) break;

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            Point neighbor = { nx, ny };
            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT &&
                !visited[ny][nx] &&
                find(snake.begin(), snake.end(), neighbor) == snake.end()) {
                q.push(neighbor);
                visited[ny][nx] = true;
                parent[ny][nx] = current;
            }
        }
    }

    if (!visited[target.y][target.x]) return false;

    Point step = target;
    while (parent[step.y][step.x] != start) {
        step = parent[step.y][step.x];
    }

    nextMove = step;
    return true;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': dir = LEFT; break;
        case 'd': dir = RIGHT; break;
        case 'w': dir = UP; break;
        case 's': dir = DOWN; break;
        case 'x': gameOver = true; break;
        case 'm': isAI = !isAI; break;
        }
    }
}

void Logic() {
    Point head = snake.front();
    Point next;

    if (isAI) {
        if (!bfsAI(head, food, next)) {
            gameOver = true;
            return;
        }
    } else {
        switch (dir) {
        case LEFT: head.x--; break;
        case RIGHT: head.x++; break;
        case UP: head.y--; break;
        case DOWN: head.y++; break;
        default: return;
        }
        next = head;
    }

    if (next.x < 0 || next.x >= WIDTH || next.y < 0 || next.y >= HEIGHT ||
        find(snake.begin(), snake.end(), next) != snake.end()) {
        gameOver = true;
        return;
    }

    snake.push_front(next);
    if (next == food) {
        score++;
        food = { rand() % WIDTH, rand() % HEIGHT };
    } else {
        snake.pop_back();
    }
}

int main() {
    srand(time(0));

    do {
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(100);
        }

        Draw();
        cout << "\nGame Over! Final Score: " << score << "\n";

        if (!isAI) {
            cout << "Do you want to play again? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                gameOver = false;
            } else {
                break;
            }
        } else {
            break;
        }
    } while (true);

    cout << "Thanks for playing.\n";
    return 0;
}
