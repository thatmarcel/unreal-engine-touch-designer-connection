#pragma once
#include "Sockets.h"

class TouchDesignerConnectionSocket {
private:
	FSocket* Socket = nullptr;
public:
	bool Open(unsigned short local_port);
	bool Close();
	bool Receive(
		char* buffer,
		int buffer_length,
		const FString* sender_ip_address,
		unsigned short sender_port
	) const;
	bool Send(
		const char* buffer,
		int buffer_length,
		const FString* destination_ip_address,
		unsigned short destination_port
	) const;
};
