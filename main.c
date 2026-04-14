#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// лог сложение
// 101001110 - 1 вектор
// 010110001 - 2 вектор
// 111111111 - ответ(т е если в 1 векторе бит равен 1 , а в другом 1 или 0, то ставим 1)
unsigned char *logSum(unsigned char *vecA, size_t lenA,unsigned char *vecB, size_t lenB) {
    if((lenA==lenB) && vecA && vecB ){
    size_t size_byte = ((lenA - 1) / 8) + 1;
    unsigned char *result = (unsigned char*)calloc(size_byte,sizeof(unsigned char));
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
    result = (unsigned char*)calloc(size_byte,sizeof(unsigned char));
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
    result = (unsigned char*)calloc(size_byte,sizeof(unsigned char));
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
    result = (unsigned char*)calloc(size_byte,sizeof(unsigned char));
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



unsigned char *convertLongBvToStr(unsigned char *vec, size_t sz){
  size_t ix = 0;
  unsigned char mask =1;
  unsigned char* str = NULL;
  if (vec && sz){
    size_t len = 8 * sz + 1;
    str =(unsigned char*)calloc(len,sizeof(unsigned char));
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



unsigned char *shiftLeft(unsigned char *vec, size_t len, size_t n) {
    if (!vec) return NULL;
    if (n >= len){return NULL;}
    size_t size_byte = ((len - 1) / 8) + 1;
    unsigned char *result = NULL;
    result = (unsigned char*)calloc(size_byte,sizeof(unsigned char));
    for (size_t i = 0; i < size_byte; i++) {result[i] = 0;}
    if (!result) return NULL;
    size_t byte = n / 8; // на сколько байтов сдвиг
    size_t bit = n % 8; // на сколько бит сдвиг

    for (size_t i = 0; i < size_byte; i++) {
        unsigned char byte_working = 0;

        if (i + byte < size_byte) {
            byte_working = vec[i + byte] >> bit;}
        if (bit > 0 && (i + byte + 1 < size_byte)) {
            unsigned char perenos = vec[i + byte + 1] << (8 - bit);
            byte_working = byte_working | perenos;
        }
        result[i] = byte_working;}
    int ostat = len % 8;
    if (ostat != 0) {
        unsigned char mask = -1;
        mask = (mask >> (8-ostat));
        result[size_byte - 1] = result[size_byte - 1] & mask;
    }
    return result;
}

unsigned char *shiftRight(unsigned char *vec, size_t len, size_t n) {
    if (!vec) return NULL;

    size_t size_byte = ((len - 1) / 8) + 1;
    unsigned char *result = NULL;
    result = (unsigned char*)calloc(size_byte,sizeof(unsigned char));
    if (!result) return NULL;
    for (size_t i = 0; i < size_byte; i++) {result[i] = 0;}
    size_t byte = n / 8; // на сколько байтов сдвиг
    size_t bit = n % 8; // на сколько бит сдвиг

    for (size_t i = size_byte-1; i < size_byte; i--) {
        unsigned char byte_working = 0;

        if (i >= byte) {
            byte_working = vec[i - byte] << bit;}
        if (bit > 0 && (i > byte)) {
            unsigned char perenos = vec[i - byte - 1] >> (8 - bit);
            byte_working = byte_working | perenos;
        }
        result[i] = byte_working;}
    int ostat = len % 8;
    if (ostat != 0) {
        unsigned char mask =-1;
        mask = (mask >> (8-ostat));
        result[size_byte - 1] = result[size_byte - 1] & mask;}
    return result;}


void printBV(unsigned char *vec, int size){
    if(vec && size){
        int byte = ((size - 1) / 8) + 1; // байты
        int ix = 0;
        unsigned char mask =1;
        for (int i = 0; i < byte;i++){
              mask = 1;
              for (int j = 0; (j<8) && (ix < size);j++){
                       if ((vec[i]& mask) != 0){printf("1");}
                       else {printf("0");}
                       mask = mask << 1;
                       ix++;
}
}
}
}
int main()
{
  //char *strA = "110011"; // 6 бит
  //char *strB = "000000"; // 8 бит

  //char *strA = "101001111"; // 9 бит
  //char *strB = "010110000"; // 9 бит

  //char *strA = "g0f00das"; // 8 бит тест нужен чтобы показать, что на вход может поступать что угодно и все будет работать верно
  //char *strB = "01011000"; // 8 бит

  //char *strA = "     0 0"; // 8 бит
  //char *strB = "00000000"; // 8 бит

  //char *strA = "1"; // 1 бит
  //char *strB = "9"; // 1 бит !!! не происходит изменение хвоста даже если ставим сет бит  поэтому его тут обрабатывать не надо!!!


  char *strA = "0000000";//7 бит
  char *strB = "1111111"; // 7 бит
  //char *strB = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"; // 100 бит
  //char *strA = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"; // 100 бит

  int cellsA, cellsB;
  unsigned char *vecA = convertStrtoLongBv(strA, &cellsA);
  unsigned char *vecB = convertStrtoLongBv(strB, &cellsB);

  int lenA = strlen(strA);
  int lenB = strlen(strB);
  if (lenA <= 0 || lenB <= 0 || lenA != lenB){printf("Error with size"); return 0;}



unsigned char *result = inversion(vecA, lenA);
// printBV(result,lenA);
// if (result){
//     char *stroka = convertLongBvToStr(result, cellsA);
//     free(result);
//     result = NULL;
//     free(stroka);
//     stroka = NULL;}


printBV(vecA,lenA);
printf("\n");
printf("Результат Инверсии: ");
printBV(result,lenA);
printf("\n");
  if (result){
    unsigned char *result2 = shiftLeft(result, lenA,3);
  if (result2){
    char *stroka = convertLongBvToStr(result2, cellsA);
    printf("Результат после сдвигов: ");
    printf("%s",stroka);
    printf("\n");
    free(stroka);}
    free(result);
    result = NULL;
    free(result2);
    result2 = NULL;}





printf("\n");
printf("----------------------------------------------------------------------------------------------------");
printf("\n");

vecA = convertStrtoLongBv(strA, &cellsA);
result = inversion(vecA, lenA);


  if (result){
    unsigned char *result2 = shiftRight(result, lenA,3);
  if (result2){
    char *stroka = convertLongBvToStr(result2, cellsA);
    printf("kaskad for right %s \n", stroka);
    free(stroka);}
    free(result);
    result = NULL;
    free(result2);
    result2 = NULL;}

for (int i = 0 ; i < 100; i++){
    if (i==0){printBV(vecA,lenA);}
    if (i >= lenA){break;}
    printf("\n");
    set1(vecA,lenA,i);
    printBV(vecA,lenA);}


printf("\n");
printf("----------------------------------------------------------------------------------------------------");
printf("\n");
for (int i = 0 ; i < 100; i++){
    if (i==0){printBV(vecA,lenA);}
    if (i >= lenA){break;}
    printf("\n");
    set0(vecA,lenA,i);
    printBV(vecA,lenA);}

printf("\n");

//Сдвиг влево
//for (int i = 0 ; i <= 7 ; i++){
  //printf("\n");
  //if (i ==0){printBV(vecA, lenA);}
  //else{
  //unsigned char * result = shiftLeft(vecA, lenA, 1);
  //if (result){
    //printBV(result, lenA);}
    //free(vecA);
    //vecA = result;}
//}
//printf("\n");
//printf("----------------------------------------------------------------------------------------------------");
//Сдвиг вправо
//for (int i = 7 ; i >=0 ; i--){
  //printf("\n");
  //if (i ==100){printBV(vecA, lenA);}
  //else{
  //unsigned char * result = shiftRight(vecA, lenA, 1);
  //if (result){
   // printBV(result, lenA);}
    //free(vecA);
  //  vecA = result;}
//}
printf("----------------------------------------------------------------------------------------------------");
result = logSum(vecA, lenA,vecB, lenB);
printBV(result,lenA);
if (result){
    char *stroka = convertLongBvToStr(result, cellsA);
    printf("Sum: %s \n", stroka);
    free(result);
    result = NULL;
    free(stroka);
    stroka = NULL;}

result = logMul(vecA, lenA,vecB, lenB);
printBV(result,lenA);
if (result){
    char *stroka = convertLongBvToStr(result, cellsA);
    printf("Mul: %s \n", stroka);
    free(result);
    result = NULL;
    free(stroka);
    stroka = NULL;}

result = sumMod2(vecA, lenA,vecB, lenB);
printBV(result,lenA);
if (result){
    char *stroka = convertLongBvToStr(result, cellsA);
    printf("SumMod2: %s \n", stroka);
    free(result);
    result = NULL;
    free(stroka);
    stroka = NULL;}

result = inversion(vecA, lenA);
printBV(result,lenA);
if (result){
    char *stroka = convertLongBvToStr(result, cellsA);
    printf("Invertion: %s \n", stroka);
    free(result);
    result = NULL;
    free(stroka);
    stroka = NULL;}
// Сдвиг влево
  //result = shiftRight(vecA, lenA, 3);
 //printBV(result,lenA);
  //if (result){
    //char *stroka = convertLongBvToStr(result, cellsA);
    //printf("SdvigRight: %s \n", stroka);
    //free(result);
    //result = NULL;
    //free(stroka);
   // stroka = NULL;}

// установка k-то бита
  //set1(vecA, lenA,3);
  //if (vecA){
    //char *stroka = convertLongBvToStr(vecA, cellsA);
    //printf("%s \n", stroka);
    //free(stroka);
    //stroka = NULL;}
//сброс k-того бита
  //set0(vecA, lenA,3);
  //if (vecA){
    //char *stroka = convertLongBvToStr(vecA, cellsA);
    //printf("%s \n", stroka);
    //free(stroka);
    //stroka = NULL;}

  free(vecA);
  free(vecB);
  return 0;
}
