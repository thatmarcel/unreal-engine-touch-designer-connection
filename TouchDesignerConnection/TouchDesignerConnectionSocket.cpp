#include "TouchDesignerConnectionSocket.h"

#include "Common/UdpSocketBuilder.h"

bool TouchDesignerConnectionSocket::Open(unsigned short local_port) {
	Socket = FUdpSocketBuilder("TouchDesigner Connection Socket")
		.AsNonBlocking()
		.AsReusable()
		.BoundToAddress(FIPv4Address::Any)
		.BoundToPort(local_port)
		.Build();

	return true;
}

bool TouchDesignerConnectionSocket::Close() {
	if (Socket) {
		if (!Socket->Shutdown(ESocketShutdownMode::ReadWrite)) {
			return false;
		}
		
		if (!Socket->Close()) {
			return false;
		}
		
		Socket = nullptr;
		
		return true;
	} else {
		return false;
	}
}


bool TouchDesignerConnectionSocket::Receive(char* buffer, int buffer_length, const FString* sender_ip_address, unsigned short sender_port) const {
	if (!Socket) {
		return false;
	}

	FIPv4Address expected_sender_address;
	
	if (!FIPv4Address::Parse(*sender_ip_address, expected_sender_address)) {
		return false;
	}

	TSharedRef<FInternetAddr> sender_address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	int32 bytes_read = 0;
	
	if (!Socket->RecvFrom(
		reinterpret_cast<uint8*>(buffer),
		buffer_length,
		bytes_read,
		*sender_address,
		ESocketReceiveFlags::None
	)) {
		return false;
	}

	if (*sender_address != *FIPv4Endpoint(expected_sender_address, sender_port).ToInternetAddr()) {
		return false;
	}

	return true;
}

bool TouchDesignerConnectionSocket::Send(const char* buffer, int buffer_length, const FString* destination_ip_address, unsigned short destination_port) const {
	if (!Socket) {
		return false;
	}

	FIPv4Address destination_address;

	if (!FIPv4Address::Parse(*destination_ip_address, destination_address)) {
		return false;
	}

	int32 bytes_sent = 0;

	if (!Socket->SendTo(
		reinterpret_cast<const uint8*>(buffer),
		buffer_length,
		bytes_sent,
		*FIPv4Endpoint(destination_address, destination_port).ToInternetAddr()
	)) {
		return false;
	}

	return true;
}