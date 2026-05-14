#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h> 

typedef struct SObject {
	float x, y;
	float width, height;
	float vertSpeed;
	bool IsFly;
	char cType;
	float horizonSpeed;
} TObject;

void setCur(int x, int y);
bool isPosInMap(int x, int y, int mapWidth, int mapHeight);
bool isCollision(const TObject o1, const TObject o2);

void setObjectPos(TObject *obj, float xPos, float yPos);
void initObject(TObject& obj, float xPos, float yPos, float oWidth, float oHeight, char inType);
void createLevel(const int lvl, int *score, int *maxLvl, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject& mario);

void ClearMap(int mapWidth, int mapHeight, char **map);
void ShowMap(int mapWidth, int mapHeight, char **map);
void putObjectOnMap(const TObject *obj, int mapWidth, int mapHeight, char **map);
void PutScoreOnMap(int *score, char **map);

void MarioCollision(const int level, int *score, int *maxLvl, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject& mario);
void VertMoveObject(TObject& obj, int *level, int *score, int *maxLvl, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject& mario);
void HorizonMoveObject(TObject& obj, int *level, int *score, int *maxLvl, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject &mario);
void HorizonMoveMap(float dx, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject& mario);
void PlayerDead(const int level, int *score, int *maxLvl, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject& mario);

void DeleteMoving(int i, int *movingLength, TObject* &moving);
TObject &GetNewMoving(TObject* &moving, int *movingLength); //& !!!
TObject &GetNewBrick(TObject* &brick, int *brickLength);

int main()
{
	const int mapWidth = 80;
	const int mapHeight = 25;

	char **map = (char**)malloc(sizeof(char*) * mapHeight);
	
	for (int i = 0; i < mapHeight; i++) {
        map[i] = (char*)malloc(sizeof(char) * (mapWidth + 1));
    }
	
	TObject mario;
	
	TObject *brick = NULL;
	int brickLength = 0;

	TObject *moving = NULL;
	int movingLength = 0;

	int maxLvl = 1;
	int score = 0;
	int level = 1;
	
	PutScoreOnMap(&score, map);
	
	createLevel(level, &score, &maxLvl, &brickLength, brick, &movingLength, moving, mario);
	
	do
	{
		ClearMap(mapWidth, mapHeight, map);

		
		if (((mario).IsFly == FALSE) && (GetKeyState(VK_SPACE) < 0)) (mario).vertSpeed = -1;
		if (GetKeyState('A') < 0) HorizonMoveMap(1, &brickLength, brick, &movingLength, moving, mario);
		if (GetKeyState('D') < 0) HorizonMoveMap(-1, &brickLength, brick, &movingLength, moving, mario);
		
		if (mario.y > mapHeight) PlayerDead(level, &score, &maxLvl, &brickLength, brick, &movingLength, moving, mario);
		
		VertMoveObject(mario, &level, &score, &maxLvl, &brickLength, brick, &movingLength, moving, mario);
		MarioCollision(level, &score, &maxLvl, &brickLength, brick, &movingLength, moving, mario);
		
		for (int i = 0; i < brickLength; i++) 
			putObjectOnMap(&brick[i], mapWidth, mapHeight, map);
		for (int i = 0; i < movingLength; i++)
		{
			VertMoveObject(moving[i], &level, &score, &maxLvl, &brickLength, brick, &movingLength, moving, mario);
			HorizonMoveObject(moving[i], &level, &score, &maxLvl, &brickLength, brick, &movingLength, moving, mario);
			if (moving[i].y > mapHeight)
			{
				DeleteMoving(i, &movingLength, moving);
				i--;
				continue;
			}
			putObjectOnMap(&moving[i], mapWidth, mapHeight, map);
		}
		putObjectOnMap(&mario, mapWidth, mapHeight, map);
		PutScoreOnMap(&score,map );
		
		setCur(0,0);
		ShowMap(mapWidth, mapHeight, map);
		
		Sleep(10);
	}
	while (GetKeyState(VK_ESCAPE) >= 0);
	
	free(brick);
	free(moving);
	
	for (int i = 0; i < mapHeight; i++)
		free(map[i]);
	free(map);
	
	return 0;
}

void setCur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool isPosInMap(int x, int y, int mapWidth, int mapHeight)
{
	return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

bool isCollision(const TObject o1, const TObject o2) {
    return (o1.x + o1.width > o2.x) && (o1.x < o2.x + o2.width) &&
           (o1.y + o1.height > o2.y) && (o1.y < o2.y + o2.height);
}


void setObjectPos(TObject& obj, float xPos, float yPos)
{
	obj.x = xPos;
	obj.y = yPos;
}

void initObject(TObject& obj, float xPos, float yPos, float oWidth, float oHeight, char inType)
{
	setObjectPos(obj, xPos, yPos);
	obj.width = oWidth;
	obj.height = oHeight;
	obj.vertSpeed = 0;
	obj.cType = inType;
	obj.horizonSpeed = 0.2;
}

void createLevel(const int lvl, int *score, int *maxLvl, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject& mario)
{
	*brickLength = 0;
	free(brick);
	brick = nullptr;
	
	*movingLength = 0;
	free(moving);
	moving = nullptr;
	
	initObject(mario, 39, 10, 3, 3, '@');
	*score = 0;
	
	if (lvl == 1)
	{
		initObject(GetNewBrick(brick, brickLength), 20, 20, 40, 5, '#');
		initObject(GetNewBrick(brick, brickLength), 30, 10, 5, 3, '?');
		initObject(GetNewBrick(brick, brickLength), 50, 10, 5, 3, '?');		
		initObject(GetNewBrick(brick, brickLength), 60, 15, 40, 10, '#');
		initObject(GetNewBrick(brick, brickLength), 60, 5, 10, 3, '-');
		initObject(GetNewBrick(brick, brickLength), 70, 5, 5, 3, '?');
		initObject(GetNewBrick(brick, brickLength), 75, 5, 5, 3, '-');
		initObject(GetNewBrick(brick, brickLength), 80, 5, 5, 3, '?');
		initObject(GetNewBrick(brick, brickLength), 85, 5, 10, 3, '-');
		initObject(GetNewBrick(brick, brickLength), 100, 20, 20, 5, '#');
		initObject(GetNewBrick(brick, brickLength), 120, 15, 10, 10, '#');
		initObject(GetNewBrick(brick, brickLength), 150, 20, 40, 5, '#');
		initObject(GetNewBrick(brick, brickLength), 210, 15, 10, 10, '+');

		initObject(GetNewMoving(moving, movingLength), 25, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 80, 10, 3, 2, 'o');
	}
	
	
	if (lvl == 2)
	{
		initObject(GetNewBrick(brick, brickLength), 20, 20, 40, 5, '#');
		initObject(GetNewBrick(brick, brickLength), 60, 15, 10, 10, '#');
		initObject(GetNewBrick(brick, brickLength), 80, 20, 20, 5, '#');
		initObject(GetNewBrick(brick, brickLength), 120, 15, 10, 10, '#');
		initObject(GetNewBrick(brick, brickLength), 150, 20, 40, 5, '#');
		initObject(GetNewBrick(brick, brickLength), 210, 15, 10, 10, '+');
		
		initObject(GetNewMoving(moving, movingLength), 25, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 80, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 65, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 120, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 160, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 175, 10, 3, 2, 'o');
		
	}
	if (lvl == 3)
	{
		initObject(GetNewBrick(brick, brickLength), 20, 20, 40, 5, '#');
		initObject(GetNewBrick(brick, brickLength), 80, 20, 15, 5, '#');
		initObject(GetNewBrick(brick, brickLength), 120, 15, 15, 10, '#');
		initObject(GetNewBrick(brick, brickLength), 160, 10, 15, 15, '+');
		
		initObject(GetNewMoving(moving, movingLength), 25, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 50, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 80, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 90, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 120, 10, 3, 2, 'o');
		initObject(GetNewMoving(moving, movingLength), 130, 10, 3, 2, 'o');
	}
	
	*maxLvl = 3;
}


void ClearMap(int mapWidth, int mapHeight, char **map)
{
	for (int i = 0; i < mapWidth; i++)
		map[0][i] = ' ';
	map[0][mapWidth] = '\0';
	for (int j = 1; j < mapHeight; j++)
		sprintf(map[j], map[0]);
}

void ShowMap(int mapWidth, int mapHeight, char **map)
{
	map[mapHeight - 1][mapWidth - 1] = '\0';
	for (int j = 0; j < mapHeight; j++)
		printf("%s\n", map[j]);
}

void putObjectOnMap(const TObject *obj, int mapWidth, int mapHeight, char **map)
{
	int ix = (int)round(obj->x);
	int iy = (int)round(obj->y);
	int iWidth = (int)round(obj->width);
	int iHeight = (int)round(obj->height);

	for (int i = ix; i < (ix + iWidth); i++)
		for (int j = iy; j < (iy + iHeight); j++)
			if (isPosInMap(i,j, mapWidth, mapHeight))
				map[j][i] = obj->cType;
}

void PutScoreOnMap(int *score, char **map)
{
	char c[30];
	sprintf(c, "Score: %d", *score);
	int len = strlen(c);
	for (int i = 0; i < len; i++)
	{
		map[1][i+5] = c[i];
	}
}


void MarioCollision(const int level, int *score, int *maxLvl, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject& mario)
{
	for (int i = 0; i < (*movingLength); i++)
		if (isCollision(mario, moving[i]))
		{
			if (moving[i].cType == 'o')
			{
				if (	(mario.IsFly == TRUE)
					&& (mario.vertSpeed > 0)
					&& (mario.y + mario.height < moving[i].y + moving[i].height) * 0.5
					)
				{
					*score += 50;
					DeleteMoving(i, movingLength, moving);
					i--;
					continue;
				}
				else
					PlayerDead(level, score, maxLvl, brickLength, brick, movingLength, moving, mario);
			}
			
			if (moving[i].cType == '$')
			{
				*score += 100;
				DeleteMoving(i, movingLength, moving);
				i--;
				continue;
			}
		}
}

void VertMoveObject(TObject& obj, int *level, int *score, int *maxLvl, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject& mario)
{
	obj.IsFly = TRUE;
	obj.vertSpeed += 0.05;
	setObjectPos(obj, obj.x, obj.y + obj.vertSpeed);
	for (int i = 0; i < *brickLength; i++)
		if (isCollision(obj, brick[i]))
		{
			if(obj.vertSpeed > 0)
				obj.IsFly = FALSE;
			
			if( (brick[i].cType == '?') && (obj.vertSpeed < 0) && (&obj == &mario) )
			{
				brick[i].cType = '-';
				initObject(GetNewMoving(moving, movingLength), brick[i].x, brick[i].y-3, 3, 2, '$');
				moving[(*movingLength) - 1].vertSpeed = -0.7;
			}
			
			obj.y -= obj.vertSpeed;
			obj.vertSpeed = 0;
			
			if (brick[i].cType == '+')
			{
				*level += 1;
				if (*level > *maxLvl) *level = 1;
				
				Sleep(500);
				createLevel(*level, score, maxLvl, brickLength, brick, movingLength, moving, mario);
			}
			break;
		}
}

void HorizonMoveObject(TObject& obj, int *level, int *score, int *maxLvl, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject &mario)
{
	obj.x += obj.horizonSpeed;
	
	for (int i = 0; i < *brickLength; i++)
		if (isCollision(obj, brick[i]))
		{
			obj.x -= obj.horizonSpeed;
			obj.horizonSpeed = -obj.horizonSpeed;
			return;
		}
	if (obj.cType == 'o')
	{
		TObject tmp = obj;
		VertMoveObject(tmp, level, score, maxLvl, brickLength, brick, movingLength, moving, mario);
		if (tmp.IsFly == TRUE)
		{
			obj.x -= obj.horizonSpeed;
			obj.horizonSpeed = -obj.horizonSpeed;	
		}
	}
}

void HorizonMoveMap(float dx, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject& mario)
{
	mario.x -= dx;
	for (int i = 0; i < *brickLength; i++)
		if (isCollision(mario, brick[i]))
		{
			mario.x += dx;
			return;
		}
	mario.x += dx;
	
	for (int i = 0; i < *brickLength; i++)
		brick[i].x += dx;	
	for (int i = 0; i < *movingLength; i++)
		moving[i].x += dx;
}

void PlayerDead(const int level, int *score, int *maxLvl, int *brickLength, TObject* &brick, int *movingLength, TObject* &moving, TObject& mario)
{
	Sleep(500);
	createLevel(level, score, maxLvl, brickLength, brick, movingLength, moving, mario);
}


void DeleteMoving(int i, int *movingLength, TObject* &moving)
{
	(*movingLength)--;
	moving[i] = moving[*movingLength];
	moving = (TObject*)realloc(moving, sizeof(TObject) * (*movingLength));
}

TObject& GetNewMoving(TObject* &moving, int *movingLength)
{
    (*movingLength)++;
    moving = (TObject*)realloc(moving, sizeof(TObject) * (*movingLength));
    return moving[(*movingLength) - 1]; 
}

TObject& GetNewBrick(TObject* &brick, int *brickLength)
{
    (*brickLength)++;
    brick = (TObject*)realloc(brick, sizeof(TObject) * (*brickLength));
    return brick[(*brickLength) - 1];
}