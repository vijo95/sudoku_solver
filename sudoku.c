#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Posibilidades
{
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
	int g;
	int h;
	int l;
};

struct DosCandidatos
{
	int p;
	int q;
};

typedef struct Posibilidades posibles;
typedef struct DosCandidatos doscandis;

void print_mat_3d(int sudoku[9][3][3]);
void init_posibles(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3]);
void anotar_candidatos(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k);
void sudoku_solver(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3]);
void posicion_unica(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i,int j, int k);
void candidato_unico(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i,int j, int k);
void poner_cero_posibles(posibles sudoku_posibles[9][3][3],int i, int j, int k);
void descartar_todos_candidatos(posibles sudoku_posibles[9][3][3],int i, int j, int k,int num);
void descartar_candidato(posibles sudoku_posibles[9][3][3],int i,int j, int k,int num);
void linea_de_candidatos(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j, int k);
void descartar_fila(posibles sudoku_posibles[9][3][3],int i,int x,int n);
void descartar_columna(posibles sudoku_posibles[9][3][3],int i,int y,int n);
void pareja_desnuda(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i,int j, int k);
void locked_candidate(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i,int j, int k);

doscandis extraer_dos_candidatos(posibles sudoku_posibles[9][3][3],int i, int j, int k);

bool existe_otro_igual_columna(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int k,int n);
bool no_existe_otro_igual_otras_columnas(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int k,int n);
bool existe_otro_igual_fila(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int k,int n);
bool no_existe_otro_igual_otras_filas(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int k,int n);
bool sus_unicos_candidatos(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k, int n, int m);
bool existen_otros_dos_candidatos_fila(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k, doscandis candidatos);
bool existen_otros_dos_candidatos_columna(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k, doscandis candidatos);
bool existen_otros_dos_candidatos_matriz(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k, doscandis candidatos);
bool tiene_solo_dos_candidatos(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j, int k);
bool no_existen_otros_candidatos_matriz_fila(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int n);
bool no_existen_otros_candidatos_matriz_columna(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int k,int n);
bool existen_otros_candidatos_columna(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j, int k,int n);
bool existen_otros_candidatos_fila(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j, int k,int n);
bool puedo_insertar_num(int sudoku[9][3][3],int i, int j,int k,int num);
bool existen_ceros(int sudoku[9][3][3]);
bool unico_para_insertar(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j,int k,int num);
bool es_candidato(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int k,int num);


int main(int argc, char const *argv[])
{
	int i,j,k,n = 0;				// HARD
	int sudoku[9][3][3] = {
							 {{0,7,0},
						    {0,0,0},	// 1
						    {0,0,9}},

						   {{0,0,3},
						    {5,0,0},	// 2
						    {0,4,0}},

						   {{0,0,8},
						    {0,2,0},	// 3
						    {1,0,0}},
// -------------------------------------------------------------- //
						   {{2,0,0},
						    {0,0,0},	// 4
						    {0,0,1}},

						   {{0,0,6},
						    {0,7,0},	// 5
						    {0,0,0}},

						   {{0,0,4},
						    {3,0,0},	// 6
						    {0,5,0}},
// -------------------------------------------------------------- //
						   {{0,0,0},
						    {0,3,0},	// 7
						    {0,0,5}},

						   {{0,0,2},
						    {1,0,0},	// 8
						    {0,8,0}},

						   {{0,0,9},
						    {0,7,5},	// 9
						    {6,0,0}}};

	posibles sudoku_posibles[9][3][3];
	init_posibles(sudoku,sudoku_posibles);

	printf("\n");
	print_mat_3d(sudoku);
	printf("\n");

	while(existen_ceros(sudoku) && i <80)
	{
		sudoku_solver(sudoku,sudoku_posibles);
		i++;
	}

	printf("  ==========================================\n\n");
	printf("\t\t || -- %d -- ||\n",i);
	print_mat_3d(sudoku);

	return 0;
}

void sudoku_solver(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3])
{
	int i,j,k;

	for(i = 0; i<9; i++)
	{
		for(j = 0; j<3; j++)
		{
			for(k = 0; k<3; k++)
			{
				posicion_unica(sudoku,sudoku_posibles,i,j,k);
				candidato_unico(sudoku,sudoku_posibles,i,j,k);
				linea_de_candidatos(sudoku,sudoku_posibles,i,j,k);
				pareja_desnuda(sudoku,sudoku_posibles,i,j,k);
				locked_candidate(sudoku,sudoku_posibles,i,j,k);
			}
		}
	}
}

void posicion_unica(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k)
{
	int counter,num;
	counter = 0;

	if(sudoku_posibles[i][j][k].a == 1)
	{
		counter++;
		num = 1;
	}
	if(sudoku_posibles[i][j][k].b == 2)
	{
		counter++;
		num = 2;
	}
	if(sudoku_posibles[i][j][k].c == 3)
	{
		counter++;
		num = 3;
	}
	if(sudoku_posibles[i][j][k].d == 4)
	{
		counter++;
		num = 4;
	}
	if(sudoku_posibles[i][j][k].e == 5)
	{
		counter++;
		num = 5;
	}
	if(sudoku_posibles[i][j][k].f == 6)
	{
		counter++;
		num = 6;
	}
	if(sudoku_posibles[i][j][k].g == 7)
	{
		counter++;
		num = 7;
	}
	if(sudoku_posibles[i][j][k].h == 8)
	{
		counter++;
		num = 8;
	}
	if(sudoku_posibles[i][j][k].l == 9)
	{
		counter++;
		num = 9;
	}

	if(counter == 1 && sudoku[i][j][k] == 0)
	{
		sudoku[i][j][k] = num;
		descartar_todos_candidatos(sudoku_posibles,i,j,k,num);
		poner_cero_posibles(sudoku_posibles,i,j,k);
	}
}

void candidato_unico(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i,int j, int k)
{
	int num;
	for(num = 1; num < 10; num++)
	{
		if(es_candidato(sudoku,sudoku_posibles,i,j,k,num) && sudoku[i][j][k] == 0 && unico_para_insertar(sudoku,sudoku_posibles,i,j,k,num))
		{
			sudoku[i][j][k] = num;
			poner_cero_posibles(sudoku_posibles,i,j,k);
			descartar_todos_candidatos(sudoku_posibles,i,j,k,num);
		}
	}
}

void linea_de_candidatos(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j, int k)
{
	int n;

	for(n = 1; n<10; n++)
	{
		if(es_candidato(sudoku,sudoku_posibles,i,j,k,n))
		{
			if(existen_otros_candidatos_fila(sudoku,sudoku_posibles,i,j,k,n) &&
				no_existen_otros_candidatos_matriz_fila(sudoku,sudoku_posibles,i,j,n))
			{
				descartar_fila(sudoku_posibles,i,j,n);
			}
			if(existen_otros_candidatos_columna(sudoku,sudoku_posibles,i,j,k,n) &&
				no_existen_otros_candidatos_matriz_columna(sudoku,sudoku_posibles,i,k,n))
			{
				descartar_columna(sudoku_posibles,i,k,n);
			}
		}
	}
}

void pareja_desnuda(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i,int j, int k)
{
	if(tiene_solo_dos_candidatos(sudoku,sudoku_posibles,i,j,k))
	{
		int t,h,g;
		doscandis candidatos;
		candidatos = extraer_dos_candidatos(sudoku_posibles,i,j,k);

		if(existen_otros_dos_candidatos_matriz(sudoku,sudoku_posibles,i,j,k,candidatos))
		{
			for(h = 0; h<3; h++)
			{
				for(g = 0; g<3; g++)
				{
					if(!sus_unicos_candidatos(sudoku,sudoku_posibles,i,h,g,candidatos.p,candidatos.q))
					{
						descartar_candidato(sudoku_posibles,i,h,g,candidatos.p);
						descartar_candidato(sudoku_posibles,i,h,g,candidatos.q);
					}
				}
			}
		}

		if(existen_otros_dos_candidatos_columna(sudoku,sudoku_posibles,i,j,k,candidatos))
		{
			if(i == 0 || i == 3 || i == 6)
				t = 0;
			else if(i == 1 || i == 4 || i == 7)
				t = 1;
			else
				t = 2;

			for(h = t; h<9; h+=3)
			{
				for(g = 0; g<3; g++)
				{
					if(!sus_unicos_candidatos(sudoku,sudoku_posibles,h,g,k,candidatos.p,candidatos.q))
					{
						descartar_candidato(sudoku_posibles,h,g,k,candidatos.p);
						descartar_candidato(sudoku_posibles,h,g,k,candidatos.q);
					}
				}
			}
		}

		if(existen_otros_dos_candidatos_fila(sudoku,sudoku_posibles,i,j,k,candidatos))
		{
			if(0 <= i && i <= 2)
				t = 0;
			else if(3 <= i && i <= 5)
				t = 3;
			else
				t = 6;

			for(h = t; h < t+3; h++)
			{
				for(g = 0; g < 3; g++)
				{
					if(!sus_unicos_candidatos(sudoku,sudoku_posibles,h,j,g,candidatos.p,candidatos.q))
					{
						descartar_candidato(sudoku_posibles,h,j,g,candidatos.p);
						descartar_candidato(sudoku_posibles,h,j,g,candidatos.q);
					}
				}
			}
		}
	}
}

void locked_candidate(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i,int j, int k)
{
	int h,g,n;
	for(n = 1; n < 10; n++)
	{
		if(es_candidato(sudoku,sudoku_posibles,i,j,k,n) &&
			existe_otro_igual_fila(sudoku,sudoku_posibles,i,j,k,n) &&
			no_existe_otro_igual_otras_filas(sudoku,sudoku_posibles,i,j,k,n))
		{
			for(h = 0; h<3; h++)
			{
				if(h != j)
				{
					for(g = 0; g<3; g++)
						descartar_candidato(sudoku_posibles,i,h,g,n);
				}
			}
		}

		if(es_candidato(sudoku,sudoku_posibles,i,j,k,n) &&
			existe_otro_igual_columna(sudoku,sudoku_posibles,i,j,k,n) &&
			no_existe_otro_igual_otras_columnas(sudoku,sudoku_posibles,i,j,k,n))
		{
			for(h = 0; h<3; h++)
			{
				if(h != k)
				{
					for(g = 0; g<3; g++)
						descartar_candidato(sudoku_posibles,i,g,h,n);
				}
			}
		}
	}
}

void descartar_todos_candidatos(posibles sudoku_posibles[9][3][3],int i, int j, int k,int num)
{
	int x,y;

	// descarta todos los candidatos n en sub-matriz 3x3
	for(x = 0; x <3; x++)
	{
		for(y = 0; y<3; y++)
		{
			descartar_candidato(sudoku_posibles,i,x,y,num);
		}
	}

	// descarta todos los candidatos n en columna k
	int p;
	if(i == 0 || i==3 || i == 6)
		p = 0;
	else if(i == 1 || i==4 || i == 7)
		p = 1;
	else
		p = 2;
	for(x = p; x <9; x+=3)
	{
		for(y = 0; y<3; y++)
		{
			descartar_candidato(sudoku_posibles,x,y,k,num);
		}
	}

	// descarta todos los candidatos n en fila j
	int t;
	if(0<= i && i<=2)
		t = 0;
	else if(i<=5)
		t = 3;
	else
		t = 6;

	for(x = t; x <t+3; x++)
	{
		for(y = 0; y<3; y++)
		{
			descartar_candidato(sudoku_posibles,x,j,y,num);
		}
	}
}

void descartar_candidato(posibles sudoku_posibles[9][3][3],int i,int j, int k,int num)
{
	switch(num)
	{
		case 1:
			sudoku_posibles[i][j][k].a = 0;
			break;
		case 2:
			sudoku_posibles[i][j][k].b = 0;
			break;
		case 3:
			sudoku_posibles[i][j][k].c = 0;
			break;
		case 4:
			sudoku_posibles[i][j][k].d = 0;
			break;
		case 5:
			sudoku_posibles[i][j][k].e = 0;
			break;
		case 6:
			sudoku_posibles[i][j][k].f = 0;
			break;
		case 7:
			sudoku_posibles[i][j][k].g = 0;
			break;
		case 8:
			sudoku_posibles[i][j][k].h = 0;
			break;
		case 9:
			sudoku_posibles[i][j][k].l = 0;
			break;
	}
}

void descartar_fila(posibles sudoku_posibles[9][3][3],int i,int j,int n)
{
	int t,h,g;

	if(0 <= i && i <= 2)
	{
		t = 0;
		for(h = t; h<t+3; h++)
		{
			for(g = 0; g<3; g++)
			{
				if(h != i)
					descartar_candidato(sudoku_posibles,h,j,g,n);
			}
		}
	}
	else if(i<= 5)
	{
		t = 3;
		for(h = t; h<t+3; h++)
		{
			for(g = 0; g<3; g++)
			{
				if(h != i)
					descartar_candidato(sudoku_posibles,h,j,g,n);
			}
		}
	}
	else
	{
		t = 6;
		for(h = t; h<t+3; h++)
		{
			for(g = 0; g<3; g++)
			{
				if(h != i)
					descartar_candidato(sudoku_posibles,h,j,g,n);
			}
		}
	}
}

void descartar_columna(posibles sudoku_posibles[9][3][3],int i,int k,int n)
{
	int t,h,g;

	if(i == 0 || i == 3 || i == 6)
	{
		t = 0;
		for(h = t; h<9; h+=3)
		{
			for(g = 0; g<3; g++)
			{
				if(h != i)
					descartar_candidato(sudoku_posibles,h,g,k,n);
			}
		}
	}
	else if(i == 1 || i == 4 || i == 7)
	{
		t = 1;
		for(h = t; h<9;h+=3)
		{
			for(g = 0; g<3; g++)
			{
				if(h != i)
					descartar_candidato(sudoku_posibles,h,g,k,n);
			}
		}
	}
	else
	{
		t = 2;
		for(h = t; h<9; h+=3)
		{
			for(g = 0; g<3; g++)
			{
				if(h != i)
					descartar_candidato(sudoku_posibles,h,g,k,n);
			}
		}
	}
}

doscandis extraer_dos_candidatos(posibles sudoku_posibles[9][3][3],int i, int j, int k)
{
	int counter = 0;
	doscandis dos_candidatos;
	dos_candidatos.p = 0;
	dos_candidatos.q = 0;

	if(sudoku_posibles[i][j][k].a != 0 && counter == 0)
	{
		dos_candidatos.p = sudoku_posibles[i][j][k].a;
		counter++;
	}
	else if(sudoku_posibles[i][j][k].a != 0 && counter == 1)
	{
		dos_candidatos.q = sudoku_posibles[i][j][k].a;
		return dos_candidatos;
	}

	if(sudoku_posibles[i][j][k].b != 0 && counter == 0)
	{
		dos_candidatos.p = sudoku_posibles[i][j][k].b;
		counter++;
	}
	else if(sudoku_posibles[i][j][k].b != 0 && counter == 1)
	{
		dos_candidatos.q = sudoku_posibles[i][j][k].b;
		return dos_candidatos;
	}

	if(sudoku_posibles[i][j][k].c != 0 && counter == 0)
	{
		dos_candidatos.p = sudoku_posibles[i][j][k].c;
		counter++;
	}
	else if(sudoku_posibles[i][j][k].c != 0 && counter == 1)
	{
		dos_candidatos.q = sudoku_posibles[i][j][k].c;
		return dos_candidatos;
	}

	if(sudoku_posibles[i][j][k].d != 0 && counter == 0)
	{
		dos_candidatos.p = sudoku_posibles[i][j][k].d;
		counter++;
	}
	else if(sudoku_posibles[i][j][k].d != 0 && counter == 1)
	{
		dos_candidatos.q = sudoku_posibles[i][j][k].d;
		return dos_candidatos;
	}

	if(sudoku_posibles[i][j][k].e != 0 && counter == 0)
	{
		dos_candidatos.p = sudoku_posibles[i][j][k].e;
		counter++;
	}
	else if(sudoku_posibles[i][j][k].e != 0 && counter == 1)
	{
		dos_candidatos.q = sudoku_posibles[i][j][k].e;
		return dos_candidatos;
	}

	if(sudoku_posibles[i][j][k].f != 0 && counter == 0)
	{
		dos_candidatos.p = sudoku_posibles[i][j][k].f;
		counter++;
	}
	else if(sudoku_posibles[i][j][k].f != 0 && counter == 1)
	{
		dos_candidatos.q = sudoku_posibles[i][j][k].f;
		return dos_candidatos;
	}

	if(sudoku_posibles[i][j][k].g != 0 && counter == 0)
	{
		dos_candidatos.p = sudoku_posibles[i][j][k].g;
		counter++;
	}
	else if(sudoku_posibles[i][j][k].g != 0 && counter == 1)
	{
		dos_candidatos.q = sudoku_posibles[i][j][k].g;
		return dos_candidatos;
	}

	if(sudoku_posibles[i][j][k].h != 0 && counter == 0)
	{
		dos_candidatos.p = sudoku_posibles[i][j][k].h;
		counter++;
	}
	else if(sudoku_posibles[i][j][k].h != 0 && counter == 1)
	{
		dos_candidatos.q = sudoku_posibles[i][j][k].h;
		return dos_candidatos;
	}

	if(sudoku_posibles[i][j][k].l != 0 && counter == 0)
	{
		dos_candidatos.p = sudoku_posibles[i][j][k].l;
		counter++;
	}
	else if(sudoku_posibles[i][j][k].l != 0 && counter == 1)
	{
		dos_candidatos.q = sudoku_posibles[i][j][k].l;
		return dos_candidatos;
	}
}

bool existe_otro_igual_columna(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int k,int n)
{
	int g;
	for(g = 0; g<3; g++)
	{
		if(es_candidato(sudoku,sudoku_posibles,i,g,k,n) && g != j)
			return true;
	}
	return false;
}

bool no_existe_otro_igual_otras_columnas(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int k,int n)
{
	int t,h,g;

	if(i == 0 || i == 3 || i == 6)
		t = 0;
	else if(i == 1 || i == 4 || i == 7)
		t = 1;
	else
		t = 2;

	for(h = t; h < 9; h+=3)
	{
		for(g = 0; g < 3; g++)
		{
			if(es_candidato(sudoku,sudoku_posibles,h,g,k,n) && h != i)
				return false;
		}
	}

	return true;
}

bool existe_otro_igual_fila(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int k,int n)
{
	int g;
	for(g = 0; g<3; g++)
	{
		if(es_candidato(sudoku,sudoku_posibles,i,j,g,n) && g != k)
			return true;
	}
	return false;
}

bool no_existe_otro_igual_otras_filas(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int k,int n)
{
	int t,h,g;

	if(0 <= i && i <= 2)
		t = 0;
	else if(3 <= i && i <= 5)
		t = 3;
	else
		t = 6;

	for(h = t; h < t+3; h++)
	{
		for(g = 0; g < 3; g++)
		{
			if(es_candidato(sudoku,sudoku_posibles,h,j,g,n) && h != i)
				return false;
		}
	}

	return true;
}

bool sus_unicos_candidatos(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k, int n, int m)
{
	doscandis candidatos;
	candidatos.p = 0;
	candidatos.q = 0;

	if(tiene_solo_dos_candidatos(sudoku,sudoku_posibles,i,j,k))
	{
		candidatos = extraer_dos_candidatos(sudoku_posibles,i,j,k);
		if(candidatos.p == n && candidatos.q == m || candidatos.p == m && candidatos.q == n)
			return true;
	}
	return false;
}

bool existen_otros_dos_candidatos_matriz(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k, doscandis candidatos)
{
	int h,g;
	doscandis candidatos2;
	candidatos2.p = 0;
	candidatos2.q = 0;

	for(h = 0; h<3; h++)
	{
		for(g = 0; g<3; g++)
		{
			if((h != j || g != k) && tiene_solo_dos_candidatos(sudoku,sudoku_posibles,i,h,g))
			{
				candidatos2 = extraer_dos_candidatos(sudoku_posibles,i,h,g);
				if(candidatos2.p == candidatos.p && candidatos2.q == candidatos.q || candidatos2.p == candidatos.q && candidatos2.q == candidatos.p)
					return true;
			}
		}
	}

	return false;
}

bool existen_otros_dos_candidatos_columna(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k, doscandis candidatos)
{
	int t,h,g;
	doscandis candidatos2;
	candidatos2.p = 0;
	candidatos2.q = 0;
	if(i == 0 || i == 3 || i == 6)
		t = 0;
	else if(i == 1 || i == 4 || i == 7)
		t = 1;
	else
		t = 2;

	for(h = t; h < 9; h += 3)
	{
		for(g = 0; g < 3; g++)
		{
			if(h != i && g != j && tiene_solo_dos_candidatos(sudoku,sudoku_posibles,h,g,k))
			{
				candidatos2 = extraer_dos_candidatos(sudoku_posibles,h,g,k);
				if(candidatos2.p == candidatos.p && candidatos2.q == candidatos.q)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool existen_otros_dos_candidatos_fila(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k, doscandis candidatos)
{
	int t,h,g;
	doscandis candidatos2;
	candidatos2.p = 0;
	candidatos2.q = 0;

	if(0 <= i && i <= 2)
		t = 0;
	else if(i <= 5)
		t = 3;
	else
		t = 6;

	for(h = t; h < t+3; h++)
	{
		for(g = 0; g < 3; g++)
		{
			if(h != i && g != k && tiene_solo_dos_candidatos(sudoku,sudoku_posibles,h,j,g))
			candidatos2 = extraer_dos_candidatos(sudoku_posibles,h,j,g);
			if(candidatos2.p == candidatos.p && candidatos2.q == candidatos.q)
				return true;
		}
	}

	return false;
}

bool tiene_solo_dos_candidatos(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j, int k)
{
	int counter = 0;

	if(sudoku[i][j][k] == 0)
	{
		if(sudoku_posibles[i][j][k].a != 0)
			counter++;
		if(sudoku_posibles[i][j][k].b != 0)
			counter++;
		if(sudoku_posibles[i][j][k].c != 0)
			counter++;
		if(sudoku_posibles[i][j][k].e != 0)
			counter++;
		if(sudoku_posibles[i][j][k].d != 0)
			counter++;
		if(sudoku_posibles[i][j][k].f != 0)
			counter++;
		if(sudoku_posibles[i][j][k].g != 0)
			counter++;
		if(sudoku_posibles[i][j][k].h != 0)
			counter++;
		if(sudoku_posibles[i][j][k].l != 0)
			counter++;
	}

	if(counter == 2)
		return true;
	else
		return false;
}

bool no_existen_otros_candidatos_matriz_columna(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int k,int n)
{
	int h,g;
	for(h = 0; h<3;h++)
	{
		if(h != k)
		{
			for(g = 0; g<3; g++)
			{
				if(es_candidato(sudoku,sudoku_posibles,i,g,h,n))
					return false;
			}
		}
	}

	return true;
}

bool no_existen_otros_candidatos_matriz_fila(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int n)
{
	int h,g;
	for(h = 0; h<3;h++)
	{
		for(g = 0; g<3; g++)
		{
			if(es_candidato(sudoku,sudoku_posibles,i,g,h,n) && g != j)
				return false;
		}
	}

	return true;
}

bool existen_otros_candidatos_columna(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j, int k,int n)
{
	int h,counter;
	counter = 0;

	for(h = 0; h<3; h++)
	{
		if(es_candidato(sudoku,sudoku_posibles,i,h,k,n))
			counter++;
	}
	if(counter >= 2)
		return true;
	else
		return false;
}

bool existen_otros_candidatos_fila(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j, int k,int n)
{
	int h,counter;
	counter = 0;
	for(h = 0; h<3; h++)
	{
		if(es_candidato(sudoku,sudoku_posibles,i,j,h,n))
			counter++;
	}
	if (counter >= 2)
		return true;
	else
		return false;
}

bool puedo_insertar_num(int sudoku[9][3][3],int i, int j,int k,int num)
{
	int x,y;

	// verifica en la sub-matriz 3x3 por otro elemento igual a num
	for(x = 0; x <3; x++)
	{
		for(y = 0; y<3; y++)
		{
			if(sudoku[i][x][y] == num)
			{
				return false;
			}
		}
	}

	// verifica en la columna por otro elemento igual a num
	int p;
	if(i == 0 || i==3 || i == 6)
		p = 0;
	else if(i == 1 || i==4 || i == 7)
		p = 1;
	else
		p = 2;
	for(x = p; x <9; x+=3)
	{
		for(y = 0; y<3; y++)
		{
			if(sudoku[x][y][k] == num)
			{
				return false;
			}
		}
	}

	// verifica en la fila por otro elemento igual a num
	int t;
	if(0<= i && i<=2)
		t = 0;
	else if(i<=5)
		t = 3;
	else
		t = 6;

	for(x = t; x <t+3; x++)
	{
		for(y = 0; y<3; y++)
		{
			if(sudoku[x][j][y] == num)
			{
				return false;
			}
		}
	}

	return true;
}

bool unico_para_insertar(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j,int k,int num)
{
	int x,y;
	bool res1,res2,res3;
	res1 = true;
	res2 = true;
	res3 = true;

	for(x = 0; x <3; x++)
	{
		for(y = 0; y<3; y++)
		{
			if(es_candidato(sudoku,sudoku_posibles,i,x,y,num) && sudoku[i][x][y] == 0)
			{
				if(!(x == j && y == k))
					res1 = false;
			}
		}
	}

	int p;
	if(i == 0 || i==3 || i == 6)
		p = 0;
	else if(i == 1 || i==4 || i == 7)
		p = 1;
	else
		p = 2;
	for(x = p; x <9; x+=3)
	{
		for(y = 0; y<3; y++)
		{
			if (es_candidato(sudoku,sudoku_posibles,x,y,k,num) && sudoku[x][y][k] == 0)
			{
				if(!(x == i && y == j))
					res2 = false;
			}
		}
	}

	int t;
	if(0<= i && i<=2)
		t = 0;
	else if(i<=5)
		t = 3;
	else
		t = 6;

	for(x = t; x <t+3; x++)
	{
		for(y = 0; y<3; y++)
		{
			if(es_candidato(sudoku,sudoku_posibles,x,j,y,num) && sudoku[x][j][y] == 0)
			{
				if(!(x == i && y == k))
					res3 = false;
			}
		}
	}

	return (res1 || res2 || res3);
}

bool es_candidato(int sudoku[9][3][3],posibles sudoku_posibles[9][3][3],int i, int j,int k,int num)
{
	if(sudoku_posibles[i][j][k].a == num && sudoku[i][j][k] == 0)
		return true;
	if(sudoku_posibles[i][j][k].b == num && sudoku[i][j][k] == 0)
		return true;
	if(sudoku_posibles[i][j][k].c == num && sudoku[i][j][k] == 0)
		return true;
	if(sudoku_posibles[i][j][k].e == num && sudoku[i][j][k] == 0)
		return true;
	if(sudoku_posibles[i][j][k].d == num && sudoku[i][j][k] == 0)
		return true;
	if(sudoku_posibles[i][j][k].f == num && sudoku[i][j][k] == 0)
		return true;
	if(sudoku_posibles[i][j][k].g == num && sudoku[i][j][k] == 0)
		return true;
	if(sudoku_posibles[i][j][k].h == num && sudoku[i][j][k] == 0)
		return true;
	if(sudoku_posibles[i][j][k].l == num && sudoku[i][j][k] == 0)
		return true;

	return false;
}

bool existen_ceros(int sudoku[9][3][3])
{
	int i,j,k;

	for(i = 0; i<9; i++)
	{
		for(j = 0; j<3; j++)
		{
			for(k = 0; k<3; k++)
			{
				if(sudoku[i][j][k] == 0)
					return true;
			}
		}
	}

	return false;
}

void init_posibles(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3])
{
	int i,j,k;

	for(i = 0; i<9; i++)
	{
		for(j = 0; j<3; j++)
		{
			for(k = 0; k<3; k++)
				if(sudoku[i][j][k] == 0)
					anotar_candidatos(sudoku,sudoku_posibles,i,j,k);
				else
					poner_cero_posibles(sudoku_posibles,i,j,k);
		}
	}
}

void anotar_candidatos(int sudoku[9][3][3], posibles sudoku_posibles[9][3][3],int i, int j, int k)
{
	if(puedo_insertar_num(sudoku,i,j,k,1))
		sudoku_posibles[i][j][k].a = 1;
	else
		sudoku_posibles[i][j][k].a = 0;


	if(puedo_insertar_num(sudoku,i,j,k,2))
		sudoku_posibles[i][j][k].b = 2;
	else
		sudoku_posibles[i][j][k].b = 0;


	if(puedo_insertar_num(sudoku,i,j,k,3))
		sudoku_posibles[i][j][k].c = 3;
	else
		sudoku_posibles[i][j][k].c = 0;


	if(puedo_insertar_num(sudoku,i,j,k,4))
		sudoku_posibles[i][j][k].d = 4;
	else
		sudoku_posibles[i][j][k].d = 0;


	if(puedo_insertar_num(sudoku,i,j,k,5))
		sudoku_posibles[i][j][k].e = 5;
	else
		sudoku_posibles[i][j][k].e = 0;


	if(puedo_insertar_num(sudoku,i,j,k,6))
		sudoku_posibles[i][j][k].f = 6;
	else
		sudoku_posibles[i][j][k].f = 0;


	if(puedo_insertar_num(sudoku,i,j,k,7))
		sudoku_posibles[i][j][k].g = 7;
	else
		sudoku_posibles[i][j][k].g = 0;


	if(puedo_insertar_num(sudoku,i,j,k,8))
		sudoku_posibles[i][j][k].h = 8;
	else
		sudoku_posibles[i][j][k].h = 0;


	if(puedo_insertar_num(sudoku,i,j,k,9))
		sudoku_posibles[i][j][k].l = 9;
	else
		sudoku_posibles[i][j][k].l = 0;
}

void poner_cero_posibles(posibles sudoku_posibles[9][3][3],int i, int j, int k)
{
		sudoku_posibles[i][j][k].a = 0;
		sudoku_posibles[i][j][k].b = 0;
		sudoku_posibles[i][j][k].c = 0;
		sudoku_posibles[i][j][k].d = 0;
		sudoku_posibles[i][j][k].e = 0;
		sudoku_posibles[i][j][k].f = 0;
		sudoku_posibles[i][j][k].g = 0;
		sudoku_posibles[i][j][k].h = 0;
		sudoku_posibles[i][j][k].l = 0;
}

void print_mat_3d(int sudoku[9][3][3])
{
	int i,j,k;

	printf("\n");
	printf("        o---------x---------x---------o\n");

	for(i = 0; i<3;i++)
	{
		printf("\t");
		printf("| ");
		for(j = 0; j <3;j++)
		{
			for(k = 0; k<3; k++)
			{
				printf("%2d",sudoku[j][i][k]);
			}
			printf("  | ");
		}
		printf("\n");
	}

	printf("        x---------x---------x---------x\n");

	for(i = 0; i<3;i++)
	{
		printf("\t");
		printf("| ");
		for(j = 3; j <6;j++)
		{
			for(k = 0; k<3; k++)
			{
				printf("%2d",sudoku[j][i][k]);;
			}
			printf("  | ");
		}
		printf("\n");
	}

	printf("        x---------x---------x---------x\n");

	for(i = 0; i<3;i++)
	{
		printf("\t");
		printf("| ");
		for(j = 6; j <9;j++)
		{
			for(k = 0; k<3; k++)
			{
				printf("%2d",sudoku[j][i][k]);;
			}
			printf("  | ");
		}
		printf("\n");
	}

	printf("        o---------x---------x---------o\n");
	printf("\n");
}
