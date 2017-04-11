/* Copyright 2017 - Edison Junior */

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {
//! Class LinkedList
    /* Classe emplementa a função de cadeia de ponteiros a lista
    */
template<typename T>
class LinkedList {
 public:
//! Metodo LinkedList()
    /*  construtor padrão, cria a cabeça da lista encadeada
    */
    LinkedList();  //  construtor padrão
//! Metodo ~LinkedList()
    /*  Destrutor padão da classe
    */
    ~LinkedList();  //  destrutor

//! Metodo clear()
    /*  Limpa a lista encadeada
    */
    void clear();  //  limpar lista

//! Metodo push_back()
    /*  Insere um node no fim da lista
    *   \param data tipo T dado a ser criado o node
    */
    void push_back(const T& data);  //  inserir no fim

//! Metodo push_front()
    /*  Insere um node no inicio da lista
    *   \param data tipo T dado a ser criado o node
    */
    void push_front(const T& data);  //  inserir no início

//! Metodo insert()
    /*  Insere um node em qualquer lugar da lista
    *   \param data tipo T dado a ser criado o node
    *   \param index tipo size_t posiçao em que o node sera criado
    */
    void insert(const T& data, std::size_t index);  //  inserir na posição

//! Metodo insert_sorted()
    /*  Insere um node em odem
    *   \param data tipo T dado a ser respeitada a ordem
    */
    void insert_sorted(const T& data);  //  inserir em ordem

//! Metodo at()
    /*  Retorna o atributo data de um node
    *   \param index do tipo size_t indice do dado a ser retornado
    */
    T& at(std::size_t index);  //  acessar um elemento na posição index

//! Metodo pop()
    /*  Retira um node da lista
    *   \param index do tipo size_t indice do node a se deletar
    */
    T pop(std::size_t index);  //  retirar da posição

//! Metodo pop_back()
    /*  Retira o ultimo node da lista
    */
    T pop_back();  //  retirar do fim

//! Metodo pop_front()
    /*  retira um node do inicio da lista
    */
    T pop_front();  //  retirar do início

//! Metodo remove()
    /*  Retira um node quem contem o dado data
    *   \param data tipo T dado do node a ser deletado
    */
    void remove(const T& data);  //  remover específico

//! Metodo empty()
    /*  Verifica se a lista esta vazia
    *   obs lista nao tem metodo full pois é dinamica e nao estatica
    */
    bool empty() const;  //  lista vazia

//! Metodo contains()
    /*  verifica se a lista contem o node com o dado especifico
    *   \param data tipo T dado a ser verificado a existencia
    */
    bool contains(const T& data) const;  //  contém

//! Metodo find()
    /*  retorna o indice do node que contem o dado especifico
    *   \param data tipo T dado a ser procurado a posiçao
    */
    std::size_t find(const T& data) const;  //  posição do dado
/*! Class LinkedList
*/
    /*
    *
    */
    std::size_t size() const;  //  tamanho da lista

 private:
    class Node {  //  Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  //  getter: dado
            return data_;
        }

        const T& data() const {  //  getter const: dado
            return data_;
        }

        Node* next() {  //  getter: próximo
            return next_;
        }

        const Node* next() const {  //  getter const: próximo
            return next_;
        }

        void next(Node* node) {  //  setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  //  último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* current(std::size_t index) {  // retorna node com idice
        auto it = head;
        if (index != 0) {
            for (auto i = 1; i < size(); ++i) {
            if (i == index)
                return it;
            it = it->next();
            }
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

template<typename T>
structures::LinkedList<T>::LinkedList() {
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* novo = new Node(data);
    if ( novo == nullptr ) {
        delete novo;
        throw(std::out_of_range("Erro lista cheia"));
    } else {
        novo->next(head);
        head = novo;
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    Node* novo = new Node(data);
    Node* before;
    if ( novo == nullptr ) {
        throw(std::out_of_range("Erro Lista Cheia"));
    } else if (index > size_) {
        delete novo;
        throw(std::out_of_range("Erro Lista Cheia"));
    } else if (index == 0) {
        delete novo;
        push_front(data);
    } else {
        before = current(index);
        novo->next(before->next());
        before->next(novo);
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* before = head;
        for (auto i = 0; i != size_; i++) {
            if (before->data() > data) {
                insert(data, i);
                break;
            } else if (i == size_ -1) {
                push_back(data);
                break;
            } else {
                before = before->next();
            }
        }
    }
}

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index > size_) {
        throw(std::out_of_range("Erro Lista Cheia"));
    } else if (empty()) {
        throw(std::out_of_range("Erro Lista vazia"));
    } else {
          Node* node = head;
          for (auto i = 0u; i != index; i++) {
              node = node->next();
          }
        // node = current(index+1);
        return node->data();
    }
}

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
  Node *sai, *before;
  T dado;
  if (empty()) {
    throw("lista vazia");
    } else if (index < 0 || index > size_ -1) {
       throw(std::out_of_range("Erro Lista Cheia"));
    } else if (index == 0) {
      pop_front();
    } else {
    before = current(index);
    sai = before->next();
    before->next(sai->next());
    dado = sai->data();
    delete sai;
    size_--;
  }
    return dado;
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
  Node *sai;
  if (empty()) {
    throw(std::out_of_range("Lista vazia"));
  } else {
    sai = end();
    T dado = sai->data();
    delete sai;
    size_--;
    return dado;
  }
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
  Node *sai;
  if (empty()) {
    throw(std::out_of_range("Erro lista vazia"));
  } else {
    sai = head;
    head = head->next();
    T dado = sai->data();
    size_--;
    delete sai;
    return dado;
  }
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    if (empty()) {
        throw(std::out_of_range("Erro Lista Cheia"));
    } else {
        std::size_t index = find(data);
        pop(index);
    }
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
  return size_ == 0;
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    if (empty()) {
        throw("lista vazia");
    } else {
        Node *verifica = head;
    for (auto i = 0; i != size_; i++) {
        if (verifica->data() == data) {
            return true;
        }
            verifica = verifica->next();
        }
    return false;
    }
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
       if (empty()) {
        throw("lista vazia");
    } else {
        Node *verifica = head;
    for (auto i = 0; i != size_; i++) {
        if (verifica->data() == data) {
            return i;
        }
            verifica = verifica->next();
        }
    }
return size_;
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
  return size_;
}

#endif
