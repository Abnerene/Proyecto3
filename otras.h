void wait(){
  cin.ignore();
  cout<<"PRESIONE ENTER PARA CONTINUAR";
  cin.get();
}


void longitudMaxima(int id,string titulo,int dato1,string dato2){	
	
	if(to_string(id).size()>lId){
		lId=to_string(id).size();
	}

	if(titulo.size()>lTitulo){
		lTitulo=titulo.size();
	}

	if(to_string(dato1).size()>lDato1){
		lDato1=to_string(dato1).size();
	}


	if(dato2.size()>lDato2){
		lDato2=dato2.size();
	}
}

string mult(string caracter,int cant){
	string linea="";
	for(int i=0;i<cant;i++){
	linea=linea+caracter;
	}
	return linea;
}

void formatoTabla1(string contenido[]){
 
	int s1=(lId-(contenido[0].size()));
	int s2=(lTitulo-(contenido[1].size()));
	int s3=(lDato1-(contenido[2].size()));
	int s4=(lDato2-(contenido[3].size()));

	cout<<"█ "<<contenido[0]+mult(" ",s1)<<" ";
	cout<<"█ "<<contenido[1]+mult(" ",s2)<<" ";
	cout<<"█ "<<contenido[2]+mult(" ",s3)<<" ";
	cout<<"█ "<<contenido[3]+mult(" ",s4)<<" █"<<endl;	
}

