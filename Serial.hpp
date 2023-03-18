#ifndef SERIAL_H
#define SERIAL_H

#include "usart.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXMESSAGELENGTH 2048
#define MAXNUMBEROFWORDS 2048

class Serial
{
private:
    UART_HandleTypeDef *huart;
    uint8_t *rxBuffer;
    char terminator, separator;
    uint16_t prevIdx = 0;

public:
    uint16_t messageLength = 0;
    uint16_t numberOfWords = 0;
    uint8_t *words[MAXNUMBEROFWORDS];


    inline uint32_t getRdmaInd()
    {
        return (MAXMESSAGELENGTH - __HAL_DMA_GET_COUNTER(huart->hdmarx)) & (MAXMESSAGELENGTH - 1);
    }

public:
    Serial() = default;

    Serial(UART_HandleTypeDef *huart, uint8_t *rxBuffer, char terminator = ';', char separator = ',');

    void pasteThisToRxCpltCallback();

    bool readyRead();

    int32_t getInt(const uint16_t &num);

    double getFloat(const uint16_t &num);

    void startReceiving();


private:

};

#endif