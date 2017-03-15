/* Copyright 2017 xyz*/

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "gtest/gtest.h"

namespace structures {

//! Classe ArrayStack
    /*! Classe pilha com tipo generico
     */
template<typename T>
class ArrayStack {
 public:
  //!   Construtor padrao
    /*  Cria o objeto de forma padrão
     */
    ArrayStack();

  //!   Construtor com parametro
    /*  Cria o objeto com o tamanho que for inserido
     *  \param max do tipo std::size_t
     */
    explicit ArrayStack(std::size_t max);

  //!   Destrutor
    /*  Usado para destruir o objeto quando nao for mais usado
     */
    ~ArrayStack();

  //!   Metodo push()
    /*  metodo insere o dado no topo da pilha
     *  \param data do tipo T
     *  \sa pop()
     */
    void push(const T& data);  // empilha

  //!   Metodo pop()
    /*  metodo retira o dado do topo da pilha e retorna
     *  \sa push()
     */
    T pop();  // desempilha

  //!   Metodo pop()
    /*  metodo retira o dado do topo da pilha e retorna a referencia
     *  \sa push()
     */
    T& top();

  //!   Metodo clar()
    /*  metodo limpa a pilha
     */
    void clear();  // limpa

  //!   Metodo size()
    /*  metodo retorna o tamanho da pilha
     *  \sa max_size()
     */
    std::size_t size();  // tamanho

  //!   Metodo max_size()
    /*  metodo retorna o tamanho maximo da pilha
     *  \sa size()
     */
    std::size_t max_size();

  //!   Metodo empty()
    /*  metodo verifica se a pilha esta vazia
     *  \sa full()
     */
    bool empty();  // vazia

  //!   Metodo full()
    /*  metodo verifica se a pilha esta cheia
     *  \sa empty()
     */
    bool full();  // cheia

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    topo_ = -1;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;;
    topo_ = -1;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        std::out_of_range("Pilha cheia");
    } else {
        contents[++topo_] = data;
    }
}

template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty()) {
        std::out_of_range("Pilha vazia");
    } else {
        return contents[topo_--];
    }
}

template<typename T>
T& structures::ArrayStack<T>::pop() {
    if (empty()) {
        std::out_of_range("Pilha vazia");
    } else {
        return contents[topo_--];
    }
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    topo_ = -1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return topo_+1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayStack<T>::empty() {
    return (topo_ == -1) ;
}

template<typename T>
bool structures::ArrayStack<T>::full() {
    return (topo_ == max_size_-1);
}

#endif
