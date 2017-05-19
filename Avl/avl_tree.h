//! Descrição do arquivo
/*!
 *	\author Daniel Boso
 *	\since 7/11/2016
 *	\version 1.0
 *	\copyright General Public License version 2
 */

#include <algorithm>
#include "array_list.h"

namespace structures {

template<typename T>
//! Class AVLTree
class AVLTree {
public:
    //! Destrutor
    ~AVLTree() {
      delete root;
    }

    //! Função insert
    /*!
     *  Insere um elemento na árvore
     *  \param dado a ser inserido
     */
    void insert(const T& data) {
      if (root == nullptr) {
        root = new Node(data);
      } else {
        root->insert(data);
      }
      size_++;
    }

    //! Função remove
    /*!
     *  Remove um elemento da árvore
     *  \param dado a ser removido
     */
    void remove(const T& data) {
      if (root->remove(data)) {
        size_--;
      }
    }

    //! Função contains
    /*!
     *  Verifica se o elemento está na árvore
     *  \param dado a ser verificado
     */
    bool contains(const T& data) const {
      if (root == nullptr) {
        return false;
      } else {
        return root->contains(data);
      }
    }

    //! Função empty
    /*!
     *  Verifica se a árvore está vazia
     */
    bool empty() const {
      if (size_ == 0) {
        return true;
      }
      return false;
    }

    //! Função size
    /*!
     *  Retorna tamanho da árvore
     */
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
        explicit Node(const T& data):
          data{data},
          height{0},
          left{nullptr},
          right{nullptr}
        {}

        T data;
        std::size_t height;
        Node* left;
        Node* right;

        void insert(const T& data_) {
          Node* novo;
          Node* tree_rotate;

          if (data_ < this->data) {
            if (this->left == nullptr) {
              novo = new Node(data_);
              this->left = novo;
              if (height_node(this->left) - height_node(this->right) > 1) {
                if (data < this->left->data) {
                  tree_rotate = simple_left(this);
                } else {
                  tree_rotate = double_left(this);
                }
                if (this->left == this) {
                  this->left = tree_rotate;
                } else {
                  this->right = tree_rotate;
                }
              } else {
                this->update_height(max_height(this->left, this->right) + 1);
              }
            } else {
              this->left->insert(data_);
            }
          } else {
            if (this->right == nullptr) {
              novo = new Node(data_);
              this->right = novo;
              if ((height_node(this->right) - height_node(this->left)) > 1) {
                if (data < this->right->data) {
                  tree_rotate = simple_right(this);
                } else {
                  tree_rotate = double_right(this);
                }
                if (this->right == this) {
                  this->right = tree_rotate;
                } else {
                  this->left = tree_rotate;
                }
              } else {
                this->update_height(max_height(this->left, this->right) + 1);
              }
            } else {
              this->right->insert(data_);
            }
          }
        }

        bool remove(const T& data_) {
          Node* temp;
          if (this == nullptr) {
            return false;
          } else {
            if (data_ < this->data) {
              return this->left->remove(data_);
            } else {
              if (data_ > this->data) {
                return this->right->remove(data_);
              } else {
                if (this->right != nullptr && this->left != nullptr) {
                  temp = this->right->left;
                  this->data = temp->data;
                  return this->right->remove(this->data);
                } else {
                  temp = this;
                  if (this->right != nullptr) {
                    temp = this->right;
                    this->data = temp->data;
                    return this->right->remove(temp->data);
                  } else {
                    if (this->left != nullptr) {
                      temp = this->left;
                      this->data = temp->data;
                      return this->left->remove(temp->data);
                    } else {
                      delete this;
                      return true;
                    }
                  }
                }
              }
            }
          }
        }

        bool contains(const T& data_) const {
          if (this->data == data_) {
            return true;
          } else {
            if (this->data < data_) {
              if (this->right == nullptr) {
                return false;
              }
                return this->right->contains(data_);
            } else {
              if (this->left == nullptr) {
                return false;
              }
              return this->left->contains(data_);
            }
          }
        }

        void update_height(std::size_t height_) {
            height = height_;
        }

        Node* simple_left(Node* node) {
          Node *root_new;
          root_new = node->left;
          node->left = root_new->left;
          root_new->right = node;
          node->update_height(max_height(node->left, node->right) +1);
          root_new->update_height(max_height(root_new->left, node->right) +1);
          return root_new;
        }

        Node* simple_right(Node* node) {
          Node *root_new;
          root_new = node->left;
          node->left = root_new->right;
          root_new->left = node;
          node->update_height(max_height(node->right, node->left) + 1);
          root_new->update_height(max_height(root_new->right, node) + 1);
          return root_new;
        }

        Node* double_left(Node* node_rotate) {
          node_rotate->left = simple_right(node_rotate->left);
          return simple_left(node_rotate);
        }

        Node* double_right(Node* node_rotate) {
          node_rotate->right = simple_right(node_rotate->right);
          return simple_right(node_rotate);
        }

        int height_node(Node *sub_tree) {
          if (sub_tree == nullptr) {
            return -1;
          } else {
            return sub_tree->height;
          }
        }

        int max_height(Node* sub_tree_a, Node* sub_tree_b) {
          int height_sub_a;
          int height_sub_b;

          if (sub_tree_a == nullptr) {
            height_sub_a = -1;
          } else {
            height_sub_a = sub_tree_a->height;
          }

          if (sub_tree_b == nullptr) {
            height_sub_b = -1;
          } else {
            height_sub_b = sub_tree_b->height;
          }

          if (height_sub_a > height_sub_b) {
            return height_sub_a;
          }
          return height_sub_b;
        }

        void pre_order(ArrayList<T>& v) const {
          if (this != nullptr) {
            v.push_back(this->data);
            this->left->pre_order(v);
            this->right->pre_order(v);
          }
        }

        void in_order(ArrayList<T>& v) const {
          if (this != nullptr) {
            this->left->in_order(v);
            v.push_back(this->data);
            this->right->in_order(v);
          }
        }

        void post_order(ArrayList<T>& v) const {
          if (this != nullptr) {
            this->left->post_order(v);
            this->right->post_order(v);
            v.push_back(this->data);
          }
        }
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures
