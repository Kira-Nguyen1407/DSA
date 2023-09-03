#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

fstream fin;

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarSpaceSize(LOCAL_VARIABLE_SPACE_SIZE) {}

void StackFrame::run(string filename) {
    string instruction;
    int line = 1;

    fin.open(filename, ios::in);
    if(!fin.good()){
        cout << "error opening file. Make sure that the file exists in the current directory." << endl;
    }

    if(fin.is_open()){
        while(!fin.eof()){
            getline(fin, instruction);
            // cout << instruction << endl;
            execute_instructions(instruction, line);
            line++;
        }
        fin.close();
    }
}

void StackFrame::execute_instructions(string instruction, int line){
    string opcode, strValue, operand1 = "", operand2 = "";
    size_t spaceFound = instruction.find(" ");

    if(spaceFound != string::npos){
        opcode = instruction.substr(0, spaceFound);
        strValue = instruction.substr(spaceFound+1, instruction.length() - spaceFound-1);
    }
    else{
        opcode = instruction;
    }
    if(opcode == "i2f"){

        if(!operandStack.isEmpty()){
            operand1 = operandStack.getTopStr();
            operandStack.pop();
        }
        else{
            throw StackEmpty(line);
        }
        
        if(!isIntNumber(operand1)){ throw TypeMisMatch(line);}

        operandStack.push(to_string((float)stoi(operand1)), 1);
    }
    if(opcode == "f2i"){

        if(!operandStack.isEmpty()){
            operand1 = operandStack.getTopStr();
            operandStack.pop();
        }
        else{
            throw StackEmpty(line);
        }
        
        if(isIntNumber(operand1)){ throw TypeMisMatch(line);}

        operandStack.push(to_string((int)stof(operand1)), 0);
    }

    if(opcode == "ibnot"){

        if(!operandStack.isEmpty()){
            operand1 = operandStack.getTopStr();
            operandStack.pop();
        }
        else{
            throw StackEmpty(line);
        }
        
        if(!isIntNumber(operand1)){ throw TypeMisMatch(line);}

        stoi(operand1) == 0 ? operandStack.push(to_string(1), 0) : operandStack.push(to_string(0), 0);
    }
    if(opcode == "igt"){
        int numberOfOperands = 0;
        bool isFirst = true;
        
        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                stoi(operand1) > stoi(operand2) ? operandStack.push(to_string(1), 0) : operandStack.push(to_string(0), 0);
            }
        }
    }
    if(opcode == "fgt"){
        int numberOfOperands = 0;
        bool isFirst = true;
        
        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            stof(operand1) > stof(operand2) ? operandStack.push(to_string(1), 0) : operandStack.push(to_string(0), 0);
        }
    }
    if(opcode == "ilt"){
        int numberOfOperands = 0;
        bool isFirst = true;
        
        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                stoi(operand1) < stoi(operand2) ? operandStack.push(to_string(1), 0) : operandStack.push(to_string(0), 0);
            }
        }
    }
    if(opcode == "flt"){
        int numberOfOperands = 0;
        bool isFirst = true;

        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            stof(operand1) < stof(operand2) ? operandStack.push(to_string(1), 0) : operandStack.push(to_string(0), 0);
        }
    }
    if(opcode == "ieq"){
        int numberOfOperands = 0;
        bool isFirst = true;

        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                stoi(operand1) == stoi(operand2) ? operandStack.push(to_string(1), 0) : operandStack.push(to_string(0), 0);
            }
        }
    }
    if(opcode == "feq"){
        int numberOfOperands = 0;
        bool isFirst = true;

        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            float checkZero;
            checkZero = stof(operand1) - stof(operand2);
            checkZero < 0 ? checkZero = checkZero* -1 : checkZero;
            checkZero < 0.0001 ? operandStack.push(to_string(1), 0) : operandStack.push(to_string(0), 0);
        }
    }
    if(opcode == "ineq"){
        int numberOfOperands = 0;
        bool isFirst = true;

        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                stoi(operand1) == stoi(operand2) ? operandStack.push(to_string(0), 0) : operandStack.push(to_string(1), 0);
            }
        }
    }
    if(opcode == "fneq"){
        int numberOfOperands = 0;
        bool isFirst = true;

        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            float checkZero;
            checkZero = stof(operand1) - stof(operand2);
            checkZero < 0 ? checkZero = checkZero* -1 : checkZero;
            checkZero < 0.0001 ? operandStack.push(to_string(0), 0) : operandStack.push(to_string(1), 0);
        }
    }
    if(opcode == "iand"){
        int numberOfOperands = 0;
        bool isFirst = true;

        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                operandStack.push(to_string(stoi(operand1) & stoi(operand2)), 0);
            }
        }
    }
    if(opcode == "ior"){
        int numberOfOperands = 0;
        bool isFirst = true;

        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                operandStack.push(to_string(stoi(operand1) | stoi(operand2)), 0);
            }
        }
    }
    if(opcode == "ineg"){

        if(!operandStack.isEmpty()){
            operand1 = operandStack.getTopStr();
            operandStack.pop();
        }
        else{
            throw StackEmpty(line);
        }
        
        if(!isIntNumber(operand1)){ throw TypeMisMatch(line);}

        operand1 == "0" ? operandStack.push("-0", 0) : operandStack.push(to_string(stoi(operand1)*-1), 0);
    }
    if(opcode == "fneg"){

        if(!operandStack.isEmpty()){
            operand1 = operandStack.getTopStr();
            operandStack.pop();
        }
        else{
            throw StackEmpty(line);
        }

        // operand1 == "0.0" ? operandStack.push("-0.0", 1) : operandStack.push(to_string(stof(operand1)*-1), 1);
        operandStack.push(to_string(stof(operand1)*-1), 1);
    }
    if(opcode == "irem"){
        int numberOfOperands = 0;
        bool isFirst = true;

        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                if(stoi(operand2) == 0) throw DivideByZero(line);
                int a = stoi(operand1), b = stoi(operand2);
                operandStack.push(to_string(a - (a/b)*b), 0);
            }
        }
    }
    if(opcode == "idiv"){
        int numberOfOperands = 0;
        bool isFirst = true;
        
        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                if(stoi(operand2) == 0) throw DivideByZero(line);
                operandStack.push(to_string(stoi(operand1)/stoi(operand2)), 0);
            }
        }
    }
    if(opcode == "fdiv"){
        int numberOfOperands = 0;
        bool isFirst = true;
        
        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            float checkZero;
            stof(operand2) < 0 ? checkZero = 0 - stof(operand2) : checkZero = stof(operand2) - 0;
            if(checkZero < 0.0001) throw DivideByZero(line);
            operandStack.push(to_string(stof(operand1)/stof(operand2)), 1);
        }
    }
    if(opcode == "imul"){
        int numberOfOperands = 0;
        bool isFirst = true;

        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }

        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                operandStack.push(to_string(stoi(operand1)*stoi(operand2)), 0);
            }
        }
    }
    if(opcode == "fmul"){
        int numberOfOperands = 0;
        bool isFirst = true;

        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            operandStack.push(to_string(stof(operand1)*stof(operand2)), 1);
        }
    }
    if(opcode == "iadd"){
        int numberOfOperands = 0;
        bool isFirst = true;
        
        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                operandStack.push(to_string(stoi(operand1)+stoi(operand2)), 0);
            }
        }
    }
    if(opcode == "fadd"){
        int numberOfOperands = 0;
        bool isFirst = true;
        
        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }

        // cout << "operand1: " << stof(operand1) << endl;
        // cout << "operand2: " << stof(operand2) << endl;
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{

            operandStack.push(to_string(stof(operand1)+stof(operand2)), 1);
        }
    }
    
    if(opcode == "isub"){
        int numberOfOperands = 0;
        bool isFirst = true;
        
        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }

        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            if(!isIntNumber(operand2) || !isIntNumber(operand1)){
                throw TypeMisMatch(line);
            }
            else{
                operandStack.push(to_string(stoi(operand1)-stoi(operand2)), 0);
            }
        }
    }

    if(opcode == "fsub"){
        int numberOfOperands = 0;
        bool isFirst = true;
        
        while(!operandStack.isEmpty()){
            if(numberOfOperands == 2) break;
            isFirst ? operand2 = operandStack.getTopStr() : operand1 = operandStack.getTopStr();
            operandStack.pop();
            isFirst = false;
            numberOfOperands++;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            operandStack.push(to_string(stof(operand1)-stof(operand2)), 1);
        }
    }
    

    if(opcode == "iconst"){
        if(!isIntNumber(strValue)) throw TypeMisMatch(line);

        if(operandStack.isFull()) throw StackFull(line);

        operandStack.push(strValue, 0);
        //operandStack.display();
    }

    // if(opcode == "i2f"){
    //     if(!operandStack.isEmpty()){
    //         operand1 = operandStack.getTop();
    //         operandStack.pop();
    //     }
    //     else{
    //         throw StackEmpty(line);
    //     }
        
    //     if(!isIntNumber(operand1)){ throw TypeMisMatch(line);}

    //     // operand1 == "0" ? operandStack.push("-0", 0) : operandStack.push(to_string(stoi(operand1)*-1), 0);

    //     operandStack.push(to_string((float)stoi(operand1)), 1);
    // }

    if(opcode == "iload"){

        string key = strValue;

        Node* AVLsearchResult = localVariableAVLTree.AVLsearch(localVariableAVLTree.getRoot(), key);

        if(AVLsearchResult == nullptr) throw UndefinedVariable(line);

        if(!isIntNumber(AVLsearchResult->data)) throw TypeMisMatch(line);

        if(operandStack.isFull()) throw StackFull(line);

        operandStack.push(AVLsearchResult->data, 0);
    }

    if(opcode == "fload"){

        string key = strValue;

        Node* AVLsearchResult = localVariableAVLTree.AVLsearch(localVariableAVLTree.getRoot(), key);

        if(AVLsearchResult == nullptr) throw UndefinedVariable(line);

       if(isIntNumber(AVLsearchResult->data)) throw TypeMisMatch(line);

        if(operandStack.isFull()) throw StackFull(line);

        operandStack.push(AVLsearchResult->data, 1);
    }

    if(opcode == "istore"){

        string key = strValue;

        if(operandStack.isEmpty()) throw StackEmpty(line);

        operand1 = operandStack.getTopStr();
        operandStack.pop();

        if(!isIntNumber(operand1)) throw TypeMisMatch(line);

        if(localVariableAVLTree.AVLTreeIsFull()) throw LocalSpaceFull(line);

        localVariableAVLTree.insert(operand1, 0, key);
    }

    if(opcode == "fstore"){

        string key = strValue;

        if(operandStack.isEmpty()) throw StackEmpty(line);

        operand1 = operandStack.getTopStr();
        operandStack.pop();

        if(isIntNumber(operand1)) throw TypeMisMatch(line);

        if(localVariableAVLTree.AVLTreeIsFull()) throw LocalSpaceFull(line);

        localVariableAVLTree.insert(operand1, 1, key);
    }

    if(opcode == "par"){
        string key = strValue;

        if(key == localVariableAVLTree.getRoot()->key){
            cout << "null" << "\n";
        }
        else{
            Node* parent = localVariableAVLTree.findParent(localVariableAVLTree.getRoot(), key);

            if(parent == nullptr){
                throw UndefinedVariable(line);
            }
            else{
                cout << parent->key << "\n";
            }
        }   
    }

    if(opcode == "val"){
        string key = strValue;

        Node* AVLsearchResult = localVariableAVLTree.AVLsearch(localVariableAVLTree.getRoot(), key);

        if(AVLsearchResult == nullptr) throw UndefinedVariable(line);

        if(AVLsearchResult->dataType == 0){
            cout << stoi(AVLsearchResult->data) << "\n";
        }
        else{
            if(AVLsearchResult->dataType == 1){
                cout << stof(AVLsearchResult->data) << "\n";
            }
        }
    }

    if(opcode == "fconst"){
        if(operandStack.isFull()) throw StackFull(line);

        operandStack.push(strValue, 1);
    }

    if(opcode == "top"){
        if(operandStack.isEmpty()) throw StackEmpty(line);

        Node* top = operandStack.getTop();
        if(top->dataType == 0){
            cout << stoi(top->data) << "\n";
        }
        else{
            if(top->dataType == 1){
                cout << stof(top->data) << "\n";
            }
        }
    }

    if(opcode == "printAVL"){
        localVariableAVLTree.prefixTraversal(localVariableAVLTree.getRoot());
    }
    if(opcode == "displayAllStack"){
        operandStack.displayAllStack();
    }
}

bool StackFrame::isIntNumber(string str){
    size_t i;
    str[0] == '-' ? i = 1 : i = 0;
    for (; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
 
    return true;
}

// bool StackFrame::checkDataTypeForIntOperand(string operand1, string operand2){
//     StackFrame::isIntNumber(operand1);
//     StackFrame::isIntNumber(operand2);
//     return true;
// }

int Stack::getSize(){return this->number_of_elements;}

bool Stack::isEmpty(){return this->number_of_elements == 0;}

void Stack::push(string data, int dataType){
    Node* newTop = new Node(data, dataType);
    newTop->next = this->top;
    this->top = newTop;
    number_of_elements++;
}

void Stack::push(std::string data, int dataType, std::string key){
    Node* newTop = new Node(data, dataType, key);
    newTop->next = this->top;
    this->top = newTop;
    number_of_elements++;
}

bool Stack::isFull(){
    return number_of_elements == OPERAND_STACK_MAX_SIZE/2;
}

void Stack::pop(){
    if(!isEmpty()){
        Node* temp = this->top;
        this->top = this->top->next;
        delete temp;
        number_of_elements--;
    }
}

Node* Stack::getTop(){return this->top;}

string Stack::getTopStr(){return this->top->data;}

void Stack::displayAllStack(){

    Node* temp;
    if (top == nullptr){
        cout << "\nStack Underflow";
        exit(1);
    }
    else{
        temp = top;
        while (temp != nullptr)
        {
            cout << temp->data;
            temp = temp->next;
            temp == nullptr ? cout << endl : cout << "->";
        }
    }
}

void AVL::prefixTraversal(Node* node){
	if(node){
        cout << "data: " << node->data << ", " << "data type: " << node->dataType << ", node balance: " << node->balance << ", key: " << node->key << endl;
        prefixTraversal(node->left);
        prefixTraversal(node->right);
    }
}

Node* AVL::findParent(Node* node, string key){

    Node* parent = nullptr;
    while(node && (node->key != key)){
        parent = node;
        if(key.compare(node->key) < 0) node = node->left;
        else if(key.compare(node->key) > 0) node = node->right;
    }

    if(node == nullptr) parent = nullptr;

    return parent;
}

Node* AVL::AVLsearch(Node* node, string key){
    if(node == nullptr) return nullptr;

    if(key.compare(node->key) < 0) return AVLsearch(node->left, key);
    if(key.compare(node->key) > 0) return AVLsearch(node->right, key);

    return node;
}

bool AVL::AVLTreeIsFull(){return this->number_of_nodes >= LOCAL_VARIABLE_SPACE_SIZE/2;}

Node* AVL::rotateRight(Node *&node){
	Node* tempPtr = node->left;
	node->left = tempPtr->right;
	tempPtr->right = node;
	return tempPtr;
}

Node* AVL::rotateLeft(Node *&node){
	Node* tempPtr = node->right;
	node->right = tempPtr->left;
	tempPtr->left = node;
	return tempPtr;
}

void AVL::insert(std::string data, int dataType, std::string key){
	Node* newNode = new Node(data, dataType, key);
	bool taller = false;

	if(this->root == nullptr){this->root = newNode;}
	else{
		this->root = AVLInsert(this->root, newNode, taller);
	}
    this->number_of_nodes++;
}

Node* AVL::rightBalance(Node* &node, bool& taller){
	Node* rightTree = node->right;

	if(rightTree->balance == RH){
		node->balance = EH;
		rightTree->balance = EH;
		node = rotateLeft(node);
		taller = false;
	}
	else{
		Node* leftTree = rightTree->left;
		if(leftTree->balance == RH){
			node->balance = LH;
			rightTree->balance = EH;
		}
		else if(leftTree->balance == EH){
			rightTree->balance = EH;
			node->balance = EH;
		}
		else{
			node->balance = EH;
			rightTree->balance = RH;
		}

		leftTree->balance = EH;
		node->right = rotateRight(rightTree);
		node = rotateLeft(node);
		taller = false;
	}

	return node;
}

Node* AVL::leftBalance(Node* &node, bool &taller){
	Node* leftTree = node->left;

	if(leftTree->balance == LH){
		node->balance = EH;
		leftTree->balance = EH;
		node = rotateRight(node);
		taller = false;
	}
	else{
		Node* rightTree = leftTree->right;
		if(rightTree->balance == LH){
			node->balance = RH;
			leftTree->balance = EH;
		}
		else if(rightTree->balance == EH){
			leftTree->balance = EH;
			node->balance = EH;
		}
		else{
			leftTree->balance = LH;
			node->balance = EH;
		}
		rightTree->balance = EH;

		node->left = rotateLeft(leftTree);
		node = rotateRight(node);
		taller = false;
	}
	return node;
}

Node* AVL::AVLInsert(Node* &node, Node* newNode, bool &taller){
	if(node == nullptr){
		node = newNode;
		taller = true;
		return node;
	}
	// if key of newNode is smaller than key of node
	if(newNode->key.compare(node->key) < 0){
		node->left = AVLInsert(node->left, newNode, taller);
		if(taller){
			if(node->balance == LH){ 
				node = leftBalance(node, taller);
			}
			else if(node->balance == EH){
				node->balance = LH;
			}
			else{
				node->balance = EH;
				taller = false;
			}
		}
	}
	else{
		node->right = AVLInsert(node->right, newNode, taller);
		if(taller){
			if(node->balance == LH){
				node->balance = EH;
				taller = false;
			}
			else if(node->balance == EH){
				node->balance = RH;
			}
			else{
				node = rightBalance(node, taller);
			}
		}
	}

	return node;
}