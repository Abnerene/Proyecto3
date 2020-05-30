#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <stdio.h>

#ifdef __linux__
#define limpiar "clear"
#endif  
#ifdef __WINDOWS
#define limpiar "cls"
#endif 
 
using namespace std;

//longitudes de datos del material
int lId=0; //Largo Maximo de ID de material
int lTitulo=0; //Largo maximo del Titulo
int lDato1=0; //Largo maximo del dato1 Material
int lDato2=0; //Largo maximo del dato2 Material
int lIdCliente=0; //Largo maximo del ID cliente
int contador=0;
int contador2=0;
#include "otras.h"
#include "clases.h"
#include "graficos.h"
int main() {

	Reserva reservacion;



	ifstream archivoMaterial;
	archivoMaterial.open("material.txt");
	string x;
	int idMaterial;
	int dato1Material;
	string dato2Material;
	string titulo;
	string tipoMaterial;
	int max=30;
	Material *apuntador[max];
	
	int countD=0;
	int countL=0;
	int countS=0;
	vector <Disco> disco;
   disco.resize(max);
//	auto disco = make_unique<Disco[]>(3);

	
	vector <Libro> libro;
  libro.resize(max);

	
	vector <Software> software;
  software.resize(max);
	int posD[30];
	int posL[30];
	int posS[30];

 	while(archivoMaterial>>idMaterial>>titulo>>tipoMaterial>>dato1Material>>dato2Material){
		
		if(tipoMaterial=="D"){	
	    disco[countD]=Disco(idMaterial,titulo,dato1Material,dato2Material);	
			apuntador[contador]=&disco[countD];
			posD[countD]=contador;
			countD++;
		//disco[countD+10];
		//disco.resize(countD+1);
		
		}

		else if(tipoMaterial=="L"){	
			libro[countL]=Libro(idMaterial,titulo,dato1Material,dato2Material);
			apuntador[contador]=&libro[countL];
			posL[countL]=contador;
			countL++;
		//  libro.resize(countL+1);
		}

		else if(tipoMaterial=="S"){	
		  software[countS]=Software(idMaterial,titulo,dato1Material,dato2Material);
			apuntador[contador]=&software[countS];
			posS[countS]=contador;
			countS++;
		//	software.resize(countS+1);
		}

		//Proceso extra para obtencion de longitud maxima de caracteres
	  longitudMaxima(idMaterial,titulo,dato1Material,dato2Material);
				
		contador++;	
	}
	archivoMaterial.close();
//--Fin de la la carga de datos al apuntador---//
//Inicio de las reservaciones
ifstream archivoReservaciones;
archivoReservaciones.open("reservaciones.txt");

int dia;
int mes;
int anio;
int idCliente;
int maxCliente=60;
Reserva reservaciones[maxCliente];
Fecha fecha;

while(archivoReservaciones>>dia>>mes>>anio>>idMaterial>>idCliente){
 	fecha= Fecha(dia,mes,anio);
	reservaciones[contador2]= Reserva(idMaterial,idCliente,fecha);
	contador2++;
	if(to_string(idCliente).size()>lIdCliente){
		lIdCliente=to_string(idCliente).size();
	}
}//Fin e la carga de datos al arreglo de objetos reservaciones


//Inicio de la implementacion del menu//
int op=0;

while(op!=6){
	system(limpiar);
	printLibray();
	printMenu();
	cout<<"  Ingrese el número de la opcion: ";
	cin>>op;

//uso de swith para cada opcion
system(limpiar);

if(op==1){ //Muestra la lista de todos los materiales
	printMateriales();
	
	//Impresion por tipo de material
	//Imprime Libros

                   
	textLibros();
	cout<<mult("▄",(lId+lTitulo+lDato1+lDato2+13))<<endl;
	for(int i=0;i<countL;i++){
		int pos=posL[i];
	  apuntador[pos]->muestraDatos();
	}
	cout<<mult("▀",(lId+lTitulo+lDato1+lDato2+13))<<endl;
	cout<<endl;

	//Imprime Discos
	textDiscos();
	cout<<mult("▄",(lId+lTitulo+lDato1+lDato2+13))<<endl;
	for(int i=0;i<countD;i++){
		int pos=posD[i];
	  apuntador[pos]->muestraDatos();
	}
	cout<<mult("▀",(lId+lTitulo+lDato1+lDato2+13))<<endl;
	cout<<endl;

	//Imprime Software
	textSoftware();
	cout<<mult("▄",(lId+lTitulo+lDato1+lDato2+13))<<endl;	
	for(int i=0;i<countS;i++){
		int pos=posS[i];
	  apuntador[pos]->muestraDatos();
	}
	cout<<mult("▀",(lId+lTitulo+lDato1+lDato2+13))<<endl;
	cout<<endl;		
	wait();
}
	
else if(op==2){	//muestra de reservaciones
	//Se obtienes los mariales por el id
	int* posRes=reserv(apuntador,reservaciones);	
	printReservaciones();

	cout<<mult("▄",lTitulo+nSpace("cliente",lIdCliente,7)+44)<<endl; 
  cout<<"█ Fecha Inicio"+mult(" ",1);
	cout<<"█ Fecha entrega"+mult(" ",1);
	cout<<"█ Material"+mult(" ",(lTitulo-8));
	cout<<"█ Cliente"+mult(" ",nSpace("cliente",lIdCliente,8)+1)<<"█"<<endl;
	cout<<"█"<<mult("▀",14)<<"█"<<mult("▀",15)<<"█"<<mult("▀",lTitulo+1)<<"█"<<mult("▀",9+nSpace("cliente",lIdCliente,7))<<"█"<<endl;
	//Ciclo de impresión de datos
	for(int i=0;i<contador2;i++){
		int cantDias=apuntador[*posRes]->diasPrestamo();
		string titulo=apuntador[*posRes]->getTitulo();
		int id=reservaciones[i].getIdCliente();
		
		cout<<"█ "<<reservaciones[i].getFechaReservacion()<<"  █";
		cout<<" "<<reservaciones[i].fechaFinReserva(cantDias)<<"   ";
		cout<<"█ "<<titulo<<mult(" ",(lTitulo-titulo.size()));
		cout<<"█ "<<id<<mult(" ",nSpace(to_string(id),lIdCliente,8)+1)<<"█"<<endl;
		posRes++;

	}
	
	//Fin del ciclo de impresión de datos
	cout<<mult("▀",lTitulo+nSpace("cliente",lIdCliente,7)+44)<<endl;
	cout<<endl;
	wait();

}//Fin de la muestra de reservaciones


else if(op==3){ //Se ingresa un Id de material y se regresa la lista de reservaciones del material
back1:
printBuscar();
int* posRes=reserv(apuntador,reservaciones);
int idM;
cout<<"Ingresa un ID de material:";
cin>>idM;
if(validarMaterial(apuntador,idM)){
	  system(limpiar);
	  printReservaciones();
		cout<<mult("▄",lTitulo+33)<<endl; 
		cout<<"█ Material"+mult(" ",(lTitulo-8));
		cout<<"█ Fecha Incio"+mult(" ",1);
		cout<<"█ Fecha entrega"+mult(" ",1)<<"█"<<endl;
		cout<<"█"<<mult("▀",lTitulo+1)<<"█"<<mult("▀",13)<<"█"<<mult("▀",15)<<"█"<<endl;

	for(int i=0; i<contador2;i++){
		int idMaterial=apuntador[*posRes]->getIdMaterial();
		if(idM ==  idMaterial){

			int cantDias=apuntador[*posRes]->diasPrestamo();
			string titulo=apuntador[*posRes]->getTitulo();
			int id=reservaciones[i].getIdCliente();
			cout<<"█ "<<titulo<<mult(" ",(lTitulo-titulo.size()));
			cout<<"█ "<<reservaciones[i].getFechaReservacion()<<" █";
			cout<<" "<<reservaciones[i].fechaFinReserva(cantDias)<<"   █"<<endl;
		//Fin del ciclo de impresión de datos
		
		}
		posRes++;
	}
	cout<<mult("▀",lTitulo+33)<<endl;
	cout<<endl;
}
else{
	system(limpiar);
	textError();
	cout<<"El ID "<<idM<<" no existe,intenta de nuevo."<<endl;
	wait();
	system(limpiar);
	goto back1;
}
wait();
}//Fin de la opcion 3

else if(op==4){ //Consultar reservacion por fecha
	Fecha buscarFecha;
	Fecha fInicio;
	Fecha fFinal;
	int* posRes=reserv(apuntador,reservaciones);
	printBuscar();
	cin>>buscarFecha;		
	
	system(limpiar);
	printReservaciones();
	cout<<"▄"<<mult("═",13)<<"▄"<<endl;
	cout<<"█ "<<buscarFecha<<" █"<<endl;
	cout<<"▀"<<mult("═",13)<<"▀"<<endl;

	int sCliente=nSpace("cliente",lIdCliente,7);
	cout<<mult("▄",lTitulo+sCliente+13)<<endl; 
  cout<<"█ Material"+mult(" ",(lTitulo-8));
	cout<<"█ Cliente"+mult(" ",sCliente)<<" █"<<endl;
	cout<<"█"<<mult("▀",lTitulo+1)<<"█"<<mult("▀",9+sCliente)<<"█"<<endl;

  for(int i=0; i<contador2;i++){
		int cantDias=apuntador[*posRes]->diasPrestamo();
		int idMaterial=apuntador[*posRes]->getIdMaterial();
		fInicio=reservaciones[i].getFechaReservacion();
		fFinal=reservaciones[i].fechaFinReserva(cantDias);
		
		if(buscarFecha>=fInicio && buscarFecha<=fFinal){
			string titulo=apuntador[*posRes]->getTitulo();
			int id=reservaciones[i].getIdCliente();
			cout<<"█ "<<titulo<<mult(" ",(lTitulo-titulo.size()));
			cout<<"█ "<<id<<mult(" ",nSpace(to_string(id),lIdCliente,7))<<" █"<<endl;	
		}
			
	posRes++;
	}
	cout<<mult("▀",lTitulo+sCliente+13)<<endl;
	cout<<endl;
	wait();
}//Fin de la consulta por fecha

else if(op==5){//Hacer una reservacion
	printReservar();
	Reserva nReserva;
	Fecha nFecha;
	idCliente=0;
	back2:
	if(idCliente==0){
		cout<<"Ingresa el ID del cliente : ";
		cin>>idCliente;
		system(limpiar);
		printReservar();
		string contenido[1]={to_string(idCliente)};
		formatoTabla2(1,contenido,nFecha);
	}

	else{
		printReservar();
		string contenido[1]={to_string(idCliente)};
		formatoTabla2(1,contenido,nFecha);
	}

	cout<<endl;
	cout<<"Ingresa el ID del material : ";
	cin>>idMaterial;
	
	
		
	if(validarMaterial(apuntador,idMaterial)){
		system(limpiar);
		printReservar();
		string contenido[2]={to_string(idCliente),to_string(idMaterial)};
		formatoTabla2(2,contenido,nFecha);

		
		cout<<"Ingrese la fecha de reservacion"<<endl;
		cin>>nFecha;
		if(validarFecha(nFecha,reservaciones,apuntador)){
			system(limpiar);
			printReservar();
			formatoTabla2(3,contenido,nFecha);
			cout<<"Reservacion exitosa"<<endl;			
			reservaciones[contador2]= Reserva(idMaterial,idCliente,nFecha);
			contador2++;
				if(to_string(idCliente).size()>lIdCliente){
					lIdCliente=to_string(idCliente).size();
				}			
		}
		else{
			cout<<"La fecha no esta disponible"<<endl;
		}
	}
	else{
		system(limpiar);
		textError();
		cout<<"El ID "<<idMaterial<<" del material no existe, intente de nuevo"<<endl;
		wait();
		system(limpiar);
		goto back2;
	}
	
	wait();
	
}//Fin de la opcion para reservar

else if(op==6){//Termina el programa y guarda cambios de reservaciones
	ofstream archivoSalida;
  archivoSalida.open("reservaciones.txt");
	for(int i=0; i<contador2;i++){
		dia=reservaciones[i].getFechaReservacion().getDia();
		mes=reservaciones[i].getFechaReservacion().getMes();
		anio=reservaciones[i].getFechaReservacion().getAnio();
		idMaterial=reservaciones[i].getIdMaterial();
		idCliente=reservaciones[i].getIdCliente();

		archivoSalida<<dia<<" "<<mes<<" "<<anio<<" "<<idMaterial<<" "<<idCliente<<endl;
	}
	archivoSalida.close();
	printUpdated();
	cout<<"Las reservaciones han sido actualizadas"<<endl;
	break;	
}//Fin de la opcion 6 (salir y actualizar reservaciones)



}//Cierra el ciclo while del Menu

} //Fin del main