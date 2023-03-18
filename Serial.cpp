#include "Serial.hpp"

Serial::Serial(UART_HandleTypeDef *huart, uint8_t *rxBuffer, char terminator, char separator)
{
    this->huart = huart;
    this->terminator = terminator;
    this->separator = separator;
    this->rxBuffer = rxBuffer;
    startReceiving();
}

void Serial::pasteThisToRxCpltCallback()
{
//    startReceiving();
}

void Serial::startReceiving()
{
    HAL_UART_DMAStop(huart);
    HAL_UART_Receive_DMA(huart, rxBuffer, MAXMESSAGELENGTH);
}

bool Serial::readyRead()
{
    // Check if message is terminated
    uint16_t idx = getRdmaInd();
    if (idx > 0 ? (rxBuffer[idx - 1] == terminator) : (rxBuffer[MAXMESSAGELENGTH - 1] == terminator))
    {
        // Place \0 at the end of message
        if (idx == 0)
            rxBuffer[MAXMESSAGELENGTH - 1] = '\0';
        else
            rxBuffer[idx - 1] = '\0';


        words[0] = rxBuffer;

        messageLength = idx;
        uint16_t wordNumber = 0;
        for (int i = 0; i < messageLength; ++i)
            if (rxBuffer[i] == separator)
            {
                rxBuffer[i] = '\0';
                words[++wordNumber] = rxBuffer + i + 1;
            }
        return true;
    }
    return false;
}

int32_t Serial::getInt(const uint16_t &num)
{
    return atol((char *) words[num]);
}

double Serial::getFloat(const uint16_t &num)
{
    return atof((char *) words[num]);
}


