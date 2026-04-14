#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// лог сложение
// 101001110 - 1 вектор
// 010110001 - 2 вектор
// 111111111 - ответ(т е если в 1 векторе бит равен 1 , а в другом 1 или 0, то ставим 1)
unsigned char *logSum(unsigned char *vecA, size_t lenA,unsigned char *vecB, size_t lenB) {
    if((lenA==lenB) && vecA && vecB ){
    unsigned char *result = NULL;
    size_t size_byte = ((lenA - 1) / 8) + 1;
    result = (unsigned char*)malloc(size_byte);
    for (size_t i = 0; i < size_byte; i++) {result[i] = 0;}
    if (result) {
        for (size_t i = 0; i < size_byte; i++) {
            result[i] = vecA[i] | vecB[i];}}
    return result;}
  return NULL;}


//логическое умножение
// 101001110 - 1 вектор
// 010110001 - 2 вектор
// 000000000 - ответ(т е если в 1 векторе бит равен 1 , а в другом 1, то ставим 1 в других случаях 0) !! обратное искл или

unsigned char *logMul(unsigned char *vecA, size_t lenA,unsigned char *vecB, size_t lenB) {
    if((lenA==lenB) && vecA && vecB ){
    unsigned char *result = NULL;
    size_t size_byte = ((lenA - 1) / 8) + 1;
    result = (unsigned char*)malloc(size_byte);
    for (size_t i = 0; i < size_byte; i++) {result[i] = 0;}

    if (result) {
        for (size_t i = 0; i < size_byte; i++) {
            result[i] = vecA[i] & vecB[i];}}
    return result;}
  return NULL;}


//Искл или(Сумма по модулю 2)
// 101001110 - 1 вектор
// 010110001 - 2 вектор
// 111111111 - ответ(т е если в 1 векторе бит равен 1 , а в другом 0, то ставим 1)
unsigned char *sumMod2(unsigned char *vecA, size_t lenA,unsigned char *vecB, size_t lenB) {
    if((lenA==lenB) && vecA && vecB ){
    unsigned char *result = NULL;
    size_t size_byte = ((lenA - 1) / 8) + 1;
    result = (unsigned char*)malloc(size_byte);
    for (size_t i = 0; i < size_byte; i++) {result[i] = 0;}
    if (result) {
        for (size_t i = 0; i < size_byte; i++) {
            result[i] = vecA[i] ^ vecB[i];}}
    return result;}
  return NULL;}

int main()
{
    printf("Hello World!\n");
    return 0;
}
