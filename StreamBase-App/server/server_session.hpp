
#ifndef __SERVER_SESSION__
#define __SERVER_SESSION__

#include "session.hpp"

class ServerSession : public Session {
public:
  ServerSession(std::shared_ptr<boost::process::async_pipe> read_pipe,
                std::shared_ptr<boost::process::async_pipe> write_pipe) :
    read_pipe(read_pipe), write_pipe(write_pipe) {}

  ~ServerSession() = default;
  
  virtual void async_read(boost::asio::mutable_buffer buffer) {
    read_pipe->
      async_read_some(buffer,
                      [&](const boost::system::error_code &error,
                          std::size_t bytes_transferred) {
                        if (error) {
                          std::cout << "Session error\n";
                          delete this;
                          return;
                        }

                        std::cout << boost::asio::buffer_cast<char *>(buffer) << std::endl;
                      });
  }

  virtual void sync_read(boost::asio::mutable_buffer buffer) {
    read_pipe->read_some(buffer);
    std::cout << boost::asio::buffer_cast<char *>(buffer) << std::endl;
  }

  virtual void async_write(boost::asio::mutable_buffer buffer) {
    write_pipe->
      async_write_some(buffer,
                      [&](const boost::system::error_code &error,
                          std::size_t bytes_transferred) {
                        if (error) {
                          std::cout << "Session error\n";
                          delete this;
                          return;
                        }

                        std::cout << boost::asio::buffer_cast<char *>(buffer) << std::endl;
                      });
  }

  virtual void sync_write(boost::asio::mutable_buffer buffer) {
    write_pipe->write_some(buffer);
    std::cout << boost::asio::buffer_cast<char *>(buffer) << std::endl;
  }


private:
  std::shared_ptr<boost::process::async_pipe> read_pipe;
  std::shared_ptr<boost::process::async_pipe> write_pipe;

};

#endif
