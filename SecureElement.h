#pragma once

#include <mbed.h>
#include "cryptoauthlib.h"

class SecureElement {
public:
    SecureElement();

    uint8_t getSerialNumber(char* str, uint8_t size);

    // returns 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00
    // if the config zone is not locked.
    uint8_t getRandomNumber(char* str, uint8_t size);    

private:
    ATCA_STATUS _getSerialNumber(uint8_t *serialNum);

private:
};