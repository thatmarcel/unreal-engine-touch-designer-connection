#include "TouchDesignerConnectionManager.h"

void TouchDesignerConnectionManager::Connect(unsigned short local_port, const FString* remote_ip_address, unsigned short remote_port) {
	if (Controller != nullptr) {
		bool _ = Controller->CloseSocket();
	}

	Controller = new TouchDesignerConnectionController(local_port, remote_ip_address, remote_port);
}

void TouchDesignerConnectionManager::ReceiveValues() {
	if (Controller == nullptr) {
		return;
	}

	for (int i = 0; i < 1000; i++) {
		char value_name[UINT8_MAX] = {};
		unsigned char value_name_length = 0;
		double value;
	
		if (!Controller->ReceiveValue(value_name, &value_name_length, &value)) {
			break;
		}

		Kvs.Add(FString(ANSI_TO_TCHAR(value_name)), value);
	}
}

bool TouchDesignerConnectionManager::SendValue(const char* value_name, unsigned char value_name_length, double value) const {
	if (Controller == nullptr) {
		return false;
	}
	
	return Controller->SendValue(value_name, value_name_length, value);
}

bool TouchDesignerConnectionManager::Disconnect() const {
	if (Controller == nullptr) {
		return false;
	}

	return Controller->CloseSocket();
}
