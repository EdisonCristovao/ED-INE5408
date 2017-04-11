/* Copyright 2017 - Edison Junior */

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>
#include "./linked_list.h"

namespace structures {
//! Classe LinkedQueue
    /*  Classe Fila de vetor com tipo generico
     */
template<typename T>
class LinkedQueue: private LinkedList<T> {
 public:
    //! Metodo Construtor
      /*  Construtor padrao da Fila encadeada
      */
    LinkedQueue();

    //! Destrutor
      /*  Usado para destruir o objeto quando nao for mais Usado
      */
    ~LinkedQueue();

    //! Metodo clear()
      /*  Limpa a fila dando ao size_ o valor -1;
      */
    void clear();  // limpar

    //! Metodo enqueue()
      /*  enfileira mais um elemento na Fila.
      *   \param data do tipo T, dado a ser infileirado
      *   \sa dequeue()
      */
    void enqueue(const T& data);  // enfilerar

    //! Metodo dequeue()
      /*  Desenfileira usado para tirar o primeiro elemento da Fila
      *   \sa enqueue()
      */
    T dequeue();  // desenfilerar

    //! Metodo front()
      /*  retorna o primeiro elemento da fila
      */
    T& front();  // primeiro dado

    //! Metodo back()
      /*  retorna o ultimo elemento da fila
      */
    T& back();  // último dado

    //! Metodo empty()
      /*  verifica se a fila esta vazia
      */
    bool empty() const;  // fila vazia

    //! Metodo size()
      /*  retorna o tamanho da fila
      */
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data);
        Node(const T& data, Node* next);
        T& data();   //  getter: info
        const T& data() const;  // getter-constante: info
        Node* next();  // getter: próximo
        const Node* next() const;  // getter-constante: próximo
        void next(Node* next);  // setter: próximo

     private:
        T data_;
        Node* next_;
    };

    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    LinkedList<T>::clear();
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    LinkedList<T>::push_back(data);
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    T ret = LinkedList<T>::pop_front();
    if (empty()) {
        tail = nullptr;
    }
    return ret;
}

template<typename T>
T& structures::LinkedQueue<T>::front() {
    return LinkedList<T>::at(0);
}

template<typename T>
T& structures::LinkedQueue<T>::back() {
    return LinkedList<T>::at(LinkedList<T>::size()-1);
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return LinkedList<T>::empty();
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return LinkedList<T>::size();
}

#endif
