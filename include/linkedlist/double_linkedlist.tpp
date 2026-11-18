#include <iostream>

using namespace std;




template <typename T>
double_linkedlist<T>::double_linkedlist():head{nullptr}, tail{nullptr} {}




// Copy constructor
template <typename T>
double_linkedlist<T>::double_linkedlist(
    const double_linkedlist<T>& other)
{
    head = nullptr;
    tail = nullptr;

    l_node<T>* temp = other.head;

    while (temp != nullptr)
    {
        append(temp->d);
        temp = temp->next;
    }
}


// Copy assignment operator
template <typename T>
double_linkedlist<T>& double_linkedlist<T>::operator=(
    const double_linkedlist<T>& other)
{
   
    if (this == &other)
        return *this;

  
    delete_all_nodes();

    
    l_node<T>* temp = other.head;

    while (temp != nullptr)
    {
        append(temp->d);
        temp = temp->next;
    }

    return *this;
}



template <typename T>
void double_linkedlist<T>::append(T _d)
{


    l_node<T>* temp = new l_node<T> ;
    temp->d = _d;
    temp->next = nullptr;
    temp->prev = nullptr;

    //if linked list empty
    if(head == nullptr)
    {
        head = tail = temp;
    }
//if linked list has l_nodes
    else
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }

}





template <typename T>
void double_linkedlist<T>::display()
{

    l_node<T>* temp = head;

    while(temp)
    {
        cout << temp->d << " ";
        temp = temp->next;
    }

}



template <typename T>
int double_linkedlist<T>::count_nodes()
{

    l_node<T> * temp = head;
    int c = 0;

    while(temp)
    {
        c++;
        temp = temp->next;
    }

    return c;

}






template <typename T>
l_node<T>* double_linkedlist<T>::search(const T& value)
{

    l_node<T> * temp = head;

    while(temp)
    {

        if(temp->d == value)
            return temp;

        temp = temp->next;
    }
    return nullptr;

}


template <typename T>
T * double_linkedlist<T>::global_search(const T& value){

    l_node<T> * temp = search(value);
    if(temp == nullptr)
        return nullptr;

    return &(temp->d);
}


template <typename T>
void double_linkedlist<T>::insert_node_after_value(T _d, T value)
{

    l_node<T> *p_after = search(value);

    if (p_after == nullptr)
        return;

    if( p_after == tail)
    {
        append(_d);
        return ;
    }


    l_node<T>* temp  = new l_node<T> ;
    temp->d = _d;

//insert in between
    temp->prev = p_after;
    temp->next = p_after->next;
    p_after->next = temp;
    temp->next->prev = temp;


}



template <typename T>
void double_linkedlist<T>::delete_node_by_value(T value)
{

    l_node<T>* temp = search(value);

//if linked list is empty
    if(head == nullptr || temp == nullptr)return;
//if linked list has one l_node
    if(head == tail)
    {
        head = tail = nullptr;
    }
//delete the first l_node
    else if(temp == head)
    {

        temp->next->prev = nullptr;
        head = temp->next;
    }
//if we delete the last l_node
    else if(temp == tail)
    {
        temp->prev->next = nullptr;
        tail = temp->prev;
    }
//delete in between
    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

    }


    delete temp;

}


template <typename T>
void double_linkedlist<T>::delete_all_nodes()
{
    l_node<T> * temp = head;

    while(temp)
    {
        l_node<T>* t = temp->next;
        delete temp;
        temp = t;
    }

    head = tail = nullptr;
}

template <typename T>
double_linkedlist<T>::~double_linkedlist()
{
    delete_all_nodes();
}

