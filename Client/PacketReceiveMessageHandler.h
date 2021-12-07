#include "IPacketHandler.h"

class PacketReceiveMessageHandler : public IPacketHandler
{
public:
	virtual void HandleOnClient(Client& client, const SOCKET& serverSocket);
};