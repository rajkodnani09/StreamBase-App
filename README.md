# StreamBase-App

README

This project contains two sub-projects:-
(i) Server
(ii) Client

This implementation uses Boost C++ libraries(1.68) to create pipes and send data through the pipes.
Both the server and client use serialization to send data and/or objects to each other. 
There are two source files i.e. server.cpp and client.cpp along with four header files i.e.
session.hpp, server_session.hpp, client_session.hpp and serialization.hpp.

Session.hpp : It defines a class session which provides the necessary functionality to the server
			  and client.
Server_session.hpp : It defines the function bodies for each of the function which is publicly inherited
					 from the class Session.
Client_session.hpp : It defines the function bodies for each of the function which is publicly inherited
					 from the class Session.
Serialization.hpp : It defines a class Animal which is used for testing purposes.

This project uses two pipes for communication one for incoming data and the other for outgoing data.

When the server is running you will need to enter the names of the in_pipe and out_pipe.
For example
On server enter
P1 P2
On client enter pipe names in reverse order
P2 P1

It should display the Animal objects that are created and sent asynchronously and synchronously by both the
server and client. The order of operations is as follows:-
(i) async_read by server and async_write by client.
(ii) async_write by server and async_read by client.
(iii) sync_read by server and sync_write by client.
(iv) sync_write by server and sync_read by client.

Cmake will build the Visual Studio solution for this project which works with Visual Studio 15 2017.
You will find the solution in the build folder.
You will have to add the Boost linker library paths for both the server and client sub-projects. 
This can be done as follows:-
1. Right click the sub-project.
2. Select Properties-> Linker-> General-> Additional Library Directories.
3. Add the Boost Library path here, example mine is C:\Users\RAJKUMAR\Downloads\boost_1_68_0\stage\lib.
4. Select Apply -> OK.

Also, Cmake will by default run ALL_BUILD. To change this you will need to
1. Right click the solution in solution explorer.
2. Select Properties -> Multiple StartUp Projects.
3. Select start for server and client and leave the rest as none.
4. Select OK.

Once the solution is ready you can build the project in Visual Studio.
