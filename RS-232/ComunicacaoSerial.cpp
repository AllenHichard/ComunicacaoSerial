#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "rs232.h"
//void chartobin (unsigned char c, char bin[]) {
//	int i;
// for(i=7;i>=0;i­­) {
//		bin[i] = (c%2) + '0';
//		c /= 2;
//	}
//}
int main() {
	int i, l, bdrate=9600; // taxa de transmissão (baud) 
	int cport_nr=0; // /dev/ttyS0
	unsigned char coordenada;
	char c, bin[]={'1','2','3','4','5','6','7','8',0};
	char mode[]={'8','N','2',0}; // 8 bits, sem paridade 	(N = None | O = Ímpar | E = Par), 2 stopbits
		if (RS232_OpenComport(cport_nr, bdrate, mode)) {
			printf("Can not open comport\n");
			usleep(1000000);
			return 0;
	}
	for(i=0; i<35; i++) {
		if (i <= 15)
			printf("Modo Gravacao\n");
		else
			printf("Modo Jogo\n");
		printf("Insira uma nova coordenada: ");
		scanf(" %c%d", &c, &l);
		if (l == 99) {
			RS232_CloseComport(cport_nr);
			return 0;
		}
		c = toupper(c);
		switch(c) {
			case 'A':
				coordenada = 160 + l;
				break;
			case 'B':
				coordenada = 176 + l;
				break;
			case 'C':
				coordenada = 192 + l;
				break;
			case 'D':
				coordenada = 208 + l;
				break;
			case 'E':
				coordenada = 224 + l;
				break;
		}
		RS232_SendByte(cport_nr, coordenada);
	//	chartobin(coordenada, bin);
		printf("Enviando %c%d = %s\n\n\n\n\n", c, l, bin);
	}
	RS232_CloseComport(cport_nr);
	return 0;
}
