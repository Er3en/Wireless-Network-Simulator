#ifndef EVENT_H_
#define EVENT_H_
#include <functional>
#include <vector>
#include <queue>

class Network;

class Event
{
public:
	typedef std::priority_queue<Event*, std::vector<Event*>, std::function<bool(Event*, Event*)>> EventList;
	Event(size_t time, Network* network_);

	virtual void Execute() = 0;

	size_t get_time() { return time_; }
protected:
	size_t time_;
	Network* network_ = nullptr;

};

#endif
