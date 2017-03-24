/* Copyright 2017 - Edison Junior */

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std
#include <stdexcept>  // excecao

namespace structures {

  //!   Classe ArrayList
    /*!   Classe generaliza estruturas para armazenar.
    */
template<typename T>
class ArrayList {
 public:
    //!   Construtor padrão
      /*!  Cria a lista com tamanho padrão
      */
    ArrayList();

    //!   Construtor com parametro
      /*!  Construtor que define o tamanho da lista por parametro.
      *    \param max_size define o tamanho da lista.
      */
    explicit ArrayList(std::size_t max_size);

    //!    Destrutor
      /*!  Destroi o objeto criado.
      */
    ~ArrayList();

    //!    Metodo clear()
      /*!  Limpa a lista size_ se torna 0
      */
    void clear();

    //! metodo push_back()
      /*!  insere dados na ultima posiçao da estrutura.
      *    \param data do tipo T dado a ser inserido na estrutura.
      *    \sa push_front()
      */
    void push_back(const T& data);

    //! Metodo push_front()
      /*!  insere dados na primeira posiçao da estrutura.
      *    \param data do tipo T dado a ser inserido na estrutura.
      *    \sa push_back()
      */
    void push_front(const T& data);

    //! Metodo insert()
      /*!  insere dados na posição desejada.
      *    \param data do tipo T dado a ser inserido.
      *    \param index do tipo std::size_t indice para se inserir o dado.
      *    \sa insert_sorted().
      */
    void insert(const T& data, std::size_t index);

    //! Metodo insert_sorted()
      /*!
      *    \sa insert().
      */
    void insert_sorted(const T& data);

    //! Metodo pop()
      /*!  retira o dado da lista
      *    \param index do tipo std::size_t index do dado a ser tirado
      *    \sa pop_back().
      *    \sa pop_front().
      */
    T pop(std::size_t index);

    //! Metodo pop_back()
      /*!  retira um dado da ultima posisção da lista
      *    \sa pop().
      *    \sa pop_front().
      */
    T pop_back();

    //! Metodo pop_front()
      /*!  retira um dado da primeira posiçao da lista
      *    \sa pop_back().
      *    \sa pop().
      */
    T pop_front();

    //! Metodo remove()
      /*!  remove o dado indicado
      *    \param data do tipo T dado a ser removido
      */
    void remove(const T& data);

    //! Metodo full()
      /*!  verifica se a lista esta cheia
      *    \sa empty().
      */
    bool full() const;

    //! Metodo empty()
      /*!  verifica se a lista esta vazia.
      *    \sa full().
      */
    bool empty() const;

    //! Metodo contains()
      /*!  verifica se contem o dado na lista
      *    \param data do tipo T dado a ser verificado a existencia
      *    \sa find().
      */
    bool contains(const T& data) const;

    //! Metodo find()
      /*!  retorna o indice do dado.
      *    \param data do tipo T dado a se retornar indice.
      *    \sa contains().
       */
    std::size_t find(const T& data) const;

    //! Metodo size()
      /*!  retorna o tamanho atual da lista.
      *    \sa max_size().
      */
    std::size_t size() const;

    //! Metodo max_size()
      /*!  retorna o tamano total da lista
      *    \sa size().
      */
    std::size_t max_size() const;

    //! Metodo at()
      /*!
      *
      */

    T& at(std::size_t index);

    //! Metodo operator[]()
      /*!
      *
      */

    T& operator[](std::size_t index);

    //! Metodo at[]()
      /*!
      *
      */

    const T& at(std::size_t index) const;

    //! Metodo operator()
      /*!
      *
      */
    const T& operator[](std::size_t index) const;

 private:
    //! Metodo move_forward()
      /*!   arrasta os dados para frente da estrutura
      *    \param index do tipo std::size_t arrasta ate o index indicado
      *    \sa move_backward().
      */
    void move_forward(std::size_t index);

    //! Metodo move_backward)_
      /*!   arrasta os dados da estrutura para tras.
      *    \param index do tipo std::size_t arrasta ate o index indicado
      *    \sa move_forward().
      */
    void move_backward(std::size_t index);

    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

template<typename T>
structures::ArrayList<T>::ArrayList() {
  max_size_ = DEFAULT_MAX;
  contents = new T[max_size_];
  size_ = 0;
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
  max_size_ = max_size;
  contents = new T[max_size_];
  size_ = 0;
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
  delete[] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
  size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
  if (full()) {
    throw(std::out_of_range("Lista cheia"));
  } else {
    contents[size_++] = data;
  }
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
  if (full()) {
    throw(std::out_of_range("Lista cheia"));
  } else if (empty()) {
    contents[size_++] = data;
  } else {
    move_backward(0);
    contents[0] = data;
    size_++;
  }
}


template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
  if (full()) {
    throw(std::out_of_range("Lista cheia"));
  } else if (index < 0 || index > size_) {
    throw(std::out_of_range("Indice incorreto"));
  } else {
    move_backward(index);
    contents[index] = data;
    size_++;
  }
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
  if (full()) {
    throw(std::out_of_range("Lista cheia"));
  } else if (empty()) {
    contents[size_++] = data;
  } else {
    auto i = 0;
    while (i != size_ && contents[i]< data) {
      i++;
    }
    insert(data, i);
  }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
  if (empty()) {
    throw(std::out_of_range("Lista vazia"));
  } else if (index < 0 || index >= size_) {
    throw(std::out_of_range("Indice incorreto"));
  }
  T data = contents[index];
  size_--;
  move_forward(index);
  return data;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
  if (empty()) {
    throw(std::out_of_range("Lista vazia"));
  }
  return contents[--size_];
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
  if (empty()) {
    throw(std::out_of_range("Lista vazia"));
  }
  T data = contents[0];
  size_--;
  move_forward(0);
  return data;
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
  if (empty()) {
    throw(std::out_of_range("Lista vazia"));
  } else {
    for (auto i = 0; i < size_; i++) {
    if (contents[i] == data) {
        pop(i);
      }
    }
  }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
  return (size_ == max_size_);
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
  return (size_ == 0);
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
  for (auto i = 0; i < size_; i++) {
    if (data == contents[i]) {
      return true;
    }
  }
  return false;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
  if (empty()) {
    throw(std::out_of_range("Lista vazia"));
  } else {
    for (auto i = 0; i < size_; i++) {
    if (data == contents[i]) {
      return i;
      }
    }
  }
  return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
  return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
  return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
  if (index < 0 || index >= size_) {
    throw(std::out_of_range("Indice incorreto"));
  }
  return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
  if (index < 0 || index > size_) {
    throw(std::out_of_range("Indice incorreto"));
  }
  return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
  if (index < 0 || index > size_) {
    throw(std::out_of_range("Indice incorreto"));
  }
  return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
  if (index < 0 || index > size_) {
    throw(std::out_of_range("Indice incorreto"));
  }
  return contents[index];
}

template<typename T>
void structures::ArrayList<T>::move_forward(std::size_t index) {
  for (auto i = index; i != size_; i++) {
    contents[i]= contents[i+1];
  }
}

template<typename T>
void structures::ArrayList<T>::move_backward(std::size_t index) {
  for (auto i = size_; i != index; i--) {
    contents[i] = contents[i-1];
  }
}

#endif
