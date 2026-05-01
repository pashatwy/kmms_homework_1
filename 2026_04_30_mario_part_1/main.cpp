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
	bool IsFly; //находится в полете или нет
	char cType; // тип объекта
	float horizonSpeed; //скорость по горизонтали
} TObject;


char map[mapHeight][mapWidth + 1];
TObject mario;

TObject *brick = NULL;
int brickLength;

TObject *moving = NULL;
int movingLength;

int level = 1;

void ClearMap()
{
	for (int i = 0; i < mapWidth; i++)
		map[0][i] = ' ';
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

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType) //инициализирует объект целиком
{
	SetObjectPos(obj, xPos, yPos);
	(*obj).width = oWidth;
	(*obj).height = oHeight;
	(*obj).vertSpeed = 0; //сначало не подвижен, верт. скорость = 0
	(*obj).cType = inType;
	(*obj).horizonSpeed = 0.2;
}

bool IsCollision(TObject o1, TObject o2); //такая функция есть, но она написана ниже
void CreateLevel(int lvl);

void VertMoveObject(TObject *obj)
{
	(*obj).IsFly = TRUE;
	(*obj).vertSpeed += 0.05; //ускорение
	SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed); //задает новую позицию изменяя y координату
	for (int i = 0; i < brickLength; i++)
		if (IsCollision( *obj, brick[i])) //проверка на столкновение
		{
			(*obj).y -= (*obj).vertSpeed;
			(*obj).vertSpeed = 0;
			(*obj).IsFly = FALSE;
			if (brick[i].cType == '+')
			{
				level += 1;
				if (level >2) level = 1;
				CreateLevel(level);
				Sleep(1000);
			}
			break;
		}
}

void DeleteMoving(int i) //при убийстве объект врага удалаяем из массива объектов
{
	movingLength--;
	moving[i] = moving[movingLength];
	moving = (TObject*)realloc( moving, sizeof(*moving) * movingLength);
}

void MarioCollision() //взаимодейстиве с движущимися объектами
{
	for (int i = 0; i < movingLength; i++)
		if (IsCollision(mario, moving[i]))
		{
			if (moving[i].cType == 'o')
			{
				if (	(mario.IsFly == TRUE)
					&& (mario.vertSpeed > 0)
					&& (mario.y + mario.height < moving[i].y + moving[i].height) * 0.5
					)
				{
					DeleteMoving(i);
					i--;
					continue;
				}
				else
					CreateLevel(level);
			}
		}
}

void HorizonMoveObject(TObject *obj)
{
	obj[0].x += obj[0].horizonSpeed;
	
	for (int i = 0; i < brickLength; i++)
		if (IsCollision(obj[0], brick[i]))
		{
			obj[0].x -= obj[0].horizonSpeed;
			obj[0].horizonSpeed = -obj[0].horizonSpeed;
			return;
		}
		TObject tmp = *obj;
		VertMoveObject(&tmp);
		if (tmp.IsFly == TRUE)
		{
			obj[0].x -= obj[0].horizonSpeed;
			obj[0].horizonSpeed = -obj[0].horizonSpeed;	
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
				map[j][i] = obj.cType;
}

void setCur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), coord); //задает позицию курсора
}

void HorizonMoveMap(float dx) //перемещение по горизонтали реализуется через перемещение самой карты
{
	mario.x -= dx;
	for (int i = 0; i < brickLength; i++) //если столкнулся - возвращаем в начальную позицию
		if (IsCollision(mario, brick[i]))
		{
			mario.x += dx;
			return;
		}
	mario.x += dx;
	
	for (int i = 0; i < brickLength; i++)
		brick[i].x += dx;	
	for (int i = 0; i < movingLength; i++)
		moving[i].x += dx;
}

bool IsCollision(TObject o1, TObject o2) //проверка на столкновение объектов
{
	return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
		((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

//добавляет новый объект в массив и возвращает в указатель
TObject *GetNewBrick()
{
	brickLength++;
	brick = (TObject*)realloc( brick, sizeof(*brick) * brickLength);
	return brick + brickLength -1;
}

TObject *GetNewMoving()
{
	movingLength++;
	moving = (TObject*)realloc( moving, sizeof(*moving) * movingLength);
	return moving + movingLength -1;
}

void CreateLevel(int lvl) //создаем уровень
{
	InitObject(&mario, 39, 10, 3, 3, '@');
	
	if (lvl == 1)
	{
		
		brickLength = 0;
		InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
		InitObject(GetNewBrick(), 60, 15, 10, 10, '#');
		InitObject(GetNewBrick(), 80, 20, 20, 5, '#');
		InitObject(GetNewBrick(), 120, 15, 10, 10, '#');
		InitObject(GetNewBrick(), 150, 20, 40, 5, '#');
		InitObject(GetNewBrick(), 210, 15, 10, 10, '+');
		movingLength = 0;
		InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 65, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 160, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 175, 10, 3, 2, 'o');
		
	}
	if (lvl == 2)
	{
		brickLength = 0;
		InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
		InitObject(GetNewBrick(), 80, 20, 15, 5, '#');
		InitObject(GetNewBrick(), 120, 15, 15, 10, '#');
		InitObject(GetNewBrick(), 160, 10, 15, 15, '+');
		movingLength = 0;
		InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 50, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 90, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 130, 10, 3, 2, 'o');
	}
}

int main()
{
	CreateLevel(level);
	
	do
	{
		ClearMap();

		
		if ((mario.IsFly == FALSE) && (GetKeyState(VK_SPACE) < 0)) mario.vertSpeed = -1; //прыжок. Дает отрицатильную скорость на пробел 
		if (GetKeyState('A') < 0) HorizonMoveMap(1);
		if (GetKeyState('D') < 0) HorizonMoveMap(-1);
		
		if (mario.y > mapHeight) CreateLevel(level);
		
		VertMoveObject(&mario);
		MarioCollision();
		
		for (int i = 0; i < brickLength; i++) //проходясь по всем brick
			PutObjectOnMap(brick[i]);
		for (int i = 0; i < movingLength; i++)
		{
			VertMoveObject(moving +i);
			HorizonMoveObject(moving + i);
			if (moving[i].y > mapHeight) //удаляем врага, если он ниже экрана
			{
				DeleteMoving(i);
				i--;
				continue;
			}
			PutObjectOnMap(moving[i]);
		}
		PutObjectOnMap(mario); //помещаем персонажа, после отчистки карты
		
		setCur(0,0);
		ShowMap();
		
		Sleep(10); //замедлим, что б видеть изменения
	}
	while (GetKeyState(VK_ESCAPE) >= 0);
		
	
	return 0;
}