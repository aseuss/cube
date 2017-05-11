//
// src/include/log.h
//
// Copyright 2016,2017 Andreas Seuss
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CUBE_LOG_H
#define CUBE_LOG_H

#ifdef __ANDROID__
#include <android/log.h>
//#define  TAG    "dbg"
#else
#include <iostream>
#endif

#include <sstream>
#include <ctime>
#include <chrono>

namespace c3 {

class Log : public std::ostringstream {
 public:
#ifdef __ANDROID__
  enum class Level : int {
    DEBUG = ANDROID_LOG_DEBUG,
    ERROR = ANDROID_LOG_ERROR,
    FATAL = ANDROID_LOG_FATAL,
    INFO = ANDROID_LOG_INFO,
    VERBOSE = ANDROID_LOG_VERBOSE,
    WARN = ANDROID_LOG_WARN,
  };
#else
   enum class Level : char {
     DEBUG = 'D',
     ERROR = 'E',
     FATAL = 'F',
     INFO = 'I',
     VERBOSE = 'V',
     WARN = 'W',
  };
#endif

  Log(Level level = Level::VERBOSE) : m_Level(level), m_LogTag("-") {}
  Log(std::string logTag, Level level = Level::VERBOSE) : m_Level(level), m_LogTag(logTag) {}
  Log(Log&& other) : m_Level(Level::VERBOSE), m_LogTag("-") {
    m_Level = other.m_Level;
    m_LogTag = other.m_LogTag;
    // probably not needed to copy / move anything else
  }

  ~Log() {
#ifdef __ANDROID__
    __android_log_print(static_cast<int>(m_Level), m_LogTag.c_str(), "%s", this->str().c_str());
#else
    std::stringstream out;
    if (m_HasColor && (m_Level == Level::ERROR || m_Level == Level::FATAL)) {
      // if color is supported print errors and fatal logs in red
      out << "\033[0;31m";
    } else if (m_HasColor && m_Level == Level::WARN) {
      // if color is supported print warnings in blue
      out << "\033[0;34m";
    }

    out << timeStamp(std::chrono::system_clock::now()) << " ";
    out << static_cast<char>(m_Level) << "/" << m_LogTag << ": " << this->str() << std::endl;

    if (m_HasColor &&
      (m_Level == Level::ERROR || m_Level == Level::WARN || m_Level == Level::FATAL)) {
      // if color is supported reset color parameters back to normal
      out << "\033[0m";
    }

    if (m_Level == Level::ERROR || m_Level == Level::FATAL) {
      // only print error and fatal messages to cerr
      std::cerr << out.rdbuf();
    } else {
      std::cout << out.rdbuf();
    }
#endif
  }

  static inline Log d() { return Log(Log::Level::DEBUG); }
  static inline Log d(std::string tag) { return Log(tag, Log::Level::DEBUG); }

  static inline Log e() { return Log(Log::Level::ERROR); }
  static inline Log e(std::string tag) { return Log(tag, Log::Level::ERROR); }

  static inline Log f() { return Log(Log::Level::FATAL); }
  static inline Log f(std::string tag) { return Log(tag, Log::Level::FATAL); }

  static inline Log i() { return Log(Log::Level::INFO); }
  static inline Log i(std::string tag) { return Log(tag, Log::Level::INFO); }

  static inline Log v() { return Log(Log::Level::VERBOSE); }
  static inline Log v(std::string tag) { return Log(tag, Log::Level::VERBOSE); }

  static inline Log w() { return Log(Log::Level::WARN); }
  static inline Log w(std::string tag) { return Log(tag, Log::Level::WARN); }

 private:
  template<typename T>
  static std::string timeStamp(std::chrono::time_point<T> time) {
    std::string result;

    std::time_t curr_time = T::to_time_t(time);
    char timeString[20];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", localtime(&curr_time));

    typename T::duration timeSinceEpoch = time.time_since_epoch();
    // get time value in seconds
    std::chrono::seconds seconds =
        std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);
    // subtract seconds from epoch time so that only milli-, micro- and nanoseconds remain
    timeSinceEpoch -= seconds;
    // get the remaining milliseconds
    std::chrono::milliseconds milliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);

    std::ostringstream ostream;
    ostream << '[' << timeString << ":" << milliseconds.count() << "]";
    result = ostream.str();
    return result;
  }

#ifndef __ANDROID__
  static const bool m_HasColor;
#endif

  Level m_Level;
  std::string m_LogTag;
};

} // end of namespace c3

#endif //CUBE_LOG_H

