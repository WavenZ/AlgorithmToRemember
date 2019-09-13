#include <iostream>
#include <memory>
#include <vector>

template <typename T>
struct Node {
	T key;
	std::shared_ptr<Node> parent, lchild, rchild;
	Node() = default;
	Node(T data) : key(data) {}
};

template<typename T>
class BSTree {
private:
	using callback = void(T data);
	using spNode = std::shared_ptr<Node<T>>;
private:
	spNode root;
	void _traverse(spNode node, callback visit) {
		if (node == nullptr) return;
		_traverse(node->lchild, visit);
		visit(node->key);
		_traverse(node->rchild, visit);
	}
	void _transplant(spNode u, spNode v) {
		if (u->parent == nullptr) {
			root = v;
			if (v) v->parent = nullptr;
		}
		else {
			if (u->key < u->parent->key)
				u->parent->lchild = v;
			else u->parent->rchild = v;
			if (v) v->parent = u->parent;
		}
	}
public:
	BSTree() : root(nullptr){}
	void insert(T key) {
		auto newNode = std::make_shared<Node<T>>(key);
		if (root == nullptr) {
			root = newNode; return;
		}
		spNode p = root, q = nullptr;
		while (p) {
			q = p;
			p = (key < p->key) ? p->lchild : p->rchild;
		}
		newNode->parent = q;
		if (key < q->key) q->lchild = newNode;
		else q->rchild = newNode;
	}
	void traverse(callback visit) {
		_traverse(root, visit);
	}
	bool search(T key) {
		spNode p = root;
		while (1) {
			if (p == nullptr) return false;
			if (key == p->key) return true;
			else if(key < p->key) p = p->lchild;
			else p = p->rchild;
		}
	}
	void del(T key) {
		spNode p = root;
		while (1) {
			if (p == nullptr) return;
			if (key == p->key) break;
			else if (key < p->key) p = p->lchild;
			else p = p->rchild;
		}
		if (p->lchild == nullptr)
			_transplant(p, p->rchild);
		else if (p->rchild == nullptr)
			_transplant(p, p->lchild);
		else {
			spNode pSucceed = p->rchild;
			while (pSucceed->lchild) pSucceed = pSucceed->lchild;
			if (pSucceed != p->rchild) {
				_transplant(pSucceed, pSucceed->rchild);
				pSucceed->rchild = p->rchild;
				pSucceed->rchild->parent = pSucceed;
			}
			_transplant(p, pSucceed);
			pSucceed->lchild = p->lchild;
			pSucceed->lchild->parent = pSucceed;
		}
	}
};


int main(void) {
	BSTree<int> T;
	std::vector<int> V = { 3, 1, 8, 5, 7, 2, 9, 4, 6, 0 };
	for (const auto& data : V) {
		T.insert(data);
		std::cout << "Insert " << data << " : ";
		T.traverse([](int data) {
			std::cout << data << " ";
		});
		std::cout << std::endl;
	}
	for (const auto& data : V) {
		T.del(data);
		std::cout << "Delete " << data << " : ";
		T.traverse([](int data) {
			std::cout << data << " ";
		});
		std::cout << std::endl;
	}
	return 0;
}
