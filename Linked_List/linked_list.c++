#include <iostream>
#include <fstream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    void push(Node **head_ref, int new_data)
    {

        Node *new_node = new Node();

        new_node->data = new_data;
        new_node->next = (*head_ref);

        (*head_ref) = new_node;
    }

    void append(Node **head_ref, int new_data)
    {

        Node *new_node = new Node();
        Node *searching_node = new Node();

        new_node->data = new_data;
        new_node->next = NULL;

        // If the node is empty
        if (*head_ref == NULL)
        {
            *head_ref = new_node;
            return;
        }

        searching_node = *head_ref;

        while (searching_node->next != NULL)
        {
            searching_node = searching_node->next;
        }

        searching_node->next = new_node;
    }

    void insert_node_using_index(Node **head_ref, int new_data, int index)
    {

        Node *new_node = new Node();

        new_node->data = new_data;
        new_node->next = (*head_ref);

        // If the node is empty
        if (*head_ref == NULL && index == 0)
        {
            *head_ref = new_node;
            return;
        }
        else if (*head_ref == NULL && index != 0)
        {
            cout << "Invalid index \n";
            return;
        }

        Node *searching_node = *head_ref;

        for (int i = 0; i < index - 1; i++)
        {
            if (searching_node->next != NULL)
            {
                searching_node = searching_node->next;
            }
            else
            {
                cout << "Invalid index \n";
                return;
            }
        }

        new_node->next = searching_node->next;
        searching_node->next = new_node;
    }

    void delete_node_using_index(Node **head_ref, int index)
    {

        // If the node is empty
        if (*head_ref == NULL)
        {
            cout << "Invalid index \n";
            return;
        }

        if (index == 0)
        {
            *head_ref = (*head_ref)->next;
            return;
        }

        Node *prev_node = *head_ref;

        for (int i = 0; i < index - 1; i++)
        {
            if (prev_node->next != NULL)
            {
                prev_node = prev_node->next;
            }
            else
            {
                cout << "Invalid index \n";
                return;
            }
        }

        Node *next_node = prev_node->next;
        prev_node->next = next_node->next;
    }

    int getLength(Node *head_ref)
    {

        Node *copy_list = head_ref;
        int how_long = 0;
        while (copy_list != NULL)
        {
            how_long++;
            copy_list = copy_list->next;
        }

        return how_long;
    }

    void reverse_print(Node **head_ref)
    {

        Node *reversed_list = NULL;

        Node *looping_node = *head_ref;

        while (looping_node != NULL)
        {

            Node().push(&reversed_list, looping_node->data);
            looping_node = looping_node->next;
        }

        Node().printList(reversed_list);
    }

    Node* remove_duplicate(Node *head_ref)
    {

        Node *current = head_ref;

        Node *next_next;

        if (current == NULL) return head_ref;

        while (current->next != NULL)
        {
            if (current->data == current->next->data)
            {
                next_next = current->next->next;
                free(current->next);
                current->next = next_next;
            }
            else 
            {
                current = current->next;
            }
        }

        return head_ref;

    }

    void printList(Node *node)
    {

        while (node != NULL)
        {
            cout << node->data << " ";
            node = node->next;
        }

        cout << "\n";
    }
};

int main(int argc, char const *argv[])
{

    Node *head = NULL;

    Node().push(&head, 5);
    Node().push(&head, 5);
    Node().push(&head, 1);
    Node().push(&head, 3);

    Node* node = Node().remove_duplicate(head);
    // Node().append(&head, 9);

    // Node().insert_node_using_index(&head, 100, 3);
    // Node().delete_node_using_index(&head, 3);

    Node().printList(node);
    // cout << Node().getLength(head) << "\n";

    // Node().reverse_print(&head);

    return 0;
}
