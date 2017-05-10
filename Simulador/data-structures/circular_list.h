// Copyright [2017] <Ramna Sidharta>

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>  // std::size+t
#include <stdexcept>  // C++ exceptions

//!.
template<typename T>
class CircularList {
 public:
    CircularList() {
		auto sentinel = new Node();
		sentinel->next(sentinel);
		head = sentinel;
	}

    ~CircularList() {
		clear();
		delete head;
	}

	//!.
    void clear() {
		while (!empty())
			pop_front();
	}

    //! .
	void push_back(const T& data) {
		insert(data, size_);
	}

    //! .
    void push_front(const T& data) {
		insert(data, 0);
	}

    //! .
	void insert(const T& data, std::size_t index) {
		if (index > size_) {
			throw std::out_of_range("Invalid index");
		} else {
			auto previous = head;
			for (std::size_t i = 0u; i < index; i++)
				previous = previous->next();
			previous->next(new Node(data, previous->next()));
			++size_;
		}
	}

    //! .
	void insert_sorted(const T& data) {
	    if (empty() || head->next()->data() >= data) {
	    	insert(data, 0);
	    } else {
		auto previous = head->next();
		while (previous->next() != head && previous->next()->data() < data)
			previous = previous->next();
		previous->next(new Node(data, previous->next()));
		++size_;
	    }
	}

    //! .
    T& at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("List is empty.");
        } else if (index >= size_) {
            throw std::out_of_range("Invalid index.");
        } else {
            auto elementAt = head->next();
            for (std::size_t i = 0u; i < index; i++) {
                elementAt = elementAt->next();
            }
            return elementAt->data();
        }
    }

    //! .
    const T& at(std::size_t index) const {
        if (empty()) {
			throw std::out_of_range("List is empty.");
		} else if (index >= size_) {
            throw std::out_of_range("Invalid index.");
        } else {
            auto elementAt = head->next();
            for (std::size_t i = 0u; i < index; i++) {
                elementAt = elementAt->next();
            }
            return elementAt->data();
        }
    }

    //! .
    T pop(std::size_t index) {
	    if (index >= size_) {
			throw std::out_of_range("Invalid index.");
		} else {
			auto previous = head;
			for (std::size_t i = 0u; i < index; i++) {
				previous = previous->next();
			}
			auto removed_element = previous->next();
			previous->next(removed_element->next());
			T removed_data = removed_element->data();

			--size_;
			delete removed_element;
			return removed_data;
		}
	}

    //! .
    T pop_back() {
		return pop(size_ - 1);
	}

    //! .
    T pop_front() {
		return pop(0);
	}

    //! .
    void remove(const T& data) {
        auto previous = head;
        while (previous->next() != head &&
                previous->next()->data() != data) {
            previous = previous->next();
        }
        auto removed = previous->next();
        previous->next(removed->next());
        delete removed;
        --size_;
    }

    //! .
    bool empty() const {
		return size_ == 0;
	}

    //! .
    bool contains(const T& data) const {
        auto element = head;
        for (std::size_t i = 0u; i < size_; i++) {
            if (element->data() == data) return true;
            element = element->next();
        }
        return false;
    }

    //! .
    std::size_t find(const T& data) const {
        auto element = head;
        std::size_t index = 0u;
        while (index < size_ && element->next()->data() != data) {
            element = element->next();
            ++index;
        }
        return index;
    }

    //! .
    std::size_t size() const {
		return size_;
	}

 private:
	class Node {
 public:
	 	explicit Node(const T& data): data_(data) {}
	 	Node() = default;
		Node(const T& data, Node* next): data_(data), next_(next) {}

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

	Node* head{nullptr};
	std::size_t size_{0u};
};

#endif

