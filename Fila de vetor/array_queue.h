/* Copyright 2017 - Edison Junior */

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

//! Classe ArrayQueue
    /*  Classe Fila com tipo generico
     */
template<typename T>
class ArrayQueue {
public:
    //! Metodo Construtor
      /*  Construtor padrao que da um tamanho pre definido a Fila
      */
    ArrayQueue() {
      max_size_ = DEFAULT_SIZE;
      contents = new T[max_size_];
    }

    //! Metodo Construtor com parametro
      /*  Cria a fila com o tamanho que o usuario escolher
      *   \param max do tipo std::size_t, define o tamanho da Fila
      */
    explicit ArrayQueue(std::size_t max) {
      max_size_ = max;
      contents = new T[max_size_];
    }

    //! Destrutor
      /*  Usado para destruir o objeto quando nao for mais Usado
      */
    ~ArrayQueue();

    //! Metodo enqueue()
      /*  enfileira mais um elemento na Fila.
      *   \param data do tipo T, dado a ser infileirado
      *   \sa dequeue()
      */
    void enqueue(const T& data) {
      if (full()) {
        std::out_of_range("Fila cheia");
      } else {
        contents[++size_] = data;
      }
    }

    //! Metodo dequeue()
      /*  Desenfileira usado para tirar o primeiro elemento da Fila
      *   \sa enqueue()
      */
    T dequeue(){
      if (empty()) {
        std::out_of_range("Fila vazia");
      } else {
        T data = contents[0];
        size_ --;
        move_foward();
        return data;
      }
    }

    //! Metodo back()
      /*  DUVIDA NESSE Metodo
      */
    T& back(){
      return contents[size_];
    }

    //! Metodo clear()
      /*  Limpa a fila dando ao size_ o valor -1;
      */
    void clear(){
      size_ = -1;
    }

    //! Metodo size()
      /*  retorna o tamanho da fila
      */
    std::size_t size(){
      return (size_+1);
    }

    //! Metodo max_size()
      /*  retorna o tamanho maximo da fila
      */
    std::size_t max_size(){
      return max_size_;
    }

    //! Metodo empty()
      /*  verifica se a fila esta vazia
      */
    bool empty(){
      return (size_ == -1);
    }

    //! Metodo full()
      /*  verifica se a fila esta cheia
      */
    bool full(){
      return (size_ == max_size_-1);
    }

 private:
    //! Metodo move_foward()
      /*  arrasta todos os valores uma posição atras,
      *   cobrindo a posiçao "0"
      */
    void move_foward(){
      for (auto i = 0; i != size_+1; i++){
        data[i] = data[i+1];
      }
    }

    T* contents;  // Vetor dados
    int size_ {-1};  // tamanho atual da fila
    std::size_t max_size_;  // tamanho maximo da fila

    static const auto DEFAULT_SIZE = 10u;   // tamanho padrao para a fila
};

}  // namespace structures
#endif
