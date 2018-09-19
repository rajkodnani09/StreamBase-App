
#define _WIN32_WINNT 0x0501
#include <boost/date_time/gregorian/greg_month.hpp>
#include <boost/date_time/gregorian_calendar.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include <functional>
#include <thread>
#include <boost/system/error_code.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/windows/overlapped_ptr.hpp>
#include <boost/bind.hpp>
#include <tchar.h>
#include <boost/asio/windows/stream_handle.hpp>
#include <windows.h>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <memory>
#include <vector>
#include <boost/process/async_pipe.hpp>
#include "client_session.hpp"
#include "serialization.hpp"
#include <boost/iostreams/device/file_descriptor.hpp>

namespace bp = boost::process;

class Client {
public:

	void openSession(const std::string in_pipe, const std::string out_pipe) {
		boost::asio::io_service curr_ios;
		boost::iostreams::file_descriptor FD1(in_pipe);
		auto read_stream = std::make_shared<boost::asio::windows::stream_handle>(curr_ios, FD1.handle());
		boost::iostreams::file_descriptor FD2(out_pipe);
		auto write_stream = std::make_shared<boost::asio::windows::stream_handle>(curr_ios, FD2.handle());

		auto *session = new ClientSession(read_stream, write_stream);
		std::cout << "created session \n";

		std::string Str;
		Str.resize(4096);
		Animal X("Monkey", 4);
		std::ostringstream SS;
		boost::archive::text_oarchive OA{ SS };
		OA << X;
		Str.clear();
		Str = SS.str();
		std::cout << SS.str() << std::endl;
		session->async_write(boost::asio::buffer(Str));
		curr_ios.run();
		curr_ios.reset();
		Str.clear();


		Str.resize(4096);
		session->async_read(boost::asio::mutable_buffer(const_cast<char *>(Str.data()), 4096));
		curr_ios.run();
		curr_ios.reset();

		std::istringstream SS1(Str);
		boost::archive::text_iarchive IA1{ SS1 };
		Animal Y;
		IA1 >> Y;
		std::cout << "Name: " << Y.name() << std::endl;
		std::cout << "Number of legs: " << Y.legs() << std::endl;
		Str.clear();


		Animal Z("Penguin", 2);
		std::ostringstream SS2;
		boost::archive::text_oarchive OA2{ SS2 };
		OA2 << Z;
		Str.clear();
		Str = SS2.str();
		std::cout << SS2.str() << std::endl;
		session->sync_write(boost::asio::buffer(Str));
		Str.clear();

		Str.resize(4096);
		session->sync_read(boost::asio::mutable_buffer(const_cast<char *>(Str.data()), 4096));

		std::istringstream SS3(Str);
		boost::archive::text_iarchive IA2{ SS3 };
		Animal A;
		IA2 >> A;
		std::cout << "Name: " << A.name() << std::endl;
		std::cout << "Number of legs: " << A.legs() << std::endl;
		Str.clear();

		delete session;
	}

	void run() {
		std::string line;
		std::getline(std::cin, line);
		std::istringstream stream(line);
		std::string pipe_1, pipe_2;
		stream >> pipe_1 >> pipe_2;
		std::cout << pipe_1 << "  " << pipe_2 << std::endl;
		openSession(pipe_1, pipe_2);
	}
};

int main() {
	Client client;
	client.run();
	return 0;
}
/*
int main() {
  boost::asio::io_service ios;
  //std::vector<char> Buf;
  std::string Str = "passing this string";
  boost::iostreams::file_descriptor FD("mypipe1");
  boost::asio::posix::stream_descriptor fifo(ios, FD.handle());
  boost::asio::async_write(fifo, boost::asio::buffer(Str),
						   [&](const boost::system::error_code& error, std::size_t bytes_transferred) {});
  ios.run();
  std::cout << Str << std::endl;

  return 0;
}

int main() {
  boost::asio::io_service ios;
  //std::vector<char> Buf;
  std::string Str = "passing this string";
  boost::iostreams::file_descriptor FD("mypipe1");
  boost::asio::posix::stream_descriptor fifo(ios, FD.handle());
  boost::asio::write(fifo, boost::asio::buffer(Str));
  std::cout << Str << std::endl;

  return 0;
  }*/

