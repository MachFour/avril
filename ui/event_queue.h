// Copyright 2011 Olivier Gillet.
//
// Author: Olivier Gillet (pichenettes@mutable-instruments.net)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Event queue.

#ifndef AVRLIB_UI_EVENT_QUEUE_H_
#define AVRLIB_UI_EVENT_QUEUE_H_

#include "avrlib/base.h"
#include "avrlib/op.h"
#include "avrlib/ring_buffer.h"
#include "avrlib/time.h"

namespace avrlib {

enum ControlType {
  CONTROL_POT = 0,
  CONTROL_ENCODER = 1,
  CONTROL_ENCODER_CLICK = 2,
  CONTROL_SWITCH = 3
};

struct Event {
  uint8_t control_type;
  uint8_t control_id;
  uint8_t value;
};

template<uint8_t size = 32>
class EventQueue {
 public:
  enum {
    buffer_size = size,
    data_size = 16,
  };
  using Value = uint16_t;
  using Me = EventQueue<size>;
  using Events = RingBuffer<Me>;

  static void Flush() {
    Events::Flush();
  };
  
  static void AddEvent(uint8_t control_type, uint8_t id, uint8_t data) {
    Word v;
    v.bytes[0] = (U8ShiftLeft4(control_type) << 2u) | (id & 0x3fu);
    v.bytes[1] = data;
    Events::Overwrite(v.value);
  }
  
  static uint8_t available() {
    return Events::readable();
  }
  
  static uint16_t idle_time() {
    uint32_t now = milliseconds();
    return static_cast<uint16_t>(now - last_event_time_) >> 8u;
  }
  
  static uint16_t idle_time_ms() {
    uint32_t now = milliseconds();
    return static_cast<uint16_t>(now - last_event_time_);
  }
  
  static void Touch() {
    last_event_time_ = milliseconds();
  }
  
  static Event PullEvent() {
    Event e;
    Word v;
    v.value = Events::ImmediateRead();
    e.control_type = U8ShiftRight4(v.bytes[0]) >> 2;
    e.control_id = v.bytes[0] & 0x3f;
    e.value = v.bytes[1];
    return e;
  }
  
 private:
  static uint32_t last_event_time_;
};

/* static */
//template<uint8_t size>
//RingBuffer<EventQueue<size>> EventQueue<size>::events_;

/* static */
template<uint8_t size>
uint32_t EventQueue<size>::last_event_time_;

}  // namespace avrlib

#endif  // AVRLIB_UI_EVENT_QUEUE_H_
