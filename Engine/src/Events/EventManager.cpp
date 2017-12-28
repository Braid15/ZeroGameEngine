#include "EventManager.h"

namespace ZeroEngine {

    //
    // BaseEventManager
    //

    BaseEventManager::BaseEventManager(const char* name) {
        _active_queue = 0;
        _name = name;
    }

    bool BaseEventManager::register_listener(const EventListenerDelegate& event_delegate, const EventType& type) {
        bool success = true;
        EventListenerList& listener_list = _listener_map[type];
        for (auto iter = listener_list.begin(); iter != listener_list.end(); ++iter) {
            if (event_delegate == (*iter)) {
                std::cout << "Attempting to double register delegate. BaseEventManager::register_listener\n";
                success = false;
                break;
            }
        }
        listener_list.push_back(event_delegate);
        return success;
    }

    bool BaseEventManager::unregister_listener(const EventListenerDelegate& event_delegate, const EventType& type) {
        bool success = false;
        auto iter = _listener_map.find(type);
        if (iter != _listener_map.end()) {
            EventListenerList& listener_list = iter->second;
            for (auto it = listener_list.begin(); it != listener_list.end(); ++it) {
                if (event_delegate == (*it)) {
                    listener_list.erase(it);
                    success = true;
                    break;
                }
            }
        }
        return success;
    }

    bool BaseEventManager::trigger_event(const IEventDataPtr& event_data) const {
        bool success = false;
        auto iter = _listener_map.find(event_data->get_event_type());

        if (iter != _listener_map.end()) {
            const EventListenerList& listener_list = iter->second;
            for (EventListenerList::const_iterator it = listener_list.begin(); it != listener_list.end(); ++it) {
                EventListenerDelegate listener = (*it);
                listener(event_data);
                success = true;
            }
        }

        return success;
    }

    bool BaseEventManager::abort_event(const EventType& type, bool all) {
        assert(_active_queue >= 0);
        assert(_active_queue < EVENT_MANAGER_QUEUE_COUNT);

        bool success = false;
        auto iter = _listener_map.find(type);

        if (iter != _listener_map.end()) {
            EventQueue& queue = _event_queues[_active_queue];
            auto it = queue.begin();

            while (it != queue.end()) {
                auto this_iter = it;
                ++it;
                if ((*this_iter)->get_event_type()) {
                    queue.erase(this_iter);
                    success = true;
                    if (!all) {
                        break;
                    }
                }
            }
        }

        return success;
    }

    bool BaseEventManager::queue_event(const IEventDataPtr& event_data) {
        assert(_active_queue >= 0);
        assert(_active_queue < EVENT_MANAGER_QUEUE_COUNT);

        bool success = false;
        auto iter = _listener_map.find(event_data->get_event_type());

        if (iter != _listener_map.end()) {
            _event_queues[_active_queue].push_back(event_data);
            success = true;
        }

        return success;
    }

    bool BaseEventManager::update(uint32 max_milliseconds) {
        Tick current_time = Game::get_ticks();
        Tick max_time = (max_milliseconds == MAX_MILLISECONDS) ? MAX_MILLISECONDS
            : current_time + max_milliseconds;

        int32 queue_to_process = _active_queue;
        _active_queue = (_active_queue + 1) % EVENT_MANAGER_QUEUE_COUNT;
        _event_queues[_active_queue].clear();

        while (!_event_queues[queue_to_process].empty()) {
            // Pop first event
            IEventDataPtr event_data = _event_queues[queue_to_process].front();
            _event_queues[queue_to_process].pop_front();

            const EventType& type = event_data->get_event_type();

            auto iter = _listener_map.find(type);
            if (iter != _listener_map.end()) {
                const EventListenerList& listener_list = iter->second;

                for (auto it = listener_list.begin(); it != listener_list.end(); ++it) {
                    EventListenerDelegate listener = (*it);
                    listener(event_data);
                }
            }

            current_time = Game::get_ticks();
            if (max_milliseconds != MAX_MILLISECONDS && current_time >= max_time) {
                std::cout << "Aborting event processing. BaseEventManager::update\n";
                break;
            }
        }

        bool queue_flushed = _event_queues[queue_to_process].empty();

        // If queue is not flushed add the remaining events to the next queue
        if (!queue_flushed) {
            while (!_event_queues[queue_to_process].empty()) {
                // Pop back to presever the order at which the events were queued
                IEventDataPtr event_data = _event_queues[queue_to_process].back();
                _event_queues[queue_to_process].pop_back();
                _event_queues[_active_queue].push_front(event_data);
            }
        }

        return queue_flushed;
    }


    //
    // ZeroEventManager
    //

    BaseEventManager* ZeroEventManager::_event_manager = nullptr;

    ZeroEventManager::~ZeroEventManager() {
    }

    void ZeroEventManager::initialize() {
        if (_event_manager == nullptr) { 
            _event_manager = zero_new ZeroEventManager();
        }
    }

    bool ZeroEventManager::register_listener(const EventListenerDelegate& delegate, const EventType& type) {
        return _event_manager->register_listener(delegate, type);
    }

    bool ZeroEventManager::unregister_listener(const EventListenerDelegate& delegate, const EventType& type) {
        return _event_manager->unregister_listener(delegate, type);
    }

    bool ZeroEventManager::trigger_event(const IEventDataPtr& event_data) {
        return _event_manager->trigger_event(event_data);
    }

    bool ZeroEventManager::abort_event(const EventType& type, bool all) {
        return _event_manager->abort_event(type, all);
    }

    bool ZeroEventManager::queue_event(const IEventDataPtr& event_data) {
        return _event_manager->queue_event(event_data);
    }

    bool ZeroEventManager::update(uint32 max_milliseconds) {
        return _event_manager->update(max_milliseconds);
    }

    const char* ZeroEventManager::get_name() {
        return _event_manager->get_name();
    }

    StringRepr ZeroEventManager::to_string() {
        return _event_manager->to_string();
    }

    void ZeroEventManager::shutdown() {
        zero_delete(_event_manager);
    }
}