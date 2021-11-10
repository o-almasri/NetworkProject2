#define WIN32_LEAN_AND_MEAN			// Strip rarely used calls

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "cAuthService.h"
#include "cAuthServer.h"
#include "sAuthRequester.h"
#include "eRequestType.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")


int main(int argc, char** argv)
{

	//Start TCP server 
	cAuthServer server = cAuthServer();
	server.Start();

	SOCKET listenSocket = server.StartListening();

	//Instantiate the chat Manager
	cAuthService authService = cAuthService();
	
	FD_SET ReadSet;
	int total;
	DWORD flags;
	DWORD RecvBytes;
	DWORD SentBytes;
	SOCKET acceptSocket = INVALID_SOCKET;
	int iResult;
	struct timeval tv;
	tv.tv_sec = 2;
	tv.tv_usec = 0;
	while (true)
	{
		
		// Initialize our read set
		FD_ZERO(&ReadSet);

		// Always look for connection attempts
		FD_SET(listenSocket, &ReadSet);

		// Set read notification for each socket.
		for (int i = 0; i < authService.GetRequests().size(); i++)
		{
			FD_SET(authService.GetRequests().at(i)->socket, &ReadSet);
		}

		// Call our select function to find the sockets that
		// require our attention
		printf("Waiting for select()...\n");
		total = select(0, &ReadSet, NULL, NULL, &tv);
		if (total == SOCKET_ERROR)
		{
			printf("select() failed with error: %d\n", WSAGetLastError());
			return 1;
		}
		else
		{
			printf("select() is successful!\n");
		}

		// #4 Check for arriving connections on the listening socket
		if (FD_ISSET(listenSocket, &ReadSet))
		{
			total--;
			acceptSocket = accept(listenSocket, NULL, NULL);
			if (acceptSocket == INVALID_SOCKET)
			{
				printf("accept() failed with error %d\n", WSAGetLastError());
				return 1;
			}
			else
			{
				iResult = ioctlsocket(acceptSocket, FIONBIO, &server.NonBlock);
				if (iResult == SOCKET_ERROR)
				{
					printf("ioctsocket() failed with error %d\n", WSAGetLastError());
				}
				else
				{
					printf("ioctlsocket() success!\n");
					//Add new connection as client 
					sAuthRequester* requester = new sAuthRequester();
					requester->socket = acceptSocket;
					printf("New client connected on socket %d\n", (int)acceptSocket);
				}
			}
		}

		// Loop through clients
		for (int i = 0; i < authService.GetRequests().size(); i++)
		{

			sAuthRequester* requester = authService.GetRequests().at(i);

			// If the ReadSet is marked for this socket, then this means data
			// is available to be read on the socket
			if (FD_ISSET(requester->socket, &ReadSet))
			{
				total--;

				DWORD Flags = 0;
				iResult = WSARecv(
					requester->socket,
					&(requester->dataBuf),
					1,
					&RecvBytes,
					&Flags,
					NULL,
					NULL
				);


				//TODO convert from binary to google protocol
				std::string request(requester->dataBuf.buf);

				if (iResult == SOCKET_ERROR)
				{
					if (WSAGetLastError() == WSAEWOULDBLOCK)
					{
						// We can ignore this, it isn't an actual error.
					}
					else
					{
						printf("WSARecv failed on socket %d with error: %d\n", (int)requester->socket, WSAGetLastError());
						authService.Disconnect(requester);
					}
				}
				else
				{
					printf("WSARecv() is OK!\n");
					if (RecvBytes == 0)
					{
						authService.Disconnect(requester);
					}
					else if (RecvBytes == SOCKET_ERROR)
					{
						printf("recv: There was an error..%d\n", WSAGetLastError());
						continue;
					}
					else
					{
						//TODO according to the message, break on which request are
						eRequestType  type = eRequestType::REGISTER;// = authService.GetRequestType(request);

						switch (type)
						{
						case eRequestType::REGISTER:
						{
							//TODO get from google protocol and convert to DTO
							sRegisterRequest rr;
							//TODO process request
							sRegisterResponse response = authService.Register(rr);
							//TODO write the result to the buffer
							//requester->dataBuf = result;
							//TODO Return the result to this requester
							server.SendResponse(requester->socket, requester->dataBuf);
							break;
						}

						case eRequestType::AUTHENTICATE:
						{
							
							//TODO get from google protocol and convert to DTO
							sLoginRequest req;
							//TODO process request
							sLoginResponse response = authService.Login(req);
							//TODO write the result to the buffer
							//requester->dataBuf = result;
							//Return the result to this requester
							server.SendResponse(requester->socket, requester->dataBuf);
							break;
						}
						default:
							break;
						}
					}
				}
			}
		}

	}


	server.Shutdown(acceptSocket);

	return 0;
}