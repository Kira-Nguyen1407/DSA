using LinkedListNamespace;
using System.Diagnostics;

public class Program{
    public static void Main(string[] args){
        LinkedList list = new LinkedList();

        int[] values = {10, 15, 2,  6,  4,  7,  40,  8};
        int[] index = {0,  0,  1,  3,  2,  3,  5,   0};
        int[] expValues = {8,  15, 2,  4,  7, 10,  40,  6}; 

        for (int idx = 0; idx < 8; idx++){
            list.Add(index[idx], values[idx]);
        }

        Debug.Assert(list.Size() == expValues.Length, "Test failed");

        for (int idx = 0; idx < 8; idx++){
           Debug.Assert( list.GetValueAt(idx) == expValues[idx], "Test failed");
        }

        list.PrintList();
    }
}