#include <iostream>

template<typename T>
struct Node {
	std::shared_ptr<Node> next;
	std::shared_ptr<Node> prev;
	T data;
	Node(T d):data(d), next(nullptr), prev(nullptr){}
};

template<typename T>
class DoublyLinkedList {
private:
	using callback = void(T);
private:
	std::shared_ptr<Node<T>> Head;
public:
	DoublyLinkedList() {
		Head = std::make_shared<Node<T>>(0);
	}
	void traverse(callback visit) {
		std::shared_ptr<Node<T>> p = Head->next;
		while (p) {
			visit(p->data);
			p = p->next;
		}
	}
	void push_back(T data) {
		std::shared_ptr<Node<T>> p = Head;
		while (p->next != nullptr)
			p = p->next;
		p->next = std::make_shared<Node<T>>(data);
		p->next->prev = p;
	}
	void push_front(T data) {
		auto newNode = std::make_shared<Node<T>>(data);
		newNode->prev = Head;
		if (Head->next) {
			newNode->next = Head->next;
			Head->next = newNode;
		}
	}
	void insert(int pos, T data) {
		if (pos < 0) return;	
		std::shared_ptr<Node<T>> p = Head;
		while (pos-- && p != nullptr) {
			p = p->next;
		}
		if (p == nullptr) return;
		else {
			auto newNode = std::make_shared<Node<T>>(data);
			newNode->prev = p;
			if (p->next) {
				newNode->next = p->next;
				p->next->prev = newNode;
			}
			p->next = newNode;
		}
	}
	void del(int pos) {
		if (pos < 0) return;
		std::shared_ptr<Node<T>> p = Head;
		while (pos-- && p->next != nullptr) {
			p = p->next;
		}
		if (p->next == nullptr) return;
		p->next = p->next->next;
		if (p->next) {
			p->next->prev = p;
		}
	}
};



int main(void) {
	DoublyLinkedList<int> L;
	for (int i = 1; i < 10; ++i) {
		L.push_back(i);
	}
	L.push_front(0);
	L.insert(0, 250);
	L.insert(12, 250);
	L.del(0);
	L.del(11);
	L.traverse([](int data) {
		std::cout << data << " "; });
	std::cout << std::endl;
}
