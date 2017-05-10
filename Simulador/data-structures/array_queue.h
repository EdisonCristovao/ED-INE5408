// Copyright [2017] Ramna Sidharta

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

//! Implements a queue (data structure) using array:
/*!
 * This data structure works just like a real 'queue', you add elements to
 * the back of the queue (enqueue), and you removes from the front (dequeue).
 * It follows the 'FIFO' (first in, first out) principle.
 */
template<typename T>
class ArrayQueue {
 public:
    ArrayQueue() = default;

	//! Constructor with a given maximum size of the queue
	/*!
	 * @param max Maximum size of the queue  
	 */
    explicit ArrayQueue(std::size_t max):
        contents(new T[max]), max_size_(max) { }

	/*!
	 * Destructor method: free queue of the memory
	 */
	virtual ~ArrayQueue() {
		delete[] contents;
	}

    //! Adds an element in the queue
	/*!
	 * Adds 'data' to the firts free position of
	 * the queue
	 * 
	 * @param data The element that will be added 
	 */
    void enqueue(const T& data) {
		if (full()) {
			throw std::out_of_range("Queue full");
		}
		contents[size_++] = data;
	}

	//! Removes a element of the queue
	/*!
	 * The firt element of the queue is removed
	 * 
	 * @return the element that was removed
	 */
    T dequeue() {
		if (empty()) {
			throw std::out_of_range("Queue empty");
		}
		T save = contents[0];
		for (std::size_t i = 0; i < size_; i++) {
			contents[i] = contents[i+1];
		}
		size_--;
		return save;
	}

	/*!
	 * @return a reference of the last element of the queue
	 */
    T& back() {
        if (empty()) {
            throw  std::out_of_range("Queue empty");
        }
        return contents[size_-1];
	}

	/*!
	 * Clears the queue 
	 */
    void clear() {
		size_ = 0;
	}

	/*!
	 * @return a unsigned integer that corresponding to the 
	 *         actual size of the queue
	 */
    std::size_t size() {
		return size_;
	}

	/*!
	 * @return the maximum size of the queue
	 */
    std::size_t max_size() {
		return max_size_;
	}

	/*!
	 * @return 'true' if the queue is empty and 'false' otherwise
	 */
    bool empty() {
		return (size_ == 0);
	}

	/*!
	 * @return 'true' if the queue is full and 'false' otherwise
	 */
    bool full() {
		return (size_ == max_size_);
	}

 private:
    T* contents = new T[DEFAULT_SIZE];
    std::size_t size_ = 0;
    std::size_t max_size_ = DEFAULT_SIZE;

    static const auto DEFAULT_SIZE = 10u;
};


#endif

