#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>

#define LOCAL_VARIABLE_SPACE_SIZE   256      

class Node{
    public:
        std::string data;
        int dataType;
        Node* next;
        Node(std::string data, int dataType) : data(data), dataType(dataType) {}
        Node() : data(""), dataType(-1) {}
};

class Stack{
    private:
        Node* top;
        int number_of_elements;
    public:
        Stack(Node* node) : top(node), number_of_elements(1){}
        Stack() : top(nullptr), number_of_elements(0) {}
        void push(std::string value, int dataType);
        void pop();
        std::string getTop();
        bool isEmpty();
        bool isFull();
        void display();
        int getSize();
};

/*
StackFrame declaration
*/
class StackFrame {
    int opStackMaxSize; // max size of operand stack
    int localVarArrSize; // size of local variable array
    Stack operandStack;
    Node localVariableArray[LOCAL_VARIABLE_SPACE_SIZE];
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
    void checkError();
    void readInstruction(std::string filename);
    void execute_instructions(std::string instruction, int line);

    bool checkDataTypeForIntOperand(std::string operand1, std::string operand2);
    bool isIntNumber(std::string str);
};

#endif // !__STACK_FRAME_H__