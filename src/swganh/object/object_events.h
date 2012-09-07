// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "swganh/event_dispatcher.h"
#include "object.h"

namespace swganh {
namespace object {

struct ControllerEvent : swganh::BaseEvent
{
    ControllerEvent(swganh::EventType type, std::shared_ptr<swganh::object::Object> object_, std::shared_ptr<swganh::object::ObjectController> controller_)
        : BaseEvent(type)
        , object(object_)
        , controller(controller_)
    {}
    std::shared_ptr<swganh::object::Object> object;
    std::shared_ptr<swganh::object::ObjectController> controller;
};

struct ObserverEvent : swganh::BaseEvent
{
	ObserverEvent(swganh::EventType type, std::shared_ptr<swganh::object::Object> object_, std::shared_ptr<swganh::observer::ObserverInterface> observer_)
        : BaseEvent(type)
        , object(object_)
        , observer(observer_)
    {}
    std::shared_ptr<swganh::object::Object> object;
    std::shared_ptr<swganh::observer::ObserverInterface> observer;
};
}} // swganh::object