/*
 * input.h
 *
 *  Created on: 25 jun. 2021
 *      Author: mateo
 */

#ifndef INPUT_H_
#define INPUT_H_

int getInt(char* msg);
float getFloat(char* msg);
char getChar(char* msg);
int getString(char* msg, char* destino);
int getStringAll(char* msg, char* destino);
int getCuit(char* msg);
int getPositivoEntero(char* msg);
float getPositivoFlotante(char* msg);
int esCuit(char* cadena);
int esNumerica(char* cadena);
int esAlfanumerica(char* cadena);

#endif /* INPUT_H_ */
