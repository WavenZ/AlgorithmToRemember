#include <iostream>
#include <memory>
#include <stack>

template<typename T>
struct Node {
	T data;
	std::shared_ptr<Node<T>> next;
	Node(T d) : data(d), next(nullptr) {}
};

template<typename T>
class stack {
private:
	using callback = void(T);
private:
	std::shared_ptr<Node<T>> Head;
public:
	stack() {
		Head = std::make_shared<Node<T>>(0);
	}
	void push(T data) {
		std::shared_ptr<Node<T>> p = Head;
		auto newNode = std::make_shared<Node<T>>(data);
		newNode->next = p->next;
		p->next = newNode;
	}
	void pop() {
		if (Head->next == nullptr) return;
		else {
			Head->next = Head->next->next;
		}
	}
	T top() {
		return Head->next->data;
	}
	bool empty() {
		return Head->next == nullptr;
	}
	void traverse(callback print) {
		std::shared_ptr<Node<T>> p = Head->next;
		while (p) {
			print(p->data);
			p = p->next;
		}
	}
};


int main(void) {
	stack<int> s;
	for (int i = 0; i < 10; ++i) {
		s.push(i);
	}
	s.traverse([](int data){
		std::cout << data << " ";});
	std::cout << std::endl;
	std::cout << s.top() << std::endl;
	while (!s.empty())
		s.pop();
	s.traverse([](int data) {
		std::cout << data << " "; });
	return 0;
}
