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


//Инверсия
// 101001110
// 010110001 (т е если встретили 1 то меняем на 0 и наоборот)
unsigned char *inversion(unsigned char *vec, size_t len) {
    if (vec){
    unsigned char *result = NULL;
    size_t size_byte = ((len - 1) / 8) + 1;
    result = (unsigned char*)malloc(size_byte);
    for (size_t i = 0; i < size_byte; i++) {result[i] = 0;}
    if (result) {
        for (size_t i = 0; i < size_byte; i++) {
            result[i] = ~vec[i];}

        if (len % 8 != 0) {// очистка хвоста путем определения его длины сдвига маски и лог умножения
            int ostat = len % 8;
            unsigned char clean = -1;
            clean = (clean >> (8-ostat));
            result[size_byte - 1] = result[size_byte - 1] & clean;
        }}
    return result;}
    return NULL;}



// установка k-того разряда
// 110111 , хочу вместо 0 поставить 1 , тогда мне нужно сделать маску где я сдвину в ней одну 1 на k мест, т.e. 001000 применить сложение логи
void set1(unsigned char *vec, size_t len,size_t k)
{   if (k < len && vec){
    int byte = 0;
    unsigned char mask = 1;
    byte = k/8; //номер  ячейки
    int bit = k%8; // номер разряда  в ячейке
    mask = mask << bit;
    vec[byte] = vec[byte] | mask;}
}
// сброс k-того разряда
// 111111 хочу на том же месте убрать 1, тогда мне надо сделать маску где я сдвину в ней одну 1 на k мест, t.e 001000 инвертирую 110111
// и сделаю лог умнож( ИЛИ это (искл или) но да ладно)
void set0(unsigned char *vec, size_t len,size_t k)
{   if (k < len && vec){
    int byte = 0;
    unsigned char mask = 1;
    byte = k/8; //номер  ячейки
    int bit = k%8; // номер разряда  в ячейке
    mask = mask << bit;
    vec[byte] = vec[byte] ^ mask;}
}

unsigned char *convertStrtoLongBv(char *str, int *cells){
  if(str && cells){
    int len = 0, ix = 0;
    len = strlen(str);
    *cells = ((len - 1) / 8) + 1;
    unsigned char mask = 1;
    unsigned char *vec = (unsigned char*)malloc(sizeof(unsigned char) * (*cells));
    if (vec==NULL) {return NULL;}
    for (int i = 0; i < *cells; i++) {vec[i] = 0;}
    for (int i = 0; i < *cells; i++)
      {
        mask = 1;
        for (size_t j = 0; (j < 8) && (ix < len); j++){
              if(str[ix] != '0'){
                      vec[i] = vec[i] | mask;}
              mask = mask << 1;
              ix++;}}
  return vec;}
  return NULL;}



char *convertLongBvToStr(unsigned char *vec, size_t sz){
  size_t ix = 0;
  unsigned char mask =1;
  char* str = NULL;
  if (vec && sz){
    size_t len = 8 * sz + 1;
    str =(char*)malloc(len);
    for (size_t i = 0; i < len; i++) {str[i] = 0;}
    if (str){
        for (size_t i = 0; i < sz; i++){
            mask = 1;
            for (size_t j = 0; j < 8 && (ix < len); j++){
                if ((vec[i]&mask)!=0){str[ix] = '1';}
                else{str[ix]='0';}
                ix++;
                mask = mask << 1;}}
        str[ix] = '\0';
      }
  return str;}
  return NULL;
}
int main()
{
    printf("Hello World!\n");
    return 0;
}
