// Copyright [2017] Ramna Sidharta

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>


//! Implements a linked list (data structure) using a non static array;
/*!
 * This data structure works just like a real 'list'. It is a list
 * with manibulable elements. Seems like a array list, but linked list
 * is implemented using pointers. 
 */
template<typename T>
class LinkedList {
 public:
    LinkedList() = default;

    //! Destroys the list.
    ~LinkedList() {
        clear();
    }

    //! Clears the list;
    /*!
     * Clears the list removing all elements individualy using a loop while.
     */
    void clear() {
        while (!empty()) pop_front();
    }

    //! Adds an element to the last position of the list;
    /*!
     * @param data - The element that'll be added to the list.
     */
    void push_back(const T& data) {
        insert(data, size_);
    }

    //! Adds an element to the first position of the list;
    /*!
     * @param data - The element that'll be added to the list.
     */
    void push_front(const T& data) {
        head = new Node(data, head);
        ++size_;
    }

    //! Adds an element to the given position;
    /*!
     * @param data - The element that'll be inserted to the list;
     * @param index - The position that the element 'data' will be inserted.
     */
    void insert(const T& data, std::size_t index) {
        if (index == 0) {
        	push_front(data);
        } else if (index > size_) {
            throw std::out_of_range("Invalid index.");
        } else {
            Node* previous = head;
            for (auto i = 0u; i < index-1; ++i)
                previous = previous->next();
            previous->next(new Node(data, previous->next()));
            ++size_;
        }
    }

    //! Adds given element to the list in order;
    /*!
     * Adds 'data' to the list before the first position that contains
     * an element bigger than it.
     *
     * @param data - The element that'll be added to the list.
     */
    void insert_sorted(const T& data) {
    	Node* previous = head;
    	if (empty() || data <= head->data()) {
        	push_front(data);
        } else {
        std::size_t i = 0u;
        while (previous->next() != nullptr && data > previous->next()->data()) {
            previous = previous->next();
            ++i;
        	}
        }
        previous->next(new Node(data, previous->next()));
        ++size_;
    }

    //! Return the element in the given position;
    /*!
     * @param index - The index to obtains its position.
     *
     * @return A reference of the element at the given index.
     */
    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds.");
        } else {
            Node* element = head;
            for (auto i = 0u; i < index; ++i) {
                element = element->next();
            }
            return element->data();
        }
    }

    //! Removes the element at the given position;
    /*!
     * @param index - The position of the element that'll be removed.
     *
     * @return A referente of the element that was removed.
     */
    T pop(std::size_t index) {
        if (index == 0) return pop_front();
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds.");
        } else {
            Node* previous = head;
            for (auto i = 0u; i < index-1; ++i) {
                previous = previous->next();
            }
            T removed_data = previous->next()->data();
            Node* removed_element = previous->next();
            previous->next(previous->next()->next());

            --size_;
            delete removed_element;
            return removed_data;
        }
    }

    //! Removes the element at the last position of the list;
    /*!
     * @return A reference of the element that was removed.
     */
    T pop_back() {
        return pop(size_ - 1);
    }

    //! Removes the element at the first position of the list;
    /*!
     * @return A reference of the element that was removed.
     */
    T pop_front() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        } else {
            T removed = head->data();
            Node* newHead = head->next();
            delete head;
            head = newHead;

            --size_;
            return removed;
        }
    }

    //! Remove the first element of the list that is equal to given data;
    /*!
     *  @param data - The data that is equal to the element that'll be removed.
     */
    void remove(const T& data) {
        if (head->data() == data) {
            pop_front();
        } else {
            Node* element = head;
            while (element->next() != nullptr &&
                    element->next()->data() != data) {
                element = element->next();
            }
            Node* removed = element->next();
            element->next(removed->next());

            delete removed;
            --size_;
        }
    }

    //! Checks if the list is empty;
    /*!
     * @return 'true' if the list is empty and 'false' otherwise.
     */
    bool empty() const {
        return size_ == 0;
    }

    //! Checks if the list contains the given element;
    /*!
     * @return 'true' if the list have an element equals to data and 'false' otherwise.
     */
    bool contains(const T& data) const {
        Node* element = head;
        while (element->next() != nullptr) {
            if (element->data() == data) return true;
            element = element->next();
        }
        return false;
    }

    //! Finds the position of the given data;
    /*! 
     * @return The position of 'data', if the list contains it.
     */
    int find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("List is empty.");
        } else {
            Node* element = head;
            std::size_t i = 0u;
            while (element != nullptr && element->data() != data) {
                element = element->next();
                ++i;
            }
            return (int) i;
        }
    }

    //! Gets the actual size - 1 of the list;
    /*!
     * @return The first position free of the list.
     */
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

    Node* head{nullptr};
    std::size_t size_{0u};
};

#endif

