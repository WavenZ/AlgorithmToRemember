#include <stdio.h>
#include <stdlib.h>

#define LH 1	// 左高
#define EH 0	// 等高
#define RH -1	// 右高

typedef int ElemType;

typedef struct Node {
	ElemType data;
	int bf;
	struct Node* lchild, * rchild;
}Node, *AVLTree;

void R_Rotate(AVLTree* T) {
	Node* lc = (*T)->lchild;
	(*T)->lchild = lc->rchild;
	lc->rchild = *T; *T = lc;
} // R_Rotate
void L_Rotate(AVLTree* T) {
	Node* rc = (*T)->rchild;
	(*T)->rchild = rc->lchild;
	rc->lchild = *T, * T = rc;
} // L_Rotate


void LeftBalance(AVLTree* T) {
	// 对以指针T所指结点为根的二叉树做做平衡旋转处理
	// 算法结束时，指针T指向新的结点
	Node* lc = (*T)->lchild;
	Node* rd = NULL;
	switch (lc->bf)
	{
	case LH:	// LL型：新结点插入在*T的左孩子的左子树上面，作单右旋处理 
		(*T)->bf = lc->bf = EH;
		R_Rotate(T); break;
	case RH:	// LR型：新结点插入在*T的左孩子的右子树上面，作双旋转处理
		rd = lc->rchild;
		switch (rd->bf)
		{
		case LH: (*T)->bf = RH; lc->bf = EH; break;
		case EH: (*T)->bf = lc->bf = EH; break;
		case RH: (*T)->bf = EH; lc->bf = LH; break;
		} // switch(rd->bf)
		rd->bf = EH;
		L_Rotate((*T)->lchild);
		R_Rotate(T);
	} // switch
} // LeftBalance

void RightBalance(AVLTree* T) {
	// 对以指针T所指结点为根的二叉树作右平衡旋转处理
	// 算法结束时，指针T指向新的结点
	Node* rc = (*T)->rchild, *ld;
	switch (rc->bf) {
	case RH:	// RR型：新结点插入在*T的右孩子的右子树上面，作单旋转处理
		(*T)->bf = rc->bf = EH;
		L_Rotate(T); break;
	case LH:	// RL型：新结点插入在*T的右孩子的左子树上面，作双旋转处理
		ld = rc->lchild;
		switch (ld->bf) {
		case RH: (*T)->bf = LH; rc->bf = EH; break;
		case EH: (*T)->bf = rc->bf = EH; break;
		case LH: (*T)->bf = EH; rc->bf = RH; break;
		} // switch(ld->bf)
		ld->bf = EH;
		R_Rotate((*T)->rchild);
		L_Rotate(T);
	} // switch(rc->bf)
} // RightBalance

int InsertAVL(AVLTree* T, ElemType data) {
	if ((*T) == NULL) {
		*T = (Node*)malloc(sizeof(Node));
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->data = data;
		(*T)->bf = EH;
		return 1;
	}
	else {
		if (data == (*T)->data) {
			return 0;
		} // if
		if (data < (*T)->data) {
			if (InsertAVL_dev(&((*T)->lchild), data))
				switch ((*T)->bf) {
				case LH:
					LeftBalance(T); return 0;
				case EH:
					(*T)->bf = LH; return 1;
				case RH:
					(*T)->bf = EH; return 0;
				} // switch(T->bf)
		} // if
		else {
			if (InsertAVL_dev(&((*T)->rchild), data))
				switch ((*T)->bf) {
				case LH:
					(*T)->bf = EH; return 0;
				case EH:
					(*T)->bf = RH; return 1;
				case RH:
					RightBalance(T); return 0;
				} // switch(T->bf)
		} // else
	} // else
}

int main(void) {
	AVLTree T = NULL;
	for (int i = 0; i < 10; ++i) {
		InsertAVL(&T, i);
	}
	return 0;
}
