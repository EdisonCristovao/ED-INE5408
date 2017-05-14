/*Copyright - Edison Cristovao Junior 2017*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "./array_list.h"

namespace structures {

//! Classe BinaryTree
/*! A classe BinaryTree é uma árvore binéria com busca de percursos. */

template<typename T>
class BinaryTree {
 public:
    BinaryTree() = default;

    virtual ~BinaryTree() {
        delete root;
        size_ = 0u;
    }

    //! Método insert
    /*! O método insert insere um dado na árvore. */
    void insert(const T& data) {
        if (empty()) {
            root = new Node(data);
        } else {
            root->insert(data);
        }
        size_++;
    }

    //! Método remove
    /*! O método remove excluiu um dado da árvore. */
    void remove(const T& data) {
        if (!empty()) {
            size_--;
            root->remove(data);
        }
    }

    //! Método contains
    /*! O método contains verifica se um dadp existe na árvore. */
    bool contains(const T& data) const {
        if (!empty()) {
            return root->contains(data);
        }
        return false;
    }

    //! Método empty
    /*! O método empty verifica se a árvore está vazia. */
    bool empty() const {
        return (size_ == 0);
    }

    //! Método size
    /*! O método size retorna o tamanho da árvore. */
    std::size_t size() const {
        return size_;
    }

    //! Método pre_order
    /*! O método pre_order adiciona o dado antes de ordenar a árvore. */
    ArrayList<T> pre_order() const {
        structures::ArrayList<T> v{};
        if (!empty()) {
            root->pre_order(v);
        }
        return v;
    }

    //! Método in_order
    /*! O método in_order adiciona o dado durante a ordenação da árvore. */
    ArrayList<T> in_order() const {
        structures::ArrayList<T> v{};
        if (!empty()) {
            root->in_order(v);
        }
        return v;
    }

    //! Método post_order
    /*! O método post_order adiciona o dado depois de ordenar a árvore. */
    ArrayList<T> post_order() const {
        structures::ArrayList<T> v{};
        if (!empty()) {
            root->post_order(v);
        }
        return v;
    }

 private:
    struct Node {
        explicit Node(const T& data) : data{data}, left{nullptr}, right{nullptr}
        {}

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            Node *n;
            if (data_ < this->data) {
                if (this->left == nullptr) {
                    n = new Node(data_);
                    this->left = n;
                } else {
                    left->insert(data_);
                }
            } else {
                if (this->right == nullptr) {
                    n = new Node(data_);
                    this->right = n;
                } else {
                    right->insert(data_);
                }
            }
        }

        bool remove(const T& data_) {
            if (data_ == this->data) {
                if ((this->left != nullptr) && (this->right != nullptr)) {
                    Node *n = this->right;
                    while (n->left != nullptr) {
                        n = n->left;
                    }
                    this->data = n->data;
                    return right->remove(this->data);
                } else {
                    if (this->right != nullptr) {
                        this->data = right->data;
                        return right->remove(this->data);
                    } else {
                        if (this->left != nullptr) {
                            this->data = left->data;
                            return left->remove(this->data);
                        } else {
                            delete this;
                            return true;
                        }
                    }
                }
            } else {
                if (this->right != nullptr && this->data < data_) {
                    return right->remove(data_);
                } else if (this->left != nullptr && this->data > data_) {
                    return left->remove(data_);
                }
            }
            return false;
        }

        bool contains(const T& data_) const {
            if (data_ == this->data) {
                return true;
            } else {
                if ((this->left != nullptr) && (data_ < this->data)) {
                    return left->contains(data_);
                } else if ((this->right != nullptr) && (data_ > this->data)) {
                    return right->contains(data_);
                }
            }
            return false;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(this->data);
            if (this->left != nullptr) {
                left->pre_order(v);
            }
            if (this->right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (this->left != nullptr) {
                left->in_order(v);
            }
            v.push_back(this->data);
            if (this->right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (this->left != nullptr) {
                left->post_order(v);
            }
            if (this->right != nullptr) {
                right->post_order(v);
            }
            v.push_back(this->data);
        }
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
