#include <bits/stdc++.h>

using namespace std; 


/*Esta función convierte un entero decimal a binario
en forma de string, y en función de la cantidad de bits
rellena con 0s a la izquierda.
*/

string DecimalABinario(uint64_t x, int bits){
	//recibe entero sin signo de 64 bits, y entero cantidad de bits(minterminos)
	//inicializamos la variable 
	string binario="";
	//mientras reciba un entero...
	while(x!=0){
	
		binario =to_string(x%2)+ binario ; 
		x = x/2; 
	}
	
	int i = binario.size(); 
	while(i<bits){
		binario = "0"+binario; 
		i++;
	}
	

	return binario; 
}


/*Esta función tomada de HackerRank permite filtrar un string 
con comas a un arreglo de strings*/
vector<string> split_string(string input_string, char delimiter) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
    	
    	if(input_string.substr(i, pos - i) != "\0")
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }
	if(input_string.substr(i, pos - i) != "\0")
    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

/*Esta función, a partir de la cadena obtenida, permite 
obtener un vector de enteros con los mintérminos*/

vector<int> ObtenerMinterminos(string cadena){
	//Limpiar cadena de comas
	vector<string> Numeros = split_string(cadena, ','); 
	
	//Obtener un arreglo con los minterminos
	vector<int> Minterminos; 
	int aux; 
	for(int i = 0; i<Numeros.size(); i++){
		
		
		aux = stoi(Numeros[i]); 
		Minterminos.push_back(aux); 
	}
	
	//Ordenar de menor a mayor con Insert Sort
	
	int temp,j; 
	
	for(int i = 1; i<Minterminos.size();i++){
		temp = Minterminos[i]; 
		j = i-1; 
		while(Minterminos[j]>temp && j>=0   ){
			Minterminos[j+1] = Minterminos[j]; 
			j--; 
			Minterminos[j+1] = temp; 
			
		}
		
		
	}
	
	return Minterminos; 
	
	
	
	
}

/*Esta función obtiene la cantidad de bits que se 
van a usar, en función del mintérmino más grande*/
int ObtenerNumeroDeBits(vector<int> Minterminos){
	int i = 0; 
	
	while(pow(2,i)<=Minterminos[Minterminos.size()-1]) i++; 
	
	
	return i; 
}



int ObtenerCantidadDeUnos(string binario){
	int contador = 0; 
	for(int i = 0; i<binario.size(); i++){
		if(binario[i] == '1') contador++; 
		
	}
	
	return contador; 
}



struct datos{
	string Mintermino; 
	string binario; 
	int NoUnos; 
	bool implicantePrimo; 
};

vector<datos> TablaFinal; 

void ImprimirTabla(vector<datos> Tabla){
	
	cout<<"--------------------------------------------"<<endl; 
	for(int i = 0; i<Tabla.size();i++){
	
		cout<<Tabla[i].Mintermino<<" "<<Tabla[i].binario<<" ";
		cout<<Tabla[i].NoUnos<<" "<<Tabla[i].implicantePrimo<<endl; 
		
	}
	
	
}

void ImprimirElemento(datos dato){
	cout<<dato.binario<<" "<<dato.implicantePrimo<<" ";
}

	

vector<datos> ObtenerTabla(vector<int> Minterminos){
	
	vector<datos> Tabla; 
	datos d; 
	int CantidadDeBits = ObtenerNumeroDeBits(Minterminos); 
	/*Aquí se almacenan los datos*/
	
	
	for(int i = 0; i<Minterminos.size();i++){
		//cout<<Minterminos[i]<<" "<<Binarios[i]<<" "<<ObtenerCantidadDeUnos(Binarios[i])<<endl; 
		d.Mintermino = to_string(Minterminos[i]); 
		d.binario = DecimalABinario(Minterminos[i], CantidadDeBits); 
		d.NoUnos = ObtenerCantidadDeUnos(d.binario); 
		d.implicantePrimo = false; 
		
		Tabla.push_back(d); 
	}
	
	//ImprimirTabla(Tabla); 
	/*A partir de este punto ya tenemos la tabla*/
	
	
	/*Ordenamos según la cantidad de unos*/
	datos temp; 
	int j; 
	
	for(int i = 1; i<Tabla.size();i++){
		temp = Tabla[i]; 
		j = i-1; 
		while(Tabla[j].NoUnos>=temp.NoUnos && j>=0   ){
			Tabla[j+1] = Tabla[j]; 
			j--; 
			Tabla[j+1] = temp; 
			
		}
		
		
	}
	
	
	return Tabla; 
	
}
/*Busca en la tabla si todos los elementos son implicantes primos*/
bool ValidarTabla(vector<datos> Tabla){
	bool bandera = true; 
	for(int i= 0; i<Tabla.size(); i++){
		bandera = Tabla[i].implicantePrimo; 
	}
	
	return bandera; 
}

/*Verifica que se diferencíen sólo en 1 bit*/
int ValidarBinario(datos d1, datos d2){
	int contador = 0;  
	for(int i = 0; i<d1.binario.size(); i++){
		if(d1.binario[i] != d2.binario[i]) contador++; 
		
	}
	return contador; 
}

/*crea un binario y le pone el dato de implicante primo en 0
*/
datos Combinar(datos dato1, datos dato2){
	datos dato;
	dato.implicantePrimo = false; 
	
	dato.Mintermino = dato1.Mintermino+"-"+dato2.Mintermino+"-"; 
	dato.NoUnos = stoi(to_string(dato1.NoUnos)+to_string(dato2.NoUnos)); 
	
	string binario = dato1.binario; 
	for(int i = 0; i<dato1.binario.size();i++){
		if(binario[i] != dato2.binario[i]) binario.replace(i,1,"X") ; 
		
	}
	dato.binario = binario; 
	
	return dato; 
}


bool contains(vector<datos> Tabla, datos d1){
	if(Tabla.size() == 0) return false; 
	
	for(int i= 0; i<Tabla.size(); i++){
		
		if(ValidarBinario(d1,Tabla[i]) == 0) return true; 
		//Es decir, encontró un binario exactamente
		//igual a sí mismo
	}
	
	
	
}

void AlgoritmoQuineMcCluskey(vector<datos> Tabla){
	vector<datos> TablaAuxiliar; 
	if(!ValidarTabla(Tabla)){ //Esto quiere decir que no todos son implicantesPrimos
				
		for(int i = 0 ; i<Tabla.size(); i++){
			bool bandera = true; 
			int j = 0; 
			for(j ; j<Tabla.size(); j++){
				
				
				if(ValidarBinario(Tabla[i],Tabla[j]) == 1 ){ // Sí se pudo combinar con al menos 
													        // uno de los otros datos
					bandera = false; 
					if(!contains(TablaAuxiliar,Combinar(Tabla[i],Tabla[j])))
					TablaAuxiliar.push_back(Combinar(Tabla[i],Tabla[j])); 
					Tabla[i].implicantePrimo = false; 
					
					
				}
				
			
			}
			if(bandera){
				
					Tabla[i].implicantePrimo = true; 
				
			}
			
		}
		//Hay que volver a buscar en la Tabla algún implicante primo que haya quedado 
		for(int i = 0; i<Tabla.size(); i++){
			
			if(Tabla[i].implicantePrimo == 1) TablaAuxiliar.push_back(Tabla[i]); 
			
		}
	
		
		AlgoritmoQuineMcCluskey(TablaAuxiliar); 
		
	}else{//Ya todos los datos son implicantes primos
	
		if(Tabla.size() != 0) TablaFinal = Tabla;  
		
	}
	
	
}

struct ImplicantePrimo{
	string Mintermino;
	int NoDeVecesQueSeRepite = 0; 
};

bool contains2(vector<ImplicantePrimo> Tabla1, string M ){
	bool bandera = false; 
	for(int i = 0; i<Tabla1.size();i++ )
		if( M == Tabla1[i].Mintermino ) bandera = true; 
	
	return bandera; 
}


vector<string> AnalizarUltimaTabla(vector<datos> UltimaTabla){
	vector<ImplicantePrimo> Implicantes; 
	
	ImplicantePrimo aux; 
	for(int j = 0; j<UltimaTabla.size(); j++){
	
		vector<string> Minterminos2 = split_string(UltimaTabla[j].Mintermino, '-'); 
		for(int i = 0; i<Minterminos2.size(); i++){
		  if(!contains2(Implicantes,Minterminos2[i])){
		  	aux.Mintermino = Minterminos2[i]; 
		  	aux.NoDeVecesQueSeRepite = 1; 
		  	Implicantes.push_back(aux); 
		  	
		  }else{
		  	for(int k =0; k<Implicantes.size(); k++)
		  		if(Implicantes[k].Mintermino == Minterminos2[i])
		  			Implicantes[k].NoDeVecesQueSeRepite++; 
			  
		  	
		  }
		}
	}
	
	vector<string> TablaFinal; 
	bool bandera = false; 
	
	for(int i = 0; i<UltimaTabla.size(); i++){
		
		vector<string> Minterminos2 = split_string(UltimaTabla[i].Mintermino, '-'); 
		bandera = false; 
		for(int j = 0; j<Minterminos2.size(); j++){
			for(int k = 0; k<Implicantes.size(); k++){
				
				if(Minterminos2[j] == Implicantes[k].Mintermino) 
					if(Implicantes[k].NoDeVecesQueSeRepite<2) bandera = true; 
				
			}
			
			
		}
		if(bandera) TablaFinal.push_back(UltimaTabla[i].binario); 
		
	}
	cout<<"---"<<endl; 
	for(int i = 0 ; i<TablaFinal.size(); i++)
		cout<<TablaFinal[i]<<endl; 
	cout<<"---"<<endl; 
	return TablaFinal; 	
	
		
}

void ConvertirBinariosALetras(vector<string> vector1){
	
    for(int i = 0; i < vector1.size(); i++)
    {
        char letra = 65;
        string auxiliar = vector1[i];
        for(int j = 0; j < auxiliar.size(); j++)
        {
            if(auxiliar[j] == 'X')
            {
                //nada
            }
            else
            {
                if(auxiliar[j] == '0')
                {
                    cout << letra << "'";
                }
                else
                {
                    cout << letra;
                }
            }
            letra = letra + 1;
        }
        if(i != vector1.size() - 1)
        {
            cout << "+";
        }
        else
        {
            cout << " ";
        }
    }
	
	
}

int main(){
	/*Primero se obtienen los minterminos*/
	
	/*Se guardan los mintérminos en un vector de enteros*/
	string cadena; 
	cin>>cadena; 
	vector<int> Minterminos = ObtenerMinterminos(cadena); 
	
	/*Para mayor comididad, trabajaremos con un ejemplo particular*/
	
	
	//vector<int> Minterminos = ObtenerMinterminos("15,11,10,9,7,5,4,3,1");
	
	vector<datos> Tabla = ObtenerTabla(Minterminos);
	
	/*Se crea una tabla como la siguiente (siguiendo el ejemplo guía): 
	
			m     b    N°1s  IP
			1    0001   1    0
			3    0011   2    0
			4    0100   1    0
			5    0101   2    0
			7    0111   3    0
			9    1001   2    0
		   10    1010   2    0
		   11    1011   3    0
		   15    1111   4    0
			
		donde: 
		m =>Mintérmino (int)
		b => binario (string)
		N°1s => Cantidad de unos (int)  
		IP => Implicante Primo (bool) 
		
		
	*/
	cout<<"------------------------------------------------------\n"<<endl; 
	
	
	ImprimirTabla(Tabla); 
	
	//system("pause>nul"); 
	
	
	//-------------A PARTIR DE ESTE PUNTO FUNCIONA TODO-----------------------
	
	/*Comenzamos con la recursividad */
	AlgoritmoQuineMcCluskey(Tabla); 
	
	ImprimirTabla(TablaFinal); 
	
	ConvertirBinariosALetras(AnalizarUltimaTabla(TablaFinal)); 
	
	
	
	return 0; 
}
