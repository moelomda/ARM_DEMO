#include "DataProcessing.h"


extern u8 Main_State ;
u8 *Tx_buffer;
u8 Recived_Data=17;
extern u8 *Rx_buffer;
extern u8 key_value;
extern u8 operation_state;

void CB();
void Operation_Proc()
{
	switch(operation_state)
	{
       	case Send_Data:
      //  encode_buffer(key_value, Tx_buffer);
		//Uart_TxBufferAsync(USARTID_1, Tx_buffer,4, CB);
       		USART_HalSendByte(USARTID_1,key_value);
		key_value = IDLE_KEY ;
        Main_State = IDLE ;
		break;
		case Recieve_Data:
	    //decode_buffer(Rx_buffer, &Recived_Data);
		Main_State = MODE;
		ACTION_Get(Recived_Data);
		Recived_Data=17;
		break ;
	}
}
/*
u8 calculate_checksum(u8 data) {
    u8 checksum = 0;
    checksum += data;
    return checksum;
}
void encode_buffer(u8 data, u8 *buffer) {
    buffer[0] = 0xFF;               // Start byte
    buffer[1] = data;               // Data byte
    buffer[2] = calculate_checksum(data); // Checksum
    buffer[3] = 0xFF;               // End byte
}
DecodeErrorStatus_t decode_buffer(u8 *buffer, u8 *data) {
    u8 Loc_ErrorStatus = DECODE_NO_ERROR;
    if (buffer[0] != 0xFF || buffer[3] != 0xFF) {
    	Loc_ErrorStatus = DECODE_INVALID_START_END_BYTES;
    }
    // Check if the checksum matches
    u8 received_checksum = buffer[2];
    u8 calculated_checksum = calculate_checksum(buffer[1]);
    if (received_checksum != calculated_checksum) {
    	Loc_ErrorStatus = DECODE_CHECKSUM_MISMATCH;
    }
    *data = buffer[1];
    return Loc_ErrorStatus ;
}
void CB()
{

}
*/
