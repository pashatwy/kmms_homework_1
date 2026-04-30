#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#define mapWidth 80
#define mapHeight 25

typedef struct SObject {
	float x, y;
	float width, height;
} TObject;


char map[mapHeight][mapWidth + 1];
TObject mario;


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
}

void PutObjectOnMap(TObject obj)
{
	int ix = (int)round(obj.x); //round - округление - результат в виде вещественного числа
	int iy = (int)round(obj.y);
	int iWidth = (int)round(obj.width);
	int iHeight = (int)round(obj.height);

	for (int i = ix; i < (ix + iWidth); i++)
		for (int j = iy; j < (iy + iHeight); j++)
			map[j][i] = '@';
}

int main()
{
	InitObject(&mario, 39, 10, 3, 3);
	ClearMap();
	PutObjectOnMap(mario); //помещаем персонажа, после отчистки карты
	ShowMap();
	return 0;
}