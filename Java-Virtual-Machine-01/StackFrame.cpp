#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

fstream fin;

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarArrSize(LOCAL_VARIABLE_ARRAY_SIZE) {}

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
            operand1 = operandStack.getTop();
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
            operand1 = operandStack.getTop();
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
            operand1 = operandStack.getTop();
            operandStack.pop();
        }
        else{
            throw StackEmpty(line);
        }
        
        if(!isIntNumber(operand1)){ throw TypeMisMatch(line);}

        stoi(operand1) == 0 ? operandStack.push(to_string(1), 0) : operandStack.push(to_string(0), 0);
    }
    if(opcode == "igt"){
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            stof(operand1) > stof(operand2) ? operandStack.push(to_string(1), 0) : operandStack.push(to_string(0), 0);
        }
    }
    if(opcode == "ilt"){
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            stof(operand1) < stof(operand2) ? operandStack.push(to_string(1), 0) : operandStack.push(to_string(0), 0);
        }
    }
    if(opcode == "ieq"){
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
            operand1 = operandStack.getTop();
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
            operand1 = operandStack.getTop();
            operandStack.pop();
        }
        else{
            throw StackEmpty(line);
        }

        // operand1 == "0.0" ? operandStack.push("-0.0", 1) : operandStack.push(to_string(stof(operand1)*-1), 1);
        operandStack.push(to_string(stof(operand1)*-1), 1);
    }
    if(opcode == "irem"){
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
        }

        // cout << "operand1: " << operand1 << endl;
        // cout << "operand2: " << operand2 << endl;
        
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            operandStack.push(to_string(stof(operand1)*stof(operand2)), 1);
        }
    }
    if(opcode == "iadd"){
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
        }
        
        if(operand1 == "" || operand2 == ""){
            throw StackEmpty(line);
        }
        else{
            operandStack.push(to_string(stof(operand1)+stof(operand2)), 1);
        }
    }
    
    if(opcode == "isub"){
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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
        bool isFirst = true;
        while(!operandStack.isEmpty()){
            isFirst ? operand2 = operandStack.getTop() : operand1 = operandStack.getTop();
            operandStack.pop();
            isFirst = false;
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

    if(opcode == "i2f"){
        if(!operandStack.isEmpty()){
            operand1 = operandStack.getTop();
            operandStack.pop();
        }
        else{
            throw StackEmpty(line);
        }
        
        if(!isIntNumber(operand1)){ throw TypeMisMatch(line);}

        // operand1 == "0" ? operandStack.push("-0", 0) : operandStack.push(to_string(stoi(operand1)*-1), 0);

        operandStack.push(to_string((float)stoi(operand1)), 1);
    }

    if(opcode == "iload"){

        int ind = stoi(strValue);

        if(ind >= LOCAL_VARIABLE_ARRAY_SIZE) throw ArrayOutOfRange(line);

        if(localVariableArray[ind].dataType == -1) throw UndefinedVariable(line);

        if(!isIntNumber(localVariableArray[ind].data)) throw TypeMisMatch(line);

        if(operandStack.isFull()) throw StackFull(line);

        operandStack.push(localVariableArray[ind].data, 0);
    }

    if(opcode == "fload"){

        int ind = stoi(strValue);

        if(ind >= LOCAL_VARIABLE_ARRAY_SIZE) throw ArrayOutOfRange(line);

        if(localVariableArray[ind].dataType == -1) throw UndefinedVariable(line);

        if(isIntNumber(localVariableArray[ind].data)) throw TypeMisMatch(line);

        if(operandStack.isFull()) throw StackFull(line);

        operandStack.push(localVariableArray[ind].data, 1);
    }

    if(opcode == "istore"){

        int ind = stoi(strValue);

        if(operandStack.isEmpty()) throw StackEmpty(line);

        operand1 = operandStack.getTop();
        operandStack.pop();

        if(!isIntNumber(operand1)) throw TypeMisMatch(line);

        if(ind >= LOCAL_VARIABLE_ARRAY_SIZE) throw ArrayOutOfRange(line);

        localVariableArray[ind] = Node(operand1, 0);
    }

    if(opcode == "fstore"){

        int ind = stoi(strValue);

        if(operandStack.isEmpty()) throw StackEmpty(line);

        operand1 = operandStack.getTop();
        operandStack.pop();

        if(isIntNumber(operand1)) throw TypeMisMatch(line);

        if(ind >= LOCAL_VARIABLE_ARRAY_SIZE) throw ArrayOutOfRange(line);

        localVariableArray[ind] = Node(operand1, 1);
    }

    if(opcode == "val"){
        int ind = stoi(strValue);

        if(ind >= LOCAL_VARIABLE_ARRAY_SIZE) throw ArrayOutOfRange(line);

        if(localVariableArray[ind].dataType == -1) throw UndefinedVariable(line);

        cout << localVariableArray[ind].data << "\n";
    }

    if(opcode == "fconst"){
        if(operandStack.isFull()) throw StackFull(line);

        operandStack.push(strValue, 1);
    }

    if(opcode == "top"){
        if(operandStack.isEmpty()) throw StackEmpty(line);

        cout << operandStack.getTop() << "\n";
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

bool StackFrame::checkDataTypeForIntOperand(string operand1, string operand2){
    StackFrame::isIntNumber(operand1);
    StackFrame::isIntNumber(operand2);
    return true;
}

int Stack::getSize(){return this->number_of_elements;}

bool Stack::isEmpty(){return this->number_of_elements == 0;}

void Stack::push(string value, int dataType){
    Node* newTop = new Node(value, dataType);
    // display();
    newTop->next = this->top;
    // display();
    this->top = newTop;
    // display();
    number_of_elements++;
    // display();
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

string Stack::getTop(){return this->top->data;}

void Stack::display(){

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