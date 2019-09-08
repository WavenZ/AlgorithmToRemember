#include <iostream>
#include <memory>

template<typename T>
struct Node {
	T data;
	std::shared_ptr<Node<T>> next;
	Node(T d) : data(d), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
	using callback = void(T);
private:
	std::shared_ptr<Node<T>> Head;
public:
	LinkedList() {
		Head = std::make_shared<Node<T>>(0);
	}
	void traverse(callback visit) {
		std::shared_ptr<Node<T>> p = Head->next;
		while (p != nullptr) {
			visit(p->data);
			p = p->next;
		}
	}
	bool push_back(T data) {
		std::shared_ptr<Node<T>> p = Head;
		while (p->next != nullptr) {
			p = p->next;
		}
		p->next = std::make_shared<Node<T>>(data);
		return true;
	}
	bool push_front(T data) {
		std::shared_ptr<Node<T>> p = Head;
		auto new_p = std::make_shared<Node<T>>(data);
		new_p->next = p->next;
		p->next = new_p;
		return true;
	}
	bool insert(T data, int pos) {
		std::shared_ptr<Node<T>> p = Head;
		while (pos-- && p != nullptr) {
			p = p->next;
		}
		if (p == nullptr) return false;	// 插入位置越界
		else {
			auto new_p = std::make_shared<Node<T>>(data);
			new_p->next = p->next;
			p->next = new_p;
			return true;
		}
	}
	bool del(int pos) {
		std::shared_ptr<Node<T>> p = Head->next;
		decltype(p) q = nullptr;
		while (pos-- && p != nullptr) {
			q = p;
			p = p->next;
		}
		if (p == nullptr) return false;
		else {
			q->next = p->next;
			return true;
		}
	}
	void reverse() {
		if (Head->next == nullptr || Head->next->next == nullptr) return;
		auto pre = Head->next;
		auto cur = Head->next->next;
		auto nex = Head->next->next->next;
		pre->next = nullptr;
		while (nex != nullptr) {
			cur->next = pre;
			pre = cur; cur = nex; nex = nex->next;
		}
		cur->next = pre;
		Head->next = cur;
	}
	T mid() {
		std::shared_ptr<Node<T>> fast = Head, slow = Head;
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow->data;
	}
	T kToEnd(int k) {
		if (k <= 0) return Head->data;
		std::shared_ptr<Node<T>> fast = Head, slow = Head;
		while (k-- && fast != nullptr)
			fast = fast->next;
		if (fast == nullptr) return Head->data;
		while (fast != nullptr) {
			fast = fast->next;
			slow = slow->next;
		}
		return slow->data;
	}
	void sort(void) {
		std::shared_ptr<Node<T>> p = nullptr, q = nullptr, r = nullptr;
		while (r != Head->next) {
			p = Head; q = Head->next;
			while (q->next != nullptr && q->next != r) // 小于，指针后移
				if (q->data < q->next->data) {
					p = q;
					q = q->next;
				}
				else {	// 大于，交换
					p->next = q->next;
					q->next = q->next->next;
					p->next->next = q;
					p = p->next;
				}
			r = q;
		}
	}
	void merge(LinkedList<T>& L) {
		std::shared_ptr<Node<T>> pa = Head->next, pb = L.Head->next;
		std::shared_ptr<Node<T>> p = Head;
		while (pa && pb) {
			if (pa->data < pb->data) {
				p->next = pa; p = pa; pa = pa->next;
			}
			else {
				p->next = pb; p = pb; pb = pb->next;
			}
		}
		p->next = pa ? pa : pb;
		L.Head->next = nullptr;
	}
};

int main(void) {
	LinkedList<int> list1, list2;
	for (int i = 0; i < 10; i+=2) {
		list1.push_back(i);
	}
	for (int i = 1; i < 10; i+=2) {
		list2.push_back(i);
	}
	list1.merge(list2);
	list1.traverse([](int data) {
		std::cout << data << " ";
	});
	std::cout << std::endl;
	list2.traverse([](int data) {
		std::cout << data << " ";
	});
	return 0;
}
