namespace LinkedListNamespace{
    public class Node {
        public int Data { get; set; }
        public Node? Next { get; set; }
        
        public Node(int data) {
            Data = data;
            Next = null;
        }
    }

    public class LinkedList {
        private Node? head;
        private Node? tail;
        private int count;

        public LinkedList() {
            head = null;
            tail = null;
            count = 0;
        }
        public void clear(){
            while(Size() > 0){
                removeAt(0);
            }
        }
        public bool removeItem(int item){
            return removeAt(indexOf(item));
        }
        public bool removeAt(int index) {
            if(index >= count || index < 0){
                return false;
            }

            if(index == count-1){
                Node? walker = head;
                Node? nodeToBeRemoved = null;
                if(head != tail){
                    while(walker != null && walker.Next != tail){
                        walker = walker.Next;
                    }
                    nodeToBeRemoved = tail;
                    tail = walker;
                }
                else{
                    nodeToBeRemoved = head;
                    head = null;
                    tail = null;
                }

                if(nodeToBeRemoved != null){
                    if(walker != null){
                        walker.Next = null;
                    }
                }
            }
            else if(index == 0){
                Node? nodeToBeRemoved = head;
                if(head != null){
                    head = head.Next;
                }
                else{
                    head = null;
                    tail = null;
                }
                if(nodeToBeRemoved != null){
                    nodeToBeRemoved.Next = null;
                }
            }
            else{
                Node? walker = head;
                int i = 0;
                while(i < index-1){
                    if(walker != null){
                        walker = walker.Next;
                    }
                    i++;
                }
                if(walker != null){
                    Node? nodeToBeRemoved = walker.Next;
                    if(nodeToBeRemoved != null){
                        walker.Next = nodeToBeRemoved.Next;
                        nodeToBeRemoved.Next = null;
                    }
                }
            }
            count = count - 1;
            return true;
        }
        public bool Contains(int item){
            return indexOf(item) == -1;
        }
        public int indexOf(int item){
            int index = -1;

            Node? walker = head;
            int i = 0;
            while (walker != null){
                if(walker.Data == item){
                    index = i;
                    break;
                }
                walker = walker.Next;
                i++;
            }

            return index;
        }
        public int GetValueAt(int index) {
            int value = -9999;

            if(index >= 0 && index < count){
                Node? walker = head;
                int i = 0;
                while(i < index){
                    if(walker != null){
                        walker = walker.Next;
                    }
                    i++;
                }
                if(walker != null){
                    value = walker.Data;
                }
            }

            return value;
        }
        public int Size(){
            return count;
        }
        public bool isEmpty() {
            return count == 0;
        }
        public void Add(int data) {
            Node newNode = new Node(data);
            if(head == null){
                head = newNode;
                tail = newNode;
            }
            else{
                if(tail != null){
                    tail.Next = newNode;
                }
                tail = newNode;
            }
            count = count + 1;
        }

        public void Add(int index, int value) {
            if(index < 0 || index > count){
                return;
            }

            Node newNode = new Node(value);

            if(index == count){
                Add(value);
                return;
            }
            else if(index == 0){
                newNode.Next = head;
                head = newNode;
            }
            else{
                Node? walker = head;
                int i = 0;
                while(i < index-1){
                    if(walker != null){
                        walker =  walker.Next;
                        i++;
                    }
                }
                if(walker != null){
                    Node? indexNode = walker.Next;
                    walker.Next = newNode;
                    if(indexNode != null){
                        newNode.Next = indexNode;
                    }
                }
            }
            count = count + 1;
        }

        public void PrintList() {
            Node? current = head;
            while (current != null) {
                Console.Write(current.Data);
                current = current.Next;
                string endStr = current == null ? "\n" : " ";
                Console.Write(endStr);
            }
            Console.WriteLine();
        }
    }
}

