#pragma once

#include "TouchDesignerConnectionController.h"

class TouchDesignerConnectionManager {
private:
	TouchDesignerConnectionController* Controller = nullptr;
public:
	TMap<FString, double> Kvs;
	
	void Connect(unsigned short local_port, const FString* remote_ip_address, unsigned short remote_port);
	void ReceiveValues();
	bool SendValue(const char* value_name, unsigned char value_name_length, double value) const;
	bool Disconnect() const;
};
