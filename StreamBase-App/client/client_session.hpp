#ifndef __CLIENT_SESSION__
#define __CLIENT_SESSION__

#include "session.hpp"

class ClientSession : public Session {
public:
  ClientSession(std::shared_ptr<boost::asio::windows::stream_handle> read_stream,
                std::shared_ptr<boost::asio::windows::stream_handle> write_stream) :
    read_stream(read_stream), write_stream(write_stream) {}

  ~ClientSession() = default;

  virtual void async_read(boost::asio::mutable_buffer buffer) {
    read_stream->async_read_some(buffer,
                            [&](const boost::system::error_code &error,
                                std::size_t bytes_transferred) {
                              if(error) {
                                std::cout << "Session error\n";
                                delete this;
                                return;
                              }

                              std::cout << boost::asio::buffer_cast<char *>(buffer) << std::endl;
                      });
  }

  virtual void sync_read(boost::asio::mutable_buffer buffer) {
    read_stream->read_some(buffer);
    std::cout << boost::asio::buffer_cast<char *>(buffer) << std::endl;
  }

  virtual void async_write(boost::asio::mutable_buffer buffer) {
    write_stream->async_write_some(buffer,
                            [&](const boost::system::error_code &error,
                                std::size_t bytes_transferred) {
                              if(error) {
                                std::cout << "Session error\n";
                                delete this;
                                return;
                              }

                              std::cout << boost::asio::buffer_cast<char *>(buffer) << std::endl;
                      });
  }

  virtual void sync_write(boost::asio::mutable_buffer buffer) {
    write_stream->write_some(buffer);    
    std::cout << boost::asio::buffer_cast<char *>(buffer) << std::endl;
  }

private:
  std::shared_ptr<boost::asio::windows::stream_handle> read_stream;
  std::shared_ptr<boost::asio::windows::stream_handle> write_stream;
};

#endif
