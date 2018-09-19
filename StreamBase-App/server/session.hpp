
#ifndef __SESSION__
#define __SESSION__

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <memory>
#include <vector>
#include <boost/process/async_pipe.hpp>
#include <iostream>
#include <sstream>

// Class to define async and sync read and writes for both the client and the server.
class Session {
public:
  virtual void async_read(boost::asio::mutable_buffer buffer) = 0;
  virtual void sync_read(boost::asio::mutable_buffer buffer) = 0;
  virtual void async_write(boost::asio::mutable_buffer buffer) = 0;
  virtual void sync_write(boost::asio::mutable_buffer buffer) = 0;
  virtual ~Session() = default;
};

#endif
