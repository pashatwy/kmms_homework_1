#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h> 

#define mapWidth 80
#define mapHeight 25

typedef struct SObject {
	float x, y;
	float width, height;
	float vertSpeed; //вертикальная скорость
} TObject;


char map[mapHeight][mapWidth + 1];
TObject mario;
TObject brick[1];

void ClearMap()
{
	for (int i = 0; i < mapWidth; i++)
		map[0][i] = '.';
	map[0][mapWidth] = '\0';
	for (int j = 1; j < mapHeight; j++)
		sprintf(map[j], map[0]);
}

void ShowMap()
{
	map[mapHeight - 1][mapWidth - 1] = '\0';
	for (int j = 0; j < mapHeight; j++)
		printf("%s\n", map[j]);
}

void SetObjectPos(TObject *obj, float xPos, float yPos) //задает позицию объекта
{
	(*obj).x = xPos;
	(*obj).y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight) //инициализирует объект целиком
{
	SetObjectPos(obj, xPos, yPos);
	(*obj).width = oWidth;
	(*obj).height = oHeight;
	(*obj).vertSpeed = 0; //сначало не подвижен, верт. скорость = 0
}

bool IsCollision(TObject o1, TObject o2); //такая функция есть, но она написана ниже

void VertMoveObject(TObject *obj)
{
	(*obj).vertSpeed += 0.05; //ускорение
	SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed); //задает новую позицию изменяя y координату
	if (IsCollision( *obj, brick[0])) //проверка на столкновение
	{
		(*obj).y -= (*obj).vertSpeed;
		(*obj).vertSpeed = 0;
	}
}

bool IsPosInMap(int x, int y)
{
	return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

void PutObjectOnMap(TObject obj)
{
	int ix = (int)round(obj.x); //round - округление - результат в виде вещественного числа
	int iy = (int)round(obj.y);
	int iWidth = (int)round(obj.width);
	int iHeight = (int)round(obj.height);

	for (int i = ix; i < (ix + iWidth); i++)
		for (int j = iy; j < (iy + iHeight); j++)
			if (IsPosInMap(i,j))
				map[j][i] = '@';
}

void setCur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), coord); //задает позицию курсора
}

bool IsCollision(TObject o1, TObject o2) //проверка на столкновение объектов
{
	return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
		((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

int main()
{
	InitObject(&mario, 39, 10, 3, 3);
	InitObject(brick, 20, 20, 40 ,5); //инициализируем платформу
	
	do
	{
		ClearMap();
		VertMoveObject(&mario);
		PutObjectOnMap(brick[0]);
		PutObjectOnMap(mario); //помещаем персонажа, после отчистки карты
		
		setCur(0,0);
		ShowMap();
		
		Sleep(10); //замедлим, что б видеть изменения
	}
	while (GetKeyState(VK_ESCAPE) >= 0);
		
	
	return 0;
}