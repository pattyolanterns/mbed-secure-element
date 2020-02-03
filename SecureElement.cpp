#include "SecureElement.h"

SecureElement::SecureElement() {

}

uint8_t SecureElement::getSerialNumber(char* str, uint8_t size) {
    ATCA_STATUS status;
    uint8_t serialNum[ATCA_SERIAL_NUM_SIZE];
    size_t s = size;

    status = _getSerialNumber(serialNum);
    if (status == ATCA_SUCCESS) {
        atcab_bin2hex(serialNum, ATCA_SERIAL_NUM_SIZE, str, &s);
        return 0;
    }
    return 1;
}

uint8_t SecureElement::getRandomNumber(char* str, uint8_t size) {
    ATCA_STATUS status;
    uint8_t randout[RANDOM_RSP_SIZE];
    size_t s = size;

    status = atcab_init(&cfg_atsha204a_i2c_default);
    if (status == ATCA_SUCCESS) {
        status = atcab_random(randout);
        atcab_release();
        if (status == ATCA_SUCCESS) {
            atcab_bin2hex(randout, RANDOM_RSP_SIZE, str, &s);
            return 0;
        }
    }
    return 1;
}

ATCA_STATUS SecureElement::_getSerialNumber(uint8_t *serialNum) {
    ATCA_STATUS status;

    status = atcab_init(&cfg_atsha204a_i2c_default);
    if (status != ATCA_SUCCESS) {
        return status;
    }
    status = atcab_read_serial_number(serialNum);
    atcab_release();
    return status;
}