/* Copyright 2017 - Edison Junior */

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

//! Classe ArrayQueue
    /*  Classe Fila de vetor com tipo generico
     */
template<typename T>
class ArrayQueue {
 public:
    //! Metodo Construtor
      /*  Construtor padrao que da um tamanho pre definido a Fila
      */
    ArrayQueue();

    //! Metodo Construtor com parametro
      /*  Cria a fila com o tamanho que o usuario escolher
      *   \param max do tipo std::size_t, define o tamanho da Fila
      */
    explicit ArrayQueue(std::size_t max);

    //! Destrutor
      /*  Usado para destruir o objeto quando nao for mais Usado
      */
    ~ArrayQueue();

    //! Metodo enqueue()
      /*  enfileira mais um elemento na Fila.
      *   \param data do tipo T, dado a ser infileirado
      *   \sa dequeue()
      */
    void enqueue(const T& data);

    //! Metodo dequeue()
      /*  Desenfileira usado para tirar o primeiro elemento da Fila
      *   \sa enqueue()
      */
    T dequeue();

    //! Metodo back()
      /*  retorna o ultimo elemento da fila
      */
    T& back();

    //! Metodo clear()
      /*  Limpa a fila dando ao size_ o valor -1;
      */
    void clear();

    //! Metodo size()
      /*  retorna o tamanho da fila
      */
    std::size_t size();

    //! Metodo max_size()
      /*  retorna o tamanho maximo da fila
      */
    std::size_t max_size();

    //! Metodo empty()
      /*  verifica se a fila esta vazia
      */
    bool empty();

    //! Metodo full()
      /*  verifica se a fila esta cheia
      */
    bool full() ;
 private:
    //! Metodo move_foward()
      /*  arrasta todos os valores uma posição atras,
      *   cobrindo a posiçao "0"
      */
    void move_foward();

    T* contents;  // Vetor dados
    int size_;  // tamanho atual da fila
    int max_size_;  // tamanho maximo da fila

    static const auto DEFAULT_SIZE = 10u;   // tamanho padrao para a fila
};

}  // namespace structures

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(){
  max_size_ = DEFAULT_SIZE;
  contents = new T[max_size_];
  size_=-1;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max){
  max_size_ = max;
  contents = new T[max_size_];
  size_=-1;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue(){
  delete[] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data){
  if (full()) {
   throw( std::out_of_range("Fila cheia"));
  } else {
    contents[++size_] = data;
  }
}

template<typename T>
T structures::ArrayQueue<T>::dequeue(){
  if (empty()) {
    throw(std::out_of_range("Fila vazia"));
  }
    T data = contents[0];
    size_--;
    move_foward();
    return data;
}

template<typename T>
T& structures::ArrayQueue<T>::back(){
  if (empty()) {
      throw(std::out_of_range("Fila vazia"));
  }
  return contents[size_];
}

template<typename T>
void structures::ArrayQueue<T>::clear(){
  size_ = -1;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size(){
  return (size_+1);
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size(){
  return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty(){
  return (size_ == -1);
}

template<typename T>
bool structures::ArrayQueue<T>::full(){
  return (size() == max_size_);
}

template<typename T>
void structures::ArrayQueue<T>::move_foward(){
  for (auto i = 0; i != size_+1; i++) {
    contents[i] = contents[i+1];
  }
}


#endif



i = 2
