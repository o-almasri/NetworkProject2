#include "IPacketHandler.h"

class PacketLeaveRoomHandler : public IPacketHandler
{
public:
	virtual void HandleOnClient(Client& client, const SOCKET& serverSocket);
};