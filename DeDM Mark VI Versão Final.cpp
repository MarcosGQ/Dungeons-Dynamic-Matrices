/*

DUNGEONS & DYNAMIC MATRICES

Criar um programa o qual:
1- Usuário define tamanho do mapa e dificuldade do jogo;
2- O codigo posiciona paredes e poços de espetos de forma aleatória no mapa;
3- Informa se é possível ou não realizar determinado movimento (por causa das paredes)
4- Informa se o personagem morreu (caiu no poço de espetos)
5- No final, grava: nome do jogador, seu tempo de jogo, dificuldade enfrentada e o tamanho do mapa;

Regras:
1- O codigo não pode criar tantas paredes ou poços ao ponto de não tornar possivel a ida
do ponto de partida ao fim do mapa.
2- o ponto inicial será a posição [0][0], e o final [n-1][n-1], sendo "n" o tamanho do mapa

Limitações:
Pode ser que seja criado um mapa sem saida, não implementei uma varredura de check para esse evento

Para o futuro:
Implementar função para checar se o mapa está sem saida

*/

#include <ctime> // MARCAR O TEMPO
#include <iostream> // CIN / COUT
#include <fstream> // OFSTREAM / IFSTREAM
#include <cstdlib> // SRAND /RAND
#include <locale> // LINGUA PORTUGUESA
using namespace std;

class mapa;
class personagem;

class mapa
{
	private: 
		int n; // tamanho do mapa
		int dificuldade;
		char **m; // ponteiro para ponteiro que "aponta" para o ponteiro de linhas da matriz dinamica
		
	public:
		mapa (int tam, int dif); // construtor
		~mapa (); // destrutor
		int acessivel (int opcao, int a, int b);
		int get_tamanho ();
		int get_dificuldade ();
		void print();
};

class personagem
{
	private:
		mapa *dungeon; // objeto da classe mapa como atributo da classe personagem
		string nome;
		int posicao_i;
		int posicao_j;
		long long tempo_inicio;
		long long tempo_final;
		
	public:
		personagem (string name, int tamm, int diff);
		~personagem ();
		int mover_esquerda ();
		int mover_direita ();
		int mover_cima ();
		int mover_baixo ();
		void vitoria (); // grava nome e tempo de jogo, se vencer
		void derrota (); // grava nome e tempo de jogo, se perder
		void set_posicao (int mov);
		int posicao_atual ();
		void print();
};

// ++++++++++++++++++ IMPLEMENTANDO OS METODOS DA CLASSE MAPA ++++++++++++++++++

mapa::mapa (int tam, int dif) // construtor o qual usuário determina o tamanho da matriz
{										 
	int i, j, obstaculo, contador;
	n= tam;
	dificuldade= dif;
	m= new char *[n]; // nº de linhas da matriz
	
	for(i= 0; i<n; i++)
    {
        m[i]= new char[n]; // nº de colunas da matriz
	}
	
	for(i= 0; i<n; i++) // preenchenco a matriz com '-' (representa espaço vazio)
	{
        for(j= 0; j<n; j++)
        {
		    m[i][j]= '-';
		}
	}
	
	int qtdade_obs= n/2; // qtdade_obs= quantidade de paredes ou poços que podem ser postos em cada linha da matriz
	
	if (dif==1) // modo facil. Há 14,28% de chance de criar um poço de espetos
	{
		for(i= 0; i<n; i++) // percorre linhas
		{
    		contador= 0; // reinicia o contador a cada linha da matriz
			for(j= 0; j<n; j++) // percorre colunas
    		{	    			    		
				obstaculo= rand ( ) % 3; // gera um numero entre 0 a 2
				if (obstaculo>=1 && contador<=qtdade_obs) // Há uma chance de 66,66% de por um obstaculo em cada posição da linha. E ainda
				{								 		  // verifica se ja não foram postos a quantidade maxima de obstaculos permitidos em cada linha
					obstaculo= rand ( ) % 7; // gera um numero entre 0 a 6 (7 chances)
					if (obstaculo>=3 && obstaculo<=5) // 3 chances de por uma parede e 3 chances de deixar o espaço vazio
					{
						m[i][j]= 'p'; // p= parede
						contador++;
					}
					else
					{
						if (obstaculo==6) // 1 chance de por um poço de espetos
						{
							m[i][j]= 'e'; // e= espetos (poço de espetos)
							contador++;
						}
					}	
				}
			}
		}
	}
	else
	{
		if (dif==2) // modo normal. Há 20% de chance de criar um poço de espetos
		{
			for(i= 0; i<n; i++) // percorre linhas
			{
	    		contador= 0; // reinicia o contador a cada linha da matriz
				for(j= 0; j<n; j++) // percorre colunas
	    		{
	    			obstaculo= rand ( ) % 3; // gera um numero entre 0 a 2
					if (obstaculo>=1 && contador<=qtdade_obs) // Há uma chance de 66,66% de por um obstaculo em cada posição da linha. E ainda
	    			{								 		  // verifica se ja não foram postos a quantidade maxima de obstaculos permitidos em cada linha
						obstaculo= rand ( ) % 5; // gera um numero entre 0 a 4 (5 chances)
	    				if (obstaculo==2 || obstaculo==3) // 2 chances de por uma parede e 2 chances de deixar o espaço vazio
	    				{
	    					m[i][j]= 'p'; // p= parede
	    					contador++;
						}
						else
						{
							if (obstaculo==4) // 1 chance de por um poço de espetos
							{
								m[i][j]= 'e'; // e= espetos (poço de espetos)
								contador++;
							}
						}	
					}
				}
			}
		}
		else // modo dificil. Há 33,33% de chance de criar um poço de espetos
		{
			for(i= 0; i<n; i++) // percorre linhas
			{
	    		contador= 0; // reinicia o contador a cada linha da matriz
				for(j= 0; j<n; j++) // percorre colunas
	    		{
	    			obstaculo= rand ( ) % 3; // gera um numero entre 0 a 2
					if (obstaculo>=1 && contador<=qtdade_obs) // Há uma chance de 66,66% de por um obstaculo em cada posição da linha. E ainda
	    			{								 		  // verifica se ja não foram postos a quantidade maxima de obstaculos permitidos em cada linha
						obstaculo= rand ( ) % 3; // gera um numero entre 0 a 4 (5 chances)
	    				if (obstaculo==1) // 1 chance de por uma parede e 1 chance de deixar o espaço vazio
	    				{
	    					m[i][j]= 'p'; // p= parede
	    					contador++;
						}
						else
						{
							if (obstaculo==2) // 1 chance de por um poço de espetos
							{
								m[i][j]= 'e'; // e= espetos (poço de espetos)
								contador++;
							}
						}	
					}	
				}
			}
		}
	}
	m[0][0]= 'x'; // põe um 'x' na primeira posição da matriz, marcando a posição do personagem
	m[0][1]= '-'; // pondo a posição ao lado como vazia pra dar maior chance de poder se movimentar
	m[n-1][n-1]= 's'; // a ultima posição do mapa representa a saida	
}	

mapa::~mapa () // implemento do destrutor
{
	for(int i= 0; i<n; i++)
	{
		delete m[i]; // primeiro deleta as colunas (todos os new char apontados por ponteiro)
	}
    delete m; // depois deleta a linha apontada pelo ponteiro para ponteiro **m
    cout << "\nO objeto foi deletado.\n";
}

int mapa::acessivel (int opcao, int a, int b) // verifica se o lugar pretendido esta dentro do limite da matriz
{										  // e se está vazio ou com poço de espetos
	int i, j, pos_atual_i, pos_atual_j;
	if (a>=0 && a<=n-1 && b>=0 && b<=n-1 && m[a][b]!='p') 
	{						
		for (i= 0; i<n; i++)
		{
			for (j= 0; j<n; j++)
			{
				if (m[i][j]=='x')
				{
					pos_atual_i= i; // varre o mapa para saber qual é a posição atual do personagem
					pos_atual_j= j; // e salva suas coordenadas
				}
			}
		}
		if (opcao==1)
		{	
			if (m[pos_atual_i][pos_atual_j-1]=='-')
			{
				m[pos_atual_i][pos_atual_j-1]= 'x';
				m[pos_atual_i][pos_atual_j]= '-';
				return 1;
			}
			else
			{
				if (m[pos_atual_i][pos_atual_j-1]=='s')
				{
					return 2;
				}
				else
				{
					if (m[pos_atual_i][pos_atual_j-1]=='e')
					{
						return 3;
					}					
				}		
			}
		}
		else
		{
			if (opcao==2)
			{
				if (m[pos_atual_i][pos_atual_j+1]=='-')
				{
					m[pos_atual_i][pos_atual_j+1]= 'x';
					m[pos_atual_i][pos_atual_j]= '-';					
					return 1;
				}
				else
				{
					if (m[pos_atual_i][pos_atual_j+1]=='s')
					{
						return 2;
					}
					else
					{
						if (m[pos_atual_i][pos_atual_j+1]=='e')
						{
							return 3;
						}					
					}		
				}
			}
			else
			{
				if (opcao==3)
				{
					if (m[pos_atual_i-1][pos_atual_j]=='-')
					{
						m[pos_atual_i-1][pos_atual_j]= 'x';
						m[pos_atual_i][pos_atual_j]= '-';
						return 1;
					}
					else
					{
						if (m[pos_atual_i-1][pos_atual_j]=='s')
						{
							return 2;
						}
						else
						{
							if (m[pos_atual_i-1][pos_atual_j]=='e')
							{
								return 3;
							}					
						}		
					}
				}
				else
				{
					if (opcao==4)
					{
						if (m[pos_atual_i+1][pos_atual_j]=='-')
						{
							m[pos_atual_i+1][pos_atual_j]= 'x';
							m[pos_atual_i][pos_atual_j]= '-';
							return 1;
						}
						else
						{
							if (m[pos_atual_i+1][pos_atual_j]=='s')
							{
								return 2;
							}
							else
							{
								if (m[pos_atual_i+1][pos_atual_j]=='e')
								{
									return 3;
								}					
							}		
						}
					}
				}
			}
		}																
	} 
	else 
	{
		return 4;
	}
}

int mapa::get_tamanho ()
{
	return n;
}

int mapa::get_dificuldade ()
{
	return dificuldade;
}

void mapa::print() 
{
	//system("cls"); Esse comando não permite exibir as frases toda vez que tenta se movimentar, exceto
	// as frases de vitoria ou morte. No linux, use "clear" ao inves de "cls".
	for (int i = 0;i< n;i++) 
	{
		for (int j = 0;j< n;j++) 
		{
			if (m[i][j]=='e')
			{
				cout << '-'; // E desse jeito o mapa não imprime os poços de espetos
			}
			else
			{
				cout << m[i][j];
			}
		}
		cout << endl;
	}
}				
// ++++++++++++++++++ IMPLEMENTANDO OS METODOS DA CLASSE PERSONAGEM ++++++++++++++++++
		
personagem::personagem (string name, int tamm, int diff)
{
	nome= name;
	posicao_i= 0;
	posicao_j= 0;
	dungeon= new mapa (tamm, diff);
	tempo_inicio= time (0); // salva o tempo de inicio de jogo
}

personagem::~personagem ()
{
	cout << "\nO objeto da classe personagem foi deletado.\n";
}		
		
int personagem::mover_esquerda ()
{
	return dungeon->acessivel (1, posicao_i, posicao_j-1); // ir para linha 206
}
	
int personagem::mover_direita ()
{
	return dungeon->acessivel (2, posicao_i, posicao_j+1);
}

int personagem::mover_cima ()
{
	return dungeon->acessivel (3, posicao_i-1, posicao_j);
}	

int personagem::mover_baixo ()
{
	return dungeon->acessivel (4, posicao_i+1, posicao_j);
}

void personagem::vitoria ()
{
	tempo_final= time (0);
	tempo_final= tempo_final - tempo_inicio;
	ofstream salva ("G:/Downloads/recordes.txt", ios::app);
	salva << "Nome: " << nome << " - O sobrevivente!.\n";
	salva << "Dificuldade: " << dungeon->get_dificuldade() << ".\n";
	salva << "Tamanho do mapa: " << dungeon->get_tamanho() << ".\n";
	salva << "Tempo de jogo: " << tempo_final << " segundos.\n\n";
	salva.close();	
}

void personagem::derrota ()
{
	tempo_final= time (0);
	tempo_final= tempo_final - tempo_inicio;
	ofstream salva ("G:/Downloads/recordes.txt", ios::app);
	salva << "Nome: " << nome << " - Aquele que morreu espetado!.\n";
	salva << "Dificuldade: " << dungeon->get_dificuldade() << ".\n";
	salva << "Tamanho do mapa: " << dungeon->get_tamanho() << ".\n";
	salva << "Tempo de jogo: " << tempo_final << " segundos.\n\n";
	salva.close();	
}

void personagem::set_posicao (int mov)
{
	if (mov==1)
	{
		posicao_j= posicao_j-1;
	}
	else
	{
		if (mov==2)
		{
			posicao_j= posicao_j+1;
		}
		else
		{
			if (mov==3)
			{
				posicao_i= posicao_i-1;
			}
			else
			{
				if (mov==4)
				{
					posicao_i= posicao_i+1;
				}
			}
		}
	}
}

int personagem::posicao_atual ()
{
	cout << "\nVoce esta nas posições: " << posicao_i << ", " << posicao_j << "\n.";
}

void personagem::print() 
{
	dungeon->print();
}
		
int main ()
{
	srand (time (0));
	setlocale (LC_ALL, "Portuguese");
	int direcao, dificult, tamanho;
	string nome;
	bool flag= true;
	cout << "Voce esta preso em um calabouço cheio de armadilhas com apenas um mapa para navegação,\nmas tem um pequeno problema, esse mapa não revela a posição das armadilhas, boa sorte.\n";
	cout << "\nLegendas do mapa: 'x'-voce, 'p'-parede e 's'-saida\n";
	cout << "Digite seu nome: ";
	cin >> nome;
	cout << "Digite o tamanho do mapa: ";
	cin >> tamanho;
	cout << "Escolha a dificuldade: 1-facil, 2-normal ou 3-dificil: ";
	cin >> dificult;
	personagem jogador (nome, tamanho, dificult);

	while (flag==true)
	{
		jogador.print();
		cout << "\nEscolha uma direção: 1-esquerda, 2-direita, 3-cima ou 4-baixo.\nOu digite 5 para visualizar sua posição atual.\nDigite: ";
		cin >> direcao;
		if (direcao==1)
		{
			direcao= jogador.mover_esquerda (); // ir para linha 360
			if (direcao==1)
			{
				jogador.set_posicao (1);
				cout << "\nVoce se deslocou uma casa para a esquerda.\n";	
			}
			else
			{
				if (direcao==2)
				{
					cout << "\nVoce se deslocou uma casa para a esquerda e encontrou a saida. Voce venceu o jogo, parabens!\n";
					jogador.vitoria();
					flag= false;
				}
				else
				{
					if (direcao==3)
					{
						cout << "\nVoce se deslocou uma casa para a esquerda e caiu em um poço cheio de espetos.\nVoce morreu!!!\n";
						jogador.derrota();
						flag= false;
					}
					else // direcao==4
					{
						cout << "\nNão é possível se movimentar, há uma parede.\n";
					}
				}
			}
		}
		else
		{
			if (direcao==2)
			{
				direcao= jogador.mover_direita ();
				if (direcao==1)
				{
					jogador.set_posicao (2);
					cout << "\nVoce se deslocou uma casa para a direita.\n";	
				}
				else
				{
					if (direcao==2)
					{
						cout << "\nVoce se deslocou uma casa para a direita e encontrou a saida. Voce venceu o jogo, parabens!\n";
						jogador.vitoria();
						flag= false;
					}
					else
					{
						if (direcao==3)
						{
							cout << "\nVoce se deslocou uma casa para a direita e caiu em um poço cheio de espetos.\nVoce morreu!!!\n";
							jogador.derrota();
							flag= false;
						}
						else // direcao==4
						{
							cout << "\nNão é possível se movimentar, há uma parede.\n";
						}
					}
				}
			}
			else
			{
				if (direcao==3)
				{
					direcao= jogador.mover_cima ();
					if (direcao==1)
					{
						jogador.set_posicao (3);
						cout << "\nVoce se deslocou uma casa para cima.\n";	
					}
					else
					{
						if (direcao==2)
						{
							cout << "\nVoce se deslocou uma casa para cima e encontrou a saida. Voce venceu o jogo, parabens!\n";
							jogador.vitoria();
							flag= false;
						}
						else
						{
							if (direcao==3)
							{
								cout << "\nVoce se deslocou uma casa para cima e caiu em um poço cheio de espetos.\nVoce morreu!!!\n";
								jogador.derrota();
								flag= false;
							}
							else // direcao==4
							{
								cout << "\nNão é possível se movimentar, há uma parede.\n";
							}
						}
					}
				}
				else
				{
					if (direcao==4)
					{
						direcao= jogador.mover_baixo ();
						if (direcao==1)
						{
							jogador.set_posicao (4);
							cout << "\nVoce se deslocou uma casa para baixo.\n";	
						}
						else
						{
							if (direcao==2)
							{
								cout << "\nVoce se deslocou uma casa para baixo e encontrou a saida. Voce venceu o jogo, parabens!\n";
								jogador.vitoria();
								flag= false;
							}
							else
							{
								if (direcao==3)
								{
									cout << "\nVoce se deslocou uma casa para baixo e caiu em um poço cheio de espetos.\nVoce morreu!!!\n";
									jogador.derrota();
									flag= false;
								}
								else // direcao==4
								{
									cout << "\nNão é possível se movimentar, há uma parede.\n";
								}
							}
						}	
					}
					else
					{
						cout << jogador.posicao_atual ();
					}
				}
			}
		}
	}
}

