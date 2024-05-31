#include "TouchDesignerConnectionController.h"

TouchDesignerConnectionController::TouchDesignerConnectionController(unsigned short local_port, const FString* remote_ip_address, unsigned short remote_port) {
	Remote_IP_Address = remote_ip_address;
	
	Remote_Port = remote_port;

	Socket = new TouchDesignerConnectionSocket();

	Socket->Open(local_port);
}

bool TouchDesignerConnectionController::SendValue(const char* value_name, unsigned char value_name_length, double value) const {
	unsigned char message[2 + sizeof(double) + UCHAR_MAX] = {
		0x01, // message id / type
		value_name_length
	};

	union {
		double value_double;
		char value_chars[sizeof(double)];
	};

	value_double = value;

	memcpy(message + 2, value_chars, sizeof(double));

	memcpy(message + 2 + sizeof(double), value_name, value_name_length);

	return Socket->Send(
		reinterpret_cast<const char*>(message),
		sizeof(message),
		Remote_IP_Address,
		Remote_Port
	);
}

bool TouchDesignerConnectionController::ReceiveValue(char* value_name, unsigned char* value_name_length, double* value) const {
	unsigned char buffer[UINT16_MAX] = {};
	
	if (!Socket->Receive(
		reinterpret_cast<char*>(buffer),
		sizeof(buffer),
		Remote_IP_Address,
		Remote_Port
	)) {
		return false;
	}

	unsigned char message_id = buffer[0];

	if (message_id != 0x01) {
		return false;
	}

	*value_name_length = buffer[1];

	union {
		double value_double;
		char value_chars[sizeof(double)];
	};

	memcpy(value_chars, buffer + 2, sizeof(double));

	*value = value_double;

	memcpy(value_name, buffer + 2 + sizeof(double), *value_name_length);
	
	return true;
}

bool TouchDesignerConnectionController::CloseSocket() const {
	return Socket->Close();
}
