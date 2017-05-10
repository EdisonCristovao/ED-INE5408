// copyright [2017] <Ramna Sidharta>

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

//! .
template<typename T>
class LinkedQueue {
 public:
    LinkedQueue() = default;

    virtual ~LinkedQueue() {
        clear();
    }

    //! .
    void clear() {
        while (!empty()) dequeue();
    }

    //! .
    void enqueue(const T& data) {
        Node* new_tail = new Node(data);  // the new element that'll added

        if (empty()) {
        	first_enqueue(new_tail);
        } else {
        Node* old_tail = tail;
        old_tail->next(new_tail);
        tail = new_tail;
        ++size_;
       }
    }

    //! .
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        } else {
            T removed = head->data();
            Node* old_head = head;
            head = head->next();
            delete old_head;

            --size_;
            return removed;
        }
    }

    //! .
    T& front() const {
        if (empty()) throw std::out_of_range("Queue is empty");
        return head->data();
    }

    //! .
    T& back() const {
        if (empty()) throw std::out_of_range("Queue is empty");
        return tail->data();
    }

    //! .
    bool empty() const {
        return size_ == 0;
    }

    //! .
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {
     public:
       explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
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
        Node* next_{nullptr};
    };

    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    void first_enqueue(Node* new_element) {
        head = new_element;
        tail = head;
        ++size_;
    }

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

