/* Copyright 2017 - Edison Junior */

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>
#include "./linked_list.h"

namespace structures {
//! Classe LinkedStack
    /* Classe pilha com tipo generico
     */
template<typename T>
class LinkedStack: protected LinkedList<T> {
 public:
  //!   Construtor padrao
    /*  Cria uma pilha de forma padrão
     */
    LinkedStack();

  //!   Metodo push()
    /*  metodo insere o dado no topo da pilha
     *  \param data do tipo T, dado a ser inserido
     *  \sa pop()
     */
    ~LinkedStack();

//! Class LinkedList
    /* Classe emplementa a função de cadeia de ponteiros a lista
    */
    void clear();  //  limpa pilha

  //!   Metodo clar()
    /*  metodo limpa a pilha
     */
    void push(const T& data);  //  empilha

  //!   Metodo pop()
    /*  metodo retira o dado do topo da pilha e retorna
     *  \sa push()
     */
    T pop();  //  desempilha

  //!   Metodo pop()
    /*  metodo retira o dado do topo da pilha e retorna a referencia
     *  \sa push()
     */
    T& top();  //  dado no topo

  //!   Metodo empty()
    /*  metodo verifica se a pilha esta vazia
     */
    bool empty() const;  //  pilha vazia

  //!   Metodo size()
    /*  metodo retorna o tamanho da pilha
     */
    std::size_t size() const;  //  tamanho da pilha

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

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    LinkedList<T>::push_back(data);
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    return LinkedList<T>::pop_back();
}

template<typename T>
T& structures::LinkedStack<T>::top() {
    return LinkedList<T>::at(LinkedList<T>::size()-1);
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return LinkedList<T>::empty();
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return LinkedList<T>::size();
}

#endif
