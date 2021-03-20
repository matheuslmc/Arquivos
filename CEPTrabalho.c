#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};




int buscaBinaria(FILE *f, char *bCep,long ini,long fim,int cont){  

	Endereco e;
	long meio;
	rewind(f);												
	if(ini <= fim){

		int qt;	

		cont++;

		meio = (ini+fim)/2;

		

		fseek(f,(meio*sizeof(Endereco)),SEEK_SET);

		qt = fread(&e, sizeof(Endereco), 1, f);
		

		if(strncmp(bCep,e.cep,8) == 0){
			printf("\nLogradouro: %.72s\nBairro: %.72s\nCidade: %.72s\nUF: %.72s\nSigla: %.2s\nCEP: %.8s\n\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			return cont;
		}
		else{
			if(strncmp(bCep,e.cep,8) > 0){
				buscaBinaria(f,bCep,meio+1,fim,cont);
			}
			else if(strncmp(bCep,e.cep,8) < 0){
				buscaBinaria(f,bCep,ini,meio-1,cont);
			}

		}

	}
	else{
		
		printf("Cep não achado");
		return cont;

	}

}

int buscaNaoBinaria(FILE *f, char *bCep,int cont){

	rewind(f);												
	Endereco e;
	int qt;		
	qt = fread(&e,sizeof(Endereco),1,f);

	while(qt > 0){

		cont++;
		if(strncmp(bCep,e.cep,8) == 0){
			printf("\n\nLogradouro: %.72s\nBairro: %.72s\nCidade: %.72s\nUF: %.72s\nSigla: %.2s\nCEP: %.8s\n\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;

		}
	
		qt = fread(&e,sizeof(Endereco),1,f);		
	
	}

	return cont;

}

int main(int argc, char**argv){
	
	FILE *f;								
	long posicao, primeiro, ultimo, meio;
	char bCep[8];

	if(argc != 2){											
		printf("Qual Cep?:\n");
		int i = 0;
		while(i < 8){
			bCep[i++] = getchar();
		}
	}
	else{

		strncpy(bCep,argv[1],8);

	}

	f = fopen("cep_ordenado.dat","r");						

	fseek(f,0,SEEK_END);									
	posicao = ftell(f);										
	printf("Tamanho do Arquivo: %ldBytes\n", posicao);
	printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n", posicao/sizeof(Endereco));
	
	primeiro = 0;
	ultimo = (posicao/sizeof(Endereco))-1;

	
	printf("BUSCA BINÁRIA");
	printf("Numero de iterações: %d\n",buscaBinaria(f, bCep,primeiro, ultimo,0));
	

	printf("BUSCA NÃO BINÁRIA\n\n");
	printf("Numero de iterações: %d\n",buscaNaoBinaria(f, bCep,0));
	

	return 0;
}
