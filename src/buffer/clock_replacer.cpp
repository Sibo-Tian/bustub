//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// clock_replacer.cpp
//
// Identification: src/buffer/clock_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/clock_replacer.h"

namespace bustub {

ClockReplacer::ClockReplacer(size_t num_pages) \
    :circular_{num_pages,ClockReplacer::Status::EMPTY},hand_{0},capacity_{num_pages}{
        circular_.reserve(num_pages);// vector initialize, :: 's syntax
    }

ClockReplacer::~ClockReplacer() = default;

auto ClockReplacer::Victim(frame_id_t *frame_id) -> bool {
    const std::lock_guard<mutex_t> guard(mutex_);

    size_t unempty_count = 0;
    frame_id_t victim_frame_id = 0;

    for(size_t i=1,idx = (hand_+i)%capacity_;i<capacity_+1;i++,idx=(hand_+i)%capacity_){
        if(circular_[idx]== ClockReplacer::Status::ACCESSED){
            unempty_count++;
            circular_[idx]==ClockReplacer::Status::UNTOUCHED;
        }
        else if(circular_[idx]==ClockReplacer::Status::UNTOUCHED){
            unempty_count++;
            victim_frame_id = victim_frame_id != 0?victim_frame_id:idx;
        }
    }
    if(unempty_count== 0U){
        frame_id = nullptr;
        return false;
    }
    if(victim_frame_id == 0){
        for(size_t i=1,idx = (hand_+i)%capacity_;i<capacity_+1;i++,idx = (hand_+i)%capacity_){
            if(circular_[idx] == ClockReplacer::Status::UNTOUCHED){
                victim_frame_id = idx;
                break;
            }
        }
    }
    *frame_id = victim_frame_id;
    hand_ = victim_frame_id;
    circular_[victim_frame_id&capacity_] = ClockReplacer::Status::EMPTY;
    return true;
}
void ClockReplacer::Pin(frame_id_t frame_id) {
    const std::
}

void ClockReplacer::Unpin(frame_id_t frame_id) {}

auto ClockReplacer::Size() -> size_t { return 0; }

}  // namespace bustub
