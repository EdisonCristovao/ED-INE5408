#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
class ArrayQueue {
 public:
    ArrayQueue() {
      max_size_ = DEFAULT_SIZE;
      contents = new T[max_size_];
    }

    explicit ArrayQueue(std::size_t max) {
      max_size_ = max;
      contents = new T[max_size_];
    }

    ~ArrayQueue();

    void enqueue(const T& data) {
      if (full()) {
        std::out_of_range("Fila cheia");
      } else {
        contents[++size_] = data;
      }
    }

    T dequeue(){
      if (empty()) {
        std::out_of_range("Fila vazia");
      } else {
        T data = contents[0];
        size_ --;
        move_foward();
        return data;
      }
    }

    T& back(){
      return contents[size_];
    }

    void clear(){
      size_ = -1;
    }

    std::size_t size(){
      return (size_+1);
    }

    std::size_t max_size(){
      return max_size_;
    }

    bool empty(){
      return (size_ == -1);
    }

    bool full(){
      return (size_ == max_size_-1);
    }

 private:
    void move_foward(){
      for (auto i = 0; i != size_+1; i++){
        data[i] = data[i+1];
      }
    }

    T* contents;
    int size_ {-1};
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures
#endif
