#ifndef DOUBLE_LINKEDLIST_H
#define DOUBLE_LINKEDLIST_H

#include <string>
using namespace std;



template <typename T>
struct l_node {
 T d;
 l_node * next;
 l_node * prev;

};


template <typename T>
class double_linkedlist
{
  private:
      l_node<T> * head;
      l_node<T> * tail;
      l_node<T>* search(const T& value);
  public:
    double_linkedlist();
    double_linkedlist(const double_linkedlist<T>& other);
    double_linkedlist<T>& operator=(const double_linkedlist<T>& other);
    void append(T _d);
    void display();
    int count_nodes();
    T* global_search(const T& value);
    void insert_node_after_value(T _d , T value);
    void delete_node_by_value(T value);
    void delete_all_nodes();
    ~double_linkedlist();

};

#include "double_linkedlist.tpp"

#endif // DOUBLE_LINKEDLIST_H
