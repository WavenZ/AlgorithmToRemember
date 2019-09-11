#include <iostream>
#include <memory>
#include <queue>
template <typename T>
struct Node {
	T data;
	std::shared_ptr<Node> next;
	Node(T d) : data(d), next(nullptr) {}
	Node(): data(T{}), next(nullptr) {}
};

template<typename T>
class queue {
private:
	using callback = void(T);
private:
	std::shared_ptr<Node<T>> Front;
	std::shared_ptr<Node<T>> Back;
public:
	queue() {
		Front = std::make_shared<Node<T>>();
		Back = Front;
	}
	void push(T data) {
		auto newNode = std::make_shared<Node<T>>(data);
		Back->next = newNode;
		Back = Back->next;
	}
	bool empty() {
		return Front == Back;
	}
	void pop() {
		if (!empty()) 
			Front = Front->next;
		else {
			std::cerr << "Queue empty !\n";
		}
	}
	T front() {
		if (!empty())
			return Front->next->data;
		else {
			std::cerr << "Queue empty !\n";
			return T{};
		}
	}
	T back() {
		if (!empty())
			return Back->data;
		else {
			std::cerr << "Queue empty !\n";
			return T{};
		}
	}
	void traverse(callback visit) {
		if (empty()) return;
		else {
			auto p = Front->next;
			while (p) {
				visit(p.data);
				p = p->next;
			}
		}
	}
};

int main(void) {
	queue<int> Q;
	std::cout << Q.front() << std::endl;
	for (int i = 0; i < 10; ++i)
		Q.push(i);
	std::cout << Q.front() << " " << Q.back() << std::endl;
	while (!Q.empty()) {
		std::cout << Q.front() << " ";
		Q.pop();
	}
	
	std::cout << std::endl;
	return 0;
}
