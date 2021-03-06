// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a simple encaptulated LinkList, utilizing
// a friend class. A friend class is one in which all of that class's
// member functions are friend functions of the class who grants them
// friendship.  Friend functions of LinkListElement are those which 
// have access to LinkListElement members as if they were within the 
// scope of the LinkListElement class (as well as within their own 
// class scope). Friend functions are sometimes necessary for tightly
// coupled (non-related) classes, when it is otherwise inappropriate to
// universally provide selected functions in the public access region.
// Friend functions are also beneficial when used in conjunction with
// operator overloading.

#include <iostream>
using namespace std;

typedef int Item;  

class LinkList;  // forward declaration

class LinkListElement
{
private:
   void *data;
   LinkListElement *next;

   // These member functions should not be part of the public interface
   // It is only appropriate for them to be used within the scope of LinkList,
   // who is a friend class of LinkListElement.
   void *GetData() { return data; }
   LinkListElement *GetNext() { return next; }
   void SetNext(LinkListElement *e) { next = e; }

public:
   // All member functions of LinkList are friend functions of LinkListElement 
   friend class LinkList;   
   LinkListElement() { data = 0; next = 0; }
   LinkListElement(Item *i) { data = i; next = 0; }
   virtual ~LinkListElement() { delete (Item *) data; next = 0; }
};

class LinkList
{
private:
   LinkListElement *head, *tail, *current;
public:
   LinkList() { head = tail = current = 0; }
   LinkList(LinkListElement *e) { head = tail = current = e; }
   void InsertAtFront(Item *);
   LinkListElement *RemoveAtFront();
   void DeleteAtFront() { delete RemoveAtFront(); }  // destructor will delete data, set next to NULL
   virtual int IsEmpty() { return head == 0; } 
   virtual void Print();  
   virtual ~LinkList() { while (!IsEmpty()) DeleteAtFront(); }
};


void LinkList::InsertAtFront(Item *theItem)
{
   LinkListElement *temp = new LinkListElement(theItem);

   temp->SetNext(head);  // temp->next = head;
   head = temp;
}

LinkListElement *LinkList::RemoveAtFront()
{
   LinkListElement *remove = head;
   head = head->GetNext();  // head = head->next;
   current = head;    // reset current for usage elsewhere
   return remove;
}
 
void LinkList::Print()
{
   Item output;

   if (!head)
      cout << "<EMPTY>" << endl;
   current = head;
   while (current)
   {
      output = *((Item *) current->GetData());
      cout << output << " ";
      current = current->GetNext();
   }
   cout << endl;
}


int main()
{
   // Create a few items, which will later be data for LinkListElements
   Item *item1 = new Item;
   *item1 = 100;
   Item *item2 = new Item(200);

   // create an element for the Linked List
   LinkListElement *element1 = new LinkListElement(item1);

   // create a linked list and initialize with one node (element)
   LinkList list1(element1);
   
   // Add some new items to the list
   list1.InsertAtFront(item2);   
   list1.InsertAtFront(new Item(50));   // add a nameless item to the list

   cout << "List 1: ";
   list1.Print();                // print out contents of list

   // delete elements from list, one by one
   while (!(list1.IsEmpty()))
   {
      list1.DeleteAtFront();
      cout << "List 1 after removing an item: ";
      list1.Print();
   }

   // create a second linked list, add some items and print
   LinkList list2;
   list2.InsertAtFront(new Item (3000));
   list2.InsertAtFront(new Item (600));
   list2.InsertAtFront(new Item (475));

   cout << "List 2: ";
   list2.Print();

   // delete elements from list, one by one
   while (!(list2.IsEmpty()))
   {
      list2.DeleteAtFront();
      cout << "List 2 after removing an item: ";
      list2.Print();
   }

   return 0;
}

