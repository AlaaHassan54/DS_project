#ifndef QUEUE_H
#define QUEUE_H



template <typename T>
struct q_node {
T data;
q_node<T> * next;

};


template <typename T>
class Queue
{

   private:
       q_node<T> * rear;
       q_node<T> * front;
   public :
    Queue();
    void enqueu(T data);
    bool dequeu(T & data);
    bool isFull();
    bool isEmpty();
    bool get_front(T& data) ;
    ~Queue();

};

#include "queue.tpp"

#endif // QUEUE_H
