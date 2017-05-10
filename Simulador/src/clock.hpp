#ifndef CLOCK_HPP
#define CLOCK_HPP

//!
 /*
  *
  */
class Clock {
  private:
   int time_{0};
   int end_time_{0};

  public:
   	Clock();
    Clock(int time);
    ~Clock();
    int time();
    void time(int time);
    int end_time();
    void end_time(int time);

    void cont_time();

    bool end();

};

Clock::Clock() {}

Clock::Clock(int time): end_time_(time) {}

Clock::~Clock() {}

int Clock::time() {
  return time_;
}

void Clock::time(int time) {
  time_ = time;
}

int Clock::end_time() {
  return end_time_;
}

void Clock::end_time(int time) {
  end_time_ = time;
}

void Clock::cont_time() {
  time_++;
}

bool Clock::end() {
	return time_ == end_time_;
}

#endif  // CLOCK_HPP
