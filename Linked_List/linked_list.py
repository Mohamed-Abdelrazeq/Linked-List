import re


class Node:
    
    def __init__(self,data):
        
        self.data = data
        self.next = None  


class MyLinkedList:

    def __init__(self):
        
        self.head = None
        self.length = 0
    
    # Get Data     
    def get(self, index):
        
        temp = self.head
        
        if self.length <= index:
            print("Invalid Index")
            return -1

        while index != 0:
            
            index -= 1
            temp = temp.next
            
        return temp.data
            
    def printList(self):
        temp = self.head
        for i in range(self.length):
            print (temp.data)
            temp = temp.next
        print("================================")
        

    # Add Data
    def addAtHead(self, val):
        
        # Configure The New Node
        new_node = Node(val)
        new_node.next = self.head

        # Update My Linked List
        self.head = new_node
        self.length += 1
        
    def addAtTail(self, val):
        
        # Create New Node
        new_node = Node(val)
        
        # Check Empty Linked List
        if self.head == None:
            self.head = new_node
            self.length += 1
            return

        # Search For the End Of Linked List
        temp = self.head
        while temp.next != None :
            temp = temp.next
        
        temp.next = new_node
        self.length += 1
        return

    def addAtIndex(self, index, val):
        
        # Search Variables
        index_ref = index
        temp = self.head

        # Create New Node
        new_node = Node(val)
        
        # Check Invalid Index
        if self.length < index:
            print("Invalid Index")
            return 
        
        #   Check Add to Head
        if index == 0:
            self.addAtHead(val)
            return
        
        # Check Add to Tail
        if self.length == index:
            self.addAtTail(val)
            return

        # Search for the Index
        while index != 1:
            index -= 1
            temp = temp.next

        # HERE ERROR
        new_node.next = temp.next
        temp.next = new_node
        self.length += 1


    # Delete Data
    def deleteAtIndex(self, index):
        temp = self.head

        self.printList()

        # Invalid Index
        if self.length <= index:
            print("Invalid Index")
            return 
        
        if index == 0:
            self.head = self.head.next

            if self.length == 1:    
                self.tail = None

            self.length -= 1            
            return 
        
        while index != 1:
            index -= 1
            temp = temp.next


        next = temp.next
        temp.next = next.next
        self.length -= 1


if __name__=='__main__':

    my_list = MyLinkedList()

    
    my_list.addAtTail(0)
    my_list.addAtTail(5)

    my_list.printList()
   

    








