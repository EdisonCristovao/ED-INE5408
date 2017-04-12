/* Copyright 2017 - Edison Junior */

#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions


namespace structures {
//!   Classe DoublyLinkedList
    /*!   Classe generaliza estruturas para armazenar.
    */
template<typename T>
class DoublyLinkedList {
 public:
    //!   Construtor padrão
      /*!  Cria a lista com tamanho padrão
      */
    DoublyLinkedList();
    //!    Destrutor
      /*!  Destroi o objeto criado.
      */
    ~DoublyLinkedList();
    //!    Metodo clear()
      /*!  Limpa a lista size_ se torna 0 e elementos sao deletados
      */
    void clear();
    //! metodo push_back()
      /*!  insere dados na ultima posiçao da estrutura.
      *    \param data do tipo T dado a ser inserido na estrutura.
      *    \sa push_front()
      */
    void push_back(const T& data);  // insere no fim
    //! Metodo push_front()
      /*!  insere dados na primeira posiçao da estrutura.
      *    \param data do tipo T dado a ser inserido na estrutura.
      *    \sa push_back()
      */
    void push_front(const T& data);  // insere no início
    //! Metodo insert()
      /*!  insere dados na posição desejada.
      *    \param data do tipo T dado a ser inserido.
      *    \param index do tipo std::size_t indice para se inserir o dado.
      *    \sa insert_sorted().
      */
    void insert(const T& data, std::size_t index);  // insere na posição
    //! Metodo insert_sorted()
      /*!
      *    \sa insert().
      */
    void insert_sorted(const T& data);  // insere em ordem
    //! Metodo pop()
      /*!  retira o dado da lista
      *    \param index do tipo std::size_t index do dado a ser tirado
      *    \sa pop_back().
      *    \sa pop_front().
      */
    T pop(std::size_t index);  // retira da posição
    //! Metodo pop_back()
      /*!  retira um dado da ultima posisção da lista
      *    \sa pop().
      *    \sa pop_front().
      */
    T pop_back();  // retira do fim
    //! Metodo pop_front()
      /*!  retira um dado da primeira posiçao da lista
      *    \sa pop_back().
      *    \sa pop().
      */
    T pop_front();  // retira do início
    //! Metodo remove()
      /*!  remove o dado indicado
      *    \param data do tipo T dado a ser removido
      */
    void remove(const T& data);  // retira específico
    //! Metodo empty()
      /*!  verifica se a lista esta vazia.
      *    \sa full().
      */
    bool empty() const;  // lista vazia
    //! Metodo contains()
      /*!  verifica se contem o dado na lista
      *    \param data do tipo T dado a ser verificado a existencia
      *    \sa find().
      */
    bool contains(const T& data) const;  // contém
    //! Metodo at()
      /*!  Retorna o dado armazenado em uma posição
      *    \param index tipo size_t indice do dado a ser retornado
      */
    T& at(std::size_t index);  // acesso a um elemento (checando limites)
        //! Metodo at()
      /*!  Retorna o dado armazenado em uma posição
      *    \param index tipo size_t indice do dado a ser retornado
      */
    const T& at(std::size_t index) const;  // getter constante a um elemento
    //! Metodo find()
      /*!  retorna o indice do dado.
      *    \param data do tipo T dado a se retornar indice.
      *    \sa contains().
       */
    std::size_t find(const T& data) const;  // posição de um dado
    //! Metodo size()
      /*!  retorna o tamanho atual da lista.
      *    \sa max_size().
      */
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data) {
            data_ = data;
            next_ = nullptr;
            prev_ = nullptr;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
            prev_ = nullptr;
        }

        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            next_ = next;
            prev_ = prev;
        }

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* node(std::size_t index) {
        Node* node = head;
        for (auto i = 0; i < size(); i++) {
            if (i == index) {
                return node;
            }
        node = node->next();
        }
        return node;
    }
    Node* head;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {  // ok
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {  // ok
    clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {  // ok
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {  // ok
    insert(data, size_);
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node* novo = new Node(data, head);
    if (novo == nullptr) {
        throw(std::out_of_range("Lista cheia"));
    } else {
        if (head != nullptr) {
            head->prev(novo);
        }
        head = novo;
        size_++;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    Node* novo = new Node(data);
    Node* before;
    if (novo == nullptr) {
        delete novo;
        throw(std::out_of_range("Lista Cheia"));
    } else if (index == 0) {
        delete novo;
        push_front(data);
    } else if (index > size_) {
        delete novo;
        throw(std::out_of_range("Indice incorreto"));
    } else {
        before = node(index-1);
        novo->next(before->next());
        before->next(novo);
        novo->prev(before);
        if (novo->next() != nullptr) {
            novo->next()->prev(novo);
        }
        size_++;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
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
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    Node *sai, *before, *after;
    T dado;
    if (empty()) {
        throw(std::out_of_range("Lista vazia"));
    } else if (index == 0) {
        dado = pop_front();
    } else if (index > size_-1) {
        throw(std::out_of_range("Indice incorreto"));
    } else {
       sai = node(index);
       after = sai->next();
       before = sai->prev();
      if (before != nullptr) {
          before->next(after);
      }
      if (after != nullptr) {
        after->prev(before);
      }
      dado = sai->data();
      delete sai;
      size_--;
    }
    return dado;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    return pop(size_-1);
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    Node *sai;
    if (empty()) {
        throw(std::out_of_range("Erro lista vazia"));
    } else {
      sai = head;
      head = sai->next();
      T dado = sai->data();
      delete sai;
      size_--;
      return dado;
      }
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    if (empty()) {
        throw(std::out_of_range("Erro Lista Cheia"));
    } else {
        std::size_t index = find(data);
        pop(index);
    }
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {  // ok
    return size_ == 0;
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
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
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (index > size_) {
        throw(std::out_of_range("Erro Lista Cheia"));
    } else if (empty()) {
        throw(std::out_of_range("Erro Lista vazia"));
    } else {
        Node* nodee = node(index);
        return nodee->data();
    }
}

template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
    if (index > size_) {
        throw(std::out_of_range("Erro Lista Cheia"));
    } else if (empty()) {
        throw(std::out_of_range("Erro Lista vazia"));
    } else {
        Node* node = node(index);
        return node->data();
    }
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
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
std::size_t structures::DoublyLinkedList<T>::size() const {  // ok
    return size_;
}

#endif
