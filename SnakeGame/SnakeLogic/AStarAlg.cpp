#include "Snake.h"
#include "Point.h"
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>

extern const char XMAX;
extern const char YMAX;

bool IsSnakePos(int, int, Snake*&);
void AStarXDAlg(Snake*& snake, Point& point);

struct Node {
    int x, y;
    int g, h;
    Node* parent;

    Node(int x, int y, int g, int h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    int f() const {
        return g + h;
    }

    bool operator>(const Node& other) const {
        return this->f() > other.f();
    }
};

struct PointHasher {
    size_t operator()(const std::pair<int, int>& point) const {
        return std::hash<int>()(point.first) ^ std::hash<int>()(point.second);
    }
};

std::vector<std::pair<int, int>> getNeighbors(int x, int y) {
    return { {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1} };
}

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool isValid(int x, int y) {
    return x >= 0 && x < XMAX && y >= 0 && y < YMAX;
}

void AStarAlg(Snake*& snake, Point& point) {
    Vector startPos = Vector(snake->head->pos->x, snake->head->pos->y);
    Vector goalPos = Vector(point.pos->x, point.pos->y);

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    std::unordered_map<std::pair<int, int>, Node*, PointHasher> allNodes;
    std::unordered_map<std::pair<int, int>, bool, PointHasher> closedList;

    Node* startNode = new Node(startPos.x, startPos.y, 0, heuristic(startPos.x, startPos.y, goalPos.x, goalPos.y));
    openList.push(*startNode);
    allNodes[{startPos.x, startPos.y}] = startNode;

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();
        closedList[{current.x, current.y}] = true;

        if (current.x == goalPos.x && current.y == goalPos.y) {
            Node* node = &current;
            // Traverse back to find the next move from start
            while (node->parent && node->parent->parent) {
                node = node->parent;
            }
            Vector nextMove = Vector(node->x - startPos.x, node->y - startPos.y);
            snake->head->updateDir(nextMove);
            return;
        }

        for (auto& neighborPos : getNeighbors(current.x, current.y)) {
            int nx = neighborPos.first;
            int ny = neighborPos.second;

            if (!isValid(nx, ny) || IsSnakePos(nx, ny, snake) || closedList[{nx, ny}]) {
                continue;
            }

            int g = current.g + 1;
            int h = heuristic(nx, ny, goalPos.x, goalPos.y);

            if (allNodes.find({ nx, ny }) == allNodes.end()) {
                Node* neighbor = new Node(nx, ny, g, h, new Node(current));
                openList.push(*neighbor);
                allNodes[{nx, ny}] = neighbor;
            }
            else if (g < allNodes[{nx, ny}]->g) {
                Node* neighbor = allNodes[{nx, ny}];
                neighbor->g = g;
                neighbor->parent = new Node(current);
                std::make_heap(const_cast<Node*>(&openList.top()), const_cast<Node*>(&openList.top()) + openList.size(), std::greater<Node>());
            }
        }
    }

    AStarXDAlg(snake, point);

    // If no path found, do nothing (or could handle differently if needed)
    return;
}