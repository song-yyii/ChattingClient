#pragma once

struct Overlap
{
	WSAOVERLAPPED	overlap = { 0 };
	int				event_type = { OV_RECV };
	WSABUF			wsabuf = { 0 };
	unsigned char	iocp_buff[BUF_SIZE] = { 0 };
};

struct RecvBuffInfo {
	unsigned char	buf[BUF_SIZE];
	int				sizePrev = { 0 };
	int				sizeCurr = { 0 };
};


class ChattingClient
{
public:
	ChattingClient();
	virtual ~ChattingClient();

private:
	SOCKET			g_socket;
	//Overlap			recv_over;
	//RecvBuffInfo	recv_buff;

	WSABUF			send_wsabuf;
	char 			send_buffer[BUF_SIZE];
	WSABUF			recv_wsabuf;
	char 			recv_buffer[BUF_SIZE];

	int				my_id;

	/*WSABUF			dataBuf;
	char			message[1024] = { 0, };
	int				sendBytes = 0;
	int				recvBytes = 0;*/

	HANDLE			handle;
	HANDLE			m_hiocp = { 0 };
	bool			m_b_server_shut_down = { false };
	bool			server_connected = { false };

public:
	void		ServerConnect();
	void		RecvThread();
	int			Recvn(SOCKET s, char* buf, int len, int flags);

	int			PacketRessembly(DWORD packetSize);
	void		ProcessPacket(unsigned char *packet);
	void		ProcessEneterChannelPacket(unsigned char *packet);
	void		ProcessCreateRoomPacket(unsigned char *packet);
	void		ProcessRoomMovePacket(unsigned char *packet);
	void		ProcessRoomUserListPacket(unsigned char *packet);
	void		ProcessNotifyExistRoomPacket(unsigned char *packet);
	void		ProcessRoomListPacket(unsigned char *packet);
	void		ProcessRoomChatPacket(unsigned char *packet);

	int			WsaRecv();
	void		SendPacket(unsigned char *packet);
	void		SendChannelMovePacket(int channel);
	void		SendCreateRoomPacket(int room);
	void		SendRoomMovePacket(unsigned char *packet);
	void		SendRoomUserListPacket(unsigned char *packet);
	void		SendRoomChatting(char* message, int room);
	void		SendEnterRoom(int room);

	void		CloseSocket();
	void		err_display(char *msg, int err_no);
	void		SetMenu();
	void		ChattingThreadStart(int roomIndex);
	void		ChattingMenu(int roomIndex);
	void		ChattingCommand(int roomIndex);
};
