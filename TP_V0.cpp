#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>
time_t tiempo = time(0);
struct tm *tlocal = localtime(&tiempo);
char fecha_hoy[9];


struct conductor
{
	int conductorID;
    char fecha_vencimiento[9];
    bool activo ;
    int total_infraciones;
    char email[25];
    float montos;
};

struct infraccion
{
    int infraccionID;
    char fechaHora[14];
    int monto;
    int conductor;
    char provincia[20];
};

using namespace std;
conductor  vecconductor[5];


void datosdeprueba()
{
    FILE *fc;
    conductor p[20];
    p[0].conductorID=1560;
    strcpy(p[0].fecha_vencimiento,"20201017");
    p[0].activo=true;
    p[0].total_infraciones=2;
    strcpy(p[0].email,"asencio@gmail.com");
   
    p[1].conductorID=3464;
    strcpy(p[1].fecha_vencimiento,"20200912");
    p[1].activo=true;
    p[1].total_infraciones=1;
    strcpy(p[1].email,"carlos12@gmail.com");
    
    p[2].conductorID=1265;
    strcpy(p[2].fecha_vencimiento,"20191015");
    p[2].activo=false;
    p[2].total_infraciones=5;
    strcpy(p[2].email,"juan@gmail.com");

    if (fc=fopen("conductores.bin","wb"))
    {
        fwrite(p, sizeof(conductor),3,fc);
        fclose(fc);
    }
    
    FILE *pb;
    infraccion f[20];
    f[0].infraccionID=1590;
    strcpy(f[0].fechaHora,"2014101111:45");
    f[0].monto= 200;
    f[0].conductor=1560;
    strcpy(f[0].provincia,"salta");
    
    f[1].infraccionID=1402;
    strcpy(f[1].fechaHora,"2019101110:20");
    f[1].monto= 100;
    f[1].conductor=1265;
    strcpy(f[1].provincia,"buenos aires");
    
    f[2].infraccionID=4060;
    strcpy(f[2].fechaHora,"2020101615:30");
    f[2].monto= 400;
    f[2].conductor=3464;
    strcpy(f[2].provincia,"rosario");
   
    if (pb=fopen("infracciones.bin","wb"))
    {
        fwrite(f, sizeof(infraccion),3,pb);
        fclose(pb);
    }
    return;
}

bool cargar_conductor(void)
{
	int temp=0;
	struct conductor cond;
	cout<<"ingrese el ID del conductor:"<<endl;;
	cin>>cond.conductorID;
	cout<<"ingrese la fecha en formato (aaaammdd):"<<endl;
	fflush(stdin);
	cin>>cond.fecha_vencimiento;
	cout<<"ingrese el estado 1 para verdadero 0 para falso:"<<endl;
	fflush(stdin);
	cin>>temp;
	cond.activo= temp;
	cout<<"ingrese el mail:" <<endl;
	fflush(stdin);
	cin>>cond.email;
	cout<<"ingrese las infracciones:"<<endl;
	fflush(stdin);
	cin>>cond.total_infraciones;
	FILE *fc=fopen("conductores.bin","ab");
	if(fc!=NULL)
	{
		fwrite(&cond,sizeof(conductor),1,fc);
		fclose(fc);	
		return true;
	}
	return false;
}

void desactivar_conductor()
{
	int temp=0;
	int conduc=0;
	struct conductor cond;
	cout<<"ingrese el ID del conductor "<<endl;
	cin>>conduc;
	FILE *fc= fopen("conductores.bin","rb+");
	int existe=0;
    fread(&cond, sizeof(conductor), 1, fc);
    while(!feof(fc))
    {
    	if(conduc==cond.conductorID)
    	{
    	   cond.activo=temp;
           fseek(fc,(-1)*sizeof(conductor), SEEK_CUR);
           fwrite(&cond ,sizeof(conductor), 1, fc);
           cout<<"Se ha desactivado el conductor"<<endl;
           existe=1;
           break;
		}
		fread(&cond, sizeof(conductor), 1, fc);
    }
    if (existe==0)
    {
    cout<<"no existe ID del conductor con dicho codigo"<<endl;
   }
    fclose(fc);
}

void buscar_conductor_porID()
{
	int temp=0;
	struct conductor cond;
	int conduc=0;
	cout<<"ingrese el ID del conductor "<<endl;
	cin>>conduc;
	FILE *fc=fopen("conductores.bin","rb");
	int existe=0;
    fread(&cond, sizeof(conductor), 1, fc);
    while(!feof(fc))
    {
    	if(conduc==cond.conductorID)
    	{
    	   temp=cond.activo;
    	   cout<<"ID:"<<cond.conductorID <<endl;
    	   cout<<"Fecha de vencimiento(aaaammdd):"<<cond.fecha_vencimiento <<endl;
    	   cout<<"Infracciones: "<< cond.total_infraciones<<endl;
    	   if(cond.activo==1)
    	   cout<<"Estado:" << "activo"<<endl;
    	   else
    	   cout<<"Estado:" << "no activo"<<endl;
    	   cout<<"Email:"<< cond.email<<endl;
           existe=1;
           break;
		}
		fread(&cond, sizeof(conductor), 1, fc);
    }
    if (existe==0)
    {
    cout<<"No existe ID del conductor con dicho codigo \n"<<endl;
   }
    fclose(fc);
	
}
void buscar_conductor_porEmail()
{
	int temp=0;
	struct conductor cond;
	char emailc[25];
	cout <<"ingrese el email del conductor"<<endl ;
	cin>>emailc;
	FILE *fc=fopen("conductores.bin","rb");
	int existe=0;
    fread(&cond, sizeof(conductor), 1, fc);
    while(!feof(fc))
    {
    	if (strcmp(emailc,cond.email) == 0) 
    	{
    	   temp=cond.activo;
    	   cout<<"**** DATOS DEL CONDUCTOR ****"<<endl;
    	   cout<<"ID: "<<cond.conductorID <<endl;
    	   cout<<"Fecha de vencimiento(aaaammdd): "<<cond.fecha_vencimiento <<endl;
    	   cout<<"Infracciones: "<< cond.total_infraciones<<endl;
    	   if(cond.activo==1)
    	   cout<<"Estado: " << "activo"<<endl;
    	   else
    	   cout<<"Estado: " << "no activo"<<endl;
    	   cout<<"Email: "<< cond.email<<endl;
           existe=1;
           break;
		}
		fread(&cond, sizeof(conductor), 1, fc);
    }
    if (existe==0)
    {
    cout<<"No existe el email del conductor"<<endl;
   }
    fclose(fc);
	
}
int levantar_conductor(void)
{
	int i=0;
	struct conductor cond;
	FILE *fc;
	if(fc=fopen("conductores.bin","rb"))
	{

	fread(&cond,sizeof(conductor),1,fc);
	while (!feof(fc))
	{
		
		vecconductor[i].conductorID=cond.conductorID;
		strcpy(vecconductor[i].fecha_vencimiento, cond.fecha_vencimiento);
		strcpy(vecconductor[i].email, cond.email);
		vecconductor[i].total_infraciones=cond.total_infraciones;
		vecconductor[i].activo=cond.activo;
		i++;
		fread(&cond,sizeof(conductor),1,fc);
	}
	fclose(fc);
	return 1;
}
return 0;
}

void finalizar_jornada()
{
  tiempo=time(NULL);
  tlocal=localtime(&tiempo);
  strftime(fecha_hoy, 9, "%Y%m%d", tlocal);
  cout<<"fecha hoy:"<<fecha_hoy<<endl;
  int i=0;
  string fechahoy=fecha_hoy;
  string fecven="";
  FILE *fc =fopen("conductores.bin","rb+");
  struct conductor cond;
  fread(&cond,sizeof(conductor),1,fc);
  while (!feof(fc))
	{
		if(cond.conductorID!=0)
		{
		bool flag=false;
		for(i=0;i<5;i++)
		{
			if(vecconductor[i].conductorID==cond.conductorID)
			{
				cout<<"conductor "<<cond.conductorID<<endl;
				fecven=vecconductor[i].fecha_vencimiento;
				if (strcmp(vecconductor[i].fecha_vencimiento,cond.fecha_vencimiento) != 0)
				{
					if(cond.activo==true )
					{
						cout<<"conductor se modifica"<<cond.conductorID<<endl;
						cond.total_infraciones=vecconductor[i].total_infraciones;
			            fseek(fc,(-1)*sizeof(conductor), SEEK_CUR);
                        fwrite(&cond, sizeof(conductor), 1, fc);
					}
				}
		
			}
		
	   }
       }
			
			fread(&cond,sizeof(conductor),1,fc);
	}
	fclose(fc);
}


void procesar_lote()
{
	FILE *pc,*pb;
	pc=fopen ("procesados.bin", "ab");
	pb=fopen("infracciones.bin","rb");
	if(pb=fopen("infracciones.bin","rb"))
	{
	struct infraccion infra;
	fread(&infra,sizeof(infraccion),1,pb);
	while(!feof(pb))
    {
    	int i=0;
    	bool control=false;
    	while(control==false)
    	{
    		if(vecconductor[i].conductorID==infra.conductor)
    		{
    			vecconductor[i].total_infraciones=vecconductor[i].total_infraciones+1;
    			vecconductor[i].montos=vecconductor[i].montos+infra.monto;
    			control=true;

			}
			else
			{
				if(i==5)
				{
					control=true;
				}
				else
				{
					i++;
				}
			}	
		}
		fwrite(&infra, sizeof(infraccion),1,pc);
		fread(&infra, sizeof(infraccion), 1, pb);
    }
	
	fclose(pc);
	fclose(pb);
	cout<<"proceso completado exitosamente" <<endl;
    }
    else
    {
    	cout<<"proceso no completado" <<endl;
	}
}

void Mostrarconductores_infraccion()
{
    int i;
    for (i=0;i<5;i++)
    {
    	if(vecconductor[i].total_infraciones>0)
    	{
    	cout << "******ID conductor" <<vecconductor[i].conductorID<< " ********" <<endl;
        cout << "Fecha de vencimiento: " << vecconductor[i].fecha_vencimiento << endl;
        cout << "Email " <<vecconductor[i].email << endl;
        cout << "Infracciones: " << vecconductor[i].total_infraciones<< endl;
        if(vecconductor[i].activo==true)
        {
        	 cout << "activo" << endl;
		}
		else
		{
        cout <<"no activo"<<endl;
		}
	}
       
    }
}

void Mostrarconductor(int IDconductor)
{
    int i;
    for (i=0;i<5;i++)
    {
    	if(vecconductor[i].conductorID==IDconductor)
    	{
    	cout << "******ID conductor:" << vecconductor[i].conductorID<< " ********" <<endl;
        cout << "fecha de vencimiento: " << vecconductor[i].fecha_vencimiento << endl;
        cout << "email " <<vecconductor[i].email << endl;
        cout << "infracciones: " << vecconductor[i].total_infraciones<< endl;
        cout<<"montos:"<<vecconductor[i].montos <<endl;
        if(vecconductor[i].activo==true)
        	 cout << "activo" << endl;
		else
			cout <<"no activo"<<endl;
		}
    }
}



char menu()
{
    char opcion;
    cout << " ***** Seleccione una opcion *****:" << endl;
    cout << "1 - levantar los conductores del archivo" << endl;
    cout << "2 - cargar un nuevo conductor"<< endl;
    cout << "3 - desactivar un conductor existente"<< endl;
    cout << "4 - buscar un conductor por ID o email"<< endl;
    cout << "5 - Listar el total de infracciones de un conductor con el total del monto adeudado por dichas infracciones."<< endl;
    cout << "6 - listar todos los conductores que tengan al menos una infraccion" << endl;
    cout << "7 - procesar un lote de infracciones"<<endl;
    cout << "8 - finalizar jornada"<<endl; 
    cout << "9 - crear archivo con datos de prueba"<<endl;
    cout << "Esc - Salir ";
    cout<<endl;
    do
        cin>>opcion;
    while (!(opcion > '0' && opcion < '10') && (opcion != 27));
    
    switch (opcion)
    {
        case '1':
            if (!levantar_conductor()) 
            {
            	 cout << "Error al intentar abrir el archivo." << endl;
			}
            else
            {
            	cout<<"el archivo fue levantado con exito." <<endl;
			}
        break;
        case '2':
           if (cargar_conductor()) 
                cout << "El registro se ha guardado con exito." << endl;
            else
                cout << "Error al intentar abrir el archivo." << endl;

        break;
        case '3':
            desactivar_conductor();
        break;
        case '4':
        {
				int c=0;
           cout << "Ingrese 1 busqueda por email, 2 busqueda por ID" << endl;
           cin>>c;
           if(c==1)
           {
           	buscar_conductor_porEmail();
		   }
		   else 
		   {
		   	if(c==2)
		   	{
		   			buscar_conductor_porID();
		   		
			   }
		   }
	     }
        break;
        case '5':
        	int IDconductor;
        	cout<<"ingrese el conductor que desea saber su monto"<<endl;
        	cin>>IDconductor;
        	Mostrarconductor(IDconductor);
            
        break;
        case '6':
            Mostrarconductores_infraccion();
        break;
        case '7':
            procesar_lote();
        break;
        case '8':
            finalizar_jornada();
            cout<<"se ha procesado el archivo de conductores"<<endl;
        break;
        case '9':
            datosdeprueba();
            cout << "Se creo un nuevo archivo (conductores/infracciones)" << endl;
        break;

    }
    return opcion;
}


    int main ()
{ 

char out;
    do
        out = menu();
    while (out != 27);


return 0;
}

