/* Copyright 2017 - Edison Junior*/

#ifndef STRUCTURES_ARRAY_STACK_H  // coments
#define STRUCTURES_ARRAY_STACK_H  // coments

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

//! Classe ArrayStack
    /* Classe pilha com tipo generico
     */
template<typename T>
class ArrayStack {
 public:
  //!   Construtor padrao
    /*  Cria uma pilha de forma padrão
     */
    ArrayStack();

  //!   Construtor com parametro
    /*  Cria a pilha com o tamanho que for inserido
     *  \param max do tipo std::size_t, tamanho maximo da pilha
     */
    explicit ArrayStack(std::size_t max);

  //!   Destrutor
    /*  Usado para destruir o objeto quando nao for mais usado
     */
    ~ArrayStack();

  //!   Metodo push()
    /*  metodo insere o dado no topo da pilha
     *  \param data do tipo T, dado a ser inserido
     *  \sa pop()
     */
    void push(const T& data);

  //!   Metodo pop()
    /*  metodo retira o dado do topo da pilha e retorna
     *  \sa push()
     */
    T pop();

  //!   Metodo pop()
    /*  metodo retira o dado do topo da pilha e retorna a referencia
     *  \sa push()
     */
    T& top();

  //!   Metodo clar()
    /*  metodo limpa a pilha
     */
    void clear();

  //!   Metodo size()
    /*  metodo retorna o tamanho da pilha
     *  \sa max_size()
     */
    std::size_t size();

  //!   Metodo max_size()
    /*  metodo retorna o tamanho maximo da pilha
     *  \sa size()
     */
    std::size_t max_size();

  //!   Metodo empty()
    /*  metodo verifica se a pilha esta vazia
     *  \sa full()
     */
    bool empty();

  //!   Metodo full()
    /*  metodo verifica se a pilha esta cheia
     *  \sa empty()
     */
    bool full();

 private:
    T* contents;  // dados da pilha
    int top_;  // tamanho atual da pilha
    int max_size_;  // tamanho maximo da pilha

    static const auto DEFAULT_SIZE = 10u;  // tamanho padrao para a pilha
};

}  // namespace structures

template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete[] contents;
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw(std::out_of_range("Pilha cheia"));
    } else {
        contents[++top_] = data;
    }
}

template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty()) {
         throw(std::out_of_range("Pilha Vazia"));
    }
    return contents[top_--];
}

template<typename T>
T& structures::ArrayStack<T>::top() {
    return contents[top_];
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return top_+1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayStack<T>::empty() {
    return (top_ == -1);
}

template<typename T>
bool structures::ArrayStack<T>::full() {
    return (size() == max_size_);
}

#endif
