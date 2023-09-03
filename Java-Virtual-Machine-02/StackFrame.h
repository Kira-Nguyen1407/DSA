#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>
#include <stack>

#define LOCAL_VARIABLE_SPACE_SIZE   256  

enum BalanceValue
{
	LH = -1,
	EH = 0,
	RH = 1
};

class Node{
    public:
        std::string key;
        std::string data;
        int dataType;
        Node* left;
        Node* right;
		Node* next;
        BalanceValue balance;

        Node(std::string data, int dataType, std::string key){
			this->key = key;
            this->data = data;
            this->dataType = dataType;
            this->left = this->right = nullptr;
			this->next = nullptr;
            this->balance = EH;
        }
		Node(std::string data, int dataType){
			this->key = "no key assigned to this node";
            this->data = data;
            this->dataType = dataType;
            this->left = this->right = nullptr;
			this->next = nullptr;
            this->balance = EH;
        }
        Node() : key("no key assigned to this node"), data("no data assigned to this node"), dataType(-1), left(nullptr), right(nullptr), next(nullptr), balance(EH){}
};

class AVL
{
	private:
		Node *root;
		int number_of_nodes;
	protected:
		
	public:
		AVL()
		{
			this->root = nullptr;
			number_of_nodes = 0;
		}

		Node *leftBalance(Node *&node, bool &taller);
		Node *rightBalance(Node *&node, bool &taller);
		//TODO Methods
		// Node *insertRec(Node *&node, const int &value, bool &taller);
		Node *AVLInsert(Node *&node, Node* newPtr, bool &taller);
		Node *AVLDelete(Node *&node, int value, bool &shorter, bool &success);
		Node* deleteRightBalance(Node* &node, bool &shorter);
		Node* deleteLeftBalance(Node* &node, bool &shorter);	
		bool AVLTreeIsFull();
		Node* AVLsearch(Node* node, std::string key);

		AVL(Node* root) : root(root) {}
		Node *rotateRight(Node *&node);
		Node *rotateLeft(Node *&node);
		
		
		// TODO Methods
		void insert(std::string data, int dataType, std::string key);
		void remove(const int &value);
		void prefixTraversal(Node* node);
		Node* getRoot(){return this->root;}
        Node* findParent(Node* node, std::string key);
};

// Node* AVL::deleteLeftBalance(Node* &node, bool &shorter){
// 	if(node->balance == RH){
// 		node->balance = EH;
// 	}
// 	else if(node->balance == EH){
// 		node->balance = LH;
// 		shorter = false;
// 	}
// 	else{
// 		Node* leftTree = node->left;
// 		if(leftTree->balance == RH){
// 			Node* rightTree = leftTree->right;
// 			if(rightTree->balance == RH){
// 				leftTree->balance = LH;
// 				node->balance = EH;
// 			}
// 			else if(rightTree->balance == EH){
// 				node->balance = EH;
// 				leftTree->balance = EH;
// 			}
// 			else{
// 				node->balance = RH;
// 				leftTree->balance = EH;
// 			}
// 			rightTree->balance = EH;
// 			node->left = rotateLeft(leftTree);
// 			node = rotateRight(node);
// 		}
// 		else{
// 			if(leftTree->balance == LH){
// 				node->balance = EH;
// 				leftTree->balance = EH;
// 			}
// 			else{
// 				node->balance = LH;
// 				leftTree->balance = RH;
// 				shorter = false;
// 			}
// 			node = rotateRight(node);
// 		}
// 	}

// 	return node;
// }

// Node* AVL::deleteRightBalance(Node* &node, bool &shorter){
// 	if(node->balance == LH){
// 		node->balance = EH;
// 	}
// 	else if(node->balance == EH){
// 		node->balance = RH;
// 		shorter = false;
// 	}
// 	else{
// 		Node* rightTree = node->right;
// 		if(rightTree->balance == LH){
// 			Node* leftTree = rightTree->left;
			
// 			if(leftTree->balance == LH){
// 				node->balance = EH;
// 				rightTree->balance = RH;
// 			}
// 			else if(leftTree->balance == EH){
// 				node->balance = EH;
// 				rightTree->balance = EH;
// 			}
// 			else{
// 				node->balance = LH;
// 				rightTree->balance = EH;
// 			}
// 			leftTree->balance = EH;
// 			node->right = rotateRight(rightTree);
// 			node = rotateLeft(node);
// 		}
// 		else{
// 			if(rightTree->balance == RH){
// 				node->balance = EH;
// 				rightTree->balance = EH;
// 			}
// 			else{
// 				node->balance = RH;
// 				rightTree->balance = LH;
// 				shorter = false;
// 			}
// 			node = rotateLeft(node);
// 		}
// 	}
// 	return node;
// }

// Node* AVL::AVLDelete(Node *&node, int deleteKey, bool &shorter, bool &success){
// 	if(node == nullptr){
// 		shorter = false;
// 		success = false;
// 		return nullptr;
// 	}

// 	if(deleteKey < node->data){
// 		node->left = AVLDelete(node->left, deleteKey, shorter, success);

// 		if(shorter){
// 			// deleteRightBalance
// 			node = deleteRightBalance(node, shorter);
// 		}
// 	}
// 	else if(deleteKey > node->data){
// 		node->right = AVLDelete(node->right, deleteKey, shorter, success);

// 		if(shorter){
// 			// deleteLeftBalance
// 			node = deleteLeftBalance(node, shorter);
// 		}
// 	}
// 	else{
// 		Node* deleteNode = node;
// 		if(deleteNode->right == nullptr){
// 			Node* newRoot = node->left;
// 			success = true;
// 			shorter = true;
// 			delete deleteNode;
// 			return newRoot;
// 		}
// 		else if(deleteNode->left == nullptr){
// 			Node* newRoot = node->right;
// 			success = true;
// 			shorter = true;
// 			delete deleteNode;
// 			return newRoot;
// 		}
// 		else{
// 			Node* exchangePtr = node->left;
// 			while(exchangePtr->right != nullptr){
// 				exchangePtr = exchangePtr->right;
// 			}
// 			node->data = exchangePtr->data;
// 			node->left = AVLDelete(node->left, exchangePtr->data, shorter, success);

// 			if(shorter){
// 				// deleteRightBalance
// 				node = deleteRightBalance(node, shorter);
// 			}
// 		}
// 	}

// 	return node;

// }

// void AVL::remove(const int &value){
// 	bool shorter = false, success = false;
// 	if(this->root == nullptr) return;
// 	else{
// 		this->root = AVLDelete(this->root, value, shorter, success);
// 	}
// }

class Stack{
    private:
        Node* top;
        int number_of_elements;
    public:
        Stack(Node* node) : top(node), number_of_elements(1){}
        Stack() : top(nullptr), number_of_elements(0) {}
        void push(std::string data, int dataType, std::string key);
		void push(std::string data, int dataType);
        void pop();
        Node* getTop();
        std::string getTopStr();
        bool isEmpty();
        bool isFull();
        void displayAllStack();
        int getSize();
};

/*
StackFrame declaration
*/
class StackFrame {
    int opStackMaxSize; // max size of operand stack
    int localVarSpaceSize; // size of local variable array
    Stack operandStack;
    AVL localVariableAVLTree = AVL();

public:
    /*
    Constructor of StackFrame
    */
    StackFrame();
    
    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);
    // void checkError();
    // void readInstruction(std::string filename);
    void execute_instructions(std::string instruction, int line);

    // bool checkDataTypeForIntOperand(std::string operand1, std::string operand2);
    bool isIntNumber(std::string str);
};

#endif // !__STACK_FRAME_H__