class Fecha{
	private:
	int dd;
	int mm;
	int aa;
	

	public:
	Fecha(){
		dd=0;
		mm=0;
		aa=0;
	}

	Fecha(int _dd,int _mm,int _aa){
		dd=_dd;
		mm=_mm;
		aa=_aa;
	}

	void setFecha(int d,int m,int a){dd=d;mm=m,aa=a;}
	int getDia(){return dd;}
	int getMes(){return mm;}
	int getAnio(){return aa;}

	Fecha operator+(int numD){
		int nD=dd+numD;
		int nM=mm;
		int nA=aa;
		if(nD>31){
			nD=nD-31;
			nM=nM+1;
		}
		if(nM>12)
		{
			nM=nM-12;
			nA=nA+1;
		}

		Fecha temporal(nD,nM,nA);
		return temporal;
	}

	bool operator>(Fecha fecha2){
		int dia2=fecha2.dd;
		int mes2=fecha2.mm;
		int anio2=fecha2.aa;

		if(aa>=anio2 && mm>=mes2 && dd>dia2){
			return true;
		}
		return false;	
	
	}

	
	bool operator<(Fecha fecha2){
		int dia2=fecha2.dd;
		int mes2=fecha2.mm;
		int anio2=fecha2.aa;

		if(aa<=anio2 && mm<=mes2 && dd<dia2){
			return true;
		}
		return false;		
	}

	bool operator<=(Fecha fecha2){
		int dia2=fecha2.dd;
		int mes2=fecha2.mm;
		int anio2=fecha2.aa;

		if(aa<=anio2 && mm<=mes2 && dd<=dia2){
					return true;
		}
		return false;		
	}

	bool operator>=(Fecha fecha2){
		int dia2=fecha2.dd;
		int mes2=fecha2.mm;
		int anio2=fecha2.aa;

		if(aa>=anio2 && mm>=mes2 && dd>=dia2){
			return true;
		}
		return false;		
	}

	bool operator==(Fecha fecha2){
		int dia2=fecha2.dd;
		int mes2=fecha2.mm;
		int anio2=fecha2.aa;

		if(aa==anio2 && mm==mes2 && dd==dia2){
					return true;
			}
		return false;	
	
	}

  static string nombreMes(int m){
		string nombres[13]={"SM","Ene","Feb","Mar","Abr","May","Jun","Jul","Ago","Sep","Oct","Nov","Dic"};
		return nombres[m];
	}	

  friend ostream & operator << (ostream &out, const Fecha &f){
		string M=nombreMes(f.mm);
		string nD="0"+to_string(f.dd);
		if(f.dd<10){
  	  out<<nD<<" "<<M<<" "<<f.aa;
		}
		else{
    	out<<f.dd<<" "<<M<<" "<<f.aa;
		}
		return out;
	}

  friend	istream &operator >> (istream &input,Fecha &f) {
		while(f.dd<1 || f.dd>30){
			cout << "Dia (1-30): ";
			input >> f.dd;
		}
		while(f.mm<1 || f.mm>12){
			cout << "Mes (1-12): ";
			input >> f.mm;
		}
		cout << "Año: ";
    input >> f.aa;
    return input;
}

};//Fin de la clase Fecha


class Reserva{
	private:
	int idMaterial;
	int idCliente;
	Fecha fechaReservacion;

	public:
	Reserva(){
		idMaterial=0;
		idCliente=0;
		fechaReservacion=Fecha();
		}

	Reserva(int material,int cliente,Fecha fecha){
		idMaterial=material;
		idCliente=cliente;
		fechaReservacion=fecha;
	}

	Fecha getFechaReservacion(){return fechaReservacion;}
	 Fecha fechaFinReserva(int diasPrestamo){	
	 Fecha temporal;
	 temporal=fechaReservacion+diasPrestamo;
		return temporal;
	};

	int getIdMaterial(){return idMaterial;}
	int getIdCliente(){return idCliente;}

};


class Material{
	private:
	int idMaterial;
	string titulo;

	public:
	int getIdMaterial(){return idMaterial;}
	string getTitulo(){return titulo;}

	Material(){
		idMaterial=0;
		titulo="";
	}

	Material(int _material,string _titulo){
		idMaterial=_material;
		titulo=_titulo;
	}
	
	virtual void muestraDatos()=0;
	virtual int diasPrestamo()=0;
};


class Libro: public Material{
	private:
	int duracion;
	string Genero;

	public:
	Libro(){
		duracion=0;
		Genero="";
	}

	Libro(int _id, string _titulo,int _duracion,string _genero):Material(_id,_titulo){

		duracion=_duracion;
		Genero=_genero;

	}

	void muestraDatos(){
		string id=to_string(getIdMaterial());
		string titulo=getTitulo();
		string contenido[4]={id,titulo,to_string(duracion),Genero};
		formatoTabla1(contenido);
	}

	int diasPrestamo(){return 7;}



};

class Disco: public Material{
	private:
	int numPag;
	string Autor;

	public:
	Disco(){
		numPag=0;
		Autor="";	
	}

	Disco(int _id, string _titulo,int _numPag,string _autor):Material(_id,_titulo){

		numPag=_numPag;
		Autor=_autor;

	}

	void muestraDatos(){
		string id=to_string(getIdMaterial());
		string titulo=getTitulo();
		string contenido[4]={id,titulo,to_string(numPag),Autor};
		formatoTabla1(contenido);
	}

	int diasPrestamo(){return 2;}


};

class Software: public Material{
	private:
	int Version;
	string SO;

	public:
	Software(){
		Version=0;
		SO="";
	}
	Software(int _id, string _titulo, int _version, string _so):Material(_id,_titulo){

		Version=_version;
		SO=_so;
	}

	void muestraDatos(){	
		string id=to_string(getIdMaterial());
		string titulo=getTitulo();
		string contenido[4]={id,titulo,to_string(Version),SO};
		formatoTabla1(contenido);
	}

	int diasPrestamo(){return 1;}


};


//Fin de las Clases


int* reserv(Material* apuntador[],Reserva reservaciones[]){

static int posReservaciones[60];
for(int i=0;i<contador2;i++){
		int materialR=reservaciones[i].getIdMaterial();			
		for(int u=0;u<contador;u++){
			int materialM=apuntador[u]->getIdMaterial();
			if(materialR==materialM){
				posReservaciones[i]=u;
			}
		}
	}
	
	return posReservaciones;

}

 bool validarMaterial(Material* apuntador[],int id){
  int idMaterial;
	for(int i=0;i<contador;i++){
    idMaterial=apuntador[i]->getIdMaterial();
		if(id==idMaterial){
			return true;
		}
	}
	return false;

}

bool validarFecha(Fecha buscarFecha,Reserva reservaciones[],Material* apuntador[]){
	Fecha fInicio;
	Fecha fFinal;
	int* posRes=reserv(apuntador,reservaciones);	
  for(int i=0; i<contador2;i++){
		int cantDias=apuntador[*posRes]->diasPrestamo();
		int idMaterial=apuntador[*posRes]->getIdMaterial();
		fInicio=reservaciones[i].getFechaReservacion();
		fFinal=reservaciones[i].fechaFinReserva(cantDias);
	
		if(buscarFecha>=fInicio && buscarFecha<=fFinal){
			return false;
		}
	posRes++;
	}
	return true;
}


int nSpace(string linea,int max, int titulo){
	int espacio=0;
	if(max>titulo){
		espacio=max-linea.size();
	}
	else{
		espacio=titulo-linea.size();	
	}
	return espacio;
	
}

void formatoTabla2(int pos,string contenido[],Fecha nFecha){

	int sCliente=nSpace("cliente",contenido[0].size(),7);
	int sCliente2=nSpace(contenido[0],contenido[0].size(),7);
	int sMaterial=nSpace("material",contenido[1].size(),7);
	int sMaterial2=nSpace(contenido[1],contenido[1].size(),8);
	
	if(pos==1){
		cout<<mult("▄",11+sCliente)<<endl;
		cout<<"█ Cliente"+mult(" ",sCliente)<<" █"<<endl;
		cout<<"█"<<mult("▀",9+sCliente)<<"█"<<endl;
		cout<<"█ "<<contenido[0]<<mult(" ",sCliente2)<<" █"<<endl;
		cout<<mult("▀",11+sCliente);

	}

	else if(pos==2){
		cout<<mult("▄",23+sCliente+sMaterial)<<endl;
		cout<<"█ Cliente"<<mult(" ",sCliente)<<" █";
		cout<<" Material"<<mult(" ",sMaterial)<<" █"<<endl;
		cout<<"█"<<mult("▀",9+sCliente)<<"█"<<mult("▀",11+sMaterial)<<"█"<<endl;

		cout<<"█ "<<contenido[0]<<mult(" ",sCliente2)<<" █ ";
		cout<<contenido[1]<<mult(" ",sMaterial2)<<" █"<<endl;

		cout<<mult("▀",23+sCliente+sMaterial)<<endl;

	}

	else if(pos==3){
		cout<<mult("▄",37+sCliente+sMaterial)<<endl;
		cout<<"█ Cliente"+mult(" ",sCliente)<<" █";
		cout<<" Material"+mult(" ",sMaterial)<<" █";
		cout<<" Fecha"+mult(" ",7)<<"█"<<endl;

		cout<<"█"<<mult("▀",9+sCliente)<<"█"<<mult("▀",11+sMaterial)<<"█"<<mult("▀",13)<<"█"<<endl;
		cout<<"█ "<<contenido[0]<<mult(" ",sCliente2);
		cout<<" █ "<<contenido[1]<<mult(" ",sMaterial2);
		cout<<" █ "<<nFecha<<" █"<<endl;		
		cout<<mult("▀",37+sCliente+sMaterial)<<endl;
	}

}