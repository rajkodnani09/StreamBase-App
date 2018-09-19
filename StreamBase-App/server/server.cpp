#define _WIN32_WINNT 0x0501
#include "server_session.hpp"
#include "serialization.hpp"
#include <thread>
namespace bp = boost::process;

void print() {
  std::cout << "Waiting for async operation\n";
}

class Server {
public:
  

  void openSession(const std::string in_pipe, const std::string out_pipe) {
    boost::asio::io_service curr_ios;
    auto curr_in_pipe = std::make_shared<bp::async_pipe>(curr_ios, in_pipe);
    std::cout << "create in pipe : " << in_pipe << "\n";
    auto curr_out_pipe = std::make_shared<bp::async_pipe>(curr_ios, out_pipe);
        std::cout << "create out pipe : " << out_pipe << "\n";
    auto *session = new ServerSession(curr_in_pipe, curr_out_pipe);
    std::cout << "created session \n";

    std::string Str;
    Str.resize(4096);
    session->async_read(boost::asio::mutable_buffer(const_cast<char *>(Str.data()), 4096));
    curr_ios.run();
    curr_ios.reset();
    
    std::istringstream SS(Str);
    boost::archive::text_iarchive IA{SS};
    Animal X;
    IA >> X;
    std::cout << "Name: " << X.name() << std::endl;
    std::cout << "Number of legs: " << X.legs() << std::endl;
    Str.clear();


    Animal Y("Sparrow", 2);
    std::ostringstream SS1;
    boost::archive::text_oarchive OA1{SS1};
    OA1 << Y;
    Str.clear();
    Str = SS1.str();
    std::cout << SS1.str() << std::endl;
    session->async_write(boost::asio::buffer(Str));

    curr_ios.run();
    curr_ios.reset();
    Str.clear();

    Str.resize(4096);
    session->sync_read(boost::asio::mutable_buffer(const_cast<char *>(Str.data()), 4096));
    std::istringstream SS2(Str);
    boost::archive::text_iarchive IA2{SS2};
    Animal Z;
    IA2 >> Z;
    std::cout << "Name: " << Z.name() << std::endl;
    std::cout << "Number of legs: " << Z.legs() << std::endl;
    Str.clear();

    Animal A("Crow", 2);
    std::ostringstream SS3;
    boost::archive::text_oarchive OA2{SS3};
    OA2 << A;
    Str.clear();
    Str = SS3.str();
    std::cout << SS3.str() << std::endl;
    session->sync_write(boost::asio::buffer(Str));
    Str.clear();

    delete session;
  }

  void run() {
    for (;;) {
      std::string line;
      std::getline(std::cin, line);
      if (line == "end")
        break;

      std::istringstream stream(line);
      std::string pipe_1, pipe_2;
      stream >> pipe_1 >> pipe_2;
      std::cout << pipe_1 << "  " << pipe_2 << std::endl;
      openSession(pipe_1, pipe_2);
    }
  }

};

int main() {
  Server server;
  server.run();
  return 0;
}

/*int main() {
  boost::asio::io_service ios;
  //std::vector<char> Buf;
  std::string Str;
  Str.resize(4096);
  bp::async_pipe ap(ios, "mypipe1");
  ap.async_read_some(boost::asio::mutable_buffer(const_cast<char *>(Str.data()), 4096),
                     [&](const boost::system::error_code& error, std::size_t bytes_transferred) {});
  ios.run();
  std::cout << Str << std::endl;
  ap.close();
  
  return 0;
}

int main() {
  boost::asio::io_service ios;
  //std::vector<char> Buf;
  std::string Str;
  Str.resize(4096);
  bp::async_pipe ap(ios, "mypipe1");
  ap.read_some(boost::asio::mutable_buffer(const_cast<char *>(Str.data()), 4096));
  std::cout << Str << std::endl;
  ap.close();
  
  return 0;
  }*/
