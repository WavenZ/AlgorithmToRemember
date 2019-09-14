#include <iostream>
#include <memory>

enum { LH, EH, RH };

template<typename ElemType>
struct Node {
	std::shared_ptr<Node> lchild, rchild;
	ElemType data;
	int bf;
	Node(ElemType Data, int Bf) : data(Data), bf(Bf) {}
}; // Node

template<typename ElemType>
class AVL_Tree {
private:
	using Callback = void(ElemType);
	using Tree = std::shared_ptr<Node<ElemType>>;
private:
	Tree root;
	void _R_Rotate(Tree &T) {
		Tree lc = T->lchild;
		T->lchild = lc->rchild;
		lc->rchild = T; T = lc;
	} // _R_Rotate
	void _L_Rotate(Tree &T) {
		Tree rc = T->rchild;
		T->rchild = rc->lchild;
		rc->lchild = T; T = rc;
	} // _L_Rotate
	void _LeftBalance(Tree &T) {
		// 对以指针T所指结点为根的二叉树做做平衡旋转处理
		// 算法结束时，指针T指向新的结点
		Tree lc = T->lchild, rd = nullptr;
		switch (lc->bf)
		{
		case LH:	// LL型：新结点插入在*T的左孩子的左子树上面，作单右旋处理 
			T->bf = lc->bf = EH;
			_R_Rotate(T); break;
		case RH:	// LR型：新结点插入在*T的左孩子的右子树上面，作双旋转处理
			rd = lc->rchild;
			switch (rd->bf)
			{
			case LH: T->bf = RH; lc->bf = EH; break;
			case EH: T->bf = lc->bf = EH; break;
			case RH: T->bf = EH; lc->bf = LH; break;
			} // switch(rd->bf)
			rd->bf = EH;
			_L_Rotate(T->lchild);
			_R_Rotate(T);
		} // switch
	} // _LeftBalance
	void _RightBalance(Tree &T) {
		// 对以指针T所指结点为根的二叉树作右平衡旋转处理
		// 算法结束时，指针T指向新的结点
		Tree rc = T->rchild, ld = nullptr;
		switch (rc->bf) {
		case RH:	// RR型：新结点插入在*T的右孩子的右子树上面，作单旋转处理
			T->bf = rc->bf = EH;
			_L_Rotate(T); break;
		case LH:	// RL型：新结点插入在*T的右孩子的左子树上面，作双旋转处理
			ld = rc->lchild;
			switch (ld->bf) {
			case RH: T->bf = LH; rc->bf = EH; break;
			case EH: T->bf = rc->bf = EH; break;
			case LH: T->bf = EH; rc->bf = RH; break;
			} // switch(ld->bf)
			ld->bf = EH;
			_R_Rotate(T->rchild);
			_L_Rotate(T);
		} // switch(rc->bf)
	} // RightBalance
	int _insert(Tree& T, ElemType data) {
		if (T == nullptr) {
			T = std::make_shared<Node<ElemType>>(data, EH);
			return 1;
		}
		else {
			if (data == T->data) {
				return 0;
			} // if
			if (data < T->data) {
				if (_insert(T->lchild, data))
					switch (T->bf) {
					case LH:
						_LeftBalance(T); return 0;
					case EH:
						T->bf = LH; return 1;
					case RH:
						T->bf = EH; return 0;
					} // switch(T->bf)
			} // if
			else {
				if (_insert(T->rchild, data))
					switch (T->bf) {
					case LH:
						T->bf = EH; return 0;
					case EH:
						T->bf = RH; return 1;
					case RH:
						_RightBalance(T); return 0;
					} // switch(T->bf)
			} // else
		} // else
	} // _insert
	void _traverse(const Tree& T, Callback visit) {
		if (T == nullptr) return;
		_traverse(T->lchild, visit);
		visit(T->data);
		_traverse(T->rchild, visit);
	} // _traverse
public:
	AVL_Tree() = default;
	void insert(ElemType data) {
		_insert(root, data);
	} // InsertAVL
	void traverse(Callback visit) {
		_traverse(root, visit);
	} // traverse
}; // AVL_Tree


int main(void) {
	AVL_Tree<int> T;
	for (int i = 0; i < 1000; ++i) {
		T.insert(i);
	}
	T.traverse([](int data) {
		std::cout << data << " "; });
	std::cout << std::endl;
	return 0;
} // main
