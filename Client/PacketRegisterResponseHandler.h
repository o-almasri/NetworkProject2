#include "IPacketHandler.h"

class PacketRegisterResponseHandler : public IPacketHandler
{
public:
	virtual void HandleOnClient(Client& client, const SOCKET& serverSocket);
};