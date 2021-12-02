#include "IPacketHandler.h"

class PacketJoinRoomHandler : public IPacketHandler
{
public:
	virtual void HandleOnClient(Client& client, const SOCKET& serverSocket);	
};