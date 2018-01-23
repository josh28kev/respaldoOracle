/* Universidad Nacional de Costa Rica
Facultad de Ciencias Exactas y Naturales
Escuela de Informàtica

Programa elaborado por:
	Kevin Josue Morales Marín

II Ciclo, 2016

Requistos previos

BD en modo ARCHIVE
Tener un usuario llamado RMAN con contraseña RMAN
Configurar TNSNAMES con IP local
Haber registrado la base de datos en RMAN y creado el catalogo.

En SQL PLUS
CREATE USER RMAN IDENTIFIED BY RMAN DEFAULT USERS QUOTA UNLIMITED ON USERS;
GRANT CONNECT TO RMAN;
GRANT RECOVERY_CATALOG_OWNER TO RMAN;
GRANT RESOURCE TO RMAN;

En RMAN
CONNECT TARGET RMAN/RMAN@XE;
CONNECT CATALOG RMAN/RMAN@XE;
CREATE CATALOG;
REGISTER DATABASE;
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <conio.h> 
 #include <dos.h> 
  #include <ctime> 
   #include <Windows.h> 
      #include <stdio.h> 
using namespace std;


int main (int argc, char *argv[]){

string tiempo;
	SYSTEMTIME time;
GetLocalTime (&time);
char buffer[256];
int hora=time.wHour; 
//sprintf_s(buffer, "%02d:%02d", time.wHour, time.wMinute);
int minutos =time.wMinute;


printf( "%02d:%02d",time.wHour, time.wMinute); 

	
 string ruta2 = argv[argc-1];
 	int hora2 =0;
	int minutos2=0;
	ifstream entrada2(argv[argc-1]);
	entrada2>>hora2;
	entrada2>>minutos2;
	entrada2.close();
	if((hora==hora2) && (minutos== minutos2|| (minutos<minutos2+5 && minutos >= minutos2))){
	string ruta = argv[argc-2];
	string objeto;
	string nombre;
	ifstream entrada (argv[argc-2]);
	entrada>>objeto;
	entrada>>nombre;
	entrada.close();
	ofstream archivo("Est.rman");
	archivo<<"CONNECT TARGET RMAN/RMAN@XE;"<<endl;
	archivo<<"CONNECT CATALOG RMAN/RMAN@XE;"<<endl;
	archivo<<"SPOOL LOG TO C:/A.LOG"<<endl;
	archivo<<"RUN{"<<endl;
	if(objeto == "full"){
	archivo<<"BACKUP DATABASE SPFILE PLUS ARCHIVELOG;"<<endl;
	}
	if(objeto == "TABLESPACE"){
	archivo<<"BACKUP TABLESPACE "+nombre+";"<<endl;
	}
	if(objeto == "DATAFILE"){
	archivo<<"BACKUP datafile "+nombre+";"<<endl;
	}
	if(objeto == "ARCHIVELOG"){
	archivo<<"BACKUP ARCHIVELOG "+nombre+";"<<endl;
	}
	archivo<<"}"<<endl;
	archivo.close();
		system("START C:/oraclexe/app/oracle/product/11.2.0/server/bin/RMAN.EXE ""@Est.rman""");
}
else{
	
	cout<<"Hora no correcta!!"<<endl;
}
	return 0;
}