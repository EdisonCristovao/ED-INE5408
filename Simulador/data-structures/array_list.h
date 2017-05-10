// Copyright [2017] <Ramna Sidharta>

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

//! Implements a list (data structure) using array;
/*!
 * This data structure works just like a real 'list'. It is a list with
 * manipulable elements. You add and remove an element to any position
 */
template<typename T>
class ArrayList {
 public:
	ArrayList() = default;

	//! Constructor with a given maximum size of the list
	/*!
	 * @param max_size - Maximum size of the list
	 */
    explicit ArrayList(std::size_t max_size):
		contents(new T[max_size]), max_size_(max_size) {
	}

    //! Destroys the list
    ~ArrayList() {
		delete[] contents;
	}

	//! Clears the list
    void clear() {
		size_ = 0;
	}

	//! Adds the given data to the last position of the list
	/*!
	 * @param data - The element that will be added to the list
	 */
    void push_back(const T& data) {
		insert(data, size_);
	}

	//! Adds the given data to the first position of the list
	/*!
	 * All other elements will to the your next position
	 *
	 * @param data - The element that will be added to the list
	 */
    void push_front(const T& data) {
		insert(data, 0);
	}

	//! Adds the given data to the given position of the list
	/*!
	 * All other elements will moved to the your next position
	 *
	 * @param data - The element that will be added to the list
	 * @param index - The position that will receive 'data'
	 */
    void insert(const T& data, std::size_t index) {
		if (indexOutOfBounds(index)) {
			throw std::out_of_range("Index out of Bounds");
		} else if (full()) {
			throw std::out_of_range("List full");
		} else {
        	moveForward(index);
        	contents[index] = data;
        	size_++;
		}
	}

	//! Adds the given data to the list in order
	/*!
	 * Adds 'data' to the list before the first position that contains
	 * an element bigger than it
	 *
	 * @param data - The element that will be added to the list
	 */
    void insert_sorted(const T& data) {
		std::size_t i;
		if (full()) {
			throw std::out_of_range("List full");
		} else {
    		i = 0u;
    		while (i < size_ && data >= contents[i])
    		    i++;
    		insert(data, i);
		}
	}

	//! Removes the element at the given position of the list
	/*!
	 * All the other elements after index - back off one position
	 * 
	 * @return A referente of the element that was removed
	 */
    T pop(std::size_t index) {
		T element;
		if (empty()) {
			throw std::out_of_range("List empty");
		} else if (index >= size_) {
			throw std::out_of_range("Index out of Bounds");
		} else {
            element = contents[index];
    	    moveBackward(index);
    	    size_--;
    		return element;
		}
	}

	//! Removes the element at the last position of the list
	/*!
	 * @return A referente of the element that was removed
	 */
    T pop_back() {
	    return pop(size_ - 1);
	}

	//! Removes the element at the first position of the list
	/*!
	 * All other elements back off one position.
	 *
	 * @return A reference of the element that was removed
	 */
    T pop_front() {
		return pop(0);
	}

	//! Remove the first element of the list that is equal to the given data
	/*!
	 * All other elements after 'data' back off one position
	 *
	 * @param data - The element that is equal to that will be removed 
	 */
    void remove(const T& data) {
	   std::size_t i = 0u;
	   while (contents[i] != data)
	        i++;
	   pop(i);
	}

	//! Checks if the list is full
	/*!
	 * @return true if the list is full and false otherwise
	 */
    bool full() const {
		return (size_ == max_size_);
	}

	//! Checks if the list is empty
	/*!
	 * @return true if the list is empty and false otherwise
	 */
    bool empty() const {
		return (size_ == 0);
	}

	//! Checks if the list contains the given data
	/*!
	 * @return true if the list contains an element equals to data
	 *         and false otherwise
	 */
    bool contains(const T& data) const {
		for (std::size_t i = 0; i < size_; i++) {
			if (contents[i] == data)
				return true;
		}
		return false;
	}

	/*!
	 * If the list contains the given data, returns your position
	 *
	 * @return Position of the element equals to 'data' in the list
	 *         or last position if it element doesn't exists
	 */
    std::size_t find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("List empty");
        } else {
            for (std::size_t i = 0u; i < size_; i++) {
    			if (contents[i] == data)
    				return i;
    		}
        }
    	return size_;
	}

	//! Return the actual size of the list
	/*!
	 * @return A unsigned integer corresponding to the numbers of 
	 *         elements in the list
	 */
	std::size_t size() const {
		return size_;
	}

	//! Returns a maximum size of the list
	/*!
	 * @return A unsigned integer that corresponding to the
	 *         maximum size of the list
	 */
    std::size_t max_size() const {
		return max_size_;
	}

	//! Return the element in the given position of the list
	/*!
	 * @param index - The index to obtains its position 
 	 *
	 * @return A reference of the element at the given index
	 */
    T& at(unsigned int index) {
		if (indexOutOfBounds(index)) {
			throw std::out_of_range("Index out of bounds of list");
        } else {
		    return contents[index];
        }
	}

    //! Overloads the operator "[]"
    /*!
     * @param index - The index on the list of the element that will be 
     *                returned 
     * 
     * @return A referente to the element at the given index
     */
    T& operator[](unsigned int index) {
	    return contents[index];
	}

    //! Return the element in the given position of the list
	/*!
	 * @param index - The index to obtains its position 
 	 *
	 * @return A reference of the element at the given index
	 */
    const T& at(unsigned int index) const {
		if (indexOutOfBounds(index)) {
			throw std::out_of_range("Index out of bounds of list");
        } else {
		    return contents[index];
        }
	}

    //! Overloads the operator "[]"
    /*!
     * @param index - The index on the list of the element that will be 
     *                returned 
     * 
     * @return A referente to the element at the given index
     */
    const T& operator[](unsigned int index) const {
	    return contents[index];
	}

	//! Checks if the given index is a valid position to add an element
	/*!
	 * @param index - the number to be checked
	 *
	 * @return true if index is valid and false otherwise
	 */
	bool indexOutOfBounds(unsigned int index) const {
		return (index > size_ ||
		        (full() && index == size_));
	}

	//! Move forward all elements after the given index
	/*!
	 * @param index - The base position to which all of the 
	 * following will be moved forward
	 */
	void moveForward(std::size_t index) {
		for (std::size_t i = size_; i > index; i--) {
			contents[i] = contents[i-1];
		}
	}

	//! Move backward all elements before the given index
	/*!
	 * @param index - The base position to which previous ones 
	 *                will be moved
	 */
	void moveBackward(std::size_t index) {
		for (std::size_t i = index; i < size_ - 1; i++) {
			contents[i] = contents[i+1];
		}
	}

 private:
    T* contents{new T[DEFAULT_MAX]};
    std::size_t size_{0u};
    std::size_t max_size_{DEFAULT_MAX};

    static const auto DEFAULT_MAX = 10u;
};

#endif
