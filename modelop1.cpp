///Ejercicio:
///Autor:DEK
///Fecha:
///Comentario:

# include<iostream>
# include<cstdlib>
# include<cstring>

using namespace std;


void cargarCadena(char *pal, int tam){
  int i;
  fflush(stdin);
  for(i=0;i<tam;i++){
      pal[i]=cin.get();
	  if(pal[i]=='\n') break;
	  }
  pal[i]='\0';
  fflush(stdin);
}


class Empresa{
private:
    int numeroEmpresa;
    char nombreEmpresa[30];
    int cantidadEmpleados;
    int categoria;
    int municipio;
    bool estado;
public:
    int getNumeroEmpresa(){return numeroEmpresa;}
    const char *getNombreEmpresa(){return nombreEmpresa;}
    int getCantidadEmpleados(){return cantidadEmpleados;}
    int getCategoria(){return categoria;}
    int getMunicipio(){return municipio;}
    bool getEstado(){return estado;}

    void setNumeroEmpresa(int nE){numeroEmpresa=nE;}
    void setNombreEmpresa(const char *nE){strcpy(nombreEmpresa,nE);}
    void setCantidadEmpleados(int cE){cantidadEmpleados=cE;}
    void setCategoria(int c){categoria=c;}
    void setMunicipio(int m){municipio=m;}
    void setEstado(bool e){estado=e;}

    void Cargar(int nE=-1);

    void Mostrar();

    bool leerDeDisco(int pos);
    bool grabarEnDisco();
    bool modificarEnDisco(int pos);
};

bool Empresa::leerDeDisco(int pos){ //pos es la posición que ocupa el registro en el archivo, empezando por 0
    FILE *p;
    p=fopen("empresas.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Empresa), 0); ///sizeof (Empresa) es el tamaño en bytes de un objeto Empresa en memoria
    bool leyo = fread(this, sizeof (Empresa), 1, p);
    fclose(p);
    return leyo;
}

bool Empresa::grabarEnDisco(){
    FILE *p;
    p=fopen("empresas.dat","ab");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (Empresa), 1, p);
    fclose(p);
    return escribio;
}

bool Empresa::modificarEnDisco(int pos){
    FILE *p;
    p=fopen("empresas.dat","rb+");
    if(p==NULL) return false;
    fseek(p, pos * sizeof(Empresa), 0);
    bool escribio=fwrite(this, sizeof (Empresa), 1, p);
    fclose(p);
    return escribio;
}

void Empresa::Cargar(int nE){
    if(nE==-1){
        cout<<"NUMERO DE EMPRESA: ";
        cin>>numeroEmpresa;
    }
    else{
        numeroEmpresa=nE;
    }
    cout<<"NOMBRE: ";
    cargarCadena(nombreEmpresa,29);
    cout<<"CANTIDAD DE EMPLEADOS: ";
    cin>>cantidadEmpleados;
    cout<<"CATEGORIA: ";
    cin>>categoria;
    cout<<"MUNICIPIO: ";
    cin>>municipio;
    estado=true;
    cout<<endl;

}

void Empresa::Mostrar(){
    if(estado==true){
        cout<<"NUMERO DE EMPRESA: ";
        cout<<numeroEmpresa<<endl;
        cout<<"NOMBRE: ";
        cout<<nombreEmpresa<<endl;
        cout<<"CANTIDAD DE EMPLEADOS: ";
        cout<<cantidadEmpleados<<endl;
        cout<<"CATEGORIA: ";
        cout<<categoria<<endl;
        cout<<"MUNICIPIO: ";
        cout<<municipio<<endl;
    }
}

class Municipio{
private:
    int numero;
    char nombreMunicipio[30];
    int seccion, cantidadHabitantes;
    bool estado;
public:
    int getSeccion(){return seccion;}
    //gets() para todas las propiedades
	//sets() para todas las propiedades
	bool leerDeDisco(int pos){
        return true;
	}
};

class Categoria{
private:
    int numeroCategoria;
    char nombreCategoria[30];
    bool esencial;
 bool estado;
public:
    int getCategoria(){return numeroCategoria;}
    bool getEsencial(){return esencial;}
    //gets() para todas las propiedades
	//sets() para todas las propiedades
	bool leerDeDisco(int pos){
        return true;
	}
};

class EmpresaEsencial{
private:
    int numeroEmpresa;
    char nombreEmpresa[30];
    int cantidadEmpleados;
    bool estado;
public:
    int getNumeroEmpresa(){return numeroEmpresa;}
    const char *getNombreEmpresa(){return nombreEmpresa;}
    int getCantidadEmpleados(){return cantidadEmpleados;}
    bool getEstado(){return estado;}

    void setNumeroEmpresa(int nE){numeroEmpresa=nE;}
    void setNombreEmpresa(const char *nE){strcpy(nombreEmpresa,nE);}
    void setCantidadEmpleados(int cE){cantidadEmpleados=cE;}
    void setEstado(bool e){estado=e;}

    bool grabarEnDisco();
};

bool EmpresaEsencial::grabarEnDisco(){
    FILE *p;
    p=fopen("empresaE.dat","ab");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (EmpresaEsencial), 1, p);
    fclose(p);
    return escribio;
}

void puntoA();
    void mostrarVector(int *v, int tam);
void puntoB();
void puntoC();
    bool esEsencial(int cat);

int main(){
    puntoA();
    puntoB();
    puntoC();
	cout<<endl;
	system("pause");
	return 0;
}



void puntoA(){
    Municipio obj;
    int pos=0, vMuniSeccion[9]={0};
    while(obj.leerDeDisco(pos)){
        vMuniSeccion[obj.getSeccion()-1]++;
    }
    mostrarVector(vMuniSeccion, 9);
}


void mostrarVector(int *v,int tam){


}

void puntoB(){
        Empresa obj;
        int pos=0;
        while(obj.leerDeDisco(pos++)){
            if(obj.getCantidadEmpleados()>200){
                cout<<obj.getNombreEmpresa()<<endl;
            }
        }
}

void puntoC(){
        Empresa obj;
        EmpresaEsencial reg;
        int pos=0;
        while(obj.leerDeDisco(pos++)){
            if(esEsencial(obj.getCategoria())==true){
                reg.setNombreEmpresa(obj.getNombreEmpresa());
                reg.setNumeroEmpresa(obj.getNumeroEmpresa());
                reg.setCantidadEmpleados(obj.getCantidadEmpleados());
                reg.setEstado(true);
                reg.grabarEnDisco();
            }
        }
}

bool esEsencial(int cat){
    Categoria aux;
    int pos=0;
    while(aux.leerDeDisco(pos++)){
        if(aux.getCategoria()==cat) return aux.getEsencial();
    }
    return false;
}
/*

void puntoC2(){
        Empresa obj;
        EmpresaEsencial reg;
        bool categorias[80];
        cargarCategorias(categorias);
        int pos=0;
        while(obj.leerDeDisco(pos++)){
            if(categorias[obj.getCategoria()-1]==true){
                reg.setNombreEmpresa(obj.getNombreEmpresa());
                reg.setNumeroEmpresa(obj.getNumeroEmpresa());
                reg.setCantidadEmpleados(obj.getCantidadEmpleados());
                reg.setEstado(true);
                reg.grabarEnDisco();
            }
        }
}

void cargarCategorias(bool *cat){
    Categoria aux;
    int pos=0;
    while(aux.leerDeDisco(pos++)){
        cat[aux.getNumeroCategoria()-1]=aux.getEsencial();
    }
    return false;
}



*/

// b) Calcular e informar por cada mes la cantidad de billetes vendidos

class loteria{
private:
int codigoDeSorteo;
int mesSorteo;
int codigoProvinciaBillete;
public:
bool leerDeDisco(int pos);



};


bool loteria::leerDeDisco(int pos){ //pos es la posición que ocupa el registro en el archivo, empezando por 0
    FILE *p;
    p=fopen("empresas.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Empresa), 0); ///sizeof (Empresa) es el tamaño en bytes de un objeto Empresa en memoria
    bool leyo = fread(this, sizeof (Empresa), 1, p);
    fclose(p);
    return leyo;

}

void ejercicioB(){
int vecProvincias[24];




}
















