

template <typename T>

Queue<T>::Queue():rear{nullptr}, front{nullptr} {}


template <typename T>
void Queue<T>::enqueu(T data)
{

    if(isFull())
        return ;

    q_node<T> * temp = new q_node<T> ;
    temp->data = data;
    temp->next = nullptr;

    if(rear == nullptr)
        rear = front = temp;
    else
    {
        rear->next = temp;
    }

    rear = temp;

}



template <typename T>
bool Queue<T>::dequeu(T & data)
{
    if(isEmpty())
        return false ;

    data = front->data;
    q_node<T> * t = front;

    if(front == rear)
    {
        front = rear = nullptr;
    }
    else
    {
        front = front->next;
    }

    delete t;

    return true;

}


template <typename T>
bool Queue<T>::isFull()
{
    q_node<T> * temp = new q_node<T> ;
    if(temp == nullptr)
        return true;

    delete temp;
    return false;

}



template <typename T>
bool Queue<T>::isEmpty()
{
    return (rear == nullptr);
}


template <typename T>
bool Queue<T>::get_front(T& data) 
{
    if(isEmpty())
        return false;

    data = front->data;
    return true;
}


template <typename T>
Queue<T>::~Queue()
{
    q_node<T>* temp = front;

    while (temp != nullptr)
    {
        q_node<T>* nextq_node = temp->next;

        delete temp;

        temp = nextq_node;
    }

    front = rear = nullptr;
}



