/*
 * Copyright 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NATIVEOBOE_FIFOCONTROLLERINDIRECT_H
#define NATIVEOBOE_FIFOCONTROLLERINDIRECT_H

#include "FifoControllerBase.h"
#include <atomic>

namespace oboe {

/**
 * A FifoControllerBase with counters external to the class.
 */
class FifoControllerIndirect : public FifoControllerBase {

public:
    FifoControllerIndirect(uint32_t bufferSize,
                           uint32_t threshold,
                           int64_t * readCounterAddress,
                           int64_t * writeCounterAddress);
    virtual ~FifoControllerIndirect();

    // TODO review use of memory barriers, probably incorrect
    virtual uint64_t getReadCounter() override {
        return mReadCounterAddress->load(std::memory_order_acquire);
    }
    virtual void setReadCounter(uint64_t n) override {
        mReadCounterAddress->store(n, std::memory_order_release);
    }
    virtual uint64_t getWriteCounter() override {
        return mWriteCounterAddress->load(std::memory_order_acquire);
    }
    virtual void setWriteCounter(uint64_t n) override {
        mWriteCounterAddress->store(n, std::memory_order_release);
    }

private:

    std::atomic<uint64_t> * mReadCounterAddress;
    std::atomic<uint64_t> * mWriteCounterAddress;

};

} // namespace oboe

#endif //NATIVEOBOE_FIFOCONTROLLERINDIRECT_H
