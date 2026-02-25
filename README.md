# Embedded Developer Trial Day

Welcome, Marcel to your trial work day! This assignment is designed to evaluate your skills in embedded systems development, particularly in C/C++ programming.

## Overview

You are provided with a ring buffer implementation in C, which is wrapped in a C++ class. The ring buffer is part of a larger project running on an ESP32. Your task is to review, fix (if necessary), improve, and integrate the module.

## Objectives

The trial day is structured into several steps:

1. **Review the Pull Request (1h):**

   - Analyze the existing pull request on the [repository](https://github.com/hirtfre/ge-trial-ring-buffer)
   - Identify and document any issues, inconsistencies, or areas for improvement in the code
   - The current implementation only supports `uint16_t`, this is a technical debt of the original author which can be ignored for the review
   - Discuss your findings with your team lead

2. **Fix identified issues (1h):**

   - Implement fixes and improvement for the issues you found during the code review (if any)
   - Complete the Pull Request

3. **Eliminate technical debt (1h, optional):**

   - Eliminate the technical debt of the original author
   - Change the Ring Buffer so that it supports `uint8_t`, `uint16_t`, `uint32_t` and `uint64_t`, this may include changes to `RingBuffer.cpp` (see @todo)
   - Create a feature branch `feature/technical-debt` to work in
   - Try applying the TDD principles for your changes
   - Create a Pull Request into the `main` branch and inform your team lead
   - _Bonus_ Draw an UML class diagram of the RingBuffer module and its dependencies (`doc/diagram/RingBuffer.uxf`)

4. **Integrate into Executable (1h):**

   - Create a feature branch `feature/ring-buffer` of the [executable](https://github.com/hirtfre/ge-trial-executable)
   - Integrate the Ring Buffer into the [executable](https://github.com/hirtfre/ge-trial-executable)
   - Test the executable on the target system
   - Change `main\app_main.cpp` so that:
     - Random values get added to a Ring Buffer every 500 ms
     - Content of the Ring Buffer gets logged every 1200 ms
   - Use the task interface (timed task) of `AbstractionLayer/Task` for scheduling and `Trace` for logging

## Guidelines and Constraints

1. **Do Not Modify the C++ Wrapper Interface:**

   - The C++ class that wraps the ring buffer defines the intent of the software architect and must not be changed

2. **Consider Embedded System constraints:**

   - Pay special attention to memory management
   - Ensure that your code is efficient in terms of both time and space complexity

3. **Code Quality:**

   - Write clean, readable, and maintainable code

## Getting Started

### Repository Access

You have access to two GitHub repositories:

1. **Ring Buffer Repository:**

   - Contains the ring buffer implementation and a pull request that you need to review.
   - Repository URL: https://github.com/hirtfre/ge-trial-ring-buffer

2. **ESP32 Executable Repository:**

   - Contains the executable project that uses the ring buffer as a submodule
   - Repository URL: https://github.com/hirtfre/ge-trial-executable

### Cloning the Repositories

1. **Clone the Ring Buffer Repository:**

```bash
git clone https://github.com/hirtfre/ge-trial-ring-buffer.git
cd ge-trial-ring-buffer
git submodule update --init
```

2. **Clone the ESP32 Executable Repository:**

```bash
git clone https://github.com/hirtfre/ge-trial-executable.git
cd ge-trial-executable
git submodule update --init
```

## Additional Notes

1. **Ask Questions:**

   - If anything is unclear, don't hesitate to ask for clarification

2. **Time Management:**

   - Manage your time effectively to complete all non-optional tasks within the trial day

We look forward to reviewing your work. Good luck!

# RingBuffer

## Overview

The `RingBuffer` library is a C++ implementation of a ring buffer (circular buffer) designed to work with any integer type. It allows efficient storage and retrieval of data in a fixed-size buffer. The buffer automatically wraps around when the end is reached, making it ideal for applications like real-time data streams, buffering I/O, or managing finite data streams.

## Usage

### Basic Example

Below is a simple example of how to use the `RingBuffer` with `uint16_t` as the data type.

```cpp
#include <RingBuffer/Factory.h>
#include <Trace/ITrace.h>

static constexpr const char *moduleName = "main";

extern "C" void app_main()
{
    auto *buffer = RingBuffer::Factory::Create(sizeof(uint16_t));

    if (buffer != nullptr)
    {
        uint16_t value = 42;

        // Add an element to the buffer
        (void)buffer->Add(value);

        // Check if the buffer is not empty
        if (!buffer->IsEmpty())
        {
            buffer->Remove(value);

            // Do something with the value
            Trace::Log(moduleName, Trace::Level::Info, "Value = %d", value); 
        }
    }
}

```
