#if !defined(__A89F8103_2CB6_4D54_9381_08DCA3B29DB2__)
#define __A89F8103_2CB6_4D54_9381_08DCA3B29DB2__
extern "C" {
#pragma pack(push, 1)
typedef struct tagPacketHeader {
  // Packet header logo
  unsigned long header_logo;
  // Server identify
  unsigned long long server_identify;
  // Original data size
  unsigned long original_size;
  // Real-time (actual) data size
  unsigned long data_size;
  // Total size of the packet frame
  unsigned long packet_size;
  // Command code
  unsigned long command_code;
  // ZIP compression type
  unsigned char zip_type;
  // Packet encryption type
  unsigned char encryption_type;
  // Packet footer logo
  unsigned long footer_logo;
  // Character array used to encapsulate the data
  char data[1];
} PacketHeader, HEAD, *PHEAD;

#pragma pack(pop)
}

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 15 Apr 2025 07:38:35 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__A89F8103_2CB6_4D54_9381_08DCA3B29DB2__
