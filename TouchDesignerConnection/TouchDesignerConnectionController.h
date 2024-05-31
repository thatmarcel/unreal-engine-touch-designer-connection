#pragma once
#include "TouchDesignerConnectionSocket.h"

class TouchDesignerConnectionController {
private:
	TouchDesignerConnectionSocket* Socket;
	const FString* Remote_IP_Address;
	unsigned short Remote_Port;
public:
	TouchDesignerConnectionController(unsigned short local_port, const FString* remote_ip_address, unsigned short remote_port);

	bool SendValue(const char* value_name, unsigned char value_name_length, double value) const;
	bool ReceiveValue(char* value_name, unsigned char* value_name_length, double* value) const;

	bool CloseSocket() const;
};
